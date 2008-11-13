// $Id$

//
// CUTS_TAO_Testing_Service
//
CUTS_INLINE
CUTS_TAO_Testing_Service::CUTS_TAO_Testing_Service (void)
{

}

//
// ~CUTS_TAO_Testing_Service
//
CUTS_INLINE
CUTS_TAO_Testing_Service::~CUTS_TAO_Testing_Service (void)
{

}

//
// fini
//
CUTS_INLINE
int CUTS_TAO_Testing_Service::fini (void)
{
  this->orb_->destroy ();
  return 0;
}
