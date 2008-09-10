// -*- java -*-

package CUTS.jbi.deployment;

import org.omg.CosNaming.*;

import org.apache.log4j.Logger;
import org.apache.log4j.BasicConfigurator;

import org.exolab.castor.mapping.*;
import org.exolab.castor.mapping.xml.*;
import org.exolab.castor.xml.Unmarshaller;
import org.exolab.castor.xml.MarshalException;
import org.exolab.castor.xml.ValidationException;

import org.apache.xerces.parsers.DOMParser;
import org.w3c.dom.*;
import org.xml.sax.InputSource;
import org.xml.sax.EntityResolver;

import java.util.Properties;
import java.util.ArrayList;
import java.io.*;

/**
 * @class JbiPlanLauncher
 */
public class JbiPlanLauncher
{
  private class DeploymentPlanInfo
  {
    public String domainApp_;

    public String domainAppManager_;

    public String executionManager_;
  }

  private org.omg.CORBA.ORB orb_ = null;

  private final Logger logger_ = Logger.getLogger (JbiPlanLauncher.class);

  private static final String fileSeparator_ =
    System.getProperty ("file.separator");

  private static String defaultPropsFilename_ =
    System.getenv ("CUTS_ROOT") +
    JbiPlanLauncher.fileSeparator_ + "etc" +
    JbiPlanLauncher.fileSeparator_ + "plans.properties";

  private final Properties planProperties_ = new Properties ();

  private String teardownPlan_ = null;

  private String deployPlan_ = null;

  private final String mappingFile_ = "cuts/java/jbi/deployment/mapping.xml";

  private class MyResolver implements EntityResolver
  {
    public InputSource resolveEntity (String publicId, String systemId)
    {
      final String schemaLoc =
        System.getenv ("CUTS_ROOT") + JbiPlanLauncher.fileSeparator_ +
        "etc" + JbiPlanLauncher.fileSeparator_ +
        "schemas" + JbiPlanLauncher.fileSeparator_ +
        "jbi" + JbiPlanLauncher.fileSeparator_ + "deployment.xsd";

      try
      {
        // Return the input source to the parser.
        FileReader reader = new FileReader (schemaLoc);
        return new InputSource (reader);
      }
      catch (Exception ex)
      {
        ex.printStackTrace ();
      }

      return null;
    }
  }

  /**
   * Initializing constructor.
   */
  public JbiPlanLauncher (org.omg.CORBA.ORB orb)
  {
    this.orb_ = orb;
  }

  /**
   * Main entry point for the class.
   */
  public void run (String [] args)
  {
    try
    {
      // Parse the command-line arguments.
      this.parseArgs (args);

      try
      {
        // Load the current properties file.
        FileInputStream propertyFile =
          new FileInputStream (new File (this.defaultPropsFilename_));

        this.planProperties_.load (propertyFile);
      }
      catch (FileNotFoundException ex)
      {

      }

      // First, teardown the specified deployment plan (if applicable).
      if (this.teardownPlan_ != null)
        this.teardownPlan ();

      // Next, deploy the specified deployment plan (if applicable).
      if (this.deployPlan_ != null)
        this.deployPlan ();
    }
    catch (Exception ex)
    {
      this.logger_.error (ex.getMessage (), ex);
    }
    finally
    {
      try
      {
        // Save the current state of the properties.
        FileOutputStream propertyFile =
          new FileOutputStream (new File (this.defaultPropsFilename_));

        this.planProperties_.store (propertyFile, "Deployment plans managed by the plan launcher");
      }
      catch (Exception ex)
      {
        this.logger_.error (ex.getMessage (), ex);
      }
    }
  }

  /**
   * Parse the command-line arguments.
   */
  private void parseArgs (String [] args)
  {
    for (int i = 0; i < args.length; ++i)
    {
      String arg = args [i];

      if (arg.equals ("-deploy"))
        this.deployPlan_ = args [++i];
      else if (arg.equals ("-teardown"))
        this.teardownPlan_ = args [++i];
    }
  }

