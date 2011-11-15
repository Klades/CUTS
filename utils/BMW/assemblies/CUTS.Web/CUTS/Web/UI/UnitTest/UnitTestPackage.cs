// -*- C# -*-

//=============================================================================
/**
 * @file        UnitTestPackage.cs
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using CUTS.Data.UnitTesting;
using MySql.Data.MySqlClient;

namespace CUTS.Web.UI.UnitTest
{
  /**
   * @class TestPackage
   *
   * Custom control for displaying the results of a test package. The
   * test package has a collection of unit test, which contain the actual
   * results.
   */
  [ParseChildren (true),
   PersistChildren (false)]
  public class UnitTestPackage : CompositeControl, INamingContainer
  {
    /**
     * Default constructor.
     */
    public UnitTestPackage ()
    {

    }

    /**
     * Clear all the unit test from the test package.
     */
    public void Clear ()
    {
      // Clear the unit tests.
      this.tests_.Clear ();

      // Clear the controls for the unit test.
      Table table = (Table)this.Controls[1];
      table.Rows.Clear ();

      this.unittest_count_ = 0;
    }

    /**
     * Insert a new unit test result into the package.
     */
    public void Add (UnitTest test)
    {
      this.EnsureChildControls ();

      // Get the table that contains the unit test.
      Table table = (Table)this.Controls[1];
      table.Rows.Add (test);

      test.Evaluate += new EventHandler (this.handle_evaluate);
      test.Chart += new EventHandler (this.handle_chart);

      // Insert the unit test into the collection and control.
      this.tests_.Add (test);
      ++ this.unittest_count_;
    }

    #region Attributes
    /// Setter/getter attributes the package's test name.
    public string Name
    {
      get
      {
        return this.name_;
      }

      set
      {
        // Make sure the child controls exist.
        this.EnsureChildControls ();

        // Update the label of the control.
        Label title = (Label)this.Controls[0];
        title.Text = String.Format ("{0} Package", value);

        // Save the name of the package.
        this.name_ = value;
      }
    }

    public UnitTests UnitTests
    {
      get
      {
        return this.tests_;
      }
    }
    #endregion

    #region Framework Methods
    protected override void LoadViewState (object savedState)
    {
      object[] state = (object[])savedState;

      if (state[0] != null)
        base.LoadViewState (state[0]);

      if (state[1] != null)
        this.name_ = (string)state[1];

      if (state[2] != null)
        this.unittest_count_ = (int)state[2];
    }

    protected override object SaveViewState ()
    {
      object[] state = new object[3];

      state[0] = base.SaveViewState ();
      state[1] = this.name_;
      state[2] = this.unittest_count_;

      return state;
    }

    protected override void CreateChildControls ()
    {
      base.CreateChildControls ();

      // First, create the header for the package.
      Label title = new Label ();
      this.Controls.Add (title);

      title.CssClass = "title";

      // Next, create the table that will host the unit test results.
      Table table = new Table ();
      this.Controls.Add (table);

      table.Width = new Unit (80, UnitType.Percentage);

      // Create the correct number of unit tests.
      for (int i = 0; i < this.unittest_count_; ++i)
      {
        UnitTest test = new UnitTest ();
        table.Rows.Add (test);

        test.Evaluate += new EventHandler (this.handle_evaluate);
        test.Chart += new EventHandler (this.handle_chart);
      }
    }

    public event CommandEventHandler EvaluateUnitTest;
    public event CommandEventHandler ChartUnitTest;

    private void handle_evaluate (object sender, EventArgs e)
    {
      if (this.EvaluateUnitTest != null)
        this.EvaluateUnitTest (this, new CommandEventArgs ("evaluate", sender));
    }

    private void handle_chart (object sender, EventArgs e)
    {
      if (this.ChartUnitTest != null)
        this.ChartUnitTest (this, new CommandEventArgs ("chart", sender));
    }
    #endregion

    #region Member Variables
    /// Name of the unit test package.
    private string name_;

    /// Number unit test in the package.
    private int unittest_count_;

    /// The collection of unit test in the package.
    private UnitTests tests_ = new UnitTests ();
    #endregion
  }
}
