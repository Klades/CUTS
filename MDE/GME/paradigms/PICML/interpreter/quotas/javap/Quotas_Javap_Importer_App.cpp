// $Id$

#include "Quotas_Javap_Importer_App.h"
#include "Javap_Output_Parser.h"

#include "ace/Get_Opt.h"
#include "ace/OS_NS_string.h"

#include "boost/spirit/include/support_istream_iterator.hpp"
#include "boost/bind.hpp"

#include "game/xme/Project.h"
#include "game/xme/Model.h"
#include "game/xme/modelgen.h"

#include "game/xml/String.h"

#include <fstream>
#include <iostream>
#include <functional>

#include "PIM/PICML/interpreters/PICML/PICML_GUID.h"

using GAME::Xml::String;

static const char * __HELP__ =
"Import Javap output into PICML for QUOTAS\n"
"\n"
"USAGE: quotas-javap [OPTIONS] [FILE]+\n"
"\n"
"General options:\n"
"  -o=XMEFILE\t\tOutput XME file name\n"
"  -h,--help\t\tPrint this help screen\n";

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

struct parse_file_t
{
  parse_file_t (Quotas_Javap_Output_Parser & parser,
                std::map <std::string, GAME::XME::FCO> & symbols,
                GAME::XME::Folder & idl_folder)
    : parser_ (parser),
      symbols_ (symbols),
      idl_folder_ (idl_folder)
  {

  }

  void operator () (const std::string & filename) const
  {
    std::ifstream infile;
    infile.open (filename.c_str ());

    if (infile.is_open ())
    {
      // Parse the opened file.
      if (!this->parser_.parse (infile, this->symbols_, this->idl_folder_))
        ACE_ERROR ((LM_ERROR,
                    ACE_TEXT ("%T (%t) - %M - failed to parse %s\n"),
                    filename.c_str ()));

      // Close the input file.
      infile.close ();
    }
    else
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to open %s\n"),
                  filename.c_str ()));
  }

private:
  Quotas_Javap_Output_Parser & parser_;

  std::map <std::string, GAME::XME::FCO> & symbols_;

  GAME::XME::Folder & idl_folder_;
};

//
// run_main
//
int Quotas_Javap_Importer_App::run_main (int argc, char *argv [])
{
  if (-1 == this->parse_args (argc, argv))
    return 1;

  GAME::XME::Project project;

  try
  {
    // Create a new PICML project.
    project = GAME::XME::Project::_create (this->opts_.xmefile_,
                                           "PICML",
                                           PICML_PARADIGM_GUID);

    project.name ("QuotasProject");
    project.root_folder ().name ("RootFolder");

    // Initialize the GME project
    GAME::XME::Folder idl_folder;
    std::map <std::string, GAME::XME::FCO> symbols;
    this->init_interface_definitions (project, idl_folder);
    this->init_predefined_types (project, symbols);

    Quotas_Javap_Output_Parser parser;

    if (this->opts_.inputs_.empty ())
    {
      if (!parser.parse (std::cin, symbols, idl_folder))
        ACE_ERROR ((LM_ERROR,
                    ACE_TEXT ("%T (%t) - %M - failed to parse input stream\n")));
    }
    else
    {
      std::for_each (this->opts_.inputs_.begin (),
                     this->opts_.inputs_.end (),
                     parse_file_t (parser, symbols, idl_folder));
    }

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
init_interface_definitions (const GAME::XME::Project & project, GAME::XME::Folder & idl_folder)
{
  using GAME::Xme_t;

  // Make sure the target container for the files exists in the
  // model. Since each class is in its own class file, we are not
  // going to make each directly to a PICML File element. Instead,
  // each File is just a container that holds many .class files.
  GAME::XME::Folder root_folder = project.root_folder ();
  const String meta_InterfaceDefinitions ("InterfaceDefinitions");

  if (GAME::create_if_not <Xme_t> (root_folder, meta_InterfaceDefinitions, idl_folder,
      GAME::contains <Xme_t> (boost::bind (std::equal_to < String > (),
                                   meta_InterfaceDefinitions,
                                   boost::bind (&GAME::XME::Folder::name, _1)))))
  {
    idl_folder.name (meta_InterfaceDefinitions);
  }
}

struct map_t
{
  const char * java_type_;
  const char * picml_type_;
};

//
// init_predefined_types
//
void Quotas_Javap_Importer_App::
init_predefined_types (const GAME::XME::Project & project,
                       std::map <std::string, GAME::XME::FCO> & symbols)
{
  using GAME::Xme_t;

  // Make sure the PredefinedTypes folder exists. Also, make sure each
  // of the predefined type elements in Java exist.
  GAME::XME::Folder root_folder = project.root_folder ();
  const String meta_PredefinedTypes ("PredefinedTypes");

  GAME::XME::Folder predefined_types;
  if (GAME::create_if_not <Xme_t> (root_folder, meta_PredefinedTypes, predefined_types,
      GAME::contains <Xme_t> (boost::bind (std::equal_to < String > (),
                                   meta_PredefinedTypes,
                                   boost::bind (&GAME::XME::Folder::name, _1)))))
  {
    predefined_types.name (meta_PredefinedTypes);
  }

#define PREDEFINED_TYPE_MAP_SIZE 4
  static const map_t predefined_map[PREDEFINED_TYPE_MAP_SIZE] =
  {
    {"java.lang.String", "String"},
    {"java.lang.Object", "GenericObject"},
    {"short", "ShortInteger"},
    {"long", "LongInteger"},
  };

  for (size_t i = 0; i < PREDEFINED_TYPE_MAP_SIZE; ++ i)
  {
    // Make sure the predefined type exists.
    GAME::XME::Atom type;
    if (GAME::create_if_not <Xme_t> (predefined_types, predefined_map[i].picml_type_, type,
        GAME::contains <Xme_t> (boost::bind (std::equal_to < String > (),
                                     predefined_map[i].picml_type_,
                                     boost::bind (&GAME::XME::Atom::kind, _1)))))
    {
      type.name (predefined_map[i].picml_type_);
    }

    // Save the type to the symbol table.
    symbols[predefined_map[i].java_type_] = type;
  }
}

//
// parse_args
//
int Quotas_Javap_Importer_App::parse_args (int argc, char * argv [])
{
  // Parse the command-line options.
  const char * optargs = "o:h";
  ACE_Get_Opt get_opt (argc, argv, optargs);

  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);

  int opt;

  while ((opt = get_opt ()) != EOF)
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp ("help", get_opt.long_option ()))
        this->print_help ();

      break;

    case 'h':
      this->print_help ();
      break;

    case 'o':
      this->opts_.xmefile_ = get_opt.opt_arg ();
      break;
    }
  }

  // The remaining arguments are input files.
  std::for_each (get_opt.argv () + get_opt.opt_ind (),
                 get_opt.argv () + get_opt.argc (),
                 boost::bind (&std::set <std::string>::insert,
                              boost::ref (this->opts_.inputs_),
                              _1));

  return 0;
}

//
// print_help
//
void Quotas_Javap_Importer_App::print_help (void)
{
  std::cerr << __HELP__ << std::endl;
  ACE_OS::exit (1);
}
