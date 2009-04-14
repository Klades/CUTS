@rem ##########################################################################
@rem ##
@rem ## @file            NodeManager.bat
@rem ##
@rem ## $Id$
@rem ##
@rem ## @author          James H. Hill
@rem ##
@rem ## Helper script to configure the deployment framework and start
@rem ## a new node manager.
@rem ##
@rem ##########################################################################

@setlocal

@set CLASSPATH=%CLASSPATH%;%CUTS_ROOT%\lib\cuts.java.jar
@set CLASSPATH=%CLASSPATH%;%CUTS_ROOT%\lib\cuts.java.jbi.jar
@set CLASSPATH=%CLASSPATH%;%CUTS_ROOT%\lib\cuts.java.jbi.deployment.jar
@set CLASSPATH=%CLASSPATH%;%CUTS_ROOT%\contrib\java\log4j-1.2.15.jar

java %JAVA_OPTS% -Djava.endorsed.dirs=%CUTS_ROOT%\contrib\java -Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB -Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton -classpath %CLASSPATH% CUTS.jbi.deployment.JbiNodeManager %*

@endlocal
