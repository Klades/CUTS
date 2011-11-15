// -*- java -*-

//=============================================================================
/**
 * @file          NodeApplicationImpl.java
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

package cuts.jbi.deployment;
import CUTS.ProcessHandler;
import cuts.jbi.client.*;
import org.apache.log4j.Logger;
import java.io.*;
import java.util.*;
import java.util.concurrent.TimeUnit;

/**
 * @class NodeApplicationImpl
 *
 * Implementation of the NodeApplication interface.
 */
public class NodeApplicationImpl
  extends NodeApplicationPOA
{
  /// The ORB for this node application.
  private org.omg.CORBA.ORB orb_ = null;

  /// The location of the configuration. This can be a relative
  /// location, or an absolute location. In the case of an absolute
  /// location, the directory must be prefixed with file:
  private String configPath_ = ".";

  private final Logger logger_ =
    Logger.getLogger (NodeApplicationImpl.class);

  private ApplicationProcessManagerImpl processManagerImpl_ = null;

  private final String pathSeparator = System.getProperty ("path.separator");

  private final String fileSeparator = System.getProperty ("file.separator");

  private final String cutsLibDir =
    System.getenv ("CUTS_ROOT") + fileSeparator + "lib" + fileSeparator;

  private final String cutsContribDir =
    System.getenv ("CUTS_ROOT") + fileSeparator + "contrib" +
    fileSeparator + "java" + fileSeparator;

  private final String jbiLibDir =
    System.getenv ("JBI_ROOT") + fileSeparator +
    "lib" + fileSeparator;

  // we're now setting these in the constructor according to the jar files in the
  // respective directories --James Edmondson
  private String jbiClassPath_;
  private String cutsClassPath_;

  /* Commented out (January 20, 2009) to address Matt Gillen's comments on QED list
   * I'm leaving this here just in case someone needs this for some reason. I set
   * -- James Edmondson
   *
  private final String jbiClassPath_ =
    jbiLibDir + "capi1.5.jar" + pathSeparator +
    jbiLibDir + "dom4j-1.6.1.jar" + pathSeparator +
    jbiLibDir + "jaxen-1.1.1.jar" + pathSeparator +
    jbiLibDir + "jbossall-client.jar" + pathSeparator +
    jbiLibDir + "xpp3_xpath-1.1.4c.jar" + pathSeparator +
    jbiLibDir + "xpp3-1.1.4c.jar";

  private final String cutsClassPath_ =
    cutsLibDir + "cuts.java.jar" + pathSeparator +
    cutsLibDir + "cuts.java.jbi.jar" + pathSeparator +
    cutsLibDir + "cuts.java.jbi.deployment.jar" + pathSeparator +
    cutsContribDir + "jacorb.jar" + pathSeparator +
    cutsContribDir + "spring.jar" + pathSeparator +
    cutsContribDir + "log4j-1.2.15.jar" + pathSeparator +
    cutsContribDir + "commons-logging-1.1.1.jar" + pathSeparator +
    cutsContribDir + "castor-1.2.jar";
  */

  /**
   * Initializing constructor.
   *
   * @param       processGroup        Name of the process group.
   * @param       confiDirectory      Directory containing configurations.
   */
  public NodeApplicationImpl (org.omg.CORBA.ORB orb)
  {
    this.orb_ = orb;

    jbiClassPath_ = directoryJarsToPath(jbiLibDir);
    cutsClassPath_ = directoryJarsToPath(cutsLibDir) + File.pathSeparator +
      directoryJarsToPath(cutsContribDir);

    // Create a callback object and activate it. This is what we will
    // pass to each of the spawn application processes.
    this.processManagerImpl_ = new ApplicationProcessManagerImpl ();
    this.processManagerImpl_._this (this.orb_);
  }

  /**
   * Reads a directory, filtering for only jar files, and returns a
   * string, File.pathSeparator delimited, to the caller. If this can
   * be used elsewhere also, we may want to move this to a separate file
   *
   * @param[in]       dirString        directory to open and read files from
   * @return          string that may be set to a path after the function call
   */

  public static String directoryJarsToPath(String dirString)
  {
    StringBuffer path = new StringBuffer ();

    // open the directory
    File dir = new File (dirString);

    // create an anonymous FileFilter for jar files in the directory
    File [] jars = dir.listFiles (new FileFilter ()
      {
        @Override
        public boolean accept (File pathname)
          {
            return pathname.getName ().endsWith (".jar");
          }
      });

    // iterate through the jars and add them to the local string path
    for (File jar : jars)
      {
        path.append (jar.getAbsolutePath ());
        path.append (File.pathSeparator);
      }

    // return the new path
    return path.toString ();
  }

  public void finishLaunch ()
  {
    // Do nothing!!
  }

  /**
   * Start the node application. This will activate all the clients
   * in each of the process.
   */
  public void start ()
  {
      this.processManagerImpl_.start ();
  }

  /**
   * Install a new instance into the specified process group.
   */
  public boolean installInstance (String groupName, String instanceName)
  {
    // Get the application process for the group.
    this.logger_.debug ("installing client [" + instanceName +
                       "] in process [" + groupName + "]");

    ApplicationProcess appProcess =
      this.processManagerImpl_.getProcess (groupName);

    if (appProcess == null)
    {
      try
      {
        // Convert the ApplicationProcessManager to a string.
        String processManagerIOR =
          this.orb_.object_to_string (this.processManagerImpl_._this ());

        String endorsedDirs =
          this.cutsLibDir + this.pathSeparator + this.cutsContribDir;

        // Create the spawn command for the new process.
        ArrayList<String> spawnCmd = new ArrayList<String> ();

        spawnCmd.add ("java");

        // Pass over the JAVA_OPTS from the node manager. We need to
        // make sure each of the spawned processes.
        String javaOpts = System.getenv ("JAVA_OPTS");

        if (javaOpts != null)
        {
          String [] optsList = javaOpts.split ("\\p{Space}");
          for (String javaOpt : optsList)
            spawnCmd.add (javaOpt);
        }

        // Set the classpath for the application process.
        String classPath = System.getProperty ("java.class.path");
        spawnCmd.add ("-classpath");
        spawnCmd.add (this.cutsClassPath_ + this.pathSeparator +
                      this.jbiClassPath_ + this.pathSeparator +
                      classPath);

        // Setup the java app and its command-line parameters.
        spawnCmd.add ("cuts.java.jbi.deployment.JbiClientApp");
        spawnCmd.add ("-name");
        spawnCmd.add (groupName);
        spawnCmd.add ("-ORBInitRef");
        spawnCmd.add ("ProcessManager=" + processManagerIOR);

        // Construct the process for the spawned application.
        ProcessBuilder processBuilder = new ProcessBuilder (spawnCmd);

        // Set the working directory for the spawned application.
        processBuilder.directory (new File (System.getProperty ("user.dir")));

        // Spawn a new application process.
        this.logger_.debug ("spawning a new application process");
        Process process = processBuilder.start ();

        if (process != null)
        {
          try
          {
            // First, check if the process has already exited.
            int exitValue = process.exitValue ();

            this.logger_.error ("process already exited [" + exitValue + "]");
          }
          catch (IllegalThreadStateException ex)
          {
            // Create a new process handler for this process.
            this.logger_.debug ("creating a new process handler for the process");
            ProcessHandler processHandler = new ProcessHandler (process);

            // Start the process handler.
            this.logger_.debug ("activating the process handler");
            processHandler.start ();

            // Wait for the process to register itself.
            this.logger_.debug ("waiting for application process to register itself");

            if (this.processManagerImpl_.
                  waitForProcessRegistered (10, TimeUnit.SECONDS))
            {
              this.logger_.debug ("associating process handler with application process");
              this.processManagerImpl_.setProcess (groupName, processHandler);

              // Get the process from the process manager.
              this.logger_.debug ("getting newly registered application process");
              appProcess = this.processManagerImpl_.getProcess (groupName);
            }
            else
            {
              this.logger_.error ("application process failed to register itself");
            }
          }
        }
        else
        {
          this.logger_.error ("failed to spawn process " + groupName);
        }
      }
      catch (Exception ex)
      {
        this.logger_.error ("failed to spawn application process", ex);
      }
    }

    // Install the client into its process.
    if (appProcess != null)
      return appProcess.installClient (instanceName);

    this.logger_.error ("process " + groupName + " not registered");
    return false;
  }

  /**
   * Destroy the application. This should remove all the installed
   * instances and destroy all the spawned processes.
   */
  public void destroy ()
  {
    this.logger_.debug ("shutting down the application process manager");
    this.processManagerImpl_.shutdown ();
  }
}
