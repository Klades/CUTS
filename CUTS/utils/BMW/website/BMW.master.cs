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
using System.Web.SessionState;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.HtmlControls;

namespace CUTS
{
  /**
   * @class BMW_Master
   *
   * Master page for the Benchmark Manager Web (BMW) Utility application.
   * This class defines the common structure of the website, and variables
   * and methods that are accesible to other member pages.
   */
  public partial class BMW_Master : System.Web.UI.MasterPage
  {
    private bool InQuietMode_;

    /**
     * Initial event/fucntion called with the page is loaded.
     *
     * @param[in]           sender        Sender of the event
     * @param[in]           e             Arguments for the event.
     */
    private void Page_Load (object sender, System.EventArgs e)
    {
      int index =
        this.Request.FilePath.IndexOf ('/', 1);

      string help_url =
        this.Request.FilePath.Insert (index, "/help");

      string filepath = this.Server.MapPath (help_url);

      if (File.Exists (filepath))
      {
        Label show_help = new Label ();
        show_help.Text =
          "<input type=\"button\" value=\"Show Help\" onclick=\"show_help ('" + help_url + "');\" />";

        this.help_item_.Controls.Add (show_help);
      }
    }

    public bool InQuietMode
    {
      get { return InQuietMode_; }
      set { InQuietMode_ = value; }
    }

    /**
     * Show an error message to the user.
     *
     * @param[in]         msg             Message to display
     */
    public void show_error_message (String msg)
    {
      this.show_message (msg, "msg_error");
    }

    /**
     * Show an info message to the user.
     *
     * @param[in]         msg             Message to display
     */
    public void show_info_message (String msg)
    {
      this.show_message (msg, "msg_info");
    }

    /**
     * Show a warning message to the user.
     *
     * @param[in]         msg             Message to display
     */
    public void show_warning_message (String msg)
    {
      this.show_message (msg, "msg_warning");
    }

    /**
     * Insert the actual message into the console. This will display the
     * console if it is not already visible to the user.
     *
     * @param[in]         msg_control     Control containing the message
     */
    private void show_message (String msg, String cssclass)
    {
      Label label = new Label ();
      label.CssClass = cssclass;
      label.Text = "<div>&middot; " + msg + "</div>";

      this.console_text_.Controls.Add (label);

      // Make sure we can actually see the console.
      if (this.console_.Style["display"] == "none")
        this.console_.Style["display"] = "block";
    }
  }
}
