// $Id: Cpp.h

#ifndef _CUTS_SETAF_FORMAT_CPP_H_
#define _CUTS_SETAF_FORMAT_CPP_H_

#include <fstream>
#include "CCF/CodeGenerationKit/IndentationCxx.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"

namespace CUTS_SETAF_CPP
{
  /**
   * Structure for defining the C++ context.
   */
  struct Context
  {
    typedef Indentation::Implanter <Indentation::Cxx, char> formatter_type;

    std::ofstream header_;

    std::auto_ptr < formatter_type > header_formatter_;

    std::ofstream source_;

    std::auto_ptr < formatter_type > source_formatter_;

    std::ofstream project_;

    std::ofstream workspace_;

  };

  typedef struct Context Context_t;

  /**
   * Generate an include string using the provided filename. The
   * filename should not include the extension.
   *
   * @param[in]       filename        Filename to include
   */
  std::string include (const std::string & filename);

  /**
   * Generate a single line comment (//) using the provide string.
   *
   * @param[in]       comment         String to comment
   */
  std::string single_line_comment (const std::string & comment);

  /**
   * Generate a function header using the function name.
   *
   * @param[in]       comment         String to comment
   */
  std::string function_header (const std::string & func);
}

#endif  // !defined _CUTS_SETAF_FORMAT_CPP_H_