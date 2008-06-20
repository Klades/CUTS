@setlocal

@set CLASSPATH=%CLASSPATH%;%CUTS_ROOT%\lib\cuts.java.jbi.deployment.jar
@set CLASSPATH=%CLASSPATH%;%CUTS_ROOT%\lib\cuts.java.jbi.jar
@set CLASSPATH=%CLASSPATH%;%JACORB_ROOT%\lib\jacorb.jar
@set CLASSPATH=%CLASSPATH%;%LOG4J_ROOT%\log4j-1.2.15.jar
@set CLASSPATH=%CLASSPATH%;%SPRING_ROOT%\dist\spring.jar
@set CLASSPATH=%CLASSPATH%;%JBI_ROOT%\lib\capi1.5.jar
@set CLASSPATH=%CLASSPATH%;%JBI_ROOT%\lib\dom4j-1.6.1.jar
@set CLASSPATH=%CLASSPATH%;%JBI_ROOT%\lib\jaxen-1.1.1.jar

jaco cuts.java.jbi.deployment.JbiNodeManager %*

@endlocal
