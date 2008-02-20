// $Id$

//=============================================================================
/**
 * @file      Picmlin_App.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _PICMLIN_APP_H_
#define _PICMLIN_APP_H_

#include "Picmlin_Options.h"
#include "Deployment_Map.h"
#include "gme/GME.h"
#include <memory>

//=============================================================================
/**
 * @class Picmlin_App
 */
//=============================================================================

class Picmlin_App
{
public:
  /// Default constructor.
  Picmlin_App (void);

  /// Destructor.
  ~Picmlin_App (void);

  int run (int argc, char * argv []);

private:
  int parse_args (int argc, char * argv []);

  /// Initialize the GME backend.
  int gme_init_project (void);

  /// Finalize the GME backend.
  int gme_fini_project (void);

  int find_deployment_plan (GME::Model & plan);

  int set_deployment (GME::Model & deployment, 
                      const CUTS_Deployment_Map & map);

  void clear_deployment (GME::Model & deployment);

  void get_all_nodes (std::map <std::string, GME::Model> & targets);

  void generate_deployment (const std::string & output);

  /// The command line options.
  Picmlin_Options options_;

  std::auto_ptr <GME::Project> project_;
};

#endif  // !defined _PICMLIN_APP_H_
