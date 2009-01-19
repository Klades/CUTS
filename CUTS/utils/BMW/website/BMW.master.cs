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
    }

    public CUTS.Web.UI.Console Console
    {
      get
      {
        return this.console_;
      }
    }

    protected void handle_onlogout (object sender, EventArgs e)
    {
      // Delete this session.
      this.Session.Abandon ();

      // Complete the logout process.
      FormsAuthentication.SignOut ();
      this.Response.Redirect ("~/default.aspx");
    }
  }
}