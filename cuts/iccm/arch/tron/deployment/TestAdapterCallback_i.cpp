// $Id$

#include "TestAdapterCallback_i.h"
#include "ace/Guard_T.h"

//
// TestAdapterCallback_i
//
TestAdapterCallback_i::TestAdapterCallback_i (void)
: set_test_adapter_cond_ (set_test_adapter_mutex_)
{

}

//
// ~TestAdapterCallback_i
//
TestAdapterCallback_i::~TestAdapterCallback_i (void)
{

}

//
// set_test_adapter
//
void
TestAdapterCallback_i::set_test_adapter (Tron::TestAdapter_ptr ta)
{
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - received test adapter\n")));

  ACE_GUARD (ACE_Thread_Mutex, g, this->set_test_adapter_mutex_);

  this->ta_ = Tron::TestAdapter::_duplicate (ta);
  this->set_test_adapter_cond_.signal ();
}

//
// wait_for_set_test_adapter
//
void
TestAdapterCallback_i::wait_for_set_test_adapter (void)
{
  ACE_GUARD (ACE_Thread_Mutex, g, this->set_test_adapter_mutex_);

  if (::CORBA::is_nil (this->ta_.in ()))
  {
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - waiting for test adapter\n")));
    this->set_test_adapter_cond_.wait ();
  }
}

//
// get_test_adapter
//
Tron::TestAdapter_ptr
TestAdapterCallback_i::get_test_adapter (void)
{
  return Tron::TestAdapter::_duplicate (this->ta_.in ());
}
