// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// DDS_Publisher_T
//
template <typename T, typename EVENT>
CUTS_INLINE
DDS_Publisher_T <T, EVENT>::DDS_Publisher_T (void)
: inst_ (T::HANDLE_NIL)
{

}

//
// ~DDS_Publisher_T
//
template <typename T, typename EVENT>
CUTS_INLINE
DDS_Publisher_T <T, EVENT>::~DDS_Publisher_T (void)
{

}

}