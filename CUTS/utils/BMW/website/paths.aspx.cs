// $Id$

//=============================================================================
/**
 * @file    Execution_Paths.aspx.cs
 */
//=============================================================================

using System;
using System.Collections;
using System.ComponentModel;
using System.Configuration;
using System.Data;
using System.Drawing;
using System.Web;
using System.Web.SessionState;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.HtmlControls;
using MySql.Data.MySqlClient;

namespace CUTS
{
  /**
   * @class Execution_Paths
   *
   * Code-behind for the Execution_Paths.aspx webpage.
   */
  public partial class Execution_Paths : System.Web.UI.Page
  {
    static private string PATH_ELEMENTS_TABLE = "execution_path_elements";

    static private string INSTANCE_TABLE = "execution_paths";

    private CUTS.Data.Database database_;

    private CUTS.Master master_;

    /**
     * Callback method for when the page is loading.
     *
     * @param[in]         sender          Sender of the event.
     * @param[in]         e               Event arguments.
     */
    private void Page_Load (object sender, System.EventArgs e)
    {
      this.master_ = (CUTS.Master)this.Master;
      MySqlConnection conn = new MySqlConnection (ConfigurationManager.AppSettings ["MySQL"]);

      try
      {
        // Open a connection to the database.
        conn.Open ();

        // Create a new database object the newly created connection.
        this.database_ =
          new CUTS.Data.Database (conn, new CUTS.Data.MySqlDataAdapterFactory ());

        if (!Page.IsPostBack)
        {
          // Open the connection and create an adapter.
          this.InitializeCritialPaths ();

          // Determine if there is a request to display a path.
          string p_query = Request.QueryString ["p"];

          if (p_query != null)
          {
            // Get the path to query.
            long path_id = Int32.Parse (p_query);
            Session ["path_id"] = path_id;

            // Update the name of the selected path.
            DataTable paths = (DataTable)this.paths_.DataSource;
            DataRow [] rows = paths.Select (String.Format ("path_id = {0}", path_id));

            this.notice_.Text =
              "<p>You are now editing the " + rows [0] ["path_name"].ToString () +
              " execution path. Use the controls below to add new instances to the " +
              " execution path sequence.</p>";

            DataSet ds = new DataSet ();

            // Fill the adapter w/ the path element data.
            MySqlDataAdapter path_adapter = this.CreatePathElementAdapter (conn, path_id);
            path_adapter.Fill (ds, PATH_ELEMENTS_TABLE);

            DataTable table = ds.Tables [PATH_ELEMENTS_TABLE];
            DataColumn [] primary_key = new DataColumn [1];
            primary_key [0] = table.Columns ["path_order"];
            table.PrimaryKey = primary_key;

            // Fill the dataset with the instance data.
            MySqlDataAdapter inst_adapter = Execution_Paths.create_instance_adapter (conn);
            inst_adapter.Fill (ds, Execution_Paths.INSTANCE_TABLE);

            // Update the view.
            UpdateView (ds);
            Session ["dataset"] = ds;
          }
        }
      }
      catch (Exception ex)
      {
        this.master_.show_error_message (ex.Message);
      }
    }

    /**
     * Event handler for clicking the button to create a critical
     * path. The critical path is created by inserting a new record
     * into the database and then requesting the new information form
     * the database.
     *
     * @param[in]     sender        Sender of the event.
     * @param[in]     e             Event arguments.
     */
    protected void CreateCritcalPath (Object sender, EventArgs e)
    {
      try
      {
        // Update the database with the new path.
        this.database_.insert_execution_path (this.path_name_.Text,
                                              Int32.Parse (this.deadline_.Text));

        // Reinitialize the critical path table,
        this.InitializeCritialPaths ();
      }
      catch (Exception ex)
      {
        this.master_.show_error_message (ex.Message);
      }
    }

    /**
     * Helper method for initializing the critical paths table. This
     * method contacts the database and retrieve the latest information
     * about the registered critical paths.
     */
    private void InitializeCritialPaths ()
    {
      // Select all the execution paths in the database.
      DataSet ds = new DataSet ();
      this.database_.select_execution_paths (ref ds);

      // Bind the data source to the control.
      this.paths_.DataSource = ds.Tables ["Table"];
      this.paths_.DataBind ();
    }

    protected void path_elements_OnItemCreated (Object sender, DataGridItemEventArgs e)
    {
      ListItemType type = e.Item.ItemType;

      switch (e.Item.ItemType)
      {
        case ListItemType.Pager:
          // Update the pager so that it spans the entire grid.
          Label page_label = new Label ();
          page_label.Text = "Page(s): ";

          TableCell pager = (TableCell)e.Item.Controls [0];
          pager.Controls.AddAt (0, page_label);
          break;
      }
    }

    protected void button_delete_path (Object sender, EventArgs e)
    {

    }

