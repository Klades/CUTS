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
     * Clear the contents of the log format table.
     */
    public void Clear ()
    {
      // Clear the data objects for the control.
      this.selected_log_formats_.Clear ();
      this.selected_relations_.Clear ();

      Table table = (Table)this.Controls[0];
      table.Rows.Clear ();

      this.insert_header_row (ref table);
      this.create_new_log_format (ref table, -1);
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
    public CUTS.Data.Relation[] SelectedRelations
    {
      get
      {
        ArrayList relations = new ArrayList ();

        Table table = (Table)this.Controls[0];

        for (int i = 2; i < table.Rows.Count; ++ i)
        {
          TableRow row = table.Rows[i];
          RelationTable relation = (RelationTable)row.Cells[2].Controls[0];
          relations.Add (relation.Relation);
        }

        return (CUTS.Data.Relation[])relations.ToArray (typeof (CUTS.Data.Relation));
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

      // Insert the header row for the table.
      this.insert_header_row (ref table);

      // Now, insert the rows into the table.
      foreach (int lfid in this.selected_log_formats_)
        this.create_new_log_format (ref table, lfid);

      // Insert the link button for adding more log formats.
      LinkButton link = new LinkButton ();
      this.Controls.Add (link);

      link.EnableViewState = true;
      link.Text = "I need more log formats";
      link.ID = "link_more_formats_";
      link.Click += new System.EventHandler (this.onclick_more_formats);
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
      // Register all the dropdown list for validation.
      Table table = (Table)this.Controls[0];

      foreach (TableRow row in table.Rows)
      {
        if (!(row is TableHeaderRow))
          this.Page.ClientScript.RegisterForEventValidation (row.Cells[1].Controls[0].UniqueID);
      }

      // Register the link for adding more log formats.
      TableRow footer = table.Rows[table.Rows.Count - 1];
      this.Page.ClientScript.RegisterForEventValidation (this.Controls[1].UniqueID);

      // Pass control to the base class.
      base.Render (writer);
    }

    /**
     * Bind the data to the control.
     */
    public override void DataBind ()
    {
      // First, ensure we have created the child control.
      this.EnsureChildControls ();

      // Create the first log format for the table.
      Table table = (Table)this.Controls[0];
      this.create_new_log_format (ref table, -1);
    }

    /**
     *
     */
    private void onclick_more_formats (object sender, EventArgs e)
    {
      // Get the table from the control.
      Table table = (Table)this.Controls[0];

      // Create a new log format for the table.
      this.create_new_log_format (ref table, -1);

      int lfid = (int)this.selected_log_formats_[this.selected_log_formats_.Count - 1];
      this.update_log_format_listings (table, -1, lfid, this.selected_log_formats_.Count);
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
      int old_lfid = (int)this.selected_log_formats_[index];
      this.selected_log_formats_[index] = lfid;

      // Get the prefix control for this row.
      LiteralControl prefix = this.get_prefix_control (row);
      this.set_prefix_text (prefix, lfid);

      if (index > 0)
      {
        // Update the relation.
        RelationTable relation = (RelationTable)row.Cells[2].Controls[0];
        relation.EffectID = lfid;
      }

      // Update the candidate causalities for all the relations.
      this.update_candidate_causalities (table, index + 1);
      this.update_log_format_listings (table, old_lfid, lfid, index + 1);
    }

    /**
     *
     */
    private void update_candidate_causalities (Table table, int ignore)
    {
      for (int i = 2; i < table.Rows.Count; ++i)
      {
        if (i != ignore)
        {
          RelationTable relation = (RelationTable)table.Rows[i].Cells[2].Controls[0];

          relation.LogIDList = (int[])this.selected_log_formats_.ToArray (typeof (int));
          relation.DataBind ();
        }
      }
    }

    /**
     * Helper method for updating the log formats when one of the log
     * formats changes. The current implementation is very inefficient
     * and needs to be updated. What should really happen is we add a
     * single format to all the controls, and remove one from all the
     * controls.
     */
    private void update_log_format_listings (Table table, int add, int remove, int ignore)
    {
      DataTable dt = this.ds_.Tables[this.formats_table_];

      // Get the list item for the new log format.
      DataRow [] dr = dt.Select (String.Format ("lfid={0}", add));

      ListItem add_item = add != -1 ?
        new ListItem (dr[0]["lfmt"].ToString (), dr[0]["lfid"].ToString ()) : null;

      // Get the list item for the old log format.
      dr = dt.Select (String.Format ("lfid={0}", remove));

      ListItem remove_item = remove != -1 ?
        new ListItem (dr[0]["lfmt"].ToString (), dr[0]["lfid"].ToString ()) : null;

      foreach (TableRow row in table.Rows)
      {
        if (!(row is TableHeaderRow))
        {
          // Get the index of the row.
          int index = table.Rows.GetRowIndex (row);

          if (index != ignore)
          {
            // Get the dropdown list for this row and save its value.
            DropDownList list = this.get_log_format_control (row);

            if (add_item != null)
              list.Items.Add (add_item);

            if (remove_item != null)
              list.Items.Remove (remove_item);
          }
        }
      }
    }

    /**
     * Helper method to add a new log format to the table. This will create
     * a new row in the table for selecting log formats. If \a use_viewstate
     * is true
     *
     * @param[in]           use_viewstate         Using the view state.
     */
    private void create_new_log_format (ref Table table, int lfid)
    {
      // Create a new log format item for the table.
      TableRow row = new TableRow ();
      table.Rows.Add (row);

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
      format_list.SelectedIndexChanged += new EventHandler (this.onchange_log_format_selection);
      format_list.Width = new Unit (500, UnitType.Pixel);

      // Create the relation cell for the table.
      TableCell relation_cell = new TableCell ();
      row.Cells.Add (relation_cell);

      int index = this.selected_log_formats_.IndexOf (lfid);
      RelationTable relation = null;

      if ((lfid == -1 && this.selected_log_formats_.Count > 0) ||
          (lfid != -1 && index > 0))
      {
        // Insert the default relation table.
        relation = new RelationTable ();
        relation_cell.Controls.Add (relation);

        relation.EnableViewState = true;
      }

      if (lfid != -1)
        return;

      // Insert the log formats into the table.
      DataTable log_formats = this.ds_.Tables[this.formats_table_];

      foreach (DataRow format in log_formats.Rows)
      {
        if (!this.selected_log_formats_.Contains (format["lfid"]))
        {
          string text = format["lfmt"].ToString ();
          string value = format["lfid"].ToString ();

          format_list.Items.Add (new ListItem (text, value));
        }
      }

      // Update the prefix control.
      lfid = int.Parse (format_list.SelectedValue);
      this.set_prefix_text (prefix, lfid);

      // Now, set the selection for the list control.
      this.selected_log_formats_.Add (lfid);

      if (relation != null)
      {
        // Update the casual relation for this format.
        relation.EffectID = lfid;
        relation.LogIDList = (int[])this.selected_log_formats_.ToArray (typeof (int));
        relation.DataSource = this.ds_.Tables[this.relations_table_];

        relation.DataBind ();
      }

      // Finally, update the link for adding more formats.
      if (this.selected_log_formats_.Count == log_formats.Rows.Count)
        this.disable_more_log_format_link ();
    }

    /**
     * Helper method to insert the header row for the log format
     * table.
     *
     * @param[inout]         table          Target table to create header
     */
    private void insert_header_row (ref Table table)
    {
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

      relation.Controls.Add (new LiteralControl ("Causality"));
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

    private DropDownList get_log_format_control (TableRow row)
    {
      return (DropDownList)row.Cells[1].Controls[0];
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

    private ArrayList selected_relations_ = new ArrayList ();
  }
}
