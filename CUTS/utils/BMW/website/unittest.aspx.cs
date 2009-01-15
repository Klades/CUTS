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
using CUTS.Web.UI;

namespace CUTS
{
  public partial class Unit_Testing : System.Web.UI.Page
  {
    private MySqlConnection conn_ =
      new MySqlConnection (ConfigurationManager.AppSettings["MySQL"]);

    private CUTS.Master master_;

    private UnitTestActions uta_;

    public Unit_Testing ()
    {
      this.conn_.Open ();
      this.uta_ = new UnitTestActions (this.conn_);
    }

    protected void Page_Load (object sender, EventArgs e)
    {
      // Get the concrete master page.
      this.master_ = (CUTS.Master)Master;

      try
      {
        if (this.IsPostBack)
          return;

        // Load initial existing data
        this.load_existing_test_suites ();
        this.load_existing_packages ();
        this.load_existing_unit_tests ();

        // Select the log formats from the database.
        DataSet ds = new DataSet ();

        MySqlDataAdapter adapter = new MySqlDataAdapter ("SELECT lfid, lfmt FROM log_formats", this.conn_);
        adapter.Fill (ds, "logformats");

        // Select the relations from the database.
        adapter.SelectCommand.CommandText = "CALL cuts.select_log_format_variable_details_all ()";
        adapter.Fill (ds, "relations");

        this.log_format_table_.DataSource = ds;
        this.log_format_table_.DataMemberLogFormats = "logformats";
        this.log_format_table_.DataMemberRelations = "relations";
        this.log_format_table_.DataBind ();

        adapter.SelectCommand.CommandText = "CALL cuts.select_log_format_variable_details_all ()";
        adapter.Fill (ds, "variables");

        // Bind the data for the grouping.
        this.grouping_.DataSource = ds;
        this.grouping_.DataMember = "variables";
        this.grouping_.DataBind ();
      }
      catch (Exception ex)
      {
        this.master_.Console.Add (MessageSeverity.Error, ex.Message);
      }
    }

    /**
     * Intelligent validation method for listboxes. Determines
     *   the selection mode. If single, then will see if the
     *   selected index is > -1 or will see if there is only
     *   one item in the box (in which case, that item will
     *   be selected). If multiple, will check to see if any of
     *   the items in the box are selected. This is smarter than
     *   .NET's validation, so please do not delete it
     *   thinking it is unneeded.
     *
     * @param[in]  lb   The listbox that you would like to validate.
     */
    private bool is_valid_selection (ListBox lb)
    {
      if (lb.SelectionMode == ListSelectionMode.Single)
      {
        if (lb.SelectedIndex < 0)
        {
          // If there is only one, we can assume they wanted that one
          if (lb.Items.Count == 1)
          {
            lb.SelectedIndex = 0;

            // The appropriate selected index changed event
            // needs to be fired here, and this is the best I could find

            if (lb.ID == this.existing_test_suites_.ID)
            {
              this.onchange_existing_test_suites (null, null);
            }
            else if (lb.ID == this.current_test_packages_.ID)
            {
              this.onchange_current_test_packages (null, null);
            }
            else if (lb.ID == this.current_unit_tests_.ID)
            {
              this.onchange_current_unit_tests (null, null);
            }

            return true;
          }
          else
            return false;
        }
        else
          return true;
      }
      else
      {
        // This is a multiple selection box
        bool anything_selected = false;
        foreach (ListItem item in lb.Items)
          if (item.Selected == true)
          {
            anything_selected = true;
            break;
          }
        return anything_selected;
      }
    }


