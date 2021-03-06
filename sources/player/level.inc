/*


*/

#if defined _level_included
	#endinput
#endif

#define _level_included
#pragma library level


#define GetPlayerLevel(%1) GetPVarInt(%1,"Level")
#define GetPlayerXP(%1) GetPVarInt(%1,"XP")
#define SetPlayerXP(%1,%2) SetPVarInt(%1,"XP",%2)

new Text:level_TextDraw_Level[MAX_PLAYERS],
	Text:level_TextDraw_XP[MAX_PLAYERS];

enum LevelInfo {
	level_xp,
    level_name[MAX_NAME]
}

new LevelList[][LevelInfo] = {
{  0,		"0 �������" },
{  500,		"1 �������" },
{  1000,	"2 �������" },
{  2000,	"3 �������" },
{  5000,	"4 �������" },
{  7500,	"5 �������" },
{  11000,	"6 �������" },
{  16000,	"7 �������" },
{  21000,	"8 �������" },
{  31000,	"9 �������" },
{  46000,	"10 �������" },
{  70000,	"11 �������" },
{  100000,	"12 �������" },
{  135000,	"13 �������" },
{  190000,	"14 �������" },
{  225000,	"15 �������" },
{  300000,	"16 �������" },
{  380000,	"17 �������" },
{  480000,	"18 �������" },
{  590000,	"19 �������" },
{  700000, 	"20 �������" },
{  820000,	"21 �������" },
{  950000,	"22 �������" },
{  1200000,	"23 �������" },
{  1350000,	"24 �������" },
{  1420000, "25 �������" },
{  1500000, "26 �������" },
{  1600000, "27 �������" },
{  1700000, "28 �������" },
{  1800000, "29 �������" },
{  2500000, "30 �������" },
{  3000000, "31 �������" },
{  3500000, "32 �������" },
{  4000000, "33 �������" },
{  5500000, "34 �������" },
{  6000000, "35 �������" },
{  6500000, "36 �������" },
{  7000000, "37 �������" },
{  7500000, "38 �������" },
{  8000000, "39 �������" },
{  10500000, "40 �������" },
{  12000000, "41 �������" },
{  13000000, "42 �������" },
{  14200000, "43 �������" },
{  15400000, "44 �������" },
{  16600000, "45 �������" },
{  17800000, "46 �������" },
{  19000000, "47 �������" },
{  21000000, "48 �������" },
{  23000000, "49 �������" },
{  26000000, "50 �������" },
{  29000000, "51 �������" },
{  32000000, "52 �������" },
{  35000000, "53 �������" },
{  38000000, "54 �������" },
{  41000000, "55 �������" },
{  43000000, "56 �������" },
{  46000000, "57 �������" },
{  50000000, "58 �������" },
{  55000000, "59 �������" },
{  60000000, "60 �������" },
{  70000000, "61 �������" }
};

#define MAX_LEVEL	(sizeof(LevelList)-1)
#define MAX_XP		LevelList[MAX_LEVEL][level_xp]

stock level_LoadConfig()
{
	if (ini_Exist(ConfigDB))
	{
		new file_level = ini_Open(ConfigDB);
		ini_Get(file_level, "Level_DB", LevelDB);
		ini_Close(file_level);
	}
	if (ini_Exist(LevelDB))
	{
		new file_base_level = ini_Open(LevelDB);
		new temp[MAX_STRING];
		for (new i = 0; i <= MAX_LEVEL; i++)
		{
			format(temp, sizeof(temp), "Level%d_Experience", i);
			ini_GetInt(file_base_level, temp, LevelList[i][level_xp]);
			
			format(temp, sizeof(temp), "Level%d_Rankname", i);
			ini_Get(file_base_level, temp, LevelList[i][level_name], MAX_NAME);
		}
		ini_Close(file_base_level);
	}
	return 1;
}

