using System;
using System.Text;
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
using Actions.UnitTestActions;
using Actions.LogFormatActions;

public partial class Unit_Testing : System.Web.UI.Page
{
  private double DEFAULT_WIDTH = 300;

  private CUTS.BMW_Master master_;

  protected void Page_Load (object sender, EventArgs e)
  {
    // used to ease creating messages
    this.master_ = (CUTS.BMW_Master)Master;

    if (IsPostBack)
      return;

    // Initially set the indices to 0. The norm for DataBound controls
    // is -1, but once they are bound you cannot manually set them to -1,
    // because it is out of range. This prevents unwanted firings of the
    // Selected Index Changed event
    Add_Existing_Package.SelectedIndex = 0;
    Add_Existing_Unit_Test.SelectedIndex = 0;

    this.reload_all_data ();
  }

  private void reload_all_data ()
  {
    // If any of the steps fail,
    // enter quiet mode to stop reporting the
    // entire cascade of errors that result
    if (false == load_Test_Suites ())
      this.master_.InQuietMode = true;
    this.Existing_Test_Suites.SelectedIndex = 0;

    if (false == load_Packages ())
      this.master_.InQuietMode = true;
    this.Test_Suite_Packages_List.SelectedIndex = 0;

    load_unit_tests ();

    this.master_.InQuietMode = false;
  }
  private bool load_Test_Suites ()
  {
    // Load Existing Test Suites
    DataTable dt = UnitTestActions.Get_All_Test_Suites ();

    if (dt.Rows.Count == 0)
    {
      this.master_.show_info_message ("You do not have a Test Suite Created! Please create one.");
      ensure_Test_Suite_Width ();
      return false;
    }

    // Bind Data
    this.Existing_Test_Suites.DataSource = dt;
    this.Existing_Test_Suites.DataBind ();

    ensure_Test_Suite_Width ();
    return true;
  }

  private void ensure_Test_Suite_Width ()
  {
    // Ensure width is at least min
    if (Create_Test_Suite_Name.Width.Value < DEFAULT_WIDTH)
      Create_Test_Suite_Name.Width = new Unit (DEFAULT_WIDTH);

    if (Existing_Test_Suites.Width.Value < DEFAULT_WIDTH)
      Existing_Test_Suites.Width = new Unit (DEFAULT_WIDTH);
  }

  private bool load_Packages ()
  {
    // Update the DropDownList to show all packages
    DataTable dt = UnitTestActions.Get_All_Packages ();

    if (dt.Rows.Count == 0)
    {
      // Really no reason to continue,
      // there will obviously be no packages for the
      // selected test suite
      this.master_.show_info_message ("There are no packages created in the system.");

      // Insert the Conveinance Statement
      if (Add_Existing_Package.Items.Count == 0)
        Add_Existing_Package.Items.Insert (0, "Please Create a Package First");

      Add_Existing_Package.SelectedIndex = -1;

      ensure_Test_Suite_Package_Width ();
      return false;
    }


    // Bind Data
    this.Add_Existing_Package.DataSource = dt;
    this.Add_Existing_Package.DataBind ();

    // Insert the Conveinance Statement
    if (Add_Existing_Package.Items [0].Value != "-1")
    {
      this.Add_Existing_Package.Items.Insert (0, new ListItem ("Choose an Existing Package to Add it . . . ", "-1"));
      this.Add_Existing_Package.SelectedIndex = 0;
    }


    // Update the Test_Suite_Packages list

    // First check integrity the selected test suite
    if (false == IsValidSelection (Existing_Test_Suites))
    {
      string err_msg = "There is no Test Suite Selected. " +
                      "One must be selected before a package list can be loaded";
      this.master_.show_info_message (err_msg);
      ensure_Test_Suite_Package_Width ();
      return false;
    }

    // Get Package info for Test Suite
    dt = UnitTestActions.Get_Packages (Existing_Test_Suites.SelectedValue);
    if (dt.Rows.Count == 0)
    {
      this.master_.show_info_message ("There are no packages defined for Test Suite '" +
                              Existing_Test_Suites.SelectedItem.Text + "'");

      // Clear Any old Items
      Test_Suite_Packages_List.Items.Clear ();
      Test_Suite_Packages_List.SelectedIndex = -1;

      ensure_Test_Suite_Package_Width ();
      return false;
    }

    // Bind the data
    this.Test_Suite_Packages_List.DataSource = dt;
    this.Test_Suite_Packages_List.DataBind ();

    // Ensure the width
    ensure_Test_Suite_Package_Width ();

    return true;
  }

