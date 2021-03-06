/*

	��������: ������� � ��������� �� ���������
	�����: ziggi

*/

#if defined _config_included
	#endinput
#endif

#define _config_included
#pragma library config

#pragma dynamic 13000

#define VERSION					"v0.4" // ������ ����
#define GTO_FILES_FORMAT		".gto" // ����������(.txt ��� ������������ ������ �� ���� GNU/Linux �� �������������)
#define GTO_FILES_FOLDER		"Open-GTO/" // �����, ��� �������� ����� Open-GTO, � scriptfiles/

#define LANGUAGE_USE			"Russian" // ������������ ����

#define MAX_STRING				128 // �� ������, ���-�� �������� ��� ����������� ��������� ����������
#define MAX_NAME				40 // ���-�� �������� ��� ���, ������� � ��.
#define MAX_IP					16 // ������������ ���������� �������� ��� IP ������

#define USE_PASSWORD_ENCRYPT // ���� �����������, �� ������ � ����� ������ ����� �����������
#if defined USE_PASSWORD_ENCRYPT
new ENCRYPTION_KEY[] = "_C)2^K�RPXjwE8b\\p{Df+=Q3(O*vgu9ZH[!1\"Le0->?/hSF<'xVzm]$4%5a`Jdny�IUW@G7s6&l:k;i~ YsoM�.cBq#|}NrTtA, ";
#endif

#define SERVER_REAL_TIME			1 // ������� ����� ������������� �������� ������� �������
#define SERVER_REAL_TIME_OFFSET		0 // �������� ������� ������������ �������

#define MAX_PLAYER_LOGIN_ATTEMPT	5 // ������������ ���������� ������� �����

#define MAX_MONEY				500000000 // ������������ ���-�� �����, ������� ����� ����� �����
#define MIN_SEND_SYMBOLS		2 // ����������� ���-�� ������������ �������� � ��
#define MAX_SEND_SYMBOLS		128 // ������������ ���-�� ������������ �������� � ��

#define INVALID_QUEST_ID		0
#define MAX_QUESTS				255

#define WORLD_SAVE_TIME			300000		// 1 ���, �� ��� ���-�� ���������� ����������� ���������� ����� ����(300000 - 5 �����)
#define GameMSG_USE_PRINT // ���� ����������, �� ������� GameMSG ������� ��������� � ������� �������
//#define DebugMSG_USE_PRINT // ���� ����������, �� ������� DMSG ������� ��������� � ������� �������

// ����(��������� �� ���������) 1 ���, 0 ����
#define LOGGING_GAME_LOG_ENABLED	1 // ����������� ��������� ���������
#define LOGGING_DEBUG_LOG_ENABLED	1 // ����������� ���������� ���������
#define LOGGING_CHAT_LOG_ENABLED	1 // ����������� ��������� � ���
#define LOGGING_CMD_LOG_ENABLED		1 // ����������� �������� ������
// �������(��������� �� ���������), � ������ ������������...
#define ANTI_HEALTH_HACK_ENABLED	1 // ������ �� ���� �� ��������
#define ANTI_MONEY_HACK_ENABLED		1 // ������ �� ���� �� ������

#define ANTI_HIGHT_PING_ENABLED		1 // ������ �� �������� �����
#define MAXIMAL_PING				500 // ����, ��� ������� ������

#define ANTI_IDLE_ENABLED			1 // ������ �� ��� �� ������ ��������
#define MAX_IDLE_TIME				2 // ���-�� �����, ����� ������� ������

#define CHAT_GUARD_ENABLED			1 // ������ ����
#define ANTI_JETPACK_ENABLED		1 // ������ �� ������������� JetPack
#define ANTI_RCON_HACK_ENABLED		1 // ������ �� ������ rcon ������
#define ANTI_ARMOUR_HACK_ENABLED	1 // ������ �� ���� �� �����
#define ANTI_WEAPON_HACK_ENABLED	0 // ������ �� ���� �� ������ � �������

