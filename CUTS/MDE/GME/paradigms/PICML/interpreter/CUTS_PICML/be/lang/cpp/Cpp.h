// -*- C++ -*-

//=============================================================================
/**
 * @file        Cpp.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CPP_H_
#define _CUTS_BE_CPP_H_

#include <fstream>
#include <stack>
#include "PICML/PICML.h"
#include "../../Port_Manager_T.h"
#include "CCF/CodeGenerationKit/IndentationCxx.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"
#include "Cpp_export.h"

namespace CUTS_BE_CPP
{
  /**
   * Structure for defining the C++ context.
   */
  struct CUTS_BE_CPP_Export Context
  {
    typedef Indentation::Implanter <Indentation::Cxx, char> formatter_type;

    std::ofstream header_;

    std::auto_ptr < formatter_type > header_formatter_;

    std::ofstream source_;

    std::auto_ptr < formatter_type > source_formatter_;

    std::stack <size_t> branches_;

    size_t arg_count_;

    bool skip_action_;

    /// Manager for mapping port types to their scoped name.
    CUTS_UDM_Port_Manager_T <PICML::OutEventPort> outevent_mgr_;
  };

  /**
   * Generate an include string using the provided filename. The
   * filename should not include the extension.
   *
   * @param[in]       filename        Filename to include
   */
  CUTS_BE_CPP_Export std::string include (const std::string & filename);

  /**
   * Generate a single line comment (//) using the provide string.
   *
   * @param[in]       comment         String to comment
   */
  CUTS_BE_CPP_Export std::string single_line_comment (const std::string & comment);

  /**
   * Generate the scope of a named type.
   *
   * @param[in]     type            Named type of interest
   * @param[in]     separator       Separator element
   * @param[in]     leading         Include leading separator
   */
  CUTS_BE_CPP_Export std::string scope (const PICML::NamedType & type,
                                        const std::string & separator = "::",
                                        bool leading = true);

  /**
   * Generate the fully qualified name for the type.
   *
   * @param[in]     type            Named type of interest
   * @param[in]     separator       Separator element
   * @param[in]     leading         Include leading separator
   */
  CUTS_BE_CPP_Export std::string fq_type (const PICML::NamedType & type,
                                          const std::string & separator = "::",
                                          bool leading = true);

  /**
   * Generate a function header using the provide string.
   */
  CUTS_BE_CPP_Export std::string function_header (const std::string & func);
}

#endif  // !defined _CUTS_BE_CPP_H_
