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
        if (value.Value != null)
          this.result_label_.Text = value.Value.ToString ();

        LiteralControl literal;

        foreach (GroupResultItem item in value.GroupResult)
        {
          literal = new LiteralControl ("<br />" + item.Name);
          this.group_label_.Controls.Add (literal);

          literal = new LiteralControl ("<br />" + item.Value.ToString ());
          this.group_result_.Controls.Add (literal);
        }

        // Save the result value.
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
        this.title_.Text = String.Format (" &middot {0}", value);
        this.name_ = value;
      }
    }

    protected override void CreateChildControls ()
    {
      base.CreateChildControls ();

      // Create the cell that contain's the unit test name.
      TableCell cell = new TableCell ();
      this.Cells.Add (cell);

      this.title_ = new Label ();
      cell.Controls.Add (this.title_);

      this.group_label_ = new PlaceHolder ();
      cell.Controls.Add (this.group_label_);

      // Create the cell that display's the results.
      cell = new TableCell ();
      this.Cells.Add (cell);

      this.result_label_ = new Label ();
      cell.Controls.Add (this.result_label_);

      this.group_result_ = new PlaceHolder ();
      cell.Controls.Add (this.group_result_);

      if (this.results_ == null)
      {
        this.result_label_.Text = "(no result)";
        this.result_label_.ForeColor = Color.Gray;
      }

      // Create cell that will hold link for charting data trend.
      cell = new TableCell ();
      this.Cells.Add (cell);

      // Create a link for charting the unit test data.
      ImageButton chart = new ImageButton ();
      cell.Controls.Add (chart);

      chart.ImageUrl = "images/graph.gif";
      chart.Click += new ImageClickEventHandler (this.handle_chart);

      // Create the cell for manually evaluating the unit test.
      cell = new TableCell ();
      this.Cells.Add (cell);

      LinkButton link = new LinkButton ();
      cell.Controls.Add (link);

      link.ID = "evaluate";
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

    private void handle_chart (object sender, ImageClickEventArgs e)
    {
      if (this.Chart != null)
        this.Chart (this, new EventArgs ());
    }

    public event EventHandler Evaluate;

    public event EventHandler Chart;

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

    protected override void OnInit (EventArgs e)
    {
      // Make sure we are aligned up top.
      this.VerticalAlign = VerticalAlign.Top;
      base.OnInit (e);
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

    private Label title_;

    private Label result_label_;

    private PlaceHolder group_label_;

    private PlaceHolder group_result_;
  }
}
