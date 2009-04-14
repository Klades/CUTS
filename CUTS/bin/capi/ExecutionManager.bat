@rem ##########################################################################
@rem ##
@rem ## @file            ExecutionManager.bat
@rem ##
@rem ## $Id$
@rem ##
@rem ## @author          James H. Hill
@rem ##
@rem ## Helper script for launching the execution manager for the deployment
@rem ## framework.
@rem ##
@rem ##########################################################################

@setlocal

@set CLASSPATH=%CLASSPATH%;%CUTS_ROOT%\lib\cuts.java.capi.deployment.jar
@rem set CLASSPATH=%CLASSPATH%;%CUTS_ROOT%\lib\cuts.java.capi.jar
@rem set CLASSPATH=%CLASSPATH%;%JACORB_ROOT%\lib\jacorb.jar
@rem set CLASSPATH=%CLASSPATH%;%LOG4J_ROOT%\log4j-1.2.15.jar

java -Djava.endorsed.dirs=%CUTS_ROOT%\contrib\java -Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB -Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton -cp %CLASSPATH% CUTS.jbi.deployment.JbiExecutionManager %*

@endlocal
