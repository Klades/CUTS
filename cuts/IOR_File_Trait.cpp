// $Id$

#include "IOR_File_Trait.h"
#include "ace/OS_NS_unistd.h"
#include "ace/streams.h"

//
// handle_activate
//
int CUTS_IOR_File_Trait::
handle_activate (::CORBA::Object_ptr obj, const ACE_CString & value)
{
  // Get the ORB for this object.
  ::CORBA::ORB_var orb = obj->_get_orb ();

  if (::CORBA::is_nil (orb.in ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to resolve ORB\n")),
                       1);

  // Convert the object to a string.
  ::CORBA::String_var str = orb->object_to_string (obj);

  // Write the string to the specified file.
  std::ofstream file;
  file.open (value.c_str ());

  if (!file.is_open ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to open %s for writing\n"),
                       value.c_str ()),
                       1);

  file << str.in ();
  file.close ();

  return 0;
}

//
// handle_deactivate
//
int CUTS_IOR_File_Trait::
handle_deactivate (::CORBA::Object_ptr obj,  const ACE_CString & value)
{
  ACE_OS::unlink (value.c_str ());
  return 0;
}
