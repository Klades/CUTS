<?php
// Master page variables
$path_to_root  = "";
$page_subtitle = "Quick Start";

// -- $page_content placeholder
ob_start (); ?>

<h2>Quick Start - Introduction</h2>

<p>Before beginning this tutorial, you should already be familiar with the 
following technologies:</p>

<ul>
  <li><a href="http://www.dre.vanderbilt.edu/CIAO">Component Integrated ACE 
      ORB (CIAO)</a></li>
  <li><a href="http://www.dre.vanderbilt.edu/cosmic">Component Synthesis with 
      Model Integrated Computing (CoSMIC)</a></li>
  <li><a href="http://www.dre.vanderbilt.edu/CIAO">Deployment And Configuration 
      Engine (DAnCE)</a></li>
</ul>

<p>During this quick start tutorial, you will learn how to do the following
with CUTS:</p>

<ul>
  <li><a href="#behavior">Add behavior and workload to components</a></li>
  <li><a href="#prepare">Prepare model for CUTS emulation</a></li>
  <li><a href="#generate">Generate source code for components</a></li>
  <li><a href="#emulation">Run a CUTS emulation</a></li>
  <li><a href="#results">View performance results using the Benchmark Manager Web 
      Utility (optional)</a></li>
</ul>

<p>This quick start tutorial uses the stock quoter example provided with the standard
<a href="http://www.dre.vanderbilt.edu/CIAO" target="_blank">Component Integrated
ACE ORB (CIAO)</a> distribution. It is located in
<tt>$(CIAO_ROOT)/docs/tutorials/Quoter/Simple/Model</tt>.</p>

<hr />

<h3 style="text-decoration:underline">
  <a name="behavior"></a>Adding Behavior and Workload to Components</h3>

<p>Adding behavior and workload to a PICML model is done using two domain specific
modeling langauges (DSMLs) named the <i>Component Behavior Modeling Language
(CBML)</i> and the <i>Workload Modeling Language (WML)</i>, respectively. Both DSMLs
have been integrated into PICML so users can reference the structural model
of their systems when modeling the system's behavior and workload. Before we begin
adding behavior and workload to the stock quoter example, we first need the
following file into GME:</p>

<code>
  $(CIAO_ROOT)/docs/tutorials/Quoter/Simple/Model/Quoter.xme
</code>

<p>Right now, behavior and workload modeling is supported at the component
level. In the stock quoter example, we will be adding behavior to both the
<tt>StockBroker</tt> and <tt>StockDistrubutor</tt> components.

<h4>StockBroker behavior</h4>

<p>The <tt>StockBroker</tt> component has the option of manully requesting
stock information or automatically receiving periodic updates from the
<tt>StockDistributor</tt> component. We are only going to model behavior
for periodically receiving the update information in this tutorial. To
insert the necessary behavior, open the <tt>StockBroker</tt> component
located at <tt>InterfaceDefinitions/Broker/Stock/StockBroker</tt> and select
the <tt>Behavior</tt> aspsect. Then, update the model so that is resembles
the one illustrated in Figure 1.</p>

<div style="text-align:center">
  <a href="private/images/stockbroker-behavior.jpg">
    <img src="private/images/stockbroker-behavior.jpg" clear="all" width="640px" 
         border="0" /></a>
  <div><b>Figure 1. Behavior of the StockBroker component.</b></div>
</div>

<p>The current model of the <tt>StockBroker</tt> contains behavior, but no
workload. To add workload to the model, we need to parameterize the generic
actions with actual workload parameters. We accomplish in a 4 steps:</p>

<ol>
  <li>Import a <i>workload generator (worker)</i> into the current project. For
      this particular example, we imported the workload located at
      <code>$(CUTS_ROOT)/cuts/workers/CPU/CUTS_CPU_Worker.xme</code>.</li>
  <li>Add a worker to the component's behavior model, which is a GME reference.</li>
  <li>Replace the generic action (<i>e.g.</i>, process_notification) with an GME
      instance of an action (<i>i.e.</i>, a workload) from the referenced
      worker.</li>
  <li>Set the name of the workload to the name of its target worker.</li>
</ol>

<p>Figure 2 illustrates the final behavior and workload model for the
<tt>StockBroker</tt>.</p>

