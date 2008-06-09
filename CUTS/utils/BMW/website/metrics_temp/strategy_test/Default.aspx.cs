using System;
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

public partial class _Default : System.Web.UI.Page 
{
    protected void Page_Load(object sender, EventArgs e)
    {
        DataTable dt = new DataTable();
        dt.Columns.Add("TestID",System.Type.GetType("System.Int32"));
        dt.Columns.Add("one",System.Type.GetType("System.Int32"));
        dt.Columns.Add("two",System.Type.GetType("System.Int32"));
        dt.Columns.Add("result",System.Type.GetType("System.Int32"));
        
        DataColumn[] PrimaryKeyColumns = new DataColumn[1];
        PrimaryKeyColumns[0] = dt.Columns["TestID"];
        dt.PrimaryKey = PrimaryKeyColumns;

        DataRow dr = dt.NewRow();
        dr["TestID"] = "1";
        dr["one"] = "1";
        dr["two"] = "1";
        dt.Rows.Add(dr);
        ReceiverAPI r = new ReceiverAPI(dt);
        

        ScalarAddCommand sc = new ScalarAddCommand(ref r, 1, "one", "two", "result");
        sc.Execute();
        
    }
}

class ReceiverAPI
{
    private DataTable dt;
    
    public ReceiverAPI(DataTable table)
    {
        this.dt = table;
    }

    public DataRow GetRow(int TestID)
    {
        //return dt.Select("TestID=" + TestID.ToString()).Single();
        return dt.Rows.Find(TestID);
    }

    public void SetRow(int TestID, string colname, string value)
    {
        if (ColExists(colname) == false)
            return; // error

        DataRow dr = dt.Rows.Find(TestID);
        dr[colname] = value;
    }
    
    public void AddCol(string colname, string datatype)
    {
        if (ColExists(colname))
            return; // error

        // Add a new DataColumn with the correct Type
        // type should be of format "System.Int32"
        DataColumn dc = new DataColumn(colname, System.Type.GetType(datatype));
        dt.Columns.Add(dc);

    }

    public bool ColExists(string colname)
    {
        // Indicates col does not exist
        if (dt.Columns.IndexOf(colname) > -1)
            return true;
        return false;
    }

    public DataTable table_
    {
        get
        {
            return dt;
        }
    }
    

}

interface ICommand
{
    void Execute();
}

class ScalarAddCommand : ICommand
{
    private ReceiverAPI r;
    private int tid;
    private string add_one;
    private string add_two;
    private string resultcol;

    public ScalarAddCommand(ref ReceiverAPI rec, int TestID, string addend_one, string addend_two, string result)
    {
        r = rec;
        tid = TestID;
        add_one = addend_one;
        add_two = addend_two;
        resultcol = result;
    }

    public void Execute()
    {
        if (r.ColExists(resultcol) == false)
            r.AddCol(resultcol,"System.Int32");
        DataRow dr = r.GetRow(tid);
        dr.SetField(resultcol, int.Parse(dr[add_one].ToString()) + int.Parse(dr[add_two].ToString()));
    }
}

class WriteToXMLCommand : ICommand
{
    private ReceiverAPI r;
    
    public WriteToXMLCommand(ref ReceiverAPI rec)
    {
        this.r = rec;
    }

    public void Execute()
    {
        DataTable dt = r.table_;
        int size = dt.Columns.Count;
        if (size < 2)
            return; // error
        
        // The first column is all the headers
        foreach (DataRow row_ in dt.Rows)
        {
            row_[0];
        }


        for (int i = 1; i < size; i++)
        {
            foreach (DataRow row_ in dt.Rows)
            {
                row_[i];
            }
        }
    }

}