    #region Load Current
    /**
   * Helper method to load packages that are included inside the
   *   currently selected test suite. If no test suite is selected,
   *   the method will clear the current package list, and
   *   show an info message in the listbox.
   */
    private void load_current_packages ()
    {
      // Check that there is a test suite selected.
      if (this.is_valid_selection (this.existing_test_suites_) == false)
      {
        // Clear out packages
        this.current_test_packages_.Items.Clear ();

        // Disable appropriate package buttons
        this.insert_test_package_.Enabled = false;
        this.remove_test_package_.Enabled = false;
        //this.create_then_insert_test_package.Checked = false;
        //this.create_then_insert_test_package.Enabled = false;

        // Disable appropriate unit test buttons
        this.insert_unit_test_.Enabled = false;
        this.remove_unit_test_.Enabled = false;

        // Clear out unit tests
        this.current_unit_tests_.Items.Clear ();

        return;
      }

      // Get the test packages for the selected item.
      DataTable dt = this.uta_.get_packages (this.existing_test_suites_.SelectedValue);

      // Bind the data to the control.
      this.current_test_packages_.DataSource = dt;
      this.current_test_packages_.DataBind ();

      // Create variables used to ensure selection
      //   validity, reload the UI as needed, and
      //   enable/disable buttons as needed
      int current_package_count_ = dt.Rows.Count;
      bool is_valid_selection = this.is_valid_selection (this.current_test_packages_);

      // What to do if there are many test packages
      //   available, but there is not one selected
      if (is_valid_selection == false && (current_package_count_ > 0))
      {
        // Force the selection to be valid
        this.current_test_packages_.SelectedIndex = 0;

        // Ensure the selected index change was noticed.
        //   This should also force a reset of the unit test view
        this.onchange_current_test_packages (new object (), new EventArgs ());
      }
      else if (current_package_count_ == 0)
      {
        // Update UI to represent no current packages
        this.current_test_packages_.Items.Clear ();
        this.current_unit_tests_.Items.Clear ();
      }

      // Enable/Disable the insert_test_package button
      ListItem item;
      item = this.current_test_packages_.Items.FindByValue (this.existing_test_packages_.SelectedValue);
      if (item == null)
        this.insert_test_package_.Enabled = this.is_valid_selection (this.existing_test_suites_);
      else
        this.insert_test_package_.Enabled = false;

      this.remove_test_package_.Enabled = (current_package_count_ > 0);
      this.insert_unit_test_.Enabled = (current_package_count_ > 0);
      this.remove_unit_test_.Enabled = (current_package_count_ > 0);
    }

    /**
     * Helper method to load unit tests that are included inside the
     *   currently selected package. If there is not a valid
     *   package selected, the method will clear the current
     *   unit test list and show an info message in the
     *   listbox.
     */
    private void load_current_unit_tests ()
    {
      // Check that there is a package selected.
      if (this.is_valid_selection (this.current_test_packages_) == false)
      {
        // If not, update UI
        this.current_unit_tests_.Items.Clear ();
        return;
      }

      // Get the unit tests for the selected package.
      DataTable dt = this.uta_.get_unit_tests (this.current_test_packages_.SelectedValue);

      // Bind the data to the control.
      this.current_unit_tests_.DataSource = dt;
      this.current_unit_tests_.DataBind ();

      // Create variables used to ensure selection
      //   validity, reload the UI as needed, and
      //   enable/disable buttons as needed
      int current_unit_test_count_ = dt.Rows.Count;
      bool is_valid_selection = this.is_valid_selection (this.current_unit_tests_);

      // What to do if there are many unit tests
      //   available, but there is not one selected (indicitive of the selected one
      //   being removed)
      if (is_valid_selection == false && (current_unit_test_count_ > 0))
      {
        // Force the selection to be valid
        this.current_unit_tests_.SelectedIndex = 0;

        // Ensure the selected index change was noticed.
        //   This should also force a reset of the unit test view
        this.onchange_current_unit_tests (new object (), new EventArgs ());
      }
      else if (current_unit_test_count_ == 0)
      {
        // Update UI to represent no current packages
        this.current_unit_tests_.Items.Clear ();
      }

      // Enable/Disable the insert_unit_test_ button
      ListItem item;
      item = this.current_unit_tests_.Items.FindByValue (this.existing_unit_tests_.SelectedValue);
      if (item == null)
        this.insert_unit_test_.Enabled = true;
      else
        this.insert_unit_test_.Enabled = false;


      this.remove_unit_test_.Enabled = (current_unit_test_count_ > 0);
    }
    #endregion

