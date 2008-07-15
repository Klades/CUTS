<%@ Page Language="C#" MasterPageFile="~/BMW.master" AutoEventWireup="true" CodeFile="unittest.aspx.cs" Inherits="Unit_Testing" Title="Untitled Page" %>
<asp:Content ID="Content1" ContentPlaceHolderID="MainContent" Runat="Server">
<table cellpadding="15" cellspacing="20" border="1">
    <tr>
    <td width="50%">
    <h3>Test Suites</h3>
    <asp:TextBox ID="txt_Create_Test_Suite"
      runat="server"
      TabIndex="1">
    </asp:TextBox>
    &nbsp;
    <asp:Button ID="btn_Create_Test_Suite"
      runat="server"
      Text="Create New"
      OnClick="OnClick_btn_Create_Test_Suite"
      TabIndex="2" />
    <br />
    <asp:Label ID="txt_Create_Test_Suite_Error" runat="server" Text="" ForeColor="red"></asp:Label>
    
    <br />
    <br />
    <asp:ListBox ID="lb_Test_Suites"
      runat="server"
      AutoPostBack="True"
      SelectionMode="Single"
      DataTextField="name"
      DataValueField="id"
      OnSelectedIndexChanged = "OnChange_lb_Test_Suites"
      ></asp:ListBox><br />
    <br />
    <br />
    </td>
    <td width="50%">
    
    <h3>Test Suite Packages</h3>
    <asp:TextBox ID="txt_Create_Test_Suite_Package"
      runat="server"
      TabIndex="3">
    </asp:TextBox>
    &nbsp;
    <asp:Button ID="btn_Create_Test_Suite_Package"
      runat="server"
      Text="Create New"
      OnClick="OnClick_btn_Create_Test_Suite_Package"
      TabIndex="4" />
    <br />
    <asp:Label ID="txt_Create_Test_Suite_Package_Error" runat="server" Text="" ForeColor="red">
    </asp:Label><br />
    <asp:DropDownList 
        ID="ddl_Add_Existing_Test_Suite_Package"
        AutoPostBack="true"
        runat="server"
        DataTextField="name"
        DataValueField="id"
        OnSelectedIndexChanged="OnChange_ddl_Add_Existing_Test_Suite_Package"
        ></asp:DropDownList><br /><br />
    <asp:ListBox ID="lb_Test_Suite_Packages"
      runat="server"
      AutoPostBack="True"
      SelectionMode="Single"
      DataTextField="name"
      DataValueField="id"
      OnSelectedIndexChanged="OnChange_lb_Test_Suite_Packages"
      ></asp:ListBox><br />
    <br />
    <br />
    
    </td>
    
  </tr>
  <tr>    
<td colspan="2">
    <h3>Unit Tests</h3>
    <a href="UT_Create.aspx" title="New Unit Test">Create New Unit Test</a><br />
    <asp:Label
        ID="txt_Add_Package_Unit_Test_Error"
        Text = ""
        runat="server"
        ForeColor="red"
        ></asp:Label>
    <asp:DropDownList 
        ID="ddl_Add_Package_Unit_Test"
        AutoPostBack="true"
        runat="server"
        DataTextField="name"
        DataValueField="utid"
        OnSelectedIndexChanged="OnChange_ddl_Add_Package_Unit_Test"
        ></asp:DropDownList><br /><br />

    <asp:ListBox ID="lb_Unit_Tests"
      runat="server"
      SelectionMode="Multiple"
      DataTextField="name" 
      DataValueField="utid"
      AutoPostBack="true"
      OnSelectedIndexChanged="OnChange_lb_Unit_Tests">
    </asp:ListBox>
</td>
</tr>
<tr>
<td colspan="2" visible="false" id="td_Unit_Test_Details" runat="server">
<h3>Unit Test Details</h3>
<strike>Click here to edit</strike> (not enabled yet)
    <br />
<table border="0" width="100%">
<tr>
<td width="90">Name</td>
<td><asp:TextBox
       ID="txt_Unit_Test_Details_Name" 
       Text=""
       ReadOnly="true"
       runat="server" Width="171px"
       BorderWidth="0"></asp:TextBox>
    &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp;
</td>
<td>       
ID <asp:Label
     ID="lbl_Unit_Test_Details_ID"
     Text=""
     runat="server"></asp:Label>
    <br />
</td>
</tr>
<tr>
<td>
Description
</td>
<td><asp:TextBox
             ID="txt_Unit_Test_Details_Description"
             ReadOnly="true"
             Text=""
             runat="server"
             TextMode="MultiLine"
             Wrap="true" Height="64px" Width="175px" ></asp:TextBox>
</td>
<td>&nbsp;</td>
</tr>
<tr>
<td>
Evaluation
</td>
<td>
 <asp:TextBox
             ID="txt_Unit_Test_Details_Evaluation"
             ReadOnly="true"
             Text=""
             runat="server" Width="309px"></asp:TextBox>

</td>
<td>&nbsp;</td>
</tr>

<tr>
<td colspan="3">
    <br />
    <br />
Warns when result is 
    <asp:TextBox
      ID="txt_Unit_Test_Details_Warn_Comparison"
      ReadOnly="true"
      Text=""
      runat="server"
      BorderWidth="0"
      ForeColor="DarkGreen"></asp:TextBox>
</td>
</tr>
<tr>
<td colspan="3">
    Fails when result is
    <asp:TextBox
      ID="txt_Unit_Test_Details_Fail_Comparison"
      ReadOnly="true"
      Text=""
      runat="server"
      BorderWidth="0"
      ForeColor="darkgreen"></asp:TextBox>
</td>
</tr>
<tr>
<td colspan="3">
<u>
    <br />
    <br />
    References these Log Formats</u><br />
    <br />
    <asp:DataGrid
      ID="dg_Unit_Test_Detail_Log_Formats"
      AllowSorting="True"
      AutoGenerateColumns="false"
      CellPadding="2"
      runat="server"
      AlternatingItemStyle-BackColor="blue" Width="90%" >
    <Columns>
        <asp:BoundColumn DataField="lfid" HeaderText="ID" ReadOnly="True"></asp:BoundColumn>
        <asp:BoundColumn DataField="lfmt" HeaderText="Format" ReadOnly="True"></asp:BoundColumn>
    </Columns>
        <AlternatingItemStyle BackColor="Blue" />
</asp:DataGrid>
    </td>
    </tr>
    </table>
    
    </td>
</tr>


</table>
</asp:Content>

