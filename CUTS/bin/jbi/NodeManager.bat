@setlocal

@rem set CLASSPATH=%CLASSPATH%;%CUTS_ROOT%\lib\cuts.java.jbi.deployment.jar
@rem set CLASSPATH=%CLASSPATH%;%CUTS_ROOT%\lib\cuts.java.jbi.jar
@rem set CLASSPATH=%CLASSPATH%;%CUTS_ROOT%\contrib\java\jacorb.jar
@rem set CLASSPATH=%CLASSPATH%;%CUTS_ROOT%\contrib\java\log4j-1.2.15.jar
@rem set CLASSPATH=%CLASSPATH%;%CUTS_ROOT%\contrib\java\spring.jar
@rem set CLASSPATH=%CLASSPATH%;%CUTS_ROOT%\contrib\java\avalon-framework-4.1.5.jar
@rem set CLASSPATH=%CLASSPATH%;%JBI_ROOT%\lib\capi1.5.jar
@rem set CLASSPATH=%CLASSPATH%;%JBI_ROOT%\lib\dom4j-1.6.1.jar
@rem set CLASSPATH=%CLASSPATH%;%JBI_ROOT%\lib\jaxen-1.1.1.jar

java %JAVA_OPTS% -Djava.endorsed.dirs=%CUTS_ROOT%\lib;%CUTS_ROOT%\contrib\java -Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB -Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton -cp %CLASSPATH% cuts.java.jbi.deployment.JbiNodeManager %*

@endlocal
