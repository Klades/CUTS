//  $Id$

#include "Tron_ORB_Initializer.h"

//
// Tron_ORB_Initializer
//
Tron_ORB_Initializer::Tron_ORB_Initializer (::CORBA::ORB_ptr orb)
: orb_ (::CORBA::ORB::_duplicate (orb)),
  is_done_ (false)
{

}

//
// ~Tron_ORB_Initializer
//
Tron_ORB_Initializer::~Tron_ORB_Initializer (void)
{

}

//
// svc
//
int
Tron_ORB_Initializer::svc (void)
{
  while (!this->is_done_)
  {
    if (this->orb_->work_pending ())
      this->orb_->perform_work ();
  }

  return 0;
}

//
// deactivate
//
void Tron_ORB_Initializer::deactivate (void)
{
  this->is_done_ = true;
}
