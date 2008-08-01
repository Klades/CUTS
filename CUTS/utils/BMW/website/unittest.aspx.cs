// -*- C# -*-

//=============================================================================
/**
 * @file            unittest.aspx.cs
 *
 * $Id$
 *
 * @author          Hamilton J. Turner
 */
//=============================================================================

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
  private CUTS.Master master_;

  protected void Page_Load (object sender, EventArgs e)
  {
    // used to ease creating messages
    this.master_ = (CUTS.Master)Master;

    if (this.IsPostBack)
      return;

    // Load all the test suites into the web controls.
    this.reload_all_data  ();
  }

  private void reload_all_data ()
  {
    this.load_test_suites ();
    this.load_test_packages ();
    this.load_unit_tests ();
  }

  /**
   * Helper method to load all the test suites from the database.
   */
  private void load_test_suites ()
  {
    // Load Existing Test Suites
    DataTable dt = UnitTestActions.Get_All_Test_Suites ();

    // Bind the data to the control.
    this.existing_test_suites_.DataSource = dt;
    this.existing_test_suites_.DataBind ();

    // Update the link for deleting a test suite.
    int count = dt.Rows.Count;
    this.insert_test_package_.Enabled = (count > 0);
    this.delete_test_suite_.Visible = (count > 0);

    // Load all the test packages.
    if (this.existing_test_suites_.SelectedIndex != -1)
      this.load_test_suite_packages ();
  }

  /**
   * Helper method to load all the packages from the database. It will
   * also load the packages for the currently selected test suite.
   */
  private void load_test_suite_packages ()
  {
    // Get the test packages for the selected item.
    DataTable dt = UnitTestActions.Get_Packages (this.existing_test_suites_.SelectedValue);

    // Bind the data to the control.
    this.current_test_packages_.DataSource = dt;
    this.current_test_packages_.DataBind ();
  }

  private void load_test_packages ()
  {
    // Get all the packages from the database.
    DataTable dt = UnitTestActions.Get_All_Packages ();

    // Bind the data table to the control.
    this.existing_test_packages_.DataSource = dt;
    this.existing_test_packages_.DataBind ();

    // Load the unit test.
    if (this.existing_test_packages_.SelectedIndex != -1)
      this.load_test_package_unit_tests ();
  }

  private void reload_packages (string target_package)
  {
    load_test_packages ();

    // Find Item we would like selected
    ListItemCollection items = existing_test_packages_.Items;
    int index_desired = items.IndexOf (items.FindByText (target_package));

    // Select it
    existing_test_packages_.SelectedIndex = index_desired;

    /*
     - Because you can add existing Packages,
         clearing the package_unit_tests_list_
         is not enough. You need to reload it
     - However, we do not need any errors
         reporting there are no Unit Tests
         for this brand New Package. Once
         messaging system is 'smart', we
         should proably add a notice about
         adding a Unit Test to this package
     */
    this.load_unit_tests ();
  }

  private void reload_test_suites (string target_ts)
  {
    this.load_test_suites ();

    // Find Item we would like selected
    ListItemCollection items = existing_test_suites_.Items;
    int index_desired = items.IndexOf (items.FindByText (target_ts));

    // Select it, and attempt to load all
    existing_test_suites_.SelectedIndex = index_desired;

    this.load_test_packages ();

  }

  private void load_unit_tests ()
  {
    // Load the existing unit tests and bind them to the control.
    DataTable dt = UnitTestActions.Get_All_Unit_Tests ();

    this.existing_unit_tests_.DataSource = dt;
    this.existing_unit_tests_.DataBind ();
  }

  private void load_test_package_unit_tests ()
  {
    // Load the unit test for the selected package. This is for the general
    // package, and not the package within a test suite since it references
    // an existing test package.
    DataTable dt = UnitTestActions.Get_Unit_Tests (this.existing_test_packages_.SelectedValue);

    // DataBind
    this.package_unit_tests_list_.DataSource = dt;
    this.package_unit_tests_list_.DataBind ();
  }

  private void load_log_format_data ()
  {
    // Load the ddl_Add_Package_Unit_Test
    DataTable dt = LogFormatActions.Get_Log_Formats (package_unit_tests_list_.SelectedValue);

    this.dg_Unit_Test_Detail_Log_Formats.DataSource = dt;
    this.dg_Unit_Test_Detail_Log_Formats.DataBind ();
  }

  protected void onclick_create_test_suite (object sender, EventArgs e)
  {
    string name = this.Create_Test_Suite_Name.Text;

    try
    {
      // Create the new test suite.
      UnitTestActions.Insert_Test_Suite (name);
      this.master_.show_info_message ("Succesfully created " + name + " test suite");
      this.Create_Test_Suite_Name.Text = "";

      // Reload the data, and select the package just created
      this.load_test_suites ();
    }
    catch (Exception ex)
    {
      this.master_.show_error_message (ex.Message);
      this.master_.show_error_message ("Failed to create test suite " + name);
    }
  }

  protected void onclick_create_test_package (object sender, EventArgs e)
  {
    string name = this.create_package_name_.Text;

    try
    {
      // Create the new test suite.
      UnitTestActions.create_test_package (name);
      this.master_.show_info_message ("Succesfully created " + name + " test package");
      this.create_package_name_.Text = "";

      // Reload the data, and select the package just created
      this.load_test_packages ();
    }
    catch (Exception ex)
    {
      this.master_.show_error_message (ex.Message);
      this.master_.show_error_message ("Failed to create test package " + name);
    }
  }

  protected void onclick_insert_test_package (object sender, EventArgs e)
  {
    if (this.existing_test_suites_.SelectedIndex != -1)
    {
      try
      {
        // Add the package to the test suite.
        string pkg_name = this.existing_test_packages_.SelectedItem.Text;
        UnitTestActions.Insert_New_Package (this.existing_test_suites_.SelectedValue, pkg_name);

        string message =
          "Successfully added " + pkg_name + " test package to " +
          this.existing_test_packages_.SelectedItem.Text + " test suite";

        this.master_.show_info_message (message);

        // Reload the packages for the test suite.
        this.load_test_suite_packages ();
      }
      catch (Exception ex)
      {
        this.master_.show_error_message (ex.Message);
        this.master_.show_error_message ("Failed to create " + this.create_package_name_.Text + " test package");
      }
    }
    else
    {
      this.master_.show_error_message ("Please select a test suite to add test package");
    }
  }

  protected void onclick_delete_test_suite (object sender, EventArgs e)
  {
    if (this.existing_test_suites_.SelectedIndex != -1)
    {
      try
      {
        // Delete the test suite from the database.
        UnitTestActions.Delete_Test_Suite (this.existing_test_suites_.SelectedValue);

        // Show a message to the user.
        string msg = "Successfully deleted test suite " + existing_test_suites_.SelectedItem.Text;
        this.master_.show_info_message (msg);
      }
      catch (Exception ex)
      {
        this.master_.show_error_message (ex.Message);
        this.master_.show_error_message ("Failed to delete selected test suite");
      }
      finally
      {
        try
        {
          //this.existing_test_suites_.SelectedIndex = -1;
          this.reload_all_data ();
        }
        catch (Exception ex)
        {
          this.master_.show_error_message (ex.Message);
          this.master_.show_error_message ("Failed to reload data");
        }
      }
    }
    else
    {
      this.master_.show_error_message ("Please select a valid test suite to delete");
    }
  }

  protected void onclick_delete_test_package (object sender, EventArgs e)
  {
    if (this.existing_test_packages_.SelectedIndex != -1)
    {
      string name = this.existing_test_packages_.SelectedItem.Text;

      try
      {
        // Delete the package from the database.
        UnitTestActions.Delete_Package (this.existing_test_packages_.SelectedValue);

        string msg = "Successfully deleted " + name + " test package from database";
        this.master_.show_info_message (msg);

        // Reload all the test packages from the database.
        this.load_test_packages ();
      }
      catch (Exception ex)
      {
        this.master_.show_error_message (ex.Message);
        this.master_.show_error_message ("Failed to delete " + name + " test package");
      }
    }
    else
    {
      this.master_.show_error_message ("Please select an existing test package to delete");
    }
  }

  protected void onclick_remove_test_package (object sender, EventArgs e)
  {
    if (this.existing_test_suites_.SelectedIndex != -1)
    {
      // Get the name of the test suite are deleting. This will be used in
      // the generated messages.
      string suite_name = this.existing_test_suites_.SelectedItem.Text;

      if (this.existing_test_packages_.SelectedIndex != -1)
      {
        try
        {
          // Remove the package from the test suite.
          UnitTestActions.Remove_Package (this.existing_test_suites_.SelectedValue,
                                          this.existing_test_packages_.SelectedValue);

          string msg =
            "Successfully removed " + this.existing_test_packages_.SelectedItem.Text +
            " test package from " + suite_name + " test suite";

          // Show the message to the user.
          this.master_.show_info_message (msg);

          // Load the test packages.
          this.load_test_packages ();
        }
        catch (Exception ex)
        {
          // Show the current exception.
          this.master_.show_error_message (ex.Message);

          // Show a more meaningful message.
          string msg = "Failed to remove selected package from " + suite_name + " test suite";
          this.master_.show_error_message (msg);
        }
      }
      else
      {
        string name = this.existing_test_suites_.SelectedItem.Text;
        string msg = "Please select a valid test package to remove from " + name + " test suite";

        this.master_.show_error_message (msg);
      }
    }
    else
    {
      this.master_.show_error_message ("No test suite is selected");
    }
  }

  protected void onclick_insert_unit_test (object sender, EventArgs e)
  {
    if (this.existing_test_packages_.SelectedIndex != -1)
    {
      // Save the name of the package that we are adding a unit test.
      string pkg_name = this.existing_test_packages_.SelectedItem.Text;

      if (this.existing_unit_tests_.SelectedIndex != -1)
      {
        string name = this.existing_unit_tests_.SelectedItem.Text;

        try
        {
          // Remove the unit test from the database, if possible.
          UnitTestActions.Insert_Existing_Unit_Test (this.existing_test_packages_.SelectedValue,
                                                     this.existing_unit_tests_.SelectedValue);

          // Display useful message to the user.
          string message =
            "Successfully added " + name + " unit test to " + pkg_name + " test package";

          this.master_.show_info_message (message);

          // Force reloading of the unit tests.
          this.load_test_package_unit_tests ();
        }
        catch (Exception ex)
        {
          this.master_.show_error_message (ex.Message);
          this.master_.show_error_message ("Failed to add " + name + " unit test to " + pkg_name + " test package");
        }
      }
      else
      {
        this.master_.show_error_message ("Please select a valid unit test to add");
      }
    }
    else
    {
      this.master_.show_error_message ("Please select an existing test package to add unit test");
    }
  }

  protected void onclick_delete_unit_test (object sender, EventArgs e)
  {
    if (this.existing_unit_tests_.SelectedIndex != -1)
    {
      string name = this.existing_unit_tests_.SelectedItem.Text;

      try
      {
        // Remove the unit test from the database, if possible.
        UnitTestActions.Delete_Unit_Test (this.existing_unit_tests_.SelectedValue);
        this.master_.show_info_message ("Successfully deleted " + name + " unit test from database");

        // Force reloading of the unit tests.
        this.load_unit_tests ();
      }
      catch (Exception ex)
      {
        this.master_.show_error_message (ex.Message);
        this.master_.show_error_message ("Failed to delete " + name + " unit test from database");
      }
    }
    else
    {
      this.master_.show_error_message ("Please select a valid unit test to delete");
    }
  }

  protected void onclick_remove_unit_test (object sender, EventArgs e)
  {
    if (this.existing_test_packages_.SelectedIndex != -1)
    {
      // Save the name of the currently select test package.
      string pkg_name = this.existing_test_packages_.SelectedItem.Text;

      if (this.package_unit_tests_list_.SelectedIndex != -1)
      {
        string ut_name =
          this.package_unit_tests_list_.SelectedItem.Text;

        try
        {
          // Remove the selected unit test from the existing package.
          UnitTestActions.Remove_Unit_Test (this.existing_test_packages_.SelectedValue,
                                            this.package_unit_tests_list_.SelectedValue);

          // Show an informative message to the user.
          string msg =
            "Successfully removed " + ut_name + " unit test from " +
            pkg_name + " test package";

          this.master_.show_info_message (msg);

          // Update the test package's unit test control.
          this.load_test_package_unit_tests ();
        }
        catch (Exception ex)
        {
          this.master_.show_error_message (ex.Message);

          string msg =
            "Failed to remove " + ut_name + " unit test from " + pkg_name +
            " test package";

          this.master_.show_error_message (msg);
        }
      }
      else
      {
        this.master_.show_error_message ("Please select an existing unit test");
      }
    }
    else
    {
      this.master_.show_error_message ("Please select an existing test package");
    }
  }

  protected void OnChange_Add_Existing_Package (object sender, EventArgs e)
  {
    // Ensure there is a Test Suite Selected
    string err_msg = "I am not sure which Test Suite you would like to add this pacakge to." +
                "Please select a Test Suite and Try again";
    if (false == is_valid_selection (existing_test_suites_, err_msg))
      return;

    // Ensure there is a Valid Package
    err_msg = "That is not a valid Package";
    if (false == is_valid_selection (existing_test_packages_, err_msg))
      return;

    // Insert the package
    try
    {
      UnitTestActions.Insert_Existing_Package (this.existing_test_suites_.SelectedValue,
                                               this.existing_test_packages_.SelectedValue);
    }
    catch (Exception ex)
    {
      this.master_.show_error_message (ex.Message);
      this.master_.show_error_message ("There was a problem adding package '" +
          existing_test_packages_.SelectedItem.Text + "' to test suite '" +
          existing_test_suites_.SelectedItem.Text + ".' This probably means it is already added. ");
      return;
    }
  }

  protected void onchange_existing_test_packages (object sender, EventArgs e)
  {
    string name = this.existing_test_packages_.SelectedItem.Text;

    StringBuilder message = new StringBuilder ();
    message.Append ("The following unit tests are included in the <b>" + name + "</b> test package. ");
    message.Append ("To add more unit tests, either create a new unit test, or ");
    message.Append ("select an existing unit tests using the listbox above.");

    this.unit_test_details_.Text = message.ToString ();
    this.load_test_package_unit_tests ();
  }

  protected void onchange_existing_unit_test (object sender, EventArgs e)
  {
    string err_message = "That is not a valid Unit Test to add.";
    if (is_valid_selection (existing_unit_tests_, err_message) == false)
      return;

    // Ensure the integrity of the Selected Package
    err_message = "You do not have a Package selected to add '" +
                    existing_unit_tests_.SelectedItem.Text + "' to. ";
    if (false == is_valid_selection (existing_test_packages_, err_message))
      return;

    // Add the Unit Test
    try
    {
      UnitTestActions.Insert_Existing_Unit_Test (this.existing_test_packages_.SelectedValue,
                                                 this.existing_unit_tests_.SelectedValue);
    }
    catch (Exception ex)
    {
      this.master_.show_error_message (ex.Message);
      this.master_.show_error_message ("There was a problem adding Unit Test '" +
          existing_unit_tests_.SelectedItem.Text + "' to Package '" +
          existing_test_packages_.SelectedItem.Text + ".' This probably means it is already added");
      return;
    }

    // Reload the Unit test Drop Down List
    this.load_unit_tests ();
  }

  protected void onchange_existing_test_suites (object sender, EventArgs e)
  {
    string name = this.existing_test_suites_.SelectedItem.Text;

    // Update the package details.
    StringBuilder message = new StringBuilder ();
    message.Append ("The following packages are included in the <b>" + name + "</b> test suite. ");
    message.Append ("To add more test packages, either create a new test package, or ");
    message.Append ("select an existing test package using the control above.");

    this.package_details_.Text = message.ToString ();

    // Load the packages for the selected test suite.
    this.load_test_suite_packages ();

    if (!this.insert_test_package_.Enabled)
      this.insert_test_package_.Enabled = true;
  }

  protected void onchange_unit_tests_list (object sender, EventArgs e)
  {
    unit_test_details_visible = true;

    // Ensure selection before sending sql
    string err_msg = "'" + package_unit_tests_list_.SelectedItem.Text + "' is not a valid Unit Test";
    if (false == is_valid_selection (package_unit_tests_list_, err_msg))
      return;

    DataRow row = UnitTestActions.Get_Unit_Test_Info (package_unit_tests_list_.SelectedValue);

    txt_Unit_Test_Details_Name.Text = row ["name"].ToString ();
    txt_Unit_Test_Details_Description.Text = row ["description"].ToString ();
    txt_Unit_Test_Details_Evaluation.Text = row ["evaluation"].ToString ();
    txt_Unit_Test_Details_Warn_Comparison.Text = row ["warn_comparison"].ToString () + " " + row ["warn"].ToString ();
    txt_Unit_Test_Details_Fail_Comparison.Text = row ["fail_comparison"].ToString () + " " + row ["fail"].ToString ();
    lbl_Unit_Test_Details_ID.Text = row ["utid"].ToString ();

    load_log_format_data ();
  }

  private bool unit_test_details_visible
  {
    get { return this.td_Unit_Test_Details.Visible; }
    set { this.td_Unit_Test_Details.Visible = value; }
  }


  /// <summary>
  /// Ensures that there is a SQL-safe valid selection
  /// </summary>
  /// <param name="lb"></param>
  /// <returns></returns>
  private bool is_valid_selection (ListBox lb)
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
  private bool is_valid_selection (ListBox lb, string error_message)
  {
    if (is_valid_selection (lb) == false)
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
  private bool is_valid_selection (DropDownList d)
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
  private bool is_valid_selection (DropDownList d, string error_message)
  {
    if (is_valid_selection (d))
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
