--
-- @file        CUTS-unittest.sql
--
-- $Id: CUTS-unittest.sql 2044 2008-07-14 14:44:28Z turnerha $
--
-- @author      Hamilton Turner
--

--
-- Create the tables and procedures for unittesting. 
-- This will all be updated soon - the comments are very sparse
-- 


/*=====================================================
-- 
-- 
-- 
--                   Tables
-- 
-- 
====================================================*/


-- main table for log formats
-- contains all one-one info
-- eventually this should be a PCRE regex so its universal
-- Also, we should eventually make the regex case sensitive
CREATE TABLE IF NOT EXISTS  cuts.logformatdesc (
  lfid            INT             NOT NULL auto_increment,
  lfmt            VARCHAR(150)    NOT NULL,
  icase_regex     VARCHAR(180)    NOT NULL,
  csharp_regex    VARCHAR(200)    DEFAULT NULL,
  
  -- set the constraints for the table
  PRIMARY KEY  (lfid),
  UNIQUE (lfmt)
);


-- sub table for log formats
-- contains variable info - name, type, id

CREATE TABLE IF NOT EXISTS cuts.logformatvariabletable (
  variable_id       INT            NOT NULL auto_increment,
  lfid              INT            NOT NULL,
  varname           VARCHAR(45)    NOT NULL,
  vartype           VARCHAR(45)    NOT NULL,
  
  -- set the constraints for the table
  PRIMARY KEY (variable_id),
  UNIQUE (lfid,varname),
  
  
  FOREIGN KEY (lfid) REFERENCES cuts.logformatdesc (lfid) 
    ON DELETE CASCADE 
    ON UPDATE CASCADE
);



-- main table for packages


CREATE TABLE IF NOT EXISTS cuts.packages (
  id            INT               NOT NULL auto_increment,
  name          VARCHAR(95)       NOT NULL,
  
  -- set the constraints for the table
  PRIMARY KEY  (id),
  UNIQUE (name)
);




-- sub table for packages
-- contains unit test ids

CREATE TABLE IF NOT EXISTS cuts.packages_unit_tests (
  id            INT              NOT NULL auto_increment,
  ut_id         INT              NOT NULL,
  
  -- set the constraints for the table
  UNIQUE (id,ut_id)
);


-- main table for test suites

CREATE TABLE IF NOT EXISTS cuts.test_suites (
  id            INT             NOT NULL auto_increment,
  name          VARCHAR(95)     NOT NULL,
  
  -- set the constraints for the table
  PRIMARY KEY  (id),
  UNIQUE (name)
);



-- sub table for test_suites
-- contains package ids

CREATE TABLE IF NOT EXISTS cuts.test_suite_packages (
  id              INT             NOT NULL,
  p_id            INT             NOT NULL,
  
  -- set the constraints for the table
  UNIQUE (id,p_id)
);


-- main table for unit tests
-- contains all one-one UT info
-- Need to update fail/warn comparison so they are ENUM
-- Need to extend so there are n-levels of warning
CREATE TABLE IF NOT EXISTS cuts.unittestdesc (
  utid            INT               NOT NULL auto_increment,
  name            VARCHAR(45)       NOT NULL,
  description     VARCHAR(95)       DEFAULT NULL,
  fail_comparison VARCHAR(20)       DEFAULT NULL,
  warn            VARCHAR(25)       DEFAULT NULL,
  fail            VARCHAR(25)       DEFAULT NULL,
  evaluation      VARCHAR(45)       DEFAULT NULL,
  warn_comparison VARCHAR(20)       DEFAULT NULL,
  
  -- set the constraints for the table
  PRIMARY KEY  (utid)
);



-- sub table for unit tests
-- contains grouping info - variableid

CREATE TABLE IF NOT EXISTS cuts.unittestgroups (
  utid          INT                 NOT NULL,
  variable_id   INT                 NOT NULL,
  
  -- set the constraints for the table
  UNIQUE (utid,variable_id),
  FOREIGN KEY (utid) REFERENCES cuts.unittestdesc (utid) 
    ON DELETE CASCADE 
    ON UPDATE CASCADE
);


-- sub table for unit tests
-- will contain relation info

CREATE TABLE IF NOT EXISTS cuts.unittestrelations (
  utid         INT                NOT NULL,
  variable_id  INT                NOT NULL,
  function     VARCHAR(45)        NOT NULL,
  variable2_id INT                NOT NULL,
  
  -- set the constraints for the table
  UNIQUE (utid,variable_id,variable2_id),
  FOREIGN KEY (utid) REFERENCES cuts.unittestdesc (utid) 
    ON DELETE CASCADE 
    ON UPDATE CASCADE
);


-- sub table for unit tests
-- contains aggregration info - variable id and aggregration funciton

CREATE TABLE IF NOT EXISTS cuts.unittestaggregration (
  utid         INT             NOT NULL,
  variable_id  INT             NOT NULL,
  function     VARCHAR(45)     NOT NULL,
  
  -- set the constraints for the table
  UNIQUE (utid,variable_id),
  FOREIGN KEY (utid) REFERENCES cuts.unittestdesc (utid) 
    ON DELETE CASCADE 
    ON UPDATE CASCADE
);


