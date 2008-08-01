--
-- @file        CUTS-unittest.sql
--
-- $Id$
--
-- @author      Hamilton Turner
--

-- ============================================================================
-- BEGIN TABLES
-- ============================================================================

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


-- main table for unit tests
-- contains all one-one UT info
-- Need to update fail/warn comparison so they are ENUM
-- Need to extend so there are n-levels of warning
CREATE TABLE IF NOT EXISTS cuts.unittestdesc (
  utid                      INT               NOT NULL auto_increment,
  name                      VARCHAR(45)       NOT NULL,
  description               VARCHAR(95)       NOT NULL,
  evaluation                VARCHAR(45)       NOT NULL,
  fail_comparison           VARCHAR(20),
  fail                      VARCHAR(25),
  warn_comparison           VARCHAR(20),
  warn                      VARCHAR(25),
  aggregration_function     VARCHAR(25),

  -- set the primary key for the table
  PRIMARY KEY  (utid),

  -- set the unique values for the table
  UNIQUE (name)
);

-- main table for packages


CREATE TABLE IF NOT EXISTS cuts.packages (
  id            INT               NOT NULL auto_increment,
  name          VARCHAR(95)       NOT NULL,

  -- set the constraints for the table
  PRIMARY KEY  (id),

  -- set the unique values for the table
  UNIQUE (name)
);

-- main table for test suites

CREATE TABLE IF NOT EXISTS cuts.test_suites (
  id            INT             NOT NULL auto_increment,
  name          VARCHAR(95)     NOT NULL,

  -- set the constraints for the table
  PRIMARY KEY  (id),

  -- set the unique values for the table
  UNIQUE (name)
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

  -- set the unique values for the table
  UNIQUE (lfid, varname),

  FOREIGN KEY (lfid) REFERENCES cuts.logformatdesc (lfid)
    ON DELETE CASCADE
    ON UPDATE CASCADE
);


-- sub table for packages
-- contains unit test ids

