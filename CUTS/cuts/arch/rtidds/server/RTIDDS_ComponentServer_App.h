// -*- C++ -*-

//=============================================================================
/**
 *  @file         RTIDDS_CCM_ComponentServer_App.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_RTIDDS_CCM_COMPONENTSERVER_APP_H_
#define _CUTS_RTIDDS_CCM_COMPONENTSERVER_APP_H_

#include "cuts/arch/ccm/CCM_ComponentServer_App_T.h"
#include "RTIDDS_ComponentServer.h"

/**
 * @class CUTS_RTIDDS_CCM_ComponentServer_App
 *
 * Main application for the RTIDDS component server.
 */
class CUTS_RTIDDS_CCM_ComponentServer_App :
  public CUTS_CCM_ComponentServer_App_T <CUTS_RTIDDS_CCM_ComponentServer_App,
                                         CUTS_RTIDDS_CCM_ComponentServer>
{
public:
  /// Type definition of the base type.
  typedef CUTS_CCM_ComponentServer_App_T <CUTS_RTIDDS_CCM_ComponentServer_App,
                                          CUTS_RTIDDS_CCM_ComponentServer> base_type;

  /// Default constructor.
  CUTS_RTIDDS_CCM_ComponentServer_App (void);

  /// Destructor.
  virtual ~CUTS_RTIDDS_CCM_ComponentServer_App (void);

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
#include "RTIDDS_ComponentServer_App.inl"
#endif

#endif  // !defined _CUTS_RTIDDS_CCM_COMPONENTSERVER_APP_H_
