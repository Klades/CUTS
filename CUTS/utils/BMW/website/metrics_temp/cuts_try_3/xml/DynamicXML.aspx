<%@ Import Namespace="System.Xml" %>
<%@ Import Namespace="System.Text" %>
<%@ Import Namespace="CreateCharts" %>
<script language="C#" runat="server">

void Page_Load(object sender, EventArgs e)
{
    Response.Clear();
    Response.ContentType = "text/xml";  
    
    // Create a new XmlTextWriter instance
    //XmlTextWriter writer = new XmlTextWriter(Response.OutputStream,Encoding.UTF8);
    //CreateChart.Chart chart = new Chart;
    
}
</script>
