#ifndef HELLOWORLDSPLTYPES_H
#define HELLOWORLDSPLTYPES_H

#include "ccpp_HelloWorld.h"
#include "../HelloWorld_stub_export.h"
#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>

extern c_metaObject __Message__load (c_base base);
extern const char * __Message__keys (void);
extern const char * __Message__name (void);
struct _Message ;
extern HELLOWORLD_STUB_Export c_bool __Message__copyIn(c_base base, struct Message *from, struct _Message *to);
extern HELLOWORLD_STUB_Export void __Message__copyOut(void *_from, void *_to);
struct _Message {
    c_long time;
    c_string content;
};

#endif
