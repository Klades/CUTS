// $Id$

#include "stdafx.h"
#include "Quotas_Integrator.h"
#include "Quotas_Integrator_Impl.h"
#include "Quotas_Driver_Component.h"
#include "Quotas_Domain_Generator.h"
#include "Quotas_Deployment_Generator.h"

#include "game/be/Interpreter_T.h"
#include "game/ComponentEx.h"
#include "game/Atom.h"
#include "game/Attribute.h"
#include "game/Connection.h"
#include "game/Model.h"
#include "game/Reference.h"
#include "game/MetaAspect.h"
#include "game/MetaModel.h"
#include "game/Transaction.h"
#include "game/Filter.h"
#include "game/manip/copy.h"
#include "game/utils/modelgen.h"
#include "game/utils/Point.h"

#include "game/dialogs/Module.h"
#include "game/dialogs/Object_Path_Dialog_Display_Strategy.h"
#include "game/dialogs/Selection_List_Dialog_T.h"

#include "boost/bind.hpp"

#include <functional>
#include <stack>

GAME_DECLARE_INTERPRETER (Quotas_Integrator_Interpreter, Quotas_Integrator_Impl);

namespace constants
{
  static const std::string Quotas_InterfaceDefinitions ("Quotas_InterfaceDefinitions");

  static const std::string Quotas_ComponentImplementations ("ComponentImplementations");
  static const std::string Quotas_ImplementationArtifacts ("ImplementationArtifacts");

  static const std::string Quotas_PredefinedTypes ("Quotas_PredefinedTypes");
}

namespace meta
{
  static const std::string PredefinedTypes ("PredefinedTypes");
  static const std::string InterfaceDefinitions ("InterfaceDefinitions");
  static const std::string ComponentImplementations ("ComponentImplementations");
  static const std::string ComponentImplementationContainer ("ComponentImplementationContainer");
  static const std::string ComponentAssembly ("ComponentAssembly");
  static const std::string ComponentInstance ("ComponentInstance");
  static const std::string ComponentInstanceType ("ComponentInstanceType");
  static const std::string SimpleProperty ("SimpleProperty");
//  static const std::string DataValue ("Value");
}

//
// Quotas_Integrator_Impl
//
Quotas_Integrator_Impl::Quotas_Integrator_Impl (void)
: GAME::Interpreter_Impl_Base ("Quotas Integrator", "Quotas.Interpreter.Integrator", "PICML")
{
}

//
// ~Quotas_Integrator_Impl
//
Quotas_Integrator_Impl::~Quotas_Integrator_Impl (void)
{
  if (this->configurator_)
    this->configurator_->resetConfiguration ();
}

//
// initialize
//
int Quotas_Integrator_Impl::initialize (GAME::Project & project)
{
  try
  {
    GAME::Dialogs::initialize_module ();

    // Let's see if we can find the PICMLManager addon. It will have
    // the progid of MGA.AddOn.PICMLManager.
    static const std::string name ("MGA.AddOn.PICMLManager");
    GAME::ComponentEx addon = project.addon_component (name);

    VERIFY_HRESULT (addon.impl ()->QueryInterface (&this->configurator_));

    using ATL::CComBSTR;

    this->configurator_->setImplementationFolder (CComBSTR (constants::Quotas_InterfaceDefinitions.c_str ()));
    this->configurator_->setArtifactFolder (CComBSTR (constants::Quotas_ImplementationArtifacts.c_str ()));
  }
  catch (const GAME::Exception &)
  {

  }

  return 0;
}

