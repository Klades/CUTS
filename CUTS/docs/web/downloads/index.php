<?php
// Master page variables
$path_to_root  = "../";
$page_subtitle = "Downloads";

// -- $page_content placeholder
ob_start (); ?>
<hr />
<a name="top"></a>
<a href="#runtime">Runtime Architecture</a> |
<a href="#modeling">Modeling Tools</a> |
<a href="#database">Database Schema(s)</a> |
<a href="#bmw">Benchmark Manager Web (BMW) Utility</a>
<hr />
</a>

<!-- begin CUTS runtime architecture -->
<a name="runtime"></a>
<h2 style="text-decoration:underline">CUTS Runtime Architecture</h2>

<h3>System Requirements</h3>

<p>The following are the miminal system requirements for installing the
CUTS building and installing the CUTS runtime architecture.</p>

<ul>
  <li><a href="http://www.dre.vanderbilt.edu/CIAO">ACE+TAO+CIAO</a></li>
</ul>

<div style="font-weight:bold">Note to Linux Users</div>
If you are building and installing the database features of CUTS in the Linux/Unix environment,
please have the most recent version of
<a href="http://www.unixodbc.org" target="_blank">UnixODBC</a> installed.

<h3>Obtaining CUTS</h3>

<p>You can obtain the latest snapshot of the CUTS runtime architecture from the
DOC Group <a href="http://subversion.tigris.org" target="_blank">Subversion</a>
repository:</p>

<code>svn://svn.dre.vanderbilt.edu/DOC/CUTS/trunk</code>

<h3>Building and Installing</h3>

Use the follow steps to build and install the CUTS runtime architecture:

<ol>
  <li><p>Set the environment variable <code>CUTS_ROOT=&lt;path_to_CUTS&gt;</CODE>.</li>

  <li>
    <p><b>non-Windows:</b> set <code>PATH=$PATH:$CUTS_ROOT/bin</code> and set
    <code>LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CUTS_ROOT/lib</code></p>
    <p><b>Windows:</b> set <code>PATH=%PATH%;%CUTS_ROOT%/bin;%CUTS_ROOT/lib</code></p>
  </li>

  <li><p>Determine what features located in <code>$CUTS_ROOT/default.features</code> are
  needed to build your version of CUTS. Under normal circumstances you will not need
  to change any of the settings in <code>default.features</code>. However, if you are
  building CUTS with database support of unixODBC, then you will need to change this
  file.</p></li>

  <li><p>Run the Makefile, Project, Workspace Creator (MPC) utility on
  <code>$CUTS_ROOT/CUTS.mwc</code> using the following command:</p>

  <pre>
  %> $ACE_ROOT/bin/mwc.pl [command-line args] CUTS.mwc
  %> $ACE_ROOT/bin/mwc.pl --help        # for help
  </pre></li>

  <li><p>Build the generated workspace with the target build tool and you
  are ready to go.</p></li>
</ol>

<h3>Verifying the Installation</h3>
<p>Once the build is complete, all shared libraries will be located
in <code>$CUTS_ROOT/lib</code>. The respective binaries for the
shared libraries located in <code>$CUTS_ROOT/lib</code> will be
located in <code>$CUTS_ROOT/bin</code>. Executables specific to CUTS
will be located in <code>$CUTS_ROOT/bin</code>.

<p style="text-align:right">[<a href="#top">Back to Top</a>]</p>

<!-- begin CUTS Modeling Tools -->
<a name="modeling"></a>
<h2 style="text-decoration:underline">CUTS Modeling Tools</h2>

<h3>System Requirements</h3>
<p>The following are the miminal system requirements for installing the
CUTS modeling tools.</p>

<ul>
  <li><a href="http://www.dre.vanderbilt.edu/CoSMIC" title="CoSMIC home page">
    Component Synthesis with Model Integrated Computing (CoSMIC)</a></li>
</ul>

<h3>Installation</h3>
<p>Click the link below to download and install the CUTS modeling tools for CoSMIC.</p>

<table width="100%">
  <tr style="text-decoration:underline; text-align:left">
    <th style="width: 200px">Filename (KB)</th>
    <th style="width: 200px">Last Updated</th>
  </tr>
  <tr>
    <td><a href="CUTS_CoSMIC.msi">CUTS_CoSMIC.msi</a>
    (<?php echo floor (filesize ('CUTS_CoSMIC.msi') / 1024) . ' KB' ?>)</td>
    <td><?php echo date ('D, M j Y, H:i:s', filemtime ('CUTS_CoSMIC.msi')) ?></td>
  </tr>
</table>

<h3>Verifying the Installation</h3>
<p>Once the installation is complete, the CUTS interpreter will apprear as a
scissor icon in the interpreter toolbar for PICML projects.</p>

<p style="text-align:right">[<a href="#top">Back to Top</a>]</p>

<!-- begin CUTS Database Schemas -->
<a name="database"></a>
<h2 style="text-decoration:underline">CUTS Database Schemas</h2>

<h3>System Requirements</h3>
<p>The following are the miminal system requirements for installing database support
for CUTS.</p>

