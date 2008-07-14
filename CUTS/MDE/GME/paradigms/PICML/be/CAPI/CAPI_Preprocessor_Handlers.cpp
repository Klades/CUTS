// $Id$

#include "CAPI_Preprocessor_Handlers.h"
#include "be/BE_Impl_Node.h"
#include "be/BE_Env_Variable_Parser_T.h"
#include "boost/spirit/actor.hpp"
#include <sstream>

/**
 * @struct ANT_Env_Variable
 */
struct ANT_Env_Variable
{
public:
  ANT_Env_Variable (std::string & out)
    : out_ (out)
  { 
  }

  template <typename IteratorT>
  void operator () (IteratorT begin, IteratorT end) const
  {
    std::string var (begin, end);
    this->out_ += "${env." + var + "}";
  }

private:
  std::string & out_;
};

//
// CUTS_BE_Preprocessor_Worker_T
//
bool CUTS_BE_Preprocessor_Worker_T <CUTS_BE_Capi>:: 
handle (CUTS_BE_Impl_Node * node, const PICML::Worker & worker)
{
  std::string import = CUTS_BE_Capi::import (worker);
  node->maplist_["imports"].insert (import);
  return true;
}

//
// CUTS_BE_Preprocessor_WorkerLibrary_T
//
bool CUTS_BE_Preprocessor_WorkerLibrary_T <CUTS_BE_Capi>::
handle (CUTS_BE_Impl_Node * node, const PICML::WorkerLibrary & lib)
{
  std::string location = lib.Location ();
  std::ostringstream jarfile;

  // Get the full path of the JAR file.
  if (!location.empty ())
    jarfile << lib.Location () << "/";
  
  jarfile << lib.name () << ".jar";

  // Convert any environment variables defined in the JAR file.
  std::string output;
  CUTS_BE_Env_Variable_Parser_T <ANT_Env_Variable> env_parser (output);

  boost::spirit::parse (jarfile.str ().c_str (), env_parser);

  // Insert the JAR file into the CLASSPATH.
  node->maplist_["classpath"].insert (output);
  
  return true;
}
