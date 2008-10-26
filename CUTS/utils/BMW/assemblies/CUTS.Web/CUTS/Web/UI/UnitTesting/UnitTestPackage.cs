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

namespace CUTS.Web.UI.UnitTesting
{
  /**
   * @class TestPackage
   *
   * Custom control for displaying the results of a test package. The
   * test package has a collection of unit test, which contain the actual
   * results.
   */
  public class UnitTestPackage : CompositeControl, INamingContainer
  {
    /**
     * Default constructor.
     */
    public UnitTestPackage ()
    {

    }

    /**
     * Initializing constructor.
     */
    public UnitTestPackage (UnitTestSuite suite)
    {
      this.suite_ = suite;
    }

    /**
     * Evaluate all the unit test in this test package.
     */
    public void EvaluateAll ()
    {
      try
      {
        // Open the evaluator for usage.
        this.suite_.Evaluator.Open ();

        // Evaluate each of the unit test in the test package.
        foreach (UnitTest ut in this.unit_tests_)
        {
          ut.Result =
            this.suite_.Evaluator.Reevaluate (this.suite_.TestNumber, ut.ID, true);
        }
      }
      finally
      {
        // Close the evaluator connection.
        this.suite_.Evaluator.Close ();
      }
    }

    /**
     * Clear all the unit test from the test package.
     */
    public void Clear ()
    {
      this.unit_tests_.Clear ();
    }

    /**
     * Insert a new unit test result into the package.
     */
    public void Add (UnitTest ut)
    {
      this.EnsureChildControls ();

      // Get the table that contains the unit test.
      Table table = (Table)this.Controls[1];

      // Insert the unit test into the collection and control.
      this.unit_tests_.Add (ut);
      this.create_unit_test (table, ut, false);
    }

    #region Attributes
    /**
     * Setter/getter attributes the package's test name.
     */
    [NotifyParentProperty (true)]
    public string Name
    {
      get
      {
        return this.name_;
      }

      set
      {
        this.EnsureChildControls ();

        Label label = (Label)this.Controls[0];
        label.Text = String.Format ("<div>{0} Package</div>", value);

        this.name_ = value;
      }
    }

