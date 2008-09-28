// -*- C# -*-

//=============================================================================
/**
 * @file          Grouping.cs
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
   * @class Grouping
   *
   * Custom control for inputing grouping information for a unit
   * test. The user is able to input the group variables as the
   * control will convert the readable text into variable ids.
   */
  public class Grouping : CompositeControl, INamingContainer
  {
    /**
     * Default constructor
     */
    public Grouping ()
    {

    }

    /**
     * Ids of the group variables.
     */
    public int[] Variables
    {
      get
      {
        // Make sure the controls are created.
        this.EnsureChildControls ();

        // Save the variable for the grouping.
        this.save_group_variables ();

        return (int[])this.grouping_.ToArray (typeof (int));
      }
    }

    /**
     * Attribute for setting/getting the data source. The data source
     * contains the information used to lookup the variable ids given
     * their fully qualified name.
     */
    public object DataSource
    {
      get
      {
        return this.dataset_;
      }

      set
      {
        this.dataset_ = (DataSet)value;
      }
    }

    /**
     * Attribute for setting/getting the data member. The data member
     * defines what table in the data source to use when converting the
     * text to ids.
     */
    public string DataMember
    {
      get
      {
        return this.member_;
      }

      set
      {
        this.member_ = value;
      }
    }

    /**
     * Bind the data to the control. This will force the control to
     * render itself.
     */
    public override void DataBind ()
    {
      this.EnsureChildControls ();
    }

    /**
     * Create the child controls for this custom control. This is
     * invoked by the underlying framework.
     */
    protected override void CreateChildControls ()
    {
      // Create the label for the control.
      Label label = new Label ();
      this.Controls.Add (label);

      label.Text = "Group by: ";
      label.CssClass = "title";

      // Insert the text box for inputing the groups.
      TextBox text = new TextBox ();
      this.Controls.Add (text);

      text.Width = this.Width;
    }

    /**
     * Load the view state of the control.
     */
    protected override void LoadViewState (object savedState)
    {
      object[] state = (object[])savedState;

      if (state[0] != null)
        base.LoadControlState (state[0]);

      if (state[1] != null)
        this.grouping_ = (ArrayList)state[1];

      if (state[2] != null)
        this.dataset_ = (DataSet)state[2];

      if (state[3] != null)
        this.member_ = (string)state[3];
    }

    /**
     * Save the view state of the control.
     */
    protected override object SaveViewState ()
    {
      object[] state = new object[4];

      state[0] = base.SaveControlState ();
      state[1] = this.grouping_;
      state[2] = this.dataset_;
      state[3] = this.member_;

      return state;
    }

    /**
     * Helper method to convert the text variable into their
     * corresponding ids.
     */
    private void save_group_variables ()
    {
      // Clear the groupings.
      this.grouping_.Clear ();

      // Get the variables from the text box.
      TextBox textbox = (TextBox)this.Controls[1];
      string text = textbox.Text.Replace (" ", "");

      string[] names = text.Split (";".ToCharArray (), StringSplitOptions.RemoveEmptyEntries);

      // Locate the ids for the variables.
      DataTable table = this.dataset_.Tables[this.member_];

      foreach (string name in names)
      {
        string filter = String.Format ("fq_name='{0}'", name);
        DataRow[] rows = table.Select (filter);

        this.grouping_.Add (rows[0]["variable_id"]);
      }
    }

    /**
     * List id of variables in the grouping.
     */
    private ArrayList grouping_ = new ArrayList ();

    /**
     * Data set use to lookup variable ids.
     */
    private DataSet dataset_;

    /**
     * Name of the data table in the dataset.
     */
    private string member_;
  }
}
