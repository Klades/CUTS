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
using System.Data.Odbc;
using System.Drawing;
using System.Web;
using System.Web.SessionState;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.HtmlControls;
using System.Runtime.Remoting;
using System.Runtime.Remoting.Channels;

using CUTS.Web.UI.Archive;

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
  public partial class Tests : System.Web.UI.Page
  {
    /**
     * Default constructor. This will attempt to establish connection
     * with the test archive. It's better to perform the initialization
     * here instead of in Page_Load since Page_Load can be invoked many
     * times during a single visit to a page.
     */
    public Tests ()
    {
      try
      {
        // Register the IiopChannel with the framework.
        IiopChannel channel = new IiopChannel ();
        ChannelServices.RegisterChannel (channel, false);
      }
      catch (RemotingException)
      {

      }

      // Configure the address of the test archive.
      string address = ConfigurationManager.AppSettings["cuts.archive.address"];
      string corbaloc = String.Format ("corbaloc:iiop:{0}/CUTS/TestArchive", address);

      // Connect to the test archive.
      this.archive_ = (CUTS.TestArchive)RemotingServices.Connect (typeof (CUTS.TestArchive), corbaloc);
    }

    /**
     * Handle the Page_Load event.
     */
    private void Page_Load (object sender, System.EventArgs e)
    {
      this.master_ = (CUTS.Master)this.Master;

      try
      {
        // Initialize the archive for the browser.
        this.browser_.TestArchive = this.archive_;

        if (!this.IsPostBack)
        {
          // Set the active test for the control.
          if (Session["activeTest"] != null)
          {
            CUTS.UUID uuid = (CUTS.UUID)Session["activeTest"];
            this.browser_.ActivateTest (uuid);
          }

          // Bind the data to the control.
          this.browser_.DataBind ();
        }
      }
      catch (Exception ex)
      {
        this.master_.Console.Add (ex);
      }
    }

    protected void handle_download_complete (object sender, EventArgs e)
    {
      // Save the active test in the session.
      TestBrowser browser = (TestBrowser)sender;
      this.Session["activeTest"] = browser.ActiveTest;

      // Redirect to the analysis page.
      this.Response.Redirect ("~/analysis.aspx");
    }

    /**
     * Reference to the test archive.
     */
    private CUTS.TestArchive archive_;

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
