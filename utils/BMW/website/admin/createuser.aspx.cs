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
      ConnectionStringSettings settings =
        ConfigurationManager.ConnectionStrings["BMWConnectionString"];

      // Open a connection to the database.
      this.bmw_ = new CUTS.BMW.Database (settings.ProviderName);
      this.bmw_.ConnectionString = settings.ConnectionString;
      this.bmw_.Open ();
    }

    protected void handle_button_oncommand (object sender, CommandEventArgs e)
    {
      switch (e.CommandName)
      {
        case "Submit":
          // Create a new user profile.
          NewUserProfile profile = new NewUserProfile ();
          profile.EmailAddress = this.email_.Text;
          profile.Password = this.password_.Text;

          try
          {
            // Create a new user in the database.
            this.bmw_.CreateNewUser (profile);

            // Reset the text for the controls.
            this.email_.Text = String.Empty;
          }
          catch (Exception)
          {

          }

          break;

        case "Clear":
          break;
      }
    }

    private CUTS.BMW.Database bmw_;
  }
}
