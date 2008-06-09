<%@ Import Namespace="System.Xml" %>
<%@ Import Namespace="System.Text" %>
<%@ Import Namespace="CreateCharts" %>
<script language="C#" runat="server">

void Page_Load(object sender, EventArgs e)
{
    Response.Clear();
    Response.ContentType = "text/xml";  
    
    // Create a new XmlTextWriter instance
    XmlTextWriter writer = new XmlTextWriter(Response.OutputStream,Encoding.UTF8);

    writer.WriteStartDocument();
    writer.WriteStartElement("chart"); // <chart>
    writer.WriteStartElement("chart_data"); // <chart_data>
    writer.WriteStartElement("row");   // <row>
    writer.WriteRaw("<null/>");        // <null/>
    writer.WriteElementString("string", "Test 1");
    writer.WriteElementString("string", "Test 2");
    writer.WriteElementString("string", "Test 3");
    writer.WriteElementString("string", "Test 4");
    writer.WriteEndElement();           // </row>


    writer.WriteStartElement("row");   // <row>
    writer.WriteElementString("string", "Test Duration");
    writer.WriteElementString("number", "5");
    writer.WriteElementString("number", "10");
    writer.WriteElementString("number", "29");
    writer.WriteElementString("number", "30");
    writer.WriteEndElement();           // </row>

    writer.WriteStartElement("row");   // <row>
    writer.WriteElementString("string", "Published MIOs");
    writer.WriteElementString("number", "2");
    writer.WriteElementString("number", "13");
    writer.WriteElementString("number", "25");
    writer.WriteElementString("number", "52");
    writer.WriteEndElement();           // </row>


    writer.WriteStartElement("row");   // <row>
    writer.WriteElementString("string", "Received MIO's");
    writer.WriteElementString("number", "2");
    writer.WriteElementString("number", "13");
    writer.WriteElementString("number", "23");
    writer.WriteElementString("number", "21");
    writer.WriteEndElement();           // </row>     

    writer.WriteEndElement();  // </chart_data>
    writer.WriteEndElement();  // </chart>
    writer.WriteEndDocument(); 
    writer.Flush();
    writer.Close();
    Response.End();
}
</script>
