<%@ Page 
    Language="C#" 
    MasterPageFile="~/BMW.master" 
    EnableViewState="true" 
    AutoEventWireup="true" 
    CodeFile="UT_Create.aspx.cs" 
    Inherits="UT_Create" 
    Title="Unit Test Create" %>

<%@ Reference 
    Control="~/controls/AddLogFormat.ascx" %>

<asp:Content ID="Content1" ContentPlaceHolderID="MainContent" Runat="Server">


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
                                <asp:PlaceHolder ID="PlaceHolder1" runat="server"></asp:PlaceHolder>
                            </p>
    <p style="color:Red; text-decoration:line-through">
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

