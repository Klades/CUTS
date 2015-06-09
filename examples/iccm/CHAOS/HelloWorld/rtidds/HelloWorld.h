
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from HelloWorld.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef HelloWorld_1436885870_h
#define HelloWorld_1436885870_h

#include "HelloWorldC.h"


#ifdef __cplusplus
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#else
#ifndef ndds_c_h
#include "ndds/ndds_c.h"
#endif
#endif


        
extern const char *MessageTYPENAME;



#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols. */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* Message_get_typecode(); /* Type code */
    
DDS_SEQUENCE(MessageSeq, Message);


NDDSUSERDllExport 
RTIBool Message_initialize(
        Message* self);

NDDSUSERDllExport 
RTIBool Message_initialize_ex(
        Message* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport 
void Message_finalize(
        Message* self);

NDDSUSERDllExport 
void Message_finalize_ex(
        Message* self,RTIBool deletePointers);

NDDSUSERDllExport 
RTIBool Message_copy(
        Message* dst,
        const Message* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif



#endif /* HelloWorld_1436885870_h */