<ul>
  <li><a title="MySQL 5.0" href="http://dev.mysql.com/downloads/mysql/5.0.html">MySQL 5.0</a></li>
  <li><a title="MySQL Connector/ODBC 3.51.21"
           href="http://dev.mysql.com/downloads/connector/odbc/3.51.html">MySQL Connector/ODBC 3.51.21</a></li>
</ul>

<p><b>NOTICE:</b> For non-Windows environments, you must install
<a href="http://www.unixodbc.org">UnixODBC</a> before installing the MySQL connectors.</p>

<h3>Installing Database and Drivers</h3>

<h4>Installing MySQL 5.0</h4>
<p>There are no special requirements for installing MySQL 5.0. However, we do require you to remember
the <b>username</b> and <b>password</b> for <u>root</u> access. If you do not remember these, then you will not be able
to install the CUTS database.</p>

<h4>Installing MySQL Connector/ODBC 3.51.x</h4>
<p>There are no special requirements for installing MySQL Connector/ODBC 3.51.12 Downloads. Just follow
the instructions that come with the driver.</p>

<h3>Installing the CUTS Database</h3>
<p>To use the database features of CUTS, you must first install the CUTS database to you MySQL
server. We strongly recommend that you use MySQL 5.0 or greater. The installation scripts are
located in <code>$CUTS_ROOT/etc/SQL</code>. When installing the scripts use a command similar to
the following:</p>

<code>%> mysql --user=root [--password=&lt;root-password&gt;] < CUTS-create.sql</code>

<p>The CUTS database script named <code>CUTS-create.sql</code> has to be the first SQL script
installed into the database. If you install any of the other scripts before
<code>CUTS-create.sql</code>, then you will not be able to
properly install the CUTS database. After you install the <code>CUTS-create.sql</code>, you can
install any of the other scripts in <code>$CUTS_ROOT/etc/SQL</code>. The table below lists the
different scripts you can install.</p>

<table>
  <tr style="text-align:left"><th style="width:175px"><u>Script Name</u></th><th><u>Description</u></th></tr>
  <tr><td>CUTS-create.sql</td><td><b>INSTALL FIRST!!</b></td></tr>
  <tr><td>CUTS-baseline.sql</td><td>Store baseline metrics for individual components.</td></tr>
  <tr><td>CUTS-deployment.sql</td><td>Store deployment information for individual components.</td></tr>
  <tr><td>CUTS-execution.sql</td><td>Store execution times for individual components.</td></tr>
  <tr><td>CUTS-execution-paths.sql</td><td>Store execution paths for component assemblies.</td></tr>
</table>


<p style="text-align:right">[<a href="#top">Back to Top</a>]</p>

<!-- begin CUTS Benchmark Manager Web (BMW) Utility -->
<a name="bmw"></a>
<h2 style="text-decoration:underline">CUTS Benchmark Manager Web (BMW) Utility</h2>

<h3>System Requirements</h3>
<p>The following are the miminal system requirements for installing the
Benchmark Manager Web (BMW) Utility.</p>

<ul>
  <li>Microsoft Internet Information Services (IIS)</li>
  <li>Microsoft .NET Framework 2.0</li>
  <li><a href="http://dev.mysql.com/downloads/connector/net/5.0.html">MySQL Connector/NET 5.0.8.1</a></li>
</ul>

<h3>Installation</h3>
<p>Click the link below to download and install the BMW.</p>

<table width="100%">
  <tr style="text-decoration:underline; text-align:left">
    <th style="width: 200px">Filename (KB)</th>
    <th style="width: 200px">Last Updated</th>
  </tr>
  <tr>
    <td><a href="BMW.msi">BMW.msi</a>
    (<?php echo floor (filesize ('BMW.msi') / 1024) . ' KB' ?>)</td>
    <td><?php echo date ('D, M j Y, H:i:s', filemtime ('BMW.msi')) ?></td>
  </tr>
</table>

<h3>Verifying the Installation</h3>
<p>Once the installation is complete, the BMW can be viewed on the host
machine using to the following URL:</p>

<blockquote><code>http://localhost/CUTS</code></blockquote>

<p>You can also view the BMW from any web browser if you know the IP address,
or URL, or the webserver. Just replace &quot;localhost&quot; in the example
above with the correct IP address, or URL.

<h3>Changing the Database Location</h3>
The BMW by default is configured to locate the database that contains the
collected experiment metrics on the localhost. If you have installed the
CUTS database on a different machine, you can change the configuration so
the BMW will connect that machine. The steps below show how to change
this configuration:</p>

<ol>
  <li>Open <code>Web.config</code> located in <code>C:\Inetpub\wwwroot\CUTS</code></li>
  <li>Locate the keys: <code>ConnectionString</code> and <code>MySQL</code></li>
  <li>Change the value of the property <code>SERVER</code> and <code>Server</code>,
  respectively, in both connection strings  to the hostname of the system hosting  the
  target CUTS database.</li>
</ol>

<p>The next version of the BMW will allow you to specify the location of
the database from its main page.</p>

<p style="text-align:right">[<a href="#top">Back to Top</a>]</p>

<!-- $page_content placeholder -->
<? $page_content = ob_get_clean (); ?>


<!-- master page -->
<? require_once ('../cuts.master.php'); ?>

