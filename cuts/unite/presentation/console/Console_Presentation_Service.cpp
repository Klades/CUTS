// $Id$

#include "Console_Presentation_Service.h"

#if !defined (__CUTS_INLINE__)
#include "Console_Presentation_Service.inl"
#endif

#include "cuts/unite/Dataset_Result.h"
#include "ace/Service_Config.h"
#include "ace/streams.h"

struct print_group_name_item
{
public:
  print_group_name_item (std::ostream & out,
                         const char * separator,
                         size_t count)
    : out_ (out),
      separator_ (separator),
      count_ (count)
  {

  }

  void operator () (const ACE_CString & name)
  {
    this->out_ << name.c_str ();

    if (this->count_ -- != 1)
      this->out_ << this->separator_;
  }

private:
  std::ostream & out_;

  const char * separator_;

  size_t curr_;

  size_t count_;
};

//
// handle_result
//
int CUTS_Console_Presentation_Service::
handle_result (CUTS_Dataset_Result & result)
{
  // Print the result(s) to the console.

  if (result.has_groupings ())
  {
    std::cout << "Test Result(s):" << std::endl
              << "=====================================" << std::endl;

    for (; !result.done (); result.advance ())
    {
      std::cout << ". ";

      // Print the group name of the result.
      std::for_each (result.get_group_name ().begin (),
                     result.get_group_name ().end (),
                     print_group_name_item (std::cout,
                                            ".",
                                            result.get_group_name ().size ()));

      // Print the actual result.
      std::cout << ": " << result.get_result () << std::endl;
    }

  }
  else
  {
    // Print the results without any group information.
    std::cout << "Test Result(s):" << std::endl
              << "=====================================" << std::endl;

    for (size_t index = 0 ; !result.done (); result.advance ())
      std::cout << ". " << (index ++) << " " << result.get_result () << std::endl;
  }

  return 0;
}

///////////////////////////////////////////////////////////////////////////////
//

ACE_STATIC_SVC_DEFINE (CUTS_Console_Presentation_Service,
                       ACE_TEXT ("cuts.console"),
                       ACE_SVC_OBJ_T,
                       &ACE_SVC_NAME (CUTS_Console_Presentation_Service),
                       ACE_Service_Type::DELETE_THIS | ACE_Service_Type::DELETE_OBJ,
                       1)

ACE_FACTORY_DEFINE (CUTS_CONSOLE_PRESENTATION_SERVICE,
                    CUTS_Console_Presentation_Service)
