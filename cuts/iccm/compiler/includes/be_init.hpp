// $Id$

#include "be_extern.h"

#define CUTS_ICCM_COMPILER(CONTEXT) \
  int BE_init (int & argc, char * argv []) { \
    ACE_NEW_RETURN (be_global, CONTEXT (), -1); \
    return 0; \
  }