<div style="text-align:center">
  <a href="private/images/stockbroker-workload.jpg">
    <img src="private/images/stockbroker-workload.jpg" clear="all" 
         width="640px" border="0" /></a>
  <div><b>Figure 2. Behavior and workload of the StockBroker component.</b></div>
</div>

<h4>StockDistributor behavior</h4>

<p>The <tt>StockDistributor</tt> component's behavior is modeled similar to the
behavior of the <tt>StockBroker</tt> component. The <tt>StockDistributor</tt>
component, however, needs to send periodic updates to the <tt>StockBroker</tt>.
We, therefore, need to model this periodic behavior such that the 
<tt>StockDistributor</tt> publishes information at the periodicity specified via 
the <tt>rate</tt> attribute at deployment and configuration time.</p>

<div style="text-align:center">
  <a href="private/images/stockdistributor-workload.jpg">
    <img src="private/images/stockdistributor-workload.jpg" clear="all" 
         width="640px" border="0" /></a>
  <div><b>Figure 3. Behavior and workload of the StockDistributor component.</b></div>
</div>

<p>Figure 3 shows the behavior for the <tt>StockDistributor</tt>, which is modeled
as follows:</p>

<ol>
  <li>Open the <tt>StockDistributor</tt> component and select the <tt>Behavior</tt>
      aspect.</li>
  <li>Insert a <tt>PeriodicEvent</tt> element into the model and set its 
      <tt>Period</tt> attribute to <tt>rate_</tt>. Please note the trailing 
      underscore.</li>
  <li>Create the behavior sequence as shown in Figure 3 for the 
      <tt>send_notification</tt> behavior. Make sure the names of the elemnts
      match the names in Figure 3.</li>.
</ol>

<div class="back-to-top">[<a href="#top">Back to Top</a>]</div>

<h3 style="text-decoration:underline">
  <a name="prepare"></a>Preparing model for CUTS emulation</h3>

<p>Now that we have modeled the behavior and workload of the components
in the stock quoter example, we are ready to prepare the model for CUTS
emulation. Run the CUTS interperter (i.e., the interpreter with the scissor
icon), and select <b>Generate component proxy models</b> under the <b>Model
Generation</b> category as shown in Figure 4.</p>

<div style="text-align:center">
  <a href="private/images/generate-proxies.jpg">
    <img src="private/images/generate-proxies.jpg" clear="all" 
         width="640px" border="0" /></a>
  <div class="figure-title">Figure 4. Running CUTS interpreter to generate 
  component proxy models.</div>
</div>

<p>This is generate the necessary model elements for proxying the emulated,
or real, components in the stock quoter example. Re-run the CUTS interpreter
and this time select <b>Generate assembly proxy models</b> in the <b>Model
Generation</b> category as shown in Figure 5.</p>

<div style="text-align:center">
  <a href="private/images/generate-assemblies.jpg">
    <img src="private/images/generate-assemblies.jpg" clear="all" 
         width="640" border="0" /></a>
  <div class="figure-title">Figure 5. Running CUTS interpreter to generate 
  component proxy assemblies and deployments.</div>
</div>

<p>This step creates a replica of the stock quoter assembly and its
deployment(s) using the component proxies. It will also configure the
proxies so they will load the correct implementation at deployment and 
configuration time. The final step is to insert the 
<tt>Benchmark_Data_Collector</tt> component into the assembly model and
configure its data collection interval and services to load for processing
the collected data.</p>

<div style="text-align:center">
  <a href="private/images/deploy-bdc.jpg">
    <img src="private/images/deploy-bdc.jpg" clear="all" width="720" border="0" /></a>
  <div class="figure-title">Figure 6. Deploying the Benchmark Data 
  Collector with the stock quoter example.</div>
</div>

<p>Figure 6 shows the end product for including and configuring the 
<tt>Benchmark_Data_Collector</tt> for the stock quoter example, which 
is done using the following steps:</p>

