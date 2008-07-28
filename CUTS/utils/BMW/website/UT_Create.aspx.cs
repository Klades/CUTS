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

public partial class UT_Create : System.Web.UI.Page
{
  /**
   * Reference to master page used to ease sending messages to the user. 
   */
  private CUTS.BMW_Master m_;

  /**
   * The minimum width for all of the dynamically bound controls on 
   * this page. 
   */
  private static double Default_Width_ = 300.0;

  protected void Page_Load ( object sender, EventArgs e )
  {
    m_ = (CUTS.BMW_Master)Master;

    if (IsPostBack)
      return;

    // Do initial Load of Log Formats
    this.load_Log_Formats();

    // Hide the info for the second Log Format
    this.UsingBothLogFormats = false;
  }

  protected void OnClick_Toggle_Second_Log_Format_Visibility ( object sender, EventArgs e )
  {
    // If visible, hide.
    // If invisible, show
    if (this.UsingBothLogFormats)
      this.UsingBothLogFormats = false;    
    else
      this.UsingBothLogFormats = true;
  }

  protected void OnClick_btn_Submit ( object sender, EventArgs e )
  {
    ArrayList lfids = new ArrayList();

    // Check the first log format
    if (this.UsingBothLogFormats == false &&
      this.IsValidSelection( Log_Format_List_1 ) == false)
    {
      // We are only using one LF, and it is invalid
      m_.show_error_message( "The Log Format is not valid" );
      return;
    }
    else if (this.UsingBothLogFormats == true &&
      (this.IsValidSelection( Log_Format_List_1 ) == false ||
       this.IsValidSelection( Log_Format_List_2 ) == false))
    {
      // We are using both log formats, but one is invalid
      m_.show_error_message( "One of the Log Formats you have selected is " +
        "invalid." );
      return;
    }

    // We passed all tests that could involve the first log format, 
    // so we will now add it
    lfids.Add( Log_Format_List_1.SelectedValue );


    // Check if second LF is used
    // We have already checked that it is valid
    if (this.UsingBothLogFormats)
      lfids.Add( Log_Format_List_2.SelectedValue );

    // Validate all inputs.
    // This should eventually use CustomValidators, but in interest of time
    //    it is manual for now. There is no speed loss by doing it 
    //    this way.
    if (UT_name.Text.Length < 3 ||
        UT_desc.Text.Length < 3 ||
        UT_fail.Text.Length < 1 ||
        UT_warn.Text.Length < 1 ||
        UT_eval.Text.Length < 5 ||
        Get_MySQL_Comparison( UT_fail_comp.Text ) == String.Empty ||
        Get_MySQL_Comparison( UT_warn_comp.Text ) == String.Empty ||
        IsValidSelection(this.Aggregrate_Funtion) == false)
    {
      m_.show_error_message( "All fields are required, minimum length for " +
        "a name or description is three characters." );
      m_.show_error_message( "Minimum length for evaluation field is " +
        "five characters" );
      return;
    }


    Hashtable variables = new Hashtable();
    variables.Add( "Name", UT_name.Text );
    variables.Add( "Description", UT_desc.Text );
    variables.Add( "FailComparison", Get_MySQL_Comparison( UT_fail_comp.Text ) );
    variables.Add( "WarnComparison", Get_MySQL_Comparison( UT_warn_comp.Text ) );
    variables.Add( "FailValue", UT_fail.Text );
    variables.Add( "WarnValue", UT_warn.Text );
    variables.Add( "Evaluation", UT_eval.Text );
    variables.Add( "LFIDs", lfids.ToArray() );
    variables.Add( "Aggregration_Func", this.Aggregrate_Funtion.SelectedValue );

    // Note Groups are disabled for now
    /*
    string[] groups = new string[1];
    groups[0] = "test_number";
    variables.Add( "Groups", groups ); */


    // Add the relationship Information 
    variables.Add( "UsingBothLogFormats", this.UsingBothLogFormats );
    if (this.UsingBothLogFormats)
    {
      if (Relation_Variable_1.SelectedValue == Relation_Variable_2.SelectedValue)
      {
        m_.show_error_message( "A variable cannot be compared against itself!" );
        return;
      }
      variables.Add( "Relation_Variable_1", Relation_Variable_1.SelectedValue );
      variables.Add( "Relation_Variable_2", Relation_Variable_2.SelectedValue );
    }

    try
    {
      UnitTestActions.Insert_New_Unit_Test( variables );
    }
    catch
    {
      m_.show_error_message( "There was a problem adding the UT" );
      return;
    }
    m_.show_info_message( "UT added successfully!" );
  }

