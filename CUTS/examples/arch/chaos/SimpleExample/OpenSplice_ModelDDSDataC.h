// -*- C++ -*-

#ifndef _OPENSPLICE_MODELDDSDATAC_H_
#define _OPENSPLICE_MODELDDSDATAC_H_

#include "ModelDDSDataC.h"
#include "cuts/arch/opensplice/OpenSplice_Traits_T.h"
#include "ddstypes/ModelDDSData_DDSDcps_impl.h"

namespace Outer
{
  MODELDDSDATA_STUB_Export bool operator <<= (TestData_DDS &, const ::CUTS_DDS::Outer::TestData_DDS & );
  MODELDDSDATA_STUB_Export bool operator >>= (const TestData_DDS &, ::CUTS_DDS::Outer::TestData_DDS & );

  namespace Inner
  {
    MODELDDSDATA_STUB_Export bool operator <<= (Data_DDS &, const ::CUTS_DDS::Outer::Inner::Data_DDS & );
    MODELDDSDATA_STUB_Export bool operator >>= (const Data_DDS &, ::CUTS_DDS::Outer::Inner::Data_DDS & );
  }
}

/**
 * @class CUTS_OpenSplice_Traits_T < ::Outer::TestData_DDS >
 *
 * Trait class for the ::Outer::TestData_DDS event
 */
template < >
class MODELDDSDATA_STUB_Export CUTS_OpenSplice_Traits_T < ::CUTS_DDS::Outer::TestData_DDS >
{
  public:
  // The reader type traits
  typedef ::CUTS_DDS::Outer::TestData_DDSDataReader reader_type;
  typedef reader_type::_ptr_type reader_ptr_type;
  typedef reader_type::_var_type reader_var_type;

  // The writer type traits
  typedef ::CUTS_DDS::Outer::TestData_DDSDataWriter writer_type;
  typedef writer_type::_ptr_type writer_ptr_type;
  typedef writer_type::_var_type writer_var_type;

  // The DDS event type traits
  typedef ::CUTS_DDS::Outer::TestData_DDS dds_event_type;
  typedef ::CUTS_DDS::Outer::TestData_DDSSeq dds_event_sequence_type;
  typedef ::CUTS_DDS::Outer::TestData_DDSSeq_var dds_event_sequence_var_type;

  typedef ::CUTS_DDS::Outer::TestData_DDSTypeSupportInterface dds_typesupport_interface_type;
  typedef dds_typesupport_interface_type::_var_type dds_typesupport_interface_var_type;
  typedef dds_typesupport_interface_type::_ptr_type dds_typesupport_interface_ptr_type;

  typedef ::CUTS_DDS::Outer::TestData_DDSTypeSupport dds_typesupport_type;
  typedef ::CUTS_DDS::Outer::TestData_DDSTypeSupport_var dds_typesupport_var_type;

  // The CORBA event type traits
  typedef ::Outer::TestData_DDS corba_event_type;
  typedef corba_event_type::_var_type corba_event_var_type;
  typedef corba_event_type::_ptr_type corba_event_ptr_type;
  typedef ::OBV_Outer::TestData_DDS corba_obv_event_type;
};

#endif  // _OPENSPLICE_MODELDDSDATAC_H_

