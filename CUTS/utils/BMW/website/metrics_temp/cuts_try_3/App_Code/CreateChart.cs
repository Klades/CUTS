using System;
using System.Data;
using System.Configuration;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;
using System.IO;
using System.Xml;
using System.Text;


/// <summary>
/// Summary description for CreateChart
/// </summary>
/// 

namespace CreateCharts
{
    public class Chart
    {
        private DataTable dt;
        private string type;
        private string XMLpath;

        public Chart(DataTable dt, string XMLpath)
        {
            this.dt = dt;
            this.XMLpath = XMLpath;
        }

        public Chart(DataTable dt, string XMLpath, string type)
        {
            this.dt = dt;
            this.type = type;
            this.XMLpath = XMLpath;
        }

        public void generate()
        {
            switch (type)
            {
                case "many":
                    //writeXMLmany();
                    string five = "hi";
                    break;
                case "one":
                    writeXMLone();
                    break;
                default:
                    writeXMLone();
                    break;
            }
  
        }

        private void writeXMLone()
        {
            FileInfo XMLExists = new FileInfo(XMLpath);
            if (XMLExists.Exists)
            {
                File.Delete(XMLpath);
            }
            
            XmlTextWriter writer = new XmlTextWriter(XMLpath , Encoding.UTF8);

            writer.WriteStartDocument();
            writer.WriteStartElement("chart"); // <chart>
            writer.WriteStartElement("chart_data"); // <chart_data>
            writer.WriteStartElement("row");   // <row>
            writer.WriteRaw("<null/>");        // <null/>
            foreach (DataRow row in dt.Rows)
            {
                writer.WriteElementString("string", row["TestID"].ToString());
            }
            writer.WriteEndElement();           // </row>

            for (int i = 1; i < dt.Columns.Count; ++i)
            {
                writer.WriteStartElement("row");   // <row>

                string colname = dt.Columns[i].ColumnName.ToString();
                writer.WriteElementString("string", colname);
                
                foreach (DataRow row in dt.Rows)
                {
                    writer.WriteElementString("number", row[colname].ToString());
                }
                writer.WriteEndElement();
            }
            
            writer.WriteEndElement();  // </chart_data>
            writer.WriteEndElement();  // </chart>
            writer.WriteEndDocument();
            writer.Flush();
            writer.Close();
         }
    }
}