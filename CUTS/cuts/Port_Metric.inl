// $Id$

//
// log
//
CUTS_INLINE
const CUTS_Activation_Record_Log & CUTS_Port_Metric::log (void) const
{
  return this->log_;
}

//
// log
//
CUTS_INLINE
CUTS_Activation_Record_Log & CUTS_Port_Metric::log (void)
{
  return this->log_;
}

//
// summary
//
CUTS_INLINE
CUTS_Port_Summary & CUTS_Port_Metric::summary (void)
{
  return this->summary_;
}

//
// summary
//
CUTS_INLINE
const CUTS_Port_Summary & CUTS_Port_Metric::summary (void) const
{
  return this->summary_;
}
