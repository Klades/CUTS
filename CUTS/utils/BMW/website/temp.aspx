<%@ Page Language="C#" MasterPageFile="~/BMW.master" AutoEventWireup="true" CodeFile="temp.aspx.cs" Inherits="CUTS.tempasdf" Title="Untitled Page" %>
<%@ MasterType VirtualPath="~/BMW.master" %>
<asp:Content ID="Content1" ContentPlaceHolderID="MainContent" Runat="Server">
<asp:Button runat="server" ID="one" OnClick="add" Text="Add Info Item" />
<asp:Button runat="server" ID="Button1" OnClick="add_err" Text="Add Err Item" />
<asp:Button runat="server" ID="Button2" OnClick="add_success" Text="Add Success Item" />
<asp:Button runat ="server" ID="adf" Text="PostBack" />
</asp:Content>

