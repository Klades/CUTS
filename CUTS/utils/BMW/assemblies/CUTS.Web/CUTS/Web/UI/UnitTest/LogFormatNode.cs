// -*- C# -*-

//=============================================================================
/**
 * @file          LogFormatNode.cs
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using CUTS.Data.UnitTesting;

namespace CUTS.Web.UI.UnitTest
{
  /**
   * @class LogFormatNode
   */
  public class LogFormatNode : CompositeControl, INamingContainer
  {
    public LogFormatNode ()
    {

    }

    public LogFormat Value
    {
      get
      {
        return this.value_;
      }

      set
      {
        // Make sure the child controls exist.
        this.EnsureChildControls ();

        // Update the label and save the format.
        this.label_.Text = String.Format ("[LF{0}]: {1}", value.ID, value.Text);
        this.value_ = value;
      }
    }

    public LogFormatCollection SelectedItems
    {
      get
      {
        return this.selected_;
      }
    }

    public LogFormatRelation [] Relations
    {
      get
      {
        // Make sure the child controls exist.
        this.EnsureChildControls ();

        // Create a array of variable relations.
        LogFormatNodeRow row;
        VariableRelation[] relations;
        LogFormatRelationCollection collection = new LogFormatRelationCollection ();

        // Iterate through each node and gets its relation.
        for (int i = 1; i < this.table_.Rows.Count; ++i)
        {
          row = (LogFormatNodeRow)this.table_.Rows[i];
          relations = row.Relation;

          if (relations.Length > 0)
          {
            // Update the id for each of the left variables.
            foreach (VariableRelation relation in relations)
              relation.Left.ID = this.value_.ID;

            collection.Add (new LogFormatRelation (relations));
          }
        }

        return collection.ToArray ();
      }
    }

    public void CandidateChildren (LogFormatCollection lfc)
    {
      // Make sure the child controls exist.
      this.EnsureChildControls ();

      // Clear all the log formats.
      this.formats_.Items.Clear ();

      foreach (LogFormat f in lfc)
      {
        // Only add the log format if it does not equal the value
        // of this node, and it is not in the selected formats.
        if (!this.value_.Equals (f) && !this.selected_.Contains (f))
          this.formats_.Items.Add (new ListItem (f.Text, f.ID.ToString ()));
      }

      // Hide the log formats if there are no items.
      this.footer_.Visible = this.formats_.Items.Count > 0 ? true : false;
    }

    protected override void CreateChildControls ()
    {
      // Pass control to the base class.
      base.CreateChildControls ();

      // Create the table for displaying the log formats.
      this.table_ = new Table ();
      this.Controls.Add (this.table_);

      // Create the header for the table.
      TableRow header = new TableRow ();
      this.table_.Rows.Add (header);

      // Create the cell and control for controlling visibility.
      TableCell cell = new TableCell ();
      header.Cells.Add (cell);

      this.visibility_ = new ImageButton ();
      cell.Controls.Add (this.visibility_);

      this.visibility_.ID = "visibility_";
      this.visibility_.ImageUrl = "images/minus.gif";
      this.visibility_.CausesValidation = false;

      // Create the cell and control for labeling the node.
      cell = new TableCell ();
      header.Cells.Add (cell);

      this.label_ = new Label ();
      cell.Controls.Add (this.label_);

      for (int i = 0; i < this.selected_.Count; ++i)
      {
        LogFormatNodeRow row = new LogFormatNodeRow ();
        this.table_.Rows.Add (row);

        row.Remove += new EventHandler (this.handle_remove_row);
      }

      // Create the footer for adding new formats to node.
      this.footer_ = new PlaceHolder ();
      this.Controls.Add (this.footer_);

      // Insert the dropdown list for selecting log formats.
      this.formats_ = new DropDownList ();
      this.footer_.Controls.Add (this.formats_);

      // Insert the button for selecting the log format.
      this.insert_ = new LinkButton ();
      this.footer_.Controls.Add (this.insert_);

      this.insert_.ID = "insert_";
      this.insert_.Text = "Add log format to node";
      this.insert_.Click += new EventHandler (this.handle_add_log_format);
      this.insert_.CausesValidation = false;
    }

    protected override object SaveViewState ()
    {
      object[] state = new object[3];

      state[0] = base.SaveViewState ();
      state[1] = this.value_;
      state[2] = this.selected_;

      return state;
    }

    protected override void Render (HtmlTextWriter writer)
    {
      // First, render the table for the node.
      writer.WriteBeginTag ("p");
      this.table_.RenderControl (writer);

      // Render the remaining items if there are items to select
      // from in the dropdown listing of candidate log formats.
      if (this.formats_.Items.Count > 0)
      {
        // Put a horizontal line between the table and controls.
        writer.WriteFullBeginTag ("hr");

        // Next, render the dropdown list.
        this.formats_.RenderControl (writer);
        writer.WriteBreak ();

        // Finally, write the link for adding more formats.
        this.insert_.RenderControl (writer);
      }

      writer.WriteEndTag ("p");
    }

    private void handle_remove_row (object sender, EventArgs e)
    {
      // Get the row that sent the message.
      LogFormatNodeRow row = (LogFormatNodeRow)sender;

      // Remove the row from the table.
      this.table_.Rows.Remove (row);

      // Remove log format from selected, and insert into listing.
      LogFormat format = row.Value;
      this.selected_.Remove (format);
      this.formats_.Items.Add (new ListItem (format.Text, format.ID.ToString ()));
    }

    private void handle_add_log_format (object sender, EventArgs e)
    {
      // Create a log format from the selected item.
      LogFormat format = new LogFormat ();
      format.ID = int.Parse (this.formats_.SelectedItem.Value);
      format.Text = this.formats_.SelectedItem.Text;

      // Create a new row in the table for selected log format.
      LogFormatNodeRow row = new LogFormatNodeRow ();
      this.table_.Rows.Add (row);

      // Set the value of the row.
      row.Value = format;
      row.Remove += new EventHandler (this.handle_remove_row);

      // Remove selected format from candidate formats.
      this.formats_.Items.Remove (this.formats_.SelectedItem);

      // Update the visibility of the footer.
      if (this.formats_.Items.Count == 0)
        this.footer_.Visible = false;

      // Save the log format in the selected formats.
      this.selected_.Add (format);
    }

    protected override void LoadViewState (object savedState)
    {
      object[] state = (object[])savedState;

      if (state[0] != null)
        base.LoadViewState (state[0]);

      if (state[1] != null)
        this.value_ = (LogFormat)state[1];

      if (state[2] != null)
        this.selected_ = (LogFormatCollection)state[2];
    }

    private Label label_;

    private LogFormat value_;

    private LogFormatCollection selected_ = new LogFormatCollection ();

    private Table table_;

    private PlaceHolder footer_;

    private DropDownList formats_;

    private ImageButton visibility_;

    private LinkButton insert_;
  }
}

