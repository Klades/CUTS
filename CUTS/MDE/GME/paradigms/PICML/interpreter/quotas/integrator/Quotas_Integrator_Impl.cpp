// $Id$

#include "stdafx.h"
#include "Quotas_Integrator.h"
#include "Quotas_Integrator_Impl.h"
#include "Quotas_Driver_Component.h"

#include "game/be/Interpreter_T.h"
#include "game/ComponentEx.h"
#include "game/Atom.h"
#include "game/Attribute.h"
#include "game/Model.h"
#include "game/Reference.h"
#include "game/MetaAspect.h"
#include "game/MetaModel.h"
#include "game/Transaction.h"
#include "game/Filter.h"
#include "game/manip/copy.h"
#include "game/utils/modelgen.h"
#include "game/utils/Point.h"

#include "game/dialogs/Selection_List_Dialog.h"
#include "game/dialogs/Object_Path_Dialog_Display_Strategy.h"

#include "boost/bind.hpp"

#include <functional>
#include <stack>

GAME_DECLARE_INTERPRETER (Quotas_Integrator_Interpreter, Quotas_Integrator_Impl);

namespace constants
{
  static const std::string Quotas_InterfaceDefinitions ("Quotas_InterfaceDefinitions");
  static const std::string Quotas_ComponentImplementations ("Quotas_ComponentImplementations");
}

namespace meta
{
  static const std::string InterfaceDefinitions ("InterfaceDefinitions");
  static const std::string ComponentImplementations ("ComponentImplementations");
  static const std::string ComponentImplementationContainer ("ComponentImplementationContainer");
  static const std::string ComponentAssembly ("ComponentAssembly");
  static const std::string ComponentInstance ("ComponentInstance");
  static const std::string ComponentInstanceType ("ComponentInstanceType");
  static const std::string Property ("Property");
  static const std::string DataValue ("DataValue");
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
    // Let's see if we can find the PICMLManager addon. It will have
    // the progid of MGA.AddOn.PICMLManager.
    static const std::string name ("MGA.AddOn.PICMLManager");
    GAME::ComponentEx addon = project.addon_component (name);

    VERIFY_HRESULT (addon.impl ()->QueryInterface (&this->configurator_));

    this->configurator_->setImplementationFolder (ATL::CComBSTR ("Quotas_ComponentImplementations"));
    this->configurator_->setArtifactFolder (ATL::CComBSTR ("Quotas_ImplmentationArtifacts"));
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
      using GAME::Dialogs::Selection_List_Dialog;

      Object_Path_Dialog_Display_Strategy display_strategy ("/");

      Selection_List_Dialog <GAME::FCO>
        selection_dialog (behavior_models, &display_strategy, ::AfxGetMainWnd ());

      selection_dialog.title ("Behavior Models");

      if (selection_dialog.DoModal () == IDOK)
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

        if (!this->integrate (component, receptacle, method, behavior, driver))
          return 0;
      }
    }
    catch (const GAME::Failed_Result &)
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
int Quotas_Integrator_Impl::
integrate (const GAME::Model & component,
           const GAME::Reference & receptacle,
           const GAME::Model & method,
           const GAME::Model & behavior,
           GAME::Model & driver)
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

  GAME::copy (behavior, driver);

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
                                  _1));
    }
  }

  // Save the current state and re-enable the addon.
  t.flush ();
  addon.enable (true);

  // Generate the default implementations and the assembly.
  if (this->get_default_qoutas_impl (driver, driver_impl) &&
      this->get_default_qoutas_impl (component, component_impl) &&
      this->create_assembly (driver_impl, driver_inst, component_impl, component_inst))
  {
    t.commit ();
    return 0;
  }

  return -1;
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
  std::string path ("Quotas_ComponentImplementations");
  path += "/" + name + "/" + name;

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
                 GAME::Model & driver_inst,
                 const GAME::Atom & comp_impl,
                 GAME::Model & comp_inst)
{
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
  GAME::Model assembly;
  if (GAME::create_if_not (container, meta::ComponentAssembly, assembly,
      GAME::contains (boost::bind (std::equal_to <std::string> (),
                                   assembly_name,
                                   boost::bind (&GAME::Model::name, _1)))))
  {
    assembly.name (assembly_name);
  }

  // Create the component instance for the target component.
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
  if (GAME::create_if_not (assembly, meta::ComponentInstance, driver_inst,
      GAME::contains (boost::bind (std::equal_to <std::string> (),
                                   driver_impl.name (),
                                   boost::bind (&GAME::Model::name, _1)))))
  {
    driver_inst.name (driver_impl.name ());
  }

  // Make sure the instance type is set.
  //inst_type = GAME::Reference::_create (driver_inst, meta::ComponentInstanceType);
  //inst_type.name (driver_impl.name ());
  //inst_type.refers_to (driver_impl);

  return true;
}

