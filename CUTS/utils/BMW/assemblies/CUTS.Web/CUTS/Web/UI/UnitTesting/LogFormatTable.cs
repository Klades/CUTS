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
using System.Data;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace CUTS.Web.UI.UnitTesting
{
  /**
   * @class LogFormatTable
   */
  public class LogFormatTable : CompositeControl, INamingContainer
  {
    /**
     * Default constructor.
     */
    public LogFormatTable ()
    {

    }

    /**
     * Readonly property for the selected log formats.
     */
    public int[] SelectedLogFormats
    {
      get
      {
        return (int[])this.selected_log_formats_.ToArray (typeof (int));
      }
    }

    /**
     * Readonly property for getting the number of selected log
     * formats. This number will dictate the size of the array returned
     * by SelectedLogFormats and SelectedRelations.
     */
    public int Count
    {
      get
      {
        return this.selected_log_formats_.Count;
      }
    }

    /**
     *
     */
    public object DataSource
    {
      get
      {
        return this.log_formats_;
      }

      set
      {
        this.log_formats_ = value;
      }
    }

    protected override void CreateChildControls ()
    {
      Table table = new Table ();
      this.Controls.Add (table);

      // Prepare the header row of the table.
      TableHeaderRow header = new TableHeaderRow ();
      table.Rows.Add (header);

      // Prepare the header cell for the prefix.
      TableHeaderCell prefix = new TableHeaderCell ();
      header.Cells.Add (prefix);

      prefix.Controls.Add (new LiteralControl ("Prefix"));

      // Prepare the header cell for the format.
      TableHeaderCell format = new TableHeaderCell ();
      header.Cells.Add (format);

      format.Controls.Add (new LiteralControl ("Log Format"));

      // Prepare the header cell for the relations.
      TableHeaderCell relation = new TableHeaderCell ();
      header.Cells.Add (relation);

      relation.Controls.Add (new LiteralControl ("Relation"));

      // Now, insert the rows into the table.
      foreach (int lfid in this.selected_log_formats_)
        this.create_new_log_format (table, lfid);

      // Prepare the footer row of the table.
      TableFooterRow footer = new TableFooterRow ();
      table.Rows.Add (footer);

      // Prepare the cell for displaying the link.
      TableCell footer_cell = new TableCell ();
      footer.Cells.Add (footer_cell);
      footer_cell.ColumnSpan = header.Cells.Count;

      // Insert the link button for adding more log formats.
      LinkButton more_formats_link = new LinkButton ();
      footer_cell.Controls.Add (more_formats_link);

      more_formats_link.ID = "more_formats_link_";
      more_formats_link.Text = "I need more log formats";
      more_formats_link.Click += new System.EventHandler (this.onclick_more_log_formats);
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
        this.selected_log_formats_ = (ArrayList)state[1];

      if (state[2] != null)
        this.log_formats_ = state[2];
    }

    /**
     *
     */
    protected override object SaveViewState ()
    {
      object[] state = new object[3];
      state[0] = base.SaveViewState ();
      state[1] = this.selected_log_formats_;
      state[2] = this.log_formats_;

      return state;
    }

    protected override void Render (HtmlTextWriter writer)
    {
      this.Page.ClientScript.RegisterForEventValidation ("more_formats_link_");
      base.Render (writer);
    }

    /**
     * Bind the data to the control.
     */
    public override void DataBind ()
    {
      // Ensure the child control have been created.
      this.EnsureChildControls ();

      // Create the first log format for the table.
      Table table = (Table)this.Controls[0];
      this.create_new_log_format (table, -1);
    }

    /**
     *
     */
    private void onclick_more_log_formats (object sender, EventArgs e)
    {
      // Get the table from the control.
      Table table = (Table)this.Controls[0];

      // Create a new log format for the table.
      this.create_new_log_format (table, -1);
    }

    /**
     *
     */
    private void onchange_log_format_selection (object sender, EventArgs e)
    {
      // Get the selected log format.
      DropDownList formats = (DropDownList)sender;
      int lfid = int.Parse (formats.SelectedValue);

      // Get the parent for the log formats control.
      TableCell cell = (TableCell)formats.Parent;
      TableRow row = (TableRow)cell.Parent;

      // Update the selected log format.
      Table table = (Table)this.Controls[0];
      int index = table.Rows.GetRowIndex (row) - 1;
      this.selected_log_formats_[index] = lfid;

      // Get the prefix control for this row.
      LiteralControl prefix = this.get_prefix_control (row);
      this.set_prefix_text (prefix, lfid);
    }

    /**
     *
     */
    private void ondatabound_log_format (object sender, EventArgs e)
    {
      // The sender of the event is a dropdown list.
      DropDownList format_list = (DropDownList)sender;

      // Get the parent row of this selection.
      TableCell format_cell = (TableCell) format_list.Parent;
      TableRow row = (TableRow)format_cell.Parent;

      // Get the index of this row in the table, which will tell us
      // which selected log format changed.
      Table table = (Table)row.Parent;
      int index = table.Rows.GetRowIndex (row) - 1;

      // Save the selected log format.
      int lfid = int.Parse (format_list.SelectedValue);
      this.selected_log_formats_.Add (lfid);

      // Update the prefix for this row.
      LiteralControl prefix = this.get_prefix_control (row);
      this.set_prefix_text (prefix, lfid);
    }

    /**
     * Helper method to add a new log format to the table. This will create
     * a new row in the table for selecting log formats. If \a use_viewstate
     * is true
     *
     * @param[in]           use_viewstate         Using the view state.
     */
    private void create_new_log_format (Table table, int lfid)
    {
      // Create a new log format item for the table.
      TableRow row = new TableRow ();

      if (lfid != -1)
        table.Rows.Add (row);
      else
        table.Rows.AddAt (table.Rows.Count - 1, row);

      // Create the prefix cell for the table.
      TableCell prefix_cell = new TableCell ();
      row.Cells.Add (prefix_cell);

      // Insert the prefix control into the cell.
      LiteralControl prefix = new LiteralControl ();
      prefix_cell.Controls.Add (prefix);

      // Configure the prefix ocontrol.
      if (lfid != -1)
        this.set_prefix_text (prefix, lfid);

      // Create the log formats cell for the table.
      TableCell format_cell = new TableCell ();
      row.Cells.Add (format_cell);

      // Insert the droplist for the log formats into the cell.
      DropDownList format_list = new DropDownList ();
      format_cell.Controls.Add (format_list);

      // Configure the dropdown list for the log formats.
      format_list.EnableViewState = true;
      format_list.AutoPostBack = true;
      format_list.DataBound += new EventHandler (this.ondatabound_log_format);
      format_list.SelectedIndexChanged += new EventHandler (this.onchange_log_format_selection);

      if (lfid == -1)
      {
        // Select the log formats to bind to the control.
        format_list.DataSource = this.log_formats_;
        format_list.DataValueField = "lfid";
        format_list.DataTextField = "lfmt";
        format_list.DataBind ();
      }

      // Create the relation cell for the table.
      TableCell relation_cell = new TableCell ();
      row.Cells.Add (relation_cell);

      // Insert the controls for the relation.

      // Configure the controls for the relation.
      //if (!using_viewstate)
      //{
      //  // First, we need to get a list of all the log formats that have
      //  // already been added to the listing. This is so we can ensure
      //  // the current listing does not list the same formats.
      //  ArrayList list = new ArrayList ();

      //  foreach (TableRow row in this.Rows)
      //  {
      //    if (row is LogFormatTableItem)
      //    {
      //      LogFormatTableItem format = (LogFormatTableItem)row;
      //      list.Add (format.LogFormatID);
      //    }
      //  }

      //  // Insert the item into the collection.
      //  int count = this.Rows.Count;
      //  this.Rows.AddAt (count - 1, item);

      //  if (list.Count > 0)
      //  {
      //    // Bind the data to the formats that have not been selected.
      //    string strlist =
      //      String.Join (",", (string[])list.ToArray (typeof (string)));

      //    string filter = String.Format ("lfid NOT IN ({0})", strlist);

      //    DataTable table = (DataTable)this.log_formats_;
      //    DataRow[] filter_formats = table.Select (filter, "lfid ASC");

      //    item.DataSourceLogFormats = filter_formats;
      //  }
      //  else
      //  {
      //    item.DataSourceLogFormats = this.log_formats_;
      //  }

      //  // Bind the data to the control.
      //  item.DataBind ();
      //}

      //// Set the view state of the item.
      //item.EnableViewState = this.EnableViewState;
    }

    private void set_prefix_text (LiteralControl prefix, int lfid)
    {
      prefix.Text = String.Format ("LF{0}.", lfid);
    }

    private LiteralControl get_prefix_control (TableRow row)
    {
      return (LiteralControl)row.Cells[0].Controls[0];
    }

    /**
     * Data table that contains all the log formats.
     */
    private object log_formats_;

    /**
     * List of selected log formats.
     */
    private ArrayList selected_log_formats_ = new ArrayList ();
  }
}
