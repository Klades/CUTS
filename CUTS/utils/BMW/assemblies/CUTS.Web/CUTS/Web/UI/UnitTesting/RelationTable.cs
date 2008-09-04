// -*- C# -*-

//=============================================================================
/**
 * @file          RelationTable.cs
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
  public class RelationTable : CompositeControl, INamingContainer
  {
    /**
     * Default constructor.
     */
    public RelationTable ()
    {

    }

    /**
     * Initializing constructor.
     */
    public RelationTable (int left, int right)
    {
      this.left_ = left;
      this.right_ = right;
    }

    /**
     * Readonly property for the selected log formats.
     */
    public CUTS.Data.Relation Relation
    {
      get
      {
        return this.relation_;
      }

      set
      {
        this.relation_ = value;
      }
    }

    /**
     *
     */
    public int LeftID
    {
      get
      {
        return this.left_;
      }

      set
      {
        this.left_ = value;
      }
    }

    /**
     *
     */
    public int RightID
    {
      get
      {
        return this.right_;
      }

      set
      {
        this.right_ = value;
      }
    }

    /**
     *
     */
    public object DataSource
    {
      get
      {
        return this.data_table_;
      }

      set
      {
        this.data_table_ = (DataTable)value;
      }
    }

    /**
     *
     */
    protected override void CreateChildControls ()
    {
      Table table = new Table ();
      this.Controls.Add (table);

      for (int i = 0; i < this.relation_.Count; ++ i)
        this.add_new_relation (table, null, null);

      LinkButton link = new LinkButton ();
      this.Controls.Add (link);

      link.Text = "more relations";
      link.CausesValidation = false;
      link.Click += new EventHandler(this.onclick_more_relations);
    }

    /**
     * Load the view state of the control.
     *
     * @param[in]         vstate        Saved view state.
     */
    protected override void LoadViewState (object vstate)
    {
      object[] state = (object[])vstate;

      if (state[0] != null)
        base.LoadViewState (state[0]);

      if (state[1] != null)
        this.relation_ = (CUTS.Data.Relation)state[1];

      if (state[2] != null)
        this.left_ = (int)state[2];

      if (state[3] != null)
        this.right_ = (int)state[3];

      if (state[4] != null)
        this.data_table_ = (DataTable)state[4];
    }

    /**
     * Save the view state of the control.
     *
     * @return            The controls view state.
     */
    protected override object SaveViewState ()
    {
      object[] state = new object[5];

      state[0] = base.SaveViewState ();
      state[1] = this.relation_;
      state[2] = this.left_;
      state[3] = this.right_;
      state[4] = this.data_table_;

      return state;
    }

    /**
     *
     */
    protected override void Render (HtmlTextWriter writer)
    {
      base.Render (writer);

      Table table = (Table)this.Controls[0];

      foreach (TableRow row in table.Rows)
      {
        // Register the dropdown list.
        this.Page.ClientScript.RegisterForEventValidation (row.Cells[0].Controls[0].UniqueID);
        this.Page.ClientScript.RegisterForEventValidation (row.Cells[2].Controls[0].UniqueID);
      }

      // Register the link.
      this.Page.ClientScript.RegisterForEventValidation (this.Controls[1].UniqueID);
    }

    /**
     * Bind the data to the control.
     */
    public override void DataBind ()
    {
      // Get the table for showing the relations.
      Table table = (Table)this.Controls[0];

      // Partition the relations into their respective sides.
      DataTable lhs, rhs;
      this.get_relations (out lhs, out rhs);

      // Clear the data structure and control.
      this.relation_.clear ();
      table.Rows.Clear ();

      // Insert a dummy value.
      this.relation_.add (null, null);

      // Now, insert the real relation.
      this.add_new_relation (table, lhs, rhs);
    }

    /**
     *
     */
    private void onclick_more_relations (object sender, EventArgs e)
    {
      // Insert a dummy relation in the data set.
      this.relation_.add (null, null);

      // Get the data for this relation.
      DataTable lhs, rhs;
      this.get_relations (out lhs, out rhs);

      // Insert a new relation into the cell.
      Table table = (Table)this.Controls[0];
      this.add_new_relation (table, lhs, rhs);
    }

    /**
     *
     */
    private void get_relations (out DataTable lhs, out DataTable rhs)
    {
      // Define the filters for either side of the relation.
      string lhs_filter = String.Format ("lfid = {0}", this.left_);
      string rhs_filter = String.Format ("lfid = {0}", this.right_);

      // Select the variable for either side of the relation.
      DataRow[] lhs_rows = this.data_table_.Select (lhs_filter);
      DataRow[] rhs_rows = this.data_table_.Select (rhs_filter);

      // Build the data table for the lhs relation.
      lhs = this.data_table_.Clone ();

      foreach (DataRow lhs_row in lhs_rows)
      {
        // Create a new for the data table.
        DataRow lhs_new = lhs.NewRow ();
        lhs_new.ItemArray = lhs_row.ItemArray;

        // Insert the new row into the data table.
        lhs.Rows.Add (lhs_new);
      }

      // Build the data table for the lhs relation.
      rhs = this.data_table_.Clone ();

      foreach (DataRow rhs_row in rhs_rows)
      {
        // Create a new for the data table.
        DataRow rhs_new = rhs.NewRow ();
        rhs_new.ItemArray = rhs_row.ItemArray;

        // Insert the new row into the data table.
        rhs.Rows.Add (rhs_new);
      }
    }

    /**
     *
     */
    private void ondatabound_relation_lhs (object sender, EventArgs e)
    {
      // Get the selected value.
      DropDownList list = (DropDownList)sender;
      int value = int.Parse (list.SelectedValue);

      // Update the value in the relation.
      int index = this.get_index (list);
      this.relation_.update_left_value (index, value);
    }

    /**
     *
     */
    private void ondatabound_relation_rhs (object sender, EventArgs e)
    {
      // Get the selected value.
      DropDownList list = (DropDownList)sender;
      int value = int.Parse (list.SelectedValue);

      // Update the value in the relation.
      int index = this.get_index (list);
      this.relation_.update_right_value (index, value);
    }

    /**
     *
     */
    private void onchange_relation_lhs (object sender, EventArgs e)
    {
      DropDownList list = (DropDownList)sender;
      int value = int.Parse (list.SelectedValue);

      int index = this.get_index (list);
      this.relation_.update_left_value (index, value);
    }

    /**
     *
     */
    private void onchange_relation_rhs (object sender, EventArgs e)
    {
      DropDownList list = (DropDownList)sender;
      int value = int.Parse (list.SelectedValue);

      int index = this.get_index (list);
      this.relation_.update_right_value (index, value);
    }

    /**
     *
     */
    private int get_index (DropDownList list)
    {
      // Get the placeholder for this relation.
      TableCell cell = (TableCell)list.Parent;
      TableRow row = (TableRow)cell.Parent;
      Table table = (Table)row.Parent;

      return table.Rows.GetRowIndex (row);
    }

    /**
     *
     */
    private void add_new_relation (Table table, DataTable lhs, DataTable rhs)
    {
      TableRow relation_row = new TableRow ();
      table.Rows.Add (relation_row);

      // Prepare the left side of the relation.
      TableCell lhs_cell = new TableCell ();
      relation_row.Cells.Add (lhs_cell);

      DropDownList lhs_list = new DropDownList ();
      lhs_cell.Controls.Add (lhs_list);

      // Insert the equal sign for the relation.
      TableCell eq_cell = new TableCell ();
      relation_row.Cells.Add (eq_cell);

      eq_cell.Controls.Add (new LiteralControl (" = "));

      // Prepare the right side of the relation.
      TableCell rhs_cell = new TableCell ();
      relation_row.Cells.Add (rhs_cell);

      DropDownList rhs_list = new DropDownList ();
      rhs_cell.Controls.Add (rhs_list);

      // Set the data source for the control.
      lhs_list.AutoPostBack = true;
      lhs_list.CausesValidation = false;
      lhs_list.EnableViewState = true;
      lhs_list.SelectedIndexChanged += new EventHandler (this.onchange_relation_lhs);
      lhs_list.DataBound += new EventHandler (this.ondatabound_relation_lhs);

      if (lhs != null)
      {
        lhs_list.DataSource = lhs;
        lhs_list.DataValueField = "variable_id";
        lhs_list.DataTextField = "varname";
        lhs_list.DataBind ();
      }

      rhs_list.AutoPostBack = true;
      rhs_list.CausesValidation = false;
      rhs_list.EnableViewState = true;
      rhs_list.SelectedIndexChanged += new EventHandler (this.onchange_relation_rhs);
      rhs_list.DataBound += new EventHandler (this.ondatabound_relation_rhs);

      if (rhs != null)
      {
        // Set the data source for the control.
        rhs_list.DataSource = rhs;
        rhs_list.DataValueField = "variable_id";
        rhs_list.DataTextField = "fq_name";
        rhs_list.DataBind ();
      }
    }

    /**
     * Log format id for the left side of the relation.
     */
    private int left_;

    /**
     * Log format id for the right side of the relation.
     */
    private int right_;

    /**
     * The value of the relation.
     */
    private CUTS.Data.Relation relation_ = new CUTS.Data.Relation ();

    private DataTable data_table_;
  }
}
