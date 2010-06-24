// $Id$

#include "Quotas_Javap_Importer_App.h"
#include "Javap_Output_Parser.h"

#include "ace/Get_Opt.h"

#include "boost/spirit/include/support_istream_iterator.hpp" 
#include "boost/bind.hpp"

#include "game/xme/Project.h"
#include "game/xme/Model.h"
#include "game/utils/modelgen.h"

#include <fstream>
#include <functional>

//
// Quotas_Javap_Importer_App
//
Quotas_Javap_Importer_App::Quotas_Javap_Importer_App (void)
{

}

//
// ~Quotas_Javap_Importer_App
//
Quotas_Javap_Importer_App::~Quotas_Javap_Importer_App (void)
{

}

//
// run_main
//
int Quotas_Javap_Importer_App::run_main (int argc, char *argv [])
{
  GAME::XME::Project project;

  try
  {
    // Initialize the GME project
    GAME::XME::Folder idl_folder;

    project = GAME::XME::Project::_create ("Test.xme", "PICML", "94FCA7F1-9017-4BFD-B557-F738FC54B103");

    // Open the specified file for reading.
    std::ifstream infile;
    infile.open (argv[1]);

    if (!infile.is_open ())
      return false;

    // Start a new transaction.
    project.name ("QuotasProject");
    project.root_folder ().name ("RootFolder");

    this->gme_project_init (project, idl_folder);

    Quotas_Javap_Output_Parser parser;
    if (!parser.parse (infile, idl_folder))
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to parse %s\n"),
                  argv[1]));

    // Close the file before exiting.
    infile.close ();

    // Save changes to the model.
    project.save ();
    project.close ();

    return 0;
  }
  catch (const GAME::XME::Exception & )
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught GME exception\n")));
  }


  return -1;
}

//
// gme_project_init
//
void Quotas_Javap_Importer_App::
gme_project_init (const GAME::XME::Project & project, GAME::XME::Folder & idl_folder)
{
  // Make sure the target container for the files exists in the 
  // model. Since each class is in its own class file, we are not
  // going to make each directly to a PICML File element. Instead,
  // each File is just a container that holds many .class files.
  GAME::XME::Folder root_folder = project.root_folder ();
  static const ::Utils::XStr meta_InterfaceDefinitions ("InterfaceDefinitions");

  if (GAME::create_if_not (root_folder, meta_InterfaceDefinitions, idl_folder,
      GAME::contains (boost::bind (std::equal_to < ::Utils::XStr > (),
                                   meta_InterfaceDefinitions,
                                   boost::bind (&GAME::XME::Folder::name, _1)))))
  {
    idl_folder.name (meta_InterfaceDefinitions);
  }
}



//
// parse_args
//
int Quotas_Javap_Importer_App::parse_args (int argc, char * argv [])
{
  return 0;
}
