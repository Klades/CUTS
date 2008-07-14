--
-- @file        CUTS-unittest.sql
--
-- $Id: CUTS-unittest.sql 2044 2008-07-14 14:44:28Z turnerha $
--
-- @author      Hamilton Turner
--

--
-- Create the tables and procedures for unittesting. 
-- This will all be updated soon - for now all of the details are at the 
-- top of the file
-- 


/*
Tables

logformatdesc
main table for log formats
contains all one-one info

logformatvariabletable
sub table for log formats
contains variable info - name, type, id

packages
main table for packages

packages_unit_tests
sub table for packages
contains unit test ids

test_suites
main table for test suites


test_suites_packages
sub table for test_suites
contains package ids

unittestdesc
main table for unit tests
contains all one-one UT info

unittestgroups
sub table for unit tests
contains grouping info - variableid

unittestrelations
sub table for unit tests
will contain relation info

unittestaggregration
sub table for unit tests
contains aggregration info - variable id and aggregration funciton

unittesttable
sub table for unit tests
contains log format ids



Procedures

Get_LFID_info
given lfid gets all info about that LF - regex, varname/type/extended name

Get_log_data
given lfid returns messages from log that match that lfid

Get_UTID_vars
given UTID gets variables used in that UT
varname/type/extended name

Insert_LF
Given 1-1 stuff for LF, inserts new and returns id

Insert_LF_variable
inserts a single log format variable

Insert_package_unit_test
given package id and utid - inserts unit test in package

insert_test_suite
given a name, it inserts that as a test suite

insert_test_suite_package
given a test suite id and name, this inserts the name as a new package, and then inserts that package into the test suite

insert_test_suite_package_existing
given test suite id and package id, inserts package into test suite

Insert_UT
given 1-1 data for unit test, inserts new UT and returns id

Insert_UT_Aggregration
given utid, variable id, and function, inserts new UT aggregration

Insert_UT_Group
given utid and variable id, inserts variable group

insert_ut_logformat
given utid and lfid, add log format to ut
*/


