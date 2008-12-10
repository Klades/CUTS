// $Id$

#include "Naomi_Generator.h"
#include "game/GME.h"
#include "game/ComponentEx.h"
#include <sstream>

//
// GME_Naomi_Generator
//
GME_Naomi_Generator::GME_Naomi_Generator (void)
{

}

//
// GME_Naomi_Generator
//
GME_Naomi_Generator::GME_Naomi_Generator (const std::string & doc)
: documentation_ (doc)
{

}

//
// ~GME_Naomi_Generator
//
GME_Naomi_Generator::~GME_Naomi_Generator (void)
{

}

//
// resources
//
const GME_Naomi_Resource_List &
GME_Naomi_Generator::resources (void) const
{
  return this->resources_;
}

//
// run_i
//
int GME_Naomi_Generator::
run_i (const std::string & attr,
       const std::string & attr_path,
       GME::Object & target,
       const std::string & prog_id)
{
  GME::RegistryNode parameters;
  std::ostringstream regpath;

  // Actual location of the parameters in the registry.
  regpath
    << "naomi:\\\\" << attr << "/parameters";

  try
  {
    GME::FCO fco = GME::FCO::_narrow (target);
    parameters = fco.registry_node (regpath.str ().c_str ());
  }
  catch (...)
  {
    GME::Folder folder = GME::Folder::_narrow (target);
    parameters = folder.registry_node (regpath.str ().c_str ());
  }

  try
  {
    // Load the specified interpreter.
    GME::ComponentEx interpreter (prog_id);

    // Pass the standard configuration to the interpreter.
    interpreter.parameter ("non-interactive", "");
    interpreter.parameter ("output", attr_path);

    // Configure the interpreter using the parameters in the collection
    // of registry nodes.
    typedef GME::Collection_T <GME::RegistryNode> RegistryNodes;

    if (parameters)
    {
      RegistryNodes parameter_list;
      size_t n = parameters.children (parameter_list);

      RegistryNodes::iterator
        iter = parameter_list.begin (),
        iter_end = parameter_list.end ();

      for ( ; iter != iter_end; ++ iter)
        interpreter.parameter (iter->name (), iter->value ());
    }

    // Execute the interpreter on the currently selected object. We
    // also should make it the focus object.
    GME::Project project = target.project ();
    GME::FCO focus = GME::FCO::_narrow (target);

    std::vector <GME::FCO> selected;
    selected.push_back (focus);

    // Before we invoke the interpreter, we must commit the current
    // transaction, and begin a new transaction.
    project.commit_transaction ();

    try
    {
      // Invoke the target interpreter.
      interpreter.invoke (project, focus, selected, 0);
    }
    catch (const GME::Exception & )
    {
      ACE_ERROR ((LM_ERROR,
                  "%T - %M - caught GME exception\n"));
    }

    // Just in case something else happens after this point, we
    // need to restart the default transaction.
    project.begin_transaction ();
  }
  catch (...)
  {
    return -1;
  }

  return 0;
}

//
// destroy
//
void GME_Naomi_Generator::destroy (void)
{
  delete this;
}

//
// description
//
const std::string & GME_Naomi_Generator::documentation (void) const
{
  return this->documentation_;
}