    protected void PathElement_Insert (Object sender, EventArgs e)
    {
      // Get the dataset for the session.
      DataSet ds = (DataSet)Session ["dataset"];

      // Get the path table from the dataset and create a new row.
      DataTable table = ds.Tables [Execution_Paths.PATH_ELEMENTS_TABLE];
      DataRow dr = table.NewRow ();

      // Initialize all the elements in the row. This will mean setting
      // the id and text of all the cells.
      dr ["path_id"] = Session ["path_id"];
      dr ["path_order"] = Int32.Parse (this.order_.Text);

      dr ["instance"] = Int32.Parse (this.instance_.SelectedValue);
      dr ["component_name"] = this.instance_.SelectedItem.Text;

      dr ["inport"] = this.src_.SelectedValue;
      dr ["inport_name"] = this.src_.SelectedItem.Text;

      dr ["outport"] = this.dst_.SelectedValue;
      dr ["outport_name"] = this.dst_.SelectedItem.Text;

      // Insert the row at the end of6 the list.
      table.Rows.Add (dr);

      UpdateView (ds);
      Session ["dataset"] = ds;
    }

    protected void PathElement_Commit (Object sender, EventArgs e)
    {
      // Get the dataset for the session.
      DataSet ds = (DataSet)Session ["dataset"];

      try
      {
        // Update the information in the database.
        long path_id = (long)Session ["path_id"];

        MySqlDataAdapter adapter =
          this.CreatePathElementAdapter ((MySqlConnection) this.database_.Connection, path_id);

        adapter.Update (ds, Execution_Paths.PATH_ELEMENTS_TABLE);

        // Refresh the view.
        UpdateView (ds);
      }
      catch (Exception ex)
      {
        this.master_.show_error_message (ex.Message);
      }
    }

    /**
     * Helper method that updates the view of the webpage. This includes
     * updating the table that contains the critical paths, and the table
     * that contains the critical path elements.
     *
     * @param[in]       ds          The source dataset.
     */
    private void UpdateView (DataSet ds)
    {
      // Bind the path elements table.
      if (ds.Tables.Contains (PATH_ELEMENTS_TABLE))
      {
        this.path_elements_.DataSource = ds.Tables [PATH_ELEMENTS_TABLE].DefaultView;
        this.path_elements_.DataBind ();

        // Calculate the next index for the user. We do not want to rely on
        // auto increment in this case since the path_order can consist of
        // non-consecutive numbers.
        Object result = ds.Tables [PATH_ELEMENTS_TABLE].Compute ("MAX(path_order)", "");

        if (result != System.DBNull.Value)
          this.order_.Text = String.Format ("{0}", (int)result + 1);
        else
          this.order_.Text = "1";
      }

      if (ds.Tables.Contains (INSTANCE_TABLE))
      {
        this.instance_.DataSource = ds.Tables [INSTANCE_TABLE].DefaultView;
        this.instance_.DataBind ();
      }
    }

    private MySqlDataAdapter CreatePathElementAdapter (MySqlConnection conn,
                                                       long path_id)
    {
      // SQL command for selecting the elements in the critical path
      // for the specified path.
      MySqlCommand select_command =
        new MySqlCommand ("CALL cuts.select_execution_path_elements_i(?path_id)", conn);

      select_command.Parameters.AddWithValue ("?path_id", path_id);
      MySqlDataAdapter adapter = new MySqlDataAdapter (select_command);

      // Create the insert command for the table.
      System.Text.StringBuilder insert_sql = new System.Text.StringBuilder ();
      insert_sql.Append ("INSERT INTO execution_path_elements (path_id, path_order, ");
      insert_sql.Append ("instance, inport, outport) VALUES (?path_id, ?path_order, ");
      insert_sql.Append ("?instance, ?inport, ?outport)");

      MySqlCommand insert_command = conn.CreateCommand ();
      insert_command.CommandText = insert_sql.ToString ();
      insert_command.Parameters.Add ("?path_id", MySqlDbType.Int32, 0, "path_id");
      insert_command.Parameters.Add ("?path_order", MySqlDbType.Int32, 0, "path_order");
      insert_command.Parameters.Add ("?instance", MySqlDbType.Int32, 0, "instance");
      insert_command.Parameters.Add ("?inport", MySqlDbType.Int32, 0, "inport");
      insert_command.Parameters.Add ("?outport", MySqlDbType.Int32, 0, "outport");
      adapter.InsertCommand = insert_command;

      System.Text.StringBuilder delete_sql = new System.Text.StringBuilder ();
      delete_sql.Append ("DELETE FROM execution_path_elements ");
      delete_sql.Append ("WHERE path_id = ?path_id AND path_order = ?path_order");

      MySqlCommand delete_command = conn.CreateCommand ();
      delete_command.CommandText = delete_sql.ToString ();
      delete_command.Parameters.Add ("?path_id", MySqlDbType.Int32, 0, "path_id");
      delete_command.Parameters.Add ("?path_order", MySqlDbType.Int32, 0, "path_order");
      adapter.DeleteCommand = delete_command;

      return adapter;
    }

    static private MySqlDataAdapter create_instance_adapter (MySqlConnection conn)
    {
      return
        new MySqlDataAdapter ("SELECT * FROM component_instances ORDER BY component_name",
                              conn);
    }

