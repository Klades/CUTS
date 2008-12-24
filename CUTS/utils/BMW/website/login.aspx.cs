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
using System.Web.UI.WebControls.WebParts;
using MySql.Data.MySqlClient;
using System.Data.SQLite;

public partial class Login : System.Web.UI.Page
{
  private void Page_Load (object sender, System.EventArgs e)
  {

  }

  protected void handle_onauthenticate (object sender, AuthenticateEventArgs e)
  {
    try
    {
      string username = this.login_.UserName.Trim ();
      string password = this.login_.Password.Trim ();

      bool result = this.authenticate_user (username, password);

      if (result)
      {
        e.Authenticated = true;
        this.login_.DestinationPageUrl = "Default.aspx";
      }
      else
      {
        e.Authenticated = false;
      }
    }
    catch (Exception)
    {
      e.Authenticated = false;
    }
  }

  private bool authenticate_user (string uname, string password)
  {
    bool flag = false;
    String connString = String.Format ("Data Source={0}", Server.MapPath("~/db/cutsbmw.db"));
    string query = "SELECT * FROM users WHERE username ='" + uname + "' AND password ='" + password + "'";
    DataSet userDS = new DataSet ();

    SQLiteConnection conn;
    SQLiteDataAdapter dataAdapter;

    try
    {
      conn = new SQLiteConnection ();
      conn.ConnectionString = connString;
      conn.Open ();

      dataAdapter = new SQLiteDataAdapter (query, conn);
      dataAdapter.Fill (userDS);
      conn.Close ();
    }
    catch (Exception ex)
    {
      string errstr = ex.Message;
      userDS = null;
    }
    if (userDS != null)
    {
      if (userDS.Tables [0].Rows.Count > 0)
        flag = true;
    }

    return flag;
  }
}
