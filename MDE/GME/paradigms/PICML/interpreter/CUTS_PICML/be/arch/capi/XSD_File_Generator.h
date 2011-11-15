// -*- C++ -*-

//=============================================================================
/**
 * @file          XSD_File_Generator.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _XSD_FILE_GENERATOR_H_
#define _XSD_FILE_GENERATOR_H_

#include "PICML/PICML.h"
#include "../../UDM_Abstract_Type_Dispatcher_T.h"
#include <fstream>
#include <stack>

/**
 * @class XSD_File_Generator
 *
 * Visitor that is responsible for generating the XSD file the event types
 * published/subscribed by clients. The generated XSD files need to be
 * registered with the server before the clients execute. Also, the
 * generated .xsd files are used by Caster (www.castor.org) to generate
 * Java bindings for XML. This allows clients to with with Java object instead
 * of verbose XML to manage an event's metadata.
 */
class XSD_File_Generator : public PICML::Visitor
{
public:
  /// Default constructor.
  XSD_File_Generator (const std::string & outdir);

  /// Destructor.
  virtual ~XSD_File_Generator (void);

  // Visit an Event element.
  void Visit_Event (const PICML::Event & event);

  void Visit_Member (const PICML::Member & member);

  void Visit_String (const PICML::String & );

  void Visit_LongInteger (const PICML::LongInteger & );

  void Visit_Byte (const PICML::Byte &);

  void Visit_ShortInteger (const PICML::ShortInteger &);

  void Visit_Aggregate (const PICML::Aggregate & );

  void Visit_Enum (const PICML::Enum & );

  void Visit_EnumValue (const PICML::EnumValue & );

private:
  void Visit_Aggregate_i (const PICML::Aggregate & aggr);

  void Visit_Event_i (const PICML::Event & event, bool anonymous = false);

  void Visit_Enum_i (const PICML::Enum & e);

  /// Output directory for the generated XML mapping.
  const std::string & outdir_;

  /// Output file for the XML mapping.
  std::ofstream fout_;

  /// Complex types that have been visited.
  std::set <PICML::Aggregate> seen_complex_types_;

  /// Complex types that need a mapping.
  std::stack <PICML::Aggregate> complex_types_;

  /// Enum types that need mapping.
  std::set <PICML::Enum> enum_types_;

  /// Dispatcher for abstract element types.
  UDM_Abstract_Type_Dispatcher_T <XSD_File_Generator> dispatcher_;
};

#endif  // !defined _CUTS_BE_CAPI_XSD_FILE_GENERATOR_H_