  private void ensure_Test_Suite_Package_Width ()
  {
    if (Test_Suite_Packages_List.Width.Value < DEFAULT_WIDTH)
      Test_Suite_Packages_List.Width = new Unit (DEFAULT_WIDTH);

    if (Create_Package_Name.Width.Value < DEFAULT_WIDTH)
      Create_Package_Name.Width = new Unit (DEFAULT_WIDTH);

    if (Add_Existing_Package.Width.Value < DEFAULT_WIDTH)
      Add_Existing_Package.Width = new Unit (DEFAULT_WIDTH);
  }

  private void reload_Packages (string package_to_select_)
  {
    load_Packages ();

    // Find Item we would like selected
    ListItemCollection items = Test_Suite_Packages_List.Items;
    int index_desired = items.IndexOf (items.FindByText (package_to_select_));

    // Select it
    Test_Suite_Packages_List.SelectedIndex = index_desired;

    /*
     - Because you can add existing Packages,
         clearing the Package_Unit_Tests_List
         is not enough. You need to reload it
     - However, we do not need any errors
         reporting there are no Unit Tests
         for this brand New Package. Once
         messaging system is 'smart', we
         should proably add a notice about
         adding a Unit Test to this package
     */
    this.master_.InQuietMode = true;
    load_unit_tests ();
    this.master_.InQuietMode = false;
  }

  private void reload_Test_Suites (string ts_to_select_)
  {
    load_Test_Suites ();

    // Find Item we would like selected
    ListItemCollection items = Existing_Test_Suites.Items;
    int index_desired = items.IndexOf (items.FindByText (ts_to_select_));

    // Select it, and attempt to load all
    Existing_Test_Suites.SelectedIndex = index_desired;

    this.master_.InQuietMode = true;
    load_Packages ();

    // If we are creating a new TS,
    //    or there are no packages in the system,
    // There will be no packages and this would throw an error
    if (this.Test_Suite_Packages_List.Items.Count != 0)
      this.Test_Suite_Packages_List.SelectedIndex = 0;

    load_unit_tests ();
    this.master_.InQuietMode = false;
  }

  private bool load_unit_tests ()
  {
    // Load the Existing Unit Tests List
    DataTable dt = UnitTestActions.Get_All_Unit_Tests ();
    if (dt.Rows.Count == 0)
    {
      // Really no reason to continue,
      // there will obviously be no packages for the
      // selected test suite
      this.master_.show_info_message ("There are no Unit Tests created. Please create at least one to continue.");

      // Add the conveinence item
      if (Add_Existing_Unit_Test.Items.Count == 0)
        this.Add_Existing_Unit_Test.Items.Insert (0, "Please Create a Unit Test");

      Ensure_Unit_Test_Width ();
      return false;
    }

    // Data Bind
    Add_Existing_Unit_Test.DataSource = dt;
    Add_Existing_Unit_Test.DataBind ();

    // Add the conveinence item
    if (this.Add_Existing_Unit_Test.Items [0].Value != "-1")
    {
      this.Add_Existing_Unit_Test.Items.Insert (0, new ListItem ("Please select an existing Unit Test to Add it . . . ", "-1"));
      this.Add_Existing_Unit_Test.SelectedIndex = 0;
    }

    // Check selected Package before running SQL
    string err_msg = "You do not have a Package Selected. " +
            "Please select a package, or create one if none exist";
    if (false == IsValidSelection (Test_Suite_Packages_List, err_msg))
    {
      Ensure_Unit_Test_Width ();
      return false;
    }

    // Load the Package Unit Tests List
    dt = UnitTestActions.Get_Unit_Tests (Test_Suite_Packages_List.SelectedValue);
    if (dt.Rows.Count == 0)
    {
      this.master_.show_info_message ("Package '" +
          Test_Suite_Packages_List.SelectedItem.Text +
          "' does not have any Unit Tests defined with it.");

      // Clear any old Unit Test data
      Package_Unit_Tests_List.Items.Clear ();
      Package_Unit_Tests_List.SelectedIndex = -1;

      Ensure_Unit_Test_Width ();

      return false;
    }

    // DataBind
    Package_Unit_Tests_List.DataSource = dt;
    Package_Unit_Tests_List.DataBind ();

    // Ensure the minimum width
    Ensure_Unit_Test_Width ();
    return true;
  }

