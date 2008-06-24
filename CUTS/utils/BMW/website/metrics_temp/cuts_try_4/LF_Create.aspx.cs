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
using System.Text.RegularExpressions;
using Actions;

public partial class LF_Create : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }
    protected void Button1_Click(object sender, EventArgs e)
    {
        string text = TextBox1.Text;
        string pattern = @"((?<lead>[-0-9a-z :;']+)(?<middle>{int (?<varname>[0-9a-z' ]+)}))";
        MatchCollection matches = Regex.Matches(text, pattern, RegexOptions.IgnoreCase);

        string lfmt = "" , icase_regex = "", cs_regex = "";
        lfmt += TextBox1.Text;
        ArrayList vars = new ArrayList();
        foreach (Match NextMatch in matches)
        {
            string lead = NextMatch.Groups["lead"].ToString();
            string mid = NextMatch.Groups["middle"].ToString();
            string varname = NextMatch.Groups["varname"].ToString();
            icase_regex += lead + Regex.Replace(mid, "{int.+?}", "[[:digit:]]+", RegexOptions.IgnoreCase);
            
            // the group automatically names the captured variables correctly
            string group = "(?<" + varname + ">/d+)";
            cs_regex += lead + Regex.Replace(mid, "{int.+?}",group, RegexOptions.IgnoreCase);
            vars.Add(varname);
        }

        LogFormatActions lf = new LogFormatActions();
        lf.Insert_LF(lfmt, icase_regex, cs_regex, vars.ToArray());
    }
}
