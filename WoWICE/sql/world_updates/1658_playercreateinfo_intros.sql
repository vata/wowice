ALTER TABLE `playercreateinfo` ADD COLUMN `introid` INT UNSIGNED DEFAULT '0' NOT NULL AFTER `maxdmg`;
UPDATE `playercreateinfo` SET `introid` = '81' WHERE `race` = '1';
UPDATE `playercreateinfo` SET `introid` = '21' WHERE `race` = '2';
UPDATE `playercreateinfo` SET `introid` = '41' WHERE `race` = '3';
UPDATE `playercreateinfo` SET `introid` = '61' WHERE `race` = '4';
UPDATE `playercreateinfo` SET `introid` = '2' WHERE `race` = '5';
UPDATE `playercreateinfo` SET `introid` = '141' WHERE `race` = '6';
UPDATE `playercreateinfo` SET `introid` = '101' WHERE `race` = '7';
UPDATE `playercreateinfo` SET `introid` = '121' WHERE `race` = '8';
UPDATE `playercreateinfo` SET `introid` = '162' WHERE `race` = '10';
UPDATE `playercreateinfo` SET `introid` = '163' WHERE `race` = '11';
UPDATE `playercreateinfo` SET `introid` = '165' WHERE `class` = '6';