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

package cuts.java.jbi.deployment;

import cuts.java.jbi.client.*;
import cuts.java.ProcessHandler;
import org.apache.log4j.Logger;
import java.util.*;
import java.io.*;
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


  /**
   * Initializing constructor.
   *
   * @param       processGroup        Name of the process group.
   * @param       confiDirectory      Directory containing configurations.
   */
  public NodeApplicationImpl (org.omg.CORBA.ORB orb)
  {
    this.orb_ = orb;

    // Create a callback object and activate it. This is what we will
    // pass to each of the spawn application processes.
    this.processManagerImpl_ = new ApplicationProcessManagerImpl ();
    this.processManagerImpl_._this (this.orb_);
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
    // Start each of the application processes that we spawned.
  }

  /**
   * Install a new instance into the specified process group.
   */
  public void installInstance (String groupName, String instanceName)
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
        // Get the CLASSPATH. We need to pass this along to 
        // the application process.
        String classPath = System.getProperty ("java.class.path");
        String javaOpts = System.getenv ("JAVA_OPTS");

        // Convert the ApplicationProcessManager to a string.
        String processManagerIOR =
          this.orb_.object_to_string (this.processManagerImpl_._this ());

        // Construct the command for spawning a new application process.
        String spawnCommand =
          "java.exe -classpath " + classPath + pathSeparator +
          this.jbiClassPath_ + pathSeparator + this.cutsClassPath_ +
          " -Djava.endorsed.dirs=" +
          this.cutsLibDir + this.pathSeparator + this.cutsContribDir +
          " " + javaOpts +
          " -Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB" +
          " -Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton" +
          " cuts.java.jbi.deployment.JbiClientApp -name " + groupName +
          " -ORBInitRef ProcessManager=" + processManagerIOR;

        // Spawn a new application process.
        this.logger_.debug ("spawning a new application process [" +
                           spawnCommand + "]");

        Process process = Runtime.getRuntime ().exec (spawnCommand);

        if (process != null)
        {
          try
          {
            // First, check if the process has already exited.
            int exitValue = process.exitValue ();

            this.logger_.error ("process already exited [" +
                                exitValue + "]");
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

    // Install the instance into the process group.
    if (appProcess != null)
    {
      appProcess.installClient (instanceName);
    }
    else
    {
      this.logger_.error ("process " + groupName +
                          " has not registered itself");
    }
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