-- sub table for unit tests
-- contains log format ids

CREATE TABLE IF NOT EXISTS cuts.unittesttable (
  utid          INT           NOT NULL,
  lfid          INT           NOT NULL,
  UNIQUE (utid,lfid),
  FOREIGN KEY (lfid) REFERENCES cuts.logformatdesc (lfid) 
    ON DELETE CASCADE 
    ON UPDATE CASCADE,
  FOREIGN KEY (utid) REFERENCES cuts.unittestdesc (utid) 
    ON DELETE CASCADE 
    ON UPDATE CASCADE
);

/*=====================================================
-- 
-- 
-- 
--                   Procedures
-- 
-- 
====================================================*/


DELIMITER //

-- given lfid gets all info about that LF - regex, varname/type/extended name

DROP PROCEDURE IF EXISTS cuts.Get_LFID_info//

CREATE PROCEDURE  
  cuts.Get_LFID_info (IN lfid_in INT)
BEGIN
      select csharp_regex,variable_id,varname,vartype, concat("LF",logformatdesc.lfid,".",varname) as extended_varname
      FROM logformatdesc join logformatvariabletable on logformatdesc.lfid = logformatvariabletable.lfid
      where logformatdesc.lfid = lfid_in;
END //


-- given lfid returns messages from log that match that lfid

DROP PROCEDURE IF EXISTS cuts.Get_log_data//

CREATE PROCEDURE  
  cuts.Get_log_data(IN lfid_in INT)

BEGIN
    select test_number,message from msglog where message regexp (SELECT icase_regex from logformatdesc WHERE lfid = lfid_in);
END //



DROP PROCEDURE IF EXISTS cuts.get_pass_warn_fail//
CREATE PROCEDURE
  cuts.get_pass_warn_fail(IN eval VARCHAR(500),
                          IN fail_op VARCHAR(2),
                          IN fail VARCHAR(10),
                          IN warn_op VARCHAR(2),
                          IN warn VARCHAR(10),
                          IN tablename VARCHAR(20))
BEGIN
    SET @sql = CONCAT("SELECT IF ((",eval,") ",fail_op," ",fail,",'fail',",
    "IF ((",eval,") ",warn_op," ",warn,",'warn','pass')) AS result ",
    "FROM ", tablename);

    PREPARE s1 FROM @sql;
    EXECUTE s1;
    DEALLOCATE PREPARE s1;

    -- Here is a simple example
    -- The result should be between 3 and 5
    -- Over 5, fail. Under 3, warn
    --
    -- SELECT IF ((result) > 5,'fail',
    --   IF ((result) < 3,'warn','pass'))
    -- AS result FROM lf7
END //



DROP PROCEDURE IF EXISTS cuts.get_pass_warn_fail_with_utid//
CREATE PROCEDURE
  cuts.get_pass_warn_fail_with_utid(IN utid_in INT, 
                                    IN eval VARCHAR(500))