    #region Load Existing
    /**
   * Helper method to load all the test suites from the database
   *   into the existing test suites listbox.
   */
    private void load_existing_test_suites ()
    {
      // Load Existing Test Suites
      DataTable dt = this.uta_.get_all_test_suites ();

      // Bind the data to the control. If you do not
      //   clear the current items, it will append
      this.existing_test_suites_.Items.Clear ();
      this.existing_test_suites_.DataSource = dt;
      this.existing_test_suites_.DataBind ();

      // Update the enabled options
      int count = dt.Rows.Count;
      this.remove_test_package_.Enabled = (count > 0);
      this.insert_test_package_.Enabled = (count > 0);
      this.insert_unit_test_.Enabled = (count > 0);
      this.remove_unit_test_.Enabled = (count > 0);
      //this.create_then_insert_test_package.Checked = (count > 0);
      //this.create_then_insert_test_package.Enabled = (count > 0);
    }

    /**
     * Loads all of the packages currently in the
     *   database into the existing packages dropdownlist.
     */
    private void load_existing_packages ()
    {
      // Get all the packages from the database.
      DataTable dt = this.uta_.get_all_packages ();

      // Bind the data to the control. If you do not
      //   clear the current items, it will append
      this.existing_test_packages_.Items.Clear ();
      this.existing_test_packages_.DataSource = dt;
      this.existing_test_packages_.DataBind ();

      // Update the enabled options
      int count = dt.Rows.Count;
      this.insert_test_package_.Enabled = (count > 0);
      this.delete_test_package_.Enabled = (count > 0);
      this.remove_test_package_.Enabled = (count > 0);
      this.insert_unit_test_.Enabled = (count > 0);
      this.remove_unit_test_.Enabled = (count > 0);
    }

    /**
     * Loads all of the unit tests currently in
     *   the database into the existing unit tests dropdownlist.
     */
    private void load_existing_unit_tests ()
    {
      // Get the data
      DataTable dt = this.uta_.get_all_unit_tests ();

      // Bind the data to the control. If you do not
      //   clear the current items, it will append
      this.existing_unit_tests_.Items.Clear ();
      this.existing_unit_tests_.DataSource = dt;
      this.existing_unit_tests_.DataBind ();

      // Update the enabled options
      int count = dt.Rows.Count;
      this.insert_unit_test_.Enabled = (count > 0);
      this.remove_unit_test_.Enabled = (count > 0);
      this.delete_unit_test_.Enabled = (count > 0);
    }
    #endregion

    #region Button Handlers
    /**
   * Button handler function that attempts to create a new test suite,
   *   reload the listbox containing the suites if it
   *   is created, and select the TS just created.
   *
   * @param[in]     sender    The button that sent the click event.
   * @param[in]     e         The EventArgs that were sent with the event.
   */
    protected void onclick_create_test_suite (object sender, EventArgs e)
    {
      string name = this.test_suite_name_.Text;

      try
      {
        // Create the new test suite.
        this.uta_.insert_test_suite (name);
        this.master_.Console.Add (MessageSeverity.Info,
                                  "Succesfully created " + name +
                                  " test suite");

        this.test_suite_name_.Text = "";

        // Reload the data
        this.load_existing_test_suites ();
      }
      catch (Exception ex)
      {
        // Show error message
        this.master_.Console.Add (MessageSeverity.Error, ex.Message);
        this.master_.Console.Add (MessageSeverity.Error, "Failed to create test suite " + name);
      }
      finally
      {
        // Attempt to select the test suite
        ListItem item = this.existing_test_suites_.Items.FindByText (name);
        if (item != null)
        {
          // Select the item
          this.existing_test_suites_.SelectedIndex = existing_test_suites_.Items.IndexOf (item);

          // Ensure the onchange event is fired no matter where in the page
          //   lifecycle we are
          this.onchange_existing_test_suites (new object (), new EventArgs ());
        }
      }
    }