#define ANTI_SPEED_HACK_ENABLED		0 // ������ �� speedhack, airbreak, ������������(���� ����������� ������ ������������, �������������� �������� ����)
#define ANTI_SPEED_HACK_CHECK_TIME	900 // ����� ������� ��� ������ �� ��������, �� ���������� ��������� 1000
										// ��� ����� ����������� �������� ����� ������������� ���� ������� ��������


// QuidemSys - ��������� � ������
#define QUIDEMSYS_ENABLED		1
#define QUIDEMSYS_TD_FONT		2 // ������������ id ������ � ����������
#define QUIDEMSYS_FUEL_SPEED	1 // ���������� �������, ������������� �� 1 �������
#define QUIDEMSYS_FUEL_TARIF	3000 // ���� ������ ����� �������, � ��������

// ������
#define MAX_GULPS			5 // ������������ ���������� ������� �� �������

// �������
#define LOTTERY_ENABLED		1 // �������-�� ������ �������
#define LOTTERY_TIME		10 // ����� ���������, � �������
#define LOTTERY_WIN_MONEY	1000000 // ���������� ����� ���������� � �������
#define LOTTERY_WIN_XP 		50000 // ���������� xp ���������� � �������
#define LOTTERY_TICKET_COST	5000 // ���� ����������� ������

// skins
#define SKINS_COST			0 // ���� ������� �����
#define SKINS_IGNORE		0, 74  // ������ ������������ ������
#define SKINS_MAXID			311
#define SKINS_MINID			1

#define GROUNDHOLD_ENABLED		1 // ����� ��������
#define GROUNDHOLD_HOLD_TIME	2 // �������� ������ ����� ��� ������ �� ����

#define BANK_PROFIT			2 // ������� ���������� ������� �� �������� � �����
#define MAX_BANK_MONEY		1000000000 // ������������ ���������� �����, ������� ����� ������� � �����

#define PAYDAY_BASE_PAY		35 // PayDay ����� �� ������
#define PAYDAY_CUTOFF		MAX_MONEY / 2 // ���-�� �����, ��� ������� ���������� �������� ������ �� PayDay
#define	PAYDAY_PAYXP		300 // PayDay ����� �� ����

#define CHAT_SHOW_ID		"(%d)" // ��� ����������� ��� � ����

#define WEAPON_SKILL_ENABLED	1 // �������� �������� ������ (���� ���������, �� ������ �� ���������)
#define WEAPON_SKILL_SPEED		50 // ���������� ��������� ������ �� ���� ��������
#define WEAPON_DROP_ENABLED		0 // �������� ��������� ������
#define WEAPON_DROP_TIME		10 // �����, ����� �������� �������� ������, �������� �� ������, � ��������
#define WEAPON_DROP_BULL		20 // ������� ��������� ���������� ������ ������� �� ������
#define MAX_DROPPED_WEAPONS		64 // ������������ ���������� ��������� ������ �������������(� ���� �������)

#define SKYDIVE_TIME		5 // �����, ����� ������� ����� ����� ����� ������������ /skydive, � �������

#define SYS_WEATHER_UPDATE	20 // �����, ����� ������� ��������� ��������� ������, � �������, ���� 0, �� ���������

#define TELEPORTS_PAUSE_TIME	300 // ����� ����� ����������������, ����� ������� ����� ��������� �����������������, � ��������

// ����������� ������� � ���������
#define ALLOWED_STRING_SYMBOLS		'a'..'z','A'..'Z','0'..'9','_','[',']','=','(',')',' '
#define ALLOWED_STRING_SYMBOLS_STR	"'a'..'z','A'..'Z','0'..'9','_','[',']','=','(',')',' '"
#define ALLOWED_NICK_SYMBOLS		'a'..'z','A'..'Z','0'..'9','_','[',']','.','=','(',')'
#define ALLOWED_NICK_SYMBOLS_STR	"'a'..'z','A'..'Z','0'..'9','_','[',']','.','=','(',')'"
// ����������� ������(by wups, ��������������)
#define MAPICON_PAY_SPRAY
#define MAPICON_TUNE
//

