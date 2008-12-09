// $Id$

#include "Test_Summary_Service.h"

#if !defined (__CUTS_INLINE__)
#include "Test_Summary_Service.inl"
#endif

#include "Basic_Test_Summary_Impl.h"
#include "XML_Test_Summary_Impl.h"
#include "ace/Get_Opt.h"
#include "ace/CORBA_macros.h"

CUTS_TESTING_SERVICE_IMPL (CUTS_Test_Summary_Service, _make_CUTS_Test_Summary_Service);

//
// init
//
int CUTS_Test_Summary_Service::init (int argc, char * argv [])
{
  CUTS_TESTING_SUMMARY_TRACE ("CUTS_Test_Summary_Service::init (int, char * [])");

  const char * optstr = "o:";
  ACE_Get_Opt get_opt (argc, argv, optstr);

  get_opt.long_option ("xml-format", ACE_Get_Opt::NO_ARG);

  char opt;

  while ((opt = get_opt ()) != EOF)
  {
    switch (opt)
    {
    case 0:
      if (ACE_OS::strcmp ("xml-format", get_opt.long_option ()) == 0)
      {
        // Let's use the XML format for this summary.
        CUTS_Test_Summary_Impl * impl = 0;

        ACE_NEW_THROW_EX (impl,
                          CUTS_XML_Test_Summary_Impl (),
                          ACE_bad_alloc ());

        this->impl_.reset (impl);
      }

      break;

    case 'o':
      // Set the output file location.
      this->output_ = get_opt.opt_arg ();
      break;
    }
  }

  if (this->impl_.get () == 0)
  {
    // We need to use the default format.
    CUTS_Test_Summary_Impl * impl = 0;

    ACE_NEW_THROW_EX (impl,
                      CUTS_XML_Test_Summary_Impl (),
                      ACE_bad_alloc ());

    this->impl_.reset (impl);
  }

  return 0;
}

//
// handle_shutdown
//
int CUTS_Test_Summary_Service::
handle_shutdown (const ACE_Time_Value & tv)
{
  CUTS_TESTING_SUMMARY_TRACE ("CUTS_Test_Summary_Service::handle_shutdown (const ACE_Time_Value &)");

  if (this->impl_.get () == 0)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T - %M - writer type undefined; aborting...\n"),
                       -1);
  }

  int retval = -1;

  if (this->output_.empty ())
  {
    // Write the summary to STDOUT.
    retval = this->impl_->generate (std::cout, *this->test_app ());
  }
  else
  {
    // Write the summary to the specified location.
    std::ofstream outfile;
    outfile.open (this->output_.c_str ());

    if (outfile.is_open ())
    {
      retval = this->impl_->generate (outfile, *this->test_app ());
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - failed to open %s for writing\n",
                  this->output_.c_str ()));

      retval = -1;
    }
  }

  return retval;
}
