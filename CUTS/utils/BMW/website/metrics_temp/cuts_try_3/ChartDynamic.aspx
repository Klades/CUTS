<%@ Page Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="ChartDynamic.aspx.cs" Inherits="ChartDynamic" Title="Dynamically Chart" %>

<asp:Content ID="Content1" ContentPlaceHolderID="main" Runat="Server">
Dynamically Chart Content

<p>What would you likt to chart?</p>
<p>Grab These Variables </p>
<asp:TextBox runat="server" ID="CD_getvars" Height="63px" Width="180px">Ex: Test Duration: {int}</asp:TextBox>
                            
<p>Perform this eval (optional)</p>
<asp:TextBox runat="server" ID="CD_eval" Height="53px" Width="155px">Ex: x / y</asp:TextBox><br /><br />
<asp:Button runat="server" Text="Create Chart" OnClick="CD_submit_onclick" />
                            <p>Note: You will be given an option to save this chart on the next page

<span style="position:absolute; top: 208px; left: 261px;">These Variables Can Be Grabbed:<br />Test Duration: {int}<br />Published {int} MIOs</span><p>&nbsp;
<span style="position:absolute; top: 318px; left: 253px;">These Operators Can Be Used:<br /> + - / *   Normal Arithmetic<br /># Mission Utility (3 arguments)</span>
</asp:Content>
<asp:Content ID="content2" ContentPlaceHolderID="side" runat="server">
</asp:content>
