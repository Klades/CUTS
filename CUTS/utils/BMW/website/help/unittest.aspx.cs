// -*- C# -*-

//=============================================================================
/**
 * @file      performance.aspx.cs
 *
 * $Id$
 *
 * @author    James H. Hill
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

namespace CUTS
{
  namespace Help
  {
    public partial class UnitTest : System.Web.UI.Page
    {
      private void Page_Load (object sender, System.EventArgs e)
      {

      }

      #region Web Form Designer generated code
      override protected void OnInit (EventArgs e)
      {
        // Initialize the component.
        InitializeComponent ();

        // Pass control to the base class.
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
}

