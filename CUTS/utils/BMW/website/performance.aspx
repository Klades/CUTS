<%@ Page Language="C#" CodeFile="performance.aspx.cs" AutoEventWireup="false" Inherits="CUTS.Performance"
    MasterPageFile="~/BMW.master" %>

<%@ Register TagPrefix="cuts" TagName="systemperformance" Src="~/controls/SystemPerformance.ascx" %>
<%@ Register TagPrefix="cuts" TagName="cumulativesystemperformance" Src="~/controls/CumulativeSystemPerformance.ascx" %>
<asp:Content runat="server" ID="main_content" ContentPlaceHolderID="MainContent">
    <h2>
        System-wide Performance Metrics</h2>
    <table style="margin-bottom: 10px">
        <tr>
            <td style="text-align: right; font-weight: bold">
                Test Number:</td>
            <td>
                <%= this.TestNumber %>
            </td>
        </tr>
        <tr>
            <td style="text-align: right; font-weight: bold">
                Execution Path:</td>
            <td>
                <asp:DropDownList runat="server" ID="execution_path_" DataTextField="path_name" DataValueField="path_id" />
                <asp:Button runat="server" ID="view_execution_path_" Text="View..." OnCommand="handle_on_command"
                    CommandName="viewpath" /></td>
        </tr>
    </table>
    <asp:Menu runat="server" ID="viewmenu_" Orientation="horizontal" OnMenuItemClick="handle_onmenuitemclick">
        <StaticMenuItemStyle BackColor="darkgray" ForeColor="black" VerticalPadding="5px"
            HorizontalPadding="10px" Font-Bold="true" />
        <StaticSelectedStyle BackColor="#9999FF" ForeColor="black" />
        <StaticHoverStyle BackColor="#CCCCFF" ForeColor="black" />
        <Items>
            <asp:MenuItem Text="Snapshot Performance" Selected="true" Value="0" />
            <asp:MenuItem Text="Cumulative Performance" Value="1" />
            <asp:MenuItem Text="Unit Test" Value="2" />
            <asp:MenuItem Text="Log Messages" Value="3" />
        </Items>
    </asp:Menu>
    <div style="background-color: #9999FF; height: 3px;">
        <!-- -->
    </div>
    <asp:MultiView runat="server" ID="multiview_" ActiveViewIndex="0" OnActiveViewChanged="handle_onactiveviewchanged">
        <asp:View runat="server" ID="current_view_">
            <table cellpadding="15" cellspacing="20" border="1" class="view_wrapper">
                <tr>
                    <td>
                        <!--
        -- Display the basic information about the system metrics. This
        -- includes the test number and collection time. We should also
        -- display the current duration of the test.
        -->
                        <p>
                            <span style="text-align: right; font-weight: bold">Collection Time:</span>
                            <asp:DropDownList runat="server" ID="collection_times_" DataTextField="collection_time"
                                DataValueField="collection_time" OnSelectedIndexChanged="on_collection_time_changed"
                                AutoPostBack="true" /></p>
                        <cuts:systemperformance runat="server" ID="sysperf_" CategoryHeading="Sender" DataComponentName="component_name"
                            DataComponentNameBaseline="component_name" DataCategoryName="sender_name" DataHostname="hostname"
                            DataHostnameBaseline="hostname" DataMetricType="perf_type" DataMetricTypeBaseline="perf_type"
                            DataSrcName="portname" DataSrcNameBaseline="portname" DataEventCount="perf_count"
                            DataEventCountBaseline="perf_count" DataBestTime="best_time" DataBestTimeBaseline="best_time"
                            DataAvgTime="average_time" DataAvgTimeBaseline="average_time" DataWorstTime="worst_time"
                            DataWorstTimeBaseline="worst_time" EnableViewState="false" />
                    </td>
                </tr>
            </table>
        </asp:View>
        <asp:View runat="server" ID="cumulative_view_">
            <table cellpadding="15" cellspacing="20" border="1" class="view_wrapper">
                <tr>
                    <td>
                        <cuts:cumulativesystemperformance runat="server" ID="cumulative_sysperf_" DataTestNumber="test_number"
                            DataComponentName="component_name" DataComponentID="component" DataCategoryName="sender_name"
                            DataCategoryID="sender" DataMetricType="metric_type" DataSrcName="srcname" DataSrcID="src"
                            DataDstName="dstname" DataDstID="dst" DataEventCount="metric_count" DataBestTime="best_time"
                            DataAvgTime="avg_time" DataWorstTime="worst_time" EnableViewState="false" />
                    </td>
                </tr>
            </table>
        </asp:View>
        <asp:View runat="server" ID="unittest_view_">
            <table cellpadding="15" cellspacing="20" border="1" class="view_wrapper">
                <tr>
                    <td>
                        <asp:DropDownList ID="ddl_Test_Suites" DataTextField="name" DataValueField="id" AutoPostBack="true"
                            OnSelectedIndexChanged="OnChange_ddl_Test_Suites" runat="server">
                        </asp:DropDownList>
                        <br />
                        <br />
                        <asp:Panel ID="panel_Packages_Unit_Tests" runat="server">
                        </asp:Panel>
                    </td>
                </tr>
            </table>
        </asp:View>
        <asp:View runat="server" ID="log_formats_view_">
            <table cellpadding="15" cellspacing="20" border="1" class="view_wrapper">
                <tr>
                    <td>
                        <p>
                            Use the controls below to view the messages that have been recorded for this test
                            run, or to export the data shown in your preferred format.
                        </p>
                        Choose Export Type:
                        <asp:DropDownList AutoPostBack="false" ID="export_type_" runat="server">
                            <asp:ListItem Text="Excel" Value="excel" />
                            <asp:ListItem Text="Word" Value="word" />
                        </asp:DropDownList>
                        <asp:Button runat="server" ID="export_" OnClick="onclick_export" Text="Save Data" />
                        <br />
                        <br />
                        <asp:DataGrid runat="server" ID="current_test_messages_" AllowSorting="true" AutoGenerateColumns="true"
                            CellPadding="2" CellSpacing="0" AllowPaging="true" PageSize="25" Width="650px"
                            ShowHeader="true" ShowFooter="false">
                            <HeaderStyle CssClass="header" />
                            <FooterStyle CssClass="footer" />
                            <AlternatingItemStyle CssClass="alternate-row" />
                            <PagerStyle Mode="NumericPages" />
                            <ItemStyle HorizontalAlign="left" />
                        </asp:DataGrid>
                    </td>
                </tr>
            </table>
        </asp:View>
    </asp:MultiView>
</asp:Content>