    /**
     * Attribute for setting/gettng the unit test in the
     * test package.
     */
    [ MergableProperty (false),
      PersistenceMode (PersistenceMode.InnerProperty),
      NotifyParentProperty (true)]
    public UnitTests UnitTests
    {
      get
      {
        return this.unit_tests_;
      }

      set
      {
        // Create a temporary table for the unit test.
        Table table = new Table ();
        table.Width = new Unit (80, UnitType.Percentage);

        // Build up the table.
        foreach (UnitTest test in value)
          this.create_unit_test (table, test, false);

        // Save the unit test information.
        this.Controls.RemoveAt (1);
        this.Controls.AddAt (1, table);

        this.unit_tests_ = value;
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
        this.unit_tests_ = (UnitTests)state[2];
    }

    protected override object SaveViewState ()
    {
      object[] state = new object[3];

      state[0] = base.SaveViewState ();
      state[1] = this.name_;
      state[2] = this.unit_tests_;

      return state;
    }

    protected override void CreateChildControls ()
    {
      // First, create the header for the package.
      Label header = new Label ();
      this.Controls.Add (header);

      header.CssClass = "title";

      // Next, create the table that will host the unit test results.
      Table table = new Table ();
      this.Controls.Add (table);

      table.Width = new Unit (80, UnitType.Percentage);

      foreach (UnitTest unittest in this.unit_tests_)
        this.create_unit_test (table, unittest, true);
    }

    protected override void Render (HtmlTextWriter writer)
    {
      Table table = (Table)this.Controls[1];
      TableCell cell;

      foreach (TableRow row in table.Rows)
      {
        if (row.Cells.Count > 2)
        {
          cell = row.Cells[2];
          this.Page.ClientScript.RegisterForEventValidation (cell.Controls[0].UniqueID);

          cell = row.Cells[3];
          this.Page.ClientScript.RegisterForEventValidation (cell.Controls[0].UniqueID);
        }
      }

      // Pass control to the base class.
      base.Render (writer);
    }
    #endregion

    #region Event Handlers
    /**
     * Event handler for clicking the evaluate command.
     */
    protected void onclick_evaluate_unit_test (object sender, CommandEventArgs e)
    {
      if (e.CommandName == "evaluate")
      {
        if (this.suite_ != null)
        {
          int utid = int.Parse ((string)e.CommandArgument);

          try
          {
            // Open the evaluator.
            this.suite_.Evaluator.Open ();

            // Evaluate the result.
            UnitTestResult result =
              this.suite_.Evaluator.Reevaluate (this.suite_.TestNumber,
                                                utid,
                                                true);

            // Save the result for the evaluation
            UnitTest test = this.unit_tests_.Find (utid);

            if (test != UnitTest.Undefined)
              test.Result = result;
          }
          finally
          {
            this.suite_.Evaluator.Close ();
          }
        }
      }
    }
    #endregion

    private void create_unit_test (Table table, UnitTest unittest, bool viewstate)
    {
      // Create the new table row this unit test.
      TableRow row = new TableRow ();
      table.Rows.Add (row);

      // Create the cell that contain's the unit test name.
      TableCell cell = new TableCell ();
      row.Cells.Add (cell);

      cell.Controls.Add (new LiteralControl (" &middot; " + unittest.Name));

      // Create the cell that display's the results.
      cell = new TableCell ();
      row.Cells.Add (cell);

      Label result = new Label ();
      cell.Controls.Add (result);

      UnitTestResult ut_result = unittest.Result;

      if (ut_result != null)
      {
        if (ut_result.Value != null)
         result.Text = ut_result.Value.ToString ();

        GroupResult grp_results = ut_result.GroupResult;

        if (grp_results.Count != 0)
        {
          foreach (GroupResultItem grp in grp_results)
          {
            // Create a new row for the group result.
            TableRow grp_row = new TableRow ();
            table.Rows.Add (grp_row);

            // Insert the cell that displays the group's name.
            TableCell grp_cell = new TableCell ();
            grp_row.Cells.Add (grp_cell);

            grp_cell.CssClass = "unittest-groupname";
            grp_cell.Controls.Add (new LiteralControl (grp.Name));

            // Insert the cell that displays the group's result.
            grp_cell = new TableCell ();
            grp_row.Cells.Add (grp_cell);

            grp_cell.Controls.Add (new LiteralControl (grp.Value.ToString ()));
          }

        }
      }
      else
      {
        result.Text = "(no result)";
        result.ForeColor = Color.Gray;
      }

      // Create cell that will hold link for charting data trend.
      cell = new TableCell ();
      row.Cells.Add (cell);

      // Create a link for charting the unit test data.
      ImageButton chart = new ImageButton ();
      cell.Controls.Add (chart);

      chart.PostBackUrl = String.Format ("~/unittestchart.aspx?t={0}&utid={1}",
                                         this.suite_.TestNumber,
                                         unittest.ID);

      chart.ID = String.Format ("ut_chart_{0}_{1}_",
                                this.suite_.TestNumber,
                                unittest.ID);

      chart.ImageUrl = "~/images/graph.gif";
      chart.AlternateText = "view data trend";
      chart.ToolTip = "view data trend";

      // Create the cell for manually evaluating the unit test.
      cell = new TableCell ();
      row.Cells.Add (cell);

      LinkButton link = new LinkButton ();
      cell.Controls.Add (link);

      link.ID = String.Format ("evaluate_{0}_{1}_",
                               this.suite_.TestNumber,
                               unittest.ID);

      link.EnableViewState = true;
      link.Text = "Click here to evaluate";
      link.CommandName = "evaluate";
      link.CommandArgument = unittest.ID.ToString ();
      link.Command += new CommandEventHandler (this.onclick_evaluate_unit_test);
    }

    #region Member Variables
    /**
     * Name of the test package.
     */
    private string name_;

    /**
     * Test number associate with package.
     */
    private UnitTestSuite suite_;

    /**
     * Collection of unit test in the test package.
     */
    private UnitTests unit_tests_ = new UnitTests ();
    #endregion
  }
}
