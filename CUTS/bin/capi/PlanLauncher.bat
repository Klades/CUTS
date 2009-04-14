@rem ##########################################################################
@rem ##
@rem ## @file            PlanLauncher.bat
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

@set CUTS_CLASSPATH=%CUTS_ROOT%\lib\cuts.java.jbi.deployment.jar;%CUTS_ROOT%\contrib\java\log4j-1.2.15.jar;%CUTS_ROOT%\contrib\java\castor-1.2.jar;%CUTS_ROOT%\contrib\java\commons-logging-1.1.1.jar
@set CUTS_OPTS=-Djava.endorsed.dirs=%CUTS_ROOT%\contrib\java -Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB -Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton

java %JAVA_OPTS% %CUTS_OPTS% -classpath %CUTS_CLASSPATH%;%CLASSPATH%;. CUTS.jbi.deployment.JbiPlanLauncher %*

@endlocal