    /**
     * Button handler function that attempts to create a new test
     *   package, reload the existing package list, and select the
     *   package just created. An error is shown if the creation
     *   fails. There are minor bugs in this function that could
     *   occur if a test package is created, but fails to insert.
     *   The user interface might not be fully updated. The fix
     *   is to revamp this function.
     *
     * @param[in]     sender    The button that sent the click event.
     * @param[in]     e         The EventArgs that were sent with the event.
     */
    protected void onclick_create_test_package (object sender, EventArgs e)
    {
      string name = this.test_package_name_.Text;

      try
      {
        // Create the test package
        this.uta_.create_test_package (name);

        // Show info message
        this.master_.Console.Add (MessageSeverity.Info,
                                  "Succesfully created " + name +
                                  " test package");

        // Update the UI
        this.load_existing_packages ();
        this.test_package_name_.Text = "";

        // If we are here, no errors have been thrown
        // Attempt to select the test package
        ListItem item = this.existing_test_packages_.Items.FindByText (name);

        if (item != null)
        {
          // Select the item
          this.existing_test_packages_.SelectedIndex = this.existing_test_packages_.Items.IndexOf (item);

          // Ensure the onchange event is fired no matter where in the page
          //   lifecycle we are
          this.onchange_existing_test_packages (new object (), new EventArgs ());
        }
      }
      catch (Exception ex)
      {
        // Show current message
        this.master_.Console.Add (MessageSeverity.Error, ex.Message);

        // Show more meaningful message
        this.master_.Console.Add (MessageSeverity.Error, "Failed to create test package " + name);
      }
    }

    /**
     * Button Handler function that is used to delete a test
     *   package, print a message out for success or failure,
     *   and reload the packages lists so they are updated.
     *   If the test package cannot be deleted, then the
     *   function will attempt to print a list of test suites
     *   it must be removed from before it can be safely
     *   deleted.
     *
     * @param[in]     sender    The button that sent the click event.
     * @param[in]     e         The EventArgs that were sent with the event.
     */
    protected void onclick_delete_test_package (object sender, EventArgs e)
    {
      // Check that the selected one is valid
      if (this.existing_test_packages_.SelectedIndex == -1)
      {
        this.master_.Console.Add (MessageSeverity.Error, "Please select a valid test package to " +
          "delete. ");
        return;
      }

      string name = this.existing_test_packages_.SelectedItem.Text;

      try
      {
        // Delete the package from the database.
        this.uta_.delete_test_package (this.existing_test_packages_.SelectedValue);

        // Show success message
        string msg = "Successfully deleted " + name + " test package from database";
        this.master_.Console.Add (MessageSeverity.Info, msg);

        // Reload all the existing and current lists
        this.load_existing_packages ();
        this.load_current_packages ();
      }
      catch (Exception ex)
      {
        DataTable dt =
          this.uta_.containing_test_suites (this.existing_test_packages_.SelectedValue);

        // Show current message
        this.master_.Console.Add (MessageSeverity.Error, ex.Message);

        // Show more meaningful message
        string message = "Failed to delete " + name + " test package";

        // Attempting to add a list of the test suites that
        //   the package is currently added to
        if (dt.Rows.Count != 0)
        {
          message += ", because it is contained in the following test suites " +
            "and must be 'Removed' from them before it can be safely deleted. " +
            " Contained in ";
          foreach (DataRow row in dt.Rows)
            message += (string)row[0] + ",";

          message = message.Remove (message.LastIndexOf (','));
        }
        this.master_.Console.Add (MessageSeverity.Error, message);
      }
    }

    /**
     * Handler for clicking the link button to delete a unit test from the
     * database.
     *
     * @param[in]     sender    The button that sent the click event.
     * @param[in]     e         The EventArgs that were sent with the event.
     */
    protected void onclick_delete_unit_test_from_database (object sender, EventArgs e)
    {
      if (this.existing_unit_tests_.SelectedIndex != -1)
      {
        string name = this.existing_unit_tests_.SelectedItem.Text;

        try
        {
          // Remove the unit test from the database, if possible.
          this.uta_.delete_unit_test (this.existing_unit_tests_.SelectedValue);
          this.master_.Console.Add (MessageSeverity.Info,
                                    "Successfully deleted " + name +
                                    " unit test from database");

          // Force reloading of the unit tests.
          this.load_existing_unit_tests ();
        }
        catch (Exception ex)
        {
          this.master_.Console.Add (MessageSeverity.Error, ex.Message);
          this.master_.Console.Add (MessageSeverity.Error, "Failed to delete " + name + " unit test from database");
        }
      }
      else
      {
        this.master_.Console.Add (MessageSeverity.Error, "Please select a valid unit test to delete");
      }
    }

