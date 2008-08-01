<%@ page language="C#" masterpagefile="~/BMW.master" enableviewstate="true" autoeventwireup="true"
  codefile="UT_Create.aspx.cs" inherits="UT_Create" title="Unit Test Create" %>

<%@ reference control="~/controls/AddLogFormat.ascx" %>
<asp:content id="Content1" contentplaceholderid="MainContent" runat="Server">
  <h2>Unit Test Configuration</h2>

  <table>
  <tr>
    <td class="title">Name: </td>
    <td><asp:textbox id="UT_name" runat="server" width="300px" /></td>
  </tr>
  <tr>
    <td class="title">Description: </td>
    <td><asp:textbox id="UT_desc" runat="server" width="300px" textmode="singleline" /></td>
  </tr>
  </table>


  <h3>Log Formats</h3>
  <p>Using the dropdown control below, please select the <a href="Log_Formats.aspx">log formats</a>
  to use when evaluating this unit test. If you need more than one more
  <a href="Log_Formats.aspx">log format</a>, then click the <b>I need more log formats</b> link below.</p>

  <!-- Table for selecting log format. A better solution would be to use a placeholder control
       and make each of its children a user-defined log format control. This way, the number
       of child control in the placeholder will represent the number of log messages. It
       will make this webpage a LOT easier to develop and maintain. -->
  <table>
  <tr>
    <td><asp:dropdownlist id="Log_Format_List_1" datatextfield="lfmt" datavaluefield="lfid"
                          runat="server" autopostback="true" onselectedindexchanged="onchange_log_format_list_1"
                          width="800px" /></td>
    <td><asp:label id="Log_Format_1_Prefix" text="" runat="server" /></td>
  </tr>

  <tr>
    <td><asp:dropdownlist id="Log_Format_List_2" datatextfield="lfmt" datavaluefield="lfid"
            onselectedindexchanged="onchange_log_format_list_2" autopostback="true" runat="server"
            width="800px" /></td>
    <td><asp:label id="Log_Format_2_Prefix" text="" runat="server" /></td>
  </tr>
  </table>

  <!-- link for selecting more log formats -->
  <p><asp:linkbutton id="more_log_formats_" runat="server"
                     onclick="onclick_toggle_second_log_format_visibility" /></p>

  <asp:literal text="<h3>Specify the relation</h3>" runat="server" id="relation_head"></asp:literal>
  <asp:dropdownlist id="Relation_Variable_1" datatextfield="extended_varname" datavaluefield="variable_id"
    runat="server">
  </asp:dropdownlist>
  <asp:literal text="&nbsp;&nbsp;==&nbsp;&nbsp;" runat="server" id="relation_text"></asp:literal>
  <asp:dropdownlist id="Relation_Variable_2" datatextfield="extended_varname" datavaluefield="variable_id"
    runat="server">
  </asp:dropdownlist>

  <h3>Evaluation</h3>
  <p>Use metrics, <i>i.e.</i>, the variables enclosed in brackets { }, identifed in the
  <a href="Log_Formats.aspx">log formats</a> above to create an evaluation function for the unit
  test in the text box below. If you have multiple <a href="Log_Formats.aspx">log formats</a>,
  please use the appropriate <a href="Log_Formats.aspx">log format</a> prefix when creating the
  evaluation function.</p>

  <p><tt>result = </tt><asp:textbox id="UT_eval" runat="server" width="380px" /></p>

  <p>
    Warn when&nbsp;&nbsp;&nbsp; &nbsp;result&nbsp;&nbsp;&nbsp;
    <asp:dropdownlist id="UT_warn_comp" runat="server">
      <asp:listitem value="less">&lt;</asp:listitem>
      <asp:listitem value="greater">&gt;</asp:listitem>
      <asp:listitem value="less_equal">&lt;=</asp:listitem>
      <asp:listitem value="greater_equal">&gt;=</asp:listitem>
      <asp:listitem value="equal">==</asp:listitem>
      <asp:listitem value="not_equal">!=</asp:listitem>
    </asp:dropdownlist>
    &nbsp;
    <asp:textbox id="UT_warn" runat="server"></asp:textbox>
    &nbsp;</p>
  <p>
    Fail when&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;result&nbsp;&nbsp;&nbsp;
    <asp:dropdownlist id="UT_fail_comp" runat="server">
      <asp:listitem value="less">&lt;</asp:listitem>
      <asp:listitem value="greater">&gt;</asp:listitem>
      <asp:listitem value="less_equal">&lt;=</asp:listitem>
      <asp:listitem value="greater_equal">&gt;=</asp:listitem>
      <asp:listitem value="equal">==</asp:listitem>
      <asp:listitem value="not_equal">!=</asp:listitem>
    </asp:dropdownlist>
    &nbsp;
    <asp:textbox id="UT_fail" runat="server"></asp:textbox>
    &nbsp;</p>
  <p>
    <!-- Note that the grouping information is hidden for now -->
    <asp:label id="temp_label" runat="server" text="Group By" visible="false"></asp:label>
    <asp:dropdownlist id="DropDownList2" runat="server" visible="false">
      <asp:listitem>test_number</asp:listitem>
    </asp:dropdownlist>
  </p>
  <p>
  </p>
  <h3>Aggregration</h3>

  <p>If there are multiple log messages that match your format, this will create multiple
  results. If this situation occurs, how should we aggregrate the multiple results?</p>

  <!-- Note that there is some server-side processing of these values
          to ensure that no one can pass commands into mySQL -->
  <asp:dropdownlist id="aggr_function_" runat="server">
    <asp:listitem text="Sum" value="SUM" />
    <asp:listitem text="Average" value="AVG" />
    <asp:listitem text="Max" value="MAX" />
    <asp:listitem text="Min" value="MIN" />
    <asp:listitem text="Count" value="COUNT" />
    <asp:listitem text="Count Distinct" value="COUNT DISTINCT" />
  </asp:dropdownlist>

  <!-- button for submitting the new unit test -->
  <p><asp:button id="btn_Submit" runat="server" text="Create"
                 onclick="onclick_submit" cssclass="button" /></p>
</asp:content>
