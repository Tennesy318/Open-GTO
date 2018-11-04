#include <a_samp>
#include "utils/foreach"
#include "utils/Pawn.CMD"
#include "utils/sscanf"
#include "config"
#include "base"
#include "lang"
#include "utils/mxINI"
#include "logging"
#include "utils/gtoutils"
#include "arrays"
#include "pickup"
#include "vehicles"
#include "player/level"
#include "player/vip"
#include "player/weapon"
#include "player/weapon_drop"
#include "player/weapon_skill"
#include "player/health"
#include "player/armour"
#include "player/vehicle"
#include "bank"
#include "fightstyles"
#include "account"
#include "cmd/player"
#include "player"
#include "weapons"
#include "zones"
#include "world"
#include "commands"
#include "gang"
#include "housing"
#include "business"
//streamers
#include "streamers/mapicon_stream"
#include "streamers/checkpoint_stream"
#include "payday"
#include "groundhold"
//admin funtions
#include "admin/functions"
#include "admin/admin_func"
#include "admin/mod_func"
#include "admin/admin_commands"
#include "admin/admin_commands_sys"
#include "admin/adm_commands"
#include "admin/mod_commands"
#include "missions"
#include "missions/trucker"
#include "click"
#include "services/fastfood"
#include "services/bar"
#include "services/skinshop"
#include "services/lottery"
#include "services/vehshop"
#include "interior"
#include "weather"
#include "quidemsys"
#include "usermenu"

// AC
#include "ac/weapon_hack"
#include "ac/fakekill_hack"
#include "ac/vpn_hack"
#include "ac/specialaction_hack"
#include "ac/money"
#include "ac/idle"
#include "ac/rconhack"
#include "ac/hightping"
#include "ac/chatguard"
#include "ac/jetpack"
#include "ac/speedhack"
#include "ac/weaponhack"
//system
#include "system/captcha"
#include "system/chat"
#include "system/interface"

main() {}

