// -*- C++ -*-

#ifndef _CUTS_CHAOS_CCM_SERVANT_H_
#define _CUTS_CHAOS_CCM_SERVANT_H_

#include "cuts/arch/ccm/CCM_Servant.h"
#include "cuts/arch/opensplice/OpenSplice_Servant.h"
#include "cuts/arch/rtidds/RTIDDS_Servant.h"
#include "cuts/arch/tcpip/TCPIP_Servant.h"
#include "CHAOS_CCM_export.h"

/**
 * @class CUTS_CHAOS_CCM_Servant
 *
 * Base class for all CHAOS servant objects. This class enables
 * the container to send commands to the servant, such as
 * domain-specific configuration information.
 */
class CUTS_CHAOS_CCM_Export CUTS_CHAOS_CCM_Servant :
  public CUTS_TCPIP_Servant,
  public CUTS_OpenSplice_Servant,
  public CUTS_RTIDDS_Servant,
  public CUTS_CCM_Servant
{
public:
  /// Destructor.
  virtual ~CUTS_CHAOS_CCM_Servant (void);

protected:
  /// Default constructor.
  CUTS_CHAOS_CCM_Servant (const char * name);
};

#if defined (__CUTS_INLINE__)
#include "CHAOS_CCM_Servant.inl"
#endif

#endif  // !defined _CUTS_CHAOS_CCM_SERVANT_H_
