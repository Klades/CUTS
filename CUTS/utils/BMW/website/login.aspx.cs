// -*- C# -*-

//=============================================================================
/**
 * @file        login.aspx.cs
 *
 * $Id$
 *
 * @author      Chris Bellande <chris dot bellande at vanderbilt dot edu>
 */
//=============================================================================

using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Web;
using System.Web.SessionState;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;

public partial class Login : System.Web.UI.Page
{
  private void Page_Load (object sender, System.EventArgs e)
  {

  }

  protected void handle_onauthenticate (object sender, AuthenticateEventArgs e)
  {
    CUTS.BMW.Database bmw = new CUTS.BMW.Database ();

    try
    {
      bmw.Open (this.Server.MapPath ("~/db/cutsbmw.db"));

      string username = this.login_.UserName.Trim ();
      string password = this.login_.Password.Trim ();

      e.Authenticated = bmw.AuthenticateUser (username, password);
    }
    finally
    {
      bmw.Close ();
    }
  }
}
