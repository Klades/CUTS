@IF NOT DEFINED CUTS_ROOT goto no_cuts_root

@mysql %* < %CUTS_ROOT%\etc\SQL\CUTS-create.sql
@mysql %* < %CUTS_ROOT%\etc\SQL\CUTS-baseline.sql
@mysql %* < %CUTS_ROOT%\etc\SQL\CUTS-deployment.sql
@mysql %* < %CUTS_ROOT%\etc\SQL\CUTS-performance.sql
@mysql %* < %CUTS_ROOT%\etc\SQL\CUTS-execution-paths.sql
@mysql %* < %CUTS_ROOT%\etc\SQL\CUTS-msglog.sql
@mysql %* < %CUTS_ROOT%\etc\SQL\CUTS-unittest.sql
@goto end

:no_cuts_root
@echo CUTS_ROOT environment variable is not defined. Please set this variable, or
@echo run the scripts listed at http://www.dre.vanderbilt.edu/CUTS

:end
