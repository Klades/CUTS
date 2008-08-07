<%@ page language="C#" masterpagefile="~/BMW.master" autoeventwireup="false" codefile="unittest.aspx.cs"
  inherits="Unit_Testing" %>

<asp:content id="Content1" contentplaceholderid="MainContent" runat="Server">
  <h2>Unit Testing Configuration</h2>
  <table cellpadding="15" style="clear: right;" cellspacing="20" border="1">
    <tr>
      <!-- section of the table for creating/configuring test suites
           for unit testing using log messages.
           -->
      <td style="width: 50%; vertical-align: top">
        <h3>I. Test Suites</h3>
        <p>Use the controls below to either create a new test suite, or select an existing
          test suite to update. To delete an existing test suite, select it from the listbox
          and click the link below.</p>
        <table>
          <tr>
            <td>
            </td>
            <td>
              <asp:requiredfieldvalidator id="test_suite_name_required_" runat="server" controltovalidate="test_suite_name_"
                errormessage="test suite name is required" forecolor="red" validationgroup="testsuite_create"
                display="dynamic" /></td>
          </tr>
          <tr>
            <td class="title" style="vertical-align: top">Name: </td>
            <td>
              <asp:textbox id="test_suite_name_" runat="server" tabindex="1" cssclass="default_width" />
              <asp:button id="btn_Create_Test_Suite" runat="server" text="Create" onclick="onclick_create_test_suite"
                tabindex="2" cssclass="button" causesvalidation="true" validationgroup="testsuite_create" /></td>
          </tr>
          <tr>
            <td class="title" style="vertical-align: top">Existing: </td>
            <td>
              <asp:listbox id="existing_test_suites_" runat="server" autopostback="True" selectionmode="Single"
                datatextfield="name" datavaluefield="id" onselectedindexchanged="onchange_existing_test_suites"
                cssclass="default_width" appenddatabounditems="true" rows="7" /></td>
          </tr>
          <tr>
            <td>
            </td>
            <td>
              <asp:linkbutton id="delete_test_suite_" runat="server" text="Delete selected test suite"
                onclick="onclick_delete_test_suite" /></td>
          </tr>
        </table>
      </td>
      <!-- section of the table for creating/configuring test packages
           for the currently selected test suite.
           -->
      <td style="width: 50%; vertical-align: top">
        <h3>II. Test Packages</h3>
        <p>Use the control below to either create a new test package, or add an existing test
          package to the selected test suite.</p>
        <table cellspacing="5">
          <tr>
            <td>
            </td>
            <td>
              <asp:requiredfieldvalidator id="test_package_name_required_" runat="server" controltovalidate="test_package_name_"
                errormessage="test packge name is required" forecolor="red" validationgroup="test_package_create"
                display="dynamic" /></td>
          </tr>
          <tr>
            <td class="title">Name: </td>
            <td>
              <asp:textbox id="test_package_name_" runat="server" tabindex="3" cssclass="default_width" />
              <asp:button id="create_test_package_" runat="server" text="Create" onclick="onclick_create_test_package"
                tabindex="4" cssclass="button" causesvalidation="true" validationgroup="test_package_create" /></td>
          </tr>
          <tr>
            <td class="title">Existing: </td>
            <td>
              <asp:dropdownlist id="existing_test_packages_" autopostback="true" runat="server"
                datatextfield="name" datavaluefield="id" cssclass="default_width" onselectedindexchanged="onchange_existing_test_packages" />
              <asp:button id="insert_test_package_" runat="server" text="Insert" cssclass="button"
                tabindex="5" onclick="onclick_insert_test_package" /></td>
          </tr>
          <tr>
            <td>
            </td>
            <td>
              <asp:linkbutton id="delete_test_package_" runat="server" text="Delete existing test package"
                onclick="onclick_delete_test_package" /></td>
          </tr>
          <tr>
            <td colspan="2">
              <p>
                <asp:label runat="server" id="package_details_" text="Please select a test suite to view its test packages." />
              </p>
              <asp:listbox id="current_test_packages_" runat="server" autopostback="True" selectionmode="single"
                datatextfield="name" datavaluefield="id" width="100%" /></td>
          </tr>
          <tr>
            <td colspan="2">
              <asp:linkbutton id="remove_package_" runat="server" text="Remove package(s) from test suite"
                onclick="onclick_remove_test_package" /></td>
          </tr>
        </table>
      </td>
    </tr>
    <tr>
      <td colspan="2">
        <table cellpadding="5">
          <tr>
            <td colspan="2">
              <h3>III. Unit Tests</h3>
              <p>Use the control on the left to create a new unit test, or use the controls on the
                right to update the unit tests for the currently selected test package. To update an
                existing unit test, select it from the <b>Existing</b> dropdown list on the right.</p>
            </td>
          </tr>
          <tr valign="top">
            <td style="border-right:1px solid darkgray">
              <!-- input the name and description of the unit test -->
              <table>
                <tr>
                  <td class="title">Name: </td>
                  <td><asp:textbox id="unit_test_name_" runat="server" width="300px" /></td>
                  <td><asp:requiredfieldvalidator
                        id="unit_test_name_required_" runat="server" controltovalidate="unit_test_name_"
                        errormessage="name is required" forecolor="red" validationgroup="unit_test_create"
                        display="dynamic" /></td>
                </tr>
                <tr>
                  <td class="title">Description: </td>
                  <td><asp:textbox id="unit_test_description_" runat="server" width="300px" textmode="singleline" /></td>
                  <td>(optional)</td>
                </tr>
              </table>

              <!-- select the log formats to use for the unit test -->
              <h3>Log Formats</h3>
              <p>Using the dropdown control below, please select the <a href="logformats.aspx">log
              formats</a> to use when evaluating this unit test. If you need more than one more
              <a href="logformats.aspx">log format</a>, then click the <b>I need more log formats</b>
              link below.</p>

              <!-- Table for selecting log format. A better solution would be to use a placeholder control
                       and make each of its children a user-defined log format control. This way, the number
                       of child control in the placeholder will represent the number of log messages. It
                       will make this webpage a LOT easier to develop and maintain. -->

              <asp:table runat="server" id="log_formats_">
                <asp:tableheaderrow>
                  <asp:tableheadercell>Prefix</asp:tableheadercell>
                  <asp:tableheadercell>Log Format</asp:tableheadercell>
                  <asp:tableheadercell>Relation</asp:tableheadercell>
                </asp:tableheaderrow>
              </asp:table>

              <p><asp:linkbutton runat="server" id="more_log_formats_"
                                 text="I need more log formats"
                                 onclick="onclick_more_log_formats" /></p>

              <!-- required evaluation for the unit test -->
              <h3>Evaluation</h3>
              <p>Use metrics, <i>i.e.</i>, the variables enclosed in brackets { }, identifed in the
                <a href="logformats.aspx">log formats</a> above to create an evaluation function
                for the unit test in the text box below. If you have multiple <a href="logformats.aspx">
                  log formats</a>, please use the appropriate <a href="logformats.aspx">log format</a>
                prefix when creating the evaluation function.</p>

              <table width="100%">
                <tr>
                  <td></td>
                  <td>
                    <asp:requiredfieldvalidator
                        id="Requiredfieldvalidator1" runat="server" controltovalidate="unit_test_eval_"
                        errormessage="evaluation is required" forecolor="red" validationgroup="unit_test_create"
                        display="dynamic" /></td>
                </tr>
                <tr>
                  <td style="width: 50px">result = </td>
                  <td><asp:textbox id="unit_test_eval_" runat="server" width="100%" /></td>
                </tr>
              </table>
              <p>
                Warn when&nbsp;&nbsp;&nbsp; &nbsp;result&nbsp;&nbsp;&nbsp;
                <asp:dropdownlist id="UT_warn_comp" runat="server">
                  <asp:listitem value="less">&lt;</asp:listitem>
                  <asp:listitem value="greater">&gt;</asp:listitem>
                  <asp:listitem value="less_equal">&lt;=</asp:listitem>
                  <asp:listitem value="greater_equal">&gt;=</asp:listitem>
                  <asp:listitem value="equal">==</asp:listitem>
                  <asp:listitem value="not_equal">!=</asp:listitem>
                </asp:dropdownlist>

                <asp:textbox id="unit_test_warn_" runat="server" /> (optional)</p>
              <p>
                Fail when&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;result&nbsp;&nbsp;&nbsp;
                <asp:dropdownlist id="UT_fail_comp" runat="server">
                  <asp:listitem value="less">&lt;</asp:listitem>
                  <asp:listitem value="greater">&gt;</asp:listitem>
                  <asp:listitem value="less_equal">&lt;=</asp:listitem>
                  <asp:listitem value="greater_equal">&gt;=</asp:listitem>
                  <asp:listitem value="equal">==</asp:listitem>
                  <asp:listitem value="not_equal">!=</asp:listitem>
                </asp:dropdownlist>

                <asp:textbox id="unit_test_fail_" runat="server" /> (optional)</p>
              <p>
                <!-- Note that the grouping information is hidden for now -->
                <asp:label id="temp_label" runat="server" text="Group By" visible="false"></asp:label>
                <asp:dropdownlist id="DropDownList2" runat="server" visible="false">
                  <asp:listitem>test_number</asp:listitem>
                </asp:dropdownlist>
              </p>

              <!-- select how to aggregrate multiple results -->
              <h3> Aggregration</h3>
              <p>If there are multiple log messages that match your format, this will create multiple
                results. If this situation occurs, how should we aggregrate the multiple results?</p>
              <!-- Note that there is some server-side processing of these values
                          to ensure that no one can pass commands into mySQL -->
              <asp:dropdownlist id="aggr_function_" runat="server">
                <asp:listitem text="Sum" value="SUM" />
                <asp:listitem text="Average" value="AVG" />
                <asp:listitem text="Max" value="MAX" />
                <asp:listitem text="Min" value="MIN" />
                <asp:listitem text="Count" value="COUNT" />
                <asp:listitem text="Count Distinct" value="COUNT DISTINCT" />
              </asp:dropdownlist>
              <!-- button for submitting the new unit test -->
              <p>
                <asp:button id="create_unit_test_" runat="server" text="Create" onclick="onclick_create_unit_test"
                  cssclass="button" causesvalidation="true" validationgroup="unit_test_create" /></p>
            </td>

            <td style="width:375px">
              <!-- section of the page for selecting an existing unit test -->
              <table cellspacing="5">
                <tr>
                  <td class="title">Existing: </td>
                  <td><asp:dropdownlist id="existing_unit_tests_" autopostback="true" runat="server" datatextfield="name"
                      datavaluefield="utid" width="100%" /></td>

                  <td><asp:button id="insert_unit_test_" runat="server"
                        onclick="onclick_insert_unit_test"
                        text="Insert" cssclass="button" /></td>
                </tr>
                <tr>
                  <td></td>
                  <td colspan="2">
                    <asp:linkbutton id="delete_unit_test_" runat="server" text="Delete existing unit test"
                                    onclick="onclick_delete_unit_test" /></td>
                </tr>
                <tr>
                  <td colspan="3">
                    <p>
                      <asp:label runat="server" id="unit_test_details_"
                                 text="Please select an existing test package to view its unit tests." /></p>
                    <p>
                      <asp:listbox id="package_unit_tests_list_" runat="server" selectionmode="Multiple"
                        datatextfield="name" datavaluefield="utid" autopostback="true" onselectedindexchanged="onchange_unit_tests_list"
                        rows="15" width="100%" /></p>
                  </td>
                </tr>
                <tr>
                  <td colspan="2">
                    <asp:linkbutton id="remove_unit_test_" runat="server" text="Remove unit test from test package"
                      onclick="onclick_remove_unit_test" /></td>
                </tr>
              </table>
            </td>
          </tr>
        </table>
      </td>
    </tr>
  </table>
</asp:content>
