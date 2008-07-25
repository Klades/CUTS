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
        ID="Log_Format_List_1"
        DataTextField="lfmt"
        DataValueField="lfid"
        runat="server"
        AutoPostBack="true"
        OnSelectedIndexChanged="OnChange_Log_Format_List_1"></asp:DropDownList>
        
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    <asp:Label 
        ID="Log_Format_1_Prefix"
        Text=""
        runat="server"></asp:Label>&nbsp;
</p>
    <asp:DropDownList 
        ID="Log_Format_List_2"
        DataTextField="lfmt"
        DataValueField="lfid"
        OnSelectedIndexChanged="OnChange_Log_Format_List_2"
        AutoPostBack="true"
        runat="server"></asp:DropDownList>
        
    <asp:Literal ID="Spacer1" runat="server">&nbsp;&nbsp;&nbsp;&nbsp;</asp:Literal>
    <asp:Label 
        ID="Log_Format_2_Prefix"
        Text=""
        runat="server"></asp:Label>
    <asp:Literal ID="Spacer2" runat="server"><br /><br /></asp:Literal>
    &nbsp;&nbsp;&nbsp;&nbsp;
    <asp:Button 
        ID="btn_more_lfs"
        BackColor="white" 
        runat="server" 
        OnClick="OnClick_Toggle_Second_Log_Format_Visibility" />
    <br />
    <asp:Literal
        Text="<h3>Specify the relation</h3>"
        runat="server"
        id="relation_head"
        ></asp:Literal>
    <asp:DropDownList
        ID="Relation_Variable_1"
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
        ID="Relation_Variable_2"
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
    
    <!-- Note that the grouping information is hidden for now -->
        <asp:Label ID="temp_label" runat="server" Text="Group By" Visible="false"></asp:Label>
        <asp:DropDownList ID="DropDownList2" runat="server" Visible="false">
            <asp:ListItem>test_number</asp:ListItem>
        </asp:DropDownList>
    </p>
    <p>
    </p>
    <h3>Aggregration</h3>
    If there is more that one result of your evaluation, how would you like to aggregrate these results?
    <!-- Note that there is some server-side processing of these values
          to ensure that no one can pass commands into mySQL -->
    <asp:DropDownList ID="Aggregrate_Funtion" runat="server">
        <asp:ListItem Text="Please select one . . ." Value="-1" />
        <asp:ListItem Text="Sum" Value="SUM" />
        <asp:ListItem Text="Average" Value="AVG" />
        <asp:ListItem Text="Max" Value="MAX" />
        <asp:ListItem Text="Min" Value="MIN" />
        <asp:ListItem Text="Count" Value="COUNT" />
        <asp:ListItem Text="Count Distinct" Value="COUNT DISTINCT" />    
    </asp:DropDownList>
    <p>
        <asp:Button ID="btn_Submit" runat="server" Text="Submit" onclick="OnClick_btn_Submit" />
    </p>
    <p>
        &nbsp;</p>



</asp:Content>

