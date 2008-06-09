using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;
using MySql.Data.MySqlClient;
using System.Text.RegularExpressions;


public partial class CreateNewUT : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }

    protected void UT_submit_onclick(object sender, EventArgs e)
    {
        string commString = "INSERT INTO `qed`.`unit_tests`" +
               " (`Name` ,`Desc` ,`HLRegex` ,`Eval`) VALUES"; 
               //" (@UT_name, @UT_desc, @UT_getvars, @UT_eval);";

        commString += " ('" + UT_name.Text +"','"+ UT_Desc.Text + "',\"" + UT_getvars.Text + "\",'" + UT_eval.Text + "');";


        string connString = "SERVER=localhost;DATABASE=qed;UID=hamy;PASSWORD=banana";
        MySqlConnection conn = new MySqlConnection(connString);
        MySqlCommand comm = new MySqlCommand(commString, conn);
        conn.Open();
        //comm.Parameters.Add(new MySqlParameter("@UT_name", UT_name.Text));
        //comm.Parameters.AddWithValue("@UT_desc", UT_Desc.Text);
        //comm.Parameters.AddWithValue("@UT_getvars", UT_getvars.Text);
        //comm.Parameters.AddWithValue("@UT_eval", UT_eval.Text);
        comm.ExecuteNonQuery();
        conn.Close();
    }
}
