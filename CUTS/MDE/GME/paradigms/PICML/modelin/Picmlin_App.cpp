// $Id$

#include "Picmlin_App.h"
#include "Scatter_To_Picml.h"
#include "gme/ComponentEx.h"
#include "ace/Get_Opt.h"
#include "ace/OS_NS_string.h"
#include "ace/OS_NS_unistd.h"
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
  get_opt.long_option ("target-deployment", ACE_Get_Opt::ARG_REQUIRED);
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
      else if (ACE_OS::strcmp (get_opt.long_option (), "target-deployment") == 0)
      {
        this->options_.target_deployment_ = get_opt.opt_arg ();
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
  try
  {
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
    CUTS_Deployment_Map deployment_map;

    if (scatter_to_picml.run (this->options_.scatter_input_, deployment_map))
    {
      // Verify the user specified a GME target project file.
      if (this->options_.gme_connstr_.empty ())
      {
        ACE_ERROR_RETURN ((LM_ERROR,
                          "*** error [picmlin]: failed to specify "
                          "GME project file\n"),
                          1);
      }

      // Initialize the GME project.
      if (this->gme_init_project () != 0)
      {
        ACE_ERROR_RETURN ((LM_ERROR,
                          "*** error [picmlin]: failed to initialize "
                          "GME\n"), 1);
      }

      GME::Model deployment_plan;

      // Begin a new transaction.
      this->project_->begin_transaction ();

      if (this->find_deployment_plan (deployment_plan) == 0)
      {
        // Update the deployment plan and commit the modifications.
        this->set_deployment (deployment_plan, deployment_map);
        this->project_->commit_transaction ();
      }
      else
      {
        // Abort the transaction since we didn't find anything.
        this->project_->abort_transaction ();
      }

      // Run the specified GME component, if it was specified.
      if (!this->options_.deployment_output_.empty ())
        this->generate_deployment (this->options_.deployment_output_);
    }
    else
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "*** error [picmlin]: failed to read Scatter input <%s>\n",
                         this->options_.scatter_input_.c_str ()),
                         1);
    }

    return 0;
  }
  catch (const GME::Failed_Result & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [picmlin]: GME operation failed [0x%X]\n",
                ex.value ()));

    this->project_->abort_transaction ();
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [picmlin]: caught unknown exception\n"));
  }

  return 1;
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

      if (ACE::get_temp_dir (pathname, MAX_PATH) != -1)
      {
        // Create a temporary filename for the project.
        ACE_TCHAR tempfile [] = "picmlin-XXXXXX";
        ACE_OS::mkstemp (tempfile);

        // Create the full pathname.
        std::ostringstream connstr;
        connstr << "MGA=" << pathname << tempfile << ".mga";

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

    if (!this->is_mga_file_)
    {
      // Export the project to the source XML file.
      this->project_->xml_export (this->options_.gme_connstr_);

      // Save the connection string for future usage.
      tempfile = this->project_->connstr ().substr (4);
    }

    // Save and close the GME project.
    VERBOSE_MESSAGE ((LM_INFO,
                      "*** info [picmlin]: saving the project file\n"));
    this->project_->save ();

    VERBOSE_MESSAGE ((LM_INFO, 
                      "*** info [picmlin]: closing the PICML project\n"));
    this->project_->close ();

    // Delete the temporary file.
    if (!tempfile.empty ())
      ACE_OS::unlink (tempfile.c_str ());

    // Release the project's resources.
    this->project_.reset ();
  }

  VERBOSE_MESSAGE ((LM_INFO,
                    "*** info [picmlin]: shutting down GME\n",
                    this->options_.gme_connstr_.c_str ()));

  // Finalize GME backend.
  GME::fini ();

  return 0;
}

//
// find_deployment_plan
//
int Picmlin_App::find_deployment_plan (GME::Model & plan)
{
  // Get the root folder.
  GME::Folder root = this->project_->root_folder ();

  // Get the specified deployment.
  GME::Object object =
    root.find_object_by_path (this->options_.target_deployment_);

  if (object)
  {
    // Extract the plan from the GME object.
    plan = GME::Model::_narrow (object);
    return 0;
  }

  // We need to create the object. Find the location of the first
  // slash in the name.
  std::string::size_type separator =
    this->options_.target_deployment_.find_first_of ("/\\");

  if (separator != std::string::npos)
  {
    std::string folder_name =
      this->options_.target_deployment_.substr (0, separator);
    std::string deployment_name =
      this->options_.target_deployment_.substr (separator + 1);

    // Create the target folder for the deployment plan.
    GME::Folder folder = GME::Folder::_create ("DeploymentPlans", root);
    folder.name (folder_name);

    // Create the target deployment model.
    plan = GME::Model::_create ("DeploymentPlan", folder);
    plan.name (deployment_name);
    return 0;
  }

  return -1;
}

//
// run_component
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
          impl_folder = impls_folders.items ().begin (),
          impl_folder_end = impls_folders.items ().end ();

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
      iter = groups.items ().begin (),
      iter_end = groups.items ().end ();

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
    iter = objects.items ().begin (),
    iter_end = objects.items ().end ();

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

  for (Folder_Set::iterator folder = folders.items ().begin ();
       folder != folders.items ().end ();
       folder ++)
  {
    // Get all the Domain models in the Target.
    typedef GME::Collection_T <GME::Model> Model_Set;

    Model_Set domains;
    folder->models ("Domain", domains);

    for (Model_Set::iterator domain = domains.items ().begin ();
         domain != domains.items ().end ();
         domain ++)
    {
      // Get all the nodes in this Domain.
      Model_Set nodes;
      domain->models ("Node", nodes);

      for (Model_Set::iterator node = nodes.items ().begin ();
           node != nodes.items ().end ();
           node ++)
      {
        // Save the node. Right now, we don't care about nodes 
        // with duplicate names.
        targets[node->name ()] = *node;
      }
    }
  }
}
