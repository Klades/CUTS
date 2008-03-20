// $Id$

#include "stdafx.h"
#include "Picmlin_App.h"
#include "Scatter_To_Picml.h"
#include "gme/ComponentEx.h"
#include "ace/Get_Opt.h"
#include "ace/OS_NS_string.h"
#include "ace/OS_NS_unistd.h"
#include "ace/OS_NS_stdio.h"
#include "ace/Lib_Find.h"
#include <sstream>

// Helper macro for generating verbose messages.
#define VERBOSE_MESSAGE(msg) \
  if (this->options_.verbose_) \
  { \
    ACE_DEBUG (msg); \
  }

//
// Picmlin_App
//
Picmlin_App::Picmlin_App (void)
: is_mga_file_ (true)
{

}

//
// ~Picmlin_App
//
Picmlin_App::~Picmlin_App (void)
{
  this->gme_fini_project ();
}

//
// parse_args
//
int Picmlin_App::parse_args (int argc, char * argv [])
{
  const char * opts = ACE_TEXT ("vf:");
  ACE_Get_Opt get_opt (argc, argv, opts, 0);

  get_opt.long_option ("gme-file", 'f', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("deployment-target-folder", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("deployment-target-model", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("instance-name-separator", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("generate-deployment", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("scatter-input", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("verbose", 'v', ACE_Get_Opt::NO_ARG);

  int option;

  while ((option = get_opt ()) != EOF)
  {
    switch (option)
    {
    case 0:
      if (ACE_OS::strcmp (get_opt.long_option (), "gme-file") == 0)
      {
        this->options_.gme_connstr_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "deployment-target-folder") == 0)
      {
        this->options_.target_deployment_folder_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "deployment-target-model") == 0)
      {
        this->options_.target_deployment_model_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "instance-name-separator") == 0)
      {
        this->options_.instance_name_separator_ = *get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "generate-deployment") == 0)
      {
        this->options_.deployment_output_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "scatter-input") == 0)
      {
        this->options_.scatter_input_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "verbose") == 0)
      {
        this->options_.verbose_ = true;
      }
      break;

    case 'f':
      this->options_.gme_connstr_ = get_opt.opt_arg ();
      break;

    case 'v':
      this->options_.verbose_ = true;
      break;

    case '?':
      // unknown option; do nothing
      break;

    case ':':
      ACE_ERROR_RETURN ((LM_ERROR,
                         "*** error [picmlin]: %c is missing an argument\n",
                         get_opt.opt_opt ()),
                         -1);
      break;

    default:
      /* do nothing */;
    }
  }

  return 0;
}

//
// run
//
int Picmlin_App::run (int argc, char * argv [])
{
  int retval;

  // Parse the command-line arguments.
  VERBOSE_MESSAGE ((LM_DEBUG,
                    "*** [picmlin]: parsing command-line options\n"));

  if (parse_args (argc, argv) != 0)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                        "*** error [picmlin]: failed to parse command "
                        "line argument(s)\n"),
                        1);
  }

  // Get the deployment map from the scatter input. Only then can
  // we try to populate the GME model.
  CUTS_Scatter_To_Picml scatter_to_picml;

  try
  {
    // Initialize the GME project.
    if (this->gme_init_project () != 0)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                        "*** error [picmlin]: failed to initialize "
                        "GME\n"), 
                        1);
    }

    // Begin a new transaction.
    this->project_->begin_transaction ();

    if (scatter_to_picml.run (this->options_.scatter_input_, 
                              *this->project_,
                              this->options_))
    {
      this->project_->commit_transaction ();

      // Run the specified GME component, if it was specified.
      if (!this->options_.deployment_output_.empty ())
        this->generate_deployment (this->options_.deployment_output_);

      retval = 0;
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "*** error [picmlin]: failed to read Scatter input <%s>\n",
                  this->options_.scatter_input_.c_str ()));

      // Abort the transaction since we didn't find anything.
      retval = 1;
      this->project_->abort_transaction ();
    }
  }
  catch (const GME::Failed_Result & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [picmlin]: GME operation failed [0x%X]\n",
                ex.value ()));

    // Save the return value and abort the transaction.
    retval = ex.value ();
    this->project_->abort_transaction ();
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [picmlin]: caught unknown exception\n"));

    // Save the return value and abort the transaction.
    retval = 1;
    this->project_->abort_transaction ();
  }

  // Finalize GME, releaseing its resources.
  this->gme_fini_project ();
  return retval;
}