    /**
     * Button handler function that deletes the selected test suites,
     *   printing out error or success messages as it goes, and reloading
     *   the interface correctly at the end.
     *
     * @param[in]     sender    The button that sent the click event.
     * @param[in]     e         The EventArgs that were sent with the event.
     */
    protected void onclick_delete_test_suite (object sender, EventArgs e)
    {
      // Check if any of the test suites are selected
      if (this.is_valid_selection (this.existing_test_suites_) == false)
      {
        this.master_.Console.Add (MessageSeverity.Error, "Please select a valid test suite to delete");
        return;
      }

      // Iterate through the items, deleting them as we go
      foreach (ListItem item in this.existing_test_suites_.Items)
        if (item.Selected)
        {
          try
          {
            // Delete the test suite from the database.
            this.uta_.delete_test_suite (item.Value);

            // Show a message to the user.
            string msg = "Successfully deleted test suite " + item.Text;
            this.master_.Console.Add (MessageSeverity.Info, msg);
          }
          catch (Exception ex)
          {
            this.master_.Console.Add (MessageSeverity.Error, ex.Message);
            this.master_.Console.Add (MessageSeverity.Error, "Failed to delete test suite " + item.Text);
          }
        }

      // Reload existing test suites
      this.load_existing_test_suites ();
      this.load_current_packages ();
    }

    /**
   * Button handler function that removes a test package from
   *   a test suite, reloads the current package list, and
   *   prints an info message.
   *
   * @param[in]     sender    The button that sent the click event.
   * @param[in]     e         The EventArgs that were sent with the event.
   */
    protected void onclick_remove_test_package (object sender, EventArgs e)
    {
      // Check that the test package selection is valid
      if (this.is_valid_selection (this.current_test_packages_) == false)
      {
        string message = "Please select a valid test package to remove.";
        this.master_.Console.Add (MessageSeverity.Error, message);
        return;
      }

      // Check that the test suite selection is valid
      if (this.is_valid_selection (this.existing_test_suites_) == false)
      {
        string message = "Please select a valid test suite to remove the test package from.";
        this.master_.Console.Add (MessageSeverity.Error, message);
        return;
      }

      // Iterate through the items, deleting them as we go
      foreach (ListItem item in this.current_test_packages_.Items)
        if (item.Selected)
        {

          // Get the name of the test suite
          string suite_name_ = this.existing_test_suites_.SelectedItem.Text;
          string package_name_ = item.Text;

          try
          {
            // Remove the package from the test suite.
            this.uta_.remove_package (this.existing_test_suites_.SelectedValue,
                                            item.Value);

            string msg =
              "Successfully removed " + package_name_ +
              " test package from " + suite_name_ + " test suite";

            // Show the message to the user.
            this.master_.Console.Add (MessageSeverity.Info, msg);
          }
          catch (Exception ex)
          {
            // Show the current exception.
            this.master_.Console.Add (MessageSeverity.Error, ex.Message);

            // Show a more meaningful message.
            string msg = "Failed to remove selected package from " + suite_name_ + " test suite";
            this.master_.Console.Add (MessageSeverity.Error, msg);
          }
        }

      // Update the current packages.
      this.load_current_packages ();
    }

    /**
     * Handler for clicking the link button to remove an existing unit test
     * from the active test package.
     *
     * @param[in]     sender    The button that sent the click event.
     * @param[in]     e         The EventArgs that were sent with the event.
     */
    protected void onclick_remove_unit_test_from_test_package (object sender, EventArgs e)
    {
      // Check that the unit test selection is valid
      if (this.is_valid_selection (this.current_unit_tests_) == false)
      {
        string message = "Please select a valid unit test to remove.";
        this.master_.Console.Add (MessageSeverity.Error, message);
        return;
      }

      // Check that the test package selection is valid
      if (this.is_valid_selection (this.current_test_packages_) == false)
      {
        string message = "Please select a valid test package to remove the unit test from.";
        this.master_.Console.Add (MessageSeverity.Error, message);
        return;
      }

      // Iterate through the items, deleting them as we go
      foreach (ListItem item in this.current_unit_tests_.Items)
      {
        if (item.Selected)
        {
          // Get the name of the test package and unit test
          string unit_test_name = item.Text;
          string package_name = this.current_test_packages_.SelectedItem.Text;

          try
          {
            // Remove the unit test from the package.
            this.uta_.remove_unit_test (this.current_test_packages_.SelectedValue,
                                        item.Value);

            string msg =
              "Successfully removed " + unit_test_name +
              " unit test from " + package_name + " test package";

            // Show the message to the user.
            this.master_.Console.Add (MessageSeverity.Info, msg);
          }
          catch (Exception ex)
          {
            // Show the current exception.
            this.master_.Console.Add (MessageSeverity.Error, ex.Message);

            // Show a more meaningful message.
            string message =
              "Failed to remove " + unit_test_name +
              " unit test from " + package_name + " test package";

            this.master_.Console.Add (MessageSeverity.Error, message);
          }
        }
      }

      // Update current unit tests list.
      this.load_current_unit_tests ();
    }

