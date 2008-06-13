<%@ Page Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="CreateChart.aspx.cs" Inherits="CreateChart" Title="Create Chart" %>

<asp:Content ID="Content1" ContentPlaceHolderID="main" Runat="Server">
<pre>
Create a New Chart</pre>
    <pre>
Name the Chart</pre>
    <pre>
<asp:TextBox ID="Chart_name" runat="server" Width="162px"></asp:TextBox></pre>
    <pre>
Describe the Chart</pre>
    <pre>
<asp:TextBox ID="Chart_desc" runat="server" Height="56px" Width="211px"></asp:TextBox>

UT1 : <asp:DropDownList ID="UT_one" runat="server" 
        onselectedindexchanged="UT_one_SelectedIndexChanged"></asp:DropDownList>



UT2 : <asp:DropDownList ID="UT_two" runat="server"></asp:DropDownList>

UT3 : <asp:DropDownList ID="UT_three" runat="server"></asp:DropDownList>

</pre>
<p>
<font color="blue">I need more UT's</font>
</p>
<p>
(optional) Eval: 
    <asp:TextBox ID="UT_eval" runat="server">Ex: UT1 / UT2</asp:TextBox>
</p>
<p>
Range of Test's 
    <asp:DropDownList ID="UT_range" runat="server">
    <asp:ListItem>All Time</asp:ListItem>
    <asp:ListItem>Recent 5</asp:ListItem>
    <asp:ListItem>Recent 10</asp:ListItem>
    <asp:ListItem>Recent 50</asp:ListItem>
    <asp:ListItem>recent 100</asp:ListItem>
    </asp:DropDownList>
</p>
    <asp:Button ID="Button1" runat="server" Text="Create Chart" 
        onclick="Button1_Click" />
    <span style="position:absolute; top: 150px; left: 336px; height: 16px; width: 215px;">Your Chart will currently look like:</span>
    <img src="images/chart_example.jpg" 
        style="position:absolute; top: 187px; left: 335px;" />
</asp:Content>
<asp:Content ID="content2" ContentPlaceHolderID="side" runat="server">
No side bar items at this time
</asp:Content>
