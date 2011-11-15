// $Id$

#include "Presentation_Service_Manager.h"

#if !defined (__CUTS_INLINE__)
#include "Presentation_Service_Manager.inl"
#endif

#include "Dataset_Result.h"
#include "Presentation_Service.h"
#include "ace/Service_Types.h"
#include <sstream>

//
// handle_result
//
int CUTS_Unite_Presentation_Service_Manager::
handle_result (CUTS_Dataset_Result & result)
{
  ACE_Service_Repository_Iterator iter (*this->repo_);

  const ACE_Service_Type * type = 0;
  const ACE_Service_Type_Impl * type_impl = 0;
  CUTS_Unite_Presentation_Service * svc = 0;
  int retval = 0;

  for (; !iter.done (); iter.advance ())
  {
    // Get the next item in the repo.
    iter.next (type);

    if (type != 0)
    {
      // Extract the concrete service from the service object.
      type_impl = type->type ();

      if (type_impl != 0)
      {
        svc =
          reinterpret_cast <
          CUTS_Unite_Presentation_Service *> (type_impl->object ());

        if (svc != 0)
        {
          // Pass the result to the service.
          if (svc->handle_result (result) != 0)
            ++ retval;

          // Rewind the the result to the beginning.
          result.rewind ();
        }
      }
    }
  }

  return retval;
}

//
// load_service
//
int CUTS_Unite_Presentation_Service_Manager::
load_service (const char * id,
              const char * location,
              const char * classname,
              const char * params)
{
  std::ostringstream directive;
  directive << "dynamic " << id << " Service_Object * "
            << location << ":_make_" << classname << "() active";

  if (params != 0)
    directive << " '" << params << "'";

  return this->process_directive (directive.str ().c_str ());
}