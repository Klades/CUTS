//  $Id$

#ifndef _TRON_CONSUMER_MAP_TYPE_H_
#define _TRON_CONSUMER_MAP_TYPE_H_

#include "Tron_Consumer_List.h"

typedef
ACE_Hash_Map_Manager < int32_t,
                       Tron_Consumer_List *,
                       ACE_RW_Thread_Mutex > tron_consumer_map_type;

#endif  // !defined _TRON_CONSUMER_MAP_TYPE_H_
