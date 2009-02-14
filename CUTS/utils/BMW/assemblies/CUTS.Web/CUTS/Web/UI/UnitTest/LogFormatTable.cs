// -*- C# -*-

//=============================================================================
/**
 * @file          LogFormatTable.cs
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

namespace CUTS.Web.UI.UnitTesting
{
  /**
   * @class LogFormatTable
   */
  public class LogFormatTable : Table, INamingContainer
  {
    /// Default constructor.
    public LogFormatTable ()
    {

    }

    /// Create the child controls for this control.
    protected override void CreateChildControls ()
    {
      base.CreateChildControls ();

      for (int i = 0; i < this.rows_; ++i)
        this.NewRow ();
    }

    /**
     *
     */
    protected override void LoadViewState (object saved_state)
    {
      object[] state = (object[])saved_state;

      if (state[0] != null)
        base.LoadViewState (state[0]);

      if (state[1] != null)
        this.rows_ = (int)state[1];

      if (state[2] != null)
        this.formats_ = (LogFormats)state[2];
    }

    /**
     *
     */
    protected override object SaveViewState ()
    {
      object[] state = new object[3];

      state[0] = base.SaveViewState ();
      state[1] = this.rows_;
      state[2] = this.formats_;

      return state;
    }

    public int SelectedCount
    {
      get
      {
        return this.rows_;
      }
    }

    public LogFormats LogFormats
    {
      get
      {
        return this.formats_;
      }

      set
      {
        this.formats_ = value;
      }
    }

    /// Bind data to the control.
    public override void DataBind ()
    {
      // Clear the child view state.
      if (this.HasChildViewState)
        this.ClearChildViewState ();

      // Let's not create the child controls.
      this.ChildControlsCreated = true;

      // Delete the rows from the table.
      this.rows_ = 0;
      this.Rows.Clear ();

      // Create the first row for the table.
      LogFormatRow row = this.NewRow ();

      // Initailize the data for this row.
      row.AddRange (this.formats_.ToArray ());
      row.SelectedValue = this.formats_[0].ID;

      // Increment the number of rows.
      this.rows_ = 1;
    }

    public void IncreaseLogFormats ()
    {
      // Create a new log format.
      this.EnsureChildControls ();
      LogFormatRow row = this.NewRow ();

      // Get the log formats from the last row.
      LogFormatRow lastrow = (LogFormatRow)this.Rows[this.rows_ - 1];
      LogFormats formats = new LogFormats (lastrow.LogFormats.ToArray ());

      // Remove last row's selected log format from all rows.
      LogFormat format = lastrow.SelectedItem;
      formats.Remove (format);

      int lastindex = this.rows_ - 1;

      for (int i = 0; i < this.rows_; ++i)
      {
        // Get the current row.
        LogFormatRow currrow = (LogFormatRow)this.Rows[i];

        // Remove the previously selected format from the row.
        if (i != lastindex)
          currrow.Remove (format);

        // Remove the newly selected format from the row.
        currrow.Remove (formats[0]);
      }

      // Initialize the contents of the row.
      row.AddRange (formats.ToArray ());
      row.SelectedValue = formats[0].ID;

      // Increment the row count.
      ++this.rows_;
    }

    public void DecreaseLogFormats ()
    {
      this.EnsureChildControls ();
      this.Rows.RemoveAt (-- this.rows_);
    }

    private void handle_selection_changed (object sender, EventArgs e)
    {
      // Get the index of the row.
      LogFormatRow row = (LogFormatRow)sender;
      int index = this.Rows.GetRowIndex (row);

      for (int i = 0; i < this.rows_; ++i)
      {
        if (i != index)
        {
          // Remove the current selection.
          row.Remove (row.SelectedItem);

          // Insert the previous selection.
          row.Add (this.prev_selection_);
        }
      }
    }

    private void handle_selection_changing (object sender, EventArgs e)
    {
      LogFormatRow row = (LogFormatRow)sender;
      this.prev_selection_ = row.SelectedItem;
    }

    private LogFormatRow NewRow ()
    {
      LogFormatRow row = new LogFormatRow ();
      this.Rows.Add (row);

      row.SelectionChanged += new EventHandler (this.handle_selection_changed);
      row.SelectionChanging += new EventHandler (this.handle_selection_changing);

      return row;
    }

    private LogFormats formats_ = new LogFormats ();

    private int rows_;

    private LogFormat prev_selection_;
  }
}