    /**
     * Button handler function that inserts a test package into the selected
     *   test suite, giving confirmation or error messages.
     *
     * @param[in]     sender    The button that sent the click event.
     * @param[in]     e         The EventArgs that were sent with the event.
     */
    protected void onclick_insert_test_package (object sender, EventArgs e)
    {
      // Check if any of the test suites are selected
      if (this.is_valid_selection (this.existing_test_suites_) == false)
      {
        this.master_.Console.Add (MessageSeverity.Error, "Please select a test suite to add test package");
        return;
      }

      string package_name = this.existing_test_packages_.SelectedItem.Text;
      string test_suite_name = this.existing_test_suites_.SelectedItem.Text;

      try
      {
        // Add the package to the test suite.
        this.uta_.insert_new_package (this.existing_test_suites_.SelectedValue, package_name);

        // Show a message to the user
        string message =
          "Successfully added " + package_name + " test package to " +
          test_suite_name + " test suite";

        this.master_.Console.Add (MessageSeverity.Info, message);

        // Reload the packages for the selected test suite.
        this.load_current_packages ();
      }
      catch (Exception ex)
      {
        // Show current message
        this.master_.Console.Add (MessageSeverity.Error, ex.Message);

        DataTable dt = this.uta_.get_packages (this.existing_test_suites_.SelectedValue);

        DataColumn[] keys = new DataColumn[1];
        keys[0] = dt.Columns["name"];
        dt.PrimaryKey = keys;

        if (dt.Rows.Contains (package_name))
        {
          // Show a more meaningful message
          string message =
            "Test suite " + test_suite_name +
            " already contains test package " + package_name;

          this.master_.Console.Add (MessageSeverity.Error, message);
        }
        else
        {
          string message = "Failed to create " + package_name + " test package";
          this.master_.Console.Add (MessageSeverity.Error, message);
        }
      }
    }

    /**
    * Button handler function that inserts a unit test into the selected
    *   test package, giving confirmation or error messages.
    *
    * @param[in]     sender    The button that sent the click event.
    * @param[in]     e         The EventArgs that were sent with the event.
    */
    protected void onclick_insert_unit_test (object sender, EventArgs e)
    {
      // Validate selected test package
      if (this.is_valid_selection (this.current_test_packages_) == false)
      {
        this.master_.Console.Add (MessageSeverity.Error, "Please select a valid test package to add the unit test to. ");
        return;
      }

      string package_name = this.current_test_packages_.SelectedItem.Text;
      string unit_test_name = this.existing_unit_tests_.SelectedItem.Text;

      try
      {
        // Add the unit test
        this.uta_.insert_existing_unit_test (this.current_test_packages_.SelectedValue,
                                             this.existing_unit_tests_.SelectedValue);

        // Display useful message to the user.
        string message =
          "Successfully added " + unit_test_name +
          " unit test to " + package_name + " test package";

        this.master_.Console.Add (MessageSeverity.Info, message);

        // Reload the unit tests.
        this.load_current_unit_tests ();
      }
      catch (Exception ex)
      {
        // Show current message
        this.master_.Console.Add (MessageSeverity.Error, ex.Message);

        DataTable dt = this.uta_.get_unit_tests (this.current_test_packages_.SelectedValue);

        DataColumn[] keys = new DataColumn[1];
        keys[0] = dt.Columns["name"];
        dt.PrimaryKey = keys;

        if (dt.Rows.Contains (unit_test_name))
        {
          // Show a more meaningful message
          this.master_.Console.Add (MessageSeverity.Error, "Test package " + package_name +
            " already contains unit test " + unit_test_name);
        }
        else
        {
          this.master_.Console.Add (MessageSeverity.Error, "Failed to create " + unit_test_name + " unit test");
        }
      }
    }

