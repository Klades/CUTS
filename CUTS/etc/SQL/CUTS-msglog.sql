--
-- @file        CUTS-msglog.sql
--
-- $Id$
--
-- @author      James H. Hill
--

--
-- Create the test table. This table contains the test
-- registration information to map/manage the information
-- contained in the exeuction_time table correctly.
--

CREATE TABLE IF NOT EXISTS cuts.msglog
(
  msgid           INT             NOT NULL auto_increment,
  test_number     INT             NOT NULL,
  hostid          INT             NOT NULL,
  msgtime         DATETIME        NOT NULL,
  severity        INT             NOT NULL,
  message         VARCHAR (255)   NOT NULL,

  -- set the contraints for the table
  PRIMARY KEY (msgid),

  FOREIGN KEY (test_number) REFERENCES cuts.tests (test_number)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  FOREIGN KEY (hostid) REFERENCES cuts.ipaddr_host_map (hostid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);

DELIMITER //

-- -----------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_log_message
-- -----------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_log_message //

CREATE PROCEDURE
  cuts.insert_log_message (IN _test_number INT,
                           IN _hostname VARCHAR (255),
                           IN _msgtime DATETIME,
                           IN _severity INT,
                           IN _message VARCHAR (255))
BEGIN
  CALL cuts.insert_log_message_i (_test_number,
                                  cuts.get_hostname_id (_hostname),
                                  _msgtime,
                                  _severity,
                                  _message);
END; //

-- -----------------------------------------------------------------------------
-- PROCEDURE: cuts.insert_log_message_i
-- -----------------------------------------------------------------------------

DROP PROCEDURE IF EXISTS cuts.insert_log_message_i //

CREATE PROCEDURE
  cuts.insert_log_message_i (IN _test_number INT,
                             IN _hostid INT,
                             IN _msgtime DATETIME,
                             IN _severity INT,
                             IN _message VARCHAR (255))
BEGIN
  INSERT INTO cuts.msglog (test_number,
                           hostid,
                           msgtime,
                           severity,
                           message)
    VALUES (_test_number, _hostid, _msgtime, _severity, _message);
END; //

DELIMITER ;