// ����
#define MAX_PLAYER_HOUSES		3 // ���������� �����, ������� ����� ����� �����(����� ������� �� �������������)
#define HOUSE_UPGRADE_ARMOUR_COST 1000000
#define HOUSE_UPGRADE_HEALTH_COST 1000000
//#define BUY_ALL_HOUSES // ��������� ��������� �������� ����� ����(���� ���������������� �� ����� ���� ������ ��������)
#define HOUSE_UNLOGIN_SELL_DAYS		7 // ���������� ����, ����� ������� ��� ����� ������, ���� ����� �� ������ � ����
//

// �������
#define MAX_PLAYER_BUSINESS		3 // ���������� ��������, ������� ����� ����� �����(����� ������� �� �������������)
#define MAX_BUSINESS_LEVEL		30 // ������������ ������� �������� �������
#define UPGRADE_TARIF			10 // ����� ����� �� ��������� ������, �������: (Businesses[id][Business_Upgrade]+1) * Businesses[id][Business_Value] * UPGRADE_TARIF
//#define BUY_ALL_BUSINESS // ��������� ��������� �������� ����� �������(���� ���������������� �� ����� ������� ������ ��������)
#define BUSINESS_UNLOGIN_SELL_DAYS	5 // ���������� ����, ����� ������� ������ ����� ������, ���� ����� �� ������ � ����
//

// ���������
#define CARS_RESPAWN_TIME	600 // ����� �������� ���������� � �������� (86400 - ���� ����)
#define OLD_ENGINE_DO // ��� � ��������� - ��������, ����� - ������(���� �����������)

// ��������� � VEHICLE_LIGHTS_ON_TIME � VEHICLE_LIGHTS_OFF_TIME �������� 0, ���� ������, ����� ���� ���������� � ����� �����
#define VEHICLE_LIGHTS_ON_TIME		16 // �����(�����), ����� ���� ���������� ����� ������������� ����������
#define VEHICLE_LIGHTS_OFF_TIME		7 // �����(�����), ����� ���� ���������� ����� ������������� �����������
//
#define MAX_PLAYER_VEHICLES			7 // ������������ ���������� ������� ����������
#define VEHSHOP_CAR_CHANGE_TIME		1 // ���������� �����, ����� ������� ��������� � �������� ��������

// �����
#define MAX_GANGS			MAX_PLAYERS // �������� ���� ������
#define MAX_GANG_SIZE		11 // ������������ ���-�� ����� � �����

#define MIN_GANG_NAME_LEN	2 // ����������� ����� ����� �����
#define MAX_GANG_NAME_LEN	40 // ������������ ����� ����� �����

#define MAX_GANG_MOTD_LEN	128 // ������������ ����� ���������� �����

#define GANG_CREATE_COST	500000 // ���-�� �����, ��������� �� �������� �����
#define GANG_COLOUR_COST	20000 // ���-�� �����, ��������� �� ����� ����� �����

#define MAX_GANG_BANK		500000000 // ������������ ���������� �����, ������� ����� ������� � ����� �����
//

// �����
#define MIN_HEALTH				35.0 // �����������(���������) ���-�� ��������
#define MAX_HEALTH				100.0 // ������������ ���-�� ��������
#define HEALTH_TARIF			4.0	// ������� ���������� ������������� �������� �� ���, �������: MIN_HEALTH + (GetPlayerLevel(playerid) * HEALTH_TARIF)
#define HEALTH_REGEN_TARIF		0.1 // ������� ���-�� ����������������� ��������, �������: (GetPlayerLevel(id) * HEALTH_REGEN_TARIF)

