<%@ Page Language="C#" MasterPageFile="~/BMW.master" AutoEventWireup="true" CodeFile="UT_Chart.aspx.cs" Inherits="UT_Chart" Title="Untitled Page" %>
<asp:Content ID="Content1" ContentPlaceHolderID="MainContent" Runat="Server">

   <object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,0,0"
    width="900" height="500" id="charts">
    <param name="movie" value="charts/charts.swf?library_path=charts/charts_library&xml_source=xml/auto_generated.xml" />
    <param name="quality" value="high" />
    <param name="bgcolor" value="#666666" />
    <param name="allowScriptAccess" value="sameDomain" />
    <embed src="charts/charts.swf?library_path=charts/charts_library&xml_source=xml/auto_generated.xml"
        quality="high" bgcolor="#666666" width="900" height="500" name="charts" allowscriptaccess="sameDomain"
        swliveconnect="true" type="application/x-shockwave-flash" pluginspage="http://www.macromedia.com/go/getflashplayer">
    </embed>
    </object>

</asp:Content>

