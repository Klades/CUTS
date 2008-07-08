@rem ##########################################################################
@rem ##
@rem ## @file            SingleProcess.bat
@rem ##
@rem ## $Id$
@rem ##
@rem ## @author          James H. Hill
@rem ##
@rem ## Helper script for manually deploying multiple JBI client objects into 
@rem ## a single application process.
@rem ##
@rem ##########################################################################

@setlocal

@rem ## common variables
@set JBI_CLASSPATH=%JBI_ROOT%\lib\capi1.5.jar;%JBI_ROOT%\lib\dom4j-1.6.1.jar;%JBI_ROOT%\lib\jaxen-1.1.1.jar;%JBI_ROOT%\lib\jbossall-client.jar;%JBI_ROOT%\lib\xpp3_xpath-1.1.4c.jar;%JBI_ROOT%\lib\xpp3-1.1.4c.jar
@set CUTS_CLASSPATH=%CUTS_ROOT%\lib\cuts.java.jbi.deployment.jar;%CUTS_ROOT%\lib\cuts.java.jar;%CUTS_ROOT%\lib\cuts.java.jbi.jar;%CUTS_ROOT%\contrib\java\spring.jar;%CUTS_ROOT%\contrib\java\log4j-1.2.15.jar;%CUTS_ROOT%\contrib\java\commons-logging-1.1.1.jar;%CUTS_ROOT%\contrib\java\castor-1.2.jar

@rem ## execute the application
java -classpath %CUTS_CLASSPATH%;%JBI_CLASSPATH%;%CLASSPATH% -Djava.endorsed.dirs=%CUTS_ROOT%\contrib\java -Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB -Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton %JAVA_OPTS% cuts.java.jbi.deployment.JbiClientApp %*

@endlocal
