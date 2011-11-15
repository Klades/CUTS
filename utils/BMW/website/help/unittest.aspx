<%@ page language="C#" codefile="unittest.aspx.cs" autoeventwireup="false"
         inherits="CUTS.Help.UnitTest" masterpagefile="~/help/help.master" %>

<asp:content contentplaceholderid="HelpTitle"  runat="server">
Unit Testing with CUTS
</asp:content>

<asp:content contentplaceholderid="HelpContent" runat="server">
  <p>Before reading this, let us first explain the terminology we use in the BMW, which
  is analogous to the language used within continuous integration system. <b>Test suites</b>
  and <b>test packages</b> are levels of abstraction for grouping. The smallest unit of
  abstraction is named <b>unit test</b>, which specifies how to evaluate a single aspect
  of the system and is based on analyzing metrics extracted from multiple log formats.
  One test suite can have infinite number of test packages, and one test package
  can have infinite number of unit tests. Figure 1 illustrates our concept of unit
  testing.</p>

  <div>
  <asp:image id="Image1" runat="server"
             imageurl="~/images/Unit_Testing_Concept.png"
             alternatetext="Unit Testing Concept Diagram" />
  <br clear="all" />
  <b>Figure 1. Conceptual diagram of unit testing in CUTS</b>
  </div>

  <p>The last of the terminology that we have been using would be <i>unit test</i> versus
  <i>metrics</i>. The main difference is unit tests are <b>pass/warn/fail</b>, and based on
  an evaluation function specified when the unit test was created. Metrics use the same evaluation,
  function, however, they simply give the result of the evaluation, <i>i.e.</i>, the scalar value
  resulting from the evaluation function.</p>

  <p>To illustrate the concept of unit testing, a quick example would be a test suite for
  networking which contains test packages for testing incoming connections, outgoing connections,
  and QOS of connections. Each package then contained multiple unit tests that related specifically
  to their area of interest.</p>
</asp:content>
