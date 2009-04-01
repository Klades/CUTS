// $Id$

#include "Presentation_Service_Manager.h"

#if !defined (__CUTS_INLINE__)
#include "Presentation_Service_Manager.inl"
#endif

#include "Presentation_Service.h"
#include "Unit_Test_Result.h"
#include "ace/Service_Types.h"

//
// handle_result
//
int CUTS_Unite_Presentation_Service_Manager::
handle_result (CUTS_Unit_Test_Result & result)
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
