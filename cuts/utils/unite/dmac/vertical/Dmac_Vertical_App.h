#ifndef _CUTS_DMAC_VERTICAL_APP_H_
#define _CUTS_DMAC_VERTICAL_APP_H_

#include <iostream>
#include "ace/SString.h"
#include "Dmac_Vertical_Format.h"
#include <algorithm>
#include <sstream>


/**
 * @class CUTS_Dmac_Vertical_App
 *
 * Represent the vertical format of a log message
 */
class CUTS_Dmac_Vertical_App
{
public:

  typedef std::vector <CUTS_Dmac_Vertical_Format *> vertical_list_t;

  typedef std::vector <CUTS_Dmac_Vertical_Format *>::iterator v_iter;

  /// Default constructor
  CUTS_Dmac_Vertical_App (void);

  /// Destructor
  ~CUTS_Dmac_Vertical_App (void);

  /**
   * Main entry point for the application
   *
   * @param[in]       argc        Number of command-line arguments
   * @param[in]       argv        The command-line arguements
   */
  int run_main (int argc, char * argv []);


private:

   // Helper method to pass the command line arguments
  int parse_args (int argc, char * argv []);

  // print the help
  void print_help (void);

  // Tokenize words
  void tokenize (const std::string & str,
                 std::set <std::string> & tokens,
                 const std::string & delimiters,
                 CUTS_Dmac_Vertical_Format * format);

  // The input datafile
  ACE_CString input_file_;

};

#endif  // !defined _TRACE_MINING_APP_H_
