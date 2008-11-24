// -*- C++ -*-

#ifndef _CUTS_TEST_LOGGER_MAP_H_
#define _CUTS_TEST_LOGGER_MAP_H_

#include "ace/Hash_Map_Manager_T.h"
#include "ace/Null_Mutex.h"
#include "ace/UUID.h"

// Forward decl.
class CUTS_TestLoggerFactory_i;

// Type definition.
typedef
ACE_Hash_Map_Manager <ACE_CString,
                      CUTS_TestLoggerFactory_i *,
                      ACE_Null_Mutex> CUTS_Test_Logger_Map;

#endif  // !defined _CUTS_TEST_LOGGER_MAP_H_