  private void Ensure_Unit_Test_Width ()
  {
    if (Package_Unit_Tests_List.Width.Value < DEFAULT_WIDTH)
      Package_Unit_Tests_List.Width = new Unit (DEFAULT_WIDTH);

    if (Add_Existing_Unit_Test.Width.Value < DEFAULT_WIDTH)
      Add_Existing_Unit_Test.Width = new Unit (DEFAULT_WIDTH);
  }

  private void load_log_format_data ()
  {
    // Load the ddl_Add_Package_Unit_Test
    DataTable dt = LogFormatActions.Get_Log_Formats (Package_Unit_Tests_List.SelectedValue);

    this.dg_Unit_Test_Detail_Log_Formats.DataSource = dt;
    this.dg_Unit_Test_Detail_Log_Formats.DataBind ();
  }


  protected void OnClick_Create_Test_Suite (object sender, EventArgs e)
  {
    // Ensure the length of the name
    //   (This also eliminates blank names or one space names - like ' ')
    if (this.Create_Test_Suite_Name.Text.Length < 3)
    {
      this.master_.show_error_message ("Please be sure the test suite name is more than three characters.");
      return;
    }

    try { UnitTestActions.Insert_Test_Suite (Create_Test_Suite_Name.Text); }
    catch
    {
      this.master_.show_error_message ("There was a problem adding the Test Suite." +
          "This probably means there was already a Test Suite with that name.");
      return;
    }

    // Reload the data, and select the package just created
    reload_Test_Suites (Create_Test_Suite_Name.Text);
  }

  protected void OnClick_Create_Package (object sender, EventArgs e)
  {
    // Ensure the length of the name
    //   (This also eliminates blank names or one space names - like ' ')
    if (this.Create_Package_Name.Text.Length < 3)
    {
      this.master_.show_error_message ("Please be sure the package name is more than three characters.");
      return;
    }

    // Ensure we know which Test Suite to
    //   add the Package to
    string err_message = "You do not have a Test Suite selected that " +
                    "it is possible to add Package '" +
                    Create_Package_Name.Text + "' to.";
    if (false == IsValidSelection (Existing_Test_Suites, err_message))
      return;


    // Add the package
    try { UnitTestActions.Insert_New_Package (Existing_Test_Suites.SelectedValue, Create_Package_Name.Text); }
    catch
    {
      this.master_.show_error_message ("There was a problem adding Package '" +
                            Create_Package_Name.Text + "' to Test Suite '" +
                            Existing_Test_Suites.SelectedItem.Text + ".' Their is probably already " +
                            "a package with that name.");
      return;
    }

    // Reload the data, and select the package just created
    reload_Packages (Create_Package_Name.Text);
  }

  protected void OnClick_Delete_Test_Suite (object sender, EventArgs e)
  {
    if (false == IsValidSelection (this.Existing_Test_Suites))
    {
      this.master_.show_error_message ("That is not a valid Test Suite to delete");
      return;
    }

    try
    {
      UnitTestActions.Delete_Test_Suite (Existing_Test_Suites.SelectedValue);
      this.master_.show_info_message ("Test Suite '" +
        Existing_Test_Suites.SelectedItem.Text + "' deleted successfully!");
      reload_all_data ();
    }
    catch
    {
      this.master_.show_error_message ("There was a problem deleting the Test Suite");
    }
  }

  protected void OnClick_Delete_Package (object sender, EventArgs e)
  {
    if (false == IsValidSelection (this.Test_Suite_Packages_List))
    {
      this.master_.show_error_message ("That is not a valid Package to delete");
      return;
    }

    try
    {
      UnitTestActions.Delete_Package (this.Test_Suite_Packages_List.SelectedValue);
      this.master_.show_info_message ("Package '" +
        this.Test_Suite_Packages_List.SelectedItem.Text +
        "' deleted successfully!");
      this.master_.InQuietMode = true;
      reload_all_data ();
      this.master_.InQuietMode = false;
    }
    catch
    {
      this.master_.show_error_message ("There was a problem deleting the Package");
    }

  }

  protected void OnClick_Remove_Package (object sender, EventArgs e)
  {
    if (false == IsValidSelection (this.Test_Suite_Packages_List))
    {
      this.master_.show_error_message ("That is not a valid Package to remove.");
      return;
    }
    if (false == IsValidSelection (this.Existing_Test_Suites))
    {
      this.master_.show_error_message ("You do not have a Test Suite Selected to remove " +
        "this Package from.");
      return;
    }

    try
    {
      UnitTestActions.Remove_Package (Existing_Test_Suites.SelectedValue,
                                     Test_Suite_Packages_List.SelectedValue);
      this.master_.show_info_message ("Package '" +
        this.Test_Suite_Packages_List.SelectedItem.Text +
        "' removed successfully!");
      //this.master_.InQuietMode = true;
      reload_all_data ();
      //this.master_.InQuietMode = false;
    }
    catch
    {
      this.master_.show_error_message ("There was a problem removing the Package");
    }
  }

