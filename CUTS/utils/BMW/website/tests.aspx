<%@ Page language="c#" codefile="tests.aspx.cs" inherits="CUTS.Web.Page.Tests" masterpagefile="~/BMW.master" %>
<%@ register tagprefix="cuts" namespace="CUTS.Web.UI.Archive" assembly="CUTS.Web" %>

<asp:content runat="server" id="content_" contentplaceholderid="MainContent">
  <cuts:testbrowser id="browser_" runat="server" />
</asp:content>
