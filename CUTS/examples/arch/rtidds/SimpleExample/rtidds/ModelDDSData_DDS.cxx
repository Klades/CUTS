
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from ModelDDSData_DDS.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Data Distribution Service manual.
*/


#ifndef NDDS_STANDALONE_TYPE
    #ifdef __cplusplus
        #ifndef ndds_cpp_h
            #include "ndds/ndds_cpp.h"
        #endif
        #ifndef dds_c_log_impl_h              
            #include "dds_c/dds_c_log_impl.h"                                
        #endif        
    #else
        #ifndef ndds_c_h
            #include "ndds/ndds_c.h"
        #endif
    #endif
    
    #ifndef cdr_type_h
        #include "cdr/cdr_type.h"
    #endif    

    #ifndef osapi_heap_h
        #include "osapi/osapi_heap.h" 
    #endif
#else
    #include "ndds_standalone_type.h"
#endif



#ifndef ModelDDSData_DDS_h
#include "ModelDDSData_DDS.h"
#endif


namespace CUTS_DDS{

namespace Outer{

namespace Inner{
/* ========================================================================= */
const char *Data_DDSTYPENAME = "CUTS_DDS::Outer::Inner::Data_DDS";

DDS_TypeCode* Data_DDS_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode Data_DDS_g_tc_name_string = DDS_INITIALIZE_STRING_TYPECODE(255);

    static DDS_TypeCode_Member Data_DDS_g_tc_members[3]=
    {
        {
            (char *)"name",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"id",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"urgent",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode Data_DDS_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"CUTS_DDS::Outer::Inner::Data_DDS", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        3, /* Number of members */
        Data_DDS_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for Data_DDS*/

    if (is_initialized) {
        return &Data_DDS_g_tc;
    }


    Data_DDS_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&Data_DDS_g_tc_name_string;
    Data_DDS_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    Data_DDS_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_boolean;

    is_initialized = RTI_TRUE;

    return &Data_DDS_g_tc;
}


RTIBool Data_DDS_initialize(
    Data_DDS* sample) {
    return Data_DDS_initialize_ex(sample,RTI_TRUE);
}
        
RTIBool Data_DDS_initialize_ex(
    Data_DDS* sample,RTIBool allocatePointers)
{

    sample->name = DDS_String_alloc((255));
    if (sample->name == NULL) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_initLong(&sample->id)) {
        return RTI_FALSE;
    }                
            
    if (!RTICdrType_initBoolean(&sample->urgent)) {
        return RTI_FALSE;
    }                
            

    return RTI_TRUE;
}

void Data_DDS_finalize(
    Data_DDS* sample)
{
    Data_DDS_finalize_ex(sample,RTI_TRUE);
}
        
void Data_DDS_finalize_ex(
    Data_DDS* sample,RTIBool deletePointers)
{        

    DDS_String_free(sample->name);                
            
}

RTIBool Data_DDS_copy(
    Data_DDS* dst,
    const Data_DDS* src)
{        

    if (!RTICdrType_copyString(
        dst->name, src->name, (255) + 1)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyLong(
        &dst->id, &src->id)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyBoolean(
        &dst->urgent, &src->urgent)) {
        return RTI_FALSE;
    }
            

    return RTI_TRUE;
}


/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'Data_DDS' sequence class.
 */
#define T Data_DDS
#define TSeq Data_DDSSeq
#define T_initialize_ex Data_DDS_initialize_ex
#define T_finalize_ex   Data_DDS_finalize_ex
#define T_copy       Data_DDS_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#ifdef __cplusplus
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#endif
#else
#include "dds_c_sequence_TSeq.gen"
#ifdef __cplusplus
#include "dds_cpp_sequence_TSeq.gen"
#endif
#endif

#undef T_copy
#undef T_finalize_ex
#undef T_initialize_ex
#undef TSeq
#undef T


} /* namespace Inner */
/* ========================================================================= */
const char *TestData_DDSTYPENAME = "CUTS_DDS::Outer::TestData_DDS";

DDS_TypeCode* TestData_DDS_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;


    static DDS_TypeCode_Member TestData_DDS_g_tc_members[2]=
    {
        {
            (char *)"key",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"packet",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode TestData_DDS_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"CUTS_DDS::Outer::TestData_DDS", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        2, /* Number of members */
        TestData_DDS_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for TestData_DDS*/

    if (is_initialized) {
        return &TestData_DDS_g_tc;
    }


    TestData_DDS_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short;
    TestData_DDS_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)CUTS_DDS::Outer::Inner::Data_DDS_get_typecode();

    is_initialized = RTI_TRUE;

    return &TestData_DDS_g_tc;
}


RTIBool TestData_DDS_initialize(
    TestData_DDS* sample) {
    return TestData_DDS_initialize_ex(sample,RTI_TRUE);
}
        
RTIBool TestData_DDS_initialize_ex(
    TestData_DDS* sample,RTIBool allocatePointers)
{

    if (!RTICdrType_initShort(&sample->key)) {
        return RTI_FALSE;
    }                
            
    if (!CUTS_DDS::Outer::Inner::Data_DDS_initialize_ex(&sample->packet,allocatePointers)) {
        return RTI_FALSE;
    }
            

    return RTI_TRUE;
}

void TestData_DDS_finalize(
    TestData_DDS* sample)
{
    TestData_DDS_finalize_ex(sample,RTI_TRUE);
}
        
void TestData_DDS_finalize_ex(
    TestData_DDS* sample,RTIBool deletePointers)
{        

    CUTS_DDS::Outer::Inner::Data_DDS_finalize_ex(&sample->packet,deletePointers);
            
}

RTIBool TestData_DDS_copy(
    TestData_DDS* dst,
    const TestData_DDS* src)
{        

    if (!RTICdrType_copyShort(
        &dst->key, &src->key)) {
        return RTI_FALSE;
    }
            
    if (!CUTS_DDS::Outer::Inner::Data_DDS_copy(
        &dst->packet, &src->packet)) {
        return RTI_FALSE;
    }
            

    return RTI_TRUE;
}


/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'TestData_DDS' sequence class.
 */
#define T TestData_DDS
#define TSeq TestData_DDSSeq
#define T_initialize_ex TestData_DDS_initialize_ex
#define T_finalize_ex   TestData_DDS_finalize_ex
#define T_copy       TestData_DDS_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#ifdef __cplusplus
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#endif
#else
#include "dds_c_sequence_TSeq.gen"
#ifdef __cplusplus
#include "dds_cpp_sequence_TSeq.gen"
#endif
#endif

#undef T_copy
#undef T_finalize_ex
#undef T_initialize_ex
#undef TSeq
#undef T


} /* namespace Outer */

} /* namespace CUTS_DDS */
