--
-- @file        CUTS-msglog.sql
--
-- $Id: CUTS-msglog.sql 1785 2008-02-04 23:12:28Z hillj $
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
  msgtime         TIMESTAMP       NOT NULL DEFAULT NOW(),
  severity        INT             NOT NULL,
  message         VARCHAR (255)   NOT NULL,

  -- set the contraints for the table
  PRIMARY KEY (msgid),
  
  FOREIGN KEY (test_number) REFERENCES cuts.tests (test_number)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,
  FOREIGN KEY (hostid) REFERENCES cuts.ipaddr_host_map (hostid)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);

DELIMITER //

DELIMITER ;
