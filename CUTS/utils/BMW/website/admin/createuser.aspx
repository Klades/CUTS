<%@ Page Language="C#" MasterPageFile="~/BMW.master" AutoEventWireup="true" CodeFile="createuser.aspx.cs" Inherits="admin_createuser" %>

<asp:Content ID="Content1" ContentPlaceHolderID="MainContent" Runat="Server">
  <h2>Create a New User</h2>
  <table border="0">
    <tr>
      <td align="right">
        <asp:Label ID="user_name_label_" runat="server" AssociatedControlID="user_name_">User 
        Name:</asp:Label>
      </td>
      <td>
        <asp:TextBox ID="user_name_" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator ID="user_name_required_" runat="server" 
          ControlToValidate="user_name_" ErrorMessage="User Name is required." 
          ToolTip="User Name is required." ValidationGroup="create_user_group_">*</asp:RequiredFieldValidator>
      </td>
    </tr>
    <tr>
      <td align="right">
        <asp:Label ID="password_label_" runat="server" AssociatedControlID="password_">Password:</asp:Label>
      </td>
      <td>
        <asp:TextBox ID="password_" runat="server" TextMode="Password"></asp:TextBox>
        <asp:RequiredFieldValidator ID="password_required_" runat="server" 
          ControlToValidate="password_" ErrorMessage="Password is required." 
          ToolTip="Password is required." ValidationGroup="create_user_group_">*</asp:RequiredFieldValidator>
      </td>
    </tr>
    <tr>
      <td align="right">
        <asp:Label ID="confirm_password_label_" runat="server" 
          AssociatedControlID="confirm_password_">Confirm Password:</asp:Label>
      </td>
      <td>
        <asp:TextBox ID="confirm_password_" runat="server" TextMode="Password"></asp:TextBox>
        <asp:RequiredFieldValidator ID="confirm_password_required_" runat="server" 
          ControlToValidate="confirm_password_" 
          ErrorMessage="Confirm Password is required." 
          ToolTip="Confirm Password is required." ValidationGroup="create_user_group_">*</asp:RequiredFieldValidator>
      </td>
    </tr>
    <tr>
      <td align="right">
        <asp:Label ID="email_label_" runat="server" AssociatedControlID="email_">E-mail:</asp:Label>
      </td>
      <td>
        <asp:TextBox ID="email_" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator ID="email_required_" runat="server" 
          ControlToValidate="email_" ErrorMessage="E-mail is required." 
          ToolTip="E-mail is required." ValidationGroup="create_user_group_">*</asp:RequiredFieldValidator>
      </td>
    </tr>
    <tr>
      <td align="center" colspan="2">
        <asp:CompareValidator ID="password_compare_" runat="server" 
          ControlToCompare="password_" ControlToValidate="confirm_password_" 
          Display="Dynamic" 
          ErrorMessage="The Password and Confirmation Password must match." 
          ValidationGroup="create_user_group_"></asp:CompareValidator>
      </td>
    </tr>
    <tr>
        <td align="right" colspan="2">
            <asp:Button ID="submit_button_" runat="server" CommandName="submit" Text="Submit" 
                ValidationGroup="create_user_group_" onclick="submit_button__Click" />
        </td>
    </tr>
    <tr>
      <td align="center" colspan="2" style="color:Red;">
        <asp:Literal ID="error_message_" runat="server" EnableViewState="False"></asp:Literal>
      </td>
    </tr>
  </table>
        
</asp:Content>

