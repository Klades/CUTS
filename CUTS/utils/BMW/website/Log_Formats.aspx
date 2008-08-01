<%@ page language="C#" masterpagefile="~/BMW.master" autoeventwireup="true" codefile="Log_Formats.aspx.cs"
  inherits="Log_Formats" %>

<asp:content id="Content1" contentplaceholderid="MainContent" runat="Server">
  <h2>
    Textual Log Formats</h2>
  <p>
    <asp:textbox id="txt_New_LF" runat="server" width="323px"></asp:textbox>
    <asp:button id="btn_New_LF" runat="server" text="Enter" onclick="OnClick_btn_New_LF" />
  </p>
  <!--
  Hamilton:

  Please update the format of this control so that (1) its width is the entire,
  (2) the id column is hidden, and (3) the user can actually delete a log format
  if they like!!

  Something similar to the grid displayed on default.aspx is what this page should
  look like.
  -->
  <asp:datagrid runat="server" id="log_formats_" allowsorting="True"
                autogeneratecolumns="false" cellpadding="2"
                borderstyle="solid"
                cellspacing="0"
                allowpaging="true"
                pagesize="25"
                width="100%"
                showheader="true"
                showfooter="false">

    <headerstyle cssclass="header" />
    <footerstyle cssclass="footer" />
    <alternatingitemstyle cssclass="alternate-row" />
    <pagerstyle mode="NumericPages" />
    <itemstyle horizontalalign="left" />

    <columns>
      <asp:boundcolumn datafield="lfmt" headertext="Log Format" readonly="true" />
    </columns>
  </asp:datagrid>
</asp:content>