//
// get_target_component
//
bool Quotas_Integrator_Impl::
get_target_component (GAME::Project & project, GAME::Model & component)
{
  GAME::Transaction t (project, TRANSACTION_READ_ONLY);

  // First, let's filter out all the Component elements that are
  // contained in this model. We can then determine how to proceed
  // once we know how many Component elements there are.
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
      using GAME::Dialogs::Selection_List_Dialog;
      using GAME::Dialogs::Object_Path_Dialog_Display_Strategy;

      // Display a dialog that allows the user to select a
      // component from the list of components available in
      // the model.
      Object_Path_Dialog_Display_Strategy display ("/", true);
      typedef Selection_List_Dialog <GAME::FCO> Selection_Dialog;
      Selection_Dialog selector (components, &display, ::AfxGetMainWnd ());

      // Set the title of the dialog.
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
      using GAME::Dialogs::Selection_List_Dialog;

      // Display a dialog that allows the user to select a recetacle
      // from the list of components available in the model.
      Selection_List_Dialog <GAME::Reference> selector (receptacles, 0, ::AfxGetMainWnd ());
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
      using GAME::Dialogs::Selection_List_Dialog;

      // Display a dialog that allows the user to select a recetacle
      // from the list of components available in the model.
      Selection_List_Dialog <GAME::Model> selector (methods, 0, ::AfxGetMainWnd ());
      selector.title ("Target Method");

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
create_action_parameter (GAME::Model action, const GAME::Reference & param)
{
  // First, create a property for the parameter.
  GAME::Model prop;
  const std::string param_name (param.name ());

  if (GAME::create_if_not (action, meta::Property, prop,
      GAME::contains (boost::bind (std::equal_to <std::string> (),
                                   param_name,
                                   boost::bind (&GAME::Model::name, _1)))))
  {
    prop.name (param_name);
  }

  // Set position of property to the same as the parameter.
  GAME::utils::Point pt;
  GAME::utils::position ("InterfaceDefinition", param, pt);
  GAME::utils::position ("Behavior", pt, prop);

  // Create a data value for the property. Right now, we make
  // the assumption we are working with only simple types.
  GAME::Reference data_value;
  const GAME::FCO refers_to = param.refers_to ();

  if (GAME::create_if_not (prop, meta::DataValue, data_value,
      GAME::contains (boost::bind (std::equal_to <GAME::FCO> (),
                                   refers_to,
                                   boost::bind (&GAME::Reference::refers_to, _1)))))
  {
    data_value.refers_to (refers_to);
  }

  // Set the name and position of the data value.
  data_value.name (param_name);
  GAME::utils::position ("DataValueAspect", pt, data_value);

  // Finally, set value to the correct random generator.
  GAME::Attribute value = data_value.attribute ("Value");
  GAME::Meta::FCO metafco = refers_to.meta ();

  if (metafco == "String" || metafco == "WideString")
    value.string_value ("RandomStringDataGenerator.getSingleton ().getNextString ()");
  else if (metafco == "LongInteger" || metafco == "UnsignedLongInteger")
    value.string_value ("RandomLongIntegerDataGenerator.getSingleton ().getNextLongInteger ()");
  else if (metafco == "ShortInteger" || metafco == "UnsignedShortInteger")
    value.string_value ("RandomShortIntegerDataGenerator.getSingleton ().getNextShortInteger ()");
  else if (metafco == "Boolean")
    value.string_value ("RandomBooleanDataGenerator.getSingleton ().getNextBoolean ()");

  return true;
}
