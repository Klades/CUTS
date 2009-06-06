// -*- C++ -*-

#ifndef _CUTS_CHAOS_CCM_COMPONENTSERVER_APP_H_
#define _CUTS_CHAOS_CCM_COMPONENTSERVER_APP_H_

#include "cuts/arch/ccm/CCM_ComponentServer_App_T.h"
#include "CHAOS_CCM_ComponentServer.h"

/// Type defintion of the component server app's base type.
typedef
  CUTS_CCM_ComponentServer_App_T <
    CUTS_CHAOS_CCM_ComponentServer_App,
    CUTS_CHAOS_CCM_ComponentServer>
    CUTS_CHAOS_CCM_ComponentServer_App_Base;

/**
 * @class CUTS_CHAOS_CCM_ComponentServer_App
 *
 * Main application for the CHAOS component server.
 */
class CUTS_CHAOS_CCM_ComponentServer_App :
  public CUTS_CHAOS_CCM_ComponentServer_App_Base
{
public:
  /// Type definition of the base type.
  typedef CUTS_CHAOS_CCM_ComponentServer_App_Base base_type;

  /// Default constructor.
  CUTS_CHAOS_CCM_ComponentServer_App (void);

  /// Destructor.
  virtual ~CUTS_CHAOS_CCM_ComponentServer_App (void);

  /**
   * Main entry point for the application.
   *
   * @param[in]       argc        Number of command-line arguments
   * @param[in]       argv        The actual command-line arguments
   */
  int run_main (int argc, char * argv []);

private:
  /// Help method to parse the command-line options.
  int parse_args (int argc, char * argv []);

  /// Print help for the application.
  void print_help (void);
};

#if defined (__CUTS_INLINE__)
#include "CHAOS_CCM_ComponentServer_App.inl"
#endif

#endif  // !defined _CUTS_CHAOS_CCM_COMPONENTSERVER_APP_H_
