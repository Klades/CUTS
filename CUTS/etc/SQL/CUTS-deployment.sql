--
-- @file        CUTS-deployment.sql
--
-- $Id: CUTS-baseline.sql 1114 2007-02-01 23:55:29Z hillj $
--
-- @author      James H. Hill
--

USE cuts;

--
-- Create the 'deployment' table. This table contains the location
-- uptime and downtime of a component instance per test.
--

CREATE TABLE IF NOT EXISTS deployment
(
  deploy_id         INT         NOT NULL auto_increment,
  test_number       INT         NOT NULL,
  instance          INT         NOT NULL,
  hostid            INT         NOT NULL,
  uptime            DATETIME,
  downtime          DATETIME,

  PRIMARY KEY (deploy_id),
  UNIQUE (test_number, instance, hostid),

  FOREIGN KEY (test_number) REFERENCES tests (test_number)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,
  FOREIGN KEY (instance) REFERENCES component_instances (instid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,
  FOREIGN KEY (hostid) REFERENCES ipaddr_host_map (hostid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);

DELIMITER //

-- -----------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_component_instance_uptime
-- -----------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_component_instance_uptime //

CREATE PROCEDURE
  cuts.insert_component_instance_uptime (IN _test_number INT,
                                         IN _instance VARCHAR(255),
                                         IN _hostid INT)
BEGIN
  INSERT INTO cuts.deployment (test_number, instance, hostid, uptime)
    VALUES (_test_number,
            cuts.get_component_instance_id (_instance),
            _hostid,
            NOW());
END; //

-- -----------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_component_instance_uptime_by_hostname
-- -----------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_component_instance_uptime_by_hostname //

CREATE PROCEDURE
  cuts.insert_component_instance_uptime_by_hostname (IN _test_number INT,
                                                     IN _instance VARCHAR(255),
                                                     IN _hostname VARCHAR(255))
BEGIN
  CALL cuts.insert_component_instance_uptime (_test_number,
                                              _instance,
                                              cuts.get_hostname_id (_hostname));
END; //

-- -----------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_component_instance_uptime_by_ipaddr
-- -----------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_component_instance_uptime_by_ipaddr //

CREATE PROCEDURE
  cuts.insert_component_instance_uptime_by_ipaddr (IN _test_number INT,
                                                   IN _instance VARCHAR(255),
                                                   IN _ipaddr VARCHAR(255))
BEGIN
  CALL cuts.insert_component_instance_uptime (_test_number,
                                              _instance,
                                              cuts.get_ipddr_id (_ipaddr));
END; //

-- -----------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_component_instance_downtime
-- -----------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_component_instance_downtime //

CREATE PROCEDURE
  cuts.insert_component_instance_downtime (IN _test_number INT,
                                           IN _instance VARCHAR(255),
                                           IN _hostid INT)
BEGIN
  UPDATE cuts.deployment
    SET downtime = NOW ()
    WHERE test_number = _test_number AND
          instance = cuts.get_component_instance_id (_instance) AND
          hostid = _hostid;
END; //

-- -----------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_component_instance_downtime_by_hostname
-- -----------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_component_instance_downtime_by_hostname //

CREATE PROCEDURE
  cuts.insert_component_instance_downtime_by_hostname (IN _test_number INT,
                                                       IN _instance VARCHAR(255),
                                                       IN _hostname VARCHAR(255))
BEGIN
  CALL cuts.insert_component_instance_downtime (_test_number,
                                                _instance,
                                                cuts.get_hostname_id (_hostname));
END; //

-- -----------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_component_instance_downtime_by_ipaddr
-- -----------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_component_instance_downtime_by_ipaddr //

CREATE PROCEDURE
  cuts.insert_component_instance_downtime_by_ipaddr (IN _test_number INT,
                                                     IN _instance VARCHAR(255),
                                                     IN _ipaddr VARCHAR(255))
BEGIN
  CALL cuts.insert_component_instance_downtime (_test_number,
                                                _instance,
                                                cuts.get_ipaddr_id (_ipaddr));
END; //

/*
-------------------------------------------------------------------------------
-- PROCEDURE: cuts.set_component_uptime
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.set_component_uptime //

CREATE PROCEDURE
  cuts.set_component_uptime (IN test INT,
                             IN instance_name VARCHAR(255),
                             IN host INT)
BEGIN
  DECLARE inst_id INT;

  SELECT component_id INTO inst_id
    FROM component_instances WHERE component_name = instance_name;

  INSERT INTO cuts.deployment (test_number, instance, hostid, uptime)
    VALUES (test, inst_id, host, NOW());
END; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.set_component_uptime_using_hostname
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.set_component_uptime_using_hostname //

CREATE PROCEDURE
  cuts.set_component_uptime_using_hostname (IN test INT,
                                            IN instance_name VARCHAR(255),
                                            IN host VARCHAR(256))
BEGIN
  DECLARE hid INT;

  -- get the hostid for the hostname
  SELECT hostid INTO hid
    FROM ipaddr_host_map WHERE hostname = host;

  CALL set_component_uptime (test, instance_name, hid);
END; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.set_component_uptime_using_ipaddr
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.set_component_uptime_using_ipaddr //

CREATE PROCEDURE
  cuts.set_component_uptime_using_ipaddr (IN test INT,
                                          IN instance_name VARCHAR(255),
                                          IN ip VARCHAR(40))
BEGIN
  DECLARE hid INT;

  -- get the hostid for the ip-address
  SELECT hostid INTO hid
    FROM ipaddr_host_map WHERE ipaddr = ip;

  CALL set_component_uptime (test, instance_name, hid);
END; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.set_component_downtime
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.set_component_downtime //

CREATE PROCEDURE
  cuts.set_component_downtime (IN test INT,
                               IN instance_name VARCHAR(255),
                               IN host INT)
BEGIN
  DECLARE inst_id INT;

  SELECT component_id INTO inst_id
    FROM component_instances WHERE component_name = instance_name;

  UPDATE cuts.deployment SET downtime = NOW()
    WHERE test_number = test AND instance = inst_id AND
      hostid = host AND downtime IS NULL;
END; //


-------------------------------------------------------------------------------
-- PROCEDURE: cuts.set_component_downtime_using_hostname
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.set_component_downtime_using_hostname //

CREATE PROCEDURE
  cuts.set_component_downtime_using_hostname (IN test INT,
                                              IN instance_name VARCHAR(255),
                                              IN host VARCHAR(256))
BEGIN
  DECLARE hid INT;

  SELECT hostid INTO hid
    FROM ipaddr_host_map WHERE hostname = host;

  CALL set_component_downtime(test, instance_name, hid);
END; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.set_component_downtime_using_ipaddr
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.set_component_downtime_using_ipaddr //

CREATE PROCEDURE
  cuts.set_component_downtime_using_ipaddr (IN test INT,
                                            IN instance_name VARCHAR(255),
                                            IN ip VARCHAR(40))
BEGIN
  DECLARE hid INT;

  SELECT hostid INTO hid
    FROM ipaddr_host_map WHERE ipaddr = ip;

  CALL set_component_downtime(test, instance_name, hid);
END; //

-------------------------------------------------------------------------------
-- FUNCTION: cuts.get_component_instance_host_i
-------------------------------------------------------------------------------

DROP FUNCTION IF EXISTS
  cuts.get_component_instance_host_i //

CREATE FUNCTION
  cuts.get_component_instance_host_i (test INT, instance_id INT)
  RETURNS INT
BEGIN
  DECLARE hid INT;

  SELECT hostid INTO hid
    FROM cuts.deployment
    WHERE test_number = test AND instance_id = instance;

  RETURN hid;
END; //

*/

DELIMITER ;
