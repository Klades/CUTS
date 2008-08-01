<%@ page language="C#" masterpagefile="~/BMW.master" autoeventwireup="true"
         codefile="unittest.aspx.cs" inherits="Unit_Testing" %>

<asp:content id="Content1" contentplaceholderid="MainContent" runat="Server">
  <h2>Unit Testing Configuration</h2>

  <table cellpadding="15" style="clear: right;"
         cellspacing="20" border="1" width="1100px">
    <tr>
      <!-- section of the table for creating/configuring test suites
           for unit testing using log messages.
           -->
      <td style="width:50%; vertical-align:top">
        <h3>Test Suites</h3>
        <p>Use the controls below to either create a new test suite, or select an existing
        test suite to update. To delete an existing test suite, select it from the listbox
        and click the link below.</p>
        <table>
          <tr>
            <td class="title">Name: </td>
            <td>
              <asp:textbox id="Create_Test_Suite_Name" runat="server" tabindex="1"
                           cssclass="default_width" />

              <asp:button id="btn_Create_Test_Suite" runat="server" text="Create"
                          onclick="onclick_create_test_suite" tabindex="2"
                          cssclass="button" /></td>
          </tr>
          <tr>
            <td class="title" style="vertical-align:top">Existing: </td>
            <td>
              <asp:listbox id="existing_test_suites_" runat="server" autopostback="True"
                           selectionmode="Single" datatextfield="name" datavaluefield="id"
                           onselectedindexchanged="onchange_existing_test_suites"
                           cssclass="default_width"
                           rows="7" /></td>
          </tr>
          <tr>
            <td></td>
            <td><asp:linkbutton id="delete_test_suite_" runat="server"
                                text="Delete selected test suite"
                                onclick="onclick_delete_test_suite" /></td>
          </tr>
        </table>
      </td>

      <!-- section of the table for creating/configuring test packages
           for the currently selected test suite.
           -->
      <td style="width:50%; vertical-align:top">
        <h3>Test Packages</h3>
        <p>Use the control below to either create a new test package, or add
        an existing test package to the selected test suite.</p>

        <table cellspacing="5">
        <tr>
          <td class="title">Name: </td>
          <td>
            <asp:textbox id="create_package_name_" runat="server"
                         tabindex="3" cssclass="default_width" />

            <asp:button id="btn_Create_Test_Suite_Package" runat="server"
                        text="Create" onclick="onclick_create_test_package"
                        tabindex="4" cssclass="button" /></td>
        </tr>
        <tr>
          <td class="title">Existing: </td>
          <td>
            <asp:dropdownlist id="existing_test_packages_" autopostback="true"
                              runat="server" datatextfield="name" datavaluefield="id"
                              cssclass="default_width"
                              onselectedindexchanged="onchange_existing_test_packages" />

            <asp:button id="insert_test_package_" runat="server"
                        text="Insert" cssclass="button"
                        tabindex="5" onclick="onclick_insert_test_package" /></td>
        </tr>
        <tr>
          <td></td>
          <td><asp:linkbutton id="delete_test_package_" runat="server"
                               text="Delete existing test package"
                               onclick="onclick_delete_test_package" /></td>
        </tr>
        <tr>
          <td colspan="2">
            <p><asp:label runat="server" id="package_details_"
                          text="Please select a test suite to view its test packages." />
                          </p>

            <asp:listbox id="current_test_packages_" runat="server" autopostback="True"
                         selectionmode="single" datatextfield="name" datavaluefield="id"
                         width="100%" /></td>
        </tr>
        <tr>
          <td colspan="2">
            <asp:linkbutton id="remove_package_" runat="server"
                            text="Remove package(s) from test suite" onclick="onclick_remove_test_package" /></td>
        </tr>
        </table>
      </td>
    </tr>
    <tr>
      <!-- section of the table for creating/configuring unit test
           for the select test package.
           -->
      <td colspan="2">
        <h3>Unit Tests</h3>

        <table>
          <tr>
            <td style="width:50%">
            <p>Use the control below to either create a new unit test, or update the
            unit tests for the currently selected test package.</p>

            <table cellspacing="5">
              <tr>
                <td></td>
                <td><a href="UT_Create.aspx">Create new unit test</a></td>
              </tr>
              <tr>
                <td class="title">Existing: </td>
                <td>
                  <asp:dropdownlist id="existing_unit_tests_" autopostback="true"
                                    runat="server" datatextfield="name" datavaluefield="utid"
                                    cssclass="default_width" />

                  <asp:button id="insert_unit_test_" runat="server"
                              onclick="onclick_insert_unit_test"
                              text="Insert" cssclass="button" /></td>
              </tr>
              <tr>
                <td></td>
                <td><asp:linkbutton id="delete_unit_test_" runat="server"
                                    text="Delete existing unit test"
                                    onclick="onclick_delete_unit_test" /></td>
              </tr>
              <tr>
                <td colspan="2">
                  <p><asp:label runat="server" id="unit_test_details_"
                                text="Please select an existing test package to view its unit tests." /></p>
                  <p>
                  <asp:listbox id="package_unit_tests_list_" runat="server"
                               selectionmode="Multiple" datatextfield="name" datavaluefield="utid"
                               autopostback="true" onselectedindexchanged="onchange_unit_tests_list"
                               width="100%" /></p></td>
              </tr>
               <tr>
                <td colspan="2">
                  <asp:linkbutton id="remove_unit_test_" runat="server"
                                  text="Remove unit test from test package" onclick="onclick_remove_unit_test" /></td>
              </tr>
           </table>
            </td>
            <td></td>
          </tr>
        </table>
      </td>
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
