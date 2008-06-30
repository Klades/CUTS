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

namespace Actions
{
    public class ChartActions
    {
        private int utid_;
        private string grouped_x_;
        private string xmlPath;

        public ChartActions(int utid, string grouped_x, string XMLpath)
        {
            this.utid_ = utid;
            this.grouped_x_ = grouped_x;
            xmlPath = XMLpath;
        }

        public void Chart()
        {
            FileInfo XMLExists = new FileInfo(xmlPath);
            if (XMLExists.Exists)
            {
                File.Delete(xmlPath);
            }

            XmlTextWriter writer = new XmlTextWriter(xmlPath, Encoding.UTF8);

            DataTable dt = DataTableActions.getInstance(utid_).Table;
            
            writer.WriteStartDocument();
            writer.WriteStartElement("chart"); // <chart>
            writer.WriteStartElement("chart_data"); // <chart_data>
            writer.WriteStartElement("row");   // <row>
            writer.WriteRaw("<null/>");        // <null/>
            foreach (DataRow row in dt.Rows)
            {
                writer.WriteElementString("string", row[grouped_x_].ToString());
            }
            writer.WriteEndElement();           // </row>

            for (int i = 1; i < dt.Columns.Count; ++i)
            {
                writer.WriteStartElement("row");   // <row>

                string colname = dt.Columns[i].ColumnName.ToString();
                if (colname == "id")
                    continue;

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