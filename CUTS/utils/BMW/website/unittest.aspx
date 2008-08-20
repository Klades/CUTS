<%@ Page Language="C#" MasterPageFile="~/BMW.master" AutoEventWireup="false" CodeFile="unittest.aspx.cs"
    Inherits="CUTS.Unit_Testing" %>

<asp:Content ID="Content1" ContentPlaceHolderID="MainContent" runat="Server">
    <h2>
        Unit Testing Configuration</h2>
    <asp:Menu runat="server" ID="viewmenu_" Orientation="horizontal" OnMenuItemClick="handle_onmenuitemclick">
        <StaticMenuItemStyle BackColor="darkgray" ForeColor="black" VerticalPadding="5px"
            HorizontalPadding="10px" Font-Bold="true" />
        <StaticSelectedStyle BackColor="#9999FF" ForeColor="black" />
        <StaticHoverStyle BackColor="#CCCCFF" ForeColor="black" />
        <Items>
            <asp:MenuItem Text="Configuration" Selected="true" Value="0" />
            <asp:MenuItem Text="Unit Test Creation" Value="1" />
        </Items>
    </asp:Menu>
    
    <div style="background-color:#9999FF; height:4px;"><!-- --></div>
    
    <asp:MultiView runat="server" ID="multiview_" ActiveViewIndex="0" OnActiveViewChanged="handle_onactiveviewchanged">
        <asp:View runat="server" ID="configuration_view_">
            <table cellpadding="15" cellspacing="20" border="1" class="view_wrapper">
                <tr>
                
                    <!-- section of the table for creating/removing test suites. -->
                    <td style="width: 40%; vertical-align: top">
                        <h3>I. Test Suites</h3>
                        <p>
                            Use the controls below to either create a new test suite, or select an existing
                            test suite to update. To delete an existing test suite, select it from the listbox
                            and click the link that appears below the box.
                        </p>
                        
                        <asp:RequiredFieldValidator ID="test_suite_name_required_" runat="server" ControlToValidate="test_suite_name_"
                            ErrorMessage="test suite name is required. <br />" ForeColor="red" ValidationGroup="testsuite_create"
                            Display="dynamic" />
                        
                        <span style="margin-left:10px;">Name:</span>
                        <asp:TextBox ID="test_suite_name_" runat="server" TabIndex="1" CssClass="default_width" /><br />
                        <span style="position:relative; top:5px; padding-left: 250px;">
                            <asp:Button ID="btn1" runat="server" Text="Create" OnClick="onclick_create_test_suite"
                                TabIndex="2" CssClass="button" CausesValidation="true" ValidationGroup="testsuite_create" />
                        </span>
                        
                        <hr style="color:White; border-top: dashed 1px blue; margin-top: 16px;" />
                        
                        <div style="margin-top:13px;">
                            <span style="vertical-align:top;">Existing:</span>
                            <asp:ListBox ID="existing_test_suites_" runat="server" AutoPostBack="True" SelectionMode="Multiple"
                                DataTextField="name" DataValueField="id" OnSelectedIndexChanged="onchange_existing_test_suites"
                                CssClass="default_width" AppendDataBoundItems="true" Rows="7" />
                            <br />
                            <span style="position: relative; top:10px; padding-left:55px;">
                                <asp:LinkButton ID="delete_test_suite_" runat="server" Text="Delete selected test suite(s)"
                                    OnClick="onclick_delete_test_suite" />
                            </span>
                        </div>
                    </td>
                    
                    <!-- section of the table for creating/configuring test packages
                           for the currently selected test suite. -->
                    <td>
                        <h3>II. Test Packages</h3>
                        
                        <p>
                            Use the controls below to create a new test package. By default it will be inserted
                            to the currently selected test suite(if there is one), but you can uncheck the 
                            box if you would not like this to happen.
                        </p>
                        
                        <asp:RequiredFieldValidator ID="test_package_name_required_" runat="server" ControlToValidate="test_package_name_"
                            ErrorMessage="test package name is required.<br />" ForeColor="red" ValidationGroup="test_package_create"
                            Display="dynamic" />
                    
                        <span style="padding-left:10px;">Name:</span>
                        <asp:TextBox ID="test_package_name_" runat="server" TabIndex="3" CssClass="default_width" />
                        <div class="button_array">
                            <asp:CheckBox ID="create_then_insert_test_package" runat="server" 
                                Checked="true" Enabled="true" />
                            <span style="position:relative; left: -3px;">Insert into test suite?</span>
                            <span style="position:relative; left: 10px;">
                                <asp:Button ID="create_package_" runat="server" Text="Create" OnClick="onclick_create_test_package"
                                    TabIndex="4" CssClass="button" CausesValidation="true" ValidationGroup="test_package_create" />
                            </span>
                        </div>
                        
                        <hr style="color:White; border-top: dashed 1px blue;" />
                        
                        <p style="margin-top:0px; padding-top:0px;">
                         Use the controls below to insert an existing test package into the selected
                         test suite, remove test packages from the selected test suite, 
                         or entirely delete a test package from the system.
                         Note that a test package must be removed from all test suites before the 
                         system will allow it to be deleted.  
                        </p>
                        
                        Existing:
                        <asp:DropDownList ID="existing_test_packages_" AutoPostBack="true" runat="server"
                            DataTextField="name" DataValueField="id" CssClass="default_width" 
                            OnSelectedIndexChanged="onchange_existing_test_packages" />
                        <asp:Button ID="insert_test_package_" runat="server" Text="Insert" CssClass="button"
                            TabIndex="5" OnClick="onclick_insert_test_package" />
                        
                        <br />
                        
                        <span style="position:relative; left: 55px; top:6px;">
                            <asp:LinkButton ID="delete_test_package_" runat="server" 
                                    Text="Delete existing test package" OnClick="onclick_delete_test_package" />    
                        </span>
                        <br />
                        <span style="padding-left:53px; position: relative; top: 15px;">
                            <asp:ListBox ID="current_test_packages_" runat="server" AutoPostBack="True" SelectionMode="Multiple"
                                DataTextField="name" DataValueField="id" CssClass="default_width" 
                                OnSelectedIndexChanged="onchange_current_test_packages" />
                        </span>
                        <br /><br />
                        <span style="position:relative; padding-left: 55px; top:10px;">
                        <asp:LinkButton ID="remove_test_package_" runat="server" 
                            Text="Remove selected test package(s)"
                            Enabled="false" OnClick="onclick_remove_test_package" />
                        </span>
                    </td>
                </tr>
                <tr>
                    <td colspan="2">
                        <h3>III. Unit Tests</h3>
                        <p>
                            Use the controls to: add an existing unit test to the currently 
                            selected package, remove a unit test from a the currently selected 
                            package, or entirely delete a unit test (which will also remove
                            it from any other packages in which it might appear).
                        </p>
        
                        <!-- section of the page for selecting an existing unit test -->
                        Existing:
                        <asp:DropDownList ID="existing_unit_tests_" AutoPostBack="true" runat="server" DataTextField="name"
                            DataValueField="utid" CssClass="larger_width" 
                            OnSelectedIndexChanged="onchange_existing_unit_tests" />
                        <asp:Button ID="insert_unit_test_" runat="server" OnClick="onclick_insert_unit_test"
                                Text="Insert" CssClass="button" />
                            
                        <br />
                        
                        <span style="position:relative; left: 55px; top:6px;">
                            <asp:LinkButton ID="delete_unit_test_" runat="server"
                                Text="Delete existing unit test"
                                OnClick="onclick_delete_unit_test" />
                        </span>
                        <br />
                        
                        <span style="position:relative; left: 55px; top:13px;">
                            <asp:ListBox ID="current_unit_tests_" runat="server" SelectionMode="Multiple"
                                DataTextField="name" DataValueField="id" AutoPostBack="true" EnableViewState="true"
                                OnSelectedIndexChanged="onchange_current_unit_tests"
                                Rows="15" CssClass="larger_width" />
                        </span>
                        <br />
                        
                        <span style="position:relative; left: 55px; top:18px;">
                            <asp:LinkButton ID="remove_unit_test_" runat="server" 
                                Text="Remove selected unit test(s)"
                                OnClick="onclick_remove_unit_test" />
                        </span>
                        <br /><br />
                        
                    </td>
                </tr>
            </table>
        </asp:View>
        
        <asp:View runat="server" ID="create_unit_test_view_">
            
            <!-- wrapper div to make things look nice -->
            <table cellpadding="15" cellspacing="20" border="1" class="view_wrapper">
            <tr>
            <td>
                <!-- input the name and description of the unit test -->
                <table>
                    <tr>
                        <td class="title">
                            Name:
                        </td>
                        <td>
                            <asp:TextBox ID="unit_test_name_" runat="server" Width="300px" /></td>
                        <td>
                            <asp:RequiredFieldValidator ID="unit_test_name_required_" runat="server" ControlToValidate="unit_test_name_"
                                ErrorMessage="name is required" ForeColor="red" ValidationGroup="unit_test_create"
                                Display="dynamic" /></td>
                    </tr>
                    <tr>
                        <td class="title">
                            Description:
                        </td>
                        <td>
                            <asp:TextBox ID="unit_test_description_" runat="server" Width="300px" TextMode="singleline" /></td>
                        <td>
                            (optional)</td>
                    </tr>
                </table>
                <!-- select the log formats to use for the unit test -->
                <h3>
                    Log Formats</h3>
                <p>
                    Using the dropdown control below, please select the <a href="logformats.aspx">log formats</a>
                    to use when evaluating this unit test. If you need more than one more <a href="logformats.aspx">
                        log format</a>, then click the <b>I need more log formats</b> link below.</p>
                <!-- Table for selecting log format. A better solution would be to use a placeholder control
               and make each of its children a user-defined log format control. This way, the number
               of child control in the placeholder will represent the number of log messages. It
               will make this webpage a LOT easier to develop and maintain. -->
                <asp:Table runat="server" ID="log_formats_">
                    <asp:TableHeaderRow>
                        <asp:TableHeaderCell>Prefix</asp:TableHeaderCell>
                        <asp:TableHeaderCell>Log Format</asp:TableHeaderCell>
                        <asp:TableHeaderCell>Relation</asp:TableHeaderCell>
                    </asp:TableHeaderRow>
                </asp:Table>
                <p>
                    <asp:LinkButton runat="server" ID="more_log_formats_" Text="I need more log formats"
                        OnClick="onclick_more_log_formats" /></p>
                <!-- required evaluation for the unit test -->
                <h3>
                    Evaluation</h3>
                <p>
                    Use metrics, <i>i.e.</i>, the variables enclosed in brackets { }, identifed in the
                    <a href="logformats.aspx">log formats</a> above to create an evaluation function
                    for the unit test in the text box below. If you have multiple <a href="logformats.aspx">
                        log formats</a>, please use the appropriate <a href="logformats.aspx">log format</a>
                    prefix when creating the evaluation function.</p>
                <table width="100%">
                    <tr>
                        <td>
                        </td>
                        <td>
                            <asp:RequiredFieldValidator ID="Requiredfieldvalidator1" runat="server" ControlToValidate="unit_test_eval_"
                                ErrorMessage="evaluation is required" ForeColor="red" ValidationGroup="unit_test_create"
                                Display="dynamic" /></td>
                    </tr>
                    <tr>
                        <td style="width: 50px">
                            result =
                        </td>
                        <td>
                            <asp:TextBox ID="unit_test_eval_" runat="server" Width="100%" /></td>
                    </tr>
                </table>
                <p>
                    Warn when&nbsp;&nbsp;&nbsp; &nbsp;result&nbsp;&nbsp;&nbsp;
                    <asp:DropDownList ID="UT_warn_comp" runat="server">
                        <asp:ListItem Value="less">&lt;</asp:ListItem>
                        <asp:ListItem Value="greater">&gt;</asp:ListItem>
                        <asp:ListItem Value="less_equal">&lt;=</asp:ListItem>
                        <asp:ListItem Value="greater_equal">&gt;=</asp:ListItem>
                        <asp:ListItem Value="equal">==</asp:ListItem>
                        <asp:ListItem Value="not_equal">!=</asp:ListItem>
                    </asp:DropDownList>
                    <asp:TextBox ID="unit_test_warn_" runat="server" />
                    (optional)
                </p>
                <p>
                    Fail when&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;result&nbsp;&nbsp;&nbsp;
                    <asp:DropDownList ID="UT_fail_comp" runat="server">
                        <asp:ListItem Value="less">&lt;</asp:ListItem>
                        <asp:ListItem Value="greater">&gt;</asp:ListItem>
                        <asp:ListItem Value="less_equal">&lt;=</asp:ListItem>
                        <asp:ListItem Value="greater_equal">&gt;=</asp:ListItem>
                        <asp:ListItem Value="equal">==</asp:ListItem>
                        <asp:ListItem Value="not_equal">!=</asp:ListItem>
                    </asp:DropDownList>
                    <asp:TextBox ID="unit_test_fail_" runat="server" />
                    (optional)
                </p>
                <p>
                    <!-- Note that the grouping information is hidden for now -->
                    <asp:Label ID="temp_label" runat="server" Text="Group By" Visible="false"></asp:Label>
                    <asp:DropDownList ID="DropDownList2" runat="server" Visible="false">
                        <asp:ListItem>test_number</asp:ListItem>
                    </asp:DropDownList>
                </p>
                <!-- select how to aggregrate multiple results -->
                <h3>
                    Aggregration</h3>
                <p>
                    If there are multiple log messages that match your format, this will create multiple
                    results. If this situation occurs, how should we aggregrate the multiple results?</p>
                <!-- Note that there is some server-side processing of these values
                  to ensure that no one can pass commands into mySQL -->
                <asp:DropDownList ID="aggr_function_" runat="server">
                    <asp:ListItem Text="Sum" Value="SUM" />
                    <asp:ListItem Text="Average" Value="AVG" />
                    <asp:ListItem Text="Max" Value="MAX" />
                    <asp:ListItem Text="Min" Value="MIN" />
                    <asp:ListItem Text="Count" Value="COUNT" />
                    <asp:ListItem Text="Count Distinct" Value="COUNT DISTINCT" />
                </asp:DropDownList>
                <!-- button for submitting the new unit test -->
                <p>
                    <asp:Button ID="create_unit_test_" runat="server" Text="Create" OnClick="onclick_create_unit_test"
                        CssClass="button" CausesValidation="true" ValidationGroup="unit_test_create" />
                </p>
            </td>
            </tr>
            </table>
        </asp:View>
    </asp:MultiView>
</asp:Content>
