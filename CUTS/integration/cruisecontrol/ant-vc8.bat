@rem *** $Id$ ***
@setlocal

@rem *** make sure Visual Studio 2005 environment variables are set
@call "%VS80COMNTOOLS%vsvars32.bat"

@rem *** call the configuration script for Visual Studio 2005 builds
@rem *** if and only if the script has been defined.
@if defined VC80BUILDCFG call %VC80BUILDCFG%

@rem *** run ant script
@call "%ANT_HOME%\bin\ant.bat" %*

@endlocal
