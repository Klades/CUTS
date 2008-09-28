// -*- C# -*-

//=============================================================================
/**
 * @file        TestPackage.cs
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

using System;
using System.Collections;
using System.Data;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using CUTS.Data.UnitTesting;

namespace CUTS.Web.UI.UnitTesting
{
  /**
   * @class TestPackage
   *
   * Custom control for displaying the results of a test package. The
   * test package has a collection of unit test, which contain the actual
   * results.
   */
  public class TestPackage : CompositeControl, INamingContainer
  {
    /**
     * Default constructor.
     */
    public TestPackage ()
    {

    }

    /**
     * Initializing constructor.
     */
    public TestPackage (int test_number, string name)
    {
      this.test_number_ = test_number;
      this.name_ = name;
    }

    /**
     * Clear all the unit test from the test package.
     */
    public void Clear ()
    {
      this.results_.Clear ();
    }

    /**
     * Setter/getter attributes the package's test name.
     */
    public string Name
    {
      get
      {
        return this.name_;
      }

      set
      {
        this.name_ = value;
      }
    }

    /**
     * Setter/getter attributes for the package's test number.
     */
    public int TestNumber
    {
      get
      {
        return this.test_number_;
      }

      set
      {
        this.test_number_ = value;
      }
    }

    /**
     * Get the unit test results for this package.
     */
    public UnitTestResult[] UnitTestResults
    {
      get
      {
        return (UnitTestResult[])this.results_.ToArray (typeof (UnitTestResult));
      }
    }

    /**
     * Insert a new unit test result into the package.
     */
    public void Add (UnitTestResult result)
    {
      this.results_.Add (result);
    }

    /**
     * Load the view state for this control.
     */
    protected override void LoadViewState (object saved_state)
    {
      object[] state = (object[])saved_state;

      if (state[0] != null)
        base.LoadViewState (state[0]);

      if (state[1] != null)
        this.name_ = (string)state[1];

      if (state[2] != null)
        this.results_ = (ArrayList)state[2];
    }

    /**
     * Save the view state of this control.
     */
    protected override object SaveViewState ()
    {
      object[] state = new object[3];

      state[0] = base.SaveViewState ();
      state[1] = this.name_;
      state[2] = this.results_;

      return state;
    }

    /**
     * Bind the data to the control.
     */
    public override void DataBind ()
    {
      base.DataBind ();
      this.EnsureChildControls ();
    }

    /**
     * Create the child controls for this control.
     */
    protected override void CreateChildControls ()
    {
      base.CreateChildControls ();

      // First, create the header for the package.
      Label header = new Label ();
      this.Controls.Add (header);

      header.Text = String.Format ("{0} Package", this.name_);
      header.Style[HtmlTextWriterStyle.FontWeight] = "bold";

      this.Controls.Add (new LiteralControl ("<hr />"));

      // Next, create the table that will host the unit test results.
      Table result_table = new Table ();
      this.Controls.Add (result_table);

      // Finally, insert each of the unit test into the table.
      foreach (UnitTestResult result in this.results_)
      {
        // Create a new row in the table.
        TableRow row = new TableRow ();
        result_table.Rows.Add (row);

        // Create the cell for the name.
        TableCell name_cell = new TableCell ();
        row.Cells.Add (name_cell);

        name_cell.Controls.Add (new LiteralControl (" &middot; " + result.Name));
        name_cell.Width = new Unit (500, UnitType.Pixel);

        // Create the cell for the result.
        TableCell result_cell = new TableCell ();
        row.Cells.Add (result_cell);

        result_cell.Controls.Add (
          new LiteralControl (
          result.Result != null ? result.Result.ToString () : ""));

        result_cell.Width = new Unit (150, UnitType.Pixel);

        // Create the cell for displaying the chart.
        TableCell chart_cell = new TableCell ();
        row.Cells.Add (chart_cell);

        if (result.Result != null ||
            result is UnitTestGroupResult)
        {
          ImageButton button = new ImageButton ();
          chart_cell.Controls.Add (button);

          button.PostBackUrl = String.Format ("unittestchart.aspx?t={0}&utid={1}",
                                              this.test_number_,
                                              result.ID);

          button.ImageUrl = "~/images/table.gif";
          button.AlternateText = "view data trend";
        }

        // Finally, let's see if this is actually a group result. If it is, then
        // we need to display the results for each group member.
        if (result is UnitTestGroupResult)
        {
          UnitTestGroupResult group = (UnitTestGroupResult)result;

          foreach (UnitTestResult member in group.Results)
          {
            TableRow member_row = new TableRow ();
            result_table.Rows.Add (member_row);

            // Insert the name of the member into the table.
            TableCell member_name_cell = new TableCell ();
            member_row.Cells.Add (member_name_cell);

            member_name_cell.Controls.Add (new LiteralControl (member.Name));

            // Insert the result of the member into the table.
            TableCell member_result_cell = new TableCell ();
            member_row.Cells.Add (member_result_cell);

            member_result_cell.Controls.Add (new LiteralControl (member.Result.ToString ()));
          }
        }
      }
    }

    /**
     * Name of the test package.
     */
    private string name_;

    /**
     * Test number for the test package.
     */
    private int test_number_ = -1;

    /**
     * Collection of unit test for the test package.
     */
    private ArrayList results_ = new ArrayList ();
  }
}