#define CHANGE_NICK_COST			100000 // ���-�� �����, ��������� ��� ����� ����
#define MIN_PLAYER_NAME				3
#define CHANGE_PASS_COST			5000 // ���-�� �����, ��������� ��� ����� ������
#define MIN_PASS_LEN				3
#define MAX_PASS_LEN				40
// ������
	// trucker
	#define TRUCKER_ENABLED					1
	#define TRUCKER_XP_RATE					25 // ���-�� ����� �� �����, �������: ( (GetPlayerLevel(playerid)+1) * 2 )^2 * trucker_GIVE_XP_RATE
	#define TRUCKER_MONEY_RATE				10
	#define TRUCKER_MONEY_PENALTY			2000 // ���-�� ����� ���������� ��� ������������ ��������
	#define TRUCKER_TIME_GET_TRAILER		120 // ���-�� ������, �������� �� ����������� ���� � ������
	#define TRUCKER_MISSION_TRY_COUNT		2 // ���-�� ���������� � ������������� ������ �� ��������
	#define TRUCKER_MISSION_TIME			480 // ����� �������� �� ����������� ������
	#define TRUCKER_RUNNER_MISSION_TIME		300 // ����� �������� ����� ��������, � ��������
	#define TRUCKER_CAR_SPAWN_TIME			30
	// cargo
	#define CARGO_MONEY		10000

//
// ��� ������
#define PLAYER_XP_DEATH_MINUS_PROC		1 // ������� ��������� XP ��������� �� ��� ���������� �����
#define PLAYER_MONEY_DEATH_MINUS_PROC	25 // ������� ��������� ����� ���������
#define PLAYER_XP_KILL_TARIF			15 // �������� �� ���������� ����������� ����� ��� ��������, ��������� � ������� player_OnPlayerKill

// ��������� ��������� ������
#define FIRST_LEVEL				1 // �������, ������� ����� ������ ����� �����������
#define PLAYER_START_MONEY		100 // ���-�� ��������� �����

#define KEY_USING			KEY_WALK
#define KEY_NAME			"ALT"
#define PICKUP_TEXT			"\n{33AA33}������� ������ '{FFFFFF}"KEY_NAME"{33AA33}'"
#define CreatePickupText(%0,%1,%2,%3)	Create3DTextLabel(%0PICKUP_TEXT, 0xFFFFFFFF,%1,%2,%3, 20.0, 0, 1)
//
#define WEAPON_HACK 38 || 36

// �������
enum {
	message_DialogID,
	account_Reg_DialogID, account_Log_DialogID,
	bank_Start_DialogID, bank_FirstList_DialogID, bank_Withdraw_DialogID, bank_Deposit_DialogID,
	click_DialogID, click_Resp_DialogID,
	house_DialogID, houses_DialogID, houses_upgrades_DialogID, houses_setrent_DialogID, house_sell_accept_DialogID,
	bis_DialogID, bis_Msg_DialogID, bis_sell_accept_DialogID,
	fightstyles_DialogID, fightstyles_user_DialogID,
	user_menu_DialogID, user_menu_Return_DialogID,
		vehicle_menu_DialogID, spawnselect_menu_DialogID, settings_menu_DialogID, vehicle_color_menu_DialogID, vehicle_radio_menu_DialogID,
		changenick_menu_DialogID, changepass_menu_DialogID,
		gang_menu_DialogID, gang_create_menu_DialogID, gang_invite_menu_DialogID, gang_color_menu_DialogID, gang_motd_menu_DialogID, gang_wmoney_menu_DialogID, gang_dmoney_menu_DialogID,
		gang_kick_menu_DialogID, gang_exit_accept_menu_DialogID,
	weapons_Select_DialogID, weapons_Buy_DialogID,
	bar_DialogID,
	fastfood_DialogID,
	SkinShop_Buy_DialogID,
	trucker_DialogID, trucker_cancel_DialogID,
	cargo_DialogID,
	teleport_menu_DialogID, teleport_DialogID,
	vshop_DialogID, airshop_DialogID, bikeshop_DialogID,
	captcha_DialogID, duel_DialogID,
	pveh_select_DialogID, pveh_do_DialogID,
}

// ������

#define SPECIAL_ACTION_PISS	68

// ���� �������
#define SPAWN_HOUSE_NONE	-1
#define SPAWN_HOUSE_GANG	-2

