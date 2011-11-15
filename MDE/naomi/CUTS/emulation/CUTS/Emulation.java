// -*- Java -*-

//=============================================================================
/**
 * @file        Emulation.java
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

package CUTS;

import java.util.*;
import java.util.regex.*;
import java.io.*;
import org.fireant.isislab.*;

/**
 * @class Emulation
 *
 * Run an CUTS emulation is ISISLab.
 */
public class Emulation
{
  /**
   * Default constructor.
   */
  public Emulation ()
  {
    this.exp_.put ("swapin", false);
    this.exp_.put ("description", "CUTS auto-generated experiment for NAOMI");
    this.exp_.put ("batch", true);
  }

  /**
   * Run the emulation.
   *
   * @param[in]         args        Command-line arguments.
   */
  public void run (String [] args)
  {
    // Parse the command-line arguments.
    this.parseArgs (args);

    // First, - the attributes in the model.
    if (this.listAttributes_)
      this.listAttributes ();

    if (this.updateAttributes_)
    {
      // Create the experiment.
      System.out.println ("creating a new emulab experiment");
      ISISLabUtil.createExperiment (this.isislab_, this.exp_);

      // Swapin the experiment.
      if (this.swapin_)
      {
        System.out.println ("swapping in the experiment in batch mode");
        ISISLabUtil.swapinExperiment (this.isislab_, this.exp_);
      }
    }

    // Lastly, generate the interface file for the model.
    this.writeIntefaceFile ();
  }

  /**
   * Generate the interface file for the model.
   */
  private void writeIntefaceFile ()
  {
    try
    {
      // Open the interface file for writing.
      String interfaceFileName = this.interfaceBaseName_ + "_interface.xml";
      System.out.println ("Generating interface file: " + interfaceFileName);

      PrintWriter out = new PrintWriter (new FileWriter (interfaceFileName));

      out.println ("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>");
      out.println ("<interface xmlns=\"http://www.atl.lmco.com/naomi/interfaces\"");
      out.println ("           xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"");
      out.println ("           xsi:schemaLocation=\"http://www.atl.lmco.com/naomi/interfaces interface.xsd\">");
      out.println ("  <name>" + this.owner_ + "</name>");
      out.println ("  <type>CUTS.emulation</type>");
      out.println ();
      out.println ("  <!-- input attributes -->");
      out.println ("  <input>CUTS.deployment</input>");
      out.println ("  <input>CUTS.emulation</input>");
      out.println ();
      out.println ("  <!-- output attributes -->");
      out.println ("  <output>CUTS.test.uuid</output>");
      out.println ("</interface>");

      out.close ();
    }
    catch (Exception e)
    {
      e.printStackTrace ();
    }
  }

  /**
   * List the attributes managed by this connector. This is an 'internal'
   * connector for CUTS, and therefore, it has a predefined set of attributes
   * that it manages.
   */
  private void listAttributes ()
  {
    StringBuffer buffer = new StringBuffer ();

    buffer.append ("Input Attributes:\n");
    buffer.append ("----------------------------------\n");
    buffer.append ("  * CUTS.deployment\n");
    buffer.append ("  * CUTS.emulation\n");
    buffer.append ("\n");
    buffer.append ("Output Attributes:\n");
    buffer.append ("----------------------------------\n");
    buffer.append ("  * CUTS.test.uuid\n");

    System.out.println (buffer.toString ());
  }

  /**
   * Parse the command line arguments for the program.
   *
   * @param[in]         args          Command-line arguments
   */
  private void parseArgs (String [] args)
  {
    for (int i = 0; i < args.length; ++ i)
    {
      String arg = args[i];

      if (arg.equals ("-username"))
      {
        this.isislab_.put ("user", args[++ i]);
      }
      else if (arg.equals ("-password"))
      {
        this.isislab_.put ("pass", args[++ i]);
      }
      else if (arg.equals ("-url"))
      {
        this.isislab_.put ("url", args[++ i]);
      }
      else if (arg.equals ("-project"))
      {
        this.exp_.put ("project", args[++ i]);
      }
      else if (arg.equals ("-experiment"))
      {
        this.exp_.put ("name", args[++ i]);
      }
      else if (arg.equals ("-nsfile"))
      {
        this.exp_.put ("nsfile", args[++ i]);
      }
      else if (arg.equals ("-swapin"))
      {
        this.exp_.put ("swapin", true);
      }
      else if (arg.equals ("-update-attributes"))
      {
        this.updateAttributes_ = true;
      }
      else if (arg.equals ("-list-attributes"))
      {
        this.listAttributes_ = true;
      }
      else if (arg.equals ("-attribute-path"))
      {
        this.attributePath_ = args [++i];
      }
      else if (arg.equals ("-interface-basename"))
      {
        this.interfaceBaseName_ = args [++i];
      }
      else if (arg.equals ("-owner"))
      {
        this.owner_ = args [++i];
      }
    }
  }

  /// Username for running the experiment.
  private HashMap exp_ = new HashMap ();

  /// Password for running the experiment.
  private HashMap isislab_ = new HashMap ();

  /// Swapin the experiment.
  private boolean swapin_ = false;

  /// List the attributes managed by this connector.
  private boolean listAttributes_ = false;

  private boolean updateAttributes_ = false;

  private String attributePath_;

  private String interfaceBaseName_;

  private String owner_;

  private UUID testUUID_ = null;

  /////////////////////////////////////////////////////////////////////////////
  // entry point

  public static void main (String [] args)
  {
    try
    {
      // Create a new emulation object.
      Emulation exp = new Emulation ();

      // Run the emulation.
      exp.run (args);
    }
    catch (Exception e)
    {
      e.printStackTrace ();
    }
  }
}