<ol>
  <li>Import the <tt>Benchmark_Data_Collector</tt> model elements located in
      <code>$(CUTS_ROOT)/cuts/BDC/BDC.xme</code> into the stock quoter 
      example.</li>
  <li>Insert an instance of the <tt>Benchmark_Data_Collector</tt>component into 
      the stock quoter's proxy assembly diagram.</li>
  <li>Set the <b>timeout</b> attribute value to <u>30</u> seconds and the 
      <b>services</b> attribute value to <u>"IO CUTS_BDC_IO --verbose;"</u>,
      but do not include the quotation marks.</li>
      
  <li>Add the <tt>Benchmark_Data_Collector</tt> instance to the deployment
      diagram for the component proxies (<i>i.e.</i>, the deployment plans
      located in CoWorkEr_DeploymentPlans).
</ol>

<p>In addition to adding the <tt>Benchmark_Data_Collector</tt> to the stock quoter
example, we also set the rate attribute for the <tt>StockDistributor</tt> to 
10000 msec (<i>i.e.</i>, 10 seconds).

<div class="back-to-top">[<a href="#top">Back to Top</a>]</div>

<h3 style="text-decoration:underline">
  <a name="generate"></a>Generating Source Code for Components</h3>

<p>Once the behavior and workload is modeled, and the CUTS-specific model elements
are added to the stock quoter model, the next step is to generate source
code from the model. This will allow use to run an emulation of the stock
quoter system on its target architecture. To generate source code from the 
model, run the CUTS interpreter again; however, this time execute the following
steps (shown in Figure 7):

<ol>
  <li>Select <b>Generate component implementation</b></li>
  <li>Enter the target <b>output directory</b></li>
  <li>Select <b>Component Integrated ACE ORB</b> in the listbox<li>
  <li>Click the <b>OK</b> button.</li>
</ol>

<div style="text-align:center">
  <a href="private/images/generate-source.jpg">
    <img src="private/images/generate-source.jpg" clear="all" width="640" 
         border="0" /></a>
  <div class="figure-title">Figure 7. Generating source code from the stock quoter
  model.</div>
</div>

<p>Once the CUTS interpreter finishes generating the source code, you must
compile it. There will be a <tt>MyQuoter_CUTS.mwc</tt> file (its name may be
different) located in the output directory. This is a 
<a href="http://www.ociweb.com/products/mpc">Makefile, Project and Workspace
Creator (MPC)</a> workspace file that contains all the necessary information to 
sucessfully compile the generated source code. Use MyQuoter_CUTS.mwc to generate 
the appropriate workspace and then compile it.</p>

<div class="back-to-top">[<a href="#top">Back to Top</a>]</div>

<h3 style="text-decoration:underline">
  <a name="emulation"></a>Running a CUTS Emulation</h3>

<p>One of the design goals of CUTS is to reuse the same infrastruture used in the
target application. This means that when deploying a CUTS solution, it uses
the same deployment tools used in the target application. The stock quoter example
uses the <a href="http://www.dre.vanderbilt.edu/CIAO">Deployment And 
Configuration Engine (DAnCE)</a> included with the
<a href="http://www.dre.vanderbilt.edu/CIAO">CIAO</a> standard distribution. To
deploy the CUTS stock quoter example, do the following:

<ol>
  <li>Generate the flat deployment plan descriptors from the stock quoter 
      model. You can find instructions on 
      <a href="http://www.dre.vanderbilt.edu/~schmidt/DOC_ROOT/CIAO/docs/tutorials/COSMIC">
      generating the flat deployment plans</a> in the original stock quoter tutorial 
      included with CoSMIC.</li>
  <li>Use DAnCE to deploy the <tt>Plan_CoWorkEr.cdp</tt>. The original stock
      quoter tutorial has instructions on 
      <a href="http://www.dre.vanderbilt.edu/~schmidt/DOC_ROOT/CIAO/docs/tutorials/Quoter/Simple/04.html">
      how to deploying the solution.</a></li>
</ol>

When the CUTS version of the stock quoter example is deployed, the Controller 
node will perdiodically collect and display application-level performance 
metrics on its console.

<div class="back-to-top">[<a href="#top">Back to Top</a>]</div>

<h3 style="text-decoration:underline">
  <a name="results"></a>Viewing Results Using the Benchmark 
Manager Web Utility (optional)</h3>

<p>Coming soon...</p>

<div class="back-to-top">[<a href="#top">Back to Top</a>]</div>

<!-- $page_content placeholder -->
<? $page_content = ob_get_clean (); ?>


<!-- master page -->
<? require_once ('cuts.master.php'); ?>

