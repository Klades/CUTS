<%@ Page language="c#" codefile="tests.aspx.cs" inherits="CUTS.Web.Page.Tests" masterpagefile="~/BMW.master" %>
<%@ register tagprefix="cuts" namespace="CUTS.Web.UI.Archive" assembly="CUTS.Web" %>
<%@ register tagprefix="cuts" namespace="CUTS.Web.UI.UnitTesting" assembly="CUTS.Web" %>

<asp:content runat="server" id="content_" contentplaceholderid="MainContent">
  <h2>Test Archive Broswer</h2>

  <cuts:testbrowser id="browser_" runat="server"
                    downloadpath="~/db/sandbox"
                    enableviewstate="true"
                    ondownloadcomplete="handle_download_complete" />
</asp:content>
