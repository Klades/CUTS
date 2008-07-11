<%@ Page Language="C#" MasterPageFile="~/BMW.master" AutoEventWireup="true" CodeFile="Log_Formats.aspx.cs" Inherits="Log_Formats" Title="Untitled Page" %>
<asp:Content ID="Content1" ContentPlaceHolderID="MainContent" Runat="Server">

<p>
Create New Log Format
</p>
<p>
<asp:TextBox ID="txt_New_LF" runat="server" Height="27px" Width="323px"></asp:TextBox>
    &nbsp;
<asp:Button ID="btn_New_LF" runat="server" Text="Add" OnClick="OnClick_btn_New_LF" />
    &nbsp;
    <asp:Label ID="lbl_New_LF_Success" runat="server" Text="" />
</p>

<asp:DataGrid runat="server"
     ID="_table"
      AllowSorting="True"
       AutoGenerateColumns="false"
       CellPadding="2">
    <Columns>
        <asp:BoundColumn DataField="lfid" HeaderText="ID"></asp:BoundColumn>
        <asp:BoundColumn DataField="lfmt" HeaderText="Format" ReadOnly="True"></asp:BoundColumn>
    </Columns>
</asp:DataGrid>

</asp:Content>