  protected void OnClick_Delete_Unit_Test (object sender, EventArgs e)
  {
    if (false == IsValidSelection (this.Package_Unit_Tests_List))
    {
      this.master_.show_error_message ("That is not a valid Unit Test to delete.");
      return;
    }

    try
    {
      UnitTestActions.Delete_Unit_Test (this.Package_Unit_Tests_List.SelectedValue);
      this.master_.show_info_message ("Unit test '" +
        this.Package_Unit_Tests_List.SelectedItem.Text +
        "' removed successfully!");
      //this.master_.InQuietMode = true;
      reload_all_data ();
      //this.master_.InQuietMode = false;
    }
    catch
    {
      this.master_.show_error_message ("There was a problem deleting the Unit Test");
    }
  }

  protected void OnClick_Remove_Unit_Test (object sender, EventArgs e)
  {
    if (false == IsValidSelection (this.Package_Unit_Tests_List))
    {
      this.master_.show_error_message ("That is not a valid unit test to remove.");
      return;
    }
    if (false == IsValidSelection (this.Test_Suite_Packages_List))
    {
      this.master_.show_error_message ("You do not have a package selected to remove " +
        "this unit test from.");
      return;
    }

    try
    {
      UnitTestActions.Remove_Unit_Test (this.Test_Suite_Packages_List.SelectedValue,
                                       this.Package_Unit_Tests_List.SelectedValue);
      this.master_.show_info_message ("Unit test '" +
        this.Package_Unit_Tests_List.SelectedItem.Text +
        "' removed successfully!");
      this.master_.InQuietMode = true;
      reload_all_data ();
      this.master_.InQuietMode = false;
    }
    catch
    {
      this.master_.show_error_message ("There was a problem removing the Unit Test");
    }
  }

  protected void OnChange_Packages_List (object sender, EventArgs e)
  {
    load_unit_tests ();
  }

  protected void OnChange_Add_Existing_Package (object sender, EventArgs e)
  {
    // Ensure there is a Test Suite Selected
    string err_msg = "I am not sure which Test Suite you would like to add this pacakge to." +
                "Please select a Test Suite and Try again";
    if (false == IsValidSelection (Existing_Test_Suites, err_msg))
      return;

    // Ensure there is a Valid Package
    err_msg = "That is not a valid Package";
    if (false == IsValidSelection (Add_Existing_Package, err_msg))
      return;

    // Insert the package
    try
    {
      UnitTestActions.Insert_Existing_Package (
                                          Existing_Test_Suites.SelectedValue,
                                          Add_Existing_Package.SelectedValue);
    }
    catch
    {
      this.master_.show_error_message ("There was a problem adding package '" +
          Add_Existing_Package.SelectedItem.Text + "' to test suite '" +
          Existing_Test_Suites.SelectedItem.Text + ".' This probably means it is already added. ");
      return;
    }


    // Reload the Package data, and select the package just added
    reload_Packages (Add_Existing_Package.SelectedItem.Text);
  }

  protected void OnChange_Add_Existing_Unit_Test (object sender, EventArgs e)
  {
    string err_message = "That is not a valid Unit Test to add.";
    if (IsValidSelection (Add_Existing_Unit_Test, err_message) == false)
      return;

    // Ensure the integrity of the Selected Package
    err_message = "You do not have a Package selected to add '" +
                    Add_Existing_Unit_Test.SelectedItem.Text + "' to. ";
    if (false == IsValidSelection (Test_Suite_Packages_List, err_message))
      return;

    // Add the Unit Test
    try
    {
      UnitTestActions.Insert_Existing_Unit_Test (
                            this.Test_Suite_Packages_List.SelectedValue,
                            this.Add_Existing_Unit_Test.SelectedValue);
    }
    catch
    {
      this.master_.show_error_message ("There was a problem adding Unit Test '" +
          Add_Existing_Unit_Test.SelectedItem.Text + "' to Package '" +
          Test_Suite_Packages_List.SelectedItem.Text + ".' This probably means it is already added");
      return;
    }

    // Reload the Unit test Drop Down List
    load_unit_tests ();

  }

