* Execute following command to create the solution file for each example. example_name should be replaced 
  accoarding to the example you are executing.
  
  $ACE_ROOT/bin/mwc.pl -type tool_name example_name.mwc
    eg : For Ant
         $ACE_ROOT/bin/mwc.pl -type vc9 Ant_Adapter.mwc

* Then build using the appripriate build tool

* Change the .unite file to have the correct path of the .datagraph file.

* Change the .datagraph file to have the correct path of the adapter dll