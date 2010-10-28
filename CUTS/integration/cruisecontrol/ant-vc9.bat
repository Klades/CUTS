@rem *** $Id$ ***
@setlocal

@rem *** make sure Visual Studio 2008 environment variables are set
call %VS90COMNTOOLS%\vsvars32.bat

@rem *** call the configuration script for Visual Studio 2008 builds
@rem *** if and only if the script has been defined.
@if defined VC90BUILDCFG call %VC90BUILDCFG%

@rem *** run ant script
call %ANT_HOME\ant.bat %*

@endlocal