public OnGameModeInit()
{
	SetGameModeText("Open-GTO "#VERSION);
	// Initialize everything that needs it
	lang_OnGameModeInit();
	logging_OnGameModeInit();
	base_OnGameModeInit();
	account_OnGameModeInit();
	player_OnGameModeInit();
	gang_OnGameModeInit();
	payday_OnGameModeInit();
	weapons_OnGameModeInit();
	vehicles_OnGameModeInit();
	groundhold_OnGameModeInit();
	business_OnGameModeInit();
	housing_OnGameModeInit();
	interior_OnGameModeInit();
	bank_OnGameModeInit();
	fights_OnGameModeInit();
	weapon_OnGameModeInit();
	quidemsys_OnGameModeInit();
	lottery_OnGameModeInit();
	vip_OnGameModeInit();
	// missions
	mission_OnGameModeInit();
	trucker_OnGameModeInit();
	// services
	fastfood_OnGameModeInit();
	bar_OnGameModeInit();
	ss_OnGameModeInit();
	vshop_OnGameModeInit();
	//
	level_OnGameModeInit();
	antiidle_OnGameModeInit();
	antihightping_OnGameModeInit();
	health_OnGameModeInit();
	aah_OnGameModeInit();
	money_OnGameModeInit();
	chatguard_OnGameModeInit();
	antijetpack_OnGameModeInit();
	antirconhack_OnGameModeInit();
	ash_OnGameModeInit();
	awh_OnGameModeInit();

	#tryinclude "custom\mapicon"
	#tryinclude "custom\pickups"
	#tryinclude "custom\objects"
	GameMSG("SERVER: Custom mapicons, objects and pickups init");

	SyncTime();
	SetWeather( mathrandom(9, 18) );
	SetTimer("OneSecTimer", 1000, 1); // 1 second
	SetTimer("FiveSecondTimer", 5000, 1); // 5 second
	SetTimer("OneMinuteTimer", 60000, 1); // 1 minute
	SetTimer("TenMinuteTimer", 600000, 1); // 10 minute
	SetTimer("OneHourTimer", 3600000, 1); // 1 hour
	if (AntiSpeedHackEnabled == 1)
	{
		SetTimer("AntiSpeedHackTimer", ANTI_SPEED_HACK_CHECK_TIME, 1);
	}
	SetTimerEx("WorldSave", WORLD_SAVE_TIME, 1, "d", 0);
	GameMSG("SERVER: Timers started");
	SpawnWorld();

	WorldSave(0);
	new hour, minute;
	gettime(hour, minute);
	GameMSG("SERVER: Open-GTO "#VERSION" initialization complete. [%02d:%02d]", hour, minute);
	return 1;
}

public OnGameModeExit()
{
	WorldSave(1);
	new hour, minute;
	gettime(hour, minute);
	GameMSG("SERVER: Open-GTO "#VERSION" turned off. [%02d:%02d]", hour, minute);
	return 1;
}

public OnPlayerConnect(playerid)
{
	#tryinclude "robjects.inc"
	if (IsPlayerNPC(playerid)) return 1;
	vpn_OnPlayerConnect(playerid);
	player_OnPlayerConnect(playerid);
   	account_OnPlayerConnect(playerid);
	chatguard_OnPlayerConnect(playerid);
	level_OnPlayerConnect(playerid);
	weapon_OnPlayerConnect(playerid);
	qudemsys_OnPlayerConnect(playerid);
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	if (playerid == INVALID_PLAYER_ID || IsPlayerNPC(playerid)) return 1;
	SetPVarInt(playerid, "Spawned", 0);
	player_OnPlayerDisconnect(playerid, reason);
	trucker_OnPlayerDisconnect(playerid, reason);
	chatguard_OnPlayerDisconnect(playerid, reason);
	gh_OnPlayerDisconnect(playerid, reason);
	level_OnPlayerDisconnect(playerid, reason);
	weapon_OnPlayerDisconnect(playerid, reason);
	qudemsys_OnPlayerDisconnect(playerid, reason);
	pveh_OnPlayerDisconnect(playerid, reason);
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch (dialogid)
	{
		case account_Log_DialogID, account_Reg_DialogID:
		{
			account_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
		}
		case house_DialogID, houses_DialogID, houses_upgrades_DialogID, houses_setrent_DialogID, house_sell_accept_DialogID:
		{
			housing_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
		}
		case bis_DialogID, bis_Msg_DialogID, bis_sell_accept_DialogID:
		{
			business_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
		}
		case fightstyles_DialogID, fightstyles_user_DialogID:
		{
			fights_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
		}
		case user_menu_DialogID, user_menu_Return_DialogID,
			vehicle_menu_DialogID, spawnselect_menu_DialogID, vehicle_color_menu_DialogID, vehicle_radio_menu_DialogID,
			settings_menu_DialogID, changenick_menu_DialogID, changepass_menu_DialogID,
			teleport_menu_DialogID,
			gang_menu_DialogID, gang_create_menu_DialogID, gang_invite_menu_DialogID, gang_color_menu_DialogID,
			gang_motd_menu_DialogID, gang_kick_menu_DialogID, gang_exit_accept_menu_DialogID,
			pveh_select_DialogID, pveh_do_DialogID:
		{
			usermenu_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
		}
		case weapons_Select_DialogID, weapons_Buy_DialogID:
		{
			weapons_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
		}
		case bank_Start_DialogID, bank_FirstList_DialogID, bank_Withdraw_DialogID, bank_Deposit_DialogID,
			gang_wmoney_menu_DialogID, gang_dmoney_menu_DialogID:
		{
			bank_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
		}
		case click_DialogID, click_Resp_DialogID:
		{
			click_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
		}
		case bar_DialogID:
		{
			bar_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
		}
		case fastfood_DialogID:
		{
			fastfood_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
		}
		case SkinShop_Buy_DialogID:
		{
			ss_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
		}
		case trucker_DialogID, trucker_cancel_DialogID:
		{
			trucker_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
		}
		case vshop_DialogID:
		{
			vshop_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
		}
		case captcha_DialogID:
		{
			captcha_OnDialogResponse(playerid, dialogid, response, inputtext);
		}
	}
	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	click_OnPlayerClickPlayer(playerid, clickedplayerid);
	return 1;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
	weapon_OnPlayerPickUpPickup(playerid, pickupid);
	aah_OnPlayerPickUpPickup(playerid, pickupid);
	awh_OnPlayerPickUpPickup(playerid, pickupid);
	vip_OnPlayerPickUpPickup(playerid, pickupid);
	return 1;
}

public OnPlayerEnterCheckpoint(playerid)
{
	trucker_OnPlayerEnterCheckpoint(playerid);
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	if (!IsPlayerConnected(playerid) || IsPlayerNPC(playerid)) return 1;
	SetPVarInt(playerid, "Spawned", 0);
	if (killerid == INVALID_PLAYER_ID)
		GameMSG("player: %s(%d): has died > Reason: (%d)", oGetPlayerName(playerid), playerid, reason);
	else
		GameMSG("player: %s(%d): has killed player %s(%d)> Reason: (%d)", oGetPlayerName(killerid), killerid, oGetPlayerName(playerid), playerid, reason);

	SendDeathMessage(killerid, playerid, reason);

	if (killerid == INVALID_PLAYER_ID) return 1;
	
	player_OnPlayerDeath(playerid, killerid, reason);
	player_OnPlayerKill(killerid, playerid, reason);
	trucker_OnPlayerDeath(playerid, killerid, reason);
	fk_OnPlayerDeath(playerid, killerid, reason);
	gang_OnPlayerDeath(playerid, killerid, reason);
	weapon_OnPlayerDeath(playerid, killerid, reason);
	level_HideTextDraws(playerid);
	PlayCrimeReportForPlayer(killerid, killerid, random(18)+3);
	PlayCrimeReportForPlayer(playerid, killerid, random(18)+3);
	return 1;
}

public OnPlayerSpawn(playerid)
{
	if (IsPlayerNPC(playerid)) return 1;

	// после использования TogglePlayerSpectating
	if (GetPVarInt(playerid, "spec_after_off") == 1)
	{
		DeletePVar(playerid, "spec_after_off");
		return 1;
	}

	// spawn player
	SetPlayerSkin(playerid, GetPlayerSkinModel(playerid));
	UpdatePlayerLevelTextDraws(playerid);

	if (GetPlayerMuteTime(playerid) != 0)
	{
		SendClientMessage(playerid, COLOUR_RED, lang_texts[1][14]);
		SetPlayerWantedLevel(playerid, 3);
	}
	
	player_OnPlayerSpawn(playerid);
	SetPlayerColor(playerid, PlayerGangColour(playerid));
	if (IsPlayerJailed(playerid))
	{
		JailPlayer(playerid, GetPlayerJailTime(playerid));
	}
	SetTimerEx("OnPlayerSpawned", 2500, 0, "d", playerid);
	interface_check(playerid);
	return 1;
}

forward OnPlayerSpawned(playerid);
public OnPlayerSpawned(playerid)
{
	SetPVarInt(playerid, "Spawned", 1);
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	SetPVarInt(playerid, "Spawned", 0);
	player_OnPlayerRequestClass(playerid, classid);
	weapon_OnPlayerRequestClass(playerid, classid);
	level_HideTextDraws(playerid);
	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
	if (!IsPlayerLogin(playerid)) return 0;
	return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	if (!IsPlayerLogin(playerid))
	{
		return SendClientMessage(playerid, -1, lang_texts[1][46]);
	}
	// commands.inc
	command_register(cmdtext, "/help", 5, commands);
	command_register(cmdtext, "/commands", 9, commands);
	command_register(cmdtext, "/sound", 6, commands);
	command_register(cmdtext, "/stats", 6, commands);
	command_register(cmdtext, "/status", 7, commands);
	command_register(cmdtext, "/stat", 5, commands);
	command_register(cmdtext, "/version", 8, commands);
	command_register(cmdtext, "/time", 5, commands);
	command_register(cmdtext, "/skydive", 8, commands);
	command_register(cmdtext, "/pm", 3, commands);

	// Lottery
	command_register(cmdtext, "/lottery", 8, lottery);

	// QuidemSys
	command_register(cmdtext, "/fill", 5, quidemsys);
	command_register(cmdtext, "/engine", 7, quidemsys);

	// vehicles
	command_register(cmdtext, "/vmenu", 6, vehicles);

	// gangs
	command_register(cmdtext, "/g", 2, gang);
	command_register(cmdtext, "/gang", 5, gang);

	// rcon admins
	command_registerNR(cmdtext, "/cmdlist", 8, Admin);
	command_registerNR(cmdtext, "/about", 6, Admin);
	command_register(cmdtext, "/carinfo", 8, Admin);
	command_register(cmdtext, "/carrep", 7, Admin);
	command_register(cmdtext, "/go", 3, Admin);
	command_register(cmdtext, "/an", 3, Admin);
	command_register(cmdtext, "/payday", 7, Admin);
	command_register(cmdtext, "/boom", 5, Admin);
	command_register(cmdtext, "/setskin", 8, Admin);
	command_register(cmdtext, "/ssay", 5, Admin);
	command_register(cmdtext, "/skydiveall", 11, Admin);
	command_register(cmdtext, "/disarm", 7, Admin);
	command_register(cmdtext, "/disarmall", 10, Admin);
	command_register(cmdtext, "/paralyzeall", 12, Admin);
	command_register(cmdtext, "/deparalyzeall", 14, Admin);
	command_register(cmdtext, "/remcash", 8, Admin);
	command_register(cmdtext, "/remcashall", 11, Admin);
	command_register(cmdtext, "/setlvl", 7, Admin);
	command_register(cmdtext, "/setstatus", 10, Admin);
	command_register(cmdtext, "/allowport", 10, Admin);
	command_register(cmdtext, "/setvip", 7, Admin);
	command_register(cmdtext, "/underwater", 11, Admin);
	command_register(cmdtext, "/ahideme", 8, Admin);
	command_register(cmdtext, "/ashowme", 8, Admin);
	command_register(cmdtext, "/godmod", 7, Admin);

	// admin sys
	command_register(cmdtext, "/sys", 4, AdminSys);

	// admins
	command_registerNR(cmdtext, "/cmdlist", 8, Adm);
	command_registerNR(cmdtext, "/about", 6, Adm);
	command_register(cmdtext, "/say", 4, Adm);
	command_register(cmdtext, "/pinfo", 6, Adm);
	command_register(cmdtext, "/admincnn", 9, Adm);
	command_register(cmdtext, "/akill", 6, Adm);
	command_register(cmdtext, "/tele-set", 9, Adm);
	command_register(cmdtext, "/tele-loc", 9, Adm);
	command_register(cmdtext, "/tele-to", 8, Adm);
	command_register(cmdtext, "/tele-here", 10, Adm);
	command_register(cmdtext, "/tele-hereall", 13, Adm);
	command_register(cmdtext, "/tele-xyzi", 10, Adm);
	command_register(cmdtext, "/sethealth", 10, Adm);
	command_register(cmdtext, "/setarm", 7, Adm);
	command_register(cmdtext, "/givexp", 7, Adm);
	command_register(cmdtext, "/agivecash", 10, Adm);
	command_register(cmdtext, "/givegun", 8, Adm);
	command_register(cmdtext, "/paralyze", 9, Adm);
	command_register(cmdtext, "/deparalyze", 11, Adm);
	command_register(cmdtext, "/showpm", 7, Adm);
	command_register(cmdtext, "/getip", 6, Adm);
	command_register(cmdtext, "/ban", 4, Adm);
	command_register(cmdtext, "/unban", 6, Adm);

	// moderators
	command_registerNR(cmdtext, "/cmdlist", 8, Mod);
	command_registerNR(cmdtext, "/about", 6, Mod);
	command_register(cmdtext, "/plist", 6, Mod);
	command_register(cmdtext, "/remcar", 7, Mod);
	command_register(cmdtext, "/kick", 5, Mod);
	command_register(cmdtext, "/carresp", 8, Mod);
	command_register(cmdtext, "/carrespall", 11, Mod);
	command_register(cmdtext, "/mute", 5, Mod);
	command_register(cmdtext, "/unmute", 7, Mod);
	command_register(cmdtext, "/jail", 5, Mod);
	command_register(cmdtext, "/unjail", 7, Mod);
	command_register(cmdtext, "/mole", 5, Mod);
	command_register(cmdtext, "/spec", 5, Mod);
	command_register(cmdtext, "/clearchat", 10, Mod);
	command_register(cmdtext, "/weather", 8, Mod);

	new logstring[MAX_STRING];
	format(logstring, sizeof(logstring), "Player: %s"CHAT_SHOW_ID": %s", oGetPlayerName(playerid), playerid, cmdtext);
	WriteLog(CMDLog, logstring);
	return 1;
}

public OnPlayerText(playerid, text[])
{
	chat_OnPlayerText(playerid, text);
	return 0;
}

public OnPlayerUpdate(playerid)
{
	wh_OnPlayerUpdate(playerid);
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if ( PRESSED( KEY_FIRE ) || PRESSED ( KEY_SECONDARY_ATTACK ) )
	{
		if ( GetPVarInt(playerid, "bar_Drinking") == 1 ) return bar_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	}
	if ( PRESSED ( KEY_USING ) || PRESSED ( KEY_FIRE ) || PRESSED ( KEY_HANDBRAKE ) )
	{
		if ( IsPlayerAtSkinShop(playerid) ) return ss_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	}
	if ( PRESSED ( KEY_USING ) )
	{
		if ( IsPlayerAtEnterExit(playerid) ) return interior_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
		if ( IsPlayerAtHouse(playerid) ) return housing_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
		if ( IsPlayerAtBusiness(playerid) ) return business_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
		if ( IsPlayerAtBank(playerid) != -1 ) return bank_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
		if ( IsPlayerAtAmmunation(playerid) != -1 ) return weapons_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
		if ( GetPlayerFightTrenerID(playerid) != -1 ) return fights_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
		if ( IsPlayerAtFastFood(playerid) ) return fastfood_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
		if ( IsPlayerAtBar(playerid) ) return bar_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
		show_menu(playerid);
		return 1;
	}
	if ( PRESSED( KEY_SUBMISSION ) )
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if ( vehicleid != 0 && IsVehicleIsRunner(vehicleid) )
		{
			trucker_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
		}
		return 1;
	}
	return 1;
}

public OnPlayerSelectedMenuRow(playerid, row)
{
	return 1;
}

public OnPlayerExitedMenu(playerid)
{
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	vehicle_OnPlayerStateChange(playerid, newstate, oldstate);
	ash_OnPlayerStateChange(playerid, newstate, oldstate);
	qudemsys_OnPlayerStateChange(playerid, newstate, oldstate);
	if (newstate == PLAYER_STATE_DRIVER)
	{
	#if defined OLD_ENGINE_DO
		if (GetPlayerVehicleSeat(playerid) == 0)
		{
			new vehicleid = GetPlayerVehicleID(playerid);

			vehicle_Engine(vehicleid, VEHICLE_PARAMS_ON);

			new hour;
			gettime(hour);
			if (hour > VEHICLE_LIGHTS_ON_TIME || hour < VEHICLE_LIGHTS_OFF_TIME)
			{
				vehicle_Light(vehicleid, VEHICLE_PARAMS_ON);
			}
		}
	#endif
		trucker_OnPlayerStateChange(playerid, newstate, oldstate);
		vip_OnPlayerStateChange(playerid, newstate, oldstate);
	}
	if (newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
	{
		vshop_OnPlayerStateChange(playerid, newstate, oldstate);
	}
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
#if defined OLD_ENGINE_DO
	if (GetPlayerVehicleSeat(playerid) == 0)
		vehicle_Engine(vehicleid, VEHICLE_PARAMS_OFF);
#endif
	modfunc_OnPlayerExitVehicle(playerid, vehicleid);
	awh_OnPlayerExitVehicle(playerid, vehicleid);
	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	ash_OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);
	modfunc_OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);
	return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	modfunc_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
	bar_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
	return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid)
{
	return 1;
}

public OnVehicleDamageStatusUpdate(vehicleid, playerid)
{
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	quidemsys_OnVehicleSpawn(vehicleid);
	vshop_OnVehicleSpawn(vehicleid);
	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	trucker_OnVehicleDeath(vehicleid, killerid);
	pveh_OnVehicleDeath(vehicleid, killerid);
	return 1;
}

public OnRconLoginAttempt(ip[], password[], success)
{
	switch(success)
	{
		case 0:
		{
			antirconhack_OnRconLoginAttempt(ip, password, success);
		}
		case 1:
		{
			// если игрок заходит ркон админом, то дадим ему полные права
			new pip[MAX_IP];
			foreach (Player, playerid)
			{
				GetPVarString(playerid, "IP", pip, sizeof(pip));
				if (!strcmp(ip, pip, false))
				{
					SetPlayerStatus(playerid, 3);
					break;
				}
			}
		}
	}
	return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	admin_OnPlayerClickMap(playerid, fX, fY, fZ);
	player_OnPlayerClickMap(playerid, fX, fY, fZ);
	return 1;
}

public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid)
{
	admin_OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid);
	return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	pveh_OnVehiclePaintjob(playerid, vehicleid, paintjobid);
	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	pveh_OnVehicleRespray(playerid, vehicleid, color1, color2);
	return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	pveh_OnVehicleMod(playerid, vehicleid, componentid);
	return 1;
}

public OnEnterExitModShop(playerid, enterexit, interiorid)
{
	new vehicleid = GetPlayerVehicleID(playerid);
	if (vehicleid != 0) {
		if (enterexit == 1) {
			SetVehicleVirtualWorld(vehicleid, playerid + 1);
			SetPlayerVirtualWorld(playerid, playerid + 1);
		} else {
			SetVehicleVirtualWorld(vehicleid, 0);
			SetPlayerVirtualWorld(playerid, 0);
		}
	}
	return 1;
}
