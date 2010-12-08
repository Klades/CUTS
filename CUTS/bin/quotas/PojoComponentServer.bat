@rem ##########################################################################
@rem ##
@rem ## @file            PojoComponentServer.bat
@rem ##
@rem ## $Id$
@rem ##
@rem ## @author          James H. Hill
@rem ##
@rem ##########################################################################

@setlocal

@rem ## define the CONTRIB_ROOT environment variable
@set CONTRIB_ROOT=%CUTS_ROOT%\contrib\java

@rem ## set the classpath
@set CLASSPATH=%CLASSPATH%;%CUTS_ROOT%\lib\cuts.quotas.pojo.jar;
@set CLASSPATH=%CLASSPATH%;%CUTS_ROOT%\lib\cuts.datamodel.jar
@set CLASSPATH=%CLASSPATH%;%CONTRIB_ROOT%\spring.jar
@set CLASSPATH=%CLASSPATH%;%CONTRIB_ROOT%\log4j-1.2.15.jar
@set CLASSPATH=%CLASSPATH%;%CONTRIB_ROOT%\commons-logging-1.1.1.jar

@rem ## start the Java process
java -Djava.endorsed.dirs=%CUTS_ROOT%\contrib\java -cp %CLASSPATH% cuts.quotas.pojo.PojoComponentServer %*

@endlocal
