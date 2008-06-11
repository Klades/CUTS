// -*- C++ -*-

//=============================================================================
/**
 * @file        XML_Mapping_File_Generator.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _XML_MAPPING_FILE_GENERATOR_H_
#define _XML_MAPPING_FILE_GENERATOR_H_

#include "PICML/PICML.h"
#include "../UDM_Abstract_Type_Dispatcher_T.h"
#include <fstream>

/**
 * @class XML_Mapping_File_Geneator
 *
 * Visitor that is responsible for generating the XML mapping file for
 * Castor (www.castor.org). The generated mapping file is used by Castor
 * to marshal/unmarshal Java objects to/from XML. This allows CAPI
 * clients to operate with POJOs instead of clunky XML when manipulating
 * the metadata for information objects.
 */
class XML_Mapping_File_Generator : public PICML::Visitor
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       outdir        The target output directory.
   */
  XML_Mapping_File_Generator (const std::string & outdir);

  /// Destructor.
  virtual ~XML_Mapping_File_Generator (void);

  // Visit an Event element.
  void Visit_Event (const PICML::Event & event);

  void Visit_Member (const PICML::Member & member);

  void Visit_String (const PICML::String & );

  void Visit_LongInteger (const PICML::LongInteger & );

  void Visit_Byte (const PICML::Byte &);

  void Visit_ShortInteger (const PICML::ShortInteger &);

private:
  /// Output directory for the generated XML mapping.
  const std::string & outdir_;

  /// Output file for the XML mapping.
  std::ofstream outfile_;

  /// Complex types that need a mapping.
  std::set <PICML::Aggregate> complex_types_;

  /// Dispatcher for abstract element types.
  UDM_Abstract_Type_Dispatcher_T <XML_Mapping_File_Generator> dispatcher_;
};

#endif  // !defined _CAPI_XML_MAPPING_FILE_GENERATOR_H_
