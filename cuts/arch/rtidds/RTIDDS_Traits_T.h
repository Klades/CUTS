// -*- C++ -*-

#ifndef _CUTS_RTIDDS_TRAITS_H_
#define _CUTS_RTIDDS_TRAITS_H_

#include "ndds/ndds_cpp.h"

/**
 * @class CUTS_RTIDDS_Traits_T
 *
 * Template class for defining the traits for an event. This will
 * simplify writing the template classes that use events.
 */
template <typename EVENT>
class CUTS_RTIDDS_Traits_T
{
public:
  // traits for the reader(s)
  typedef ::DDSDataReader   reader_type;
  typedef ::DDSDataReader * reader_ptr_type;

  // traits for the writer(s)
  typedef ::DDSDataWriter   writer_type;
  typedef ::DDSDataWriter * writer_ptr_type;
};

#endif  // !defined _CUTS_RTIDDS_TRAITS_H_
