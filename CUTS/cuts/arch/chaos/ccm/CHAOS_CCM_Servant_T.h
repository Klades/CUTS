// -*- C++ -*-

#ifndef _CUTS_CHAOS_CCM_SERVANT_T_H_
#define _CUTS_CHAOS_CCM_SERVANT_T_H_

#include "cuts/arch/ccm/CCM_Servant_T.h"
#include "cuts/arch/tcpip/TCPIP_Servant_VTable_T.h"
#include "CHAOS_CCM_Servant.h"

/**
 * @class CUTS_CHAOS_CCM_Servant_T
 */
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
class CUTS_CHAOS_CCM_Servant_T :
  public CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, CUTS_CHAOS_CCM_Servant>
{
public:
  /// Type definition of the base type.
  typedef CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, CUTS_CHAOS_CCM_Servant> base_type;

  CUTS_CHAOS_CCM_Servant_T (
    const char * name,
    typename EXECUTOR::_ptr_type executor);

  /// Destructor.
  virtual ~CUTS_CHAOS_CCM_Servant_T (void);

  // Method for handling the event. It will dispatch the events
  // to the correct method.
  virtual int handle_event (ACE_UINT32 id, CUTS_TCPIP_InputCDR & input);

protected:
  typedef typename base_type::consumer_map_type consumer_map_type;

  typedef typename base_type::emits_map_type emits_map_type;

  typedef typename base_type::publishes_map_type publishes_map_type;

  /// Type definition of the virtual table.
  typedef CUTS_TCPIP_Servant_VTable_T <T> virtual_table_type;

  /// Virtual table for the servant.
  static virtual_table_type table_;
};

#if defined (__CUTS_INLINE__)
#include "CHAOS_CCM_Servant_T.inl"
#endif

#include "CHAOS_CCM_Servant_T.cpp"

#endif  // !defined _CUTS_CHAOS_CCM_SERVANT_T_H_
