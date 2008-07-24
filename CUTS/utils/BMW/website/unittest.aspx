<%@ Page Language="C#" MasterPageFile="~/BMW.master" AutoEventWireup="true" CodeFile="unittest.aspx.cs" Inherits="Unit_Testing" Title="Untitled Page" %>
<asp:Content ID="Content1" ContentPlaceHolderID="MainContent" Runat="Server">
<asp:Button runat="server" CssClass="help-btn" ID="show_help" BackColor="white" OnClick="OnClick_show_help" Text="Show Help" />
<table cellpadding="15" style="clear:right;" cellspacing="20" border="1">
    <tr>
    <td width="50%">
    <h3>Test Suites</h3>
    <asp:TextBox ID="Create_Test_Suite_Name"
      runat="server"
      TabIndex="1">
    </asp:TextBox>
    &nbsp;
    <asp:Button ID="btn_Create_Test_Suite"
      runat="server"
      Text="Create New"
      OnClick="OnClick_Create_Test_Suite"
      TabIndex="2" />&nbsp;<br />
    
    <br />
    <br />
    <asp:ListBox ID="Existing_Test_Suites"
      runat="server"
      AutoPostBack="True"
      SelectionMode="Single"
      DataTextField="name"
      DataValueField="id"
      OnSelectedIndexChanged = "OnChange_Test_Suites_List"
      ></asp:ListBox><br />
    <br />
    <br />
    </td>
    <td width="50%">
    
    <h3>Test Suite Packages</h3>
    <asp:TextBox ID="Create_Package_Name"
      runat="server"
      TabIndex="3">
    </asp:TextBox>
    &nbsp;
    <asp:Button ID="btn_Create_Test_Suite_Package"
      runat="server"
      Text="Create New"
      OnClick="OnClick_Create_Package"
      TabIndex="4" />
    <br />
    <br />
    <asp:DropDownList 
        ID="Add_Existing_Package"
        AutoPostBack="true"
        runat="server"
        DataTextField="name"
        DataValueField="id"
        OnSelectedIndexChanged="OnChange_Add_Existing_Package"
        ></asp:DropDownList><br /><br />
    <asp:ListBox ID="Test_Suite_Packages_List"
      runat="server"
      AutoPostBack="True"
      SelectionMode="Single"
      DataTextField="name"
      DataValueField="id"
      OnSelectedIndexChanged="OnChange_Packages_List"
      ></asp:ListBox><br />
    <br />
    <br />
    
    </td>
    
  </tr>
  <tr>    
<td colspan="2">
    <h3>Unit Tests</h3>
    <a href="UT_Create.aspx" title="New Unit Test">Create New Unit Test</a><br />
    &nbsp;<asp:DropDownList 
        ID="Add_Existing_Unit_Test"
        AutoPostBack="true"
        runat="server"
        DataTextField="name"
        DataValueField="utid"
        OnSelectedIndexChanged="OnChange_Add_Existing_Unit_Test"
        ></asp:DropDownList><br /><br />

    <asp:ListBox ID="Package_Unit_Tests_List"
      runat="server"
      SelectionMode="Multiple"
      DataTextField="name" 
      DataValueField="utid"
      AutoPostBack="true"
      OnSelectedIndexChanged="OnChange_Unit_Tests_List">
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


<asp:Panel 
Width="1000px" 
BorderStyle="Solid" 
ID="my_help_" 
Visible="false" 
runat="server"
BorderColor="black"
BorderWidth="2px"
BackColor="wheat"
style="padding:40px; text-align:center" >
<p>Before reading this, you should understand the terminology we are using here and in the BMW. Test Suites and Test Suite Packages are levels of abstraction, one Test Suite can have infinite Packages, and one Package can have infinite unit tests. The last of the terminology that we have been using would be 'Unit Tests' versus 'Metrics'. The difference is that Unit Tests are Pass/Warn/Fail, based on the evaluation given. Metrics use the same evaluation, but rather than give you a pass/warn/fail, they are simply give you the result of the evaluation (the number that resulted, aka the 'metric').</p>

<p>A quick example would be a test suite for networking which contains packages for testing incoming connections, outgoing connections, and QOS of connections. Each package could contain multiple unit tests that related specifically to their area - the point being that a user could simply run the test suite for networking (from the BMW interface) and every single unit test would be correctly run and the results readied.</p>

<p>Here is a quick picture to help you see visually the idea and understand the Unit Testing abstraction layers: </p>
<img src="images/Unit_Testing_Concept.png" alt="Unit Testing Concept Diagram" />
</asp:Panel>
</asp:Content>