//
// invoke_ex
//
int Quotas_Integrator_Impl::
invoke_ex (GAME::Project & project,
           GAME::FCO & fco,
           std::vector <GAME::FCO> & selected,
           long flags)
{
  // First, make sure the target directory for the generated driver
  // components exists in the current model.
  GAME::Folder idl_folder;

  do
  {
    GAME::Transaction t (project);
    if (GAME::create_if_not (project.root_folder (), meta::InterfaceDefinitions, idl_folder,
        GAME::contains (boost::bind (std::equal_to <std::string> (),
                                     constants::Quotas_InterfaceDefinitions,
                                     boost::bind (&GAME::Folder::name, _1)))))
    {
      idl_folder.name (constants::Quotas_InterfaceDefinitions);
    }

    t.commit ();
  } while (false);

  // Select the .mga file that contains that collection of behavior
  // models from which we plan on selecting a single model.
  static const char * filters = "GME Files (*.mga)|*.mga|All Files (*.*)|*.*||";
  static const int onf_flags = OFN_READONLY | OFN_ENABLESIZING | OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_LONGNAMES;
  char filename[MAX_PATH] = {0};

  CFileDialog filedlg (true, 0, 0, onf_flags, filters, ::AfxGetMainWnd ());

  filedlg.m_ofn.lpstrTitle = "Select a GME model...";
  filedlg.m_ofn.lpstrFile = filename;
  filedlg.m_ofn.nMaxFile = sizeof (filename);

  if (filedlg.DoModal () == IDCANCEL)
    return 0;

  try
  {
    // Open the selected project that contains the behavior we need to
    // extract and integrate into this model.
    std::string connstr ("MGA=");
    connstr.append (filename);

    // Start a readonly transaction for the behavior project. This is
    // because we are importing elements from that model into this model.
    GAME::Project behavior_project = GAME::Project::_open (connstr);
    GAME::Transaction behavior_t (behavior_project, TRANSACTION_READ_ONLY);

    try
    {
      // Select all the TopLevelBehavior elements in the model.
      GAME::Filter behavior_filter (behavior_project);
      behavior_filter.kind ("TopLevelBehavior");

      std::vector <GAME::FCO> behavior_models;
      if (0 == behavior_filter.apply (behavior_models))
        return 0;

      // Display the list of TopLevelBehavior elements. We want to
      // select one of them that will be intergreted with an driver
      // component.
      using GAME::Dialogs::Object_Path_Dialog_Display_Strategy;
      using GAME::Dialogs::Selection_List_Dialog_T;

      Object_Path_Dialog_Display_Strategy display_strategy ("/");
      typedef Selection_List_Dialog_T <GAME::FCO> FCO_Selection_List_Dialog;
      FCO_Selection_List_Dialog selection_dialog (&display_strategy, ::AfxGetMainWnd ());

      selection_dialog.insert (behavior_models);
      selection_dialog.title ("Behavior Models");
      int retval = selection_dialog.DoModal ();

      if (retval == IDOK)
      {
        // Select the behavior model from the selected .mga file that will
        // be integrated into the structural model.
        GAME::Model behavior = GAME::Model::_narrow (selection_dialog.selection ());

        GAME::Model component, driver, method;
        GAME::Reference receptacle;

        if (!this->get_target_component (project, component))
          return 0;

        if (!this->generate_driver_component (component, idl_folder, driver))
          return 0;

        if (!this->get_receptacle_and_method (driver, receptacle, method))
          return 0;

        GAME::Model assembly;
        if (!this->integrate (component, receptacle, method, behavior, driver, assembly))
          return 0;

        GAME::Model domain;
        if (!this->generate_domain (project, domain))
          return 0;

        GAME::Model deployment;
        if (!this->generate_deployment (project, domain, assembly, deployment))
          return 0;
      }
    }
    catch (const GAME::Failed_Result & )
    {

    }
    catch (const GAME::Exception & )
    {

    }

    // Make sure we close the behavior project.
    behavior_t.commit ();
    behavior_project.close ();
  }
  catch (const GAME::Exception & )
  {

  }

  return 0;
}

