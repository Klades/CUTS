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
    public RelationTable (int left)
    {
      this.left_ = left;
    }

    /**
     * Readonly property for the selected log formats.
     */
    public CUTS.Data.Relation Relation
    {
      get
      {
        // First, we need to build the relation from the text boxes.
        TextBox text_lhs = (TextBox)this.Controls[2];
        TextBox text_rhs = (TextBox)this.Controls[5];

        string lhs_value = text_lhs.Text.Replace (" ", "");
        string rhs_value = text_rhs.Text.Replace (" ", "");

        string[] lhs_items = lhs_value.Split (";".ToCharArray (), StringSplitOptions.RemoveEmptyEntries);
        string[] rhs_items = rhs_value.Split (";".ToCharArray (), StringSplitOptions.RemoveEmptyEntries);

        if (lhs_items.Length != rhs_items.Length)
          throw new Exception ("relations are not the same size");

        CUTS.Data.Relation relation = new CUTS.Data.Relation (lhs_items.Length);

        this.update_relations_left (ref relation, lhs_items);
        this.update_relations_right (ref relation, rhs_items);
        return relation;
      }
    }

    private void update_relations_left (ref CUTS.Data.Relation relation, string[] names)
    {
      foreach (string name in names)
      {
        string filter = String.Format ("lfid={0} AND varname='{1}'", this.left_, name);
        DataRow[] rows = this.data_table_.Select (filter);

        relation.add (rows[0]["variable_id"], null);
      }
    }

    private void update_relations_right (ref CUTS.Data.Relation relation, string[] names)
    {
      DropDownList list = (DropDownList)this.Controls[4];
      int right = int.Parse (list.SelectedValue);

      for (int i = 0; i < names.Length; ++i)
      {
        string filter = String.Format ("lfid={0} AND varname='{0}'", right, names[i]);
        DataRow[] rows = this.data_table_.Select (filter);

        relation.update_right_value (i, rows[0]["variable_id"]);
      }
    }

    public int [] LogIDList
    {
      get
      {
        return (int [])this.log_ids_.ToArray (typeof (int));
      }

      set
      {
        this.log_ids_ = new ArrayList (value);
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
        // Make sure the control exists.
        this.EnsureChildControls ();

        // Update the text of the literal control.
        LiteralControl lit = (LiteralControl)this.Controls[1];
        lit.Text = String.Format ("LF{0}. ", value);

        // Empty the contents of the textbox.
        TextBox textbox = (TextBox)this.Controls[2];
        textbox.Text = String.Empty;

        // Save the value.
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
        this.EnsureChildControls ();
        DropDownList id_list = (DropDownList)this.Controls[4];

        return int.Parse (id_list.SelectedValue);
      }

      set
      {
        // Make sure the control exists.
        this.EnsureChildControls ();

        // Update the text of the literal control.
        DropDownList list = (DropDownList)this.Controls[4];
        list.SelectedValue = value.ToString ();
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
      // Insert the where statement.
      LiteralControl lit_where = new LiteralControl (" where ");
      this.Controls.Add (lit_where);

      // Insert the log format prefix for the left side.
      LiteralControl lit_lhs = new LiteralControl (String.Format ("LF{0}. ", this.left_));
      this.Controls.Add (lit_lhs);

      // Insert the textbox control for the left side.
      TextBox text_lhs = new TextBox ();
      this.Controls.Add (text_lhs);
      text_lhs.EnableViewState = true;
      text_lhs.CausesValidation = false;

      LiteralControl lit_equal = new LiteralControl (" => ");
      this.Controls.Add (lit_equal);

      // Insert the log format prefix for the right side.
      DropDownList id_list = new DropDownList ();
      this.Controls.Add (id_list);

      id_list.ID = String.Format ("idlist{0}_", this.left_);
      id_list.EnableViewState = true;

      // Insert the textbox control for the right side.
      TextBox text_rhs = new TextBox ();
      this.Controls.Add (text_rhs);
      text_rhs.EnableViewState = true;
      text_rhs.CausesValidation = false;
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
        this.left_ = (int)state[1];

      if (state[3] != null)
        this.data_table_ = (DataTable)state[3];
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
      state[1] = this.left_;
      state[3] = this.data_table_;

      return state;
    }

    /**
     *
     */
    protected override void Render (HtmlTextWriter writer)
    {
      this.Page.ClientScript.RegisterForEventValidation (this.Controls[2].UniqueID);
      this.Page.ClientScript.RegisterForEventValidation (this.Controls[5].UniqueID);

      base.Render (writer);
    }

    /**
     * Bind the data to the control.
     */
    public override void DataBind ()
    {
      this.EnsureChildControls ();

      DropDownList id_list = (DropDownList)this.Controls[4];

      foreach (int id in this.log_ids_)
      {
        String text = String.Format ("LF{0}.", id);
        String value = id.ToString ();

        id_list.Items.Add (new ListItem (text, value));
      }
   }

    /**
     * Log format id for the left side of the relation.
     */
    private int left_;

    private DataTable data_table_;

    private ArrayList log_ids_;

    private CUTS.Data.Relation relation_ = new CUTS.Data.Relation ();
  }
}
