// -*- C# -*-

//=============================================================================
/**
 * @file          UnitTest.cs
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

using System;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using CUTS.Data.UnitTesting;

namespace CUTS.Web.UI.UnitTest
{
  /**
   * @class UnitTest
   *
   * Control for evaluating a unit test within a test package.
   */
  [ParseChildren (true),
   PersistChildren (false)]
  public class UnitTest : TableRow, INamingContainer
  {
    /**
     * Default constructor.
     */
    public UnitTest ()
    {

    }

    public int UnitTestId
    {
      get
      {
        return this.utid_;
      }

      set
      {
        this.utid_ = value;
      }
    }

    public UnitTestResult Result
    {
      get
      {
        return this.results_;
      }

      set
      {
        // Make sure the child controls exists.
        this.EnsureChildControls ();

        // Update the result for the unit test.

        // Save the result.
        this.results_ = value;
      }
    }

    public string Name
    {
      get
      {
        return this.name_;
      }

      set
      {
        // Make sure the child control exist.
        this.EnsureChildControls ();

        // Update the unit test name.
        Label title = this.get_control_unit_test_name ();
        title.Text = String.Format (" &middot {0}", value);

        // Save the name of the unit test.
        this.name_ = value;
      }
    }

    protected override void CreateChildControls ()
    {
      base.CreateChildControls ();

      // Create the cell that contain's the unit test name.
      TableCell cell = new TableCell ();
      this.Cells.Add (cell);

      Label title = new Label ();
      cell.Controls.Add (title);

      // Create the cell that display's the results.
      cell = new TableCell ();
      this.Cells.Add (cell);

      Label result = new Label ();
      cell.Controls.Add (result);

      if (this.results_ == null)
      {
        result.Text = "(no result)";
        result.ForeColor = Color.Gray;
      }

      // Create cell that will hold link for charting data trend.
      cell = new TableCell ();
      this.Cells.Add (cell);

      // Create a link for charting the unit test data.
      ImageButton chart = new ImageButton ();
      cell.Controls.Add (chart);

      // Create the cell for manually evaluating the unit test.
      cell = new TableCell ();
      this.Cells.Add (cell);

      LinkButton link = new LinkButton ();
      cell.Controls.Add (link);

      link.Text = "Click here to evaluate";
      link.Click += new EventHandler (this.handle_evaluate);
    }

    protected override object SaveViewState ()
    {
      object[] state = new object[4];

      state[0] = base.SaveViewState ();
      state[1] = this.name_;
      state[2] = this.utid_;
      state[3] = this.results_;

      return state;
    }

    protected override void LoadViewState (object savedState)
    {
      object[] state = (object[])savedState;

      if (state[0] != null)
        base.LoadViewState (state[0]);

      if (state[1] != null)
        this.name_ = (string)state[1];

      if (state[2] != null)
        this.utid_ = (int)state[2];

      if (state[3] != null)
        this.results_ = (UnitTestResult)state[3];
    }

    private void handle_evaluate (object sender, EventArgs e)
    {
      if (this.Evaluate != null)
        this.Evaluate (this, e);
    }

    public event EventHandler Evaluate;

    private Label get_control_unit_test_name ()
    {
      return (Label)this.Cells[0].Controls[0];
    }

    private ImageButton get_control_chart_link ()
    {
      return (ImageButton)this.Cells[2].Controls[0];
    }

    private LinkButton get_control_evaluate_link ()
    {
      return (LinkButton)this.Cells[3].Controls[0];
    }

    /**
     * Name of the unit test.
     */
    private string name_;

    /**
     * Unique id of the unit test.
     */
    private int utid_;

    /**
     * Results for the unit test.
     */
    private UnitTestResult results_;
  }
}
