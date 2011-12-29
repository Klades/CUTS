#ifndef _CUTS_DMAC_DATAFLOW_FILE_GENERATOR_H_
#define _CUTS_DMAC_DATAFLOW_FILE_GENERATOR_H_

#include <sstream>
#include <fstream>
#include "CCF/CodeGenerationKit/IndentationXML.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"
#include "Dmac_Log_Format.h"
#include "Dmac_Execution.h"


namespace CUTS_DMAC_XML_GEN
{

  struct Context
  {
    typedef Indentation::Implanter <Indentation::XML, char> formatter_type;

    std::ofstream xml_;

    std::auto_ptr < formatter_type > xml_formatter_;

  };

  typedef struct Context Context_t;
}

/**
 * @class CUTS_Dmac_Dataflow_File_Generator
 *
 * Represent dataflow file generator
 */

class CUTS_Dmac_Dataflow_File_Generator
{
public:

  /**
   * Initializing constructor
   *
   * @param[in]   log_formats   Set of log formats for the trace
   * @param[in]   adapter_name  Name of the datagraph file
   */

  CUTS_Dmac_Dataflow_File_Generator (std::vector <CUTS_Dmac_Log_Format *> & log_formats,
                                     const char * name);

  // Destructor
  ~CUTS_Dmac_Dataflow_File_Generator (void);

  /**
   * Set the context
   *
   * @param[in]   ctx     Additional details for code genration
   */
  void ctx (CUTS_DMAC_XML_GEN::Context_t & ctx);

  // Open file for output stream
  void open_file (void);

  // Close the file after writting
  void close_file (void);

  /**
   * Generate the datagraph for a given execution
   *
   * @param[in]   ex     Execution context
   */
  void generate_xml (CUTS_Dmac_Execution * ex);

  // Intialize the xml file with declarations
  void init_xml (void);


private:

  // Generate the initial xml declarations
  void generate_declerations (CUTS_Dmac_Execution * ex);

  // Generate the identified log formats
  void generate_logformats (CUTS_Dmac_Execution * ex);

  // Finalize the xml generation
  void generate_close_tag (void);

  // List of identified log formats
  std::vector <CUTS_Dmac_Log_Format *> & log_formats_;

  // Code generation contex
  CUTS_DMAC_XML_GEN::Context_t ctx_;

  // Name of the dataflow model
  std::string name_;

};

#endif  // !defined _CUTS_DMAC_DATAFLOW_FILE_GENERATOR_H_
