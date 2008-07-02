<%@ Page Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="LF_Create.aspx.cs" Inherits="LF_Create" Title="Untitled Page" %>

<asp:Content ContentPlaceHolderID="main" ID="content1" runat="server">

    <p>
        Create New Log Format</p>
    <p>
        <asp:TextBox ID="TextBox1" runat="server" Height="27px" Width="323px"></asp:TextBox>
    <asp:Label ID="Label1" runat="server" Text="A Few Examples"></asp:Label>

    </p>
    <p>
        <asp:Button ID="Button1" runat="server" onclick="Button1_Click" Text="Submit" />

    </p>
    
</asp:Content>
<asp:Content ContentPlaceHolderID="side" ID="content2" runat="server">


</asp:Content>