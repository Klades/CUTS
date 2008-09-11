@rem ##########################################################################
@rem ##
@rem ## @file            TestLoggerTest.bat
@rem ##
@rem ## $Id$
@rem ##
@rem ## @author          James H. Hill
@rem ##
@rem ##########################################################################

@setlocal

@rem ## common variables
@set CUTS_CLASSPATH=%CUTS_ROOT%\lib\CUTS.TestLogger.jar;%CUTS_ROOT%\lib\cuts.java.jbi.deployment.jar;%CUTS_ROOT%\lib\cuts.java.jar;%CUTS_ROOT%\lib\cuts.java.jbi.jar;%CUTS_ROOT%\contrib\java\spring.jar;%CUTS_ROOT%\contrib\java\log4j-1.2.15.jar;%CUTS_ROOT%\contrib\java\commons-logging-1.1.1.jar;%CUTS_ROOT%\contrib\java\castor-1.2.jar

@rem ## execute the application
java -cp .;%CUTS_CLASSPATH% -Djava.endorsed.dirs=%CUTS_ROOT%\contrib\java -Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB -Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton TestLoggerTest

@endlocal
