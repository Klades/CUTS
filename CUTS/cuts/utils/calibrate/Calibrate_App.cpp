// $Id$

#include "Calibrate_App.h"

#if !defined (__CUTS_INLINE__)
#include "Calibrate_App.inl"
#endif

#include "Calibrate_Options.h"
#include "cuts/Worker.h"
#include "cuts/Auto_Functor_T.h"
#include "ace/DLL.h"
#include "ace/Get_Opt.h"

//
// run_main
//
int CUTS_Calibrate_App::run_main (int argc, char * argv [])
{
  if (-1 == this->parse_args (argc, argv))
    return 1;

  ACE_DLL test_dll;

  ACE_DEBUG ((LM_INFO,
              "%T (%t) - %M - opening %s for calibration\n",
              this->opts_.worker_library_.c_str ()));

  if (-1 == test_dll.open (this->opts_.worker_library_.c_str ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T - %M - failed to open %s [%m]\n",
                       this->opts_.worker_library_.c_str ()),
                       1);

  // Load the export symbol that will allow use to create the worker
  // to be calibrated.
  ACE_DEBUG ((LM_INFO,
              "%T (%t) - %M - extracting worker object from library\n"));

  void * symbol = test_dll.symbol (CUTS_WORKER_FACTORY_SYMBOL_NAME);

  if (0 == symbol)
    ACE_ERROR_RETURN ((LM_ERROR,
                        "%T (%t) - %M - failed to load symbol '%s'\n",
                        CUTS_WORKER_FACTORY_SYMBOL_NAME),
                        1);

  typedef CUTS_Worker * (* CUTS_WORKER_EXPORT_SYMBOL) (void);
  CUTS_WORKER_EXPORT_SYMBOL worker_factory = (CUTS_WORKER_EXPORT_SYMBOL) symbol;
  CUTS_Worker * worker = worker_factory ();

  if (0 == worker)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T - %M - failed to create worker object\n"),
                       1);

  CUTS_Auto_Functor_T <CUTS_Worker> auto_clean (worker, &CUTS_Worker::release);

  // Invoke the calibration method.
  bool retval = worker->calibrate ();

  ACE_DEBUG ((LM_DEBUG,
              "%T - %M - calibration %s...\n",
              (retval ? "succeeded" : "failed")));

  return 0;
}

//
// parse_args
//
int CUTS_Calibrate_App::parse_args (int argc, char * argv [])
{
  const char * opts = ACE_TEXT ("vf:");
  ACE_Get_Opt get_opt (argc, argv, opts, 1);

  int option;

  while ((option = get_opt ()) != EOF)
  {
    switch (option)
    {
    case 'f':
      this->opts_.worker_library_ = get_opt.opt_arg ();
      break;

    case '?':
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - -%c is an unknown option\n",
                  get_opt.opt_opt ()));
      break;

    case ':':
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - -%c is missing an argument\n",
                         get_opt.opt_opt ()),
                         -1);
      break;
    }
  }

  return 0;
}