//
// gme_init_project
//
int Picmlin_App::gme_init_project (void)
{
  VERBOSE_MESSAGE ((LM_INFO,
                    "*** info [picmlin]: initializing GME\n"));

  try
  {
    GME::init ();
    this->project_.reset (new GME::Project ());

    VERBOSE_MESSAGE ((LM_INFO,
                      "*** info [picmlin]: opening GME model %s\n",
                      this->options_.gme_connstr_.c_str ()));

    // Determine if this file is a MGA file.
    this->is_mga_file_ = 
      this->options_.gme_connstr_.rfind (".mga") != std::string::npos;

    if (this->is_mga_file_)
    {
      std::ostringstream connstr;
      connstr << "MGA=" << this->options_.gme_connstr_;

      this->project_->open (connstr.str ());
    }
    else
    {
      ACE_TCHAR pathname[MAX_PATH];

      if (ACE::get_temp_dir (pathname, MAX_PATH - 20) != -1)
      {
        // Create a temporary filename for the project.
        ACE_OS::strcat (pathname, "picmlin-XXXXXX.mga");
        ACE_HANDLE fd = ACE_OS::mkstemp (pathname);

        if (fd == 0)
          return -1;

        // Delete the temporary file, which we aren't using.
        ACE_OS::close (fd);
        ACE_OS::unlink (pathname);

        // Create the full pathname.
        std::ostringstream connstr;
        connstr << "MGA=" << pathname;

        // Create a empty PICML project and import the XML file.
        this->project_->create (connstr.str (), "PICML");
        this->project_->xml_import (this->options_.gme_connstr_);
      }
      else
      {
        return -1;
      }
    }

    return 0;
  }
  catch (const GME::Failed_Result & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [picmlin]: GME operation failed [0x%X]\n",
                ex.value ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [picmlin]: caught unknown exception\n"));
  }

  return -1;
}

//
// gme_fini_project
//
int Picmlin_App::gme_fini_project (void)
{
  if (this->project_.get ())
  {
    std::string tempfile;

    // Save the project file.
    this->project_->save ();

    if (!this->is_mga_file_)
    {
      VERBOSE_MESSAGE ((LM_INFO,
                        "*** info [picmlin]: exporting project as %s\n",
                        this->options_.gme_connstr_.c_str ()));

      // Export the project to the source XML file.
      this->project_->xml_export (this->options_.gme_connstr_);

      // Delete the temporary file.
      tempfile = this->project_->connstr ().substr (4);
    }

    // Close the project file.
    VERBOSE_MESSAGE ((LM_INFO,
                      "*** info [picmlin]: closing the PICML project\n"));

    this->project_->close ();
    this->project_.reset ();

    if (!tempfile.empty ())
      ACE_OS::unlink (tempfile.c_str ());
  }

  VERBOSE_MESSAGE ((LM_INFO,
                    "*** info [picmlin]: shutting down GME\n",
                    this->options_.gme_connstr_.c_str ()));

  // Finalize GME backend.
  GME::fini ();

  return 0;
}

//
// generate_deployment
//
void Picmlin_App::generate_deployment (const std::string & output)
{
  // Load the GME component.
  VERBOSE_MESSAGE ((LM_DEBUG,
                    "*** info [picmlin]: loading deployment plan interpreter\n"));

  GME::ComponentEx gme_component;
  gme_component.load ("MGA.Interpreter.DeploymentPlan");

  // TODO: verify component is an interpreter.
  // TODO: verify component is compatible with project.

  VERBOSE_MESSAGE ((LM_DEBUG,
                    "*** info [picmlin]: initializing the project\n"));

  // Initialize the interpreter and set the output directory 
  // for the deployment plan.
  gme_component.initialize (*this->project_);
  gme_component.parameter ("output", this->options_.deployment_output_);
  gme_component.parameter ("non-interactive", "");

  // We can now invoke the component/interpreter. We are need to
  // pass in dummy parameters for to make everyone happy.

  GME::FCO current;
  std::vector <GME::FCO> selected;

  VERBOSE_MESSAGE ((LM_DEBUG,
                    "*** info [picmlin]: running deployment plan interpreter\n"));

  gme_component.invoke (*this->project_, current, selected, 0);
}

