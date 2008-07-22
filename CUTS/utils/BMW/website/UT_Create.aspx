<%@ Page 
    Language="C#" 
    MasterPageFile="~/BMW.master" 
    EnableViewState="true" 
    AutoEventWireup="true" 
    CodeFile="UT_Create.aspx.cs" 
    Inherits="UT_Create" 
    Title="Unit Test Create" %>

<%@ Reference 
    Control="~/controls/AddLogFormat.ascx" %>

<asp:Content ID="Content1" ContentPlaceHolderID="MainContent" Runat="Server">
    <h2>
        Create New Unit Test</h2>
    <p>
        Name
        <asp:TextBox ID="UT_name" runat="server" Width="284px"></asp:TextBox>
&nbsp;&nbsp; Desc
        <asp:TextBox ID="UT_desc" runat="server" Height="44px" Width="261px" TextMode="MultiLine" Wrap="true"></asp:TextBox>
    </p>
    <h3>
        Use these Log Formats</h3>
<p>        
    <asp:DropDownList 
        ID="ddl_Log_Formats_1"
        DataTextField="lfmt"
        DataValueField="lfid"
        runat="server"
        AutoPostBack="true"
        OnSelectedIndexChanged="OnChange_ddl_Log_Formats_1"></asp:DropDownList>
        
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    <asp:Label 
        ID="lbl_Log_Formats_1"
        Text=""
        runat="server"></asp:Label>
    
    
    <asp:panel 
        ID="panel_Log_Format_variables_1"
        EnableViewState="true"
        runat="server"></asp:panel>
</p>
    <asp:DropDownList 
        ID="ddl_Log_Formats_2"
        DataTextField="lfmt"
        DataValueField="lfid"
        OnSelectedIndexChanged="OnChange_ddl_Log_Formats_2"
        AutoPostBack="true"
        runat="server"></asp:DropDownList>
        
        &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    <asp:Label 
        ID="lbl_Log_Formats_2"
        Text=""
        runat="server"></asp:Label>
    <asp:Panel
        ID="panel_Log_Format_variables_2"
        runat="server"></asp:Panel>
  
    
        <asp:Button ID="btn_more_lfs" BackColor="white" runat="server" OnClick="OnClick_more_log_formats" />
    <br />
    <asp:Literal
        Text="<h3>Specify the relation</h3>"
        runat="server"
        id="relation_head"
        ></asp:Literal>
    <asp:DropDownList
        ID="relation1"
        DataTextField="extended_varname"
        DataValueField="variable_id"
        runat="server"
        ></asp:DropDownList>
    <asp:Literal
        Text="&nbsp;&nbsp;==&nbsp;&nbsp;"
        runat="server"
        ID="relation_text"
        ></asp:Literal>
    <asp:DropDownList
        ID="relation2"
        DataTextField="extended_varname"
        DataValueField="variable_id"
        runat="server"
        ></asp:DropDownList>
   
    <h3>
        Perform this Evaluation</h3>
    <p>
        <asp:TextBox ID="UT_eval" runat="server" Width="381px" Height="24px"></asp:TextBox>
    </p>
    <p>
        Warn when&nbsp;&nbsp;&nbsp;
        &nbsp;Result&nbsp;&nbsp;&nbsp;
        <asp:DropDownList ID="UT_warn_comp" runat="server">
            <asp:ListItem Value="less">&lt;</asp:ListItem>
            <asp:ListItem Value="greater">&gt;</asp:ListItem>
            <asp:ListItem Value="less_equal">&lt;=</asp:ListItem>
            <asp:ListItem Value="greater_equal">&gt;=</asp:ListItem>
            <asp:ListItem Value="equal">==</asp:ListItem>
            <asp:ListItem Value="not_equal">!=</asp:ListItem>
        </asp:DropDownList>
&nbsp;
        <asp:TextBox ID="UT_warn" runat="server"></asp:TextBox>
        &nbsp;</p>
    <p>
        Fail when&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
        &nbsp;Result&nbsp;&nbsp;&nbsp;
        <asp:DropDownList ID="UT_fail_comp" runat="server">
            <asp:ListItem Value="less">&lt;</asp:ListItem>
            <asp:ListItem Value="greater">&gt;</asp:ListItem>
            <asp:ListItem Value="less_equal">&lt;=</asp:ListItem>
            <asp:ListItem Value="greater_equal">&gt;=</asp:ListItem>
            <asp:ListItem Value="equal">==</asp:ListItem>
            <asp:ListItem Value="not_equal">!=</asp:ListItem>
        </asp:DropDownList>
&nbsp;
        <asp:TextBox ID="UT_fail" runat="server"></asp:TextBox>
        &nbsp;</p>
    <p>
        Group By :
        <asp:DropDownList ID="DropDownList2" runat="server">
            <asp:ListItem>test_number</asp:ListItem>
        </asp:DropDownList>
    </p>
    <p>
        <asp:Button ID="btn_Submit" runat="server" Text="Submit" onclick="OnClick_btn_Submit" />
    </p>
    <p>
        &nbsp;</p>



</asp:Content>

