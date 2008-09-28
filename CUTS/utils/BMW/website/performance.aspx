<%@ page language="C#" codefile="performance.aspx.cs" autoeventwireup="false" inherits="CUTS.Performance"
  masterpagefile="~/BMW.master" %>

<%@ register tagprefix="cuts" tagname="systemperformance" src="~/controls/SystemPerformance.ascx" %>
<%@ register tagprefix="cuts" tagname="cumulativesystemperformance" src="~/controls/CumulativeSystemPerformance.ascx" %>
<asp:content runat="server" id="main_content" contentplaceholderid="MainContent">
  <h2>
    System-wide Performance Metrics</h2>
  <table style="margin-bottom: 10px">
    <tr>
      <td style="text-align: right; font-weight: bold">
        Test Number:</td>
      <td>
        <%= this.test_number_ %>
      </td>
    </tr>
    <tr>
      <td style="text-align: right; font-weight: bold">
        Execution Path:</td>
      <td>
        <asp:dropdownlist runat="server" id="execution_path_" datatextfield="path_name" datavaluefield="path_id" />
        <asp:button runat="server" id="view_execution_path_" text="View..." oncommand="handle_on_command"
          commandname="viewpath" /></td>
    </tr>
  </table>
  <asp:menu runat="server" id="viewmenu_" orientation="horizontal" onmenuitemclick="handle_onmenuitemclick">
    <staticmenuitemstyle backcolor="darkgray" forecolor="black" verticalpadding="5px"
      horizontalpadding="10px" font-bold="true" />
    <staticselectedstyle backcolor="#9999FF" forecolor="black" />
    <statichoverstyle backcolor="#CCCCFF" forecolor="black" />
    <items>
      <asp:menuitem text="Snapshot Performance" selected="true" value="0" />
      <asp:menuitem text="Cumulative Performance" value="1" />
      <asp:menuitem text="Unit Testing" value="2" />
      <asp:menuitem text="Log Messages" value="3" />
    </items>
  </asp:menu>

  <div style="background-color:#9999FF;height:3px;margin-bottom:10px">&nbsp;</div>

  <asp:multiview runat="server" id="multiview_" activeviewindex="0"
                 onactiveviewchanged="handle_onactiveviewchanged">
    <asp:view runat="server" id="current_view_">
      <table>
        <tr>
          <td>
            <!--
        -- Display the basic information about the system metrics. This
        -- includes the test number and collection time. We should also
        -- display the current duration of the test.
        -->
            <p>
              <span style="text-align: right; font-weight: bold">Collection Time:</span>
              <asp:dropdownlist runat="server" id="collection_times_" datatextfield="collection_time"
                datavaluefield="collection_time" onselectedindexchanged="on_collection_time_changed"
                autopostback="true" /></p>
            <cuts:systemperformance runat="server" id="sysperf_" categoryheading="Sender" datacomponentname="component_name"
              datacomponentnamebaseline="component_name" datacategoryname="sender_name" datahostname="hostname"
              datahostnamebaseline="hostname" datametrictype="perf_type" datametrictypebaseline="perf_type"
              datasrcname="portname" datasrcnamebaseline="portname" dataeventcount="perf_count"
              dataeventcountbaseline="perf_count" databesttime="best_time" databesttimebaseline="best_time"
              dataavgtime="average_time" dataavgtimebaseline="average_time" dataworsttime="worst_time"
              dataworsttimebaseline="worst_time" enableviewstate="false" />
          </td>
        </tr>
      </table>
    </asp:view>

    <asp:view runat="server" id="cumulative_view_">
      <table>
        <tr>
          <td>
            <cuts:cumulativesystemperformance runat="server" id="cumulative_sysperf_" datatestnumber="test_number"
              datacomponentname="component_name" datacomponentid="component" datacategoryname="sender_name"
              datacategoryid="sender" datametrictype="metric_type" datasrcname="srcname" datasrcid="src"
              datadstname="dstname" datadstid="dst" dataeventcount="metric_count" databesttime="best_time"
              dataavgtime="avg_time" dataworsttime="worst_time" enableviewstate="false" />
          </td>
        </tr>
      </table>
    </asp:view>

    <asp:view runat="server" id="unittest_view_">
      <table>
        <tr>
          <td class="title">Test Suite: </td>
          <td><asp:dropdownlist runat="server" id="ddl_Test_Suites"
                                datatextfield="name" datavaluefield="id"
                                autopostback="false" runat="server"
                                width="150px" />
          <td><asp:button runat="server" id="evaluate_test_suite_"
                          onclick="onclick_evaluate_test_suite" text="Evaluate" /> </td>
        </tr>
      </table>
      <br />
      <asp:panel id="unit_test_panel_" runat="server" />
    </asp:view>

    <asp:view runat="server" id="log_formats_view_">
      <table>
        <tr>
          <td>
            <p>
              Use the controls below to view the messages that have been recorded for this test
              run, or to export the data shown in your preferred format.
            </p>
            Choose Export Type:
            <asp:dropdownlist autopostback="false" id="export_type_" runat="server">
              <asp:listitem text="Excel" value="excel" />
              <asp:listitem text="Word" value="word" />
            </asp:dropdownlist>
            <asp:button runat="server" id="export_" onclick="onclick_export" text="Save Data" />
            <br />
            <br />
            <asp:datagrid runat="server" id="current_test_messages_" allowsorting="true" autogeneratecolumns="true"
              cellpadding="2" cellspacing="0" allowpaging="true" pagesize="25" width="650px"
              showheader="true" showfooter="false">
              <headerstyle cssclass="header" />
              <footerstyle cssclass="footer" />
              <alternatingitemstyle cssclass="alternate-row" />
              <pagerstyle mode="NumericPages" />
              <itemstyle horizontalalign="left" />
            </asp:datagrid>
          </td>
        </tr>
      </table>
    </asp:view>
  </asp:multiview>
</asp:content>
