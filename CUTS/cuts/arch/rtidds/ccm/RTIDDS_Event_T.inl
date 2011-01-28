// -*- C++ -*-
// $Id$

//
// CUTS_RTIDDS_Upcall_Event_T
//
template <typename EVENT, typename DDS_EVENT>
CUTS_INLINE
CUTS_RTIDDS_Upcall_Event_T <EVENT, DDS_EVENT>::
CUTS_RTIDDS_Upcall_Event_T (DDS_EVENT & dds_event)
: content_ (dds_event)
{

}

//
// CUTS_RTIDDS_Upcall_Event_T
//
template <typename EVENT, typename DDS_EVENT>
CUTS_INLINE
CUTS_RTIDDS_Upcall_Event_T <EVENT, DDS_EVENT>::
~CUTS_RTIDDS_Upcall_Event_T (void)
{

}

//
// content
//
template <typename EVENT, typename DDS_EVENT>
CUTS_INLINE
void CUTS_RTIDDS_Upcall_Event_T <EVENT, DDS_EVENT>::
content (const DDS_EVENT & content)
{
  this->content_ = content;
}

//
// content
//
template <typename EVENT, typename DDS_EVENT>
CUTS_INLINE
const DDS_EVENT &
CUTS_RTIDDS_Upcall_Event_T <EVENT, DDS_EVENT>::content (void) const
{
  return this->content_;
}

//
// content
//
template <typename EVENT, typename DDS_EVENT>
CUTS_INLINE
DDS_EVENT & CUTS_RTIDDS_Upcall_Event_T <EVENT, DDS_EVENT>::content (void)
{
  return this->content_;
}
