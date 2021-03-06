//
// Created:     05.09.06
// Aurthor:    Iain Gilbert
//

#if defined _base_included
  #endinput
#endif

#define _base_included
#pragma library base


new ConfigDB[MAX_STRING] = GTO_FILES_FOLDER "Config/Base-cfg"GTO_FILES_FORMAT;
new LevelDB[MAX_STRING] = GTO_FILES_FOLDER "Config/Levels-cfg"GTO_FILES_FORMAT;
new GangDB[MAX_STRING] = GTO_FILES_FOLDER "Gang/";
new AccountDB[MAX_STRING] = GTO_FILES_FOLDER "Account/";
new PlayerDB[MAX_STRING] = GTO_FILES_FOLDER "Player/";
new HousesDB[MAX_STRING] = GTO_FILES_FOLDER "Housing/";
new BusinessDB[MAX_STRING] = GTO_FILES_FOLDER "Business/";
new WeaponDB[MAX_STRING] = GTO_FILES_FOLDER "Weapon/";
new GroundholdDB[MAX_STRING] = GTO_FILES_FOLDER "Groundhold/";
new BanDB[MAX_STRING] = GTO_FILES_FOLDER "Banned/";

new RealTime = SERVER_REAL_TIME,
	RealTimeOffset = SERVER_REAL_TIME_OFFSET,
	WorldTime;

new nullstr[MAX_STRING];

enum CoordInfo {
    Float:Coord_X,
    Float:Coord_Y,
    Float:Coord_Z
}

stock BaseLoadConfig()
{
	if (!ini_Exist(ConfigDB)) return 0;
	new file_base = ini_Open(ConfigDB);
	ini_GetInt(file_base, "Real_Time", RealTime);
	ini_GetInt(file_base, "Real_Time_Offset", RealTimeOffset);
	ini_Close(file_base);
	return 1;
}

stock BaseSaveConfig()
{
	new file_base = (!ini_Exist(ConfigDB)) ? ini_Create(ConfigDB) : ini_Open(ConfigDB);
	ini_SetInt(file_base, "Real_Time", RealTime);
	ini_SetInt(file_base, "Real_Time_Offset", RealTimeOffset);
	ini_Close(file_base);
	return 1;
}

stock base_OnGameModeInit()
{
	BaseLoadConfig();
	UsePlayerPedAnims();
	ShowPlayerMarkers(1);
	ShowNameTags(1);
	ManualVehicleEngineAndLights();
	EnableStuntBonusForAll(0);
	GameMSG("SERVER: Base module init");
	return 1;
}

stock show_Msg_Dialog(playerid, string_head[], string_content[], button[])
{
	return ShowPlayerDialog(playerid, message_DialogID, DIALOG_STYLE_MSGBOX,
		string_head,
		string_content,
		button, ""
	);
}
