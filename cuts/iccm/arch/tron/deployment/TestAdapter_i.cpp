// $Id$

#include "TestAdapter_i.h"
#include "ace/Guard_T.h"

//
// TestAdapter_i
//
TestAdapter_i::TestAdapter_i (void)
: init_complete_cond_ (init_complete_mutex_),
  activate_complete_cond_ (activate_complete_mutex_),
  is_init_ (false),
  is_activated_ (false)
{

}

//
// ~TestAdapter_i
//
TestAdapter_i::~TestAdapter_i (void)
{

}


//
// initalization_complete
//
void TestAdapter_i::initialization_complete (void)
{
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - signaling that initialization is complete\n")));

  ACE_GUARD (ACE_Thread_Mutex, g, this->init_complete_mutex_);
  this->is_init_ = true;
  this->init_complete_cond_.signal ();
}

//
// activate_complete
//
void TestAdapter_i::activate_complete (void)
{
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - signaling that activation is complete\n")));

  ACE_GUARD (ACE_Thread_Mutex, g, this->activate_complete_mutex_);
  this->is_activated_ = true;
  this->activate_complete_cond_.signal ();

}

//
// wait_for_initalization_complete
//
void TestAdapter_i::wait_for_initialization_complete (void)
{
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - waiting for initialization to complete [%d]\n"), this->is_init_));

  ACE_GUARD (ACE_Thread_Mutex, g, this->init_complete_mutex_);

  if (!this->is_init_)
    this->init_complete_cond_.wait ();
}

//
// wait_for_activate_complete
//
void TestAdapter_i::wait_for_activate_complete (void)
{
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - waiting for activation to complete [%d]\n"), this->is_activated_));
  ACE_GUARD (ACE_Thread_Mutex, g, this->activate_complete_mutex_);

  if (!this->is_activated_)
    this->activate_complete_cond_.wait ();
}
