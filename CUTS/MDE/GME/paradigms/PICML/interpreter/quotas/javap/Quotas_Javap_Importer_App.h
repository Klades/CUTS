// -*- C++ -*-

//=============================================================================
/**
 * @class         Quotas_Javap_Importer_App.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _QUOTAS_JAVAP_IMPORTER_APP_H_
#define _QUOTAS_JAVAP_IMPORTER_APP_H_

namespace GAME
{
namespace XME
{
class Project;
class Folder;
}
}

/**
 * @class Quotas_Javap_Importer_App
 *
 * Main wrapper class for the Quotas javap importer application.
 */
class Quotas_Javap_Importer_App
{
public:
  /// Default constructor.
  Quotas_Javap_Importer_App (void);

  /// Destructor.
  ~Quotas_Javap_Importer_App (void);

  /**
   * Main entry point for the application
   *
   * @param[in]       argc        Number of arguments
   * @param[in]       argv        The command-line arguments
   */
  int run_main (int argc, char * argv []);

private:
  int parse_args (int argc, char * argv []);

  void gme_project_init (const GAME::XME::Project & proj,
                         GAME::XME::Folder & container);
};

#endif  // !defined _QUOTAS_JAVAP_IMPORTER_APP_H_
