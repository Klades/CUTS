
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from ModelDDSData_DDS.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Data Distribution Service manual.
*/

#ifndef ModelDDSData_DDSSupport_h
#include "ModelDDSData_DDSSupport.h"
#endif

#ifndef ModelDDSData_DDSPlugin_h
#include "ModelDDSData_DDSPlugin.h"
#endif



#ifdef __cplusplus  
    #ifndef dds_c_log_impl_h              
         #include "dds_c/dds_c_log_impl.h"                                
    #endif        
#endif        


namespace CUTS_DDS{

namespace Outer{

namespace Inner{



/* ========================================================================= */
/**
   <<IMPLEMENTATION>>

   Defines:   TData,
              TDataWriter,
              TDataReader,
              TTypeSupport

   Configure and implement 'Data_DDS' support classes.

   Note: Only the #defined classes get defined
*/

/* ----------------------------------------------------------------- */
/* DDSDataWriter
*/

/**
  <<IMPLEMENTATION >>

   Defines:   TDataWriter, TData
*/

/* Requires */
#define TTYPENAME   Data_DDSTYPENAME

/* Defines */
#define TDataWriter Data_DDSDataWriter
#define TData       CUTS_DDS::Outer::Inner::Data_DDS


#ifdef __cplusplus
#include "dds_cpp/generic/dds_cpp_data_TDataWriter.gen"
#else
#include "dds_c/generic/dds_c_data_TDataWriter.gen"
#endif


#undef TDataWriter
#undef TData

#undef TTYPENAME

/* ----------------------------------------------------------------- */
/* DDSDataReader
*/

/**
  <<IMPLEMENTATION >>

   Defines:   TDataReader, TDataSeq, TData
*/

/* Requires */
#define TTYPENAME   Data_DDSTYPENAME

/* Defines */
#define TDataReader Data_DDSDataReader
#define TDataSeq    Data_DDSSeq
#define TData       CUTS_DDS::Outer::Inner::Data_DDS


#ifdef __cplusplus
#include "dds_cpp/generic/dds_cpp_data_TDataReader.gen"
#else
#include "dds_c/generic/dds_c_data_TDataReader.gen"
#endif


#undef TDataReader
#undef TDataSeq
#undef TData

#undef TTYPENAME

/* ----------------------------------------------------------------- */
/* TypeSupport

  <<IMPLEMENTATION >>

   Requires:  TTYPENAME,
              TPlugin_new
              TPlugin_delete
   Defines:   TTypeSupport, TData, TDataReader, TDataWriter
*/

/* Requires */
#define TTYPENAME    Data_DDSTYPENAME
#define TPlugin_new  CUTS_DDS::Outer::Inner::Data_DDSPlugin_new
#define TPlugin_delete  CUTS_DDS::Outer::Inner::Data_DDSPlugin_delete

/* Defines */
#define TTypeSupport Data_DDSTypeSupport
#define TData        CUTS_DDS::Outer::Inner::Data_DDS
#define TDataReader  Data_DDSDataReader
#define TDataWriter  Data_DDSDataWriter
#ifdef __cplusplus



#include "dds_cpp/generic/dds_cpp_data_TTypeSupport.gen"



#else
#include "dds_c/generic/dds_c_data_TTypeSupport.gen"
#endif
#undef TTypeSupport
#undef TData
#undef TDataReader
#undef TDataWriter

#undef TTYPENAME
#undef TPlugin_new
#undef TPlugin_delete



} /* namespace Inner */



/* ========================================================================= */
/**
   <<IMPLEMENTATION>>

   Defines:   TData,
              TDataWriter,
              TDataReader,
              TTypeSupport

   Configure and implement 'TestData_DDS' support classes.

   Note: Only the #defined classes get defined
*/

/* ----------------------------------------------------------------- */
/* DDSDataWriter
*/

/**
  <<IMPLEMENTATION >>

   Defines:   TDataWriter, TData
*/

/* Requires */
#define TTYPENAME   TestData_DDSTYPENAME

/* Defines */
#define TDataWriter TestData_DDSDataWriter
#define TData       CUTS_DDS::Outer::TestData_DDS


#ifdef __cplusplus
#include "dds_cpp/generic/dds_cpp_data_TDataWriter.gen"
#else
#include "dds_c/generic/dds_c_data_TDataWriter.gen"
#endif


#undef TDataWriter
#undef TData

#undef TTYPENAME

/* ----------------------------------------------------------------- */
/* DDSDataReader
*/

/**
  <<IMPLEMENTATION >>

   Defines:   TDataReader, TDataSeq, TData
*/

/* Requires */
#define TTYPENAME   TestData_DDSTYPENAME

/* Defines */
#define TDataReader TestData_DDSDataReader
#define TDataSeq    TestData_DDSSeq
#define TData       CUTS_DDS::Outer::TestData_DDS


#ifdef __cplusplus
#include "dds_cpp/generic/dds_cpp_data_TDataReader.gen"
#else
#include "dds_c/generic/dds_c_data_TDataReader.gen"
#endif


#undef TDataReader
#undef TDataSeq
#undef TData

#undef TTYPENAME

/* ----------------------------------------------------------------- */
/* TypeSupport

  <<IMPLEMENTATION >>

   Requires:  TTYPENAME,
              TPlugin_new
              TPlugin_delete
   Defines:   TTypeSupport, TData, TDataReader, TDataWriter
*/

/* Requires */
#define TTYPENAME    TestData_DDSTYPENAME
#define TPlugin_new  CUTS_DDS::Outer::TestData_DDSPlugin_new
#define TPlugin_delete  CUTS_DDS::Outer::TestData_DDSPlugin_delete

/* Defines */
#define TTypeSupport TestData_DDSTypeSupport
#define TData        CUTS_DDS::Outer::TestData_DDS
#define TDataReader  TestData_DDSDataReader
#define TDataWriter  TestData_DDSDataWriter
#ifdef __cplusplus



#include "dds_cpp/generic/dds_cpp_data_TTypeSupport.gen"



#else
#include "dds_c/generic/dds_c_data_TTypeSupport.gen"
#endif
#undef TTypeSupport
#undef TData
#undef TDataReader
#undef TDataWriter

#undef TTYPENAME
#undef TPlugin_new
#undef TPlugin_delete



} /* namespace Outer */

} /* namespace CUTS_DDS */
