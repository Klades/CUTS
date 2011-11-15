// $Id$

//
// CUTS_RTIDDS_CCM_Publisher
//
CUTS_INLINE
CUTS_RTIDDS_CCM_Publisher::CUTS_RTIDDS_CCM_Publisher (void)
: publisher_ (0),
  abstract_writer_ (0)
{

}

//
// ~CUTS_RTIDDS_CCM_Publisher
//
CUTS_INLINE
CUTS_RTIDDS_CCM_Publisher::~CUTS_RTIDDS_CCM_Publisher (void)
{
  this->disconnect ();
}

//
// configure
//
CUTS_INLINE
void CUTS_RTIDDS_CCM_Publisher::configure (::DDSPublisher * publisher)
{
  this->publisher_ = publisher;
}
