ALTER TABLE `quests` ADD `RewRepFaction3` INT UNSIGNED NOT NULL DEFAULT '0' AFTER `RewRepFaction2` ,
ADD `RewRepFaction4` INT UNSIGNED NOT NULL DEFAULT '0' AFTER `RewRepFaction3` ,
ADD `RewRepFaction5` INT UNSIGNED NOT NULL DEFAULT '0' AFTER `RewRepFaction4` ,
ADD `RewRepFaction6` INT UNSIGNED NOT NULL DEFAULT '0' AFTER `RewRepFaction5` ;

ALTER TABLE `quests` ADD `RewRepValue3` INT UNSIGNED NOT NULL DEFAULT '0' AFTER `RewRepValue2` ,
ADD `RewRepValue4` INT UNSIGNED NOT NULL DEFAULT '0' AFTER `RewRepValue3` ,
ADD `RewRepValue5` INT UNSIGNED NOT NULL DEFAULT '0' AFTER `RewRepValue4` ,
ADD `RewRepValue6` INT UNSIGNED NOT NULL DEFAULT '0' AFTER `RewRepValue5` ;
