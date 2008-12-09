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
using MySql.Data.MySqlClient;
using System.Data.SQLite;

public partial class admin_createuser : System.Web.UI.Page
{
  protected void Page_Load (object sender, EventArgs e)
  {

  }

  protected void submit_button__Click (object sender, EventArgs e)
  {
    string uname = this.user_name_.Text;
    string password = this.password_.Text;
    string email = this.email_.Text;

    String connString = String.Format ("Data Source={0}", Server.MapPath ("~/db/cutsbmw.sqlite"));
    //string connString = "Server=localhost;Port=3306;Database=cuts;Uid=root;Pwd=Vandy;";
    string query = "INSERT INTO users (username,password,email,admin) VALUES ('" + uname + "','" + password + "','" + email + "', 0)";

    //MySqlConnection conn;
    //MySqlCommand cmd;
    SQLiteConnection conn;
    SQLiteCommand cmd;

    try
    {
      conn = new SQLiteConnection (connString);
      cmd = new SQLiteCommand (query);
      conn.Open ();
      cmd.Connection = conn;
      cmd.ExecuteNonQuery ();

      this.error_message_.Text = "Creation successful";
    }
    catch (Exception ex)
    {
      this.error_message_.Text = ex.Message;
    }
  }
}

