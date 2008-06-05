<%@ Page Language="C#" AutoEventWireup="true"  CodeFile="Default.aspx.cs" Inherits="_Default" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Untitled Page</title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        Please enter a expression:
        <br />
        <br />
    <asp:TextBox ID="TextBox1" runat="server" Height="93px" 
             Width="376px"></asp:TextBox>
        <br />
        <br />
        <asp:Button ID="Button1" runat="server" Text="Submit" onclick="Button1_Click" />
        <br />
        <br />
        <asp:Label ID="LabelLog" runat="server" Text=""></asp:Label>
        <br />
        <br />
        <br />
        </div>
    </form>
</body>
</html>
