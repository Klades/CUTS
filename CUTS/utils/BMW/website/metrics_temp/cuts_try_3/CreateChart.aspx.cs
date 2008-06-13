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

public partial class CreateChart : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        string connString = ConfigurationSettings.AppSettings["connString"];
        MySqlConnection conn = new MySqlConnection(connString);
        string commString = "SELECT Name,UTid from unit_tests;";
        MySqlCommand comm = new MySqlCommand(commString, conn);
        conn.Open();
        MySqlDataReader rdr = comm.ExecuteReader();

        UT_one.DataSource = rdr;
        UT_one.DataTextField = "Name";
        UT_one.DataValueField = "UTid";
        UT_one.DataBind();
        rdr.Close();

        rdr = comm.ExecuteReader();
        UT_two.DataSource = rdr;
        
        UT_two.DataTextField = "Name";
        UT_two.DataValueField = "UTid";
        UT_two.DataBind();
        rdr.Close();

        rdr = comm.ExecuteReader(CommandBehavior.CloseConnection);
        UT_three.DataSource = rdr;
        UT_three.DataTextField = "Name";
        UT_three.DataValueField = "UTid";
        UT_three.DataBind();
        rdr.Close();

        UT_one.Items.Insert(0, new ListItem("Please Select a UT . . . ","-1"));
        UT_two.Items.Insert(0, new ListItem("Please Select a UT . . . ","-1"));
        UT_three.Items.Insert(0, new ListItem("Please Select a UT . . . ","-1"));


    }
    protected void Button1_Click(object sender, EventArgs e)
    {
        string connString = ConfigurationSettings.AppSettings["connString"];
        MySqlConnection conn = new MySqlConnection(connString);
        string commString = "INSERT INTO `qed`.`charts` (`Name`, `Desc`, `UTs`, `Eval`) VALUES ('";

        commString += Chart_name.Text + "','";
        commString += Chart_desc.Text + "','";
        if (UT_one.SelectedValue != "-1")
            commString += UT_one.SelectedValue.ToString();
        if (UT_two.SelectedValue != "-1")
            commString += "," + UT_two.SelectedValue.ToString();
        if (UT_three.SelectedValue != "-1")
            commString += "," + UT_three.SelectedValue.ToString();
        commString += "','";
        commString += Regex.Replace(UT_eval.Text, "UT", "") + "');";

        MySqlCommand comm = new MySqlCommand(commString, conn);
        conn.Open();
        comm.ExecuteNonQuery();

    }
    protected void UT_one_SelectedIndexChanged(object sender, EventArgs e)
    {
        Response.Write("Index changed!");
    }
}
