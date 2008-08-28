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

    // Generate a UUID for the experiment.

    // Update the UUID in the experiment file.

    // Create the experiment.
    ISISLabUtil.createExperiment (this.isislab_, this.exp_);

    // Swapin the experiment.
    if (this.swapin_)
      ISISLabUtil.swapinExperiment (this.isislab_, this.exp_);

    // Write the UUID to the CUTS.test.uuid attribute file.
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

      if (arg.equals ("--username"))
      {
        this.isislab_.put ("user", args[++ i]);
      }
      else if (arg.equals ("--password"))
      {
        this.isislab_.put ("pass", args[++ i]);
      }
      else if (arg.equals ("--url"))
      {
        this.isislab_.put ("url", args[++ i]);
      }
      else if (arg.equals ("--project"))
      {
        this.exp_.put ("project", args[++ i]);
      }
      else if (arg.equals ("--experiment"))
      {
        this.exp_.put ("name", args[++ i]);
      }
      else if (arg.equals ("--description"))
      {
        this.exp_.put ("description", args[++ i]);
      }
      else if (arg.equals ("--nsfile"))
      {
        this.exp_.put ("nsfile", args[++ i]);
      }
      else if (arg.equals ("--swapin"))
      {
        this.exp_.put ("swapin", true);
      }
    }
  }

  /// Username for running the experiment.
  private HashMap exp_ = new HashMap ();

  /// Password for running the experiment.
  private HashMap isislab_ = new HashMap ();

  /// Swapin the experiment.
  private boolean swapin_ = false;

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
