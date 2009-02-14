<%@ Page language="c#" codefile="analysis.aspx.cs" inherits="CUTS.Web.Page.Analysis" masterpagefile="~/BMW.master" %>
<%@ register tagprefix="cuts" namespace="CUTS.Web.UI.UnitTest" assembly="CUTS.Web" %>
<%@ register tagprefix="cuts" namespace="WebChart" assembly="WebChart" %>

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
                          onevaluateunittest="handle_evaluate_unit_test"
                          onchartunittest="handle_chart_unit_test" />

      <cuts:chartcontrol runat="server" id="chart_"
                         chartpadding="30" padding="40" borderstyle="ridge"
                         height="400px" width="800px" ycustomend="0" yvaluesinterval="0"
                         ycustomstart="0" bordercolor="Silver" showxvalues="false"
                         visible="false"
                         enableviewstate="true">
        <yaxisfont stringformat="Far,Near,Character,LineLimit" />
        <charttitle forecolor="black" stringformat="Center,Near,Character,LineLimit" font="Tahoma, 10pt, style=Bold" />
        <legend font="Microsoft Sans Serif, 8pt" position="right" />
        <background type="Solid" angle="90" endpoint="100, 400" color="white" hatchstyle="Horizontal"/>
        <ytitle stringformat="Center,Near,Character,DirectionVertical"
                font="Tahoma, 8pt, style=Bold" />
        <xtitle stringformat="Center,Far,Character,LineLimit"
                font="Tahoma, 8pt, style=Bold"
                text="Event Number"  />

        <border dashstyle="dashdot" color="black" />
        <plotbackground forecolor="white" />
      </cuts:chartcontrol>
    </asp:view>
  </asp:multiview>
</asp:content>
