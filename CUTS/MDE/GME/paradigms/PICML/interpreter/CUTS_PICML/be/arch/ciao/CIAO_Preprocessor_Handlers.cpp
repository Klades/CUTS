// $Id$

#include "CIAO_Preprocessor_Handlers.h"
#include "../../BE_Impl_Node.h"

//
// CUTS_BE_Preprocessor_WorkerLibrary_T
//
bool CUTS_BE_Preprocessor_WorkerLibrary_T <CUTS_BE_Ciao>::
handle (CUTS_BE_Impl_Node * node, const PICML::WorkerLibrary & lib)
{
  // Save the name of the library.
  node->lib_.insert (lib.name ());

  // Save the location of the library.
  std::string location = lib.Location ();

  if (!location.empty ())
    node->lib_paths_.insert (lib.Location ());

  return true;
}

//
// CUTS_BE_Preprocessor_WorkerFile_T
//
bool CUTS_BE_Preprocessor_WorkerFile_T <CUTS_BE_Ciao>::
handle (CUTS_BE_Impl_Node * node, const PICML::WorkerFile & file)
{
  // Save the name of the file.
  node->include_.insert (file.name ());

  // Save the location of the file.
  std::string location = file.Location ();

  if (!location.empty ())
    node->include_paths_.insert (location);

  return true;
}