//
// integrate
//
bool Quotas_Integrator_Impl::
integrate (const GAME::Model & component,
           const GAME::Reference & receptacle,
           const GAME::Model & method,
           const GAME::Model & behavior,
           GAME::Model driver,
           GAME::Model & assembly)
{
  // First, let's create the remaining structure of the test.
  GAME::Atom driver_impl, component_impl;
  GAME::Model driver_inst, component_inst;

  GAME::Project project = component.project ();
  GAME::Transaction t (project);

  // Copy the behavior into the specified model. We need to disable the
  // CBML Model Intelligence so we do not produce duplicate elements.
  // We can enable it once we are done with the copying process (i.e., the
  // current transaction.
  GAME::ComponentEx addon = project.addon_component ("MGA.AddOn.CBMLManager");
  addon.enable (false);

  GAME::Folder type_system;
  if (GAME::create_if_not (project.root_folder (), meta::PredefinedTypes, type_system,
      GAME::contains (boost::bind (std::equal_to <std::string> (),
                                   constants::Quotas_PredefinedTypes,
                                   boost::bind (&GAME::Folder::name, _1)))))
 {
   type_system.name (constants::Quotas_PredefinedTypes);
 }

  GAME::copy_config_t config;
  config.location_info_ = false;

  // First, copy over the type system from the behavior model.
  std::vector <GAME::Folder> type_systems;
  GAME::Folder root_folder = behavior.project ().root_folder ();
  root_folder.children (meta::PredefinedTypes, type_systems);

  std::vector <GAME::Folder>::iterator
    iter = type_systems.begin (), iter_end = type_systems.end ();

  for (; iter != iter_end; ++ iter)
    GAME::copy (*iter, type_system, config);

  // Now, copy the behavior to the target model.
  GAME::copy (behavior, driver, config);

  // Locate the RequestAction in the behavior model.
  std::vector <GAME::Model> actions;

  if (driver.children ("RequestAction", actions))
  {
    // Get the method's parameters. We need to create properties
    // in the request action for each parameter.
    std::vector <GAME::Reference> params;
    method.children ("InParameter", params);

    // Set the name/method of each generic request action to the
    // provided receptacle and method.
    std::vector <GAME::Model>::iterator
      iter = actions.begin (), iter_end = actions.end ();

    for (; iter != iter_end; ++ iter)
    {
      iter->name (receptacle.name ());
      iter->attribute ("MethodName").string_value (method.name ());

      // Set the parameters for the action.
      std::for_each (params.begin (),
                     params.end (),
                     boost::bind (&Quotas_Integrator_Impl::create_action_parameter,
                                  this,
                                  *iter,
                                  _1,
                                  boost::ref (config.mapping_)));
    }
  }

  // Save the current state and re-enable the addon.
  t.flush ();
  addon.enable (true);

  // Generate the default implementations and the assembly.
  if (!this->get_default_qoutas_impl (driver, driver_impl))
    return false;

  if (!this->get_default_qoutas_impl (component, component_impl))
    return false;

  t.commit ();

  if (!this->create_assembly (driver_impl, component_impl, assembly))
    return false;

  return true;
}

//
// generate_domain
//
bool Quotas_Integrator_Impl::
generate_domain (GAME::Project proj, GAME::Model & domain)
{
  // Start a new tranaction.
  GAME::Transaction t (proj);

  static const std::string meta_Targets ("Targets");
  static const std::string constant_Quotas_Targets ("Quotas_Targets");

  // Create the folder for the domain.
  GAME::Folder targets;
  if (GAME::create_if_not (proj.root_folder (), meta_Targets, targets,
      GAME::contains (boost::bind (std::equal_to <std::string> (),
                                   constant_Quotas_Targets,
                                   boost::bind (&GAME::Folder::name, _1)))))
  {
    targets.name (constant_Quotas_Targets);
  }

  static const std::string constant_Quotas_Domain ("Quotas_Domain");
  Quotas_Domain_Generator domain_gen;

  // Now, let's create the domain.
  if (!domain_gen.generate (targets, constant_Quotas_Domain, 1))
    return false;

  domain = domain_gen.generated_domain ();
  t.commit ();

  return true;
}

