<?php 
// Master page variables
$page_subtitle = "Home Page";

// TemplateContent: page_content
ob_start ();
?>
<!-- style for this page -->
<style>
dt.news {font-style: italic}
</style>
<? $head_content = ob_get_contents (); ob_clean (); ?>
<img src="private/images/workflow-small.jpg" alt="CUTS architecture &amp; workflow"
		 title="CUTS architecture &amp; workflow"
		 align="right" hspace="10px" />
<h3>Welcome!</h3>
<p>The Component Workload Emulator (CoWorkEr) Utilization Test Suite (also known as CUTS)
is a model-driven engineering (MDE)-based tool that allows developers to conduct system
integration test at early stages of development and locate performance problems before
they become to hard to locate and resolve later in the development lifecycle. Developers
and testers use CUTS to model the expected behavior of their real components. The behavior 
models are then used to generate emulation components that are <i>compliant with the target
technologies specification</i> and <i>have the same interfaces and attributes as their real
counterpart</i>. The emulated components are then executed in the target environment
and different QoS metrics (e.g., throughput, response time, and service rate) are 
monitored and collected. Developers and testers can grapically view the collected metrics 
while the system is executing to understand its current performance, and gain insight on 
how to improve it. Lastly, as the real component's implementation is completed, it can
replace its respective emulation component to produce more realistic results and
facilitate continuous system integration.</p>

<!--table width="100%">
<tr style="vertical-align:top">
	<td >
		<div style="text-decoration:underline; font-weight:bold">Recent News</div>
		<dl>
			<dt class="news">Enter timestamp here...</dt>
			<dd>Enter new here...</dd>

			<dt class="news">Enter timestamp here...</dt>
			<dd>Enter new here...</dd>
		</dl>
	</td>
	<td style="text-align:right">
</td>
</tr>
</table-->
<? $page_content = ob_get_clean (); ?>

<!-- master page -->
<? require_once ('cuts.master.php'); ?>
