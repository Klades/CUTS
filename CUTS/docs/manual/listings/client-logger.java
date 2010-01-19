import CUTS.client.logging.Logger;

public class TestApplication {
  public static void main (String [] args) {
    String loggingClientLoc = /* location of logging client */
    Logger clientLogger = new Logger ();

    // connect to the logging client
    clientLogger.connect (loggingClientLoc);

    // send a log message
    clientLogger.log ("this is a simple message");

    // disconnect from the logging client
    clientLogger.disconnect ();
  }
}