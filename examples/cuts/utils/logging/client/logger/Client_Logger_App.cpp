// $Id$

#include "cuts/utils/logging/client/logger/Client_Logger.h"

//
// ACE_TMAIN
//
int ACE_TMAIN (int argc, char * argv [])
{
  try
  {
    if (1 == argc)
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - missing command-line arguments\n")),
                         1);

    // Connect the logger to the logging client.
    CUTS_Client_Logger logger;
    if (-1 == logger.connect (argv[1]))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - client logger failed to connect\n")),
                         -1);

    // Send a single, yet simple message.
    if (-1 == logger.log (LM_DEBUG, "this is a simple message"))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to log message\n")),
                         -1);


    // Disconnect from the logging client.
    if (-1 == logger.disconnect ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - client logger failed to disconnect\n")),
                         -1);

    return 0;
  }
  catch (const ::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception\n")));
  }

  return 1;
}
