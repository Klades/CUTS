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


// logout
// store DB stuff in cookie info
// encrypt password
// add admin folder and admin functions

public partial class login : System.Web.UI.Page
{
    private void Page_Load(object sender, System.EventArgs e)
    {

    }

    protected void Login1_Authenticate(object sender, AuthenticateEventArgs e)
    {
        try
        {
            string uname = Login1.UserName.Trim();
            string password = Login1.Password.Trim();
            bool flag = AuthenticateUser(uname, password);
            if (flag)
            {
                e.Authenticated = true;
                Login1.DestinationPageUrl = "Default.aspx";
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

    private bool AuthenticateUser(string uname, string password)
    {
        bool flag = false;
        string connString = "Server=localhost;Port=3306;Database=cuts;Uid=cuts;Pwd=cuts;";
        string query = "SELECT * FROM users WHERE username ='" + uname + "' AND password ='" + password + "'";
        DataSet userDS = new DataSet();
        MySqlConnection conn;
        MySqlDataAdapter dataAdapter;
        //MySqlCommand command;
        try
        {
            conn = new MySqlConnection(connString);
            conn.Open();
            dataAdapter = new MySqlDataAdapter(query, conn);
            dataAdapter.Fill(userDS);
            conn.Close();
        }
        catch (Exception)
        {
            userDS = null;
        }

        if (userDS != null)
        {
            if (userDS.Tables[0].Rows.Count > 0)
                flag = true;
        }
        return flag;
    }
}