  private string Get_MySQL_Comparison ( string comparison )
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
        m_.show_error_message( "The warn or fail comparison had a problem." +
          "Please refresh the page and try again." );
        return String.Empty;
    }
  }

  private void load_Log_Formats ()
  {
    string sql = "SELECT lfid,lfmt FROM logformatdesc";
    DataTable data = ExecuteMySqlAdapter( sql );

    // Load first DDL of LogFormats
    Log_Format_List_1.DataSource = data;
    Log_Format_List_1.DataTextField = "lfmt";
    Log_Format_List_1.DataValueField = "lfid";
    Log_Format_List_1.DataBind();
    Log_Format_List_1.Items.Insert( 0, "Please choose a Log Format . . ." );

    // Load second
    Log_Format_List_2.DataSource = data;
    Log_Format_List_2.DataTextField = "lfmt";
    Log_Format_List_2.DataValueField = "lfid";
    Log_Format_List_2.DataBind();
    Log_Format_List_2.Items.Insert( 0, "Please choose a Log Format . . ." );

    // Ensure the width
    Ensure_Width( Log_Format_List_1 );
    Ensure_Width( Log_Format_List_2 );
  }

  private void load_Relation_Form ()
  {
    if (UsingBothLogFormats == false)
      return;

    // Ensure the validity of both LF's selected
    if (IsValidSelection( this.Log_Format_List_1 ) == false ||
              IsValidSelection( this.Log_Format_List_2 ) == false)
    {
      m_.show_error_message( "Before the relationship lists can be populated,"+
        "you must select two valid logformats." );
      
      // Ensure the width of both DropDownLists
      Ensure_Width( Relation_Variable_1 );
      Ensure_Width( Relation_Variable_2 );
      return;
    }

    // show the relation form
    this.RelationsVisible = true;

    // Grab the extended variable names and the variable id's for the first
    // Log Format
    string sql = "CALL Get_LFID_info('" + 
      this.Log_Format_List_1.SelectedValue + "');";
    DataTable dt = ExecuteMySqlAdapter( sql );

    // Bind the data
    Relation_Variable_1.DataSource = dt;
    Relation_Variable_1.DataTextField = "extended_varname";
    Relation_Variable_1.DataValueField = "variable_id";
    Relation_Variable_1.DataBind();

    // Grab the extended variable names and the variable id's for the second
    // Log Format
    sql = "CALL Get_LFID_info('" + Log_Format_List_2.SelectedValue + "');";
    dt = ExecuteMySqlAdapter( sql );

    // Bind the data
    Relation_Variable_2.DataSource = dt;
    Relation_Variable_1.DataTextField = "extended_varname";
    Relation_Variable_1.DataValueField = "variable_id";
    Relation_Variable_2.DataBind();

    // Ensure the widths of the DropDownLists
    Ensure_Width( Relation_Variable_1 );
    Ensure_Width( Relation_Variable_2 );
  }

  protected void OnChange_Log_Format_List_1 ( object sender, EventArgs e )
  {
    if (this.IsValidSelection(this.Log_Format_List_1) == false)
      return;

    this.Log_Format_1_Prefix.Text = "Prefix Variables with LF" + 
     this.Log_Format_List_1.SelectedValue;

    load_Relation_Form();
  }

  protected void OnChange_Log_Format_List_2 ( object sender, EventArgs e )
  {
    if (this.IsValidSelection(this.Log_Format_List_2) == false)
      return;

    Log_Format_2_Prefix.Text = "Prefix Variables with LF" + 
      Log_Format_List_2.SelectedValue;

    load_Relation_Form();
  }

  /**
   * Ensures the width for any dynamically loaded control on the page.
   * 
   * @param d     The Dropdownlist to ensure the width of. If another type
   *              of dynamic databound control is added, then an 
   *              override will need to be created.
   */
  private void Ensure_Width (DropDownList d)
  {
    if (d.Width.Value < Default_Width_)
      d.Width = new Unit( Default_Width_ );
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
  private bool RelationsVisible
  {
    get { return this.relation_head.Visible; }
    set
    {
      relation_head.Visible = value;
      Relation_Variable_1.Visible = value;
      Relation_Variable_2.Visible = value;
      relation_text.Visible = value;
      Spacer1.Visible = value;
      Spacer2.Visible = value;

      if (value == true)
      {
        Ensure_Width( Relation_Variable_1 );
        Ensure_Width( Relation_Variable_2 );
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
  private bool IsValidSelection ( DropDownList d )
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
  private bool UsingBothLogFormats
  {
    get { return Log_Format_List_2.Visible; }
    set
    {
      Log_Format_2_Prefix.Visible = value;
      Log_Format_List_2.Visible = value;
      RelationsVisible = value;

      if (value == true)
        btn_more_lfs.Text = "[-] I only need one Log Format";
      else
        btn_more_lfs.Text = "[+] I need more Log Formats";
    }
  }
  
  /**
   * Safely execute a MySQL statement. This manages the connection
   * and can throw an Argument Exception indicating what the 
   * sql attempted to execute was. 
   * 
   * @param sql    The statement to be executed.
   */
  private DataTable ExecuteMySqlAdapter ( string sql )
  {
    MySqlConnection conn = new MySqlConnection( ConfigurationManager.AppSettings["MySQL"] );
    conn.Open();
    MySqlDataAdapter da = new MySqlDataAdapter( sql, conn );
    DataSet ds = new DataSet();
    try { da.Fill( ds ); }
    catch { throw new ArgumentException( "The sql executed was : " + sql ); }
    finally { conn.Close(); }

    return ds.Tables[0];
  }
}