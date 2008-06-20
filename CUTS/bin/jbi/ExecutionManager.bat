@setlocal

@set CLASSPATH=%CLASSPATH%;%CUTS_ROOT%\lib\cuts.java.jbi.deployment.jar
@set CLASSPATH=%CLASSPATH%;%CUTS_ROOT%\lib\cuts.java.jbi.jar
@set CLASSPATH=%CLASSPATH%;%JACORB_ROOT%\lib\jacorb.jar
@set CLASSPATH=%CLASSPATH%;%LOG4J_ROOT%\log4j-1.2.15.jar

jaco cuts.java.jbi.deployment.JbiExecutionManager %*

@endlocal
