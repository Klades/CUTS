<%@ page language="C#" masterpagefile="~/BMW.master" autoeventwireup="true" codefile="unittest.aspx.cs"
  inherits="Unit_Testing" %>

<asp:content id="Content1" contentplaceholderid="MainContent" runat="Server">
  <table cellpadding="15" style="clear: right;" cellspacing="20" border="1">
    <tr>
      <td width="50%">
        <h3>
          Test Suites</h3>
        <asp:textbox id="Create_Test_Suite_Name" runat="server" tabindex="1">
        </asp:textbox>
        &nbsp;
        <asp:button id="btn_Create_Test_Suite" runat="server" text="Create New" onclick="OnClick_Create_Test_Suite"
          tabindex="2" />&nbsp;<br />
        <br />
        <br />
        <asp:listbox id="Existing_Test_Suites" runat="server" autopostback="True" selectionmode="Single"
          datatextfield="name" datavaluefield="id" onselectedindexchanged="OnChange_Test_Suites_List">
        </asp:listbox><br />
        <br />
        <asp:button id="Button1" runat="server" text="Delete" onclick="OnClick_Delete_Test_Suite" /><br />
      </td>
      <td width="50%">
        <h3>
          Test Suite Packages</h3>
        <asp:textbox id="Create_Package_Name" runat="server" tabindex="3">
        </asp:textbox>
        &nbsp;
        <asp:button id="btn_Create_Test_Suite_Package" runat="server" text="Create New" onclick="OnClick_Create_Package"
          tabindex="4" />
        <br />
        <br />
        <asp:dropdownlist id="Add_Existing_Package" autopostback="true" runat="server" datatextfield="name"
          datavaluefield="id" onselectedindexchanged="OnChange_Add_Existing_Package">
        </asp:dropdownlist><br />
        <br />
        <asp:listbox id="Test_Suite_Packages_List" runat="server" autopostback="True" selectionmode="Single"
          datatextfield="name" datavaluefield="id" onselectedindexchanged="OnChange_Packages_List">
        </asp:listbox><br />
        <br />
        <asp:button id="Button2" runat="server" text="Remove" onclick="OnClick_Remove_Package" />
        <asp:button id="Button3" runat="server" text="Delete" onclick="OnClick_Delete_Package" /><br />
      </td>
    </tr>
    <tr>
      <td colspan="2">
        <h3>
          Unit Tests</h3>
        <a href="UT_Create.aspx" title="New Unit Test">Create New Unit Test</a><br />
        &nbsp;<asp:dropdownlist id="Add_Existing_Unit_Test" autopostback="true" runat="server"
          datatextfield="name" datavaluefield="utid" onselectedindexchanged="OnChange_Add_Existing_Unit_Test">
        </asp:dropdownlist><br />
        <br />
        <asp:listbox id="Package_Unit_Tests_List" runat="server" selectionmode="Multiple"
          datatextfield="name" datavaluefield="utid" autopostback="true" onselectedindexchanged="OnChange_Unit_Tests_List">
        </asp:listbox>
        <br />
        <br />
        <asp:button id="Button4" runat="server" text="Remove" onclick="OnClick_Remove_Unit_Test" />
        <asp:button id="Button5" runat="server" text="Delete" onclick="OnClick_Delete_Unit_Test" /></td>
    </tr>
    <tr>
      <td colspan="2" visible="false" id="td_Unit_Test_Details" runat="server">
        <h3>
          Unit Test Details</h3>
        <strike>Click here to edit</strike> (not enabled yet)
        <br />
        <table border="0" width="100%">
          <tr>
            <td width="90">
              Name</td>
            <td>
              <asp:textbox id="txt_Unit_Test_Details_Name" text="" readonly="true" runat="server"
                width="171px" borderwidth="0"></asp:textbox>
              &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp;
            </td>
            <td>
              ID
              <asp:label id="lbl_Unit_Test_Details_ID" text="" runat="server"></asp:label>
              <br />
            </td>
          </tr>
          <tr>
            <td>
              Description
            </td>
            <td>
              <asp:textbox id="txt_Unit_Test_Details_Description" readonly="true" text="" runat="server"
                textmode="MultiLine" wrap="true" height="64px" width="175px"></asp:textbox>
            </td>
            <td>
              &nbsp;</td>
          </tr>
          <tr>
            <td>
              Evaluation
            </td>
            <td>
              <asp:textbox id="txt_Unit_Test_Details_Evaluation" readonly="true" text="" runat="server"
                width="309px"></asp:textbox>
            </td>
            <td>
              &nbsp;</td>
          </tr>
          <tr>
            <td colspan="3">
              <br />
              <br />
              Warns when result is
              <asp:textbox id="txt_Unit_Test_Details_Warn_Comparison" readonly="true" text="" runat="server"
                borderwidth="0" forecolor="DarkGreen"></asp:textbox>
            </td>
          </tr>
          <tr>
            <td colspan="3">
              Fails when result is
              <asp:textbox id="txt_Unit_Test_Details_Fail_Comparison" readonly="true" text="" runat="server"
                borderwidth="0" forecolor="darkgreen"></asp:textbox>
            </td>
          </tr>
          <tr>
            <td colspan="3">
              <u>
                <br />
                <br />
                References these Log Formats</u><br />
              <br />
              <asp:datagrid id="dg_Unit_Test_Detail_Log_Formats" allowsorting="True" autogeneratecolumns="false"
                cellpadding="2" runat="server" alternatingitemstyle-backcolor="blue" width="90%">
                <columns>
                  <asp:boundcolumn datafield="lfid" headertext="ID" readonly="True"></asp:boundcolumn>
                  <asp:boundcolumn datafield="lfmt" headertext="Format" readonly="True"></asp:boundcolumn>
                </columns>
                <alternatingitemstyle backcolor="Blue" />
              </asp:datagrid>
            </td>
          </tr>
        </table>
      </td>
    </tr>
  </table>
</asp:content>