    #endregion

    #region On Change Handlers
    /**
   * OnChange handler for the existing test suites list. Checks the
   *   selection validity, enables/disables buttons as needed, and
   *   then loads the current package list if the test suite selection
   *   is valid.
   *
   * @param[in]     sender    The onject that sent the onchange event.
   * @param[in]     e         The EventArgs that were sent with the event.
   */
    protected void onchange_existing_test_suites (object sender, EventArgs e)
    {
      // Check that there is a valid selection
      if (this.is_valid_selection (this.existing_test_suites_) == false)
      {
        // Disable appropriate buttons
        this.insert_test_package_.Enabled = false;
        this.remove_test_package_.Enabled = false;
        this.insert_unit_test_.Enabled = false;
        this.remove_unit_test_.Enabled = false;

        return;
      }

      // Ensure valid buttons are enabled
      this.insert_test_package_.Enabled = true;
      this.remove_test_package_.Enabled = true;
      this.insert_unit_test_.Enabled = true;
      this.remove_unit_test_.Enabled = true;

      // Load the packages for the selected test suite.
      this.load_current_packages ();
    }

    /**
     * On Change Handler for the existing test packages. Function
     *   checks to see if the selected test package exists in the current
     *   test packages list, disables/enables appropriate buttons,
     *   and possibly selects the test package in the current test packages
     *   list.
     *
     * @param[in]     sender    The onject that sent the onchange event.
     * @param[in]     e         The EventArgs that were sent with the event.
     */
    protected void onchange_existing_test_packages (object sender, EventArgs e)
    {
      // Save the package id
      string selected_package_id = this.existing_test_packages_.SelectedValue;

      // See if that package exists in the current test packages list
      ListItem item = this.current_test_packages_.Items.FindByValue (selected_package_id);

      // If item exists
      if (item != null)
      {
        // Select it in the current test package list
        this.current_test_packages_.SelectedIndex = this.current_test_packages_.Items.IndexOf (item);

        // Make sure the change in the selected index is noticed
        this.onchange_current_test_packages (new object (), new EventArgs ());

        // Enable/Disable the correct buttons
        this.insert_test_package_.Enabled = false;
        this.remove_test_package_.Enabled = true;
      }
      else
      {
        // Enable/Disable the correct buttons
        this.insert_test_package_.Enabled = true;
        this.remove_test_package_.Enabled = false;
      }
    }

    /**
     * On Change Handler for the existing unit tests. Function
     *   checks to see if the selected unit test exists in the current
     *   unit tests list, disables/enables appropriate buttons,
     *   and possibly selects the unit test in the current unit tests
     *   list.
     *
     * @param[in]     sender    The onject that sent the onchange event.
     * @param[in]     e         The EventArgs that were sent with the event.
     */
    protected void onchange_existing_unit_tests (object sender, EventArgs e)
    {
      // Save the unit test
      string selected_unit_test_id = this.existing_unit_tests_.SelectedValue;

      // See if that unit test exists in the current unit tests list
      ListItem item = this.current_unit_tests_.Items.FindByValue (selected_unit_test_id);

      // If item exists
      if (item != null)
      {
        // Select it in the current unit test list
        this.current_unit_tests_.SelectedIndex = this.current_unit_tests_.Items.IndexOf (item);

        // Make sure the change in the selected index is noticed
        this.onchange_current_unit_tests (new object (), new EventArgs ());

        // Enable/Disable the correct buttons
        this.insert_unit_test_.Enabled = false;
        this.remove_unit_test_.Enabled = true;
      }
      else
      {
        // Enable/Disable the correct buttons
        this.insert_unit_test_.Enabled = true;
        this.remove_unit_test_.Enabled = false;
      }
    }

