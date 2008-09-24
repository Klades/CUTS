<%@ page language="C#" masterpagefile="~/BMW.master" autoeventwireup="false" codefile="unittest.aspx.cs" inherits="CUTS.Unit_Testing" %>
<%@ register tagprefix="cuts" namespace="CUTS.Web.UI.UnitTesting" assembly="CUTS.Web" %>

<asp:content id="Content1" contentplaceholderid="MainContent" runat="server">
  <h2>Functional/Non-functional Unit Testing</h2>

  <!--
     menu at the top to the page
     -->
  <asp:menu runat="server" id="viewmenu_" orientation="horizontal" onmenuitemclick="handle_onmenuitemclick">
    <staticmenuitemstyle backcolor="darkgray" forecolor="black" verticalpadding="5px"
                         horizontalpadding="10px" font-bold="true" />

    <staticselectedstyle backcolor="#9999FF" forecolor="black" />
    <statichoverstyle backcolor="#CCCCFF" forecolor="black" />

    <items>
      <asp:menuitem text="Configuration" selected="true" value="0" />
      <asp:menuitem text="Specification" value="1" />
    </items>
  </asp:menu>

  <!--
    spacer between the menu and multiview
    -->
  <div style="background-color: #9999FF; height: 4px;">&nbsp;</div>

  <asp:multiview runat="server" id="multiview_" activeviewindex="0"
                 onactiveviewchanged="handle_onactiveviewchanged">

    <asp:view runat="server" id="configuration_view_">
      <!--
        unit test configuration view of the page
        -->
      <table cellpadding="15" cellspacing="20" border="1" style="table-layout:fixed">
        <tr>
          <td style="width:500px; vertical-align: top">
            <!--
              section of the table for creating/removing test suites
              -->
            <h3>I. Test Suites</h3>

            <p>Use the controls below to create a new test suite.</p>

            <table>
              <tr>
                <td class="title">Name: </td>
                <td><asp:textbox id="test_suite_name_" runat="server" cssclass="default_width" /></td>
                <td><asp:button id="btn1" runat="server" text="Create"
                                onclick="onclick_create_test_suite"
                                tabindex="2" cssclass="button" causesvalidation="true"
                                validationgroup="testsuite_create_group_" /></td>
              </tr>
              <tr>
                <td></td>
                <td colspan="2">
                  <asp:requiredfieldvalidator id="test_suite_name_required_" runat="server"
                                              controltovalidate="test_suite_name_"
                                              errormessage="Test suite name is required"
                                              forecolor="red" validationgroup="testsuite_create_group_"
                                              display="static" /></td>
              </tr>

              <tr>
                <td colspan="3">
                  <hr style="color: white; border-top: dashed 1px blue" />
                  <p>Use the controls below to manage existing test suites.</p>
                  <p></p>
                </td>
              </tr>

              <!-- This is the section of the box for managing existing test suites.
                   By clicking a test suite, then a user can either delete it, or
                   add new packages to the test suite -->

              <tr>
                <td class="title" style="vertical-align:top">Existing: </td>
                <td><asp:listbox id="existing_test_suites_" runat="server"
                                 autopostback="true" selectionmode="multiple"
                                 datatextfield="name" datavaluefield="id"
                                 onselectedindexchanged="onchange_existing_test_suites"
                                 cssclass="default_width" appenddatabounditems="true" rows="7" /></td>
              </tr>
              <tr>
                <td></td>
                <td><asp:linkbutton id="delete_test_suite_" runat="server"
                                    text="Delete selected test suite(s)"
                                    onclick="onclick_delete_test_suite" /></td>
              </tr>
            </table>
          </td>

          <td style="width:500px; vertical-align: top">
            <!--
              section of the table for creating/configuring test packages
              for the currently selected test suite.
              -->
            <h3>II. Test Packages</h3>

            <p>Use the controls below to create a new test package.</p>

            <table>
              <tr>
                <td class="title">Name: </td>
                <td><asp:textbox id="test_package_name_" runat="server" cssclass="default_width" /></td>
                <td><asp:button id="create_package_" runat="server" text="Create"
                                onclick="onclick_create_test_package" cssclass="button" causesvalidation="true"
                                validationgroup="test_package_create_group_" /></td>
              </tr>
              <tr>
                <td></td>
                <td colspan="2">
                  <asp:requiredfieldvalidator id="test_package_name_required_" runat="server"
                                              controltovalidate="test_package_name_"
                                              errormessage="Test package name is required"
                                              forecolor="red" validationgroup="test_package_create_group_"
                                              display="static" /></td>
                <td></td>
              </tr>

              <tr>
                <td colspan="3">
                  <hr style="color: white; border-top: dashed 1px blue;" />
                  <p>Use the controls below to manage existing test packages.</p>
                  <p></p>
                </td>
              </tr>

              <tr>
                <td class="title">Existing: </td>
                <td><asp:dropdownlist id="existing_test_packages_" autopostback="true" runat="server"
                                      datatextfield="name" datavaluefield="id" cssclass="default_width"
                                      onselectedindexchanged="onchange_existing_test_packages" /></td>
                <td><asp:button id="insert_test_package_" runat="server" text="Insert" cssclass="button"
                                onclick="onclick_insert_test_package" /></td>
              </tr>

              <tr>
                <td></td>
                <td><asp:linkbutton id="delete_test_package_" runat="server"
                                    text="Delete existing test package"
                                    onclick="onclick_delete_test_package" /></td>
              </tr>

              <tr>
                <td></td>
                <td><asp:listbox id="current_test_packages_" runat="server" autopostback="true"
                                 selectionmode="multiple" datatextfield="name" datavaluefield="id"
                                 cssclass="default_width" onselectedindexchanged="onchange_current_test_packages" /></td>
              </tr>

              <tr>
                <td></td>
                <td colspan="2">
                  <asp:linkbutton id="remove_test_package_" runat="server"
                                  text="Remove selected test package(s) from active test suite" enabled="false"
                                  onclick="onclick_remove_test_package" /></td>
              </tr>
            </table>
          </td>
        </tr>
        <tr>
          <td colspan="2">
            <!--
              section of the page for managing unit tests
              -->
            <h3>III. Unit Tests</h3>

            <p>Use the controls below to manage unit test.</p>

            <table>
              <tr>
                <td class="title">Existing: </td>
                <td><asp:dropdownlist id="existing_unit_tests_" autopostback="true"
                                      runat="server" datatextfield="name" datavaluefield="utid"
                                      cssclass="larger_width"
                                      onselectedindexchanged="onchange_existing_unit_tests" /></td>
                <td><asp:button id="insert_unit_test_" runat="server"
                                onclick="onclick_insert_unit_test" text="Insert" cssclass="button" /></td>
              </tr>

              <tr>
                <td></td>
                <td><asp:linkbutton id="delete_unit_test_" runat="server" text="Delete existing unit test"
                                    onclick="onclick_delete_unit_test_from_database" /></td>
              </tr>

              <tr>
                <td></td>
                <td><asp:listbox id="current_unit_tests_" runat="server"
                                 selectionmode="multiple" datatextfield="name"
                                 datavaluefield="id" autopostback="true" enableviewstate="true"
                                 onselectedindexchanged="onchange_current_unit_tests"
                                 rows="15" cssclass="larger_width" /></td>
              </tr>

              <tr>
                <td></td>
                <td colspan="2">
                  <asp:linkbutton id="remove_unit_test_" runat="server"
                                  text="Remove selected unit test(s) from active test package"
                                  onclick="onclick_remove_unit_test_from_test_package" /></td>
              </tr>
            </table>
          </td>
        </tr>
      </table>
    </asp:view>

    <!--
      Unit test specification view of the page. This portion of the page
      allows user to create their unit test.
      -->
    <asp:view runat="server" id="create_unit_test_view_">
      <!-- wrapper div to make things look nice -->
      <table cellpadding="15" cellspacing="20" border="1" class="view_wrapper">
        <tr>
          <td>
            <!--
              input the name and description of the unit test
              -->
            <table>
              <tr>
                <td class="title">Name:</td>
                <td><asp:textbox id="unit_test_name_" runat="server" width="300px" /></td>
                <td>
                  <asp:requiredfieldvalidator id="unit_test_name_required_" runat="server" controltovalidate="unit_test_name_"
                    errormessage="name is required" forecolor="red" validationgroup="unit_test_create"
                    display="dynamic" /></td>
              </tr>
              <tr>
                <td class="title">Description:</td>
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
            <cuts:logformattable runat="server" id="log_format_table_"
                                 enableviewstate="true" />

            <!--
              required evaluation for the unit test
               -->
            <h3>Evaluation</h3>

            <p>Use metrics, <i>i.e.</i>, the variables enclosed in brackets { }, identifed in the
              <a href="logformats.aspx">log formats</a> above to create an evaluation function
              for the unit test in the text box below. If you have multiple <a href="logformats.aspx">
              log formats</a>, please use the appropriate <a href="logformats.aspx">log format</a>
              prefix when creating the evaluation function.</p>

            <table width="100%">
              <tr>
                <td>
                </td>
                <td>
                  <asp:requiredfieldvalidator id="Requiredfieldvalidator1" runat="server" controltovalidate="unit_test_eval_"
                    errormessage="evaluation is required" forecolor="red" validationgroup="unit_test_create"
                    display="dynamic" /></td>
              </tr>
              <tr>
                <td style="width: 50px">
                  result =
                </td>
                <td>
                  <asp:textbox id="unit_test_eval_" runat="server" width="100%" /></td>
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
              <asp:textbox id="unit_test_warn_" runat="server" />
              (optional)
            </p>
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
              <asp:textbox id="unit_test_fail_" runat="server" />
              (optional)
            </p>

            <!--
              select how to aggregrate multiple results
              -->
            <h3>Aggregration</h3>

            <p>If there are multiple log messages that match your format, this will create multiple
              results. If this situation occurs, how should we aggregrate the multiple results?</p>

            <asp:dropdownlist id="aggr_function_" runat="server">
              <asp:listitem text="Sum" value="SUM" />
              <asp:listitem text="Average" value="AVG" />
              <asp:listitem text="Max" value="MAX" />
              <asp:listitem text="Min" value="MIN" />
              <asp:listitem text="Count" value="COUNT" />
              <asp:listitem text="Count Distinct" value="COUNT DISTINCT" />
            </asp:dropdownlist>

            <!-- button for submitting the new unit test -->
            <p><asp:button id="create_unit_test_" runat="server" text="Create"
                           onclick="onclick_create_unit_test"
                           cssclass="button" causesvalidation="true"
                           validationgroup="unit_test_create" /></p></td>
        </tr>
      </table>
    </asp:view>
  </asp:multiview>
</asp:content>
