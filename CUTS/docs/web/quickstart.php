<?php
// Master page variables
$path_to_root  = "";
$page_subtitle = "Quick Start";

// -- $page_content placeholder
ob_start (); ?>

<p>Coming soon...</p>

<!-- $page_content placeholder -->
<? $page_content = ob_get_clean (); ?>


<!-- master page -->
<? require_once ('cuts.master.php'); ?>

