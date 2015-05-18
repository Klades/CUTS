// -*- C++ -*-
// $Id: generate_cpp_class.py 3685 2012-09-26 14:45:04Z dfeiock $

namespace iCCM
{
       
//
// QpidPB_Listener_T
//
template <typename CONSUMER_T, typename EVENT>
CUTS_INLINE
QpidPB_Listener_T <CONSUMER_T, EVENT>::
QpidPB_Listener_T (CONSUMER_T * consumer)
: consumer_ (consumer),
  manager_ (0)
{

}

//
// ~QpidPB_Listener_T
//
template <typename CONSUMER_T, typename EVENT>
CUTS_INLINE
QpidPB_Listener_T <CONSUMER_T, EVENT>::~QpidPB_Listener_T (void)
{

}

} // namespace iCCM
