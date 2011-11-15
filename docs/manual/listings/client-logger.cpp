#include "cuts/utils/logging/client/logger/Client_Logger.h"

int main (int argc, char * argv []) {
  try {
    // connect client logger to logging client.
    CUTS_Client_Logger logger;
    if (-1 == logger.connect (argv[1]))
      return 1;

    // Send a single, yet simple message.
    logger.log (LM_DEBUG, "this is a simple message");

    // Disconnect from the logging client.
    logger.disconnect ();
    return 0;
  }
  catch (const ::CORBA::Exception & ex) {  }
  catch (...) {  }

  return 1;
}