BEGIN

    -- Opening declare of all vars
    DECLARE fail_op VARCHAR(2);
    DECLARE fail_val VARCHAR(10);
    DECLARE warn_op VARCHAR(2);
    DECLARE warn_val VARCHAR(10);
    DECLARE tablename VARCHAR(20);

    -- populating variables from one to one relationship
    SELECT fail_comparison, fail, warn_comparison, warn
    INTO fail_op, fail_val, warn_op, warn_val FROM unittestdesc
    WHERE utid = utid_in;

    -- getting tablename
    -- NOTE: THIS WILL ONLY WORK AS LONG AS THERE IS ONLY ONE LF PER UT
    SELECT CONCAT("LF",lfid) INTO tablename FROM unittesttable WHERE utid=utid_in;

    -- Create Dynamic SQL
    SET @sql = CONCAT("SELECT test_number,(",eval,") AS evaluation,
     IF ((",eval,") ",fail_op," ",fail_val,",'fail',",
    "IF ((",eval,") ",warn_op," ",warn_val,",'warn','pass')) AS result ",
    "FROM ", tablename, " GROUP BY test_number;");

    -- Execute and clean up
    PREPARE s1 FROM @sql;
    EXECUTE s1;
    DEALLOCATE PREPARE s1;

    -- Here is a simple example
    -- The result should be between 3 and 5
    -- Over 5, fail. Under 3, warn
    --
    -- SELECT IF ((result) > 5,'fail',
    --   IF ((result) < 3,'warn','pass'))
    -- AS result FROM lf7
END //



-- given UTID gets variables used in that UT
-- varname/type/extended name

DROP PROCEDURE IF EXISTS cuts.Get_UTID_vars//
CREATE PROCEDURE
  cuts.Get_UTID_vars(IN utid_in INT)
BEGIN
      SELECT varname, concat("LF",lfid,".",varname) as extended_varname, 'false' as grouped_on_x, 'false' as grouped_on_z, vartype
      FROM logformatvariabletable where lfid in
                                                (SELECT lfid FROM unittesttable WHERE utid = utid_in);
END //



DROP PROCEDURE IF EXISTS cuts.GetVariableAggregration//
CREATE PROCEDURE
  cuts.GetVariableAggregration(IN LFID_in integer,
                               IN VarName_in VARCHAR(45))
BEGIN
    SELECT Function,concat("LF",lfid,".",varname,"") as ExtendedName
    FROM unittestaggregration as uta join logformatvariabletable as lfv
    where uta.variable_id = lfv.variable_id
    and lfv.lfid = LFID_in and lfv.varname = VarName_in;
END //



DROP PROCEDURE IF EXISTS cuts.Insert_LF//
CREATE PROCEDURE
  cuts.Insert_LF(IN log_form VARCHAR(150),
                 IN iregex VARCHAR(180),
                 IN csregex VARCHAR(180))
BEGIN
    INSERT INTO logformatdesc (lfmt,icase_regex,csharp_regex) VALUES (log_form, iregex, csregex);
    SELECT lfid FROM  logformatdesc WHERE lfmt = log_form;
END //



DROP PROCEDURE IF EXISTS cuts.Insert_LF_variable//
CREATE PROCEDURE
  cuts.Insert_LF_variable(IN id INT, 
                          IN name VARCHAR(45),
                          IN vtype VARCHAR(45))
BEGIN
    INSERT INTO logformatvariabletable (lfid, varname, vartype) VALUES (id,name,vtype);
END //


-- given package id and utid - inserts unit test in package
DROP PROCEDURE IF EXISTS cuts.insert_package_unit_test//
CREATE PROCEDURE 
  cuts.insert_package_unit_test(IN id_in integer,
                                IN utid_in integer)
BEGIN
      insert into packages_unit_tests (id, ut_id) values (id_in, utid_in);
END //

-- given a name, it inserts that as a test suite

DROP PROCEDURE IF EXISTS cuts.insert_test_suite//
CREATE PROCEDURE
  cuts.insert_test_suite(IN name_in VARCHAR(65))
BEGIN
    Insert into test_suites (name) values (name_in);
END //


-- given a test suite id and name, this inserts the name as a new package, and then inserts that package into the test suite

DROP PROCEDURE IF EXISTS cuts.insert_test_suite_package//
CREATE PROCEDURE
  cuts.insert_test_suite_package(IN test_suite_id_in integer,
                                 IN name_in VARCHAR(65))
BEGIN
      Declare new_p_id integer;

      -- Insert into packages table
      INSERT into packages (name) values (name_in);

      -- Add to test suite
      SELECT id into new_p_id FROM packages where name = name_in limit 1;
      INSERT into test_suite_packages (id,p_id) values (test_suite_id_in, new_p_id);
END //


-- given test suite id and package id, inserts package into test suite

DROP PROCEDURE IF EXISTS cuts.insert_test_suite_package_existing//
CREATE PROCEDURE
  cuts.insert_test_suite_package_existing(IN id_in integer,
                                          IN pid_in integer)
BEGIN
      insert into test_suite_packages (id,p_id) values (id_in, pid_in);
END //


-- given 1-1 data for unit test, inserts new UT and returns id

DROP PROCEDURE IF EXISTS cuts.Insert_UT//
CREATE PROCEDURE
  cuts.Insert_UT(IN name_in VARCHAR(45),
                 IN descr VARCHAR(95),
                 IN fail_comp VARCHAR(20),
                 IN warn_comp VARCHAR(20),
                 IN eval VARCHAR(150),
                 IN fail VARCHAR(25),
                 IN warn VARCHAR(25))
BEGIN
    INSERT INTO unittestdesc (name,description,fail_comparison,warn,fail,evaluation,warn_comparison)
                        VALUES (name_in,descr,fail_comp,warn,fail,eval,warn_comp);
    SELECT utid FROM  unittestdesc WHERE name = name_in;
END //


-- given utid, variable id, and function, inserts new UT aggregration

DROP PROCEDURE IF EXISTS cuts.Insert_UT_Aggregration//
CREATE PROCEDURE
  cuts.Insert_UT_Aggregration(IN utid_in INT,
                              IN VariableID_in INT,
                              IN function_in VARCHAR(45))
BEGIN
      Insert into unittestaggregration (utid, variable_id, function) values (utid_in, VariableID_in, function_in);
END //

-- given utid and variable id, inserts variable group

DROP PROCEDURE IF EXISTS cuts.Insert_UT_Group//
CREATE PROCEDURE
  cuts.Insert_UT_Group(IN utid_in INT,
                       IN variableID_in INT)
BEGIN
      Insert into unittestgroups (utid,variable_id) values (utid_in, variableID_in);
END //


-- given utid and lfid, add log format to ut

DROP PROCEDURE IF EXISTS cuts.Insert_UT_LogFormat//
CREATE PROCEDURE
  cuts.Insert_UT_LogFormat(IN utid_in INT,
                           IN lfid_in INT)
BEGIN
    INSERT INTO unittesttable (utid,lfid) VALUES (utid_in,lfid_in);
END //

DELIMITER ;