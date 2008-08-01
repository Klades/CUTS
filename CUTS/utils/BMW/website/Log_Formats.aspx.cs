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
using System.Text;
using System.Text.RegularExpressions;
using MySql.Data.MySqlClient;
using Actions.LogFormatActions;


public partial class Log_Formats : System.Web.UI.Page
{
  /**
   * @var Master master_  A reference to the Master page that easily
   *                      allows access to the messagins system.
   */
  private CUTS.Master master_;

  /**
   * @var double Default_Width_  The default width(in px) for the page's Log
   *                               Log Format Table.
   */
  private static double Default_Width_ = 800.0;

  /**
   * Callback method for when the page is loading.
   *
   * @param[in]       sender        Sender of the event.
   * @param[in]       e             Event arguments.
   */
  protected void Page_Load (object sender, EventArgs e)
  {
    this.master_ = (CUTS.Master)Master;

    if (IsPostBack)
      return;

    this.load_data ();
  }

  /**
   * Method that loads(or re-loads) the Log Format Table with the current
   * contents of the database.
   */
  private void load_data ()
  {
    DataTable dt = LogFormatActions.Get_All_Log_Formats ();

    // Data Bind
    this.log_formats_.DataSource = dt;
    this.log_formats_.DataBind ();

    // Ensure Widths
    if (this.log_formats_.Width.Value < Default_Width_)
      this.log_formats_.Width = new Unit (Default_Width_);
    if (this.txt_New_LF.Width.Value < Default_Width_)
      this.txt_New_LF.Width = new Unit (Default_Width_);

    // Make the ID column small
    this.log_formats_.Columns[0].ItemStyle.Width = new Unit (10);
    this.log_formats_.Columns[0].HeaderStyle.Width = new Unit (10);
    this.log_formats_.Columns[0].FooterStyle.Width = new Unit (10);

    // Setup the button better
    this.btn_New_LF.Height = this.txt_New_LF.Height;
  }

  /**
   * Callback method for when someone clicks to enter in a new
   * Log Format. This validates the input and attempts to insert a new
   * LF into the database, correctly reporting on errors or success,
   * and reloading the LF Table in the event of success.
   *
   * Types of variables currently supported include:
   * INT
   * STRING  -  allowed characters include -a-zA-Z.0-9 :,;+=_
   *
   * @param[in]       sender        Sender of the event.
   * @param[in]       e             Event arguments.
   */
  protected void OnClick_btn_New_LF (object sender, EventArgs e)
  {
    try
    {
      string pattern = @"(?<text>[^{}]*)(?<vardecl>\{(?<vartype>[a-zA-Z]+) (?<varname>[a-zA-Z_]+)\})?";
      Regex reg = new Regex (pattern, RegexOptions.IgnoreCase);
      Match match = reg.Match (this.txt_New_LF.Text);

      StringBuilder mysql_regex = new StringBuilder ();
      StringBuilder csharp_regex = new StringBuilder ();

      Hashtable variables = new Hashtable ();

      while (match.Success)
      {
        // Get the groups from the current capture set.
        string text =
          match.Groups["text"].Captures.Count == 1 ?
          match.Groups["text"].Captures[0].Value : null;

        string vartype =
          match.Groups["vartype"].Captures.Count == 1 ?
          match.Groups["vartype"].Captures[0].Value : null;

        string varname =
          match.Groups["varname"].Captures.Count == 1 ?
          match.Groups["varname"].Captures[0].Value : null;

        // First, let's see if there any text that we need to add to the
        // regular expressions. This will be string literal text.
        if (text != null)
        {
          mysql_regex.Append (text);
          csharp_regex.Append (text);
        }

        // Next, we need to append the variable to the regular expression
        if (vartype != null && varname != null)
        {
          string vardecl = match.Groups["vardecl"].Captures[0].Value;

          switch (vartype)
          {
            case "int":
            case "INT":
              // Update the regular expressions.
              mysql_regex.Append ("[[:digit:]]+");
              csharp_regex.Append ("(?<" + varname + @">\d+)");

              variables.Add (varname, "INT");
              break;

            case "string":
            case "STRING":
              // Update the regular expressions.
              mysql_regex.Append ("[-a-zA-Z.0-9 :,;+=_]+");
              csharp_regex.Append (@"(?<" + varname + @">[-a-zA-Z.0-9 :,;+=]+)");

              variables.Add (varname, "STRING");
              break;

            default:
              throw new Exception (vartype + " is not a valid variable type (declartion: " + vardecl + ")");
          }
        }

        // Get the next match.
        match = match.NextMatch ();
      }

      // Insert log format into the database.
      LogFormatActions.Insert_LF (this.txt_New_LF.Text,
                                  mysql_regex.ToString (),
                                  csharp_regex.ToString (),
                                  variables);

      this.master_.show_info_message ("Successfully created log format: " + this.txt_New_LF.Text);
      this.txt_New_LF.Text = "";

      // Load the data for the control.
      this.load_data ();
    }
    catch (Exception ex)
    {
      this.master_.show_error_message (ex.Message);
      this.master_.show_error_message ("Failed to create log format: " + this.txt_New_LF.Text);
    }
  }
}
