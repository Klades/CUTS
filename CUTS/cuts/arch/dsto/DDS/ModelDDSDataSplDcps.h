#ifndef MODELDDSDATASPLTYPES_H
#define MODELDDSDATASPLTYPES_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>

extern c_metaObject __ModelDDSData_Outer__load (c_base base);

extern c_metaObject __ModelDDSData_Outer_Inner__load (c_base base);

extern c_metaObject __Outer_Inner_Data_DDS__load (c_base base);
extern char * __Outer_Inner_Data_DDS__keys (void);
extern char * __Outer_Inner_Data_DDS__name (void);
struct _Outer_Inner_Data_DDS {
    c_string name;
    c_long id;
    c_bool urgent;
};

extern c_metaObject __Outer_TestData_DDS__load (c_base base);
extern char * __Outer_TestData_DDS__keys (void);
extern char * __Outer_TestData_DDS__name (void);
struct _Outer_TestData_DDS {
    c_ushort key;
    struct _Outer_Inner_Data_DDS packet;
};

#endif
