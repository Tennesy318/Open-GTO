/*
	Created: 04.06.11
	Aurthor: ZiGGi
*/

#if defined _bar_included
	#endinput
#endif

#define _bar_included
#pragma library bar

stock bar_OnGameModeInit()
{
	for (new b_id = 0; b_id < sizeof(Bars); b_id++)
	{
	    CreatePickup(1551, 23, Bars[b_id][Coord_X], Bars[b_id][Coord_Y], Bars[b_id][Coord_Z]);
		CreatePickupText("Бар", Bars[b_id][Coord_X], Bars[b_id][Coord_Y], Bars[b_id][Coord_Z]);
	}
	GameMSG(lang_texts[17][12]);
	return 1;
}

stock bar_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if ( PRESSED ( KEY_USING ) )
	{
		return bar_ShowDialog(playerid);
	}
	else if ( PRESSED ( KEY_FIRE ) )
	{
		if (GetPVarInt(playerid, "bar_Drinking") == 1 && GetPVarInt(playerid, "bar_Gulping") == 0)
		{
			GivePVarInt(playerid, "bar_Gulps", 1);
			SetPVarInt(playerid, "bar_Gulping", 1);
			SetTimerEx("bar_Gulp", 2000, 0, "d", playerid);
			return 1;
		}
	}
	else if ( PRESSED ( KEY_SECONDARY_ATTACK ) )
	{
		bar_GulpStop(playerid);
	}
	return 1;
}

forward bar_Gulp(playerid);
public bar_Gulp(playerid)
{
	if (GetPVarInt(playerid, "bar_Gulps") >= MAX_GULPS)
	{
		bar_GulpStop(playerid);
	}
	SetPVarInt(playerid, "bar_Gulping", 0);
	return 1;
}

stock bar_ShowDialog(playerid)
{
	new string[MAX_STRING * sizeof(Drinks)];
	string = lang_texts[17][13];

	for (new i = 0; i < sizeof(Drinks); i++) {
		format(string, sizeof(string),
			lang_texts[17][11],
			string, Drinks[i][Name], Drinks[i][Cost], Drinks[i][Alcohol], Drinks[i][Hp]
		);
	}
	return ShowPlayerDialog(playerid, bar_DialogID, DIALOG_STYLE_TABLIST_HEADERS,
		lang_texts[17][14],
		string,
		lang_texts[17][15], lang_texts[17][16]
	);
}

stock bar_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if (dialogid == bar_DialogID)
	{
		if (!response) return 1;
		if (oGetPlayerMoney(playerid) < Drinks[listitem][Cost])
		{
			return show_Msg_Dialog(playerid, lang_texts[17][14], lang_texts[17][17], lang_texts[17][18]);
		}
		oGivePlayerMoney(playerid,-Drinks[listitem][Cost], 1);
		SetPlayerSpecialAction(playerid, Drinks[listitem][Action]);
		SetPVarInt(playerid, "bar_Drinking", 1);
		SetPlayerDrunkLevel(playerid, GetPlayerDrunkLevel(playerid) + floatround(Drinks[listitem][Alcohol]*100, floatround_round));
		if (Drinks[listitem][Hp] + oGetPlayerHealth(playerid) > GetMaxHealth(playerid))
		{
			oSetPlayerHealth(playerid, GetMaxHealth(playerid));
		}
		else
		{
			oSetPlayerHealth(playerid, oGetPlayerHealth(playerid) + Drinks[listitem][Hp]);
		}
		new string[MAX_STRING];
		format(string, sizeof(string),
			lang_texts[17][19],
			Drinks[listitem][Name], Drinks[listitem][Cost], Drinks[listitem][Alcohol], Drinks[listitem][Hp]
		);
		show_Msg_Dialog(playerid, lang_texts[17][14], string, lang_texts[17][18]);
		return 1;
	}
	return 1;
}

stock bar_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	#pragma unused vehicleid
	if (ispassenger)
	{
		bar_GulpStop(playerid);
	}
	return 1;
}

stock bar_GulpStop(playerid)
{
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	SetPVarInt(playerid, "bar_Drinking", 0);
	SetPVarInt(playerid, "bar_Gulps", 0);
	SetPVarInt(playerid, "bar_Gulping", 0);
	return 1;
}

stock IsPlayerAtBar(playerid)
{
	for (new b_id = 0; b_id < sizeof(Bars); b_id++)
	{
		if (IsPlayerInRangeOfPoint(playerid, 2, Bars[b_id][Coord_X], Bars[b_id][Coord_Y], Bars[b_id][Coord_Z]))
		{
			return 1;
		}
	}
	return 0;
}
