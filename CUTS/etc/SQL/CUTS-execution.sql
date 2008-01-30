--
-- @file        CUTS-archive.sql
--
-- $Id: CUTS-create.sql 1127 2007-02-04 02:59:21Z hillj $
--
-- @author      James H. Hill
--

USE cuts;

--
-- Create the execution_time table. This table contains
-- the overall execution times for various paths in a
-- component. These paths can be sequences together to
-- determine the end-to-end execution time of a path in
-- a system
--

CREATE TABLE IF NOT EXISTS performance_endpoint
(
  test_number       INT         NOT NULL,
  collection_time   DATETIME    NOT NULL,

  -- component information
  instance          INT NOT NULL,
  sender            INT,
  inport            INT NOT NULL,

  -- in case we have multiple outport (or sends) on the same port
  outport_index     INT NOT NULL,
  outport           INT NOT NULL,

  perf_count        INT NOT NULL,
  best_time         INT NOT NULL default 0,
  worst_time        INT NOT NULL default 0,
  total_time        INT NOT NULL default 0,

  -- define the unique entries in the table to prevent duplicates
  UNIQUE (test_number, collection_time, instance, sender, inport, outport_index, outport),

  -- define all the foreign keys in the table
  FOREIGN KEY (test_number) REFERENCES tests (test_number)
    ON DELETE CASCADE,

  FOREIGN KEY (instance) REFERENCES component_instances (instid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,
  FOREIGN KEY (sender) REFERENCES component_instances (instid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,
  FOREIGN KEY (inport) REFERENCES porttypes (pid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,
  FOREIGN KEY (outport) REFERENCES porttypes (pid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS performance
(
  test_number       INT         NOT NULL,
  collection_time   DATETIME    NOT NULL,

  -- component information
  instance          INT NOT NULL,
  sender            INT,
  inport            INT NOT NULL,

  -- performance information
  perf_type       ENUM ('transit',
                        'queue',
                        'process')  NOT NULL,

  perf_count        INT NOT NULL,
  best_time         INT NOT NULL default 0,
  worst_time        INT NOT NULL default 0,
  total_time        INT NOT NULL default 0,

  INDEX (test_number),
  INDEX (collection_time),
  INDEX (test_number, collection_time),

  -- define the unique entries in the table to prevent duplicates
  UNIQUE (test_number, collection_time, instance, sender, inport, perf_type),

  -- define the foreign keys for data integrity
  FOREIGN KEY (test_number) REFERENCES tests (test_number)
    ON DELETE CASCADE,
  FOREIGN KEY (instance) REFERENCES component_instances (instid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,
  FOREIGN KEY (instance) REFERENCES component_instances (instid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);

-- Change the delimiter for creating the procedures. Failing
-- to change the delimit will result in the invalid execution
-- of the SQL statements below.

delimiter //

-- -----------------------------------------------------------------------------
-- FUNCTION: cuts.get_insert_execution_time
-- -----------------------------------------------------------------------------

DROP FUNCTION IF EXISTS cuts.get_max_collection_time //

CREATE FUNCTION
  cuts.get_max_collection_time (test INT)
  RETURNS DATETIME
BEGIN
  DECLARE retval DATETIME;

  SELECT MAX(collection_time) INTO retval
    FROM cuts.performance WHERE test_number = test;

  IF retval IS NULL THEN
    SET retval = NOW();
  END IF;

  RETURN retval;
END; //

/*
-------------------------------------------------------------------------------
-- FUNCTION: cuts.get_distinct_component_count
-------------------------------------------------------------------------------

DROP FUNCTION IF EXISTS cuts.get_distinct_component_count //

CREATE FUNCTION
  cuts.get_distinct_component_count (test INT,
                                     coll_time DATETIME)
RETURNS INT
BEGIN
  DECLARE distinct_count INT;

  SELECT COUNT(DISTINCT component) INTO distinct_count
    FROM cuts.performance
    WHERE test_number = test AND collection_time = coll_time;

  RETURN distinct_count;
END; //

*/
-- -----------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_component_instance_performance
-- -----------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_component_instance_performance //

CREATE PROCEDURE
  cuts.insert_component_instance_performance (IN test INT,
                                              IN collection DATETIME,
                                              IN inst VARCHAR (255),
                                              IN send VARCHAR (255),
                                              IN inport VARCHAR (255),
                                              IN p_type VARCHAR (40),
                                              IN p_count INT,
                                              IN best_time INT,
                                              IN worst_time INT,
                                              IN total_time INT)
BEGIN
  INSERT INTO cuts.performance (test_number,
                                collection_time,
                                instance,
                                sender,
                                inport,
                                perf_type,
                                perf_count,
                                best_time,
                                total_time,
                                worst_time)
   VALUES (test, collection,
           cuts.get_component_instance_id (inst),
           cuts.get_component_instance_id (send),
           cuts.get_port_id ('sink', inport),
           p_type, p_count, best_time, worst_time, total_time);
END; //

-- -----------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_component_instance_performance_endpoint
-- -----------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_component_instance_performance_endpoint //

CREATE PROCEDURE
  cuts.insert_component_instance_performance_endpoint (IN test INT,
                                                       IN collection DATETIME,
                                                       IN inst VARCHAR (255),
                                                       IN sender VARCHAR (255),
                                                       IN inport VARCHAR (255),
                                                       IN outport_index INT,
                                                       IN outport VARCHAR (255),
                                                       IN perf_count VARCHAR (40),
                                                       IN best_time INT,
                                                       IN worst_time INT,
                                                       IN total_time INT)
BEGIN
  INSERT INTO cuts.performance_endpoint (
    test_number, collection_time, instance, sender, inport,
    outport_index, outport, perf_count, best_time, total_time, worst_time)
    VALUES (test, collection,
            cuts.get_component_instance_id (inst),
            cuts.get_component_instance_id (sender),
            cuts.get_port_id ('sink', inport),
            outport_index,
            cuts.get_port_id ('source', outport),
            perf_count, best_time, worst_time, total_time);
END; //

/*
-------------------------------------------------------------------------------
-- PROCEDURE: cuts.select_execution_time
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS
  cuts.select_execution_time //

CREATE PROCEDURE
  cuts.select_execution_time (IN test INT, IN ctime DATETIME)
BEGIN
SELECT t13.*, t14.ipaddr, t14.hostname FROM
  (SELECT t11.*, t12.hostid FROM
    (SELECT t9.*, t10.portname AS dstname FROM
      (SELECT t4.*, t8.portname AS srcname FROM
        (SELECT t2.*, t3.component_name FROM
          (SELECT results.*, t1.component_name AS sender_name FROM
            (SELECT *, (total_time / metric_count) AS avg_time FROM execution_time AS e
              WHERE collection_time = ctime AND test_number = test) AS results
          LEFT JOIN component_instances AS t1
              ON t1.component_id = results.sender) AS t2
        LEFT JOIN component_instances AS t3 ON t2.component = t3.component_id) AS t4
      LEFT JOIN
        (SELECT pid, portname FROM ports AS t6, portnames AS t7
          WHERE t6.portid = t7.portid) AS t8 ON t8.pid = t4.src) AS t9
    LEFT JOIN
        (SELECT pid, portname FROM ports AS t11, portnames AS t12
          WHERE t11.portid = t12.portid) AS t10 ON t10.pid = t9.dst) AS t11
    LEFT JOIN deployment AS t12 ON t12.instance = t11.component AND t12.test_number = test) AS t13
  LEFT JOIN ipaddr_host_map AS t14 ON t13.hostid = t14.hostid
  ORDER BY t13.component_name, srcname, dstname;
END; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.select_distinct_collection_times
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS
  cuts.select_distinct_collection_times //

CREATE PROCEDURE
  cuts.select_distinct_collection_times (IN test INT)
BEGIN
  SELECT DISTINCT collection_time
    FROM execution_time  WHERE test_number = test;
END; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.select_execution_time_with_limits
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS
  cuts.select_execution_time_with_limits //

CREATE PROCEDURE
  cuts.select_execution_time_with_limits (IN test INT,
                                          IN ctime DATETIME,
                                          IN start_index INT,
                                          IN numrecs INT)
BEGIN
  SET @test = test;
  SET @collection_time = ctime;
  SET @offset = start_index;
  SET @rows = numrecs;

  -- prepare the statement for usage.
  PREPARE STMT FROM
    "SELECT t13.*, t14.ipaddr, t14.hostname FROM
      (SELECT t11.*, t12.hostid FROM
        (SELECT t9.*, t10.portname AS dstname FROM
          (SELECT t4.*, t8.portname AS srcname FROM
            (SELECT t2.*, t3.component_name FROM
              (SELECT results.*, t1.component_name AS sender_name FROM
                (SELECT *, (total_time / metric_count) AS avg_time FROM execution_time AS e
                  WHERE collection_time = ? AND test_number = ?) AS results
              LEFT JOIN component_instances AS t1
                  ON t1.component_id = results.sender) AS t2
            LEFT JOIN component_instances AS t3 ON t2.component = t3.component_id) AS t4
          LEFT JOIN
            (SELECT pid, portname FROM ports AS t6, portnames AS t7
              WHERE t6.portid = t7.portid) AS t8 ON t8.pid = t4.src) AS t9
        LEFT JOIN
            (SELECT pid, portname FROM ports AS t11, portnames AS t12
              WHERE t11.portid = t12.portid) AS t10 ON t10.pid = t9.dst) AS t11
        LEFT JOIN deployment AS t12 ON t12.instance = t11.component AND t12.test_number = ?) AS t13
      LEFT JOIN ipaddr_host_map AS t14 ON t13.hostid = t14.hostid
      ORDER BY t13.component_name, srcname, dstname LIMIT ?, ?";

  -- execute the statement using limits
  EXECUTE STMT USING @collection_time, @test, @test, @offset, @rows;
END; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.select_execution_time_ex
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS
  cuts.select_execution_time_ex //

CREATE PROCEDURE
  cuts.select_execution_time_ex (IN test INT, IN ctime DATETIME,
                                 IN cid INT, IN sender_id INT)
BEGIN
  SELECT t9.*, t10.portname AS dstname FROM
    (SELECT t4.*, t8.portname AS srcname FROM
      (SELECT t2.*, t3.component_name FROM
        (SELECT results.*, t1.component_name AS sender_name FROM
          (SELECT *, (total_time / metric_count) AS avg_time FROM execution_time AS e
             WHERE collection_time = ctime AND test_number = test
               AND component = cid AND sender = sender_id) AS results
         LEFT JOIN component_instances AS t1
             ON t1.component_id = results.sender) AS t2
      LEFT JOIN component_instances AS t3 ON t2.component = t3.component_id) AS t4
    LEFT JOIN
      (SELECT pid, portname FROM ports AS t6, portnames AS t7
         WHERE t6.portid = t7.portid) AS t8 ON t8.pid = t4.src) AS t9
  LEFT JOIN
      (SELECT pid, portname FROM ports AS t11, portnames AS t12
         WHERE t11.portid = t12.portid) AS t10 ON t10.pid = t9.dst;
END; //

-------------------------------------------------------------------------------
-- PROCEDURE: select_distinct_components_in_execution_time
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS
  cuts.select_distinct_components_in_execution_time //

CREATE PROCEDURE
  cuts.select_distinct_components_in_execution_time (IN test INT,
                                                     IN ctime DATETIME)
BEGIN
  SELECT DISTINCT component, component_name
    FROM execution_time AS t1
    LEFT JOIN component_instances AS t2
      ON t1.component = t2.component_id
    WHERE t1.test_number = test AND t1.collection_time = ctime
    ORDER BY component_name;
END ; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.select_overall_component_processing_time_all
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS
  cuts.select_overall_component_processing_time_all //

CREATE PROCEDURE
  cuts.select_overall_component_processing_time_all (IN test INT)
BEGIN
  SELECT component, src, dst, SUM(metric_count) AS total_event_count,
      MIN(best_time) AS abs_min_time,
      SUM(total_time) / SUM(metric_count) AS overall_avg_time,
      MAX(worst_time) AS abs_max_time
    FROM execution_time
    WHERE test_number = test AND metric_type = 'process'
    GROUP BY dst;
END ; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.select_overall_component_processing_time_i
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS
  cuts.select_overall_component_processing_time_i //

CREATE PROCEDURE
  cuts.select_overall_component_processing_time_i (IN test INT,
                                                   IN inst INT)
BEGIN
  SELECT component, src, dst, SUM(metric_count) AS total_event_count,
      MIN(best_time) AS abs_min_time,
      SUM(total_time) / SUM(metric_count) AS overall_avg_time,
      MAX(worst_time) AS abs_max_time
    FROM execution_time
    WHERE test_number = test AND component = inst AND metric_type = 'process'
    GROUP BY dst;
END ; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.select_overall_component_processing_time
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS
  cuts.select_overall_component_processing_time //

CREATE PROCEDURE
  cuts.select_overall_component_processing_time (IN test INT,
                                                 IN inst VARCHAR(255))
BEGIN
  DECLARE inst_id INT;

  SELECT component_id INTO inst_id FROM component_instances
    WHERE component_name = inst;

  CALL cuts.select_overall_component_processing_time(test, inst_id);
END ; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.select_execution_time_cumulative
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS
  cuts.select_execution_time_cumulative //

CREATE PROCEDURE
  cuts.select_execution_time_cumulative (IN test INT)
BEGIN
  SELECT t9.*, t10.portname AS dstname FROM
    (SELECT t4.*, t8.portname AS srcname FROM
      (SELECT t2.*, t3.component_name FROM
        (SELECT results.*, t1.component_name AS sender_name FROM
          (SELECT test_number, component, sender, src, dst, metric_type, SUM(metric_count) AS metric_count,
             MIN(best_time) AS best_time,  SUM(total_time) / SUM(metric_count) AS avg_time,
             MAX(worst_time) AS worst_time FROM execution_time AS e
             WHERE test_number = test
             GROUP BY component, metric_type, src, dst
             ORDER BY collection_time) AS results
         LEFT JOIN component_instances AS t1
             ON t1.component_id = results.sender) AS t2
      LEFT JOIN component_instances AS t3 ON t2.component = t3.component_id) AS t4
    LEFT JOIN
      (SELECT pid, portname FROM ports AS t6, portnames AS t7
         WHERE t6.portid = t7.portid) AS t8 ON t8.pid = t4.src) AS t9
  LEFT JOIN
      (SELECT pid, portname FROM ports AS t11, portnames AS t12
         WHERE t11.portid = t12.portid) AS t10 ON t10.pid = t9.dst
  ORDER BY t9.component_name, srcname, dstname;
END ; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.select_execution_time_delta
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS
  cuts.select_execution_time_delta //

CREATE PROCEDURE
  cuts.select_execution_time_delta (IN test INT, IN coll_time DATETIME)
BEGIN
  SELECT
      t1.test_number, t1.collection_time, t1.component,
      t1.metric_type, t1.sender, t1.src, t1.dst,
      t1.best_time - t2.best_time AS best_time,
      (t1.total_time / t1.metric_count) - (t2.total_time / t2.event_count) AS avg_time,
      t1.worst_time - t2.worst_time AS worst_time
    FROM execution_time AS t1 LEFT JOIN baseline AS t2
      ON t1.component = t2.instance AND t1.metric_type = t2.metric_type AND
        t1.src = t2.inport AND t1.dst = t2.outport
    WHERE t1.test_number = test AND t1.collection_time = coll_time AND
      (t2.host = cuts.get_component_instance_host_i(test, t1.component) OR t2.host IS NULL)
    ORDER BY t1.component, t1.src, t1.dst, t1.sender;
END ; //

-------------------------------------------------------------------------------
-- PROCEDURE: cuts.select_execution_time_cumulative_delta
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS
  cuts.select_execution_time_cumulative_delta //

CREATE PROCEDURE
  cuts.select_execution_time_cumulative_delta (IN test INT)
BEGIN
  SELECT
      t1.test_number, t2.host, t1.component, t1.sender,
      t1.metric_type, t1.src, t1.dst,
      SUM(t1.metric_count) AS metric_count,
      MIN(t1.best_time) - t2.best_time AS best_time,
      (SUM(t1.total_time) / SUM(t1.metric_count)) - (t2.total_time / t2.event_count) AS avg_time,
      MAX(t1.worst_time) - t2.worst_time AS worst_time
  FROM execution_time AS t1 LEFT JOIN baseline AS t2
  ON t1.component = t2.instance AND t1.src = t2.inport
    AND t1.dst = t2.outport AND t1.metric_type = t2.metric_type
  WHERE t1.test_number = test AND
    (t2.host = cuts.get_component_instance_host_i(test, t1.component) OR t2.host IS NULL)
  GROUP BY component, metric_type, src, dst
  ORDER BY collection_time;
END ; //

*/

delimiter ;