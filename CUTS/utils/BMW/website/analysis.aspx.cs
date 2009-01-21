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

    }

    /**
     * Handle the Page_Load event.
     */
    private void Page_Load (object sender, System.EventArgs e)
    {
      this.master_ = (CUTS.Master)this.Master;

      try
      {

      }
      catch (Exception ex)
      {
        this.master_.Console.Add (ex);
      }
    }

    protected void handle_onmenuitemclick (Object sender, MenuEventArgs e)
    {
      this.multiview_.ActiveViewIndex = int.Parse (e.Item.Value);
    }

    protected void handle_onactiveviewchanged (Object sender, EventArgs e)
    {
      switch (this.multiview_.ActiveViewIndex)
      {
        case 0:
          break;

        case 1:
          break;
      }
    }

    protected void handle_download_complete (object sender, EventArgs e)
    {

    }

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
