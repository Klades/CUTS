<%@ page language="C#" masterpagefile="~/BMW.master" autoeventwireup="true"
         codefile="logformats.aspx.cs" inherits="CUTS.Log_Formats" %>

<asp:content id="Content1" contentplaceholderid="MainContent" runat="Server">
  <h2>Textual Log Formats</h2>
  <p>Use the control below to enter a new log format. To identify metrics of interest in
  a log format, enclose the text that represents the metric in brackets as a variable
  declaratio. The following is an example for locating log messages that capture the number
  of events received:</p>

  <table>
  <tr>
    <td colspan="2">
      <dl>
        <dt class="title">Example:</dt>
        <dd><tt>received {INT events} events</tt></dd>
      </dl>
    </td>
  </tr>
  <tr>
    <td class="title">Log format: </td>
    <td><asp:textbox id="log_format_" runat="server" width="300px" /></td>
    <td><asp:requiredfieldvalidator id="logformat_required_" runat="server"
                                    controltovalidate="log_format_"
                                    errormessage="log format is required"
                                    forecolor="red"
                                    validationgroup="insert_logformat"
                                    display="dynamic" /></td>
  </tr>
  <tr>
    <td></td>
    <td>
      <asp:button id="btn_New_LF" runat="server" text="Insert"
                  onclick="OnClick_btn_New_LF" cssclass="button"
                  causesvalidation="true"
                  validationgroup="insert_logformat" /></td>
    <td></td>
  </tr>
  </table>

  <p>The following is a list of existing log formats:</p>

  <asp:datagrid runat="server" id="log_formats_" allowsorting="true"
                autogeneratecolumns="false" cellpadding="2"
                borderstyle="solid"
                cellspacing="0"
                allowpaging="true"
                pagesize="25"
                width="650px"
                showheader="true"
                showfooter="false"
                datakeyfield="lfid">

    <headerstyle cssclass="header" />
    <footerstyle cssclass="footer" />
    <alternatingitemstyle cssclass="alternate-row" />
    <pagerstyle mode="NumericPages" />
    <itemstyle horizontalalign="left" />

    <columns>
      <asp:boundcolumn datafield="lfmt" headertext="Log Format" readonly="true" />

      <asp:templatecolumn itemstyle-horizontalalign="center">
        <headertemplate>
          <asp:checkbox runat="server" id="delete_"
                        causesvalidation="false"
                        oncheckedchanged="oncheckchanged_toggle_delete"
                        autopostback="true" />
        </headertemplate>
        <itemtemplate>
          <asp:checkbox runat="server" id="delete_"
                        causesvalidation="false"
                        autopostback="false" />
        </itemtemplate>
      </asp:templatecolumn>
    </columns>
  </asp:datagrid>

  <p><asp:linkbutton runat="server"
                     id="delete_log_formats_"
                     text="Delete selected log formats"
                     onclick="onclick_delete_log_formats" /></p>
</asp:content>
