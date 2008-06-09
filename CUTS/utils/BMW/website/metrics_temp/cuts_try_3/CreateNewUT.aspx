<%@ Page Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="CreateNewUT.aspx.cs" Inherits="CreateNewUT" Title="Create New Unit Test" %>

<asp:Content ID="Content1" ContentPlaceHolderID="main" Runat="Server">
Create A New Unit Test
<p>Name This Unit Test</p>
    <asp:TextBox ID="UT_name" runat="server"></asp:TextBox>
<p>Describe the UT</p>
    <asp:TextBox ID="UT_Desc" runat="server"></asp:TextBox>
<p>Get these Variables</p>
    <asp:TextBox ID="UT_getvars" runat="server"></asp:TextBox>
<p>Perform this Calculation (optional)</p>
    <asp:TextBox ID="UT_eval" runat="server"></asp:TextBox>

    <asp:Button ID="UT_submit" runat="server" Text="Create" OnClick="UT_submit_onclick" />


</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="side" Runat="Server">
    <p class="menusubtitle">
        Latest News</p>
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

