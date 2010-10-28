@rem *** $Id$ ***
@setlocal

@rem *** make sure the Visual Studio 8 environment variables are set
call %VS80COMNTOOLS%\vsvars32.bat

@rem *** run the ant script
call %ANT_HOME\ant.bat %*

@endlocal
