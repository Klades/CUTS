<%@ Page language="c#" codefile="analysis.aspx.cs" inherits="CUTS.Web.Page.Analysis" masterpagefile="~/BMW.master" %>
<%@ register tagprefix="cuts" namespace="CUTS.Web.UI.UnitTesting" assembly="CUTS.Web" %>

<asp:content runat="server" id="content_" contentplaceholderid="MainContent">
  <!--
     menu at the top to the page
     -->
  <asp:menu runat="server" id="viewmenu_" orientation="horizontal" onmenuitemclick="handle_onmenuitemclick">
    <staticmenuitemstyle backcolor="darkgray" forecolor="black" verticalpadding="5px"
                         horizontalpadding="10px" font-bold="true" />

    <staticselectedstyle backcolor="#9999FF" forecolor="black" />
    <statichoverstyle backcolor="#CCCCFF" forecolor="black" />

    <items>
      <asp:menuitem text="Unit Testing" value="0" />
    </items>
  </asp:menu>

  <!--
    spacer between the menu and multiview
    -->
  <div style="background-color: #9999FF; height: 4px; margin-bottom:5px">&nbsp;</div>

  <asp:multiview runat="server" id="analysis_" activeviewindex="0"
                 onactiveviewchanged="handle_onactiveviewchanged">

    <asp:view runat="server" id="unit_testing_">
      <div>
        <span class="title">Test Suite: </span>
        <asp:dropdownlist id="test_suite_list_" runat="server"
                          enableviewstate="true" />

        <asp:button id="load_" runat="server"
                    text="Load..." cssclass="button"
                    onclick="handle_load_test_suite" />
      </div>

      <cuts:unittestsuite runat="server" id="test_suite_"
                          enableviewstate="true"
                          onevaluateunittest="handle_evaluate_unit_test" />
    </asp:view>
  </asp:multiview>
</asp:content>
