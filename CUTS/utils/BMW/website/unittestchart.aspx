<%@ page language="C#" masterpagefile="~/BMW.master" autoeventwireup="true" codefile="unittestchart.aspx.cs"
         inherits="CUTS.UnitTestChart" %>
<%@ register tagprefix="cuts" namespace="WebChart" assembly="WebChart" %>

<asp:content id="content_" contentplaceholderid="MainContent" runat="server">
  <cuts:chartcontrol runat="server" id="chart_"
                     chartpadding="30" padding="40" borderstyle="ridge"
                     height="400px" width="800px" ycustomend="0" yvaluesinterval="0"
                     ycustomstart="0" bordercolor="Silver" showxvalues="false">
    <yaxisfont stringformat="Far,Near,Character,LineLimit" />
    <charttitle forecolor="black" stringformat="Center,Near,Character,LineLimit" font="Tahoma, 10pt, style=Bold" />
    <legend font="Microsoft Sans Serif, 8pt" position="right" />
    <background type="Solid" angle="90" endpoint="100, 400" color="white" hatchstyle="Horizontal"/>
    <ytitle stringformat="Center,Near,Character,DirectionVertical"
            text="Average End-to-End Response Time (msec)"
            font="Tahoma, 8pt, style=Bold" />
    <xtitle stringformat="Center,Far,Character,LineLimit"
            font="Tahoma, 8pt, style=Bold"
            text="Event Number"  />

    <border dashstyle="dashdot" color="black" />
    <plotbackground forecolor="white" />
  </cuts:chartcontrol>
</asp:content>
