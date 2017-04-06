SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

DROP TABLE IF EXISTS `db`;
CREATE TABLE `db` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(32) NOT NULL,
  `host` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`,`host`),
  KEY `host` (`host`),
  CONSTRAINT `db_ibfk_1` FOREIGN KEY (`host`) REFERENCES `host` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

DROP TABLE IF EXISTS `host`;
CREATE TABLE `host` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(512) NOT NULL,
  `last_log_file` varchar(32) DEFAULT NULL,
  `last_log_pos` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

DROP TABLE IF EXISTS `tables`;
CREATE TABLE `tables` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(64) NOT NULL,
  `database` int(11) NOT NULL,
  `created` int(11) DEFAULT NULL,
  `read` int(11) DEFAULT NULL,
  `write` int(11) DEFAULT NULL,
  `insert` int(11) DEFAULT NULL,
  `update` int(11) DEFAULT NULL,
  `delete` int(11) DEFAULT NULL,
  `alter` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`,`database`),
  KEY `database` (`database`),
  CONSTRAINT `tables_ibfk_1` FOREIGN KEY (`database`) REFERENCES `db` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

DROP VIEW IF EXISTS `dbtables`;
CREATE VIEW `dbtables` AS select
  `host`.`name` AS `host`,
  `db`.`name` AS `db`,
  `tables`.`name` AS `table`,
  from_unixtime(`tables`.`created`) AS `created`,
  from_unixtime(`tables`.`read`) AS `read`,
  from_unixtime(`tables`.`write`) AS `write`,
  from_unixtime(`tables`.`insert`) AS `insert`,
  from_unixtime(`tables`.`update`) AS `update`,
  from_unixtime(`tables`.`delete`) AS `delete`,
  from_unixtime(`tables`.`alter`) AS `alter`
from `tables`
join `db` on(`tables`.`database` = `db`.`id`)
join `host` on(`db`.`host` = `host`.`id`);

SET FOREIGN_KEY_CHECKS = 1;
