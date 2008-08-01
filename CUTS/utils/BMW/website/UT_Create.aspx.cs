using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using MySql.Data.MySqlClient;
using System.Text.RegularExpressions;
using System.Drawing;
using Actions.UnitTestActions;

/**
 * @class UT_Create
 *
 * Code-behind class for the UT_Create.aspx webpage.
 */
public partial class UT_Create : System.Web.UI.Page
{
  /**
   * Reference to master page used to ease sending messages to the user.
   */
  private CUTS.Master master_;

  /**
   * The minimum width for all of the dynamically bound controls on
   * this page.
   */
  private static double Default_Width_ = 300.0;

  protected void Page_Load (object sender, EventArgs e)
  {
    master_ = (CUTS.Master)Master;

    if (IsPostBack)
      return;

    // Do initial Load of Log Formats
    this.load_log_formats ();

    // Hide the info for the second Log Format
    this.is_using_both_log_formats = false;
  }

  protected void onclick_toggle_second_log_format_visibility (object sender, EventArgs e)
  {
    // If visible, hide.
    // If invisible, show
    if (this.is_using_both_log_formats)
      this.is_using_both_log_formats = false;
    else
      this.is_using_both_log_formats = true;
  }

  protected void onclick_submit (object sender, EventArgs e)
  {
    ArrayList lfids = new ArrayList ();

    // Check the first log format
    if (this.Log_Format_List_1.SelectedIndex == -1)
    {
      // We are only using one LF, and it is invalid
      this.master_.show_error_message ("The first log format is invalid");
    }
    else if (this.is_using_both_log_formats == true &&
             this.Log_Format_List_2.SelectedIndex == -1)
    {
      this.master_.show_error_message ("The second log format is invalid");
    }
    else
    {
      // We passed all tests that could involve the first log format,
      // so we will now add it
      lfids.Add (Log_Format_List_1.SelectedValue);


      // Check if second LF is used
      // We have already checked that it is valid
      if (this.is_using_both_log_formats)
        lfids.Add (Log_Format_List_2.SelectedValue);

      // Validate all inputs.
      // This should eventually use CustomValidators, but in interest of time
      //    it is manual for now. There is no speed loss by doing it
      //    this way.
      if (UT_name.Text.Length < 3 ||
          UT_desc.Text.Length < 3 ||
          UT_fail.Text.Length < 1 ||
          UT_warn.Text.Length < 1 ||
          UT_eval.Text.Length < 5 ||
          get_mysql_comparison (UT_fail_comp.Text) == String.Empty ||
          get_mysql_comparison (UT_warn_comp.Text) == String.Empty ||
          this.aggr_function_.SelectedIndex == -1)
      {
        this.master_.show_error_message ("All fields are required, minimum length for " +
          "a name or description is three characters.");
        return;
      }


      Hashtable variables = new Hashtable ();
      variables.Add ("Name", UT_name.Text);
      variables.Add ("Description", UT_desc.Text);
      variables.Add ("FailComparison", get_mysql_comparison (UT_fail_comp.Text));
      variables.Add ("WarnComparison", get_mysql_comparison (UT_warn_comp.Text));
      variables.Add ("FailValue", UT_fail.Text);
      variables.Add ("WarnValue", UT_warn.Text);
      variables.Add ("Evaluation", UT_eval.Text);
      variables.Add ("LFIDs", lfids.ToArray ());
      variables.Add ("Aggregration_Func", this.aggr_function_.SelectedValue);

      // Note Groups are disabled for now
      /*
      string[] groups = new string[1];
      groups[0] = "test_number";
      variables.Add( "Groups", groups ); */


      // Add the relationship Information
      variables.Add ("is_using_both_log_formats", this.is_using_both_log_formats);
      if (this.is_using_both_log_formats)
      {
        if (Relation_Variable_1.SelectedValue == Relation_Variable_2.SelectedValue)
        {
          this.master_.show_error_message ("A variable cannot be compared against itself!");
          return;
        }

        variables.Add ("Relation_Variable_1", Relation_Variable_1.SelectedValue);
        variables.Add ("Relation_Variable_2", Relation_Variable_2.SelectedValue);
      }

      try
      {
        UnitTestActions.Insert_New_Unit_Test (variables);
        this.master_.show_info_message ("Successfully created new unit test");
      }
      catch (Exception ex)
      {
        this.master_.show_error_message (ex.Message);
        this.master_.show_error_message ("Failed to create new unit test");
      }
    }
  }

  private string get_mysql_comparison (string comparison)
  {
    // They are used directly in the query
    switch (comparison)
    {
      case "less":
        return @"<";
      case "greater":
        return @">";
      case "less_equal":
        return @"<=";
      case "greater_equal":
        return @">=";
      case "equal":
        return @"=";
      case "not_equal":
        return @"<>";
      default:
        master_.show_error_message ("The warn or fail comparison had a problem." +
          "Please refresh the page and try again.");
        return String.Empty;
    }
  }

  private void load_log_formats ()
  {
    string sql = "SELECT lfid,lfmt FROM logformatdesc";
    DataTable data = execute_mysql_adapter (sql);

    // Load first DDL of LogFormats
    Log_Format_List_1.DataSource = data;
    Log_Format_List_1.DataTextField = "lfmt";
    Log_Format_List_1.DataValueField = "lfid";
    Log_Format_List_1.DataBind ();

    // Load second
    Log_Format_List_2.DataSource = data;
    Log_Format_List_2.DataTextField = "lfmt";
    Log_Format_List_2.DataValueField = "lfid";
    Log_Format_List_2.DataBind ();

    // Ensure the width
    ensure_width (Log_Format_List_1);
    ensure_width (Log_Format_List_2);
  }

