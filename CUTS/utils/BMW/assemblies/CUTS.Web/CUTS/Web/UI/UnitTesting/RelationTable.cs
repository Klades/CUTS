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
    public RelationTable (int effect_id)
    {
      this.effect_id_ = effect_id;
    }

    /**
     * Readonly property for the selected log formats.
     */
    public CUTS.Data.Relation Relation
    {
      get
      {
        this.save_relation (ref this.relation_);
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
    private void save_relation (ref CUTS.Data.Relation relation)
    {
      // Clear the contents of the relation.
      relation.clear ();

      // Get the selected causality index for this object.
      DropDownList list = this.get_causility_list ();
      int causality = int.Parse (list.SelectedValue);

      // Get the names in the text boxes.
      string[] causalities = this.split_variables (this.get_causality_textbox ().Text);
      string[] effects = this.split_variables (this.get_effect_textbox ().Text);

      if (causalities.Length != effects.Length)
        throw new Exception ("Causality and effect list are of different length");

      int length = causalities.Length;

      for (int i = 0; i < length; ++i)
      {
        // Get the variable for the causality.
        string filter = String.Format ("lfid={0} AND varname='{1}'", causality, causalities[i]);
        DataRow[] causaility_rows = this.data_table_.Select (filter);

        // Get the variable for the effect.
        filter = String.Format ("lfid={0} AND varname='{1}'", this.effect_id_, effects[i]);
        DataRow[] effect_rows = this.data_table_.Select (filter);

        // Insert the variables ino the relation.
        relation.add (causaility_rows[0]["variable_id"], effect_rows[0]["variable_id"]);
      }
    }

    /**
     *
     */
    private void save_effect_relation (ref CUTS.Data.Relation relation)
    {
      // Get the names in the effect textbox.
      TextBox text = this.get_effect_textbox ();
      string[] names = this.split_variables (text.Text);

      for (int i = 0; i < names.Length; ++ i)
      {
        string filter = String.Format ("lfid={0} AND varname='{1}'", this.effect_id_, names[i]);
        DataRow[] rows = this.data_table_.Select (filter);

        relation.update_right_value (i, rows[0]["variable_id"]);
      }
    }

    /**
     *
     */
    private string[] split_variables (string value)
    {
      string temp = value.Replace (" ", "");
      return temp.Split (";".ToCharArray (), StringSplitOptions.RemoveEmptyEntries);
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
    public int EffectID
    {
      get
      {
        return this.effect_id_;
      }

      set
      {
        // Make sure the control exists.
        this.EnsureChildControls ();

        // Update the text of the literal control.
        LiteralControl lit = (LiteralControl)this.Controls[4];
        lit.Text = String.Format ("LF{0}. ", value);

        // Empty the contents of the textbox.
        TextBox textbox = (TextBox)this.Controls[5];
        textbox.Text = String.Empty;

        // Save the value.
        this.effect_id_ = value;
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

      // Insert the log format prefix for the right side.
      DropDownList id_list = new DropDownList ();
      this.Controls.Add (id_list);

      id_list.ID = String.Format ("idlist{0}_", this.effect_id_);
      id_list.EnableViewState = true;
      id_list.AutoPostBack = false;

      // Insert the textbox control for the left side.
      TextBox text_lhs = new TextBox ();
      this.Controls.Add (text_lhs);

      text_lhs.EnableViewState = true;
      text_lhs.CausesValidation = false;

      LiteralControl lit_equal = new LiteralControl (" => ");
      this.Controls.Add (lit_equal);

      // Insert the log format prefix for the left side.
      LiteralControl lit_lhs = new LiteralControl (String.Format ("LF{0}. ", this.effect_id_));
      this.Controls.Add (lit_lhs);

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
        this.effect_id_ = (int)state[1];

      if (state[2] != null)
        this.data_table_ = (DataTable)state[2];
    }

    /**
     * Save the view state of the control.
     *
     * @return            The controls view state.
     */
    protected override object SaveViewState ()
    {
      object[] state = new object[3];

      state[0] = base.SaveViewState ();
      state[1] = this.effect_id_;
      state[2] = this.data_table_;

      return state;
    }

    /**
     * Bind the data to the control.
     */
    public override void DataBind ()
    {
      // Make sure the child controls are created.
      this.EnsureChildControls ();

      // Locate the dropdown list and clear its contents. Make sure
      // to save the current selection so we can restore it later.

      DropDownList id_list = (DropDownList)this.Controls[1];
      string selection = id_list.SelectedValue;
      id_list.Items.Clear ();

      // Insert each of the log formats into the listing.
      foreach (int id in this.log_ids_)
      {
        if (id != this.effect_id_)
        {
          String text = String.Format ("LF{0}.", id);
          String value = id.ToString ();

          id_list.Items.Add (new ListItem (text, value));
        }
      }

      // Restore the previous selection.
      if (this.log_ids_.Contains (selection))
        id_list.SelectedValue = selection;
    }

    private DropDownList get_causility_list ()
    {
      return (DropDownList)this.Controls[1];
    }

    private TextBox get_causality_textbox ()
    {
      return (TextBox)this.Controls[2];
    }

    private TextBox get_effect_textbox ()
    {
      return (TextBox)this.Controls[5];
    }

    /**
     * Log format id for the left side of the relation.
     */
    private int effect_id_;

    private DataTable data_table_;

    private ArrayList log_ids_;

    private CUTS.Data.Relation relation_ = new CUTS.Data.Relation ();
  }
}
