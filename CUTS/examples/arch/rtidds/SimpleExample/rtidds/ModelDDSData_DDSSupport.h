
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from ModelDDSData_DDS.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Data Distribution Service manual.
*/

#ifndef ModelDDSData_DDSSupport_h
#define ModelDDSData_DDSSupport_h

/* Uses */
#ifndef ModelDDSData_DDS_h
#include "ModelDDSData_DDS.h"
#endif



#ifdef __cplusplus
#ifndef ndds_cpp_h
  #include "ndds/ndds_cpp.h"
#endif
#else
#ifndef ndds_c_h
  #include "ndds/ndds_c.h"
#endif
#endif


namespace CUTS_DDS{

namespace Outer{

namespace Inner{
        

/* ========================================================================= */
/**
   Uses:     T

   Defines:  TTypeSupport, TDataWriter, TDataReader

   Organized using the well-documented "Generics Pattern" for
   implementing generics in C and C++.
*/

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)

#ifdef __cplusplus
  /* If we're building on Windows, explicitly import the superclasses of
   * the types declared below.
   */        
  class __declspec(dllimport) ::DDSTypeSupport;
  class __declspec(dllimport) ::DDSDataWriter;
  class __declspec(dllimport) ::DDSDataReader;
#endif

#endif

#ifdef __cplusplus


DDS_TYPESUPPORT_CPP(Data_DDSTypeSupport, Data_DDS);

DDS_DATAWRITER_CPP(Data_DDSDataWriter, Data_DDS);
DDS_DATAREADER_CPP(Data_DDSDataReader, Data_DDSSeq, Data_DDS);


#else

DDS_TYPESUPPORT_C(Data_DDSTypeSupport, Data_DDS);
DDS_DATAWRITER_C(Data_DDSDataWriter, Data_DDS);
DDS_DATAREADER_C(Data_DDSDataReader, Data_DDSSeq, Data_DDS);

#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


} /* namespace Inner */
        

/* ========================================================================= */
/**
   Uses:     T

   Defines:  TTypeSupport, TDataWriter, TDataReader

   Organized using the well-documented "Generics Pattern" for
   implementing generics in C and C++.
*/

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)

#ifdef __cplusplus
  /* If we're building on Windows, explicitly import the superclasses of
   * the types declared below.
   */        
  class __declspec(dllimport) ::DDSTypeSupport;
  class __declspec(dllimport) ::DDSDataWriter;
  class __declspec(dllimport) ::DDSDataReader;
#endif

#endif

#ifdef __cplusplus


DDS_TYPESUPPORT_CPP(TestData_DDSTypeSupport, TestData_DDS);

DDS_DATAWRITER_CPP(TestData_DDSDataWriter, TestData_DDS);
DDS_DATAREADER_CPP(TestData_DDSDataReader, TestData_DDSSeq, TestData_DDS);


#else

DDS_TYPESUPPORT_C(TestData_DDSTypeSupport, TestData_DDS);
DDS_DATAWRITER_C(TestData_DDSDataWriter, TestData_DDS);
DDS_DATAREADER_C(TestData_DDSDataReader, TestData_DDSSeq, TestData_DDS);

#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


} /* namespace Outer */

} /* namespace CUTS_DDS */


#endif  /* ModelDDSData_DDSSupport_h */
