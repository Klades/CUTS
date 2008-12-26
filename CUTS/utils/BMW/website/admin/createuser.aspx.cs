// -*- C# -*-

//=============================================================================
/**
 * @file        createuser.aspx.cs
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
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;

using CUTS.BMW;

namespace CUTS.BMW.Page.Admin
{
  public partial class CreateUser : System.Web.UI.Page
  {
    protected void Page_Load (object sender, EventArgs e)
    {

    }

    protected void handle_button_oncommand (object sender, CommandEventArgs e)
    {
      switch (e.CommandName)
      {
        case "Submit":
          // Create a new user profile.
          NewUserProfile profile = new NewUserProfile ();
          profile.Username = this.username_.Text;
          profile.Password = this.password_.Text;
          profile.EmailAddress = this.email_.Text;

          CUTS.BMW.Database bmw = new CUTS.BMW.Database ();

          try
          {
            // Open a connection to the database.
            bmw.Open (Server.MapPath ("~/db/cutsbmw.db"), false);

            // Create a new user in the database.
            bmw.CreateNewUser (profile);

            // Reset the text for the controls.
            this.username_.Text = String.Empty;
            this.email_.Text = String.Empty;
          }
          finally
          {
            if (bmw.State == ConnectionState.Open)
              bmw.Close ();
          }

          break;

        case "Clear":
          break;
      }
    }
  }
}
