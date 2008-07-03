@setlocal

@rem set CLASSPATH=%CLASSPATH%;%CUTS_ROOT%\lib\cuts.java.jbi.deployment.jar
@rem set CLASSPATH=%CLASSPATH%;%CUTS_ROOT%\lib\cuts.java.jbi.jar
@rem set CLASSPATH=%CLASSPATH%;%JACORB_ROOT%\lib\jacorb.jar
@rem set CLASSPATH=%CLASSPATH%;%LOG4J_ROOT%\log4j-1.2.15.jar

java -Djava.endorsed.dirs=%CUTS_ROOT%\lib;%CUTS_ROOT%\contrib\java -Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB -Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton -cp %CLASSPATH% cuts.java.jbi.deployment.JbiExecutionManager %*

@endlocal
