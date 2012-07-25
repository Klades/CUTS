// $Id$

namespace iCCM
{

//
// DDS_Publisher_Table_T
//
template <typename T, typename EVENT>
CUTS_INLINE
DDS_Publisher_Table_T <T, EVENT>::DDS_Publisher_Table_T (void)
{

}

//
// ~DDS_Publisher_Table_T
//
template <typename T, typename EVENT>
CUTS_INLINE
DDS_Publisher_Table_T <T, EVENT>::~DDS_Publisher_Table_T (void)
{

}

//
// allocate_event
//
template <typename T, typename EVENT>
CUTS_INLINE
EVENT * DDS_Publisher_Table_T <T, EVENT>::allocate_event (void)
{
  return this->writer_->allocate_event ();
}

//
// send_event
//
template <typename T, typename EVENT>
CUTS_INLINE
void DDS_Publisher_Table_T <T, EVENT>::send_event (EVENT * ev)
{
  return this->writer_->send_event (ev);
}

}