CREATE TABLE IF NOT EXISTS cuts.packages_unit_tests (
  id            INT              NOT NULL auto_increment,
  ut_id         INT              NOT NULL,

  -- set the constraints for the table
  FOREIGN KEY (id) REFERENCES cuts.packages (id)
    ON DELETE CASCADE
    ON UPDATE CASCADE,

  FOREIGN KEY (ut_id) REFERENCES cuts.unittestdesc (utid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,
  UNIQUE (id,ut_id)
);


-- sub table for test_suites
-- contains package ids

CREATE TABLE IF NOT EXISTS cuts.test_suite_packages (
  id              INT             NOT NULL,
  p_id            INT             NOT NULL,

  -- set the unique values for the constraint
  UNIQUE (id, p_id),

  -- set the foreign keys for the table
  FOREIGN KEY (id) REFERENCES cuts.test_suites (id)
    ON DELETE CASCADE
    ON UPDATE CASCADE,

  FOREIGN KEY (p_id) REFERENCES cuts.packages (id)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);


-- sub table for unit tests
-- contains grouping info - variableid

CREATE TABLE IF NOT EXISTS cuts.unittestgroups (
  utid          INT                 NOT NULL,
  variable_id   INT                 NOT NULL,

  -- set the constraints for the table
  UNIQUE (utid, variable_id),

  FOREIGN KEY (utid) REFERENCES cuts.unittestdesc (utid)
    ON DELETE CASCADE
    ON UPDATE CASCADE
);


-- sub table for unit tests
-- will contain relation info

CREATE TABLE IF NOT EXISTS cuts.unit_test_relations (
  utid          INT                NOT NULL,
  variable_id   INT                NOT NULL,
  variable_id_2 INT                NOT NULL,

  -- set the constraints for the table
  PRIMARY KEY (utid),

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

  UNIQUE (utid, lfid),

  FOREIGN KEY (utid) REFERENCES cuts.unittestdesc (utid)
    ON DELETE CASCADE
    ON UPDATE CASCADE,

  FOREIGN KEY (lfid) REFERENCES cuts.logformatdesc (lfid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);

-- ============================================================================
-- BEGIN STORED PROCEDURES
-- ============================================================================

DELIMITER //

-- given lfid gets all info about that LF - regex, varname/type/extended name

DROP PROCEDURE IF EXISTS cuts.Get_LFID_info//

CREATE PROCEDURE
  cuts.Get_LFID_info (IN lfid_in INT)
BEGIN
      -- When Databinding, the created column needs to have a type
      -- given to it, or it will not be able to bind correctly
      select csharp_regex,variable_id,varname,vartype, CAST(concat("LF",logformatdesc.lfid,".",varname) AS CHAR) as extended_varname
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



-- Simply inserts a relation into a unit test

DROP PROCEDURE IF EXISTS cuts.Insert_UT_Relation//
CREATE PROCEDURE
  cuts.Insert_UT_Relation(IN utid_in  INT,
                          IN vid_1_in INT,
                          IN vid_2_in INT)
BEGIN
      INSERT INTO unit_test_relations (utid,variable_id,variable_id_2) VALUES (utid_in, vid_1_in, vid_2_in);
END //


DROP PROCEDURE IF EXISTS cuts.evaluate_unit_test//
CREATE PROCEDURE
  cuts.evaluate_unit_test(IN utid_in INT)
BEGIN

    DECLARE fail_op      VARCHAR(2);
    DECLARE fail_val     VARCHAR(10);
    DECLARE warn_op      VARCHAR(2);
    DECLARE warn_val     VARCHAR(10);
    DECLARE tablename    VARCHAR(20);
    DECLARE eval         VARCHAR(150);
    DECLARE eval_no_aggr VARCHAR(150);
    DECLARE lfid_count   INT;

    -- Temporary variable to simplify the case where there are two LF's needed
    DECLARE temp         VARCHAR(10);

    -- Grab all one to one variables
    SELECT   fail_comparison, fail,     warn_comparison, warn
      INTO   fail_op,         fail_val, warn_op,         warn_val
      FROM cuts.unittestdesc
      WHERE utid = utid_in;

    -- Grab the desired aggregration and the evaluation
    SELECT   CONCAT(aggregration_function,"(",evaluation,")"), evaluation
      INTO   eval,                                             eval_no_aggr
      FROM unittestdesc
      WHERE utid = utid_in;

    -- See if we are working on a two LF unit test, or a normal one
    SELECT COUNT(*)
      INTO lfid_count
      FROM cuts.unittesttable
      WHERE utid = utid_in;


    IF lfid_count = 1 THEN
         -- If only one, store it
             SELECT CONCAT("LF",lfid)
                INTO tablename
                FROM cuts.unittesttable
                WHERE utid = utid_in;
    ELSEIF lfid_count = 2 THEN
            -- Store the first value
            SELECT lfid
              INTO temp
              FROM cuts.unittesttable
              WHERE utid = utid_in
              LIMIT 1;
            -- Store the second value
            SELECT lfid
              INTO tablename
              FROM cuts.unittesttable
              WHERE utid = utid_in
              LIMIT 1,1;
            -- Combine them
            SELECT CONCAT("LF",temp,",LF",tablename)
              INTO tablename;
        -- ]
    END IF;


    -- Returns test_number, evaluation, result
    -- Also returns result_count, which is useful for charting
    SET @sql = CONCAT("
        SELECT test_number,(",eval,") AS evaluation,
          IF ((",eval,") ",fail_op," ",fail_val,",'fail',",
          "IF ((",eval,") ",warn_op," ",warn_val,",'warn','pass')) AS result, ",
          "COUNT(",eval_no_aggr,") AS result_count ",
          "FROM ", tablename, " GROUP BY test_number;
        ");

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

END//

DROP PROCEDURE IF EXISTS cuts.evaluate_unit_test_single//
CREATE PROCEDURE cuts.evaluate_unit_test_single(
                                                IN utid_in INT,
                                                IN test_number INT)
BEGIN
    DECLARE fail_op             VARCHAR(2);
    DECLARE fail_val            VARCHAR(10);
    DECLARE warn_op             VARCHAR(2);
    DECLARE warn_val            VARCHAR(10);
    DECLARE tablename           VARCHAR(90);
    DECLARE single_tablename    VARCHAR(90);
    DECLARE eval                VARCHAR(150);
    DECLARE eval_no_aggr        VARCHAR(150);
    DECLARE lfid_count          INT;

    -- Temporary variable to simplify the case where there are two LF's needed
    DECLARE temp      VARCHAR(10);
    DECLARE t_var1    VARCHAR(45);
    DECLARE t_var2    VARCHAR(45);

    -- Grab all one to one variables
    SELECT   fail_comparison, fail,     warn_comparison, warn
      INTO   fail_op,         fail_val, warn_op,         warn_val
      FROM cuts.unittestdesc
      WHERE utid = utid_in;

    -- Grab the desired aggregration and the evaluation
    SELECT   CONCAT(aggregration_function,"(",evaluation,")"), evaluation
      INTO   eval,                                             eval_no_aggr
      FROM unittestdesc
      WHERE utid = utid_in;

    -- See if we are working on a two LF unit test, or a normal one
    SELECT COUNT(*)
      INTO lfid_count
      FROM cuts.unittesttable
      WHERE utid = utid_in;


    IF lfid_count = 1 THEN
         -- If only one, store it
         -- The single tablename allows us to remove ambiguity from
         --   WHERE test_number =
             SELECT CONCAT("LF",lfid), CONCAT("LF",lfid)
                INTO tablename,        single_tablename
                FROM cuts.unittesttable
                WHERE utid = utid_in;
    ELSEIF lfid_count = 2 THEN

            SELECT lfid, CONCAT("LF",lfid)
              INTO temp, single_tablename
              FROM cuts.unittesttable
              WHERE utid = utid_in
              LIMIT 1;

            SELECT lfid
              INTO tablename
              FROM cuts.unittesttable
              WHERE utid = utid_in
              LIMIT 1,1;

            SELECT CONCAT("LF",lfid,".",varname)
              INTO t_var1
              FROM logformatvariabletable
              WHERE variable_id=( SELECT variable_id
                                    FROM unit_test_relations
                                    WHERE utid=utid_in );

            SELECT CONCAT("LF",lfid,".",varname)
              INTO t_var2
              FROM logformatvariabletable
              WHERE variable_id=( SELECT variable_id_2
                                    FROM unit_test_relations
                                    WHERE utid=utid_in );

            -- You need at least one table names t0
            SELECT CONCAT("LF",temp," JOIN LF",tablename," ON ",
              t_var1,"=",t_var2)
              INTO tablename;
    END IF;


    -- Returns evaluation, result
    -- Also returns result_count, which is useful for charting
    -- There is always a table called t0 to make the test_number
    -- un-ambiguous
    SET @sql = CONCAT("
        SELECT (",eval,") AS evaluation,
          IF ((",eval,") ",fail_op," ",fail_val,",'fail',",
          "IF ((",eval,") ",warn_op," ",warn_val,",'warn','pass')) AS result, ",
          "COUNT(",eval_no_aggr,") AS result_count ",
          "FROM ", tablename,
          " WHERE ",single_tablename,".test_number=",test_number,";"
        );

    PREPARE s1 FROM @sql;
    EXECUTE s1;
    DEALLOCATE PREPARE s1;
END//

-- Allows you to grab all the results of a unit test, filtered by a test
--   number

DROP PROCEDURE IF EXISTS cuts.evaluate_unit_test_as_metric//
CREATE PROCEDURE
  cuts.evaluate_unit_test_as_metric(IN utid_in INT,
                                    IN test_num INT )
BEGIN
    DECLARE fail_op             VARCHAR(2);
    DECLARE fail_val            VARCHAR(10);
    DECLARE warn_op             VARCHAR(2);
    DECLARE warn_val            VARCHAR(10);
    DECLARE tablename           VARCHAR(90);
    DECLARE single_tablename    VARCHAR(90);
    DECLARE eval                VARCHAR(150);
    DECLARE lfid_count          INT;

    DECLARE temp                VARCHAR(10);
    DECLARE t_var1              VARCHAR(45);
    DECLARE t_var2              VARCHAR(45);

    DECLARE debugger            VARCHAR(1024);

    -- See if we are working on a two LF unit test, or a normal one
    SELECT COUNT(*)
      INTO lfid_count
      FROM cuts.unittesttable
      WHERE utid = utid_in;

    SELECT   fail_comparison, fail,     warn_comparison, warn,     evaluation
      INTO   fail_op,         fail_val, warn_op,         warn_val, eval
      FROM unittestdesc
      WHERE utid = utid_in;

    IF lfid_count = 1 THEN
            SELECT CONCAT("LF",lfid), CONCAT("LF",lfid)
                INTO tablename,        single_tablename
                FROM cuts.unittesttable
                WHERE utid = utid_in;
    ELSEIF lfid_count = 2 THEN

            SELECT lfid, CONCAT("LF",lfid)
              INTO temp, single_tablename
              FROM cuts.unittesttable
              WHERE utid = utid_in
              LIMIT 1;

            SELECT lfid
              INTO tablename
              FROM cuts.unittesttable
              WHERE utid = utid_in
              LIMIT 1,1;

            SELECT CONCAT("LF",lfid,".",varname)
              INTO t_var1
              FROM logformatvariabletable
              WHERE variable_id=( SELECT variable_id
                                    FROM unit_test_relations
                                    WHERE utid=utid_in );

            SELECT CONCAT("LF",lfid,".",varname)
              INTO t_var2
              FROM logformatvariabletable
              WHERE variable_id=( SELECT variable_id_2
                                    FROM unit_test_relations
                                    WHERE utid=utid_in );


            SELECT CONCAT("LF",temp," JOIN LF",tablename," ON ",
              t_var1,"=",t_var2)
              INTO tablename;
    END IF;

    SELECT CONCAT("
        SELECT (",eval,") AS evaluation ",
          "FROM ", tablename," ",
          "WHERE ", single_tablename,".test_number=",test_num,";"
        ) INTO debugger;

    SET @sql = CONCAT("
        SELECT (",eval,") AS evaluation ",
          "FROM ", tablename," ",
          "WHERE ", single_tablename,".test_number=",test_num,";"
        );


    PREPARE s1 FROM @sql;
    EXECUTE s1;
    DEALLOCATE PREPARE s1;
END//

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
  cuts.insert_test_suite_package(IN tsid INT,
                                 IN pkg_name VARCHAR(65))
BEGIN
  INSERT INTO test_suite_packages (id, p_id)
    VALUES (tsid,
            cuts.get_test_package_id (pkg_name));
END //


DROP PROCEDURE IF EXISTS cuts.create_test_package //

CREATE PROCEDURE
  cuts.create_test_package (IN pkg_name VARCHAR (65))
BEGIN
  INSERT INTO cuts.packages (name) VALUES (pkg_name);
END //

DROP FUNCTION IF EXISTS cuts.get_test_package_id //

CREATE FUNCTION
  cuts.get_test_package_id (pkg_name VARCHAR (65))
  RETURNS INT
BEGIN
  DECLARE retval INT;

  DECLARE CONTINUE HANDLER FOR NOT FOUND
  BEGIN
    INSERT INTO cuts.packages (name) VALUES (pkg_name);
    SET retval = LAST_INSERT_ID();
  END;

  SELECT id INTO retval FROM cuts.packages WHERE name = pkg_name;
  RETURN retval;
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
CREATE PROCEDURE cuts.Insert_UT(IN name_in VARCHAR(45),
                                IN descr VARCHAR(95),
                                IN fail_comp VARCHAR(20),
                                IN warn_comp VARCHAR(20),
                                IN eval VARCHAR(150),
                                IN fail VARCHAR(25),
                                IN warn VARCHAR(25),
                                IN aggr VARCHAR(25))
BEGIN
    INSERT INTO cuts.unittestdesc (name,
                                   description,
                                   fail_comparison,
                                   warn,fail,
                                   evaluation,
                                   warn_comparison,
                                   aggregration_function)
                           VALUES (name_in,
                                   descr,
                                   fail_comp,
                                   warn,
                                   fail,
                                   eval,
                                   warn_comp,
                                   aggr);

    SELECT utid FROM  unittestdesc WHERE name = name_in;
END //


-- THIS PROC IS DEPRECATED AND SHOULD NOT BE USED
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
