// -*- C# -*-

//=============================================================================
/**
 * @file          LogFormatNodeRow.cs
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

using System;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using CUTS.Data.UnitTesting;

namespace CUTS.Web.UI.UnitTest
{
  /**
   * @class LogFormatNodeRow
   *
   * Single row for a LogFormatNode. The LogFormatNodeRow represents a
   * log format that is caused by the log format in the LogFormatNode.
   */
  public class LogFormatNodeRow : TableRow, INamingContainer
  {
    public LogFormatNodeRow ()
    {

    }

    public LogFormat Value
    {
      get
      {
        return this.logformat_;
      }

      set
      {
        this.EnsureChildControls ();

        this.label_.Text = String.Format ("[LF{0}]: {1}", value.ID, value.Text);
        this.rhs_label_.Text = String.Format ("LF{0}. ", value.ID);

        this.logformat_ = value;
      }
    }

    protected override void CreateChildControls ()
    {
      base.CreateChildControls ();

      // Create an empty first cell.
      this.Cells.Add (new TableCell ());

      // Create the cell and controls for displaying the value.
      TableCell cell = new TableCell ();
      this.Cells.Add (cell);

      // Create the image button for deleting the row.
      this.delete_ = new ImageButton ();
      cell.Controls.Add (this.delete_);

      // Configure the delete button.
      this.delete_.ID = "delete_";
      this.delete_.ImageUrl = "images/delete.gif";
      this.delete_.Click += new ImageClickEventHandler (this.handle_delete_row);
      this.delete_.CausesValidation = false;
      this.delete_.Style[HtmlTextWriterStyle.PaddingRight] = "2px";

      // Label for displaying the log format.
      this.label_ = new Label ();
      cell.Controls.Add (this.label_);
      cell.Controls.Add (new LiteralControl ("<br />where "));

      // Create the controls for editing the relation.
      this.lhs_ = new TextBox ();
      cell.Controls.Add (this.lhs_);
      cell.Controls.Add (new LiteralControl (" = "));

      this.rhs_label_ = new Label ();
      cell.Controls.Add (this.rhs_label_);

      this.rhs_ = new TextBox ();
      cell.Controls.Add (this.rhs_);
    }

    private void handle_delete_row (object sender, EventArgs e)
    {
      if (this.Remove != null)
        this.Remove (this, e);
    }

    public event EventHandler Remove;

    protected override object SaveViewState ()
    {
      object[] state = new object[2];

      state[0] = base.SaveViewState ();
      state[1] = this.logformat_;

      return state;
    }

    public VariableRelation[] Relation
    {
      get
      {
        // Make sure the child controls exist.
        this.EnsureChildControls ();

        LogFormatRelation relations = new LogFormatRelation ();

        // Get the variable from either side.
        string[] lhs = this.get_variables (this.lhs_);
        string[] rhs = this.get_variables (this.rhs_);

        // Convert the array of variables into relations.
        VariableRelation relation;

        for (int i = 0; i < lhs.Length; ++i)
        {
          // Create a new relation.
          relation = new VariableRelation ();
          relation.Left.Name = lhs[i];
          relation.Right.ID = this.logformat_.ID;
          relation.Right.Name = rhs[i];

          // Save the relation.
          relations.Add (relation);
        }

        // Return the array to the caller.
        return relations.ToArray ();
      }

      set
      {
        // Make sure the child controls exist.
        this.EnsureChildControls ();

      }
    }

    private string[] get_variables (TextBox text)
    {
      string separators = ",;";
      return text.Text.Split (separators.ToCharArray (),
                              StringSplitOptions.RemoveEmptyEntries);
    }

    protected override void LoadViewState (object savedState)
    {
      object[] state = (object[])savedState;

      if (state[0] != null)
        base.LoadViewState (state[0]);

      if (state[1] != null)
        this.logformat_ = (LogFormat)state[1];
    }

    private Label label_;

    private LogFormat logformat_;

    private ImageButton delete_;

    private TextBox lhs_;

    private TextBox rhs_;

    private Label rhs_label_;
  }
}
