// $Id: Dmac_Log_Database_Miner.h

#ifndef _CUTS_DMAC_LOG_FORMAT_FILE_PROCESSOR_H_
#define _CUTS_DMAC_LOG_FORMAT_FILE_PROCESSOR_H_


#include "Dmac_Log_Format.h"
#include "Dmac_export.h"

/**
 * @class CUTS_Dmac_Log_Format_File_Processor
 *
 * Dmac_Log_Format_File_Processor class
 */

class CUTS_DMAC_Export CUTS_Dmac_Log_Format_File_Processor
{
public:

  /// Default constructor
  CUTS_Dmac_Log_Format_File_Processor ();

  /// Destructor
  ~CUTS_Dmac_Log_Format_File_Processor (void);

  void process_file (const char * file_name,
                     std::vector <CUTS_Dmac_Log_Format *> & log_formats);

};

#endif  // !defined _CUTS_DMAC_LOG_FORMAT_FILE_PROCESSOR_H_