  protected void OnChange_Test_Suites_List (object sender, EventArgs e)
  {
    // Pass in the new selection so we can try to load it
    reload_Test_Suites (Existing_Test_Suites.SelectedItem.Text);
  }

  protected void OnChange_Unit_Tests_List (object sender, EventArgs e)
  {
    Unit_Test_Details_Visible = true;

    // Ensure selection before sending sql
    string err_msg = "'" + Package_Unit_Tests_List.SelectedItem.Text + "' is not a valid Unit Test";
    if (false == IsValidSelection (Package_Unit_Tests_List, err_msg))
      return;

    DataRow row = UnitTestActions.Get_Unit_Test_Info (Package_Unit_Tests_List.SelectedValue);

    txt_Unit_Test_Details_Name.Text = row ["name"].ToString ();
    txt_Unit_Test_Details_Description.Text = row ["description"].ToString ();
    txt_Unit_Test_Details_Evaluation.Text = row ["evaluation"].ToString ();
    txt_Unit_Test_Details_Warn_Comparison.Text = row ["warn_comparison"].ToString () + " " + row ["warn"].ToString ();
    txt_Unit_Test_Details_Fail_Comparison.Text = row ["fail_comparison"].ToString () + " " + row ["fail"].ToString ();
    lbl_Unit_Test_Details_ID.Text = row ["utid"].ToString ();

    load_log_format_data ();
  }

  private void initialize_help ()
  {
    StringBuilder builder = new StringBuilder ();

  }

  private bool Unit_Test_Details_Visible
  {
    get { return this.td_Unit_Test_Details.Visible; }
    set { this.td_Unit_Test_Details.Visible = value; }
  }


  /// <summary>
  /// Ensures that there is a SQL-safe valid selection
  /// </summary>
  /// <param name="lb"></param>
  /// <returns></returns>
  private bool IsValidSelection (ListBox lb)
  {
    // If there is only one, we can assume they wanted that one
    if (lb.SelectedIndex < 0)
      if (lb.Items.Count == 1)
        lb.SelectedIndex = 0;
      else
        return false;
    return true;
  }

  /// <summary>
  /// Ensures that there is a SQL-safe valid selection
  /// </summary>
  /// <param name="lb"></param>
  /// <param name="error_message"></param>
  /// <returns></returns>
  private bool IsValidSelection (ListBox lb, string error_message)
  {
    if (IsValidSelection (lb) == false)
    {
      this.master_.show_error_message (error_message);
      return false;
    }
    else
      return true;
  }
  /// <summary>
  /// Ensures that there is a SQL-safe valid selection
  /// </summary>
  /// <param name="d"></param>
  /// <returns></returns>
  private bool IsValidSelection (DropDownList d)
  {
    // Assuming we have a first item similar to
    // "Please Select One . . ."
    if (d.SelectedIndex < 1)
      return false;
    return true;
  }
  /// <summary>
  /// Ensures that there is a SQL-safe valid selection
  /// </summary>
  /// <param name="d"></param>
  /// <param name="error_message"></param>
  /// <returns></returns>
  private bool IsValidSelection (DropDownList d, string error_message)
  {
    if (IsValidSelection (d))
      return true;


    this.master_.show_error_message (error_message);
    return false;
  }
}

/* Exceptions

 *  These should only be used when there is something that
 *  would cause an error. The main use will be when some
 *  value that is to be passed to MySql is not valid,
 *  such as a DropDownList not having a selected value

*/

/// <summary>
/// These should only be used when there is something that
/// would cause an error. The main use will be when some
/// value that is to be passed to MySql is not valid,
/// such as a DropDownList not having a selected value.
/// </summary>
public class LoadTestSuiteException : Exception
{ // All we need is a default Exception constructor

  public LoadTestSuiteException (string message)
    : base (message) { }
}

/// <summary>
/// These should only be used when there is something that
/// would cause an error. The main use will be when some
/// value that is to be passed to MySql is not valid,
/// such as a DropDownList not having a selected value.
/// </summary>
public class LoadTestSuitePackageException : Exception
{ // All we need is a default Exception constructor

  public LoadTestSuitePackageException (string message)
    : base (message) { }
}

/// <summary>
/// These should only be used when there is something that
/// would cause an error. The main use will be when some
/// value that is to be passed to MySql is not valid,
/// such as a DropDownList not having a selected value.
/// </summary>
public class LoadPackageUnitTestsException : Exception
{ // All we need is a default Exception constructor

  public LoadPackageUnitTestsException (string message)
    : base (message) { }
}
