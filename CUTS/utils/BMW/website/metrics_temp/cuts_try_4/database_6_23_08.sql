/* Database, procedures, and views
  Written by Hamilton Turner
  6 - 23 - 08
  @brief  intended to work with CUTS and provide a front end UI to 
          create, view, edit charts,unit tests, or logformats
*/

CREATE DATABASE `cuts` /*!40100 DEFAULT CHARACTER SET latin1 */;

DROP TABLE IF EXISTS `cuts`.`log`;
CREATE TABLE  `cuts`.`log` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `TestID` int(10) unsigned NOT NULL,
  `message` varchar(255) NOT NULL,
  `notes` varchar(45) default NULL,
  PRIMARY KEY  (`id`),
  KEY `Tid` (`TestID`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=latin1;

DROP TABLE IF EXISTS `cuts`.`logformatdesc`;
CREATE TABLE  `cuts`.`logformatdesc` (
  `lfid` int(10) unsigned NOT NULL auto_increment,
  `lfmt` varchar(150) NOT NULL default ' ' COMMENT 'this is the test duration: {int} part',
  `icase_regex` varchar(180) NOT NULL default ' ' COMMENT 'eventually we should have case sensitive',
  `csharp_regex` varchar(200) default NULL COMMENT 'eventually this should be a PCRE regex so its universal',
  PRIMARY KEY  (`lfid`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=latin1;

DROP TABLE IF EXISTS `cuts`.`logformatvariabletable`;
CREATE TABLE  `cuts`.`logformatvariabletable` (
  `lfid` int(10) unsigned NOT NULL auto_increment,
  `varname` varchar(45) NOT NULL,
  `vartype` varchar(45) NOT NULL,
  `grouped` tinyint(1) NOT NULL default '0' COMMENT 'this allows you to group your results by a certain variable',
  `aggregate_func` varchar(45) default NULL,
  UNIQUE KEY `UNIQUE` (`lfid`,`varname`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=latin1;

DROP TABLE IF EXISTS `cuts`.`packagedesc`;
CREATE TABLE  `cuts`.`packagedesc` (
  `pkid` int(10) unsigned NOT NULL auto_increment,
  `desc` varchar(45) NOT NULL,
  `name` varchar(45) NOT NULL,
  PRIMARY KEY  (`pkid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

DROP TABLE IF EXISTS `cuts`.`packagetable`;
CREATE TABLE  `cuts`.`packagetable` (
  `pkid` int(10) unsigned NOT NULL,
  `utid` int(10) unsigned NOT NULL,
  UNIQUE KEY `UNIQUE_REST` (`pkid`,`utid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

DROP TABLE IF EXISTS `cuts`.`testsuitedesc`;
CREATE TABLE  `cuts`.`testsuitedesc` (
  `tsid` int(10) unsigned NOT NULL auto_increment,
  `desc` varchar(45) NOT NULL,
  PRIMARY KEY  (`tsid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

DROP TABLE IF EXISTS `cuts`.`testsuitetable`;
CREATE TABLE  `cuts`.`testsuitetable` (
  `tsid` int(10) unsigned NOT NULL,
  `tpid` int(10) unsigned NOT NULL,
  UNIQUE KEY `UNIQUE_REST` (`tsid`,`tpid`)
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
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;

DROP TABLE IF EXISTS `cuts`.`unittesttable`;
CREATE TABLE  `cuts`.`unittesttable` (
  `utid` int(10) unsigned NOT NULL,
  `lfid` int(10) unsigned NOT NULL,
  UNIQUE KEY `UNIQUE` (`utid`,`lfid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

DROP VIEW IF EXISTS `cuts`.`logformat_down`;
CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW  `cuts`.`logformat_down` AS select `logformatdesc`.`lfid` AS `lfid`,`logformatdesc`.`lfmt` AS `lfmt`,`logformatvariabletable`.`varname` AS `varname` from (`logformatdesc` join `logformatvariabletable`) where (`logformatdesc`.`lfid` = `logformatvariabletable`.`lfid`);

DROP VIEW IF EXISTS `cuts`.`unittest_down`;
CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW  `cuts`.`unittest_down` AS select `unittestdesc`.`utid` AS `utid`,`logformatdesc`.`lfid` AS `lfid`,`unittestdesc`.`name` AS `name`,`logformatdesc`.`lfmt` AS `lfmt` from ((`unittestdesc` join `unittesttable`) join `logformatdesc`) where ((`unittestdesc`.`utid` = `unittesttable`.`utid`) and (`unittesttable`.`lfid` = `logformatdesc`.`lfid`));

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
    select testID,message from `log` where message regexp (SELECT icase_regex from logformatdesc WHERE lfid = lfid_in);
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
CREATE DEFINER=`root`@`localhost` PROCEDURE  `cuts`.`Insert_LF_variable`(id INT, name VARCHAR(45), vtype VARCHAR(45), is_grouped tinyint)
BEGIN
    INSERT INTO `logformatvariabletable` (lfid, varname, vartype, grouped) VALUES (id,name,vtype,is_grouped);
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

DROP PROCEDURE IF EXISTS `cuts`.`Insert_UT_logformat`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE  `cuts`.`Insert_UT_logformat`(uid INT, lid INT)
BEGIN
    INSERT INTO `unittesttable` (utid,lfid) VALUES (uid,lid);
END $$

DELIMITER ;