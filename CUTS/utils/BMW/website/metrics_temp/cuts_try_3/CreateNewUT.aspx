<%@ Page Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="CreateNewUT.aspx.cs" Inherits="CreateNewUT" Title="Create New Unit Test" %>

<asp:Content ID="Content1" ContentPlaceHolderID="main" Runat="Server">
Create A New Unit Test
<p>Name This Unit Test</p>
    <asp:TextBox ID="UT_name" runat="server" Height="27px" Width="185px"></asp:TextBox>
<p>Describe the UT</p>
    <asp:TextBox ID="UT_Desc" runat="server" Height="54px" Width="207px"></asp:TextBox>
<p>
<span style="position:absolute; top: 444px; left: 310px; width: 233px; right: 459px;">
    <b>These Operators Can Be Used:<br /> </b>+ - / *   Normal Arithmetic<br /># Mission Utility (3 arguments)</span>Get these Variables</p>
    <asp:TextBox ID="UT_getvars" runat="server" Height="59px" Width="205px"></asp:TextBox>
<p>Perform this Calculation (optional)</p>
    <asp:TextBox ID="UT_eval" runat="server" Height="43px" Width="191px"></asp:TextBox>

    <br />
    <br />

    <asp:Button ID="UT_submit" runat="server" Text="Create" OnClick="UT_submit_onclick" />


</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="side" Runat="Server">
    <p class="menusubtitle">

<span style="position:absolute; top: 348px; left: 310px; width: 229px; font-weight: normal;">
        <b>These Variables Can Be Grabbed:<br /></b>Test Duration: {int}<br />Published {int} MIOs</span><span 
            style="font-weight: normal">Latest News</span></p>
    <p>
        Sub title for news
    </p>
    <ul class="bulletmenu">
        <li>link 1</li>
        <li>link 1</li>
        <li>link 1</li>
        <li>link 1</li>
        
    </ul>
</asp:Content>

