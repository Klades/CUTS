
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from ModelDDSData_DDS.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Data Distribution Service manual.
*/

#ifndef ModelDDSData_DDSPlugin_h
#define ModelDDSData_DDSPlugin_h

#ifndef ModelDDSData_DDS_h
#include "ModelDDSData_DDS.h"
#endif




struct RTICdrStream;

#ifndef pres_typePlugin_h
#include "pres/pres_typePlugin.h"
#endif


#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif


namespace CUTS_DDS{

namespace Outer{

namespace Inner{


#define Data_DDSPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
#define Data_DDSPlugin_return_sample PRESTypePluginDefaultEndpointData_returnSample 
#define Data_DDSPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define Data_DDSPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 
 

#define Data_DDSPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define Data_DDSPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern Data_DDS*
Data_DDSPluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern Data_DDS*
Data_DDSPluginSupport_create_data();

NDDSUSERDllExport extern RTIBool 
Data_DDSPluginSupport_copy_data(
    Data_DDS *out,
    const Data_DDS *in);

NDDSUSERDllExport extern void 
Data_DDSPluginSupport_destroy_data_ex(
    Data_DDS *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
Data_DDSPluginSupport_destroy_data(
    Data_DDS *sample);

NDDSUSERDllExport extern void 
Data_DDSPluginSupport_print_data(
    const Data_DDS *sample,
    const char *desc,
    unsigned int indent);

 

/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
Data_DDSPlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
Data_DDSPlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);
    
NDDSUSERDllExport extern PRESTypePluginEndpointData 
Data_DDSPlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
Data_DDSPlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);

NDDSUSERDllExport extern RTIBool 
Data_DDSPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    Data_DDS *out,
    const Data_DDS *in);

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool 
Data_DDSPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const Data_DDS *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
Data_DDSPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    Data_DDS *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);


NDDSUSERDllExport extern RTIBool
Data_DDSPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
Data_DDSPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size);

NDDSUSERDllExport extern unsigned int 
Data_DDSPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size);

NDDSUSERDllExport extern unsigned int
Data_DDSPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size,
    const void * sample);


/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginKeyKind 
Data_DDSPlugin_get_key_kind();

NDDSUSERDllExport extern unsigned int 
Data_DDSPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
Data_DDSPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const Data_DDS *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
Data_DDSPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    Data_DDS * sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
Data_DDSPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    Data_DDS *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

     
/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
Data_DDSPlugin_new();

NDDSUSERDllExport extern void
Data_DDSPlugin_delete(struct PRESTypePlugin *);
 

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif


} /* namespace Inner */


#define TestData_DDSPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
#define TestData_DDSPlugin_return_sample PRESTypePluginDefaultEndpointData_returnSample 
#define TestData_DDSPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define TestData_DDSPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 
 

#define TestData_DDSPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define TestData_DDSPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern TestData_DDS*
TestData_DDSPluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern TestData_DDS*
TestData_DDSPluginSupport_create_data();

NDDSUSERDllExport extern RTIBool 
TestData_DDSPluginSupport_copy_data(
    TestData_DDS *out,
    const TestData_DDS *in);

NDDSUSERDllExport extern void 
TestData_DDSPluginSupport_destroy_data_ex(
    TestData_DDS *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
TestData_DDSPluginSupport_destroy_data(
    TestData_DDS *sample);

NDDSUSERDllExport extern void 
TestData_DDSPluginSupport_print_data(
    const TestData_DDS *sample,
    const char *desc,
    unsigned int indent);

 

/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
TestData_DDSPlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
TestData_DDSPlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);
    
NDDSUSERDllExport extern PRESTypePluginEndpointData 
TestData_DDSPlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
TestData_DDSPlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);

NDDSUSERDllExport extern RTIBool 
TestData_DDSPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    TestData_DDS *out,
    const TestData_DDS *in);

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool 
TestData_DDSPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const TestData_DDS *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
TestData_DDSPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    TestData_DDS *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);


NDDSUSERDllExport extern RTIBool
TestData_DDSPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
TestData_DDSPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size);

NDDSUSERDllExport extern unsigned int 
TestData_DDSPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size);

NDDSUSERDllExport extern unsigned int
TestData_DDSPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size,
    const void * sample);


/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginKeyKind 
TestData_DDSPlugin_get_key_kind();

NDDSUSERDllExport extern unsigned int 
TestData_DDSPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
TestData_DDSPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const TestData_DDS *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
TestData_DDSPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    TestData_DDS * sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
TestData_DDSPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    TestData_DDS *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

     
/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
TestData_DDSPlugin_new();

NDDSUSERDllExport extern void
TestData_DDSPlugin_delete(struct PRESTypePlugin *);
 

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif


} /* namespace Outer */

} /* namespace CUTS_DDS */
        

#endif /* ModelDDSData_DDSPlugin_h */
