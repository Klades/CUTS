using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using MySql.Data.MySqlClient;
using Actions;
using System.Text.RegularExpressions;


public partial class Log_Formats : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        if (IsPostBack)
            return;

        load_data();
    }

    private void load_data()
    {
      /**
       * Hamilton:
       *
       * Please update this so that it uses a SQL stored procedure.
       */
        // Get all the test from the database.
        string sql = "SELECT * FROM logformatdesc;";
        DataTable dt = ExecuteMySqlAdapter(sql);

        // Expose the <DefaultView> of the result.
        this._table.DataSource = dt;
        this._table.DataBind();
    }


    protected void OnClick_btn_New_LF(object sender, EventArgs e)
    {
        try
        {
            string text = txt_New_LF.Text;
            string pattern = @"((?<lead>[-0-9a-z :;']+)(?<middle>{int (?<varname>[0-9a-z' ]+)}))";
            MatchCollection matches = Regex.Matches(text, pattern, RegexOptions.IgnoreCase);

            string lfmt = "", icase_regex = "", cs_regex = "";
            lfmt += txt_New_LF.Text;
            ArrayList vars = new ArrayList();
            foreach (Match NextMatch in matches)
            {
                string lead = NextMatch.Groups["lead"].ToString();
                string mid = NextMatch.Groups["middle"].ToString();
                string varname = NextMatch.Groups["varname"].ToString();
                icase_regex += lead + Regex.Replace(mid, "{int.+?}", "[[:digit:]]+", RegexOptions.IgnoreCase);

                // the group automatically names the captured variables correctly
                // You must use @ to escape the slashes in C#
                // You have to use two \\ to escape the \ in mySql
                // End result is stored and retrieved (as desired) as (?<varname>\d+)
                string group = "(?<" + varname + @">\\d+)";
                cs_regex += lead + Regex.Replace(mid, "{int.+?}", group, RegexOptions.IgnoreCase);
                vars.Add(varname);
            }

            LogFormatActions lf = new LogFormatActions();
            lf.Insert_LF(lfmt, icase_regex, cs_regex, vars.ToArray());

            /**
             * Hamilton:
             *
             * Please update this so that it only prints a success message
             * without the actual log format that was entered. If the log format
             * is TOO long, then this will not display properly!!
             *
             * Moreove, you are only entering on message, so the user will no
             * what the message format is. ;-)
             */
            lbl_New_LF_Success.Style.Add("color", "green");
            lbl_New_LF_Success.Text = txt_New_LF.Text + " added Successfully!";

            this.load_data();
        }
        catch
        {
          /**
           * Hamilton:
           *
           * Please update this so that it only prints an error message
           * without the actual log format that was entered. If the log format
           * is TOO long, then this will not display properly!!
           *
           * Moreove, you are only entering on message, so the user will no
           * what the message format is. ;-) What you should really do in this
           * case is update the input control with the original message!!
           */
          lbl_New_LF_Success.Style.Add("color", "red");
            lbl_New_LF_Success.Text = "There was a problem adding " + txt_New_LF.Text;
        }
    }

    private DataTable ExecuteMySqlAdapter(string sql)
    {
        MySqlConnection conn = new MySqlConnection(ConfigurationManager.AppSettings["MySQL"]);
        conn.Open();

        MySqlDataAdapter da = new MySqlDataAdapter(sql, conn);
        DataSet ds = new DataSet();
        da.Fill(ds);

        conn.Close();
        return ds.Tables[0];
    }
}
