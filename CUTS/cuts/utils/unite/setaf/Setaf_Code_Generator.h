#ifndef _CUTS_SETAF_CODE_GENERATOR_H_
#define _CUTS_SETAF_CODE_GENERATOR_H_

#include <sstream>
#include "Setaf_Format.h"
#include "Cpp.h"
#include "Setaf_Utils.h"

/**
 *
 *
 * @class CUTS_Setaf_Code_Generator
 */


class CUTS_Setaf_Code_Generator
{
public:

  /**
   * Initializing constructor
   *
   * @param[in]   output_dir    Location to store the generated code
   * @param[in]   adapter_name  Name of the adapter
   */
  CUTS_Setaf_Code_Generator (const char * output_dir,
                             const char * adapter_name);

  // Destructor
  ~CUTS_Setaf_Code_Generator (void);

  /**
   * Set new Datapoints
   *
   * @param[in]   entries   set of datapoints
   */
  void entries (CUTS_SETAF_UTILS::Setaf_Entries & entries);

  /**
   * Set new Datapoints
   *
   * @param[in]   entries   set of datapoints created from adapter
   */
  void relations (CUTS_SETAF_UTILS::Setaf_Relations & relations);

  /**
   * Set new relations
   *
   * @param[in]   relations   set of new relations created from adapter
   */
  void setaf_code (CUTS_SETAF_UTILS::Setaf_Code & setaf_code);

  /**
   * Set new variable declarations
   *
   * @param[in]   variable_decls    set of variable declarations in adapter
   */
  void variable_decls (CUTS_SETAF_UTILS::string_vector & variable_decls);

  /**
   * Set Initialization code
   *
   * @param[in]   init_str    Initialization code from adapter
   */
  void init_str (std::string & init_str);

  /**
   * Set Reset code
   *
   * @param[in]   reset_str   Reset code from adapter
   */
  void reset_str (std::string & reset_str);

  /**
   * Set the Ctx for code generation
   *
   * @param[in]   ctx   Ctx containing the code generation details
   */
  void ctx (CUTS_SETAF_CPP::Context_t & ctx);

  /**
   * Get the output directory
   *
   * @return   path of the output directory
   */
  std::string output_dir (void);

  /**
   * Get the Name of the adapter
   *
   * @return   Name of the adapter
   */
  std::string adapter_name (void);

  /**
   * Get the Relations added from the adapter
   *
   * @return   Relations
   */
  CUTS_SETAF_UTILS::Setaf_Relations & relations (void);

  /**
   * Get the Lofgormat variables added from the adapter
   *
   * @return   Log format Variables
   */
  CUTS_SETAF_UTILS::Setaf_Entries & entries (void);

  /**
   * Get the Adaptation code
   *
   * @return   Set of adaptation code.
   */
  CUTS_SETAF_UTILS::Setaf_Code & setaf_code (void);

  /**
   * Get the variable declarations
   *
   * @return   code containing the variable declarations
   */
  CUTS_SETAF_UTILS::string_vector & variable_decls (void);

  // Generate the mpc file
  void generate_project (void);

  // Generate the mwc file
  void generate_workspace (void);

  // Generate the header file
  void generate_header (void);

  // Generate the source file
  void generate_source (void);

  // Open the files for writting the output
  void open_files (void);

  // Close the file
  void close_files (void);


private:

  // Datapoints in the adapter specification
  CUTS_SETAF_UTILS::Setaf_Entries entries_;

  // Relations in the adapter specification
  CUTS_SETAF_UTILS::Setaf_Relations relations_;

  // Private variable declarations in the adapter specification
  CUTS_SETAF_UTILS::string_vector variable_decls_;

  // Adaptation code in the adapter specification
  CUTS_SETAF_UTILS::Setaf_Code setaf_code_;

  // Context fot the code generation
  CUTS_SETAF_CPP::Context_t ctx_;

  // Initialization code in the adapter specification
  std::string init_str_;

  // Reset code in the adapter soecification
  std::string reset_str_;

  // Directory to output the generated code.
  std::string output_dir_;

  // Name of the adapter
  std::string adapter_name_;

  // Generate the includes declarations
  void generate_includes (void);

  // Generate the content of the header file
  void generate_header_body (void);

  // Completes the header file generation
  void generate_header_end (void);

  // Generate the code for init method
  void generate_init_method (void);

  // Generate the code for reset method
  void generate_reset_method (void);

  // Generate the code for close method
  void generate_close_method (void);

  // Generate the code for update log format method
  void generate_update_log_format (void);

  // Generate the code for update relations method
  void generate_update_relations (void);

  // Generate the code for update valuse
  void generate_update_variable_values (void);

  // Completing the source file geenration.
  void generate_end_of_source ();

};

#if defined (__CUTS_INLINE__)
#include "Setaf_Code_Generator.inl"
#endif

#endif  // !defined _CUTS_SETAF_CODE_GENERATOR_H_