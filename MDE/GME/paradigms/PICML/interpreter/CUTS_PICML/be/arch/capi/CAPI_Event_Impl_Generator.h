//-*- C++ -*-

//=============================================================================
/**
 * @file          CAPI_Event_Impl_Generator.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CAPI_EVENT_IMPL_GENERATOR_H_
#define _CUTS_BE_CAPI_EVENT_IMPL_GENERATOR_H_

#include "PICML/PICML.h"
#include "CCF/CodeGenerationKit/IndentationJava.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"
#include <fstream>

/**
 * @class CUTS_BE_CAPI_Event_Impl_Generator
 */
class CUTS_BE_CAPI_Event_Impl_Generator : public PICML::Visitor
{
public:
  /**
   * Initializing constructor.
   */
  CUTS_BE_CAPI_Event_Impl_Generator (const std::string & outdir);

  virtual ~CUTS_BE_CAPI_Event_Impl_Generator (void);

  virtual void Visit_Event (const PICML::Event & event);

private:
  void write_includes (void);

  void write_constructors (void);

  void write_static (const PICML::Event & event);

  void write_getter_methods (void);

  /// Output directory for the implemenatation.
  std::string outdir_;

  /// Output file stream for the implementation.
  std::ofstream outfile_;

  /// Indentation implanter.
  typedef Indentation::Implanter <
    Indentation::Java, char> _formatter_type;

  /// Pointer to the formatter.
  std::auto_ptr <_formatter_type> formatter_;

  std::string impl_;

  std::string type_;
};

#endif  // !defined _CUTS_BE_CAPI_EVENT_IMPL_GENERATOR_H_
