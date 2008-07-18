@echo OFF
set err=0

IF NOT DEFINED CUTS_ROOT goto forgot_cuts_root

echo.
echo  /-----------------------------------\
echo  /      CUTS DataBase Installer      \
echo  /                                   \
echo  / Installs tables, procedures, and  \
echo  /   functions needed to run CUTS    \
echo  /-----------------------------------\
echo.
echo.

IF "%1"=="-u" goto start
IF "%2"=="-u" goto start
IF "%3"=="-u" goto start
IF "%4"=="-u" goto start
IF "%5"=="-u" goto start
IF "%6"=="-u" goto start
IF "%7"=="-u" goto start
IF "%8"=="-u" goto start
IF "%9"=="-u" goto start

:err
echo set error
set err=1

:start
echo When you are ready,
pause
echo Install Started...
sleep 1
@mysql %* < %CUTS_ROOT%\etc\SQL\CUTS-create.sql
cls
echo !......                                 !
sleep 1
@mysql %* < %CUTS_ROOT%\etc\SQL\CUTS-baseline.sql
cls
echo !...........                            !
sleep 1
@mysql %* < %CUTS_ROOT%\etc\SQL\CUTS-deployment.sql
cls
echo !....................                   !
sleep 1
@mysql %* < %CUTS_ROOT%\etc\SQL\CUTS-performance.sql
cls
echo !...........................            !
sleep 1
@mysql %* < %CUTS_ROOT%\etc\SQL\CUTS-execution-paths.sql
cls
echo !..................................     !
sleep 1
@mysql %* < %CUTS_ROOT%\etc\SQL\CUTS-msglog.sql
cls
echo !.......................................!
sleep 1
@mysql %* < %CUTS_ROOT%\etc\SQL\CUTS-unittest.sql 


IF NOT "%err%"=="1" goto end
echo.
echo.
echo Oops - You did not specify a username for mySQL. If you don't know what
echo this means, and you got an error, try re-running this script as 
echo install-mysql.bat -u root 
echo.
echo.
goto try_again


:forgot_cuts_root
echo.
echo.
echo Oops - It looks like you have not set the CUTS_ROOT environment variable. 
echo. 
echo Either you can set this variable, or run the scripts located in 
echo CUTS_ROOT\etc\SQL in the order listed at
echo     http://www.dre.vanderbilt.edu/CUTS/
goto try_again


:end
echo Install Complete!
pause
cls
exit

:try_again
pause