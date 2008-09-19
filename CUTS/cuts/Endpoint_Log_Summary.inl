// $Id$

//
// CUTS_Endpoint_Log_Summary
//
CUTS_INLINE
CUTS_Endpoint_Log_Summary::CUTS_Endpoint_Log_Summary (void)
{

}

//
// logs
//
CUTS_INLINE
const CUTS_Endpoint_Data_Logs &
CUTS_Endpoint_Log_Summary::logs (void) const
{
  return this->logs_;
}

//
// ~CUTS_Endpoint_Log_Summary
//
CUTS_INLINE
CUTS_Endpoint_Log_Summary::~CUTS_Endpoint_Log_Summary (void)
{
  this->clean_reset ();
}

