<%@ Page Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="ChartDynamic.aspx.cs" Inherits="ChartDynamic" Title="Dynamically Chart" %>

<asp:Content ID="Content1" ContentPlaceHolderID="main" Runat="Server">
Dynamically Chart Content

<p>What would you likt to chart?</p>
<p>Grab These Variables </p>
<asp:TextBox runat="server" ID="t1">Ex: Test Duration: {int}</asp:TextBox>
<p>Perform this eval (optional)</p>
<asp:TextBox runat="server" ID="t2">Ex: x / y</asp:TextBox><br /><br />
<asp:Button runat="server" Text="Create Chart" />
<p>Note: You will be given an option to save this chart on the next page</p>

</asp:Content>
<asp:Content ID="content2" ContentPlaceHolderID="side" runat="server">

</asp:Content>
