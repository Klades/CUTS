@rem ##########################################################################
@rem ##
@rem ## @file            NameService.bat
@rem ##
@rem ## $Id$
@rem ##
@rem ## @author          James H. Hill
@rem ##
@rem ## Helper script to starting the naming service.
@rem ##
@rem ##########################################################################

@setlocal

java %JAVA_OPTS% -Djava.endorsed.dirs=%CUTS_ROOT%\contrib\java -Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB -Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton org.jacorb.naming.NameServer %*

@endlocal
