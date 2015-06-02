#ifndef CCPP_HELLOWORLD_H
#define CCPP_HELLOWORLD_H



#ifdef CCPP_USE_CUSTOM_SUFFIX_HELLOWORLD
#include "HelloWorld.h"
#include "HelloWorldDcps.h"
#else
#include "HelloWorldC.h"
#include "HelloWorldDcpsC.h"
#endif

#include <orb_abstraction.h>
#include "HelloWorldDcps_impl.h"



#endif /* CCPP_HELLOWORLD_H */