  /**
   * Deploy the specified deployment plan.
   */
  private void deployPlan ()
  {
    try
    {
      // Manually parse the plan since I can't get Castor to perform
      // the correct mapping!!
      DeploymentPlan plan = this.manualParsePlan ();

      // Load the mapping file for the deployment plan.
      //this.logger_.debug ("loading mapping file for deployment from " + this.mappingFile_);

      //Mapping mapping = new Mapping ();
      //mapping.loadMapping (getClass ().getClassLoader ().getResource (this.mappingFile_));

      //MappingRoot mapRoot = mapping.getRoot ();
      //this.logger_.debug ("class count = " + mapRoot.getClassMappingCount ());

      // Initialize the unmashaller.
      //this.logger_.debug ("creating unmarshaller for deployment plan");
      //Unmarshaller unmarshaller = new Unmarshaller ();
      //unmarshaller.setValidation (false);
      //unmarshaller.setMapping (mapping);

      // Read the deployment plan.
      //this.logger_.debug ("reading deployment plan " + this.deployPlan_);
      //FileReader reader = new FileReader (this.deployPlan_);
      //DeploymentPlan plan = (DeploymentPlan)unmarshaller.unmarshal (reader);

      System.err.println (plan.UUID);

      // Request a reference to the naming service.
      this.logger_.debug ("locating naming service");
      NamingContextExt rootContext =
        NamingContextExtHelper.narrow (
        this.orb_.string_to_object (
        System.getProperty ("ORBInitRef.NameService")));

      this.logger_.debug ("resolving location of execution manager");
      ExecutionManager em =
        ExecutionManagerHelper.narrow (
        rootContext.resolve (
        rootContext.to_name ("ExecutionManager.JBI")));

      // Prepare the plan for deployment. This will return the domain application
      // manager for the deployment plan.
      this.logger_.debug ("sending deployment plan " + this.deployPlan_ +
                          " to execution manager");
      DomainApplicationManager dam = em.preparePlan (plan);

      // Start launching the deployment plan, which will return to us the domain
      // application for the deployment plan.
      DomainApplication domainApp =
        DomainApplicationHelper.narrow (dam.startLaunch ());

      // Finish the launch process of the domain application.
      domainApp.finishLaunch ();

      // Start the domain application (i.e., the deployment).
      domainApp.start ();

      // Convert the deployment information into strings.
      DeploymentPlanInfo info = new DeploymentPlanInfo ();
      info.domainApp_ = this.orb_.object_to_string (domainApp);
      info.domainAppManager_ = this.orb_.object_to_string (dam);
      info.executionManager_ = this.orb_.object_to_string (em);

      // Save the domain application manager and the execution manager to
      // the properties file.
      this.savePlanProperties (plan.UUID, info);
    }
    catch (Exception ex)
    {
      this.logger_.error (ex.getMessage (), ex);
    }
  }

  /**
   * Teardown the specified deployment plan.
   */
  private void teardownPlan ()
  {
    try
    {
      // Get the execution manager and domain application manager
      // for the specified plan.
      DeploymentPlanInfo info = new DeploymentPlanInfo ();

      if (this.loadPlanProperties (this.teardownPlan_, info))
      {
        // Get all the approriate objects from the deployment plan's
        // information.
        DomainApplication domainApp =
          DomainApplicationHelper.narrow (
          this.orb_.string_to_object (info.domainApp_));

        DomainApplicationManager dam =
          DomainApplicationManagerHelper.narrow (
          this.orb_.string_to_object (info.domainAppManager_));

        ExecutionManager em =
          ExecutionManagerHelper.narrow (
          this.orb_.string_to_object (info.executionManager_));

        // First, destroy the domain application.
        dam.destroyApplication (domainApp);

        // Then, destroy the domain application manager.
        em.destroyManager (dam);

        // Remove the deployment plan's information from the properties.
        this.removePlanProperties (this.teardownPlan_);
      }
    }
    catch (Exception ex)
    {
      this.logger_.error (ex.getMessage (), ex);
    }
  }

  /**
   * Save the plan's information to the properties file.
   */
  private boolean savePlanProperties (String uuid,
                                      DeploymentPlanInfo info)
  {
    this.planProperties_.setProperty (
      this.getExecutionManagerPropName (uuid), info.executionManager_);

    this.planProperties_.setProperty (
      this.getDomainAppManagerPropName (uuid), info.domainAppManager_);

    this.planProperties_.setProperty (
      this.getDomainAppPropName (uuid), info.domainApp_);

    return true;
  }

  /**
   * Load the plan's information from the properties file.
   */
  private boolean loadPlanProperties (String uuid,
                                      final DeploymentPlanInfo info)
  {
    info.domainApp_ =
      this.planProperties_.getProperty (
      this.getDomainAppPropName (uuid));

    if (info.domainApp_ == null)
      return false;

    info.executionManager_ =
      this.planProperties_.getProperty (
      this.getExecutionManagerPropName (uuid));

    if (info.executionManager_ == null)
      return false;

    info.domainAppManager_ =
      this.planProperties_.getProperty (
      this.getDomainAppManagerPropName (uuid));

    if (info.domainAppManager_ == null)
      return false;

    return true;
  }

