//-*- java -*-

//=============================================================================
/**
 * @file        Logger.java
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

package CUTS.client;
import java.util.ArrayList;
import java.util.Properties;

/**
 * @class TestManagerClient
 */
public class TestManagerClient
{
  /**
   * Default constructor.
   */
  public TestManagerClient ()
  {
    final String CUTS_ROOT = System.getenv ("CUTS_ROOT");
    final String pathSeparator = System.getProperty ("file.seperator");

    ArrayList<String> args = new ArrayList ();
    args.add ("-Djava.endorsed.dirs=" + CUTS_ROOT + pathSeparator + "contrib" + pathSeparator + "java");
    args.add ("-Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB");
    args.add ("-Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton");

    // Initalize the CORBA ORB.
    this.orb_ = org.omg.CORBA.ORB.init (args.toArray (new String [0]), null);
  }

  /**
   * Initializing constructor.
   *
   * @param[in]       orb           ORB used by object for requests.
   */
  public TestManagerClient (org.omg.CORBA.ORB orb)
  {
    this.orb_ = orb;
  }

  /**
   * Connect to the local logging client. The location provided to
   * this function is must be valid input for string_to_object ().
   * Examples of valid locations are: corbaloc, corbaname, and IORs.
   *
   * @param[in]       location      Location of the logging client
   */
  public void connect (String location)
  {
    org.omg.CORBA.Object obj = this.orb_.string_to_object (location);
    this.testManager_ = CUTS.TestManagerHelper.narrow (obj);
  }

  /**
   * Get the contained test manager. This object is only valid after
   * the connect () method has been called first.
   */
  public CUTS.TestManager getTestManager ()
  {
    return this.testManager_;
  }

  /// ORB used by the logger to communicate with outside world.
  private org.omg.CORBA.ORB orb_ = null;

  /// Local logging client object.
  private CUTS.TestManager testManager_ = null;
}
