--
-- @file        CUTS-create.sql
--
-- $Id$
--
-- @author      James H. Hill
--

CREATE DATABASE IF NOT EXISTS cuts;
USE cuts;

--
-- Create the test table. This table contains the test
-- registration information to map/manage the information
-- contained in the exeuction_time table correctly.
--

CREATE TABLE IF NOT EXISTS tests
(
  test_number   INT             NOT NULL auto_increment,
  test_name     VARCHAR(255),
  test_uuid     VARCHAR(255),

  start_time    DATETIME,
  stop_time     DATETIME,

  status        ENUM ('inactive',
                      'active',
                      'complete'),

  -- set the contraints for the table
  PRIMARY KEY (test_number)
);

--
-- Create the table that contains the names of ports.
--

CREATE TABLE IF NOT EXISTS portnames
(
  pid          INT              NOT NULL auto_increment,
  portname     VARCHAR (255)    default NULL,

  PRIMARY KEY (pid),
  UNIQUE (portname)
);

--
-- Create the ports table. This table contains which ports
-- belong to what component types. It also contains the ports
-- type (i.e., facet, receptacle, & etc.).
--

CREATE TABLE IF NOT EXISTS porttypes
(
  pid              INT      NOT NULL auto_increment,
  port_type        ENUM ('facet', 'receptacle', 'sink', 'source') NOT NULL,
  port_name        INT      NOT NULL,

  -- set the constaints for the table
  PRIMARY KEY (pid),
  UNIQUE (port_type, port_name),

  FOREIGN KEY (port_name) REFERENCES portnames (pid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);

--
-- Create the table that contains all the component types.
-- We also initialize the table after we have created it.
--

CREATE TABLE IF NOT EXISTS component_typenames
(
  nameid     INT              NOT NULL auto_increment,
  typename   VARCHAR (255)    NOT NULL,

  PRIMARY KEY (nameid),
  UNIQUE (typename)
);

--
-- Create the table that contains all the component types.
-- We also initialize the table after we have created it.
--

CREATE TABLE IF NOT EXISTS component_types
(
  typeid     INT    NOT NULL auto_increment,
  typename   INT    NOT NULL,
  port       INT    NOT NULL,

  PRIMARY KEY (typeid),
  UNIQUE (typename, port),

  FOREIGN KEY (typename) REFERENCES component_typenames (nameid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,
  FOREIGN KEY (port) REFERENCES porttypes (pid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);

--
-- This table contains the mapping of UUIDs their appropriate
-- component name. The UUID is the primary key for the table
-- because no two components can have the same UUID regardless
-- of them being located in two totally different deployments,
-- or systems.
--

CREATE TABLE IF NOT EXISTS component_instances
(
  instid          INT             NOT NULL auto_increment,
  component_name  VARCHAR (512)   NOT NULL,
  typeid          INT             NOT NULL,

  PRIMARY KEY (instid),
  UNIQUE      (component_name),

  FOREIGN KEY (typeid) REFERENCES component_typenames (nameid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);

--
-- Table the contains the mapping of a IP-address to a
-- readable hostname. The port number contains the port
-- the node daemon is listening. We also initialize the
-- table with some values after we have created it.
--

CREATE TABLE IF NOT EXISTS ipaddr_host_map
(
  hostid      INT               NOT NULL auto_increment,
  ipaddr      VARCHAR (40)      NOT NULL,
  hostname    VARCHAR (255),
  portnum     INT(5)            DEFAULT NULL,

  PRIMARY KEY (hostid),
  UNIQUE (hostname)
);

--
-- Create the scratchpad table. This is the table the
-- database worker uses to perform its database
-- operations for the given workload.
--

CREATE TABLE IF NOT EXISTS scratchpad
(
  component_id    INT        NOT NULL,
  worktag         INT        NOT NULL,
  dataset         VARCHAR (255)
);

--
-- Create the 'users' table. This table contains login information
-- for users who are allowed to view the database.
--

CREATE TABLE IF NOT EXISTS users
(
  userid          INT             NOT NULL auto_increment,
  username        VARCHAR(50)     NOT NULL,
  password        TINYTEXT        NOT NULL,
  email           VARCHAR(50)     NOT NULL,
  admin           TINYINT(1)      NOT NULL DEFAULT 0,

  PRIMARY KEY (userid),
  UNIQUE (username)
);

--
-- create user 'cuts'
--

GRANT SELECT, UPDATE, DELETE, INSERT, EXECUTE
  ON cuts.*
  TO cuts@'%'
  IDENTIFIED BY 'cuts';

GRANT SELECT, UPDATE, DELETE, INSERT, EXECUTE
  ON cuts.*
  TO cuts@'localhost'
  IDENTIFIED BY 'cuts';

DELIMITER //

-- -----------------------------------------------------------------------------
-- FUNCTION: cuts.get_portname_id
-- -----------------------------------------------------------------------------

DROP FUNCTION IF EXISTS cuts.get_portname_id //

CREATE FUNCTION
  cuts.get_portname_id (pname VARCHAR (255))
  RETURNS INT
BEGIN
  DECLARE retval INT;

  DECLARE CONTINUE HANDLER FOR NOT FOUND
  BEGIN
    INSERT INTO portnames (portname) VALUES (pname);
    SET retval = LAST_INSERT_ID();
  END;

  SELECT pid INTO retval FROM portnames
    WHERE portname = pname LIMIT 1;

  RETURN retval;
END; //

-- -----------------------------------------------------------------------------
-- FUNCTION: cuts.get_port_id
-- -----------------------------------------------------------------------------

DROP FUNCTION IF EXISTS cuts.get_port_id //

CREATE FUNCTION
  cuts.get_port_id (ptype VARCHAR (40),
                    pname VARCHAR (255))
  RETURNS INT
BEGIN
  DECLARE retval INT;
  DECLARE nameid INT;

  DECLARE CONTINUE HANDLER FOR NOT FOUND
  BEGIN
    INSERT INTO porttypes (port_type, port_name) VALUES (ptype, nameid);
    SET retval = LAST_INSERT_ID();
  END;

  SET nameid = cuts.get_portname_id (pname);

  SELECT pid INTO retval FROM porttypes
    WHERE port_type = ptype AND port_name = nameid
    LIMIT 1;

  RETURN retval;
END; //

-- -----------------------------------------------------------------------------
-- FUNCTION: cuts.get_component_typename_id
-- -----------------------------------------------------------------------------

DROP FUNCTION IF EXISTS cuts.get_component_typename_id //

CREATE FUNCTION
  cuts.get_component_typename_id (name VARCHAR (255))
  RETURNS INT
BEGIN
  DECLARE retval INT;

  DECLARE CONTINUE HANDLER FOR NOT FOUND
  BEGIN
    INSERT INTO component_typenames (typename) VALUES (name);
    SET retval = LAST_INSERT_ID();
  END;

  SELECT nameid INTO retval FROM component_typenames
    WHERE typename = name LIMIT 1;

  RETURN retval;
END; //

-- -----------------------------------------------------------------------------
-- FUNCTION: cuts.get_component_instance_id
-- -----------------------------------------------------------------------------

DROP FUNCTION IF EXISTS cuts.get_component_instance_id //

CREATE FUNCTION
  cuts.get_component_instance_id (name VARCHAR (255))
  RETURNS INT
BEGIN
  DECLARE retval INT;

  DECLARE CONTINUE HANDLER FOR NOT FOUND
  BEGIN
    RETURN NULL;
  END;

  SELECT instid INTO retval FROM component_instances
    WHERE component_name = name LIMIT 1;

  RETURN retval;
END; //

-- -----------------------------------------------------------------------------
-- FUNCTION: cuts.get_hostname_id
-- -----------------------------------------------------------------------------

DROP FUNCTION IF EXISTS cuts.get_hostname_id //

CREATE FUNCTION
  cuts.get_hostname_id (name VARCHAR (255))
  RETURNS INT
BEGIN
  DECLARE retval INT;

  DECLARE CONTINUE HANDLER FOR NOT FOUND
  BEGIN
    RETURN NULL;
  END;

  SELECT hostid INTO retval FROM cuts.ipaddr_host_map
    WHERE hostname = name LIMIT 1;

  RETURN retval;
END; //

-- -----------------------------------------------------------------------------
-- FUNCTION: cuts.get_ipaddr_id
-- -----------------------------------------------------------------------------

DROP FUNCTION IF EXISTS cuts.get_ipaddr_id //

CREATE FUNCTION
  cuts.get_ipaddr_id (ipaddr VARCHAR (255))
  RETURNS INT
BEGIN
  DECLARE retval INT;

  DECLARE CONTINUE HANDLER FOR NOT FOUND
  BEGIN
    RETURN NULL;
  END;

  SELECT hostid INTO retval FROM cuts.ipaddr_host_map
    WHERE ipaddr = ipaddr LIMIT 1;

  RETURN retval;
END; //

-- -----------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_component_type_info
-- -----------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_component_typeinfo //

CREATE PROCEDURE
  cuts.insert_component_typeinfo (IN ctype VARCHAR (255),
                                  IN ptype VARCHAR (40),
                                  IN pname VARCHAR (255))
BEGIN
  DECLARE EXIT HANDLER FOR SQLSTATE '23000'
  BEGIN

  END;

  INSERT INTO cuts.component_types (typename, port)
    VALUES (cuts.get_component_typename_id (ctype),
            cuts.get_port_id (ptype, pname));
END; //

-- -----------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_component_instance
-- -----------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_component_instance //

CREATE PROCEDURE
  cuts.insert_component_instance (IN cinst VARCHAR (255),
                                  IN ctype VARCHAR (255))
BEGIN
  DECLARE EXIT HANDLER FOR SQLSTATE '23000'
  BEGIN

  END;

  INSERT INTO cuts.component_instances (component_name, typeid)
    VALUES (cinst, cuts.get_component_typename_id (ctype));
END; //

-- -----------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_component_instance
-- -----------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_ipaddr_hostname //

CREATE PROCEDURE
  cuts.insert_ipaddr_hostname (IN ipaddr VARCHAR (255),
                               IN hostname VARCHAR (255))
BEGIN
  DECLARE EXIT HANDLER FOR SQLSTATE '23000'
  BEGIN

  END;

  INSERT INTO cuts.ipaddr_host_map (ipaddr, hostname)
    VALUES (ipaddr, hostname);
END; //

/*
-------------------------------------------------------------------------------
-- FUNCTION: cuts.component_portname
-------------------------------------------------------------------------------

DROP FUNCTION IF EXISTS cuts.component_portname //

CREATE FUNCTION cuts.component_portname (pid INT)
RETURNS VARCHAR (255)
BEGIN
  DECLARE portname VARCHAR (255);

  SELECT t2.portname INTO portname
    FROM ports AS t1, portnames AS t2
    WHERE t1.portid = t2.portid AND t1.pid = pid;

  RETURN portname;
END; //

-------------------------------------------------------------------------------
-- FUNCTION: cuts.get_component_name
-------------------------------------------------------------------------------

DROP FUNCTION IF EXISTS cuts.get_component_name //

CREATE FUNCTION cuts.get_component_name (id INT)
RETURNS VARCHAR (255)
BEGIN
  DECLARE instance VARCHAR (255);

  SELECT component_name INTO instance
    FROM component_instances WHERE component_id = id;

  RETURN instance;
END; //

-------------------------------------------------------------------------------
-- FUNCTION: cuts.get_component_instance_id
-------------------------------------------------------------------------------

DROP FUNCTION IF EXISTS cuts.get_component_instance_id //

CREATE FUNCTION
  cuts.get_component_instance_id (_instance VARCHAR (255))
  RETURNS INT
BEGIN
  DECLARE _id VARCHAR (255);

  SELECT component_id INTO _id FROM component_instances
    WHERE component_name = _instance;

  RETURN id;
END; //

-------------------------------------------------------------------------------
-- FUNCTION: cuts.get_portname_id
-------------------------------------------------------------------------------

DROP FUNCTION IF EXISTS cuts.get_portname_id //

CREATE FUNCTION
  cuts.get_portname_id (_portname VARCHAR (255))
  RETURNS INT
BEGIN
  DECLARE _id INT;

  SELECT portid INTO _id FROM portnames
    WHERE portname = _portname;

  RETURN _id;
END; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.select_component_info_i
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS
  cuts.select_component_info_i //

CREATE PROCEDURE
  cuts.select_component_info_i (IN inst_id INT)
BEGIN
  SELECT t5.*, t6.portname FROM
    (SELECT t3.*, t4.pid, t4.portid, t4.port_type FROM
      (SELECT t1.*, t2.typename FROM component_instances AS t1
        LEFT JOIN component_types AS t2 ON t1.typeid = t2.typeid
        WHERE t1.component_id = inst_id) AS t3
      LEFT JOIN ports AS t4 ON t3.typeid = t4.ctype) AS t5
    LEFT JOIN portnames AS t6 ON t5.portid = t6.portid;
END; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.select_component_portnames_i
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS
  cuts.select_component_portnames_i //

CREATE PROCEDURE
  cuts.select_component_portnames_i (IN inst_id INT,
                                     IN porttype VARCHAR(20))
BEGIN
  SELECT t5.pid, t6.portname FROM
    (SELECT t3.*, t4.pid, t4.portid, t4.port_type FROM
      (SELECT t1.*, t2.typename FROM component_instances AS t1
        LEFT JOIN component_types AS t2 ON t1.typeid = t2.typeid
        WHERE t1.component_id = inst_id) AS t3
      LEFT JOIN ports AS t4 ON t3.typeid = t4.ctype
      WHERE t4.port_type = porttype) AS t5
    LEFT JOIN portnames AS t6 ON t5.portid = t6.portid;
END; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.select_component_portnames_i
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS
  cuts.select_component_portnames //

CREATE PROCEDURE
  cuts.select_component_portnames (IN instance VARCHAR(255),
                                   IN porttype VARCHAR(20))
BEGIN
  DECLARE inst_id INT;

  SELECT component_id INTO inst_id FROM component_instances
    WHERE component_name = instance;

  CALL cuts.select_component_portnames_i (inst_id, porttype);
END; //

-------------------------------------------------------------------------------
-- FUNCTION: cuts.get_port_id
-------------------------------------------------------------------------------

DROP FUNCTION IF EXISTS
  cuts.get_port_id //

CREATE FUNCTION cuts.get_port_id (_instance VARCHAR (255),
                                  _portname VARCHAR (255),
                                  _porttype VARCHAR (255))
  RETURNS INT
BEGIN
  DECLARE _pid INT;
  DECLARE _portid INT;

  SELECT portid INTO _portid FROM portnames
    WHERE portname = _port_name;

  SELECT pid INTO _pid FROM ports
    WHERE ctype = cuts.get_component_instance_id (_instance) AND
      portid = cuts.get_portname_id (_portname) AND port_type = _porttype;

  RETURN _pid;
END; //
*/

DELIMITER ;