//
// generate_deployment
//
bool Quotas_Integrator_Impl::
generate_deployment (GAME::Project proj,
                     const GAME::Model & domain,
                     const GAME::Model & assembly,
                     GAME::Model & deployment)
{
  // Start a new tranaction.
  GAME::Transaction t (proj);

  static const std::string meta_DeploymentPlans ("DeploymentPlans");
  static const std::string constant_Quotas_DeploymentPlans ("Quotas_DeploymentPlans");

  // Create the folder for the deployment plans.
  GAME::Folder plans;
  if (GAME::create_if_not (proj.root_folder (), meta_DeploymentPlans, plans,
      GAME::contains (boost::bind (std::equal_to <std::string> (),
                                   constant_Quotas_DeploymentPlans,
                                   boost::bind (&GAME::Folder::name, _1)))))
  {
    plans.name (constant_Quotas_DeploymentPlans);
  }

  t.commit ();

  // Create the deployment plan.
  static const std::string constant_DeploymentPlan ("DeploymentPlan");
  Quotas_Deployment_Generator deployment_gen;

  if (!deployment_gen.generate (plans,
                                constant_DeploymentPlan,
                                domain,
                                assembly,
                                deployment))
  {
    return false;
  }

  return true;
}

//
// get_default_qoutas_impl
//
bool Quotas_Integrator_Impl::
get_default_qoutas_impl (const GAME::Model & c, GAME::Atom & impl)
{
  std::stack <GAME::Object> s;
  GAME::Object parent = c.parent ();

  while (parent.meta ().name () != "File")
  {
    s.push (parent);
    parent = parent.parent ();
  }

  std::string name;

  while (!s.empty ())
  {
    // Get the next parent on the stack.
    parent = s.top ();
    s.pop ();

    // Append the name of the parent.
    name += parent.name () +  "_";
  }

  // Finish of the name of the implementation.
  name += c.name () + "Impl";

  // Construct the path of the implementation.
  std::string path =
    constants::Quotas_ComponentImplementations + "/" +
    name + "/" + name;

  // Use the constructed name to locate the real object.
  GAME::Object obj = c.project ().root_folder ().find_object_by_path (path);

  if (obj.is_nil ())
    return false;

  impl = GAME::Atom::_narrow (obj);
  return true;
}

//
// create_assembly
//
bool Quotas_Integrator_Impl::
create_assembly (const GAME::Atom & driver_impl,
                 const GAME::Atom & comp_impl,
                 GAME::Model & assembly)
{
  GAME::Transaction t (driver_impl.project ());

  // Make sure the target folder exists.
  GAME::Project project = driver_impl.project ();
  GAME::Folder folder;

  if (GAME::create_if_not (project.root_folder (), meta::ComponentImplementations, folder,
      GAME::contains (boost::bind (std::equal_to <std::string> (),
                                   constants::Quotas_ComponentImplementations,
                                   boost::bind (&GAME::Folder::name, _1)))))
  {
    folder.name (constants::Quotas_ComponentImplementations);
  }

  // Construct the name fo the target assembly, and container.
  std::string assembly_name (comp_impl.name ());
  assembly_name += "_Test";

  // Make the container for the component assembly.
  GAME::Model container;
  if (GAME::create_if_not (folder, meta::ComponentImplementationContainer, container,
      GAME::contains (boost::bind (std::equal_to <std::string> (),
                                   assembly_name,
                                   boost::bind (&GAME::Folder::name, _1)))))
  {
    container.name (assembly_name);
  }

  // Create the assembly for the component.
  if (GAME::create_if_not (container, meta::ComponentAssembly, assembly,
      GAME::contains (boost::bind (std::equal_to <std::string> (),
                                   assembly_name,
                                   boost::bind (&GAME::Model::name, _1)))))
  {
    assembly.name (assembly_name);
  }

  // Create the component instance for the target component.
  GAME::Model comp_inst;
  if (GAME::create_if_not (assembly, meta::ComponentInstance, comp_inst,
      GAME::contains (boost::bind (std::equal_to <std::string> (),
                                   comp_impl.name (),
                                   boost::bind (&GAME::Model::name, _1)))))
  {
    comp_inst.name (comp_impl.name ());
  }

  // Make sure the instance type is set.
  GAME::Reference inst_type = GAME::Reference::_create (comp_inst, meta::ComponentInstanceType);
  inst_type.name (comp_impl.name ());
  inst_type.refers_to (comp_impl);

  // Create the component instance for the driver component.
  GAME::Model driver_inst;
  if (GAME::create_if_not (assembly, meta::ComponentInstance, driver_inst,
      GAME::contains (boost::bind (std::equal_to <std::string> (),
                                   driver_impl.name (),
                                   boost::bind (&GAME::Model::name, _1)))))
  {
    driver_inst.name (driver_impl.name ());
  }

  // Make sure the instance type is set.
  inst_type = GAME::Reference::_create (driver_inst, meta::ComponentInstanceType);
  inst_type.name (driver_impl.name ());
  inst_type.refers_to (driver_impl);

  t.flush ();

  // Finally, make a connection between the two instances.
  GAME::Reference receptacle;
  if (!this->get_testdriver_receptacle (driver_inst, receptacle))
    return false;

  GAME::Reference facet;
  if (!this->get_testobject_facet (comp_inst, facet))
    return false;

  GAME::Connection invoke_connection;
  if (!GAME::find (assembly, "Invoke", invoke_connection,
       boost::bind (std::logical_and <bool> (),
                    boost::bind (std::equal_to <GAME::FCO> (),
                                 receptacle,
                                 boost::bind (&GAME::Connection::src, _1)),
                    boost::bind (std::equal_to <GAME::FCO> (),
                                 facet,
                                 boost::bind (&GAME::Connection::dst, _1)))))
  {
    invoke_connection = GAME::Connection::_create (assembly,
                                                   "Invoke",
                                                   receptacle,
                                                   facet);
  }

  t.commit ();

  return true;
}

