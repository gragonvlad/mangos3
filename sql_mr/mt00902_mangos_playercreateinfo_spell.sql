
-- Pack Hobgoblin
DELETE FROM `playercreateinfo_spell` WHERE `Spell` = 69046;
INSERT IGNORE INTO playercreateinfo_spell
SELECT 9, class, 69046, 'Pack Hobgoblin' FROM playercreateinfo_spell WHERE race = 9;

-- Aberration
DELETE FROM `playercreateinfo_spell` WHERE `Spell` = 68976;
INSERT IGNORE INTO playercreateinfo_spell
SELECT 22, class, 68976, 'Aberration' FROM playercreateinfo_spell WHERE race = 22;

-- Darkflight
DELETE FROM `playercreateinfo_spell` WHERE `Spell` = 68992;
INSERT IGNORE INTO playercreateinfo_spell
SELECT 22, class, 68992, 'Darkflight' FROM playercreateinfo_spell WHERE race = 22;

-- Flayer
DELETE FROM `playercreateinfo_spell` WHERE `Spell` = 68978;
INSERT IGNORE INTO playercreateinfo_spell
SELECT 22, class, 68978, 'Flayer' FROM playercreateinfo_spell WHERE race = 22;

-- Two Forms
DELETE FROM `playercreateinfo_spell` WHERE `Spell` = 68996;
INSERT IGNORE INTO playercreateinfo_spell
SELECT 22, class, 68996, 'Two Forms' FROM playercreateinfo_spell WHERE race = 22;

-- Viciousness
DELETE FROM `playercreateinfo_spell` WHERE `Spell` = 68975;
INSERT IGNORE INTO playercreateinfo_spell
SELECT 22, class, 68975, 'Viciousness' FROM playercreateinfo_spell WHERE race = 22;

-- Gnome racial - Escape Artist
DELETE FROM `playercreateinfo_spell` WHERE `Spell` = 20589;
INSERT INTO `playercreateinfo_spell` (`race`, `class`, `Spell`, `Note`) VALUES
(7, 1, 20589, 'Escape Artist'),
(7, 4, 20589, 'Escape Artist'),
(7, 5, 20589, 'Escape Artist'),
(7, 6, 20589, 'Escape Artist'),
(7, 8, 20589, 'Escape Artist'),
(7, 9, 20589, 'Escape Artist');