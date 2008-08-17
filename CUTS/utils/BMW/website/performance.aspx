<%@ page language="C#" codefile="performance.aspx.cs" autoeventwireup="false"
         inherits="CUTS.Performance" masterpagefile="~/BMW.master" %>

<%@ register tagprefix="cuts" tagname="systemperformance"
             src="~/controls/SystemPerformance.ascx" %>

<%@ register tagprefix="cuts" tagname="cumulativesystemperformance"
             src="~/controls/CumulativeSystemPerformance.ascx" %>

<asp:content runat="server" id="main_content"
             contentplaceholderid="MainContent">
               
  <h2>System-wide Performance Metrics</h2>

  <table style="margin-bottom:10px">
    <tr>
      <td style="text-align:right;font-weight:bold">Test Number:</td>
      <td><%= this.TestNumber %></td>
    </tr>
    <tr>
      <td style="text-align:right;font-weight:bold">Execution Path:</td>
      <td><asp:dropdownlist runat="server"
                            id="execution_path_"
                            datatextfield="path_name"
                            datavaluefield="path_id" />
          <asp:button runat="server"
                      id="view_execution_path_"
                      text="View..."
                      oncommand="handle_on_command"
                      commandname="viewpath" /></td>
    </tr>
  </table>

  <asp:menu runat="server"
            id="viewmenu_"
            orientation="horizontal"
            onmenuitemclick="handle_onmenuitemclick">
    <staticmenuitemstyle backcolor="darkgray"
                         forecolor="black"
                         verticalpadding="5px"
                         horizontalpadding="10px"
                         font-bold="true" />

    <staticselectedstyle backcolor="#9999FF"
                         forecolor="black" />

    <statichoverstyle backcolor="#CCCCFF"
                      forecolor="black" />
    <items>
      <asp:menuitem text="Snapshot Performance" selected="true" value="0" />
      <asp:menuitem text="Cumulative Performance" value="1"  />
      <asp:menuitem text="Unit Test" value="2"  />
    </items>
  </asp:menu>

  <div style="background-color:#9999FF; height:3px; margin-bottom:5px"><!-- --></div>

  <asp:multiview runat="server" id="multiview_" activeviewindex="0"
                 onactiveviewchanged="handle_onactiveviewchanged">
    <asp:view runat="server" id="current_view_">
      <!--
        -- Display the basic information about the system metrics. This
        -- includes the test number and collection time. We should also
        -- display the current duration of the test.
        -->
    <p><span style="text-align:right;font-weight:bold">Collection Time:</span>
      <asp:dropdownlist runat="server"
                        id="collection_times_"
                        datatextfield="collection_time"
                        datavaluefield="collection_time"
                        onselectedindexchanged="on_collection_time_changed"
                        autopostback="true" /></p>

      <cuts:systemperformance runat="server"
                              id="sysperf_"
                              categoryheading="Sender"
                              datacomponentname="component_name"
                              datacomponentnamebaseline="component_name"
                              datacategoryname="sender_name"
                              datahostname="hostname"
                              datahostnamebaseline="hostname"
                              datametrictype="perf_type"
                              datametrictypebaseline="perf_type"
                              datasrcname="portname"
                              datasrcnamebaseline="portname"
                              dataeventcount="perf_count"
                              dataeventcountbaseline="perf_count"
                              databesttime="best_time"
                              databesttimebaseline="best_time"
                              dataavgtime="average_time"
                              dataavgtimebaseline="average_time"
                              dataworsttime="worst_time"
                              dataworsttimebaseline="worst_time"
                              enableviewstate="false" />
    </asp:view>


    <asp:view runat="server" id="cumulative_view_">
      <cuts:cumulativesystemperformance
          runat="server"
          id="cumulative_sysperf_"
          datatestnumber="test_number"
          datacomponentname="component_name"
          datacomponentid="component"
          datacategoryname="sender_name"
          datacategoryid="sender"
          datametrictype="metric_type"
          datasrcname="srcname"
          datasrcid="src"
          datadstname="dstname"
          datadstid="dst"
          dataeventcount="metric_count"
          databesttime="best_time"
          dataavgtime="avg_time"
          dataworsttime="worst_time"
          enableviewstate="false" />
    </asp:view>

    <asp:view runat="server" id="unittest_view_">
      
      <asp:DropDownList
          id="ddl_Test_Suites"
          DataTextField="name"
          DataValueField="id"
          AutoPostBack="true"
          OnSelectedIndexChanged="OnChange_ddl_Test_Suites"
          runat="server"></asp:DropDownList>
      <br /><br />
      
      <asp:Panel
          ID="panel_Packages_Unit_Tests"
          runat="server"></asp:Panel>
      
    </asp:view>
    
    <asp:view runat="server" id="log_formats_view_">

      <asp:Button runat="server" ID="export_to_excel_" 
         
        Text="Excel" />

      <asp:DataGrid runat="server" ID="current_log_formats_">
        </asp:DataGrid>
      
    </asp:view>
  </asp:multiview>
</asp:content>
