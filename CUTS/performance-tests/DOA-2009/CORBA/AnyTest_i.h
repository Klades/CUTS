// -*- C++ -*-

#ifndef _CUTS_ANYTEST_I_H_
#define _CUTS_ANYTEST_I_H_

#include "AnyTestS.h"

/**
 * @class AnyTest_i
 */
class AnyTest_i :
  public POA_PerformanceTests::AnyTest
{
public:
  AnyTest_i (void);

  virtual ~AnyTest_i (void);

  virtual void send_any (const ::CORBA::Any & any);

  virtual void send_any_oneway (const ::CORBA::Any & any);

  virtual void send_simple_data (::CORBA::ULong data)
  {

  }

  size_t any_count (void)
  {
    return this->any_count_;
  }

  size_t any_oneway_count (void)
  {
    return this->any_oneway_count_;
  }

private:
  size_t any_count_;

  size_t any_oneway_count_;
};

#endif  // !defined _CUTS_ANYTEST_I_H_
