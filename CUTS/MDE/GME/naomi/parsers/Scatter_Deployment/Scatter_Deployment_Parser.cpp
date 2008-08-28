// $Id$

#include "Scatter_Deployment_Parser.h"
#include "GME/T2M/parsers/Scatter_Deployment/Scatter_Deployment_Parser.h"
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
  if (name == "software.components")
  {
    size_t pos = uri.find_first_of (":\\\\");

    if (pos != std::string::npos)
      this->filename_ = uri.substr (pos + 3);
    else
      this->filename_ = uri;
  }

  return 0;
}

//
// run
//
int NAOMI_Scatter_Deployment_Parser::
run (GME::Object & target, const std::string & attr_path)
{
  // Construct the full name of the deployments filename.
  std::ostringstream ostr;
  ostr << attr_path << "/" << this->filename_;

  // Parse the Scatter deployment plan.
  Scatter_Deployment_Parser parser;
  parser.parse (ostr.str (), target);

  return 0;
}

GME_NAOMI_CREATE_PARSER_IMPLEMENT (NAOMI_Scatter_Deployment_Parser);
