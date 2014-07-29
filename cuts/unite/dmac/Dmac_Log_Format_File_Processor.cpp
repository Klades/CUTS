#include "Dmac_Log_Format_File_Processor.h"
#include <fstream>
#include <sstream>
#include <iostream>

CUTS_Dmac_Log_Format_File_Processor::
CUTS_Dmac_Log_Format_File_Processor (void)
{

}

CUTS_Dmac_Log_Format_File_Processor::
~CUTS_Dmac_Log_Format_File_Processor (void)
{

}

void CUTS_Dmac_Log_Format_File_Processor::
process_file (const char * file_name,
              std::vector<CUTS_Dmac_Log_Format*> & log_formats)
{
  std::string delims (" \t\n\x01");
  ifstream lf_file;
  lf_file.open (file_name);
  lf_file.seekg (0, ios::beg);
  if (lf_file.is_open ())
  {
    size_t i = 0;
    while (lf_file.good ())
    {
      CUTS_DMAC_UTILS::string_vector word_list;
      std::string row;
      getline (lf_file, row);
      CUTS_DMAC_UTILS::tokenize (row, word_list, delims);
      i++;
      CUTS_Dmac_Log_Format * lf = new CUTS_Dmac_Log_Format (i, word_list);
      log_formats.push_back (lf);
    }
    lf_file.close ();
  }
}