// -*- C# -*-

//=============================================================================
/**
 * @file      default.aspx.cs
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

using System;
using System.Collections;
using System.Configuration;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Web;
using System.Web.SessionState;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.HtmlControls;
using MySql.Data.MySqlClient;
using CUTS.Data;

namespace CUTS.Web.Page
{
  //===========================================================================
  /**
   * @class Test
   *
   * Backend source for the default.aspx web page.
   */
  //===========================================================================

  public partial class Default : System.Web.UI.Page
  {
    private CUTS.Master master_;

    public Default ()
    {

    }

    /**
     * Callback method for loading a page.
     *
     * @param[in]     sender        Sender of the event.
     * @param[in]     e             Arguments for the event.
     */
    private void Page_Load (object sender, System.EventArgs e)
    {
      this.master_ = (CUTS.Master)this.Master;
    }

    ///
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
