#include "HelloWorldSplDcps.h"
#include "ccpp_HelloWorld.h"

const char *
__Message__name(void)
{
    return (const char*)"Message";
}

const char *
__Message__keys(void)
{
    return (const char*)"time";
}

#include <v_kernel.h>
#include <v_topic.h>
#include <os_stdlib.h>
#include <string.h>

c_bool
__Message__copyIn(
    c_base base,
    struct Message *from,
    struct _Message *to)
{
    c_bool result = TRUE;

    to->time = (c_long)from->time;
#ifdef OSPL_BOUNDS_CHECK
    if(from->content){
        to->content = c_stringNew(base, from->content);
    } else {
        result = FALSE;
    }
#else
    to->content = c_stringNew(base, from->content);
#endif
    return result;
}

void
__Message__copyOut(
    void *_from,
    void *_to)
{
    struct _Message *from = (struct _Message *)_from;
    struct Message *to = (struct Message *)_to;
    to->time = (::CORBA::Long)from->time;
    to->content = CORBA::string_dup(from->content);
}

