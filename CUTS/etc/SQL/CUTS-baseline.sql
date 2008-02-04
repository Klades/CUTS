--
-- @file        CUTS-baseline.sql
--
-- $Id$
--
-- @author      James H. Hill
--

USE cuts;

--
-- Create the performance_baseline table for endpoints. This table
-- contains performance_baseline metric information to each component
-- instance type per host.
--

CREATE TABLE IF NOT EXISTS performance_endpoint_baseline
(
  bid               INT NOT NULL auto_increment,

  -- component information
  host              INT,
  instance          INT NOT NULL,
  inport            INT NOT NULL,

  -- in case we have multiple outport (or sends) on the same port
  outport_index     INT NOT NULL,
  outport           INT NOT NULL,

  perf_count        INT NOT NULL,
  best_time         INT NOT NULL default 0,
  worst_time        INT NOT NULL default 0,
  total_time        INT NOT NULL default 0,

  -- define the unique entries in the table to prevent duplicates
  PRIMARY KEY (bid),
  UNIQUE (host, instance, inport, outport_index, outport),

  -- define all the foreign keys in the table
  FOREIGN KEY (instance) REFERENCES component_instances (instid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,
  FOREIGN KEY (host) REFERENCES ipaddr_host_map (hostid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,
  FOREIGN KEY (inport) REFERENCES porttypes (pid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,
  FOREIGN KEY (outport) REFERENCES porttypes (pid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);

--
-- Create the performance_baseline table for summaries. This table
-- contains performance_baseline metric information to each component
-- instance type per host.
--

CREATE TABLE IF NOT EXISTS performance_baseline
(
  bid               INT NOT NULL auto_increment,

  -- component information
  host              INT,
  instance          INT NOT NULL,
  inport            INT NOT NULL,

  -- performance information
  perf_type         ENUM ('transit',
                          'queue',
                          'process')  NOT NULL,

  perf_count        INT NOT NULL default 0,
  best_time         INT NOT NULL default 0,
  worst_time        INT NOT NULL default 0,
  total_time        INT NOT NULL default 0,

  -- define the unique entries in the table to prevent duplicates
  PRIMARY KEY (bid),
  UNIQUE (host, instance, inport, perf_type),

  -- define all the foreign keys in the table
  FOREIGN KEY (instance) REFERENCES component_instances (instid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,
  FOREIGN KEY (host) REFERENCES ipaddr_host_map (hostid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,
  FOREIGN KEY (inport) REFERENCES porttypes (pid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);

DELIMITER //

-- -----------------------------------------------------------------------------
-- FUNCTION: cuts.get_component_baseline_id
-- -----------------------------------------------------------------------------

DROP FUNCTION IF EXISTS cuts.get_component_instance_baseline_id //

CREATE FUNCTION cuts.get_component_instance_baseline_id (hostid INT,
                                                         instid INT,
                                                         iid INT,
                                                         ptype VARCHAR (40))
  RETURNS INT
BEGIN
  DECLARE retval INT;

  DECLARE CONTINUE HANDLER FOR NOT FOUND RETURN NULL;

  IF (hostid IS NULL) THEN
    SELECT t1.bid INTO retval FROM cuts.performance_baseline AS t1
      WHERE t1.host IS NULL AND t1.instance = instid AND
            t1.inport = iid AND t1.perf_type = ptype
      LIMIT 1;
  ELSE
    SELECT t1.bid INTO retval FROM cuts.performance_baseline AS t1
      WHERE t1.host = hostid AND t1.instance = instid AND
            t1.inport = iid AND t1.perf_type = ptype
      LIMIT 1;
  END IF;

  RETURN retval;
END; //

-- -----------------------------------------------------------------------------
-- FUNCTION: cuts.get_component_instance_endpoint_baseline_id
-- -----------------------------------------------------------------------------

DROP FUNCTION IF EXISTS cuts.get_component_instance_endpoint_baseline_id //

CREATE FUNCTION
  cuts.get_component_instance_endpoint_baseline_id (_hostid INT,
                                                    _instid INT,
                                                    _iid INT,
                                                    _outport_index INT,
                                                    _oid INT)
  RETURNS INT
BEGIN
  DECLARE retval INT;

  DECLARE CONTINUE HANDLER FOR NOT FOUND RETURN NULL;

  IF (_hostid IS NULL) THEN
    SELECT t1.bid INTO retval FROM cuts.performance_endpoint_baseline AS t1
      WHERE t1.host IS NULL AND t1.instance = _instid AND
            t1.inport = _iid AND t1.outport_index = _outport_index AND
            t1.outport = _oid
      LIMIT 1;
  ELSE
    SELECT t1.bid INTO retval FROM cuts.performance_endpoint_baseline AS t1
      WHERE t1.host = _hostid AND t1.instance = _instid AND
            t1.inport = _iid AND t1.outport_index = _outport_index AND
            t1.outport = _oid
      LIMIT 1;
  END IF;

  RETURN retval;
END; //

-- -----------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_component_instance_baseline
-- -----------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_component_instance_baseline //

CREATE PROCEDURE
  cuts.insert_component_instance_baseline (IN _hostid INT,
                                           IN _instance VARCHAR (255),
                                           IN _inport VARCHAR (255),
                                           IN _perf_type VARCHAR (40),
                                           IN _perf_count INT,
                                           IN _best_time INT,
                                           IN _worst_time INT,
                                           IN _total_time INT)
BEGIN
  DECLARE instid INT;
  DECLARE iid INT;
  DECLARE mybid INT;

  /*
   * The following functions will not throw a NOT FOUND
   * error.
   */
  SET instid = cuts.get_component_instance_id (_instance);
  SET iid = cuts.get_port_id ('sink', _inport);

  /*
   * Get the baseline id for the metrics. If there isn't a
   * baseline id, then we are going to insert a new one. This
   * is handled by the continue handler!!
   */
  SET mybid = cuts.get_component_instance_baseline_id (_hostid,
                                                       instid,
                                                       iid,
                                                       _perf_type);

  IF mybid IS NULL THEN
    INSERT INTO cuts.performance_baseline (host, instance, inport, perf_type,
                                           perf_count, best_time, worst_time,
                                           total_time)
      VALUES (_hostid, instid, iid, _perf_type, _perf_count,
              _best_time, _worst_time, _total_time);
  ELSE
    /*
     * Update an existing performance_baseline metric.
     */
    UPDATE cuts.performance_baseline
      SET perf_count = _perf_count, best_time = _best_time,
          worst_time = _worst_time, total_time = _total_time
      WHERE bid = mybid;
  END IF;
END; //

-- -----------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_component_instance_baseline
-- -----------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_component_instance_endpoint_baseline //

CREATE PROCEDURE
  cuts.insert_component_instance_endpoint_baseline (IN _hostid INT,
                                                    IN _instance VARCHAR (255),
                                                    IN _inport VARCHAR (255),
                                                    IN _outport_index INT,
                                                    IN _outport VARCHAR (40),
                                                    IN _perf_count INT,
                                                    IN _best_time INT,
                                                    IN _worst_time INT,
                                                    IN _total_time INT)
BEGIN
  DECLARE instid INT;
  DECLARE iid INT;
  DECLARE oid INT;
  DECLARE mybid INT;

  /*
   * The following functions will not throw a NOT FOUND
   * error.
   */
  SET instid = cuts.get_component_instance_id (_instance);
  SET iid = cuts.get_port_id ('sink', _inport);
  SET oid = cuts.get_port_id ('source', _outport);

  /*
   * Get the baseline id for the metrics. If there isn't a
   * baseline id, then we are going to insert a new one.
   */
  SET mybid =
    cuts.get_component_instance_endpoint_baseline_id (_hostid,
                                                      instid,
                                                      iid,
                                                      _outport_index,
                                                      oid);

  IF mybid IS NULL THEN
    INSERT INTO cuts.performance_endpoint_baseline (
      host, instance, inport, outport_index, outport,
      perf_count, best_time, worst_time, total_time)
      VALUES (_hostid, instid, iid, _outport_index, oid,
              _perf_count, _best_time, _worst_time, _total_time);
  ELSE
    /*
     * Update an existing performance_baseline metric.
     */
    UPDATE cuts.performance_endpoint_baseline
      SET perf_count = _perf_count, best_time = _best_time,
          worst_time = _worst_time, total_time = _total_time
      WHERE bid = mybid;
  END IF;
END; //

-- -----------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_component_instance_baseline_by_ipaddr
-- -----------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_component_instance_baseline_by_ipaddr //

CREATE PROCEDURE
  cuts.insert_component_instance_baseline_by_ipaddr (IN ipaddr VARCHAR (40),
                                                     IN instance VARCHAR (255),
                                                     IN inport VARCHAR (255),
                                                     IN perf_type VARCHAR (40),
                                                     IN perf_count INT,
                                                     IN best_time INT,
                                                     IN worst_time INT,
                                                     IN total_time INT)
BEGIN
  CALL insert_component_instance_baseline (cuts.get_ipaddr_id (ipaddr),
                                           instance,
                                           inport,
                                           perf_type,
                                           perf_count,
                                           best_time,
                                           worst_time,
                                           total_time);
END; //

-- -----------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_component_instance_endpoint_baseline_by_ipaddr
-- -----------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_component_instance_endpoint_baseline_by_ipaddr //

CREATE PROCEDURE
  cuts.
  insert_component_instance_endpoint_baseline_by_ipaddr (IN _ipaddr VARCHAR (255),
                                                         IN _instance VARCHAR (255),
                                                         IN _inport VARCHAR (255),
                                                         IN _outport_index INT,
                                                         IN _outport VARCHAR (40),
                                                         IN _perf_count INT,
                                                         IN _best_time INT,
                                                         IN _worst_time INT,
                                                         IN _total_time INT)
BEGIN
  CALL insert_component_instance_endpoint_baseline (cuts.get_ipaddr_id (_ipaddr),
                                                    _instance,
                                                    _inport,
                                                    _outport_index,
                                                    _outport,
                                                    _perf_count,
                                                    _best_time,
                                                    _worst_time,
                                                    _total_time);
END; //

-- -----------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_component_instance_baseline_by_hostname
-- -----------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_component_instance_baseline_by_hostname //

CREATE PROCEDURE
  cuts.insert_component_instance_baseline_by_hostname (IN hostname VARCHAR (255),
                                                       IN instance VARCHAR (255),
                                                       IN inport VARCHAR (255),
                                                       IN perf_type VARCHAR (40),
                                                       IN perf_count INT,
                                                       IN best_time INT,
                                                       IN worst_time INT,
                                                       IN total_time INT)
BEGIN
  CALL insert_component_instance_baseline (cuts.get_hostname_id (hostname),
                                           instance,
                                           inport,
                                           perf_type,
                                           perf_count,
                                           best_time,
                                           worst_time,
                                           total_time);
END; //

-- -----------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_component_instance_endpoint_baseline_by_hostname
-- -----------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_component_instance_endpoint_baseline_by_hostname //

CREATE PROCEDURE
  cuts.
  insert_component_instance_endpoint_baseline_by_hostname (IN _hostname VARCHAR (255),
                                                           IN _instance VARCHAR (255),
                                                           IN _inport VARCHAR (255),
                                                           IN _outport_index INT,
                                                           IN _outport VARCHAR (40),
                                                           IN _perf_count INT,
                                                           IN _best_time INT,
                                                           IN _worst_time INT,
                                                           IN _total_time INT)
BEGIN
  CALL insert_component_instance_endpoint_baseline (cuts.get_hostname_id (_hostname),
                                                    _instance,
                                                    _inport,
                                                    _outport_index,
                                                    _outport,
                                                    _perf_count,
                                                    _best_time,
                                                    _worst_time,
                                                    _total_time);
END; //

-- -----------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_component_instance_baseline_default
-- -----------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_component_instance_baseline_default //

CREATE PROCEDURE
  cuts.insert_component_instance_baseline_default (IN instance VARCHAR (255),
                                                   IN inport VARCHAR (255),
                                                   IN perf_type VARCHAR (40),
                                                   IN perf_count INT,
                                                   IN best_time INT,
                                                   IN worst_time INT,
                                                   IN total_time INT)
BEGIN
  CALL insert_component_instance_baseline (NULL,
                                           instance,
                                           inport,
                                           perf_type,
                                           perf_count,
                                           best_time,
                                           worst_time,
                                           total_time);
END; //

-- -----------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_component_instance_endpoint_baseline_default
-- -----------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_component_instance_endpoint_baseline_default //

CREATE PROCEDURE
  cuts.
  insert_component_instance_endpoint_baseline_default (IN _instance VARCHAR (255),
                                                       IN _inport VARCHAR (255),
                                                       IN _outport_index INT,
                                                       IN _outport VARCHAR (40),
                                                       IN _perf_count INT,
                                                       IN _best_time INT,
                                                       IN _worst_time INT,
                                                       IN _total_time INT)
BEGIN
  CALL cuts.insert_component_instance_endpoint_baseline (NULL,
                                                         _instance,
                                                         _inport,
                                                         _outport_index,
                                                         _outport,
                                                         _perf_count,
                                                         _best_time,
                                                         _worst_time,
                                                         _total_time);
END; //
/*
-- -----------------------------------------------------------------------------
-- PROCEDURE: cuts.select_baseline_metrics_all
-- -----------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.select_performance_baseline_all //

CREATE PROCEDURE
  cuts.select_performance_baseline_all ()
BEGIN
  SELECT t7.*, t8.portname AS source FROM
    (SELECT t5.*, t6.portname AS sink FROM
      (SELECT t3.*, IFNULL(t4.hostname, '') AS hostname FROM
        (SELECT t1.*, (t1.total_time / t1.event_count) AS avg_time, t2.component_name
          FROM performance_baseline AS t1
          LEFT JOIN component_instances AS t2 ON t1.instance = t2.component_id) AS t3
        LEFT JOIN ipaddr_host_map AS t4 ON t3.host = t4.hostid) AS t5
      LEFT JOIN (SELECT pid, portname
        FROM ports, portnames
          WHERE ports.portid = portnames.portid) AS t6 ON t5.inport = t6.pid) AS t7
    LEFT JOIN (SELECT pid, portname
        FROM ports, portnames
          WHERE ports.portid = portnames.portid) AS t8 ON t7.outport = t8.pid
    ORDER BY component_name;
END; //
/*
-------------------------------------------------------------------------------
-- PROCEDURE: cuts.select_baseline_metric_for_test
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.select_baseline_metric_for_test //

CREATE PROCEDURE
  cuts.select_baseline_metric_for_test (IN test INT)
BEGIN
  SELECT DISTINCT t10.component, t9.* FROM execution_time AS t10
    LEFT JOIN (SELECT t7.*, t8.portname AS source FROM
      (SELECT t5.*, t6.portname AS sink FROM
        (SELECT t3.*, IFNULL(t4.hostname, '') AS hostname FROM
          (SELECT t1.*, (t1.total_time / t1.event_count) AS avg_time, t2.component_name
            FROM performance_baseline AS t1
            LEFT JOIN component_instances AS t2 ON t1.instance = t2.component_id) AS t3
          LEFT JOIN ipaddr_host_map AS t4 ON t3.host = t4.hostid) AS t5
        LEFT JOIN (SELECT pid, portname
          FROM ports, portnames
            WHERE ports.portid = portnames.portid) AS t6 ON t5.inport = t6.pid) AS t7
      LEFT JOIN (SELECT pid, portname
          FROM ports, portnames
            WHERE ports.portid = portnames.portid) AS t8 ON t7.outport = t8.pid) AS t9
      ON t9.instance = t10.component
      WHERE t10.test_number = test
      ORDER BY component_name;
END; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.select_baseline_metric_for_test_by_time
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.select_baseline_metric_for_test_by_time //

CREATE PROCEDURE
  cuts.select_baseline_metric_for_test_by_time (IN test INT,
                                                IN coll DATETIME)
BEGIN
  SELECT DISTINCT t10.component, t9.* FROM execution_time AS t10
    LEFT JOIN (SELECT t7.*, t8.portname AS source FROM
      (SELECT t5.*, t6.portname AS sink FROM
        (SELECT t3.*, IFNULL(t4.hostname, '') AS hostname FROM
          (SELECT t1.*, (t1.total_time / t1.event_count) AS avg_time, t2.component_name
            FROM performance_baseline AS t1
            LEFT JOIN component_instances AS t2 ON t1.instance = t2.component_id) AS t3
          LEFT JOIN ipaddr_host_map AS t4 ON t3.host = t4.hostid) AS t5
        LEFT JOIN (SELECT pid, portname
          FROM ports, portnames
            WHERE ports.portid = portnames.portid) AS t6 ON t5.inport = t6.pid) AS t7
      LEFT JOIN (SELECT pid, portname
          FROM ports, portnames
            WHERE ports.portid = portnames.portid) AS t8 ON t7.outport = t8.pid) AS t9
      ON t9.instance = t10.component
      WHERE t10.test_number = test AND t10.collection_time = coll
      ORDER BY component_name;
END; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.select_baseline_metric
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.select_baseline_metric //

CREATE PROCEDURE
  cuts.select_baseline_metric (IN instance_name VARCHAR (255))
BEGIN
  SELECT t7.*, t8.portname AS source FROM
    (SELECT t5.*, t6.portname AS sink FROM
      (SELECT t3.*, IFNULL(t4.hostname, '') AS hostname FROM
        (SELECT t1.*, (t1.total_time / t1.event_count) AS avg_time, t2.component_name
          FROM performance_baseline AS t1
          LEFT JOIN component_instances AS t2 ON t1.instance = t2.component_id
          WHERE t2.component_name = instance_name) AS t3
        LEFT JOIN ipaddr_host_map AS t4 ON t3.host = t4.hostid) AS t5
      LEFT JOIN (SELECT pid, portname
        FROM ports, portnames
          WHERE ports.portid = portnames.portid) AS t6 ON t5.inport = t6.pid) AS t7
    LEFT JOIN (SELECT pid, portname
        FROM ports, portnames
          WHERE ports.portid = portnames.portid) AS t8 ON t7.outport = t8.pid;
END; //
*/

DELIMITER ;