// '��������������' ������� mxINI
#define ini_Create		ini_createFile
#define ini_Open		ini_openFile
#define ini_Close		ini_closeFile
#define ini_Set			ini_setString
#define ini_SetInt		ini_setInteger
#define ini_SetFloat	ini_setFloat
#define ini_Get			ini_getString
#define ini_GetInt		ini_getInteger
#define ini_GetFloat	ini_getFloat
#define ini_Remove		ini_removeKey
#define ini_Remov		fremove
#define ini_Exist		fexist

// �����
#define COLOUR_GREY 0xAFAFAFAA // grey
#define COLOUR_GREEN 0x33AA33AA // green
#define COLOUR_LIGHTGREEN 0x9ACD32AA //lightgreen
#define COLOUR_RED 0xAA3333AA // red
#define COLOUR_LIGHTRED 0xFF6347AA // lightred
#define COLOUR_YELLOW 0xFFFF00AA // yellow
#define COLOUR_WHITE 0xFFFFFFAA // white
#define COLOUR_BLUE 0x0000FFAA // blue
#define COLOUR_LIGHTBLUE 0x33CCFFAA // LightBlue
#define COLOUR_ORANGE 0xFF9900AA //orange
#define COLOUR_PURPLE 0xC2A2DAAA //purple
#define COLOUR_CRIMSON 0xDC143CAA
//#define COLOUR_LIMEGREEN 0x32CD32AA
#define COLOUR_AQUA 0x00FFFFAA
#define COLOUR_FLBLUE 0x6495EDAA
#define COLOUR_MAGENTA 0xFF00FFAA
//#define COLOUR_GOLD 0xFFD700AA
#define COLOUR_PINK 0xFFC0CBAA
#define COLOUR_MISC 0xAFAFAFAA // Grey - Misc
#define COLOUR_CHAT 0xFFFFFFAA // White - Chat
#define COLOUR_PLAYER 0xAAAAAAAA // White - Player
#define COLOUR_XP_GOOD 0x00C7FFAA // Blue - XP
#define COLOUR_XP_BAD 0x00008BAA // Blue - XP
#define COLOUR_COMBAT_GOOD 0xAA3333AA // Red - Combat
#define COLOUR_COMBAT_BAD 0xBB3333AA // Red - Combat
#define COLOUR_MONEY_GOOD 0xFFFF00AA // Yellow - Money
#define COLOUR_MONEY_BAD 0xDAA520AA // Yellow - Money
#define COLOUR_GANG 0xFF8C00AA // orange
#define COLOUR_GANG_CHAT 0xFFA500AA // orange
#define COLOUR_PM 0xFFCC22FF
#define WARN_MS_COLOR 0xFF5050AA

//#define COLOUR_LIGHTCORAL 0xF08080AA
#define COLOUR_DARKRED 0x8B0000AA
#define COLOUR_DEEPPINK 0xFF1493AA
#define COLOUR_TOMATO 0xFF6347AA
#define COLOUR_OrangeRed 0xFF4500AA
#define COLOUR_DarkOrange 0xFF8C00AA
#define COLOUR_Moccasin 0xFFE4B5AA
#define COLOUR_Khaki 0xF0E68CAA
#define COLOUR_DarkViolet 0x9400D3AA
#define COLOUR_Indigo 0x4B0082AA
#define COLOUR_GreenYellow 0xADFF2FAA
#define COLOUR_Lime 0x00FF00AA
//#define COLOUR_LIMEGREEN 0x32CD32AA
#define COLOUR_SpringGreen 0x00FF7FAA
#define COLOUR_Olive 0x808000AA
#define COLOUR_Teal 0x008080AA
//#define COLOUR_Aquamarine 0x7FFFD4AA
#define COLOUR_SteelBlue 0x4682B4AA
#define COLOUR_SkyBlue 0x87CEEBAA
#define COLOUR_Tan 0xD2B48CAA
#define COLOUR_Peru 0xCD853FAA
#define COLOUR_Sienna 0xA0522DAA
//#define COLOUR_MistyRose 0xFFE4E1AA
#define COLOUR_DimGray 0x696969AA
#define COLOUR_Black 0x000000AA

// �� �������
#define PRESSED(%0) \
	(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
