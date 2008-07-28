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
using System.Text.RegularExpressions;
using MySql.Data.MySqlClient;
using Actions.LogFormatActions;


public partial class Log_Formats : System.Web.UI.Page
{
  /**
   * @var BMW_Master master_  A reference to the Master page that easily
   *                      allows access to the messagins system. 
   */
  private CUTS.BMW_Master master_;
  
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
  protected void Page_Load ( object sender, EventArgs e )
  {
    master_ = (CUTS.BMW_Master)Master;
    if (IsPostBack)
      return;

    this.load_data();
  }

  /**
   * Method that loads(or re-loads) the Log Format Table with the current
   * contents of the database. 
   */
  private void load_data ()
  {
    DataTable dt = LogFormatActions.Get_All_Log_Formats();
   
    // Data Bind
    this.Log_Format_Table_.DataSource = dt;
    this.Log_Format_Table_.DataBind();

    // Check for info
    if (dt.Rows.Count == 0)
      this.master_.show_info_message("There are no log messages created yet. Please " +
        "add one.");

    // Ensure Widths
    if (this.Log_Format_Table_.Width.Value < Default_Width_)
      this.Log_Format_Table_.Width = new Unit( Default_Width_ );
    if (this.txt_New_LF.Width.Value < Default_Width_)
      this.txt_New_LF.Width = new Unit( Default_Width_ );

    // Make the ID column small
    this.Log_Format_Table_.Columns[0].ItemStyle.Width = new Unit( 10 );
    this.Log_Format_Table_.Columns[0].HeaderStyle.Width = new Unit( 10 );
    this.Log_Format_Table_.Columns[0].FooterStyle.Width = new Unit( 10 );

    // Setup the button better
    this.btn_New_LF.Height = this.txt_New_LF.Height;
  }

  /**
   * Callback method for when someone clicks to enter in a new 
   * Log Format. This validates the input and attempts to insert a new
   * LF into the database, correctly reporting on errors or success, 
   * and reloading the LF Table in the event of success. 
   * 
   * @param[in]       sender        Sender of the event.
   * @param[in]       e             Event arguments.
   */
  protected void OnClick_btn_New_LF ( object sender, EventArgs e )
  {
    if (this.txt_New_LF.Text.Length < 3)
    {
      master_.show_error_message( "The Log Format must be at least 3 characters!" );
      return;
    }
    try
    {
      string text = txt_New_LF.Text;
      string pattern = @"((?<lead>[-0-9a-z :;']+)(?<middle>{int (?<varname>[0-9a-z' ]+)}))";
      MatchCollection matches = Regex.Matches( text, pattern, RegexOptions.IgnoreCase );

      string lfmt = "", icase_regex = "", cs_regex = "";
      lfmt += txt_New_LF.Text;
      ArrayList vars = new ArrayList();
      foreach (Match NextMatch in matches)
      {
        string lead = NextMatch.Groups["lead"].ToString();
        string mid = NextMatch.Groups["middle"].ToString();
        string varname = NextMatch.Groups["varname"].ToString();
        icase_regex += lead + Regex.Replace( mid, "{int.+?}", "[[:digit:]]+", RegexOptions.IgnoreCase );

        // the group automatically names the captured variables correctly
        // You must use @ to escape the slashes in C#
        // You have to use two \\ to escape the \ in mySql
        // End result is stored and retrieved (as desired) as (?<varname>\d+)
        string group = "(?<" + varname + @">\\d+)";
        cs_regex += lead + Regex.Replace( mid, "{int.+?}", group, RegexOptions.IgnoreCase );
        vars.Add( varname );
      }

       LogFormatActions.Insert_LF( lfmt, icase_regex, cs_regex, vars.ToArray() );

      master_.show_info_message( "'" + txt_New_LF.Text + "' added Successfully!" );

      this.load_data();
    }
    catch
    {
      master_.show_error_message( "There was a problem adding '" +
        txt_New_LF.Text + "'. This probably means it is already created." );
    }
  }

    
}
