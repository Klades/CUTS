<%@ Page Language="C#" MasterPageFile="~/MasterPage.master" EnableViewState="true" AutoEventWireup="true" CodeFile="UT_Create.aspx.cs" Inherits="UT_Create" Title="Untitled Page" %>

<asp:Content ID="content1" ContentPlaceHolderID="main" runat="server">


    <p>
        Create New Unit Test</p>
    <p>
        Name
        <asp:TextBox ID="UT_name" runat="server" Width="154px"></asp:TextBox>
&nbsp;&nbsp; Desc
        <asp:TextBox ID="UT_desc" runat="server" Height="44px" Width="202px"></asp:TextBox>
    </p>
    <p>
        Use these Log Formats</p>
    <p>
        <asp:DropDownList ID="DropDownList1" runat="server" Height="24px" Width="431px" 
            onselectedindexchanged="DropDownList1_SelectedIndexChanged" AutoPostBack="true">
        </asp:DropDownList>
&nbsp;
        <asp:Label ID="Label1" runat="server" Text=""></asp:Label>
    </p>
    <p>
        [+] I need more Log Formats</p>
    <p>
        Perform this Evaluation</p>
    <p>
        <asp:TextBox ID="UT_eval" runat="server" Width="241px" Height="24px"></asp:TextBox>
    </p>
    <p>
        Warn when&nbsp;&nbsp;&nbsp;
        &nbsp;Result&nbsp;&nbsp;&nbsp;
        <asp:DropDownList ID="UT_warn_comp" runat="server">
            <asp:ListItem Value="less than">&lt;</asp:ListItem>
            <asp:ListItem Value="greater than">&gt;</asp:ListItem>
            <asp:ListItem Value="less than equal">&lt;=</asp:ListItem>
            <asp:ListItem Value="greater than equal">&gt;=</asp:ListItem>
            <asp:ListItem Value="equal">==</asp:ListItem>
            <asp:ListItem Value="not equal">!=</asp:ListItem>
        </asp:DropDownList>
&nbsp;
        <asp:TextBox ID="UT_warn" runat="server"></asp:TextBox>
        &nbsp;</p>
    <p>
        Fail when&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
        &nbsp;Result&nbsp;&nbsp;&nbsp;
        <asp:DropDownList ID="UT_fail_comp" runat="server">
            <asp:ListItem Value="less than">&lt;</asp:ListItem>
            <asp:ListItem Value="greater than">&gt;</asp:ListItem>
            <asp:ListItem Value="less than equal">&lt;=</asp:ListItem>
            <asp:ListItem Value="greater than equal">&gt;=</asp:ListItem>
            <asp:ListItem Value="equal">==</asp:ListItem>
            <asp:ListItem Value="not equal">!=</asp:ListItem>
        </asp:DropDownList>
&nbsp;
        <asp:TextBox ID="UT_fail" runat="server"></asp:TextBox>
        &nbsp;</p>
    <p>
        Group By :
        <asp:DropDownList ID="DropDownList2" runat="server">
            <asp:ListItem>TestID</asp:ListItem>
        </asp:DropDownList>
    </p>
    <p>
        <asp:Button ID="Button1" runat="server" Text="Submit" onclick="Button1_Click" />
    </p>
    <p>
        &nbsp;</p>


</asp:Content>

<asp:Content ID="contetn2" ContentPlaceHolderID="side" runat="server">


</asp:Content>