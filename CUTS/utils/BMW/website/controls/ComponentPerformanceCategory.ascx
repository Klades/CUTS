<%@ Control Language="C#"
            AutoEventWireup="true"
            CodeFile="ComponentPerformanceCategory.ascx.cs"
            Inherits="CUTS.ComponentPerformanceCategory" %>

<%@ reference control="~/controls/PortPerformance.ascx" %>
<%@ reference control="~/controls/CumulativePortPerformance.ascx" %>

<div><asp:label runat="server" id="category_name_" text="Category" />:
     <asp:label runat="server" id="category_"/></div>
<asp:placeholder runat="server" id="ports_" />