  private void load_relation_form ()
  {
    if (is_using_both_log_formats == false)
      return;

    // Ensure the validity of both LF's selected
    if (is_valid_selection (this.Log_Format_List_1) == false ||
              is_valid_selection (this.Log_Format_List_2) == false)
    {
      master_.show_error_message ("Before the relationship lists can be populated," +
        "you must select two valid logformats.");

      // Ensure the width of both DropDownLists
      ensure_width (Relation_Variable_1);
      ensure_width (Relation_Variable_2);
      return;
    }

    // show the relation form
    this.is_relation_visible = true;

    // Grab the extended variable names and the variable id's for the first
    // Log Format
    string sql = "CALL Get_LFID_info('" +
      this.Log_Format_List_1.SelectedValue + "');";
    DataTable dt = execute_mysql_adapter (sql);

    // Bind the data
    Relation_Variable_1.DataSource = dt;
    Relation_Variable_1.DataTextField = "extended_varname";
    Relation_Variable_1.DataValueField = "variable_id";
    Relation_Variable_1.DataBind ();

    // Grab the extended variable names and the variable id's for the second
    // Log Format
    sql = "CALL Get_LFID_info('" + Log_Format_List_2.SelectedValue + "');";
    dt = execute_mysql_adapter (sql);

    // Bind the data
    Relation_Variable_2.DataSource = dt;
    Relation_Variable_1.DataTextField = "extended_varname";
    Relation_Variable_1.DataValueField = "variable_id";
    Relation_Variable_2.DataBind ();

    // Ensure the widths of the DropDownLists
    ensure_width (Relation_Variable_1);
    ensure_width (Relation_Variable_2);
  }

  protected void onchange_log_format_list_1 (object sender, EventArgs e)
  {
    if (!this.is_valid_selection (this.Log_Format_List_1))
      return;

    this.Log_Format_1_Prefix.Text =
      "variable prefix: LF" + this.Log_Format_List_1.SelectedValue;

    load_relation_form ();
  }

  protected void onchange_log_format_list_2 (object sender, EventArgs e)
  {
    if (this.is_valid_selection (this.Log_Format_List_2) == false)
      return;

    Log_Format_2_Prefix.Text = "Prefix Variables with LF" +
      Log_Format_List_2.SelectedValue;

    load_relation_form ();
  }

  /**
   * Ensures the width for any dynamically loaded control on the page.
   *
   * @param d     The Dropdownlist to ensure the width of. If another type
   *              of dynamic databound control is added, then an
   *              override will need to be created.
   */
  private void ensure_width (DropDownList d)
  {
    if (d.Width.Value < Default_Width_)
      d.Width = new Unit (Default_Width_);
  }

  /**
   * This is a decoupled way to get or set the relation between two log
   * formats to being visible or not being visible. This should be true
   * when trying to use two Log Formats, and false when only trying to
   * use one.
   *
   * @retval true   Indicates the relationship form is visible.
   * @retval false  Indicates the relationship form is not visible.
   */
  private bool is_relation_visible
  {
    get
    {
      return this.relation_head.Visible;
    }

    set
    {
      relation_head.Visible = value;
      Relation_Variable_1.Visible = value;
      Relation_Variable_2.Visible = value;
      relation_text.Visible = value;

      if (value == true)
      {
        this.ensure_width (Relation_Variable_1);
        this.ensure_width (Relation_Variable_2);
      }
    }
  }


  /**
   * Provides a quick check that a DropDownList has a selection which
   * is valid. Note that this assumes the DDL has a first item similar to
   * 'Please Select One'.
   *
   * @param d       The DropDownList to check.
   *
   * @retval true   The selection is valid and can be safely used elsewhere.
   * @retval false  The selection is invalid and cannot be safey
   *                used elsewhere.
   */
  private bool is_valid_selection (DropDownList d)
  {
    if (d.SelectedIndex < 1)
      return false;
    return true;
  }

  /**
   * Provides a decoupled way to see if both Log Formats are being used, or
   * if just one is being used.
   *
   * @retval true     Both Log Formats are being used.
   * @retval false    Only the first Log Format is being used.
   */
  private bool is_using_both_log_formats
  {
    get { return Log_Format_List_2.Visible; }
    set
    {
      Log_Format_2_Prefix.Visible = value;
      Log_Format_List_2.Visible = value;
      is_relation_visible = value;

      if (value == true)
        more_log_formats_.Text = "I only need one log format";
      else
        more_log_formats_.Text = "I need more log formats";
    }
  }

  /**
   * Safely execute a MySQL statement. This manages the connection
   * and can throw an Argument Exception indicating what the
   * sql attempted to execute was.
   *
   * @param sql    The statement to be executed.
   */
  private DataTable execute_mysql_adapter (string sql)
  {
    MySqlConnection conn = new MySqlConnection (ConfigurationManager.AppSettings ["MySQL"]);
    conn.Open ();
    MySqlDataAdapter da = new MySqlDataAdapter (sql, conn);
    DataSet ds = new DataSet ();
    try { da.Fill (ds); }
    catch { throw new ArgumentException ("The sql executed was : " + sql); }
    finally { conn.Close (); }

    return ds.Tables [0];
  }
}