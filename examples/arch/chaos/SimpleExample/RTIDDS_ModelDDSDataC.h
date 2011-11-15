// -*- C++ -*-

#ifndef _RTIDDS_MODELDDSDATAC_H_
#define _RTIDDS_MODELDDSDATAC_H_

#include "ModelDDSDataC.h"
#include "rtidds/ModelDDSData_DDSSupport.h"
#include "cuts/arch/rtidds/RTIDDS_Traits_T.h"

namespace Outer
{
  MODELDDSDATA_STUB_Export bool operator <<= (TestData_DDS &, const ::CUTS_NDDS::Outer::TestData_DDS & );
  MODELDDSDATA_STUB_Export bool operator >>= (const TestData_DDS &, ::CUTS_NDDS::Outer::TestData_DDS & );

  namespace Inner
  {
    MODELDDSDATA_STUB_Export bool operator <<= (Data_DDS &, const ::CUTS_NDDS::Outer::Inner::Data_DDS & );
    MODELDDSDATA_STUB_Export bool operator >>= (const Data_DDS &, ::CUTS_NDDS::Outer::Inner::Data_DDS & );
  }
}

/**
 * @class CUTS_RTIDDS_Traits_T < ::Outer::TestData_DDS >
 *
 * Trait class for the ::Outer::TestData_DDS event
 */
template < >
class MODELDDSDATA_STUB_Export CUTS_RTIDDS_Traits_T < ::CUTS_NDDS::Outer::TestData_DDS >
{
  public:
  // The reader type traits
  typedef ::CUTS_NDDS::Outer::TestData_DDSDataReader reader_type;
  typedef reader_type * reader_ptr_type;

  // The writer type traits
  typedef ::CUTS_NDDS::Outer::TestData_DDSDataWriter writer_type;
  typedef writer_type * writer_ptr_type;

  // The DDS event type traits
  typedef ::CUTS_NDDS::Outer::TestData_DDS dds_event_type;
  typedef ::CUTS_NDDS::Outer::TestData_DDSSeq dds_event_sequence_type;
  typedef ::CUTS_NDDS::Outer::TestData_DDSTypeSupport dds_typesupport_type;

  // The CORBA event type traits
  typedef ::Outer::TestData_DDS corba_event_type;
  typedef corba_event_type::_var_type corba_event_var_type;
  typedef corba_event_type::_ptr_type corba_event_ptr_type;
  typedef ::OBV_Outer::TestData_DDS corba_obv_event_type;
};

#endif  // _RTIDDS_MODELDDSDATAC_H_

