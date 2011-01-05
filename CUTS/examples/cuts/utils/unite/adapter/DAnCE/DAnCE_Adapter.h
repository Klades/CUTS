// -*- C++ -*-

#ifndef _DANCE_ADAPTER_H_
#define _DANCE_ADAPTER_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/OS_Memory.h"
#include "cuts/utils/unite/Log_Format_Adapter.h"
#include "DAnCE_Adapter_export.h"


class DANCE_ADAPTER_Export DAnCE_Adapter : public CUTS_Log_Format_Adapter
{

  public:

  // init method
    void init ();

  // Update the log format by adding variables
    void update_log_format (CUTS_Log_Format * lfmt);

  // Update the log format by adding new relations
    void update_log_format_relations (CUTS_Log_Format * lfmt);

  // Update the variable values
    bool update_log_format_variable_values (ACE_CString & key,
                                              CUTS_Log_Format_Variable * var,
                                              CUTS_Log_Format * lfmt);

  // Reset the adapter
    void reset ();

  // Close the adapter
    void close ();


  private:
    int lf13_update_count_;
};

// Declares the create method for dynamically loading the adapter
CUTS_LOG_FORMAT_ADAPTER_EXPORT_DECL (DANCE_ADAPTER_Export);

#endif /* _DANCE_ADAPTER_H_ */