//
// set_deployment
//
int Picmlin_App::set_deployment (GME::Model & deployment, 
                                 const CUTS_Deployment_Map & map)
{
  VERBOSE_MESSAGE ((LM_INFO,
                    "*** info [picmlin]: converting Scatter model to "
                    "PICML model...\n"));

  // Clear the deployment.
  this->clear_deployment (deployment);
 
  typedef std::map <std::string, GME::Model> Node_Map;
  Node_Map nodes;

  // Get all the nodes in the model.
  this->get_all_nodes (nodes);

  // Deploy all the components to the corresponding nodes.
  CUTS_Deployment_Map::const_iterator 
    iter = map.begin (),
    iter_end = map.end ();

  // Get the root folder to the project.
  GME::Folder root = this->project_->root_folder ();

  // Get all the implementation folders from the project.
  typedef GME::Collection_T <GME::Folder> Folder_Set;
  Folder_Set impls_folders;

  root.folders ("ComponentImplementations", impls_folders);

  for ( ; iter != iter_end; iter ++)
  {
    // Find the node with the current iterator's name.
    VERBOSE_MESSAGE ((LM_DEBUG,
                      "*** debug [picmlin]: setting components for "
                      "host <%s>\n",
                      iter->first.c_str ()));

    Node_Map::const_iterator node = nodes.find (iter->first);

    if (node != nodes.end ())
    {
      // Insert the node into the deployment.
      GME::Reference noderef = 
        GME::Reference::_create ("NodeReference", deployment);

      // Set the name and reference for the node.
      noderef.refers_to (node->second);
      noderef.name (node->first);

      // Create the default collocation group.
      GME::Set group = GME::Set::_create ("CollocationGroup", deployment);
      group.name (node->first + "_CollocationGroup");

      // Attach the collection group to the node.
      GME::Connection::_create ("InstanceMapping", deployment, group, noderef);

      typedef std::set <std::string> string_set;
      string_set::const_iterator 
        str_iter = iter->second.begin (),
        str_iter_end = iter->second.end ();

      std::string path;

      for (; str_iter != str_iter_end; str_iter ++)
      {
        // Convert the string name to a path, if necessary.
        path = *str_iter;

        if (this->options_.instance_name_separator_ != 0)
        {
          std::replace (path.begin (),
                        path.end (),
                        this->options_.instance_name_separator_,
                        '/');
        }

        // Find this instance in the GME model.
        GME::Object instance;
        
        Folder_Set::const_iterator 
          impl_folder = impls_folders.begin (),
          impl_folder_end = impls_folders.end ();

        for ( ; impl_folder != impl_folder_end; impl_folder ++)
        {
          // Query for the object by its path.
          VERBOSE_MESSAGE ((LM_DEBUG, 
                            "*** debug [picmlin]: looking for <%s> in "
                            "folder <%s>\n",
                            path.c_str (),
                            impl_folder->name ().c_str ()));

          instance = impl_folder->find_object_by_path (path);

          // Exit the loop if we have found the object.
          if (instance)
            break;
        }

        if (instance)
        {
          // Add this instance to the deployment.
          GME::Reference instref = 
            GME::Reference::_create ("ComponentRef", deployment);

          // Get the FCO from the object.
          GME::FCO fco = GME::FCO::_narrow (instance);

          // Set name and reference of component reference. 
          instref.name (instance.name ());
          instref.refers_to (fco);

          // Add the reference to the deployment group.
          VERBOSE_MESSAGE ((LM_INFO,
                            "*** info [picmlin]: installing <%s> on <%s>\n",
                            str_iter->c_str (),
                            iter->first.c_str ()));

          group.insert (instref);
        }
        else
        {
          ACE_ERROR ((LM_ERROR,
                      "*** error [picmlin]: failed to locate instance <%s>\n",
                      str_iter->c_str ()));
        }
      }
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "*** error [picmlin]: failed to locate host <%s>\n",
                  iter->first.c_str ()));
    }
  }
  return 0;
}

//
// clear_deployment
//
void Picmlin_App::clear_deployment (GME::Model & deployment)
{
  VERBOSE_MESSAGE ((LM_DEBUG,
                    "*** [picmlin]: cleaning deployment plan <%s>\n",
                    deployment.name ().c_str ()));

  typedef GME::Collection_T <GME::Set> Set_set;
  Set_set groups;

  if (deployment.sets ("CollocationGroup", groups))
  {
    Set_set::iterator 
      iter = groups.begin (),
      iter_end = groups.end ();

    for ( ; iter != iter_end; iter ++)
    {
      // Clear the set then the destroy it.
      iter->clear ();
      iter->destroy ();
    }
  }

  // Delete the remaining children in the model.
  typedef GME::Collection_T <GME::Object> Object_Set;
  Object_Set objects;

  deployment.children (objects);

  Object_Set::iterator 
    iter = objects.begin (),
    iter_end = objects.end ();

  for (; iter != iter_end; iter ++)
    iter->destroy ();
}

//
// get_all_nodes
//
void Picmlin_App::
get_all_nodes (std::map <std::string, GME::Model> & targets)
{
  VERBOSE_MESSAGE ((LM_DEBUG,
                    "*** debug [picmlin]: gathering all hosts\n"));

  // Get the root folder of the project.
  GME::Folder root = this->project_->root_folder ();

  // Get all the <Target> folders in the model.
  typedef GME::Collection_T <GME::Folder> Folder_Set;

  Folder_Set folders;
  root.folders ("Targets", folders);

  for (Folder_Set::iterator folder = folders.begin ();
       folder != folders.end ();
       folder ++)
  {
    // Get all the Domain models in the Target.
    typedef GME::Collection_T <GME::Model> Model_Set;

    Model_Set domains;
    folder->models ("Domain", domains);

    for (Model_Set::iterator domain = domains.begin ();
         domain != domains.end ();
         domain ++)
    {
      // Get all the nodes in this Domain.
      Model_Set nodes;
      domain->models ("Node", nodes);

      for (Model_Set::iterator node = nodes.begin ();
           node != nodes.end ();
           node ++)
      {
        // Save the node. Right now, we don't care about nodes 
        // with duplicate names.
        targets[node->name ()] = *node;
      }
    }
  }
}
