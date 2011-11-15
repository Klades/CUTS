// -*- C++ -*-

//=============================================================================
/**
 * @file        Antispam_App.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ANTISPAM_APP_H_
#define _CUTS_ANTISPAM_APP_H_

#include "ace/SString.h"
#include "Component_Manager.h"
#include "Component_Assembly.h"
#include "Deployment.h"

namespace CUTS
{
  // Forward decl.
  class componentType;

  // Forward decl.
  class inputType;

  // Forward decl.
  class instanceType;

  // Forward decl.
  class connectionType;

  // Forward decl.
  class hostType;
}

/**
 * @class CUTS_Antispam_App
 */
class CUTS_Antispam_App
{
public:
  /// Default constuctor.
  CUTS_Antispam_App (void);

  /// Destructor
  ~CUTS_Antispam_App (void);

  int run_main (int argc, char * argv []);

private:
  int parse_args (int argc, char * argv []);

  bool construct_model (void);

  void process_component_type (const CUTS::componentType & type);

  void process_input (CUTS_Component *, const CUTS::inputType & input);

  void process_instance (const CUTS::instanceType & inst);

  void process_connection (const CUTS::connectionType & conn);

  void process_host (const CUTS::hostType & host);

  /// The location of the configuration.
  ACE_CString config_;

  /// Manager of the component types.
  CUTS_Component_Manager mgr_;

  CUTS_Component_Assembly assembly_;

  CUTS_Deployment deployment_;
};

#endif  // !defined _CUTS_ANTISPAM_APP_H_
