// $Id$

//=============================================================================
/**
 *  @file         Timeline.aspx.cs
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

using System;
using System.Collections;
using System.ComponentModel;
using System.Configuration;
using System.Data;
using System.Data.Common;
using System.Drawing;
using System.Web;
using System.Web.SessionState;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.HtmlControls;
using System.Runtime.Remoting;
using System.Runtime.Remoting.Channels;

using CUTS.Web.UI;
using CUTS.Web.UI.Archive;
using CUTS.Web.UI.UnitTesting;
using CUTS.Data.UnitTesting;

// from IIOPChannel.dll
using Ch.Elca.Iiop.Idl;
using Ch.Elca.Iiop;
using Ch.Elca.Iiop.Services;
using omg.org.CORBA;

namespace CUTS.Web.Page
{
  /**
   * @class Timeline
   *
   * Code-behind for the timeline.aspx webpage.
   */
  public partial class Analysis : System.Web.UI.Page
  {
    /**
     * Default constructor. This will attempt to establish connection
     * with the test archive. It's better to perform the initialization
     * here instead of in Page_Load since Page_Load can be invoked many
     * times during a single visit to a page.
     */
    public Analysis ()
    {
      // Instantiate a connection to the database.
      ConnectionStringSettings settings =
        ConfigurationManager.ConnectionStrings["BMWConnectionString"];

      this.database_ = new CUTS.BMW.Database (settings.ProviderName);
      this.database_.ConnectionString = settings.ConnectionString;
    }

    /**
     * Handle the Page_Load event.
     */
    private void Page_Load (object sender, System.EventArgs e)
    {
      this.master_ = (CUTS.Master)this.Master;

      try
      {
        object active_test = this.Session["activeTest"];

        if (active_test == null)
          this.Response.Redirect ("~/tests.aspx");
      }
      catch (Exception ex)
      {
        this.master_.Console.Add (ex);
      }
    }

    protected void handle_onmenuitemclick (Object sender, MenuEventArgs e)
    {
      this.analysis_.ActiveViewIndex = int.Parse (e.Item.Value);
    }

    protected void handle_onactiveviewchanged (Object sender, EventArgs e)
    {
      switch (this.analysis_.ActiveViewIndex)
      {
        case 0:
          this.update_unit_testing_view ();
          break;
      }
    }

    private void update_unit_testing_view ()
    {
      try
      {
        // Open a connection to the database.
        this.database_.Open ();

        // Initialize the dropdown list.
        DataTable suites = this.database_.SelectUnitTestSuites ();

        this.test_suite_list_.DataSource = suites;
        this.test_suite_list_.DataTextField = "name";
        this.test_suite_list_.DataValueField = "id";
        this.test_suite_list_.DataBind ();
      }
      catch (Exception e)
      {
        this.master_ = (CUTS.Master)this.Page.Master;
        this.master_.Console.Add (e);
      }
      finally
      {
        if (this.database_.State == ConnectionState.Open)
          this.database_.Close ();
      }
    }

    protected void handle_load_test_suite (object sender, EventArgs e)
    {
      try
      {
        // Open connection to database.
        this.database_.Open ();

        // Select all the unit test for the test suite.
        int utid = int.Parse (this.test_suite_list_.SelectedValue);
        DbDataReader reader = this.database_.SelectTestSuiteManifestReader (utid);

        try
        {
          // Clear the contents of the test suite.
          this.test_suite_.Clear ();

          if (reader.HasRows)
          {
            // Perform a read so we can cache some data.
            reader.Read ();

            // Cache the ordinals of key columns.
            int package_ordinal = reader.GetOrdinal ("package_name");
            int unittest_ordinal_name = reader.GetOrdinal ("unit_test_name");
            int unittest_ordinal_id = reader.GetOrdinal ("unit_test_id");

            string curr_package = String.Empty;
            UnitTestPackage package = null;

            do
            {
              // Get the name of the current package.
              string package_name = reader.GetString (package_ordinal);

              if (!package_name.Equals (curr_package))
              {
                // Create a new unit test package.
                package = new UnitTestPackage ();
                this.test_suite_.Add (package);

                // Initialize its contents.
                package.Name = package_name;

                // Save the name as the current package.
                curr_package = package_name;
              }

              if (package != null)
              {
                // Create a new unit test in the package.
                UnitTest unittest = new UnitTest ();
                package.Add (unittest);

                // Set the unit test properties.
                unittest.Name = reader.GetString (unittest_ordinal_name);
                unittest.UnitTestId = reader.GetInt32 (unittest_ordinal_id);
              }
            } while (reader.Read ());
          }
          else
          {

          }
        }
        finally
        {
          // Make sure we close the data reader.
          if (!reader.IsClosed)
            reader.Close ();
        }
      }
      finally
      {
        // Make sure we close our connection to the database.
        if (this.database_.State == ConnectionState.Open)
          this.database_.Close ();
      }
    }

    protected void handle_evaluate_unit_test (object sender, CommandEventArgs e)
    {
      if (this.master_ == null)
        this.master_ = (CUTS.Master)this.Page.Master;

      // Get the unit test from the argument.
      UnitTest unittest = (UnitTest)e.CommandArgument;

      // Initialize a new evaluator.
      UnitTestEvaluator evaluator = new UnitTestEvaluator (this.database_.Provider);
      evaluator.ConnectionString = this.database_.ConnectionString;
      evaluator.TempPath = Server.MapPath ("~/db/sandbox/evaluations");

      // Get the active test.
      CUTS.UUID active_test = (CUTS.UUID)this.Session["activeTest"];

      // Construct the location of the test data.
      string pathname = String.Format ("~/db/sandbox/{0}.cdb",
                                       CUTS.Data.UUID.ToString (active_test));

      pathname = this.Server.MapPath (pathname);

      // Re-evalatue the unit test
      try
      {
        evaluator.Open ();
        unittest.Result = evaluator.Reevaluate (pathname, unittest.UnitTestId, true);
      }
      catch (Exception ex)
      {
        this.master_.Console.Add (ex);
      }
      finally
      {
        if (evaluator.State == ConnectionState.Open)
          evaluator.Close ();
      }
    }

    private CUTS.BMW.Database database_;

    /**
     * Reference to the master page.
     */
    private CUTS.Master master_;

    #region Web Form Designer generated code
    override protected void OnInit (EventArgs e)
    {
      //
      // CODEGEN: This call is required by the ASP.NET Web Form Designer.
      //
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
