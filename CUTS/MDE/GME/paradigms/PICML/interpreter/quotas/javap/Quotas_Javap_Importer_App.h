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

#include <map>
#include <string>
#include <set>

namespace GAME
{
namespace XME
{
// Forward decl.
class Project;

// Forward decl.
class Folder;

// Forward decl.
class FCO;

}
}

/**
 * @class Quotas_Javap_Importer_App_Options
 */
class Quotas_Javap_Importer_App_Options
{
public:
  std::string xmefile_;

  std::set <std::string> inputs_;
};

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

  void init_interface_definitions (const GAME::XME::Project & , GAME::XME::Folder & );

  void init_predefined_types (const GAME::XME::Project &,
                              std::map <std::string, GAME::XME::FCO> & symbols);

private:
  /// Options for the application.
  Quotas_Javap_Importer_App_Options opts_;
};

#endif  // !defined _QUOTAS_JAVAP_IMPORTER_APP_H_
