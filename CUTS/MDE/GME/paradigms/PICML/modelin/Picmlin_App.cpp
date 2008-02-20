// $Id$

#include "Picmlin_App.h"
#include "gme/ComponentEx.h"
#include "ace/Get_Opt.h"
#include "ace/OS_NS_string.h"
#include "Scatter_To_Picml.h"

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

  get_opt.long_option ("connstr", 'f', ACE_Get_Opt::ARG_REQUIRED);
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
      if (ACE_OS::strcmp (get_opt.long_option (), "connstr") == 0)
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

    if (scatter_to_picml.run (this->options_.scatter_input_,
                              deployment_map))
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

      // Start a new transaction for the conversion. We then need to
      // locate the correct deployment plan.
      this->project_->begin_transaction ();

      GME::Model deployment_plan;

      // Update the deployment plan.
      if (this->find_deployment_plan (deployment_plan) == 0)
        this->set_deployment (deployment_plan, deployment_map);

      // Commit the modifications to the project.
      this->project_->commit_transaction ();

      // Run the specified GME component, if it was specified.
      if (!this->options_.deployment_output_.empty ())
        this->generate_deployment (this->options_.deployment_output_);
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
  GME::init ();
  this->project_.reset (new GME::Project ());

  VERBOSE_MESSAGE ((LM_INFO,
                    "*** info [picmlin]: opening GME model %s\n",
                    this->options_.gme_connstr_.c_str ()));

  // Open a new GME project.
  this->project_->open (this->options_.gme_connstr_.c_str ());
  return 0;
}

//
// gme_fini_project
//
int Picmlin_App::gme_fini_project (void)
{
  if (this->project_.get ())
  {
    this->project_->close ();
    this->project_.reset ();
  }

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
          group.insert (instref);
        }
      }
    }
  }
  return 0;
}

//
// clear_deployment
//
void Picmlin_App::clear_deployment (GME::Model & deployment)
{
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
