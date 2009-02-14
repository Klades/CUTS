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

CREATE TABLE IF NOT EXISTS  cuts.log_formats
(
  lfid            INT     NOT NULL auto_increment,
  lfmt            TEXT    NOT NULL,
  icase_regex     TEXT    NOT NULL,
  csharp_regex    TEXT    NOT NULL,

  -- set the constraints for the table
  PRIMARY KEY (lfid)
);

--
-- TABLE: cuts.unit_tests
--
CREATE TABLE IF NOT EXISTS cuts.unit_tests
(
  utid                      INT               NOT NULL auto_increment,
  name                      VARCHAR(45)       NOT NULL,
  description               VARCHAR(256),
  evaluation                VARCHAR(45)       NOT NULL,
  aggregration_function     VARCHAR(25)       NOT NULL,

  -- set the primary key for the table
  PRIMARY KEY  (utid),

  -- set the unique values for the table
  UNIQUE (name)
);

-- main table for packages


CREATE TABLE IF NOT EXISTS cuts.packages
(
  id            INT               NOT NULL auto_increment,
  name          VARCHAR(95)       NOT NULL,

  -- set the constraints for the table
  PRIMARY KEY  (id),

  -- set the unique values for the table
  UNIQUE (name)
);

-- main table for test suites

CREATE TABLE IF NOT EXISTS cuts.test_suites
(
  id            INT             NOT NULL auto_increment,
  name          VARCHAR(95)     NOT NULL,

  -- set the constraints for the table
  PRIMARY KEY  (id),

  -- set the unique values for the table
  UNIQUE (name)
);