//
// get_target_component
//
bool Quotas_Integrator_Impl::
get_target_component (GAME::Project & project, GAME::Model & component)
{
  GAME::Transaction t (project, TRANSACTION_READ_ONLY);

  // First, let's filter out all the Component elements that are contained
  // in this model. We can then determine how to proceed once we know how
  // many Component elements there are.
  GAME::Filter filter (project);
  filter.kind ("Component");

  std::vector <GAME::FCO> components;

  switch (filter.apply (components))
  {
  case 0:
    return false;

  case 1:
    component = GAME::Model::_narrow (components.front ());
    break;

  default:
    {
      using GAME::Dialogs::Selection_List_Dialog_T;
      using GAME::Dialogs::Object_Path_Dialog_Display_Strategy;

      // Display a dialog that allows the user to select a component from
      // the list of components available in the model.
      Object_Path_Dialog_Display_Strategy display ("/", true);

      typedef Selection_List_Dialog_T <GAME::FCO> Selection_Dialog;
      Selection_Dialog selector (&display, ::AfxGetMainWnd ());

      // Set the title of the dialog.
      selector.insert (components);
      selector.title ("Component Models");

      if (selector.DoModal () == IDCANCEL)
        return false;

      // Save the component.
      component = GAME::Model::_narrow (selector.selection ());
    }
    break;
  }

  return true;
}

