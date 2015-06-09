
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from HelloWorld.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#include "HelloWorld.h"



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

    
        
const char *MessageTYPENAME = "Message";

    /* ========================================================================= */

DDS_TypeCode* Message_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode Message_g_tc_content_string = DDS_INITIALIZE_STRING_TYPECODE(255);

    static DDS_TypeCode_Member Message_g_tc_members[2]=
    {
        {
            (char *)"time",/* Member name */
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
            (char *)"content",/* Member name */
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

    static DDS_TypeCode Message_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"Message", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        2, /* Number of members */
        Message_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for Message*/

    if (is_initialized) {
        return &Message_g_tc;
    }


    Message_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    Message_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&Message_g_tc_content_string;

    is_initialized = RTI_TRUE;

    return &Message_g_tc;
}



RTIBool Message_initialize(
    Message* sample) {
    return ::Message_initialize_ex(sample, RTI_TRUE, RTI_TRUE);
}
        
RTIBool Message_initialize_ex(
    Message* sample, RTIBool allocatePointers, RTIBool allocateMemory)
{

    if (allocatePointers == RTI_FALSE) {};
    if (allocateMemory == RTI_FALSE) {};
    if (sample == NULL) {};


    
    if (!RTICdrType_initLong(&sample->time)) {
        return RTI_FALSE;
    }            
                 
    
    if (((CORBA::Char *&)sample->content)!=NULL){
        CORBA::string_free((CORBA::Char *&)sample->content);
    }
    
    ((CORBA::Char *&)sample->content)=(CORBA::Char *)CORBA::string_alloc((255));
    
    if (((CORBA::Char *&)sample->content) == NULL) {    
        return RTI_FALSE;
    }
    
    memset((CORBA::Char *&)sample->content,'x',(255));
    ((CORBA::Char *&)sample->content)[(255)] = '\0';
            
    return RTI_TRUE;
}

void Message_finalize(
    Message* sample)
{
    ::Message_finalize_ex(sample,RTI_TRUE);
}
        
void Message_finalize_ex(
    Message* sample,RTIBool deletePointers)
{

    if (sample == NULL) {};
    if (deletePointers == RTI_FALSE) {};


    CORBA::string_free((CORBA::Char *&)sample->content);
    ((CORBA::Char *&)sample->content)=(CORBA::Char *)NULL;
             
}


RTIBool Message_copy(
    Message* dst,
    const Message* src)
{
    
    if (!RTICdrType_copyLong(
        &dst->time,&src->time)) {
        return RTI_FALSE;
    }                        
                        
    dst->content = src->content;
            

    return RTI_TRUE;
}


        
/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'Message' sequence class.
*/
#define T Message
#define TSeq MessageSeq
#define T_initialize_ex ::Message_initialize_ex
#define T_finalize_ex   ::Message_finalize_ex
#define T_copy       ::Message_copy
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#ifdef __cplusplus
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#endif
#undef T_copy
#undef T_finalize_ex
#undef T_initialize_ex
#undef TSeq
#undef T



/* ----------------------------------------------------------------- */

