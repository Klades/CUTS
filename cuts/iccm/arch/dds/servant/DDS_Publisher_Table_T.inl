// $Id$

namespace iCCM
{

//
// DDS_Publisher_Table_T
//
template <typename T, typename EVENT>
CUTS_INLINE
DDS_Publisher_Table_T <T, EVENT>::DDS_Publisher_Table_T (void)
: inst_ (T::HANDLE_NIL)
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

}
