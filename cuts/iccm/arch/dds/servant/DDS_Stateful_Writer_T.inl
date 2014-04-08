// -*- C++ -*-
// $Id$

namespace iCCM
{

///////////////////////////////////////////////////////////////////////////////
// class DDS_Stateful_Writer_T

//
// ~DDS_Stateful_Writer_T
//
template <typename T, typename EVENT>
CUTS_INLINE
DDS_Stateful_Writer_T <T, EVENT>::~DDS_Stateful_Writer_T (void)
{

}

//
// activate
//
template <typename T, typename EVENT>
CUTS_INLINE
void DDS_Stateful_Writer_T <T, EVENT>::activate (void)
{

}

//
// passivate
//
template <typename T, typename EVENT>
CUTS_INLINE
void DDS_Stateful_Writer_T <T, EVENT>::passivate (void)
{

}


///////////////////////////////////////////////////////////////////////////////
// class DDS_Unregistered_Instance_Writer_T

//
// ~DDS_Unregistered_Instance_Writer_T
//
template <typename T, typename EVENT>
CUTS_INLINE
DDS_Unregistered_Instance_Writer_T <T, EVENT>::~DDS_Unregistered_Instance_Writer_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// class DDS_Registered_Instance_Writer_T

//
// ~DDS_Registered_Instance_Writer_T
//
template <typename T, typename EVENT>
CUTS_INLINE
DDS_Registered_Instance_Writer_T <T, EVENT>::~DDS_Registered_Instance_Writer_T (void)
{
  #ifdef ICCM_DDS_USES_POINTERS
    this->writer_->dispose (&this->event_.dds_event (), this->inst_);
  #else
    this->writer_->dispose (this->event_.dds_event (), this->inst_);
  #endif
}

}