DROP TABLE IF EXISTS `cuts`.`logformatdesc`;
CREATE TABLE  `cuts`.`logformatdesc` (
  `lfid` int(10) unsigned NOT NULL auto_increment,
  `lfmt` varchar(150) NOT NULL default ' ' COMMENT 'this is the test duration: {int} part',
  `icase_regex` varchar(180) NOT NULL default ' ' COMMENT 'eventually we should have case sensitive',
  `csharp_regex` varchar(200) default NULL COMMENT 'eventually this should be a PCRE regex so its universal',
  PRIMARY KEY  (`lfid`)
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=latin1;



DROP TABLE IF EXISTS `cuts`.`logformatvariabletable`;
CREATE TABLE  `cuts`.`logformatvariabletable` (
  `variable_id` int(10) unsigned NOT NULL auto_increment,
  `lfid` int(10) unsigned NOT NULL default '0',
  `varname` varchar(45) NOT NULL,
  `vartype` varchar(45) NOT NULL,
  PRIMARY KEY  USING BTREE (`variable_id`),
  UNIQUE KEY `UNIQUE` (`lfid`,`varname`)
) ENGINE=InnoDB AUTO_INCREMENT=15 DEFAULT CHARSET=latin1;





DROP TABLE IF EXISTS `cuts`.`packages`;
CREATE TABLE  `cuts`.`packages` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `name` varchar(95) NOT NULL default 'null_name',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `uniq` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;




DROP TABLE IF EXISTS `cuts`.`packages_unit_tests`;
CREATE TABLE  `cuts`.`packages_unit_tests` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `ut_id` int(10) unsigned NOT NULL,
  UNIQUE KEY `Index_2` (`id`,`ut_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;




DROP TABLE IF EXISTS `cuts`.`test_suites`;
CREATE TABLE  `cuts`.`test_suites` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `name` varchar(95) NOT NULL default 'null_name',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `uniq` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;




DROP TABLE IF EXISTS `cuts`.`test_suite_packages`;
CREATE TABLE  `cuts`.`test_suite_packages` (
  `id` int(10) unsigned NOT NULL,
  `p_id` int(10) unsigned NOT NULL,
  UNIQUE KEY `uniq` (`id`,`p_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;




DROP TABLE IF EXISTS `cuts`.`unittestdesc`;
CREATE TABLE  `cuts`.`unittestdesc` (
  `utid` int(10) unsigned NOT NULL auto_increment,
  `name` varchar(45) NOT NULL,
  `desc` varchar(95) default NULL,
  `fail_comparison` varchar(20) default NULL COMMENT 'contains < > <= ect. should probably eventually be an enum type',
  `warn` varchar(25) default NULL COMMENT 'need to extend so that there are n-levels of warning',
  `fail` varchar(25) default NULL,
  `evaluation` varchar(45) default NULL,
  `warn_comparison` varchar(20) default NULL,
  PRIMARY KEY  (`utid`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;





DROP TABLE IF EXISTS `cuts`.`unittestgroups`;
CREATE TABLE  `cuts`.`unittestgroups` (
  `utid` int(10) unsigned NOT NULL,
  `variable_id` int(10) unsigned NOT NULL,
  UNIQUE KEY `UNIQUE` USING BTREE (`utid`,`variable_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;





DROP TABLE IF EXISTS `cuts`.`unittestrelations`;
CREATE TABLE  `cuts`.`unittestrelations` (
  `utid` int(10) unsigned NOT NULL,
  `variable_id` int(10) unsigned NOT NULL,
  `function` varchar(45) NOT NULL,
  `variable2_id` int(10) unsigned NOT NULL,
  UNIQUE KEY `UNIQUE` USING BTREE (`utid`,`variable_id`,`variable2_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;





DROP TABLE IF EXISTS `cuts`.`unittestaggregration`;
CREATE TABLE  `cuts`.`unittestaggregration` (
  `utid` int(10) unsigned NOT NULL,
  `variable_id` int(10) unsigned NOT NULL,
  `function` varchar(45) NOT NULL,
  UNIQUE KEY `UNIQUE` USING BTREE (`utid`,`variable_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;





DROP TABLE IF EXISTS `cuts`.`unittesttable`;
CREATE TABLE  `cuts`.`unittesttable` (
  `utid` int(10) unsigned NOT NULL,
  `lfid` int(10) unsigned NOT NULL,
  UNIQUE KEY `UNIQUE` (`utid`,`lfid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;




DELIMITER $$

DROP PROCEDURE IF EXISTS `cuts`.`Get_LFID_info`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE  `cuts`.`Get_LFID_info`(lfid_in int)
BEGIN
      select csharp_regex,varname,vartype, concat("LF",logformatdesc.lfid,".",varname) as extended_varname
      FROM logformatdesc join logformatvariabletable on logformatdesc.lfid = logformatvariabletable.lfid
      where logformatdesc.lfid = lfid_in;
END $$

DELIMITER ;




DELIMITER $$

DROP PROCEDURE IF EXISTS `cuts`.`Get_log_data`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE  `cuts`.`Get_log_data`(lfid_in int)
BEGIN
    select test_number,message from `msglog` where message regexp (SELECT icase_regex from logformatdesc WHERE lfid = lfid_in);
END $$

DELIMITER ;




DELIMITER $$

DROP PROCEDURE IF EXISTS `cuts`.`Get_UTID_vars`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE  `cuts`.`Get_UTID_vars`(utid_in INT)
BEGIN
      SELECT varname, concat("LF",lfid,".",varname) as extended_varname, 'false' as grouped_on_x, 'false' as grouped_on_z, vartype
      FROM logformatvariabletable where lfid in
                                                (SELECT lfid FROM unittesttable WHERE utid = utid_in);
END $$

DELIMITER ;




DELIMITER $$

DROP PROCEDURE IF EXISTS `cuts`.`GetVariableAggregration`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE  `cuts`.`GetVariableAggregration`(LFID_in integer, VarName_in varchar(45))
BEGIN
    SELECT `Function`,concat("`LF",lfid,"`.`",varname,"`") as ExtendedName
    FROM unittestaggregration as uta join logformatvariabletable as lfv
    where uta.variable_id = lfv.variable_id
    and lfv.lfid = LFID_in and lfv.varname = VarName_in;
END $$

DELIMITER ;



DELIMITER $$

DROP PROCEDURE IF EXISTS `cuts`.`Insert_LF`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE  `cuts`.`Insert_LF`(log_form VARCHAR(150),iregex varchar(180),csregex varchar(180))
BEGIN
    INSERT INTO `logformatdesc` (lfmt,icase_regex,csharp_regex) VALUES (log_form, iregex, csregex);
    SELECT lfid FROM  `logformatdesc` WHERE lfmt = log_form;
END $$

DELIMITER ;




DELIMITER $$

DROP PROCEDURE IF EXISTS `cuts`.`Insert_LF_variable`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE  `cuts`.`Insert_LF_variable`(id INT, name VARCHAR(45), vtype VARCHAR(45))
BEGIN
    INSERT INTO `logformatvariabletable` (lfid, varname, vartype) VALUES (id,name,vtype);
END $$

DELIMITER ;




DELIMITER $$

DROP PROCEDURE IF EXISTS `cuts`.`insert_package_unit_test`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE  `cuts`.`insert_package_unit_test`(id_in integer, utid_in integer)
BEGIN
      insert into packages_unit_tests (id, ut_id) values (id_in, utid_in);
END $$

DELIMITER ;




DELIMITER $$

DROP PROCEDURE IF EXISTS `cuts`.`insert_test_suite`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE  `cuts`.`insert_test_suite`(name_in varchar(65))
BEGIN
    Insert into test_suites (name) values (name_in);
END $$

DELIMITER ;





DELIMITER $$

DROP PROCEDURE IF EXISTS `cuts`.`insert_test_suite_package`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE  `cuts`.`insert_test_suite_package`(test_suite_id_in integer, name_in varchar(65))
BEGIN
      Declare new_p_id integer;

      -- Insert into packages table
      INSERT into packages (name) values (name_in);

      -- Add to test suite
      SELECT id into new_p_id FROM packages where name = name_in limit 1;
      INSERT into test_suite_packages (id,p_id) values (test_suite_id_in, new_p_id);
END $$

DELIMITER ;




DELIMITER $$

DROP PROCEDURE IF EXISTS `cuts`.`insert_test_suite_package_existing`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE  `cuts`.`insert_test_suite_package_existing`(id_in integer, pid_in integer)
BEGIN
      insert into test_suite_packages (id,p_id) values (id_in, pid_in);
END $$

DELIMITER ;




DELIMITER $$

DROP PROCEDURE IF EXISTS `cuts`.`Insert_UT`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE  `cuts`.`Insert_UT`(name_in VARCHAR(45),descr varchar(95),fail_comp varchar(20),warn_comp varchar(20),
                                                        eval varchar(150),fail varchar(25), warn varchar(25))
BEGIN
    INSERT INTO `unittestdesc` (name,`desc`,fail_comparison,warn,fail,evaluation,warn_comparison)
                        VALUES (name_in,descr,fail_comp,warn,fail,eval,warn_comp);
    SELECT utid FROM  `unittestdesc` WHERE name = name_in;
END $$

DELIMITER ;




DELIMITER $$

DROP PROCEDURE IF EXISTS `cuts`.`Insert_UT_Aggregration`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE  `cuts`.`Insert_UT_Aggregration`(utid_in integer, VariableID_in integer, function_in varchar(45))
BEGIN
      Insert into unittestaggregration (utid, variable_id, `function`) values (utid_in, VariableID_in, function_in);
END $$

DELIMITER ;




DELIMITER $$

DROP PROCEDURE IF EXISTS `cuts`.`Insert_UT_Group`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE  `cuts`.`Insert_UT_Group`(utid_in integer, variableID_in integer)
BEGIN
      Insert into unittestgroups (utid,variable_id) values (utid_in, variableID_in);
END $$

DELIMITER ;




DELIMITER $$

DROP PROCEDURE IF EXISTS `cuts`.`Insert_UT_LogFormat`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE  `cuts`.`Insert_UT_LogFormat`(utid_in INT, lfid_in INT)
BEGIN
    INSERT INTO `unittesttable` (utid,lfid) VALUES (utid_in,lfid_in);
END $$

DELIMITER ;