//
// get_target_receptacle_and_method
//
bool Quotas_Integrator_Impl::
get_receptacle_and_method (const GAME::Model & driver,
                           GAME::Reference & receptacle,
                           GAME::Model & method)
{
  GAME::Transaction t (driver.project (), TRANSACTION_READ_ONLY);

  std::vector <GAME::Reference> receptacles;

  switch (driver.children ("RequiredRequestPort", receptacles))
  {
  case 0:
    return false;

  case 1:
    receptacle = receptacles.front ();
    break;

  default:
    {
      using GAME::Dialogs::Selection_List_Dialog_T;

      // Display a dialog that allows the user to select a recetacle
      // from the list of components available in the model.
      typedef Selection_List_Dialog_T <GAME::Reference> Selection_Dialog;
      Selection_Dialog selector (0, ::AfxGetMainWnd ());

      selector.insert (receptacles);
      selector.title ("Target Receptacle");

      if (selector.DoModal () == IDCANCEL)
        return false;

      receptacle = selector.selection ();
    }
  }

  // Finally, select the target method from the receptacle that we
  // would like to validate. We do this by getting the receptacle's
  // type and selecting one of its methods.
  GAME::Model object = GAME::Model::_narrow (receptacle.refers_to ());
  std::vector <GAME::Model> methods;

  switch (object.children ("TwowayOperation", methods))
  {
  case 0:
    return false;

  case 1:
    method = methods.front ();
    break;

  default:
    {
      using GAME::Dialogs::Selection_List_Dialog_T;

      // Display a dialog that allows the user to select a recetacle
      // from the list of components available in the model.
      Selection_List_Dialog_T <GAME::Model> selector (0, ::AfxGetMainWnd ());
      selector.title ("Target Method");
      selector.insert (methods);

      if (selector.DoModal () == IDCANCEL)
        return false;

      method = selector.selection ();
    }
  }

  return true;
}

//
// generate_driver_component
//
bool Quotas_Integrator_Impl::
generate_driver_component (const GAME::Model & component,
                           GAME::Folder & idl_folder,
                           GAME::Model & driver)
{
  GAME::Transaction t (idl_folder.project ());

  // Generate the driver component for this component.
  Quotas_Driver_Component_Generator driver_gen (idl_folder);
  bool retval = driver_gen.generate (component, driver);

  if (retval)
    t.commit ();

  return retval;
}

//
// set_action_parameters
//
bool Quotas_Integrator_Impl::
create_action_parameter (GAME::Model action,
                         const GAME::Reference & param,
                         std::map <GAME::FCO, GAME::FCO> & mapping)
{
  // First, create a property for the parameter.
  GAME::Reference simple_property;
  const std::string param_name (param.name ());

  if (GAME::create_if_not (action, meta::SimpleProperty, simple_property,
      GAME::contains (boost::bind (std::equal_to <std::string> (),
                                   param_name,
                                   boost::bind (&GAME::Model::name, _1)))))
  {
    simple_property.name (param_name);
  }

  // Set position of property to the same as the parameter.
  GAME::utils::Point pt;
  GAME::utils::position ("InterfaceDefinition", param, pt);
  GAME::utils::position ("Behavior", pt, simple_property);

  const GAME::FCO & refers_to = mapping[param.refers_to ()];
  simple_property.refers_to (refers_to);

  if (!refers_to.is_nil ())
  {
    // Finally, set value to the correct random generator.
    GAME::Attribute value = simple_property.attribute ("Value");
    GAME::Meta::FCO metafco = refers_to.meta ();

    if (metafco == "String" || metafco == "WideString")
      value.string_value ("RandomStringDataGenerator.getSingleton ().getNextString ()");
    else if (metafco == "LongInteger" || metafco == "UnsignedLongInteger")
      value.string_value ("RandomLongIntegerDataGenerator.getSingleton ().getNextLongInteger ()");
    else if (metafco == "ShortInteger" || metafco == "UnsignedShortInteger")
      value.string_value ("RandomShortIntegerDataGenerator.getSingleton ().getNextShortInteger ()");
    else if (metafco == "Boolean")
      value.string_value ("RandomBooleanDataGenerator.getSingleton ().getNextBoolean ()");
  }

  return true;
}

//
// get_testobject_facet
//
bool Quotas_Integrator_Impl::
get_testobject_facet (const GAME::Model & model,
                      GAME::Reference & facet)
{
  std::vector <GAME::Reference> insts;
  if (0 == model.children ("ProvidedRequestPortInstance", insts))
    return false;

  facet = insts.front ();
  return true;
}

//
// get_testdriver_receptacle
//
bool Quotas_Integrator_Impl::
get_testdriver_receptacle (const GAME::Model & model,
                           GAME::Reference & receptacle)
{
  std::vector <GAME::Reference> insts;
  if (0 == model.children ("RequiredRequestPortInstance", insts))
    return false;

  receptacle = insts.front ();
  return true;
}