stock level_SaveConfig()
{
	new file_level = (!ini_Exist(ConfigDB)) ? ini_Create(ConfigDB) : ini_Open(ConfigDB);
	ini_Set(file_level, "Level_DB", LevelDB);
	ini_Close(file_level);
	
	new file_base_level = (ini_Exist(LevelDB)) ? ini_Open(LevelDB) : ini_Create(LevelDB);
	new temp[MAX_STRING];
	for (new i = 0; i <= MAX_LEVEL; i++)
	{
	    format(temp, sizeof(temp), "Level%d_Rankname", i);
		ini_Set(file_base_level, temp, LevelList[i][level_name]);
		
		format(temp, sizeof(temp), "Level%d_Experience", i);
		ini_SetInt(file_base_level, temp, LevelList[i][level_xp]);
	}
	ini_Close(file_base_level);
	return 1;
}

stock level_OnGameModeInit()
{
	level_LoadConfig();
	GameMSG("SERVER: (player)Level module init");
	return 1;
}

stock level_OnPlayerConnect(playerid)
{
	// Level
	level_TextDraw_Level[playerid] = TextDrawCreate(5.000000, 412.000000, "Level: 1");
	TextDrawBackgroundColor(level_TextDraw_Level[playerid], 255);
	TextDrawFont(level_TextDraw_Level[playerid], 1);
	TextDrawLetterSize(level_TextDraw_Level[playerid], 0.310000, 1.200000);
	TextDrawColor(level_TextDraw_Level[playerid], -1);
	TextDrawSetOutline(level_TextDraw_Level[playerid], 0);
	TextDrawSetProportional(level_TextDraw_Level[playerid], 1);
	TextDrawSetShadow(level_TextDraw_Level[playerid], 1);
	// XP
	level_TextDraw_XP[playerid] = TextDrawCreate(5.000000, 422.000000, "XP: Unknown/Unknown");
	TextDrawBackgroundColor(level_TextDraw_XP[playerid], 255);
	TextDrawFont(level_TextDraw_XP[playerid], 1);
	TextDrawLetterSize(level_TextDraw_XP[playerid], 0.250000, 1.100000);
	TextDrawColor(level_TextDraw_XP[playerid], -1);
	TextDrawSetOutline(level_TextDraw_XP[playerid], 0);
	TextDrawSetProportional(level_TextDraw_XP[playerid], 1);
	TextDrawSetShadow(level_TextDraw_XP[playerid], 1);
	//
	return 1;
}

stock level_OnPlayerDisconnect(playerid,reason)
{
	#pragma unused reason
	level_HideTextDraws(playerid);
	TextDrawDestroy(level_TextDraw_Level[playerid]);
	TextDrawDestroy(level_TextDraw_XP[playerid]);
	return 1;
}

stock GetLevelName(level)
{
	new name[MAX_NAME];
	if (level < 0 || level > MAX_LEVEL+1) return name;
	set(name, LevelList[level][level_name]);
	return name;
}

stock GetXPToLevel(playerid,level)
{
	if (level <= MAX_LEVEL && level > GetPlayerLevel(playerid))
	{
		return (LevelList[level][level_xp] - GetPlayerXP(playerid));
	}
	return 0;
}

stock CalculatePlayerLevel(playerid)
{
	new level;
	for (new i = 0; i <= MAX_LEVEL; i++)
	{
		if (GetPlayerXP(playerid) >= LevelList[i][level_xp])
		{
			level = i;
		}
	}
	return level;
}