    /**
     * Handler for the OnSelectedIndexChanged for the instance_ object. When
     * this handler is invoked, it updates the source and sinks for the
     * selected component.
     */
    protected void instance_OnSelectedIndexChanged (Object sender, EventArgs e)
    {
      // Get the id of the selected instance.
      int inst = Int32.Parse (this.instance_.SelectedValue);

      // Select the sinks and sources for this instance.
      DataSet ds = new DataSet ();
      this.database_.select_component_portnames_i (inst, "sink", ref ds);
      this.database_.select_component_portnames_i (inst, "sources", ref ds);

      // Bind the different ports to their respective controls.
      this.src_.DataSource = ds.Tables ["Table"];
      this.src_.DataBind ();

      this.dst_.DataSource = ds.Tables ["Table1"];
      this.dst_.DataBind ();
    }

    /**
     * Default handler for the oncommand event.
     *
     * @param[in]       sender        Sender of the event.
     * @param[in]       e             Arguments for the event.
     */
    protected void OnCommand (Object sender, CommandEventArgs e)
    {
      if (e.CommandName == "DeletePathElement")
      {
        DataSet ds = (DataSet)Session ["dataset"];
        DataTable dt = ds.Tables [PATH_ELEMENTS_TABLE];
        DataRow row = dt.Rows.Find (e.CommandArgument);

        if (row != null)
        {
          // Delete the row and update the view.
          row.Delete ();
          this.UpdateView (ds);

          // Save the dataset.
          Session ["dataset"] = ds;
        }
      }
    }

    /**
     * Callback method for selecting all the test on the
     * current page.
     *
     * @param[in]       e       Arguments for the event.
     */
    protected void toggle_delete_path_elements (object sender, System.EventArgs e)
    {
      // The sender of this event is a <CheckBox>
      CheckBox check = (CheckBox)sender;

      foreach (DataGridItem item in this.path_elements_.Items)
      {
        CheckBox action = (CheckBox)item.FindControl ("delete_");
        action.Checked = check.Checked;
      }
    }

    /**
     * Callback method for clicking the Delete checkbox in the header of
     * the execution paths.
     *
     * @param[in]         sender          Sender of event
     * @param[in]         e               Arguments associated with event
     */
    protected void toggle_delete_paths (object sender, System.EventArgs e)
    {
      CheckBox check = (CheckBox)sender;

      foreach (DataGridItem item in this.paths_.Items)
      {
        CheckBox action = (CheckBox)item.FindControl ("delete_");
        action.Checked = check.Checked;
      }
    }

    /**
     * Callback method for clicking the "Delete All" link.
     *
     * @param[in]       sender        Sender of the event.
     */
    protected void delete_selected_execution_paths (object sender, System.EventArgs e)
    {
      // Create a list for holding the selected numbers.
      ArrayList list = new ArrayList ();

      try
      {
        foreach (DataGridItem item in this.paths_.Items)
        {
          // Locate the <action_> control since it's the checkbox
          // that determines the action of the current test.
          CheckBox action = (CheckBox)item.FindControl ("delete_");

          if (action != null && action.Checked)
          {
            // Add the test number to the list if we are checked.
            System.Int32 path_id =
              (System.Int32)this.paths_.DataKeys [item.ItemIndex];

            list.Add (path_id);
          }
        }

        if (list.Count > 0)
        {
          // Let's convert the array to an <System.Int32> array
          // and pass control to the database utility.
          System.Int32 [] path_id_list =
            (System.Int32 [])list.ToArray (typeof (System.Int32));

          this.database_.delete_execution_paths (path_id_list);
        }

        // Update the view.
        this.InitializeCritialPaths ();
      }
      catch (Exception ex)
      {
        this.master_.show_error_message (ex.Message);
      }
    }

    /**
     * Callback method for clicking the "Delete All" link.
     *
     * @param[in]       sender        Sender of the event.
     */
    protected void PathElement_Delete (object sender, System.EventArgs e)
    {
      // Get the dataset for the path elements.
      DataSet ds = (DataSet)Session ["dataset"];

      if (ds == null)
        return;

      foreach (DataGridItem item in this.path_elements_.Items)
      {
        // Locate the <action_> control since it's the checkbox
        // that determines the action of the current test.
        CheckBox action = (CheckBox)item.FindControl ("delete_");

        if (action != null && action.Checked)
        {
          object key = this.path_elements_.DataKeys [item.ItemIndex];
          DataRow row = ds.Tables [PATH_ELEMENTS_TABLE].Rows.Find (key);

          if (row != null)
            row.Delete ();
        }
      }

      this.UpdateView (ds);
      Session ["dataset"] = ds;
    }

    #region Web Form Designer generated code
    override protected void OnInit (EventArgs e)
    {
      InitializeComponent ();
      base.OnInit (e);
    }

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent ()
    {
      this.Load += new System.EventHandler (this.Page_Load);

    }
    #endregion
  }
}
