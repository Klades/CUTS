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
     * Readonly property for the relations between two log formats.
     */
    //public CUTS.Data.Relation[] SelectedRelations
    //{
    //  get
    //  {
    //    return (CUTS.Data.Relation[])this.relations_.ToArray (typeof (CUTS.Data.Relation));
    //  }
    //}

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

    public string DataMemberLogFormats
    {
      get
      {
        return this.formats_table_;
      }

      set
      {
        this.formats_table_ = value;
      }
    }

    public string DataMemberRelations
    {
      get
      {
        return this.relations_table_;
      }

      set
      {
        this.relations_table_ = value;
      }
    }

    /**
     *
     */
    public DataSet DataSource
    {
      get
      {
        return this.ds_;
      }

      set
      {
        this.ds_ = value;
      }
    }

    /**
     *
     */
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
      LinkButton link = new LinkButton ();
      footer_cell.Controls.Add (link);

      link.EnableViewState = true;
      link.CausesValidation = false;
      link.Text = "I need more log formats";
      link.Click += new System.EventHandler (this.onclick_handler);
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
        this.ds_ = (DataSet)state[2];

      if (state[3] != null)
        this.formats_table_ = (string)state[3];

      if (state[4] != null)
        this.relations_table_ = (string)state[4];
    }

    /**
     *
     */
    protected override object SaveViewState ()
    {
      object[] state = new object[6];
      state[0] = base.SaveViewState ();
      state[1] = this.selected_log_formats_;
      state[2] = this.ds_;
      state[3] = this.formats_table_;
      state[4] = this.relations_table_;

      return state;
    }

    /**
     *
     */
    protected override void Render (HtmlTextWriter writer)
    {
      Table table = (Table)this.Controls[0];
      int count = table.Rows.Count - 1;

      for (int i = 1; i < count; ++i)
      {
        TableRow row = table.Rows[i];

        // Register the log format control for validation.
        this.Page.ClientScript.RegisterForEventValidation (row.Cells[1].Controls[0].UniqueID);
      }

      //// Register the link for adding more log formats.
      //TableRow footer = table.Rows[table.Rows.Count - 1];
      //this.Page.ClientScript.RegisterForEventValidation (footer.Cells[0].Controls[0].UniqueID);

      // Pass control to the base class.
      base.Render (writer);
    }

    /**
     * Bind the data to the control.
     */
    public override void DataBind ()
    {
      // Create the first log format for the table.
      Table table = (Table)this.Controls[0];
      this.create_new_log_format (table, -1);
    }

    /**
     *
     */
    private void onclick_handler (object sender, EventArgs e)
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

      if (index > 0)
      {
        // Get the relation cell for this row.
        TableCell relation_cell = row.Cells[2];
        RelationTable relation_table = (RelationTable)relation_cell.Controls[0];

        // Reset the contents of the relation.
        int left = (int)this.selected_log_formats_[index];
        int right = (int)this.selected_log_formats_[index - 1];

        relation_table.LeftID = left;
        relation_table.RightID = right;

        // Bind the data to the control.
        relation_table.DataSource = this.get_relations (left, right);
        relation_table.DataBind ();
      }
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

      // Create the relation cell for the table.
      TableCell relation_cell = new TableCell ();
      row.Cells.Add (relation_cell);

      int index = this.selected_log_formats_.IndexOf (lfid);

      if ((lfid == -1 && this.selected_log_formats_.Count > 0) ||
          (lfid != -1 && index > 0))
      {
        // Insert the default relation table.
        RelationTable relation_table = new RelationTable ();
        relation_cell.Controls.Add (relation_table);

        relation_table.EnableViewState = true;

        //if (lfid != -1)
        //{
        //  relation_table.LeftID = lfid;
        //  relation_table.RightID = this.selected_log_formats_[index - 1];
        //}
      }

      if (lfid != -1)
        return;

      // Finally, bind the data to the control. We need to do this last to
      // ensure all the controls for this row have been created.
      if (this.selected_log_formats_.Count > 0)
      {
        // Do not select log formats that are already showing.
        DataTable unselected = this.get_unselected_log_formats (0);

        if (unselected.Rows.Count <= 1)
          this.disable_more_log_format_link ();

        format_list.DataSource = unselected;
      }
      else
      {
        // Use the entire list of log formats.
        DataTable complete = this.ds_.Tables[this.formats_table_];

        if (complete.Rows.Count <= 1)
          this.disable_more_log_format_link ();

        format_list.DataSource = complete;
      }

      // Configure the dropdown list for the log formats.
      format_list.CausesValidation = false;
      format_list.EnableViewState = true;
      format_list.AutoPostBack = true;
      format_list.DataBound += new EventHandler (this.ondatabound_log_format);
      format_list.SelectedIndexChanged += new EventHandler (this.onchange_log_format_selection);
      format_list.Width = new Unit (500, UnitType.Pixel);
      format_list.DataTextField = "lfmt";
      format_list.DataValueField = "lfid";
      format_list.DataBind ();
    }

    /**
     *
     */
    private DataTable get_relations (int index)
    {
      // Define the filters for either side of the relation.
      int left = (int)this.selected_log_formats_[index];
      int right = (int)this.selected_log_formats_[index - 1];

      return this.get_relations (left, right);
    }

    /**
     *
     */
    private DataTable get_relations (int left, int right)
    {
      string filter = String.Format ("lfid IN ({0},{1})", left, right);

      // Select the variable for either side of the relation.
      DataTable relations = this.ds_.Tables[this.relations_table_];
      DataRow[] rows = relations.Select (filter);

      // Build the data table for the lhs relation.
      DataTable result = relations.Clone ();

      foreach (DataRow row in rows)
      {
        // Create a new for the data table.
        DataRow nr = result.NewRow ();
        nr.ItemArray = row.ItemArray;

        // Insert the new row into the data table.
        result.Rows.Add (nr);
      }

      return result;
    }

    /**
     * Helper method to get the prefix control for a row.
     */
    private LiteralControl get_prefix_control (TableRow row)
    {
      return (LiteralControl)row.Cells[0].Controls[0];
    }

    /**
     * Helper method to set the text for the prefix control.
     */
    private void set_prefix_text (LiteralControl prefix, int lfid)
    {
      prefix.Text = String.Format ("LF{0}.", lfid);
    }

    /**
     *
     */
    private void disable_more_log_format_link ()
    {
      Table table = (Table)this.Controls[0];
      TableRow footer = table.Rows[table.Rows.Count - 1];
      LinkButton link = (LinkButton)footer.Cells[0].Controls[0];

      link.Visible = false;
    }

    /**
     *
     */
    private DataTable get_unselected_log_formats (int start)
    {
      // Create a structural copy of the log formats table.
      DataTable log_formats = this.ds_.Tables[this.formats_table_];
      DataTable tmp_table = log_formats.Clone ();

      // Gather the ids of all the selected log formats.
      ArrayList selected = new ArrayList (this.selected_log_formats_.Count - 1);

      for (int i = start; i < this.selected_log_formats_.Count; ++i)
        selected.Add (this.selected_log_formats_[i].ToString ());

      string lfids = String.Join (", ", (string[])selected.ToArray (typeof (string)));
      string filter = String.Format ("NOT lfid IN ({0})", lfids);

      // Finally select the remaining log formats and return a data
      // table containing them.
      DataTable formats = this.ds_.Tables[this.formats_table_];
      DataRow[] remaining = formats.Select (filter);

      foreach (DataRow row in remaining)
      {
        DataRow nrow = tmp_table.NewRow ();
        tmp_table.Rows.Add (nrow);

        nrow["lfid"] = row["lfid"];
        nrow["lfmt"] = row["lfmt"];
      }

      return tmp_table;
    }

    /**
     * Data table that contains all the log formats.
     */
    private DataSet ds_;

    private string formats_table_;

    private string relations_table_;

    /**
     * List of selected log formats.
     */
    private ArrayList selected_log_formats_ = new ArrayList ();
  }
}
