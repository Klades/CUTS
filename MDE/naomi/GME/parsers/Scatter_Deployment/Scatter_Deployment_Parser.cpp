// $Id$

#include "Scatter_Deployment_Parser.h"
#include "GME/T2M/parsers/Scatter_Deployment/Scatter_Deployment_Parser.h"
#include "game/Model.h"
#include "game/Project.h"
#include "game/RegistryNode.h"
#include "ace/Log_Msg.h"
#include <sstream>

//
// NAOMI_Scatter_Deployment_Parser
//
NAOMI_Scatter_Deployment_Parser::NAOMI_Scatter_Deployment_Parser (void)
{

}

//
// NAOMI_Scatter_Deployment_Parser
//
NAOMI_Scatter_Deployment_Parser::~NAOMI_Scatter_Deployment_Parser (void)
{

}

//
// handle_resource
//
int NAOMI_Scatter_Deployment_Parser::
handle_resource (const std::string & name, const std::string & uri)
{
  if (name == "cutsPairs")
  {
    size_t pos = uri.find_first_of (":\\\\");

    if (pos != std::string::npos)
      this->filename_ = ".." + uri.substr (pos + 3);
    else
      this->filename_ = uri;
  }

  return 0;
}

//
// run
//
int NAOMI_Scatter_Deployment_Parser::
run (GME::Object & target, const std::string & attr, const std::string & path)
{
  // Get the parameters, if any.
  GME::Model deployment = GME::Model::_narrow (target);

  // Construct the full name of the deployments filename.
  // Actual location of the parameters in the registry.
  std::ostringstream regpath;
  regpath << "naomi:\\\\" << attr << "/parameters";
  GME::RegistryNode parameters = deployment.registry_node (regpath.str ());

  GME::Model target_assembly;
  GME::Model target_domain;

  if (parameters)
  {
    typedef GME::Collection_T <GME::RegistryNode> RegistryNodes;

    RegistryNodes parameter_list;
    size_t n = parameters.children (parameter_list);

    RegistryNodes::iterator
      iter = parameter_list.begin (),
      iter_end = parameter_list.end ();

    std::string value;
    GME::Object found_obj;

    for ( ; iter != iter_end; ++ iter)
    {

      if (iter->name () == "targetAssembly")
      {
        // Locate the target assembly in the project.
        value = iter->value ();

        found_obj =
          target.project ().root_folder ().find_object_by_path (value);

        if (found_obj)
        {
          target_assembly = GME::Model::_narrow (found_obj);
        }
        else
        {
          ACE_ERROR ((LM_ERROR,
                      "%T - %M - failed to locate object %s; please "
                      "verify its path exist in model\n",
                      value.c_str ()));
        }
      }
      else if (iter->name () == "targetDomain")
      {
        value = iter->value ();

        // Locate the target domain in the project.
        found_obj =
          target.project ().root_folder ().find_object_by_path (value);

        if (found_obj)
        {
          target_domain = GME::Model::_narrow (found_obj);
        }
        else
        {
          ACE_ERROR ((LM_ERROR,
                      "%T - %M - failed to locate object %s; verify its path; ",
                      "exist in the model\n",
                      value.c_str ()));
        }
      }
    }
  }

  // Construct the output filename.
  std::ostringstream ostr;
  ostr << path << "/" << this->filename_;

  // Parse the Scatter deployment plan.
  Scatter_Deployment_Parser parser;
  return parser.parse (ostr.str (), target, target_assembly, target_domain) ? 0 : -1;
}

GME_NAOMI_CREATE_PARSER_IMPLEMENT (NAOMI_Scatter_Deployment_Parser);
