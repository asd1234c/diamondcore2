ALTER TABLE quest_template ADD COLUMN RewXPId tinyint(3) unsigned NOT NULL default '0' AFTER NextQuestInChain;
ALTER TABLE quest_template ADD COLUMN RewHonorMultiplier float NOT NULL default '0' AFTER RewHonorableKills;
ALTER TABLE quest_template CHANGE COLUMN RewHonorableKills RewHonorAddition int unsigned NOT NULL default '0';