// -*- C# -*-

//=============================================================================
/**
 * @file            BMW.master.cs
 *
 * $Id$
 *
 * @author          James H. Hill
 */
//=============================================================================

using System;
using System.IO;
using System.Collections;
using System.Configuration;
using System.ComponentModel;
using System.Data;
using System.Data.Odbc;
using System.Diagnostics;
using System.ServiceProcess;
using System.Drawing;
using System.Web;
using System.Web.Security;
using System.Web.SessionState;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.HtmlControls;

namespace CUTS
{
  /**
   * @class Master
   *
   * Master page for the Benchmark Manager Web (BMW) Utility application.
   * This class defines the common structure of the website, and variables
   * and methods that are accesible to other member pages.
   */
  public partial class Master : System.Web.UI.MasterPage
  {
    /**
     * Initial event/fucntion called with the page is loaded.
     *
     * @param[in]           sender        Sender of the event
     * @param[in]           e             Arguments for the event.
     */
    private void Page_Load (object sender, System.EventArgs e)
    {
      this.download_path_ = Server.MapPath ("~/db/sandbox");
    }

    public CUTS.Web.UI.Console Console
    {
      get
      {
        return this.console_;
      }
    }

    public string DownloadPath
    {
      get
      {
        return this.download_path_;
      }
    }

    public string GetFileName (CUTS.UUID uuid)
    {
      return String.Format ("{0}/{1}.cdb",
                            this.download_path_,
                            CUTS.Data.UUID.ToString (uuid));
    }

    /**
     * Handler for the Consol.ClearMessages event.
     */
    protected void handle_clear_message (object sender, EventArgs e)
    {
      CUTS.Web.UI.Console console = (CUTS.Web.UI.Console)sender;

      if (console.Visible)
        console.Visible = false;
    }

    /**
     * Handler for the Console.AddMessage event.
     */
    protected void handle_add_message (object sender, EventArgs e)
    {
      CUTS.Web.UI.Console console = (CUTS.Web.UI.Console)sender;

      if (!console.Visible)
        console.Visible = true;
    }

    protected void handle_onlogout (object sender, EventArgs e)
    {
      if (Session["activeTest"] != null)
      {
        // Delete the active test.
        CUTS.UUID uuid = (CUTS.UUID)Session["activeTest"];
        string path = this.GetFileName (uuid);

        if (File.Exists (path))
          File.Delete (path);
      }

      // Delete this session.
      this.Session.Abandon ();

      // Complete the logout process.
      FormsAuthentication.SignOut ();
      this.Response.Redirect ("~/default.aspx");
    }

    private string download_path_;
  }
}