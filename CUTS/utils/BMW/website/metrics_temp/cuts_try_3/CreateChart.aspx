<%@ Page Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="CreateChart.aspx.cs" Inherits="CreateChart" Title="Create Chart" %>

<asp:Content ID="Content1" ContentPlaceHolderID="main" Runat="Server">
<pre>
Create a New Chart

UT1 : Please choose a UT
UT2 : Please choose a UT
UT3 : Please choose a UT
</pre>
<p>
<font color="blue">I need more UT's</font>
</p>
<p>
(optional) Eval: 
    <asp:TextBox ID="TextBox1" runat="server">Ex: UT1 / UT2</asp:TextBox>
</p>
<p>
Range of Test's 
    <asp:DropDownList ID="DropDownList1" runat="server">
    <asp:ListItem>All Time</asp:ListItem>
    <asp:ListItem>Recent 5</asp:ListItem>
    <asp:ListItem>Recent 10</asp:ListItem>
    <asp:ListItem>Recent 50</asp:ListItem>
    <asp:ListItem>recent 100</asp:ListItem>
    </asp:DropDownList>
</p>
    <asp:Button ID="Button1" runat="server" Text="Create Chart" />
</asp:Content>
<asp:Content ID="content2" ContentPlaceHolderID="side" runat="server">
No side bar items at this time
</asp:Content>
