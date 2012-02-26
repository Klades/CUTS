// $Id: Setaf_Lang_Compiler.h

#ifndef _CUTS_SETAF_LANG_COMPILER_H_
#define _CUTS_SETAF_LANG_COMPILER_H_

#include <sstream>
#include "Setaf_Format.h"
#include "ace/SString.h"
#include "Setaf_Utils.h"
#include "Setaf_export.h"


/**
 * @ingroup SETAF_Common
 *
 * @class CUTS_Setaf_Lang_Compiler
 *
 * Represent language compiler.
 */
class CUTS_SETAF_Export CUTS_Setaf_Lang_Compiler
{
public:
  // Default Constructor
  CUTS_Setaf_Lang_Compiler ();

  // Destructor
  ~CUTS_Setaf_Lang_Compiler (void);

  /**
   * Compiling the adaptation spec
   *
   * @param[in]   file_content    content of the file
   * @param[in]   entries         list of datapoints
   * @param[in]   relations       list of relations
   * @param[in]   var_decls       list of variable declarations
   * @param[in]   codes           list of adaptation code blocks
   * @param[in]   init_code       Initialization code
   * @param[in]   reset_code      Reset code
   */
  bool compile (const char * file_content,
                CUTS_SETAF_UTILS::Setaf_Entries & entries,
                CUTS_SETAF_UTILS::Setaf_Relations & relations,
                CUTS_SETAF_UTILS::string_vector & var_decls,
                CUTS_SETAF_UTILS::Setaf_Code & codes,
                std::string & init_code,
                std::string & reset_code);
};

#endif  // !defined _CUTS_SETAF_LANG_COMPILER_H_