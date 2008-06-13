<%@ Page Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="SavedCharts.aspx.cs" Inherits="SavedCharts" Title="Saved Charts" %>

<asp:Content ID="Content1" ContentPlaceHolderID="main" Runat="Server">
<p>Here are the charts you have saved</p>
<p><a href="SavedChartsWrapper.aspx?id=1">Test Duration</a></p>
<p><a href="SavedChartsWrapper.aspx?id=2">Published MIO's</a></p>
<p><a href="SavedChartsWrapper.aspx?id=3">Received MIO's</a></p>
</asp:Content>
<asp:Content ID="content2" ContentPlaceHolderID="side" runat="server" />