  /**
   * Remove a plan's information from the properties file.
   */
  private void removePlanProperties (String uuid)
  {
    this.planProperties_.remove (this.getExecutionManagerPropName (uuid));
    this.planProperties_.remove (this.getDomainAppManagerPropName (uuid));
    this.planProperties_.remove (this.getDomainAppPropName (uuid));
  }

  private String getExecutionManagerPropName (String uuid)
  {
    return this.getBasePropName (uuid) + ".ExecutionManager";
  }

  private String getDomainAppManagerPropName (String uuid)
  {
    return this.getBasePropName (uuid) + ".DomainApplicationManager";
  }

  private String getDomainAppPropName (String uuid)
  {
    return this.getBasePropName (uuid) + ".DomainApplication";
  }

  private String getBasePropName (String uuid)
  {
    return "plan." + uuid;
  }

  /**
   * Manually load a deployment plan using Xerces-J
   */
  private DeploymentPlan manualParsePlan ()
    throws org.xml.sax.SAXException, java.io.IOException,
           java.lang.Exception
  {
    // Configure the parser.
    DOMParser parser = new DOMParser ();
    parser.setEntityResolver (new MyResolver ());
    parser.setFeature ("http://xml.org/sax/features/validation", true);
    parser.setFeature ("http://apache.org/xml/features/validation/schema", true);
    parser.setFeature ("http://xml.org/sax/features/namespaces", true);

    // Load the XML document into memory.
    this.logger_.debug ("manually parsing deployment plan " + this.deployPlan_);
    parser.parse (this.deployPlan_);

    // Get the root node for the document.
    DeploymentPlan plan = new DeploymentPlan ();
    Document document = parser.getDocument ();
    Element rootElement = document.getDocumentElement ();

    // Get the UUID of the deployment plan.
    NodeList uuidNodes = rootElement.getElementsByTagName ("UUID");
    Element uuidElement = (Element)uuidNodes.item (0);
    plan.UUID = uuidElement.getChildNodes ().item (0).getNodeValue ();

    // Get the instances of the deployment plan.
    NodeList instanceNodes = rootElement.getElementsByTagName ("instance");

    ArrayList<ComponentInstanceDescriptor> instances =
      new ArrayList<ComponentInstanceDescriptor> (instanceNodes.getLength ());

    for (int i = 0; i < instanceNodes.getLength (); ++i)
    {
      // Get the next instance element in the document.
      Element instanceElement = (Element)instanceNodes.item (i);

      // Get the id of the instance.
      String id = instanceElement.getAttribute ("id");

      // Get the child nodes of this instance.
      NodeList info = instanceElement.getChildNodes ();

      // Get the location of the instance.
      Element locationElement = (Element) info.item (1);
      Element processElement = (Element) info.item (3);

      // Create a new component instance descriptor and save it.
      ComponentInstanceDescriptor cid =
        new ComponentInstanceDescriptor (id,
        locationElement.getChildNodes ().item (0).getNodeValue (),
        processElement.getChildNodes ().item (0).getNodeValue ());

      instances.add (cid);
    }

    // Add the component instance descriptors to the deployment plan.
    plan.componentInstances =
      instances.toArray (new ComponentInstanceDescriptor [0]);

    return plan;
  }

  /**
   * Main entry point for the application.
   */
  public static void main (String [] args)
  {
    // Set up a simple configuration that logs on the console.
    BasicConfigurator.configure ();

    // Get the ExecutionManager logger.
    Logger logger = Logger.getLogger (JbiPlanLauncher.class);
    org.omg.CORBA.ORB orb = null;

    try
    {
      // Initialize the CORBA ORB.
      orb = org.omg.CORBA.ORB.init (args, null);

      // Create a new plan launcher object.
      JbiPlanLauncher jbiPlanLauncher = new JbiPlanLauncher (orb);

      // Run the plan launcher.
      jbiPlanLauncher.run (args);
    }
    catch (Exception ex)
    {
      logger.error (ex.getMessage (), ex);
    }
    finally
    {
      // Destroy the ORB, if applicable.
      if (orb != null)
        orb.destroy ();
    }
  }
}
