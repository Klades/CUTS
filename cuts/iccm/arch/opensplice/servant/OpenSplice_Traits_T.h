// -*- C++ -*-

#ifndef _CUTS_OPENSPLICE_TRAITS_H_
#define _CUTS_OPENSPLICE_TRAITS_H_

#include "dds_dcpsC.h"

namespace iCCM
{

/**
 * @class OpenSplice_Traits_T
 *
 * Template class for defining the traits for an event. This will
 * simplify writing the template classes that use events.
 */
template <typename EVENT>
class OpenSplice_Traits_T
{
public:
  // traits for the reader(s)
  typedef ::DDS::DataReader reader_type;
  typedef ::DDS::DataReader_ptr reader_type_ptr;
  typedef ::DDS::DataReader_var reader_type_var;

  // traits for the writer(s)
  typedef ::DDS::DataWriter writer_type;
  typedef ::DDS::DataWriter_ptr writer_type_ptr;
  typedef ::DDS::DataWriter_var writer_type_var;
};

}

#endif  // !defined _CUTS_OPENSPLICE_TRAITS_H_
