/* -*- C++ -*- */
// $Id: Log_Format_Adapter.h 80826 2010-03-17 


#ifndef _CUTS_LOG_FORMAT_ADAPTER_H
#define _CUTS_LOG_FORMAT_ADAPTER_H

#include "Unite_export.h"
#include "Log_Format.h"



class CUTS_UNITE_Export CUTS_Log_Format_Adapter  
{
  
public:

  virtual ~CUTS_Log_Format_Adapter(void);
  // virtual destructor.
  
  virtual void adapter_init() = 0;

  virtual void update_log_format(CUTS_Log_Format* lfmt) = 0;

  virtual void update_log_format_relations(CUTS_Log_Format *lfmt) = 0;

  virtual bool update_log_format_variable_values(ACE_CString &key, CUTS_Log_Format_Variable * var, CUTS_Log_Format* lfmt) = 0;

  virtual void adapter_reset() = 0;

  virtual void adapter_close() = 0;

  
  //virtual void print_hello (void) = 0;
  // This method gives the title of the magazine.
};

#endif /* _CUTS_LOG_FORMAT_ADAPTER_H */