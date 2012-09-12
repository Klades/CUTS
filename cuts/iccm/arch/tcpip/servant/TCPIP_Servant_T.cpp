// $Id$

#if !defined (__CUTS_INLINE__)
#include "TCPIP_Servant_T.inl"
#endif

namespace iCCM
{

//
// table_
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
CUTS_TCPIP_Servant_VTable_T <T>
TCPIP_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::table_;

//
// handle_event
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
int TCPIP_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
handle_event (ACE_UINT32 id, ACE_InputCDR & input)
{
  static T * self = dynamic_cast <T *> (this);

  if (0 != self)
  {
    if (id < this->table_.size ())
      (this->table_[id]) (self, input);
      return 0;
  }

  return -1;
}

}
