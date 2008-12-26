<%@ page language="C#" masterpagefile="~/BMW.master" autoeventwireup="true"
         codefile="createuser.aspx.cs" inherits="CUTS.BMW.Page.Admin.CreateUser" %>

<asp:content id="content" contentplaceholderid="MainContent" runat="server">
  <p>Use the form below to create a new user account.</p>

  <table border="0">
    <tr>
      <td class="form-title">
        <asp:label id="username_label_" runat="server"
                   associatedcontrolid="username_">Username: </asp:label></td>
      <td><asp:textbox id="username_" runat="server"></asp:textbox></td>
      <td><asp:requiredfieldvalidator id="username_required_" runat="server"
                                      controltovalidate="username_"
                                      errormessage="required"
                                      tooltip="Username is required"
                                      validationgroup="createuser_"></asp:requiredfieldvalidator></td>
    </tr>

    <tr>
      <td class="form-title">
        <asp:label id="password_label_" runat="server"
                   associatedcontrolid="password_">Password: </asp:label></td>
      <td><asp:textbox id="password_" runat="server" textmode="Password"></asp:textbox></td>
      <td><asp:requiredfieldvalidator id="password_required_" runat="server"
                                      controltovalidate="password_"
                                      errormessage="required"
                                      tooltip="Password is required"
                                      validationgroup="createuser_"></asp:requiredfieldvalidator></td>
    </tr>

    <tr>
      <td class="form-title">
        <asp:label id="confirm_password_label_" runat="server"
                   associatedcontrolid="confirm_password_">Confirm password: </asp:label></td>
      <td><asp:textbox id="confirm_password_" runat="server" textmode="Password"></asp:textbox></td>
      <td>
        <asp:requiredfieldvalidator id="confirm_password_required_" runat="server"
                                    controltovalidate="confirm_password_"
                                    errormessage="required"
                                    tooltip="Password confirmation is required"
                                    validationgroup="createuser_"></asp:requiredfieldvalidator>
        <asp:comparevalidator id="password_compare_" runat="server"
                              controltocompare="password_"
                              controltovalidate="confirm_password_"
                              display="dynamic"
                              errormessage="Passwords do not match"
                              validationgroup="createuser_"></asp:comparevalidator></td>
    </tr>

    <tr>
      <td class="form-title">
        <asp:label id="email_label_" runat="server"
                   associatedcontrolid="email_">E-mail address: </asp:label></td>
      <td><asp:textbox id="email_" runat="server"></asp:textbox></td>
      <td>
        <asp:requiredfieldvalidator id="email_required_" runat="server"
                                    controltovalidate="email_"
                                    errormessage="required"
                                    tooltip="E-mail address is required"
                                    validationgroup="createuser_"></asp:requiredfieldvalidator></td>
    </tr>

    <tr>
      <td align="right" colspan="2">
        <asp:button id="submit_" runat="server"
                    text="Create User"
                    validationgroup="createuser_"
                    commandname="Submit"
                    oncommand="handle_button_oncommand" />

      </td>
    </tr>
    <tr>
      <td align="center" colspan="2" style="color: Red;">
        <asp:literal id="error_message_" runat="server" enableviewstate="False"></asp:literal>
      </td>
    </tr>
  </table>
</asp:content>
