// -*- C# -*-

//=============================================================================
/**
 * @file            unittest.aspx.cs
 *
 * $Id$
 *
 * @author          Hamilton Turner
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

  private MySqlConnection conn_ =
    new MySqlConnection (ConfigurationManager.AppSettings["MySQL"]);

  protected void Page_Load (object sender, EventArgs e)
  {
    // used to ease creating messages
    this.master_ = (CUTS.Master)Master;

    if (this.ViewState["logformats"] != null)
    {
      // Get the number of log formats to show.
      int formats = (int)this.ViewState["logformats"];

      // Determine how many rows we need to insert into the table.
      int rows = this.log_formats_.Rows.Count - 1;

      // Insert all the rows. The first row does not get a relation control.
      for (; rows < formats; ++ rows)
        this.insert_new_log_format (true);
    }
    else
    {
      this.insert_new_log_format (false);
      this.ViewState["logformats"] = 1;
    }

    if (this.IsPostBack)
      return;

    // Load all the test suites into the web controls.
    this.reload_all_data ();
  }

  private void reload_all_data ()
  {
    // Load the test suite from the database.
    this.load_test_suites ();

    // Load the test packages from the database.
    this.load_test_packages ();

    // Load the unit tests from the database.
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

  //private void load_log_format_data ()
  //{
  //  // Load the ddl_Add_Package_Unit_Test
  //  DataTable dt = LogFormatActions.Get_Log_Formats (package_unit_tests_list_.SelectedValue);

  //  this.dg_Unit_Test_Detail_Log_Formats.DataSource = dt;
  //  this.dg_Unit_Test_Detail_Log_Formats.DataBind ();
  //}

  protected void onclick_create_test_suite (object sender, EventArgs e)
  {
    string name = this.test_suite_name_.Text;

    try
    {
      // Create the new test suite.
      UnitTestActions.Insert_Test_Suite (name);
      this.master_.show_info_message ("Succesfully created " + name + " test suite");
      this.test_suite_name_.Text = "";

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
    string name = this.test_package_name_.Text;

    try
    {
      // Create the new test suite.
      UnitTestActions.create_test_package (name);
      this.master_.show_info_message ("Succesfully created " + name + " test package");
      this.test_package_name_.Text = "";

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
        this.master_.show_error_message ("Failed to create " + this.test_package_name_.Text + " test package");
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

  //protected void onchange_existing_unit_test (object sender, EventArgs e)
  //{
  //  string err_message = "That is not a valid Unit Test to add.";
  //  if (is_valid_selection (existing_unit_tests_, err_message) == false)
  //    return;

  //  // Ensure the integrity of the Selected Package
  //  err_message = "You do not have a Package selected to add '" +
  //                  existing_unit_tests_.SelectedItem.Text + "' to. ";
  //  if (false == is_valid_selection (existing_test_packages_, err_message))
  //    return;

  //  // Add the Unit Test
  //  try
  //  {
  //    UnitTestActions.Insert_Existing_Unit_Test (this.existing_test_packages_.SelectedValue,
  //                                               this.existing_unit_tests_.SelectedValue);
  //  }
  //  catch (Exception ex)
  //  {
  //    this.master_.show_error_message (ex.Message);
  //    this.master_.show_error_message ("There was a problem adding Unit Test '" +
  //        existing_unit_tests_.SelectedItem.Text + "' to Package '" +
  //        existing_test_packages_.SelectedItem.Text + ".' This probably means it is already added");
  //    return;
  //  }

  //  // Reload the Unit test Drop Down List
  //  this.load_unit_tests ();
  //}

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

  }

  protected void onchange_log_format (object sender, EventArgs e)
  {
    // Extract the control that sent this event. It should be a dropdown control.
    // Otherwise, another control is trying to use this callback.
    DropDownList list = (DropDownList)sender;

    // Update the prefix label for this listing.
    this.update_log_format_prefix_label (list);

    // Update the relations for this listing.
    this.update_log_format_relations (list);
  }

  protected void ondatabound_log_formats (object sender, EventArgs e)
  {
    DropDownList list = (DropDownList)sender;

    // Update the prefix label for this listing.
    this.update_log_format_prefix_label (list);

    // Update the relations for this listing.
    this.update_log_format_relations (list);
  }

  /**
   * Helper method that updates the prefix label for the log formats. This
   * will use the current selection to generate the prefix string. If there
   * is no selection, then the prefix string will be set to an empty string.
   *
   * @param[in]         formats         Drop-down list of the log formats.
   */
  private void update_log_format_prefix_label (DropDownList formats)
  {
    // Get the parent cell of this control.
    TableCell cell = (TableCell)formats.Parent;

    // The prefix label is the the one and only control in the first cell
    // of the current row. :-)
    TableRow row = (TableRow)cell.Parent;
    Literal prefix = (Literal)row.Cells[0].Controls[0];

    if (formats.SelectedIndex != -1)
      prefix.Text = "LF" + formats.SelectedValue + ".";
    else
      prefix.Text = "";
  }

  /**
   * Helper method for updating the relationship controls for the log
   * message. The left-hand dropdown will show the variables for this log
   * format. The right-hand side will show the variables for the log
   * formats in the previous rows
   */
  protected void update_log_format_relations (DropDownList formats)
  {
    // Locate the relation cell, and their controls.
    TableCell formats_cell = (TableCell)formats.Parent;
    TableRow current_row = (TableRow)formats_cell.Parent;

    // Get the index of the current row.
    int row_index = this.log_formats_.Rows.GetRowIndex (current_row);

    TableCell relation_cell;
    MySqlCommand command = this.conn_.CreateCommand ();
    MySqlDataAdapter adapter = new MySqlDataAdapter (command);
    DataSet ds = new DataSet ();

    if (row_index > 1)
    {
      // Get the variables for the left-hand side relation. This variables
      // are the ones from the selected log format.
      string lhs_sql =
        "SELECT variable_id, varname FROM cuts.log_format_variables " +
        "WHERE lfid = ?lfid ORDER BY varname";

      command.CommandText = lhs_sql;
      command.Parameters.AddWithValue ("?lfid", formats.SelectedValue);

      adapter.Fill (ds, "lhs_relation");

      // Bind the data tables to the appropriate cells.
      relation_cell = current_row.Cells[2];
      DropDownList lhs_relation = this.get_lhs_relation (relation_cell);

      lhs_relation.DataSource = ds;
      lhs_relation.DataMember = "lhs_relation";
      lhs_relation.DataValueField = "variable_id";
      lhs_relation.DataTextField = "varname";
      lhs_relation.DataBind ();

      // Now, we need to update the right-hand side of the equal sign for
      // this log message, and all the log messages after this one.
      ArrayList lfids_list = new ArrayList ();

      for (; row_index < this.log_formats_.Rows.Count; ++row_index)
      {
        // Get the next items for the next iteration.
        current_row = this.log_formats_.Rows[row_index];
        relation_cell = current_row.Cells[2];

        for (int i = 1; i < row_index; ++i)
        {
          // Get the dropdown list for this row.
          DropDownList log_format =
            (DropDownList)this.log_formats_.Rows[i].Cells[1].Controls[0];

          // Insert the selected value from the list.
          lfids_list.Add (log_format.SelectedValue);
        }

        string prev_lfids =
          String.Join (",", (string[])lfids_list.ToArray (typeof (string)));

        string rhs_sql =
          "SELECT variable_id, lfid, varname, CONCAT('LF', CAST(lfid AS CHAR), '.', varname) AS fq_name " +
          "FROM cuts.log_format_variables " +
          "WHERE lfid IN (" + prev_lfids + ") ORDER BY fq_name";

        adapter.SelectCommand.CommandText = rhs_sql;
        adapter.Fill (ds, "rhs_relation");

        // Now, let's locate either relation's dropdown list.
        DropDownList rhs_relation = this.get_rhs_relation (relation_cell);

        rhs_relation.DataSource = ds;
        rhs_relation.DataMember = "rhs_relation";
        rhs_relation.DataValueField = "variable_id";
        rhs_relation.DataTextField = "fq_name";
        rhs_relation.DataBind ();
      }
    }
  }

  /**
   * Event handler for clicking the Create button for a unit test. This will
   * create an entry in the database for the specified information.
   */
  protected void onclick_create_unit_test (object sender, EventArgs e)
  {
    // Get all the log format ids that are used in this unit test. This
    // is as simple as iterating over all the rows in the table and locating
    // the 'log_format_' control in that row. ;-)

    ArrayList lfids = new ArrayList ();
    ArrayList relations = new ArrayList ();

    for (int i = 1; i < this.log_formats_.Rows.Count; ++i)
    {
      // Find the "log_format_" control in this row.
      DropDownList formats = this.get_log_format_control (this.log_formats_.Rows[i]);

      // Insert its value into the listing of log format ids.
      lfids.Add (formats.SelectedValue);
    }

    // Get the relations for the unit test.
    for (int i = 2; i < this.log_formats_.Rows.Count; ++ i)
    {
      DropDownList lhs_relation, rhs_relation;
      this.get_relations (this.log_formats_.Rows[i], out lhs_relation, out rhs_relation);

      relations.Add (new Pair (lhs_relation.SelectedValue, rhs_relation.SelectedValue));
    }

    // Prepare the variables for inserting the new unit test.
    Hashtable variables = new Hashtable ();
    variables.Add ("Name", this.unit_test_name_.Text);
    variables.Add ("Description", this.unit_test_description_.Text);
    variables.Add ("FailComparison", this.get_mysql_comparison (UT_fail_comp.Text));
    variables.Add ("WarnComparison", this.get_mysql_comparison (UT_warn_comp.Text));
    variables.Add ("FailValue", this.unit_test_fail_.Text);
    variables.Add ("WarnValue", this.unit_test_warn_.Text);
    variables.Add ("Evaluation", this.unit_test_eval_.Text);
    variables.Add ("Aggregration_Func", this.aggr_function_.SelectedValue);
    variables.Add ("Formats", (string[])lfids.ToArray (typeof (string)));
    variables.Add ("Relations", (Pair[])relations.ToArray (typeof (Pair)));

    try
    {
      // Insert the neq unit test into the database.
      UnitTestActions.Insert_New_Unit_Test (variables);
      this.master_.show_info_message ("Successfully created new unit test");

      // Reset the unit test form.
      this.reset_unit_test_form ();

      // Reload the existing test suite control.
      this.load_unit_tests ();
    }
    catch (Exception ex)
    {
      this.master_.show_error_message (ex.Message);
      this.master_.show_error_message ("Failed to create new unit test");
    }
  }

  /**
   * Event handler for click the 'I need more log formats' link. This will
   * insert a new row into the table for selecting log formats when
   * evaluating the unit test
   */
  protected void onclick_more_log_formats (object sender, EventArgs e)
  {
    // Insert a new log message format into the table.
    this.insert_new_log_format (false);

    // Get and update the number of log formats that were created dynamically.
    int formats =
      this.ViewState["logformats"] != null ? (int)this.ViewState["logformats"] + 1 : 1;

    // Store the count back into the view state.
    this.ViewState["logformats"] = formats;
  }

  /**
   * Reset the unit test creation form.
   */
  private void reset_unit_test_form ()
  {
    // Reset all of the textboxes
    this.unit_test_name_.Text = String.Empty;
    this.unit_test_description_.Text = String.Empty;
    this.unit_test_eval_.Text = String.Empty;
    this.unit_test_fail_.Text = String.Empty;
    this.unit_test_warn_.Text = String.Empty;

    // Clear all the rows from the log formats. This means removing its
    // viewstate items as well.
    this.log_formats_.Rows.Clear ();
    this.ViewState.Remove ("logformats");

    // Insert a fresh new row into the table.
    this.insert_new_log_format (false);
  }

  /**
   * Helper method for inserting a new log format into the table
   */
  private void insert_new_log_format (bool use_viewstate)
  {
    // Create the prefix label for the log format.
    Literal prefix = new Literal ();
    prefix.EnableViewState = true;

    // Create a new table cell for the control.
    TableCell prefix_cell = new TableCell ();
    prefix_cell.Controls.Add (prefix);

    // Create the new dropdown control for the log formats.
    DropDownList formats = new DropDownList ();
    formats.DataTextField = "lfmt";
    formats.DataValueField = "lfid";
    formats.Width = new Unit (400.0, UnitType.Pixel);
    formats.EnableViewState = true;
    formats.AutoPostBack = true;
    formats.DataBound += new System.EventHandler (this.ondatabound_log_formats);
    formats.SelectedIndexChanged += new System.EventHandler (this.onchange_log_format);

    // Create a new cell for the format's control.
    TableCell format_cell = new TableCell ();
    format_cell.Controls.Add (formats);

    // Create a new table row for the new log format.
    TableRow new_row = new TableRow ();
    new_row.Cells.Add (prefix_cell);
    new_row.Cells.Add (format_cell);

    if (this.log_formats_.Rows.Count >= 2)
    {
      Literal where_stmt = new Literal ();
      where_stmt.Text = " where ";

      // Create the relation dropdown controls.
      DropDownList lhs_relation = new DropDownList ();
      lhs_relation.EnableViewState = true;

      Literal equal_sign = new Literal ();
      equal_sign.Text = " = ";

      DropDownList rhs_relation = new DropDownList ();
      rhs_relation.EnableViewState = true;

      // Create the relation cell for the table.
      TableCell relation_cell = new TableCell ();
      relation_cell.Controls.Add (where_stmt);
      relation_cell.Controls.Add (lhs_relation);
      relation_cell.Controls.Add (equal_sign);
      relation_cell.Controls.Add (rhs_relation);

      // Insert the relation cell into the row.
      new_row.Cells.Add (relation_cell);
    }

    // Insert the new row into the table.
    this.log_formats_.Rows.Add (new_row);

    if (!use_viewstate)
    {
      // Bind the data to the dropdown list control. This will trigger the
      // ondatabound event, which will initialize the prefix label.
      string sql = "SELECT lfid, lfmt FROM log_formats";
      DataTable data = execute_mysql_adapter (sql);

      formats.DataSource = data;
      formats.DataBind ();
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

  private DropDownList get_lhs_relation (TableCell relation_cell)
  {
    return (DropDownList)relation_cell.Controls[1];
  }

  private DropDownList get_rhs_relation (TableCell relation_cell)
  {
    return (DropDownList)relation_cell.Controls[3];
  }

  private void get_relations (TableRow row, out DropDownList lhs, out DropDownList rhs)
  {
    this.get_relations (row.Cells[2], out lhs, out rhs);
  }

  private void get_relations (TableCell row, out DropDownList lhs, out DropDownList rhs)
  {
    lhs = this.get_lhs_relation (row);
    rhs = this.get_rhs_relation (row);
  }

  private DropDownList get_log_format_control (TableRow row)
  {
    return this.get_log_format_control (row.Cells[1]);
  }

  private DropDownList get_log_format_control (TableCell cell)
  {
    return (DropDownList)cell.Controls[0];
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
    MySqlConnection conn = new MySqlConnection (ConfigurationManager.AppSettings["MySQL"]);
    conn.Open ();
    MySqlDataAdapter da = new MySqlDataAdapter (sql, conn);
    DataSet ds = new DataSet ();

    try
    {
       da.Fill (ds);
    }
    catch
    {
      throw new ArgumentException ("The sql executed was : " + sql);
    }
    finally
    {
      conn.Close ();
    }

    return ds.Tables[0];
  }

  override protected void OnInit (EventArgs e)
  {
    // Initialize the component.
    InitializeComponent ();

    // Pass control to the base class.
    base.OnInit (e);
  }

  private void InitializeComponent ()
  {
    // Set the page load callback.
    this.Load += new System.EventHandler (this.Page_Load);
  }
}
