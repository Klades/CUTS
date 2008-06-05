using System;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Web;
using System.Text.RegularExpressions;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;
using MySql.Data.MySqlClient;


public partial class _Default : System.Web.UI.Page 
{

    protected void Page_Load(object sender, EventArgs e)
    {
        
    }
    protected void Button1_Click(object sender, EventArgs e)
    {
        CUTS_System cs = new CUTS_System();
        cs.parse(TextBox1.Text);
        LabelLog.Text += cs.log;
        cs.
    }

}

public class CUTS_System
{
    // CUTS_System
    // created Jun 08
    //
    // Purpose: To allow be able to generate one
    //   datatable, with a primary column of testID
    //   and other columns of varying name and types.
    //   To act on that table, providing row by row and 
    //        column-wise arithmatic operations
    //  
    //    
    
    private string connString;
    private DataTable table_;
    private Logger logger_;
    private DataTable temp_;


    public CUTS_System()
    {
        // Sets up the one internal dataTable
        table_ = new DataTable();
        DataColumn dc = new DataColumn("TestID", System.Type.GetType("System.Int32"));
        table_.Columns.Add(dc);

        connString = "SERVER=localhost;DATABASE=qed;UID=hamy;PASSWORD=banana";
        logger_ = new Logger();

        // Used once per statement to temp
        // hold the message and testID
        // before they are merged with
        // the main column
        temp_ = new DataTable();
    }

    // To provide parsing of many statements
    // separated by semicolons
    public void parse(string raw) 
    { 
        string[] statements = Regex.Split(raw, ";");
        foreach (string expr in statements)
            parse_single(expr);
    }

    // parses a single statement
    private void parse_single(string raw)
    {
        // Create initial match and generate lead, middle, end groups
        Regex reg = new Regex("(?<lead>[-0-9a-zA-Z :;']+)?(?<middle>{int (?<var_name>[0-9a-z ]+)})(?<end>[-0-9a-z :;']+)?", RegexOptions.IgnoreCase);
        Match match = reg.Match(raw);
        logger_.log("matched string:" + raw);
        string lead = match.Groups["lead"].ToString(),
            middle = match.Groups["middle"].ToString(),
            var_name = match.Groups["var_name"].ToString(),
            end = match.Groups["end"].ToString();

        // Create SQL to grab the right rows
        string sql = create_sql_regexp(lead,middle,end);
        logger_.log("created sql: " + sql);

        // Execute SQL, save results to named datatable
        execute_sql(sql, var_name);
        logger_.log("executed sql, populated datatable temp");

        // create the regex to pull the data
        // out of the message field of the database
        string cs_data_removal_regexp_str = data_removal_regexp(lead, middle, end);
        
        // add data for this iteration to any previous data 
        merge_tables(middle,var_name, cs_data_removal_regexp_str);
     }

    // Creates the regexp to remove the 
    // data from the message field
    private string data_removal_regexp(string lead, string middle, string end)
    {
        // for now lead and end have no purpose.
        // seems more generic to include them
        string cs_mid = Regex.Replace(middle, "{int.+?}", @"(?<data>\d+)", RegexOptions.IgnoreCase);
        return lead + cs_mid + end;

    }

    // Merges temp table and "permanent" final table_
    private void merge_tables(string middle, string var_name,string data_removal_regexp_str)
    {
        // Check for duplicate column/variable names
        if (table_.Columns.IndexOf(var_name) != -1)
            // Need to throw exception here! Means there are two duplicate names
            logger_.log("Found duplicate name, trying to throw exception on var_name : " + var_name);

        // Find Type for new DataColumn
        string type = "";
        if (Regex.IsMatch(middle,"{int",RegexOptions.IgnoreCase))
            type = "System.Int32";
        if (type == "")
            // need to throw exception
            logger_.log("no type was found");


        // Add a new DataColumn with the correct Type
        DataColumn dc = new DataColumn(var_name,System.Type.GetType(type));
        table_.Columns.Add(dc);
        
        // Iterate over the temp_ table rows to merge two 
        // tables according to testid
        int count = temp_.Rows.Count;
        for (int i = 0; i < count; ++i)
        {
            string test_id = temp_.Rows[i]["TestID"].ToString();

            // Check to see if row exists in main table
            if (table_.Select("TestID = " + test_id).Length == 0)
            {
                //Note: this inherently leaves any other
                // columns null if it is not the first 
                // pass of this section. Might need a better
                // solution
                DataRow newRow = table_.NewRow();
                newRow["TestID"] = (i + 1).ToString();
                table_.Rows.Add(newRow);

                logger_.log("Added test " + (i+1).ToString() + " to main table");
            }

            // Select row from "permanent" table_
            DataRow row = table_.Select("TestID = " +test_id).Single();
        
            // Remove the data from the message column
            Regex regexp = new Regex(data_removal_regexp_str, RegexOptions.IgnoreCase);
            Match match = regexp.Match(temp_.Rows[i]["message"].ToString());
            
            // Store actual data in table_
            // Note: group data is universal across different types
            row[var_name] = match.Groups["data"].ToString();
        }

        // Help garbage collector
        temp_ = null;
    }

    // Fills temp_ table with data from a single statement
    private void execute_sql(string sql, string table_name)
    {
        MySqlConnection conn = new MySqlConnection(connString);
        DataTable dt = new DataTable(table_name);
        MySqlDataAdapter da = new MySqlDataAdapter(sql, conn);
        da.Fill(dt);
        temp_ = dt;
    }

    // Creates the sql statement that will choose the right 
    // message rows
    private string create_sql_regexp(string lead, string middle, string end)
    {
        lead = clean_for_sql(lead);
        end = clean_for_sql(end);
        if (Regex.IsMatch(middle, "{int", RegexOptions.IgnoreCase))
            middle = "[[:digit:]]+";
        return "SELECT TestID,message FROM results WHERE message REGEXP '" + lead + middle + end + "';";
    }

    // replaces all illegial sql characters with their
    // correct alternatives
    private string clean_for_sql(string clean_me)
    {
        clean_me = Regex.Replace(clean_me, ":", "[[.colon.]]");
        return clean_me;
    }
        
    // Just a temporary function to help debug/trace app
    public string log
    {
        get
        {
            return logger_.log_str;
        }
    }

}

class Logger
{
    private string log_;

    public void log(string msg)
    {
        log_ += "<br> " + msg;    
    }

    public string log_str
    {
        get
        {
            return log_;
        }
    }
}