CREATE TABLE IF NOT EXISTS cuts.test_suite_packages
(
  tspid   INT   NOT NULL auto_increment,
  tsid    INT   NOT NULL,
  tpid    INT   NOT NULL,

  -- package can appear only once in a test suite
  PRIMARY KEY (tspid),
  UNIQUE (tsid, tpid),

  FOREIGN KEY (tsid) REFERENCES cuts.test_suites (id)
    ON DELETE CASCADE
    ON UPDATE CASCADE,

  FOREIGN KEY (tpid) REFERENCES cuts.packages (id)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS cuts.test_package_items
(
  tpiid   INT   NOT NULL auto_increment,
  tspid   INT   NOT NULL,
  utid    INT   NOT NULL,

  -- a unit test can appear only once in a test suite
  PRIMARY KEY (tpiid),
  UNIQUE (tspid, utid),

  FOREIGN KEY (tspid) REFERENCES cuts.test_suite_packages (tspid)
    ON DELETE CASCADE
    ON UPDATE CASCADE,

  FOREIGN KEY (utid) REFERENCES cuts.unit_tests (utid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);

-- sub table for log formats
-- contains variable info - name, type, id

CREATE TABLE IF NOT EXISTS cuts.log_format_variables
(
  variable_id       INT            NOT NULL auto_increment,
  lfid              INT            NOT NULL,
  varname           VARCHAR(45)    NOT NULL,
  vartype           VARCHAR(45)    NOT NULL,

  -- set the constraints for the table
  PRIMARY KEY (variable_id),

  -- set the unique values for the table
  UNIQUE (lfid, varname),

  FOREIGN KEY (lfid) REFERENCES cuts.log_formats (lfid)
    ON DELETE CASCADE
    ON UPDATE CASCADE
);

-- sub table for unit tests
-- will contain relation info

CREATE TABLE IF NOT EXISTS cuts.unit_test_relations
(
  utid          INT                NOT NULL,
  relid         INT                NOT NULL,
  rel_index     INT                NOT NULL,
  variable_id   INT                NOT NULL,
  variable_id_2 INT                NOT NULL,

  -- set the constraints for the table
  PRIMARY KEY (utid, relid, rel_index),

  UNIQUE (utid, relid, variable_id, variable_id_2),
  UNIQUE (utid, relid, variable_id),
  UNIQUE (utid, relid, variable_id_2),

  FOREIGN KEY (utid) REFERENCES cuts.unit_tests (utid)
    ON DELETE CASCADE
    ON UPDATE CASCADE,

  FOREIGN KEY (variable_id)
    REFERENCES cuts.log_format_variables (variable_id)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,

  FOREIGN KEY (variable_id_2)
    REFERENCES cuts.log_format_variables (variable_id)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);

--
-- TABLE: cuts.unit_test_log_formats
--
CREATE TABLE IF NOT EXISTS cuts.unit_test_log_formats
(
  utid          INT           NOT NULL,
  lfid          INT           NOT NULL,

  UNIQUE (utid, lfid),

  FOREIGN KEY (utid) REFERENCES cuts.unit_tests (utid)
    ON DELETE CASCADE
    ON UPDATE CASCADE,

  FOREIGN KEY (lfid) REFERENCES cuts.log_formats (lfid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);

--
-- TABLE: cuts.unit_test_log_formats
--
CREATE TABLE IF NOT EXISTS cuts.unit_test_groupings
(
  utid          INT           NOT NULL,
  grpindex      INT           NOT NULL,
  varid         INT           NOT NULL,

  UNIQUE (utid, grpindex),
  UNIQUE (utid, varid),

  FOREIGN KEY (utid)
    REFERENCES cuts.unit_tests (utid)
    ON DELETE CASCADE
    ON UPDATE CASCADE,

  FOREIGN KEY (varid)
    REFERENCES cuts.log_format_variables (variable_id)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);

-- ============================================================================
-- BEGIN STORED PROCEDURES
-- ============================================================================

DELIMITER //

-- given lfid gets all info about that LF - regex, varname/type/extended name

DROP PROCEDURE IF EXISTS cuts.select_log_format_information //

CREATE PROCEDURE
  cuts.select_log_format_information (IN lfid_in INT)
BEGIN
      -- When Databinding, the created column needs to have a type
      -- given to it, or it will not be able to bind correctly
      select csharp_regex,variable_id,varname,vartype, CAST(concat("LF",log_formats.lfid,".",varname) AS CHAR) as extended_varname
      FROM log_formats join log_format_variables on log_formats.lfid = log_format_variables.lfid
      where log_formats.lfid = lfid_in;
END //

-- -----------------------------------------------------------------------------
-- FUNCTION: cuts.get_test_package_id
-- -----------------------------------------------------------------------------

DROP FUNCTION IF EXISTS cuts.get_test_package_id //

CREATE FUNCTION
  cuts.get_test_package_id (_name VARCHAR (255))
  RETURNS INT
BEGIN
  DECLARE retval INT;

  DECLARE CONTINUE HANDLER FOR NOT FOUND
  BEGIN
    INSERT INTO packages (name) VALUES (_name);
    SET retval = LAST_INSERT_ID();
  END;

  SELECT id INTO retval FROM packages WHERE name = _name;

  RETURN retval;
END; //

--
-- FUNCTION: cuts.get_variable_log_format_id
--

DROP FUNCTION IF EXISTS cuts.get_variable_log_format_id //

CREATE FUNCTION cuts.get_variable_log_format_id (_varid INT)
  RETURNS INT
BEGIN
  DECLARE retval INT;

  SELECT lfid INTO retval
    FROM cuts.log_format_variables WHERE variable_id = _varid;

  RETURN retval;
END //

--
-- FUNCTION: cuts.get_log_format_variable_id
--

DROP FUNCTION IF EXISTS cuts.get_log_format_variable_id //

CREATE FUNCTION cuts.get_log_format_variable_id (_lfid INT,
                                                 _varname VARCHAR(45))
  RETURNS INT
BEGIN
  DECLARE retval INT;

  SELECT variable_id INTO retval
    FROM cuts.log_format_variables
    WHERE lfid = _lfid AND varname = _varname;

  RETURN retval;
END //

--
-- PROCEDURE: cuts.select_log_data
--

DROP PROCEDURE IF EXISTS cuts.select_log_data //

CREATE PROCEDURE
  cuts.select_log_data(IN lfid_in INT)
BEGIN
    SELECT test_number, message
      FROM cuts.msglog
      WHERE message REGEXP (
        SELECT icase_regex FROM log_formats WHERE lfid = lfid_in);
END //

--
-- PROCEDURE: cuts.select_unit_test_causal_relations
--

DROP PROCEDURE IF EXISTS cuts.select_unit_test_causal_relations //

CREATE PROCEDURE cuts.select_unit_test_causal_relations (IN _utid INT)
BEGIN
  SELECT DISTINCT
        relid,
        cuts.get_variable_log_format_id (variable_id) AS cause,
        cuts.get_variable_log_format_id (variable_id_2) AS effect
    FROM cuts.unit_test_relations
    WHERE utid = _utid;
END //

--
-- PROCEDURE: cuts.select_unit_test_log_formats
--

DROP PROCEDURE IF EXISTS cuts.select_unit_test_log_formats //

CREATE PROCEDURE cuts.select_unit_test_log_formats (IN utid_ INT)
BEGIN
  SELECT t2.*
    FROM cuts.unit_test_log_formats AS t1,
         cuts.log_formats AS t2
    WHERE utid = utid_ AND
          t1.lfid = t2.lfid;
END //

--
-- PROCEDURE: cuts.select_test_suite_packages_i
--
DROP PROCEDURE IF EXISTS cuts.select_test_suite_packages_i //

CREATE PROCEDURE
  cuts.select_test_suite_packages_i (IN _suite INT)
BEGIN
  SELECT t1.tspid, t2.name
    FROM cuts.test_suite_packages AS t1,
         cuts.packages AS t2
    WHERE t1.tsid = _suite AND
          t1.tpid = t2.id;
END //

--
-- PROCEDURE: cuts.select_test_package_items_i
--
DROP PROCEDURE IF EXISTS cuts.select_test_package_items_i //

CREATE PROCEDURE
  cuts.select_test_package_items_i (IN _package INT)
BEGIN
  SELECT t1.tpiid, t2.name
    FROM cuts.test_package_items AS t1,
         cuts.unit_tests AS t2
    WHERE t1.tspid = _package AND
          t1.utid = t2.utid;
END //

--
-- PROCEDURE: cuts.select_unused_test_package_items_i
--
DROP PROCEDURE IF EXISTS cuts.select_unused_test_package_items_i //

CREATE PROCEDURE
  cuts.select_unused_test_package_items_i (IN _package INT)
BEGIN
  SELECT t1.utid, t1.name
    FROM cuts.unit_tests AS t1
    WHERE t1.utid NOT IN (
      SELECT utid FROM cuts.test_package_items
        WHERE tspid = _package)
    ORDER BY t1.name;
END //

DROP PROCEDURE IF EXISTS cuts.select_log_data_by_test //

CREATE PROCEDURE
  cuts.select_log_data_by_test (IN test_number_ INT,
                                IN format_ INT)

BEGIN
  SELECT hostname, msgtime, severity, message
    FROM cuts.msglog AS t1, cuts.ipaddr_host_map AS t2
    WHERE test_number = test_number_ AND
          t1.hostid = t2.hostid AND
          message REGEXP (SELECT icase_regex FROM cuts.log_formats WHERE lfid = format_)
    ORDER BY hostname, t1.msgtime ASC, t1.msgid ASC;
END //

--
-- PROCEDURE: cuts.select_log_data_desc_by_test_number
--

DROP PROCEDURE IF EXISTS cuts.select_log_data_desc_by_test_number //

CREATE PROCEDURE
  cuts.select_log_data_desc_by_test_number (IN test_number_ INT,
                                            IN format_ INT)
BEGIN
  SELECT hostname, msgtime, severity, message
    FROM cuts.msglog AS t1, cuts.ipaddr_host_map AS t2
    WHERE test_number = test_number_ AND
          t1.hostid = t2.hostid AND
          message REGEXP (
            SELECT icase_regex FROM cuts.log_formats WHERE lfid = format_)
    ORDER BY hostname, t1.msgtime DESC, t1.msgid DESC;
END //

--
-- PROCEDURE: cuts.select_log_data_asc_by_test_number
--

DROP PROCEDURE IF EXISTS cuts.select_log_data_asc_by_test_number //

CREATE PROCEDURE
  cuts.select_log_data_asc_by_test_number (IN test_number_ INT,
                                           IN format_ INT)
BEGIN
  SELECT hostname, msgtime, severity, message
    FROM cuts.msglog AS t1, cuts.ipaddr_host_map AS t2
    WHERE test_number = test_number_ AND
          t1.hostid = t2.hostid AND
          message REGEXP (
            SELECT icase_regex FROM cuts.log_formats WHERE lfid = format_)
    ORDER BY hostname, t1.msgtime ASC, t1.msgid DESC;
END //

--
-- FUNCTION: cuts.get_unit_test_id
--

DROP FUNCTION IF EXISTS cuts.get_unit_test_id //

CREATE FUNCTION cuts.get_unit_test_id (_name VARCHAR(45))
  RETURNS INT
BEGIN
  DECLARE retval INT;

  SELECT utid INTO retval
    FROM cuts.unit_tests WHERE name = _name;

  RETURN retval;
END //

--
-- FUNCTION: cuts.get_qualified_variable_name
--

DROP FUNCTION IF EXISTS cuts.get_qualified_variable_name //

CREATE FUNCTION cuts.get_qualified_variable_name (var_ INT)
  RETURNS VARCHAR (256)
BEGIN
  DECLARE retval VARCHAR (256);

  SELECT CONCAT('LF', CAST(lfid AS CHAR), '.', varname) AS fq_name
    INTO retval
    FROM cuts.log_format_variables
    WHERE variable_id = var_;

  RETURN retval;
END //

DROP FUNCTION IF EXISTS cuts.get_variable_owner //

CREATE FUNCTION cuts.get_variable_owner (varid_ INT)
  RETURNS VARCHAR (64)
BEGIN
  DECLARE retval VARCHAR (64);

  SELECT CONCAT('LF', CAST(lfid AS CHAR))
    INTO retval
    FROM cuts.log_format_variables
    WHERE variable_id = varid_;

  return retval;
END //

DROP PROCEDURE IF EXISTS cuts.select_unit_test_variables //

CREATE PROCEDURE cuts.select_unit_test_variables (IN utid_ INT)
BEGIN
  SELECT
    lfid, vartype, varname, CONCAT('LF', CAST(lfid AS CHAR), '.', varname) AS fq_name
    FROM cuts.log_format_variables
    WHERE lfid IN (SELECT lfid FROM cuts.unit_test_log_formats WHERE utid = utid_);
END //

DROP PROCEDURE IF EXISTS cuts.select_unit_test_relations_as_set //

CREATE PROCEDURE cuts.select_unit_test_relations_as_set (IN utid_ INT)
BEGIN
  SELECT relid,
         rel_index,
         cuts.get_qualified_variable_name (variable_id) AS lhs,
         cuts.get_qualified_variable_name (variable_id_2) AS rhs
    FROM cuts.unit_test_relations
    WHERE utid = utid_
    ORDER BY relid, rel_index;
END //

DROP PROCEDURE IF EXISTS cuts.select_unit_test_relations_as_sql //

CREATE PROCEDURE cuts.select_unit_test_relations_as_sql (IN utid_ INT)
BEGIN
  SELECT CONCAT(cuts.get_qualified_variable_name (variable_id),
                ' = ',
                cuts.get_qualified_variable_name (variable_id_2)) AS relation
    FROM cuts.unit_test_relations
    WHERE utid = utid_;
END //

--
-- PROCEDURE: cuts.insert_unit_test_relation
--

DROP PROCEDURE IF EXISTS cuts.insert_unit_test_relation //

CREATE PROCEDURE
  cuts.insert_unit_test_relation (IN _name VARCHAR(45),
                                  IN _relid INT,
                                  IN _index INT,
                                  IN _lfid_cause INT,
                                  IN _varname_cause VARCHAR(45),
                                  IN _lfid_effect INT,
                                  IN _varname_effect VARCHAR(45))
BEGIN
  INSERT INTO cuts.unit_test_relations (utid, relid, rel_index, variable_id, variable_id_2)
    VALUES (cuts.get_unit_test_id (_name),
            _relid,
            _index,
            cuts.get_log_format_variable_id (_lfid_cause, _varname_cause),
            cuts.get_log_format_variable_id (_lfid_effect, _varname_effect));
END //

--
-- PROCEDURE: cuts.insert_log_format
--

DROP PROCEDURE IF EXISTS cuts.insert_log_format //

CREATE PROCEDURE cuts.insert_log_format (IN _format TEXT,
                                         IN _mysql_regex TEXT,
                                         IN _csharp_regex TEXT)
BEGIN
  INSERT INTO cuts.log_formats (lfmt, icase_regex, csharp_regex)
    VALUES (_format, _mysql_regex, _csharp_regex);

  SELECT LAST_INSERT_ID() AS lfid;
END //


DROP PROCEDURE IF EXISTS cuts.insert_log_format_variable//
CREATE PROCEDURE
  cuts.insert_log_format_variable(IN id INT,
                          IN name VARCHAR(45),
                          IN vtype VARCHAR(45))
BEGIN
    INSERT INTO log_format_variables (lfid, varname, vartype) VALUES (id,name,vtype);
END //


-- given package id and utid - inserts unit test in package
DROP PROCEDURE IF EXISTS cuts.insert_package_unit_test//
CREATE PROCEDURE
  cuts.insert_package_unit_test(IN id_in integer,
                                IN utid_in integer)
BEGIN
      insert into package_unit_tests (id, ut_id) values (id_in, utid_in);
END //

-- given a name, it inserts that as a test suite

DROP PROCEDURE IF EXISTS cuts.insert_test_suite//
CREATE PROCEDURE
  cuts.insert_test_suite(IN name_in VARCHAR(65))
BEGIN
    Insert into test_suites (name) values (name_in);
END //


-- given a test suite id and name, this inserts the name as a new package, and then inserts that package into the test suite

DROP PROCEDURE IF EXISTS cuts.insert_test_suite_package //

CREATE PROCEDURE
  cuts.insert_test_suite_package (IN _tsid INT,
                                  IN _name VARCHAR(65))
BEGIN
  INSERT INTO cuts.test_suite_packages (tsid, tpid)
    VALUES (_tsid,
            cuts.get_test_package_id (_name));
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

DROP PROCEDURE IF EXISTS cuts.insert_unit_test //

CREATE PROCEDURE cuts.insert_unit_test (IN name_in VARCHAR(45),
                                        IN descr VARCHAR(95),
                                        IN eval TEXT,
                                        IN aggr VARCHAR(25))
BEGIN
  INSERT INTO cuts.unit_tests (name, description, evaluation, aggregration_function)
    VALUES (name_in, descr, eval, aggr);
END //

--
-- cuts.get_test_suite_id
--

DROP FUNCTION IF EXISTS cuts.get_test_suite_id //

CREATE FUNCTION cuts.get_test_suite_id (_name VARCHAR (256))
  RETURNS INT
BEGIN
  DECLARE retval INT;

  SELECT id INTO retval FROM cuts.test_suites WHERE name = _name;

  RETURN retval;
END //

--
-- cuts.select_test_suite_manifest
--

DROP PROCEDURE IF EXISTS cuts.select_test_suite_manifest //

CREATE PROCEDURE cuts.select_test_suite_manifest (IN _name VARCHAR (256))
BEGIN
  CALL cuts.select_test_suite_manifest_i (cuts.get_test_suite_id (_name));
END //

--
-- cuts.select_test_suite_manifest_i
--

DROP PROCEDURE IF EXISTS cuts.select_test_suite_manifest_i //

CREATE PROCEDURE cuts.select_test_suite_manifest_i (IN _id INT)
BEGIN
  SELECT t1.id AS test_suite_id,
         t1.name AS test_suite_name,
         t3.id AS package_id,
         t3.name AS package_name,
         t5.utid AS unit_test_id,
         t5.name AS unit_test_name,
         t5.description AS description,
         t5.evaluation AS evaluation,
         t5.aggregration_function AS aggr_func
    FROM cuts.test_suites AS t1,
         cuts.test_suite_packages AS t2,
         cuts.packages AS t3,
         cuts.package_unit_tests AS t4,
         cuts.unit_tests AS t5
    WHERE t1.id = _id AND
          t1.id = t2.id AND t2.p_id = t3.id AND t3.id = t4.id AND  t4.ut_id = t5.utid
    ORDER BY t1.name, t3.name, t5.name;
END //

--
-- cuts.select_unit_tests_in_test_suite
--

DROP PROCEDURE IF EXISTS cuts.select_unit_tests_in_test_suite //

CREATE PROCEDURE cuts.select_unit_tests_in_test_suite (IN _name VARCHAR (256))
BEGIN
  CALL cuts.select_unit_tests_in_test_suite_i (cuts.get_test_suite_id (_name));
END //

--
-- PROCEDURE: cuts.select_unit_tests_in_test_suite_i
--

DROP PROCEDURE IF EXISTS cuts.select_unit_tests_in_test_suite_i //

CREATE PROCEDURE cuts.select_unit_tests_in_test_suite_i (IN _tsid INT)
BEGIN
  SELECT * FROM cuts.unit_tests WHERE utid IN (
    SELECT ut_id FROM cuts.package_unit_tests WHERE id IN (
      SELECT p_id FROM cuts.test_suite_packages WHERE id = _tsid));
END //

-- given utid and lfid, add log format to ut

DROP PROCEDURE IF EXISTS cuts.insert_unit_test_log_format //

CREATE PROCEDURE
  cuts.insert_unit_test_log_format (IN _name VARCHAR(45),
                                    IN _lfid INT)
BEGIN
  CALL cuts.insert_unit_test_log_format_i (cuts.get_unit_test_id (_name), _lfid);
END //

--
-- PROCEDURE: cuts.insert_unit_test_log_format_i
--

DROP PROCEDURE IF EXISTS cuts.insert_unit_test_log_format_i //
CREATE PROCEDURE
  cuts.insert_unit_test_log_format_i (IN _utid INT,
                                      IN _lfid INT)
BEGIN
    INSERT INTO cuts.unit_test_log_formats (utid, lfid)
      VALUES (_utid, _lfid);
END //

--
-- PROCEDURE: cuts.select_log_format_variable_details_all
--
DROP PROCEDURE IF EXISTS cuts.select_log_format_variable_details_all //

CREATE PROCEDURE cuts.select_log_format_variable_details_all ()
BEGIN
  SELECT *, CONCAT('LF', CAST(lfid AS CHAR), '.', varname) AS fq_name
    FROM cuts.log_format_variables
    ORDER BY fq_name;
END //

--
-- PROCEDURE: cuts.insert_unit_test_grouping
--

DROP PROCEDURE IF EXISTS cuts.insert_unit_test_grouping //

CREATE PROCEDURE cuts.insert_unit_test_grouping (IN _testname VARCHAR(45),
                                                 IN _index INT,
                                                 IN _lfid INT,
                                                 IN _varname VARCHAR(45))
BEGIN
  INSERT INTO cuts.unit_test_groupings (utid, grpindex, varid)
    VALUES (cuts.get_unit_test_id (_testname),
            _index,
            cuts.get_log_format_variable_id (_lfid, _varname));
END //

--
-- PROCEDURE: cuts.select_unit_test_grouping
--

DROP PROCEDURE IF EXISTS cuts.select_unit_test_grouping //

CREATE PROCEDURE cuts.select_unit_test_grouping (IN _utid INT)
BEGIN
  SELECT grpindex, cuts.get_qualified_variable_name (varid) AS fq_name
    FROM cuts.unit_Test_groupings
    WHERE utid = _utid
    ORDER BY grpindex;
END //

DELIMITER ;