    /**
     * On Change handler for current test packages. Reloads
     *   the current unit tests list as needed, and updates
     *   the existing test packages list to have the same
     *   selection.
     *
     * @param[in]     sender    The onject that sent the onchange event.
     * @param[in]     e         The EventArgs that were sent with the event.
     */
    protected void onchange_current_test_packages (object sender, EventArgs e)
    {
      // Load the new current unit tests list
      this.load_current_unit_tests ();

      // Save the unit test id
      string package_id_ = this.current_test_packages_.SelectedValue;

      // Update the existing unit tests list
      ListItem item = this.existing_test_packages_.Items.FindByValue (package_id_);
      this.existing_test_packages_.SelectedIndex = this.existing_test_packages_.Items.IndexOf (item);
    }

    /**
     * On Change handler for current unit tests. Updates the existing unit tests
     *   list to have the same selection, and reloads the UI as needed.
     *   Easily extendable to add in showing unit test details.
     *
     * @param[in]     sender    The onject that sent the onchange event.
     * @param[in]     e         The EventArgs that were sent with the event.
     */
    protected void onchange_current_unit_tests (object sender, EventArgs e)
    {
      // Because the load_current_unit_tests rebinds the data
      // you loose the selected index. So, it is saved and
      // restored here, rather than creating a "reload_current_unit_tests"
      bool[] selected = new bool[this.current_unit_tests_.Items.Count];
      for (int i = 0; i < this.current_unit_tests_.Items.Count; ++i)
        selected[i] = this.current_unit_tests_.Items[i].Selected;

      // Reload the UI as needed
      load_current_unit_tests ();

      // Restore previous selection
      for (int i = 0; i < this.current_unit_tests_.Items.Count; ++i)
        this.current_unit_tests_.Items[i].Selected = selected[i];

      // Save the unit test id
      string unit_test_id_ = this.current_unit_tests_.SelectedValue;

      // Update the existing unit tests list
      ListItem item = this.existing_unit_tests_.Items.FindByValue (unit_test_id_);
      this.existing_unit_tests_.SelectedIndex = this.existing_unit_tests_.Items.IndexOf (item);
    }

    #endregion


    protected void handle_onmenuitemclick (Object sender, MenuEventArgs e)
    {
      this.multiview_.ActiveViewIndex = int.Parse (e.Item.Value);
    }

    protected void handle_onactiveviewchanged (Object sender, EventArgs e)
    {
      switch (this.multiview_.ActiveViewIndex)
      {
        case 0:
          this.load_existing_test_suites ();
          this.load_existing_packages ();
          this.load_existing_unit_tests ();
          break;

        case 1:
          break;
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

      int[] lfids = this.log_format_table_.SelectedLogFormats;
      CUTS.Data.Relation [] relations = this.log_format_table_.SelectedRelations;

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
      variables.Add ("Formats", lfids);
      variables.Add ("Relations", relations);
      variables.Add ("Groupings", this.grouping_.Variables);

      try
      {
        // Insert the neq unit test into the database.
        this.uta_.insert_new_unit_test (variables);
        this.master_.Console.Add (MessageSeverity.Info, "Successfully created new unit test");

        // Reset the unit test form.
        this.reset_unit_test_form ();
      }
      catch (Exception ex)
      {
        this.master_.Console.Add (MessageSeverity.Error, ex.Message);
        this.master_.Console.Add (MessageSeverity.Error, "Failed to create new unit test");
      }
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
      this.log_format_table_.Clear ();
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
          master_.Console.Add (MessageSeverity.Error, "The warn or fail comparison had a problem." +
            "Please refresh the page and try again.");
          return String.Empty;
      }
    }

    private DropDownList get_log_format_control (TableRow row)
    {
      return this.get_log_format_control (row.Cells[1]);
    }

    private DropDownList get_log_format_control (TableCell cell)
    {
      return (DropDownList)cell.Controls[0];
    }

    override protected void OnInit (EventArgs e)
    {
      // Initialize the component.
      this.InitializeComponent ();

      // Pass control to the base class.
      base.OnInit (e);
    }

    private void InitializeComponent ()
    {
      // Set the page load callback.
      this.Load += new System.EventHandler (this.Page_Load);
    }
  }
}