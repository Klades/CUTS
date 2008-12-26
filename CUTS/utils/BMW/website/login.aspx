<%@ page language="C#" masterpagefile="~/BMW.master" autoeventwireup="true" codefile="login.aspx.cs"
  inherits="CUTS.BMW.Page.Login" %>

<asp:content id="Content1" contentplaceholderid="MainContent" runat="Server">
  <h2>Login Page</h2>
  <asp:login id="login_" runat="server" membershipprovider="BMW"
             visiblewhenloggedin="false">
    <layouttemplate>
      <table border="0" cellpadding="1" cellspacing="0" style="border-collapse: collapse;">
        <tr>
          <td>
            <table border="0" cellpadding="0">
              <tr>
                <td align="right">
                  <asp:label id="UserNameLabel" runat="server"
                             associatedcontrolid="UserName">Username: </asp:label>
                </td>
                <td><asp:textbox id="UserName" runat="server"></asp:textbox></td>
                <td><asp:requiredfieldvalidator id="UserNameRequired" runat="server"
                                                controltovalidate="UserName"
                                                errormessage="Username is required"
                                                validationgroup="Login">Username is required</asp:requiredfieldvalidator>
                </td>
              </tr>
              <tr>
                <td align="right">
                  <asp:label id="PasswordLabel" runat="server"
                             associatedcontrolid="Password">Password: </asp:label>
                </td>
                <td><asp:textbox id="Password" runat="server" textmode="Password"></asp:textbox></td>
                <td><asp:requiredfieldvalidator id="PasswordRequired" runat="server" controltovalidate="Password"
                                                errormessage="Password is required." tooltip="Password is required"
                                                validationgroup="Login">Password is required</asp:requiredfieldvalidator>
                </td>
              </tr>
              <tr>
                <td align="center" colspan="2" style="color: Red;">
                  <asp:literal id="FailureText" runat="server" enableviewstate="False"></asp:literal>
                </td>
              </tr>
              <tr>
                <td align="right" colspan="2">
                  <asp:button id="LoginButton" runat="server" commandname="Login"
                              text="Log In" validationgroup="Login" />
                </td>
              </tr>
            </table>
          </td>
        </tr>
      </table>
    </layouttemplate>
  </asp:login>
</asp:content>
