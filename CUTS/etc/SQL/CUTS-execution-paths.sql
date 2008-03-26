--
-- @file        CUTS-path-analysis.sql
--
-- $Id: CUTS-create.sql 1127 2007-02-04 02:59:21Z hillj $
--
-- @author      James H. Hill
--

USE cuts;

--
-- Create the table that contains all the critical paths created by the
-- user. The elements in path apprear in cuts.critical_path_elements table.
--

CREATE TABLE IF NOT EXISTS execution_paths
(
  path_id       INT             NOT NULL auto_increment,
  path_name     VARCHAR (32),
  deadline      INT             NOT NULL DEFAULT 250,

  PRIMARY KEY (path_id)
);

--
-- Create the table that contains the elements for the paths contained in
-- cuts.critical_path. This table is constructed such that any path that
-- is deleted from cuts.critical_path will remove all path elements in
-- this table. Also, if component instances ids are changed, they are
-- reflected in this table, and components instances aren't allowd to be
-- deleted if their id appears in this column.
--

CREATE TABLE IF NOT EXISTS execution_path_elements
(
  epeid         INT  NOT NULL auto_increment,
  path_id       INT  NOT NULL,
  path_order    INT  NOT NULL,
  instance      INT  NOT NULL,
  inport        INT  NOT NULL,
  outport       INT  NOT NULL,

  PRIMARY KEY (epeid),  
  UNIQUE (path_id, path_order),

  FOREIGN KEY (path_id) REFERENCES execution_paths (path_id)
    ON DELETE CASCADE
    ON UPDATE CASCADE,

  FOREIGN KEY (instance) REFERENCES component_instances (instid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,

  FOREIGN KEY (inport) REFERENCES porttypes (pid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,

  FOREIGN KEY (outport) REFERENCES porttypes (pid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);

DELIMITER //

-------------------------------------------------------------------------------
-- cuts.get_execution_path_id
-------------------------------------------------------------------------------

DROP FUNCTION IF EXISTS
  cuts.get_execution_path_id; //

CREATE FUNCTION
  cuts.get_execution_path_id (_path_name VARCHAR (32))
  RETURNS INT
BEGIN
  DECLARE retval INT;

  DECLARE CONTINUE HANDLER FOR NOT FOUND
  BEGIN
    INSERT INTO cuts.execution_paths (path_name) 
      VALUES (_path_name);
      
    SET retval = LAST_INSERT_ID();
  END;

  SELECT t0.path_id INTO retval 
    FROM cuts.execution_paths AS t0
    WHERE path_name = _path_name LIMIT 1;

  RETURN retval;
END; //

-------------------------------------------------------------------------------
-- cuts.get_execution_path_element_next
-------------------------------------------------------------------------------

DROP FUNCTION IF EXISTS
  cuts.get_execution_path_element_next; //

CREATE FUNCTION
  cuts.get_execution_path_element_next (_path_name VARCHAR (32))
  RETURNS INT
BEGIN
  DECLARE retval INT;

  SELECT MAX(path_order) INTO retval 
    FROM cuts.execution_path_elements
    WHERE path_id = cuts.get_execution_path_id (_path_name);
  
  IF ISNULL(retval) THEN
    SET retval = 0;
  ELSE
    SET retval = retval + 1;
  END IF;
  
  RETURN retval;
END; //

-------------------------------------------------------------------------------
-- cuts.insert_execution_path_element
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS
  cuts.insert_execution_path_element; //

CREATE PROCEDURE
  cuts.insert_execution_path_element (IN _path_name VARCHAR (32),
                                      IN _instance_name VARCHAR (255),
                                      IN _inport VARCHAR (255),
                                      IN _outport VARCHAR (255))
BEGIN
  DECLARE pathid INT;
  DECLARE ipid INT;
  DECLARE opid INT;
  DECLARE instid INT;
  DECLARE nextid INT;
  
  SET pathid = cuts.get_execution_path_id (_path_name);
  SET ipid = cuts.get_port_id ('sink', _inport);
  SET opid = cuts.get_port_id ('source', _outport);
  SET instid = cuts.get_component_instance_id (_instance_name);
  SET nextid = cuts.get_execution_path_element_next (_path_name);
  
  INSERT INTO 
    cuts.execution_path_elements (path_id, path_order, instance, inport, outport)
    VALUES (pathid, nextid, instid, ipid, opid); 
END; //

-------------------------------------------------------------------------------
-- cuts.select_execution_path_elements_performance
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS
  cuts.select_execution_path_elements_performance; //

CREATE PROCEDURE
  cuts.select_execution_path_elements_performance (IN _path_name VARCHAR (32),
                                                   IN _test_number INT)
BEGIN
  SELECT t8.* FROM 
    cuts.execution_path_elements AS t9
  LEFT JOIN (    
    SELECT t0.*, t7.outport_name
    FROM (
      SELECT t1.test_number, 
             t1.instance,
             t1.sender,
             t1.inport, 
             t1.outport_index,
             t1.outport,
             SUM(t1.perf_count) AS perf_count,
             MIN(t1.best_time) AS best_time,
             SUM(t1.total_time) / SUM(t1.perf_count) AS average_time,
             MAX(t1.worst_time) AS worst_time,
             t2.component_name,
             t4.portname AS inport_name
      FROM cuts.performance_endpoint AS t1,
           cuts.component_instances AS t2,
           cuts.porttypes AS t3,
           cuts.portnames AS t4
      WHERE t1.instance = t2.instid AND
            t1.inport = t3.pid AND
            t3.port_name = t4.pid AND
            t1.test_number = _test_number
      GROUP BY t1.instance, t1.inport, t1.outport_index, t1.outport) AS t0
    LEFT JOIN (
      SELECT t5.pid, 
            t6.portname AS outport_name
      FROM cuts.porttypes AS t5,
          cuts.portnames AS t6
      WHERE t5.port_name = t6.pid) AS t7
    ON t0.outport = t7.pid) AS t8
  ON t9.instance = t8.instance AND 
     t9.inport = t8.inport AND 
     t9.outport = t8.outport
  ORDER BY t9.path_order;
END; //

-------------------------------------------------------------------------------
-- cuts.select_execution_path_performance_cumulative
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS
  cuts.select_execution_path_performance_cumulative; //

CREATE PROCEDURE
  cuts.select_execution_path_performance_cumulative (IN _path_name VARCHAR (32),
                                                     IN _test_number INT)
BEGIN
  SELECT 
    _test_number AS test_number,
    _path_name AS pathname,
    SUM(t8.best_time) AS best_time,
    SUM(t8.average_time) AS average_time,
    SUM(t8.worst_time) AS worst_time
  FROM cuts.execution_path_elements AS t9
  LEFT JOIN (    
    SELECT t0.*, t7.outport_name
    FROM (
      SELECT t1.test_number, 
             t1.instance,
             t1.sender,
             t1.inport, 
             t1.outport_index,
             t1.outport,
             SUM(t1.perf_count) AS perf_count,
             MIN(t1.best_time) AS best_time,
             SUM(t1.total_time) / SUM(t1.perf_count) AS average_time,
             MAX(t1.worst_time) AS worst_time,
             t2.component_name,
             t4.portname AS inport_name
      FROM cuts.performance_endpoint AS t1,
           cuts.component_instances AS t2,
           cuts.porttypes AS t3,
           cuts.portnames AS t4
      WHERE t1.instance = t2.instid AND
            t1.inport = t3.pid AND
            t3.port_name = t4.pid AND
            t1.test_number = _test_number
      GROUP BY t1.instance, t1.inport, t1.outport_index, t1.outport) AS t0
    LEFT JOIN (
      SELECT t5.pid, 
            t6.portname AS outport_name
      FROM cuts.porttypes AS t5,
          cuts.portnames AS t6
      WHERE t5.port_name = t6.pid) AS t7
    ON t0.outport = t7.pid) AS t8
  ON t9.instance = t8.instance AND 
     t9.inport = t8.inport AND 
     t9.outport = t8.outport
  WHERE t9.path_id = cuts.get_execution_path_id (_path_name) 
  ORDER BY t9.path_order;
END; //

-------------------------------------------------------------------------------
-- cuts.select_execution_path_elements_i
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS
  cuts.select_execution_path_elements_i; //

CREATE PROCEDURE
  cuts.select_execution_path_elements_i (IN _pathid INT)
BEGIN
  SELECT t5.epeid,
         t5.path_id,
         t5.path_order,
         t5.instance,
         t5.component_name,
         t5.inport,
         t5.inport_name,
         t5.outport,
         t8.portname AS outport_name
  FROM 
    (SELECT t1.epeid,
            t1.path_id,
            t1.path_order,
            t1.instance,
            t2.component_name,
            t1.inport,
            t4.portname AS inport_name,
            t1.outport
    FROM cuts.execution_path_elements AS t1,
         cuts.component_instances AS t2,
         cuts.porttypes AS t3,
         cuts.portnames AS t4
    WHERE t1.path_id = _pathid AND
          t1.instance = t2.instid AND 
          t1.inport = t3.pid AND t3.port_name = t4.pid) AS t5
  LEFT JOIN 
    (SELECT t6.pid,
            t7.portname
     FROM cuts.porttypes AS t6,
          cuts.portnames AS t7
     WHERE t6.port_name = t7.pid) AS t8
  ON t5.outport = t8.pid
  ORDER BY t5.path_order;      
END; //

-------------------------------------------------------------------------------
-- cuts.select_execution_path_elements
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS
  cuts.select_execution_path_elements; //

CREATE PROCEDURE
  cuts.select_execution_path_elements (IN _pathname VARCHAR (255))
BEGIN
  CALL cuts.select_execution_path_elements_i (cuts.get_execution_path_id (_pathname));
END; //

/*
-------------------------------------------------------------------------------
-- cuts.select_execution_path_times_i
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS
  cuts.select_execution_path_times_i; //

CREATE PROCEDURE
  cuts.select_execution_path_times_i (IN test INT, IN path INT)
BEGIN
  SELECT t13.* FROM critical_path_elements AS cp
    LEFT JOIN (SELECT t9.*, t10.portname AS dstname FROM
      (SELECT t4.*, t8.portname AS srcname FROM
        (SELECT t2.*, t3.component_name FROM
          (SELECT results.*, t1.component_name AS sender_name FROM
            (SELECT *, (total_time / metric_count) AS avg_time FROM execution_time AS e
              WHERE test_number = test) AS results
          LEFT JOIN component_instances AS t1
              ON t1.component_id = results.sender) AS t2
        LEFT JOIN component_instances AS t3 ON t2.component = t3.component_id) AS t4
      LEFT JOIN
        (SELECT pid, portname FROM ports AS t6, portnames AS t7
          WHERE t6.portid = t7.portid) AS t8 ON t8.pid = t4.src) AS t9
    LEFT JOIN
        (SELECT pid, portname FROM ports AS t11, portnames AS t12
           WHERE t11.portid = t12.portid) AS t10 ON t10.pid = t9.dst) AS t13
    ON cp.instance = t13.component AND cp.src = t13.src AND
      (cp.dst = t13.dst OR t13.dst IS NULL)
    WHERE cp.path_id = path
    ORDER BY t13.collection_time, cp.path_order;
END; //

-------------------------------------------------------------------------------
-- cuts.select_execution_path_times
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS
  cuts.select_execution_path_times; //

CREATE PROCEDURE
  cuts.select_execution_path_times (IN test INT,
                                    IN pathname VARCHAR (255))
BEGIN
  DECLARE pid INT;

  SELECT path_id INTO pid FROM cuts.critical_path
    WHERE path_name = pathname;

  CALL cuts.select_execution_path_times_i (test, pid);
END; //

-------------------------------------------------------------------------------
-- cuts.select_execution_path_names_all
-------------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS
  cuts.select_execution_path_names_all; //

CREATE PROCEDURE
  cuts.select_execution_path_names_all ()
BEGIN
  SELECT * FROM critical_path;
END; //

-------------------------------------------------------------------------------
-- cuts.execution_path_deadline_i
-------------------------------------------------------------------------------

DROP FUNCTION IF EXISTS
  cuts.execution_path_deadline_i; //

CREATE FUNCTION
  cuts.execution_path_deadline_i (path INT)
  RETURNS INT
BEGIN
  DECLARE ep_deadline INT;

  SELECT deadline INTO ep_deadline FROM cuts.critical_path
    WHERE path_id = path;

  RETURN ep_deadline;
END; //

-------------------------------------------------------------------------------
-- cuts.execution_path_deadline
-------------------------------------------------------------------------------

DROP FUNCTION IF EXISTS
  cuts.execution_path_deadline; //

CREATE FUNCTION
  cuts.execution_path_deadline (pathname VARCHAR(255))
  RETURNS INT
BEGIN
  DECLARE ep_deadline INT;

  SELECT deadline INTO ep_deadline FROM cuts.critical_path
    WHERE path_name = path;

  RETURN ep_deadline;
END; //
*/

DELIMITER ;