stock GivePlayerXP(playerid, xpamount, showtext = 0)
{
	if (xpamount == 0) return 0;
	GangGivePlayerXP(playerid,xpamount);

	new texttime = (xpamount > 5000) ? 2000 : 1000;
	
	if (GetPlayerXP(playerid) + xpamount < 0)
	{
		xpamount = -GetPlayerXP(playerid);
	}
	if (GetPlayerXP(playerid) + xpamount >= MAX_XP)
	{
		SendClientMessage(playerid, COLOUR_RED, lang_texts[9][17]);
		xpamount = MAX_XP - GetPlayerXP(playerid);
	}
	new string[MAX_STRING];
	if (xpamount >= 0)
	{
		format(string, sizeof(string), lang_texts[9][18], xpamount);
		GameTextForPlayer(playerid, string, texttime, 3);
		if (showtext == 1)
		{
			format(string, sizeof(string), lang_texts[9][20], xpamount);
			SendClientMessage(playerid, COLOUR_XP_GOOD, string);
		}
	}
	else
	{
		format(string, sizeof(string), lang_texts[9][19], -xpamount);
		GameTextForPlayer(playerid, string, texttime, 3);
		if (showtext == 1)
		{
			format(string, sizeof(string), lang_texts[9][21], -xpamount);
			SendClientMessage(playerid, COLOUR_XP_BAD, string);
		}
	}
	SetPlayerXP(playerid,GetPlayerXP(playerid) + xpamount);
	UpdatePlayerLevelTextDraws(playerid);
	CheckPlayerLevel(playerid);
	return 1;
}

stock CheckPlayerLevel(playerid)
{
	new newlevel = CalculatePlayerLevel(playerid);
	new oldlevel = GetPlayerLevel(playerid);
	if (oldlevel < newlevel)
	{
		PlayerLevelUp(playerid, newlevel, oldlevel);
	}
	else if (oldlevel > newlevel)
	{
		PlayerLevelDown(playerid, newlevel, oldlevel);
	}
	return 1;
}

stock PlayerLevelDown(playerid, newlevel, oldlevel)
{
	SetPlayerLevel(playerid, newlevel);
	PlayerPlaySoundOnPlayer(playerid, 1057);
	
	new string[MAX_STRING];
	format(string, sizeof(string), lang_texts[9][22], newlevel);
	SendClientMessage(playerid, COLOUR_XP_BAD, string);
	
	GameMSG("player: %s(%d): decreased his level from %d to %d", oGetPlayerName(playerid), playerid, oldlevel, newlevel);
	return 1;
}

stock PlayerLevelUp(playerid, newlevel, oldlevel)
{
	SetPlayerLevel(playerid, newlevel);
	SetMaxPlayerHealth(playerid);
	PlayerPlaySoundOnPlayer(playerid, 1057);
	
	new string[MAX_STRING];
	format(string, sizeof(string), lang_texts[9][23], newlevel);
	SendClientMessage(playerid, COLOUR_XP_GOOD, string);
	
	ShowWeaponsOnLevel(playerid, newlevel, oldlevel);
	
	GameMSG("player: %s(%d): increased his level from %d to %d", oGetPlayerName(playerid), playerid, oldlevel, newlevel);
	return 1;

}

stock SetPlayerLevel(playerid, level)
{
	SetPVarInt(playerid, "Level", level);
	SetPlayerScore(playerid, level);
	UpdatePlayerLevelTextDraws(playerid);
}

stock level_HideTextDraws(playerid)
{
	TextDrawHideForPlayer(playerid,level_TextDraw_Level[playerid]);
	TextDrawHideForPlayer(playerid,level_TextDraw_XP[playerid]);
	return 1;
}

stock UpdatePlayerLevelTextDraws(playerid)
{
	new string[64],
		level = GetPlayerLevel(playerid);
	
	format(string,sizeof(string),"Level: %d",level);
	TextDrawSetString(level_TextDraw_Level[playerid], string);
	TextDrawShowForPlayer(playerid,level_TextDraw_Level[playerid]);
	
	if (level >= MAX_LEVEL)
	{
		TextDrawHideForPlayer(playerid,level_TextDraw_XP[playerid]);
		return 1;
	}
	else
	{
		format(string,sizeof(string),
			"XP: %d/%d",
			GetPlayerXP(playerid) - LevelList[level][level_xp], LevelList[level+1][level_xp] - LevelList[level][level_xp]
		);
		TextDrawSetString(level_TextDraw_XP[playerid], string);
		TextDrawShowForPlayer(playerid,level_TextDraw_XP[playerid]);
	}
	return 1;
}
