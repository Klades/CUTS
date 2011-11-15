<%@ page language="c#" codefile="paths.aspx.cs" autoeventwireup="true" inherits="CUTS.Execution_Paths"
  masterpagefile="~/BMW.master" %>

<asp:content runat="server" id="main_content_" contentplaceholderid="MainContent">
  <h2>
    Execution Paths</h2>
  <table width="100%" border="0">
    <tr valign="top">
      <!-- portion of page for displaying current paths -->
      <td>
        <!-- data grid that displays the paths in the database -->
        <asp:datagrid runat="server" id="paths_"
                      cellpadding="4" cellspacing="0"
                      allowpaging="true" pagesize="5"
                      width="100%" autogeneratecolumns="false"
                      showheader="true" showfooter="false"
                      datakeyfield="path_id">

          <headerstyle cssclass="header" />

          <footerstyle cssclass="footer" />

          <alternatingitemstyle cssclass="alternate-row" />

          <pagerstyle mode="NumericPages" />

          <columns>
            <asp:boundcolumn datafield="path_name" headertext="Name of Execution Path" itemstyle-horizontalalign="Left" />

            <asp:boundcolumn datafield="deadline" headertext="Deadline (msec)" itemstyle-horizontalalign="Center"
              itemstyle-width="150px" />

            <asp:hyperlinkcolumn datanavigateurlfield="path_id" headertext="Edit" datanavigateurlformatstring="Critical_Path.aspx?p={0}"
              text='<img src="images/edit.gif" border="0" alt="edit path elements" />' itemstyle-horizontalalign="center" />

            <asp:templatecolumn itemstyle-horizontalalign="center">
              <headertemplate>
                <asp:checkbox runat="server" id="delete_" oncheckedchanged="toggle_delete_paths"
                              causesvalidation="false" autopostback="true" />
              </headertemplate>
              <itemtemplate>
                <asp:checkbox runat="server" id="delete_" />
              </itemtemplate>
            </asp:templatecolumn>
          </columns>
        </asp:datagrid>

      </td>
      <!-- table form for creating critical paths -->
      <td style="width: 45%">
        <table>
          <tr>
            <td class="title">Name:</td>
            <td><asp:textbox runat="server" id="path_name_" /></td>
            <td>
              <asp:requiredfieldvalidator id="path_name_validator_" runat="server" controltovalidate="path_name_"
                errormessage="Name is required" forecolor="red" validationgroup="createpath" />
            </td>
          </tr>
          <tr>
            <td class="title">Deadline (ms):</td>
            <td><asp:textbox runat="server" id="deadline_" /></td>
            <td>
              <asp:requiredfieldvalidator id="deadline_validator_" runat="server" controltovalidate="deadline_"
                errormessage="Deadline is required" forecolor="red" validationgroup="createpath"
                display="dynamic" />
              <asp:rangevalidator id="deadline_value_validator_" runat="server" minimumvalue="1"
                maximumvalue="4294967296" controltovalidate="deadline_" validationgroup="createpath"
                errormessage="Invalid deadline" display="dynamic" />
            </td>
          </tr>
          <tr>
            <td colspan="2" align="right">
              <asp:button runat="server" text="Create Path" id="create_path_" onclick="CreateCritcalPath"
                validationgroup="createpath" />
            </td>
          </tr>
        </table>
      </td>
    </tr>
  </table>

  <asp:linkbutton runat="server" text="Delete Selected"
                  onclick="delete_selected_execution_paths" />

  <h2>Execution Path Members</h2>
  <asp:label runat="server" id="notice_" />

  <table>
    <tr>
      <td class="title">
        Next Index:</td>
      <td>
        <asp:textbox id="order_" runat="server" width="75" maxlength="11"></asp:textbox></td>
    </tr>
    <tr>
      <td class="title">
        Instance:</td>
      <td>
        <asp:dropdownlist id="instance_" runat="server" datatextfield="component_name" datavaluefield="instid"
          onselectedindexchanged="instance_OnSelectedIndexChanged" autopostback="true" width="100%" /></td>
    </tr>
    <tr>
      <td class="title">
        Input Port:</td>
      <td>
        <asp:dropdownlist id="src_" runat="server" datavaluefield="pid" datatextfield="portname"
          width="200" />
        <span class="title">Output Port: </span>
        <asp:dropdownlist id="dst_" runat="server" datavaluefield="pid" datatextfield="portname"
          width="200" />
      </td>
    </tr>
    <tr>
      <td colspan="2">
        <asp:button id="button_PathElementInsert" onclick="PathElement_Insert" runat="server"
          text="Insert Instance" />
      </td>
    </tr>
  </table>
  <asp:datagrid id="path_elements_" runat="server" datakeyfield="path_order"
    pagesize="15" allowpaging="true" autogeneratecolumns="false" showfooter="false"
    borderstyle="solid" cellpadding="4" cellspacing="0" onitemcreated="path_elements_OnItemCreated">
    <headerstyle cssclass="header" />
    <footerstyle cssclass="footer" />
    <alternatingitemstyle cssclass="alternate-row" />
    <pagerstyle mode="NumericPages" />
    <columns>
      <asp:boundcolumn datafield="path_order" headertext="Index" itemstyle-horizontalalign="Center" />
      <asp:boundcolumn datafield="component_name" headertext="Instance Name" />
      <asp:boundcolumn datafield="inport_name" headertext="Source Port" />
      <asp:boundcolumn datafield="outport_name" headertext="Destination Port" />
      <asp:templatecolumn itemstyle-horizontalalign="center">
        <headertemplate>
          <asp:checkbox runat="server" id="delete_" oncheckedchanged="toggle_delete_path_elements" causesvalidation="false"
            autopostback="true" />
        </headertemplate>
        <itemtemplate>
          <asp:checkbox runat="server" id="delete_" />
        </itemtemplate>
      </asp:templatecolumn>
    </columns>
  </asp:datagrid>
  <p>
    <asp:linkbutton id="button_CommitPathElements" onclick="PathElement_Commit" runat="server"
      text="Commit Changes" />
    &middot;
    <!-- controls at the bottom of page used for batch processing -->
    <asp:linkbutton runat="server" id="button_DeletePathElements" onclick="PathElement_Delete"
      text="Delete Selected" causesvalidation="false" />
  </p>
</asp:content>
