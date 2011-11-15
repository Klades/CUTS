// -*- C++ -*-

#ifndef _CUTS_RTIDDS_CCM_SERVANT_H_
#define _CUTS_RTIDDS_CCM_SERVANT_H_

#include "ndds/ndds_cpp.h"
#include "cuts/arch/ccm/CCM_Servant.h"
#include "cuts/arch/rtidds/RTIDDS_Servant.h"
#include "RTIDDS_CCM_export.h"

/**
 * @class CUTS_RTIDDS_CCM_Servant
 *
 * Base class for all RTIDDS servant objects. This class enables
 * the container to send commands to the servant, such as configuration
 * information for each of its topics.
 */
class CUTS_RTIDDS_CCM_Export CUTS_RTIDDS_CCM_Servant :
  public CUTS_RTIDDS_Servant,
  public CUTS_CCM_Servant
{
public:
  /// Destructor.
  virtual ~CUTS_RTIDDS_CCM_Servant (void);

protected:
  /// Default constructor.
  CUTS_RTIDDS_CCM_Servant (const char * name);
};

#if defined (__CUTS_INLINE__)
#include "RTIDDS_CCM_Servant.inl"
#endif

#endif  // !defined _CUTS_RTIDDS_CCM_SERVANT_H_
