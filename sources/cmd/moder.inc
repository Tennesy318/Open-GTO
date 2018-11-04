/*

    Команды модера
	
*/

CMD:cmdlist(playerid, params[]) {
	SendClientMessage(playerid, COLOUR_WHITE, lang_texts[13][1]);
	SendClientMessage(playerid, COLOUR_WHITE, lang_texts[13][8]);
	SendClientMessage(playerid, COLOUR_WHITE, lang_texts[13][9]);
	if(IsPlayerAdmin(playerid))
	{
		SendClientMessage(playerid, COLOUR_WHITE, lang_texts[13][23]);
		SendClientMessage(playerid, COLOUR_WHITE, lang_texts[13][24]);
		SendClientMessage(playerid, COLOUR_WHITE, lang_texts[13][25]);
		SendClientMessage(playerid, COLOUR_WHITE, lang_texts[13][26]);
	}
	if(IsPlayerRconAdmin(playerid))
	{
		SendClientMessage(playerid, COLOUR_WHITE, lang_texts[13][2]);
		SendClientMessage(playerid, COLOUR_WHITE, lang_texts[13][3]);
		SendClientMessage(playerid, COLOUR_WHITE, lang_texts[13][4]);
		SendClientMessage(playerid, COLOUR_WHITE, lang_texts[13][5]);
		SendClientMessage(playerid, COLOUR_WHITE, lang_texts[13][6]);
	}
	return 1;
}

CMD:about(playerid, params[]) {
	SendClientMessage(playerid, COLOUR_LIGHTGREEN, lang_texts[15][41]);
	SendClientMessage(playerid, COLOUR_LIGHTGREEN, lang_texts[15][42]);
	SendClientMessage(playerid, COLOUR_LIGHTRED, lang_texts[15][43]);
	SendClientMessage(playerid, COLOUR_LIGHTRED, lang_texts[15][44]);
	return 1;
}

CMD:pinfo(playerid, params[]) {
	new subparams[32];

	if (sscanf(params, "s[32]", subparams)) {
		return SendClientMessage(playerid, COLOUR_RED, "/pinfo [id игрока]");
	}
	SendClientMessage(playerid, COLOUR_YELLOW, lang_texts[15][46]);
	new ccount;
	foreach (Player, id)
	{
		if (IsPlayerJailed(id))
		{
			new string[MAX_STRING];
			if (GetPlayerJailTime(id) > 0)
			{
				format(string, sizeof(string), lang_texts[18][3], oGetPlayerName(id), id, GetPlayerJailTime(id));
			}
			else
			{
				format(string, sizeof(string), lang_texts[18][4], oGetPlayerName(id), id);
			}
			SendClientMessage(playerid, COLOUR_LIGHTRED, string);
			ccount++;
		}
		if (GetPlayerMuteTime(id) != 0)
		{
			new string[MAX_STRING];
			if (GetPlayerMuteTime(id) != 0)
			{
				format(string, sizeof(string), lang_texts[18][5], oGetPlayerName(id), id, GetPlayerMuteTime(id));
			}
			else
			{
				format(string, sizeof(string), lang_texts[18][6], oGetPlayerName(id), id);
			}
			SendClientMessage(playerid, COLOUR_LIGHTGREEN, string);
			ccount++;
		}
	}
	if (ccount == 0) SendClientMessage(playerid, COLOUR_XP_GOOD, lang_texts[18][7]);
	return 1;
}
CMD:spec(playerid, params[]) {
    if (!IsPlayerMod(playerid)) return 0;
	new targetid;
	if (sscanf(params, "u", targetid)) {
		return SendClientMessage(playerid, -1, "Используйте: /spec [ник/id]");
	}

	if (targetid == INVALID_PLAYER_ID || targetid == playerid) {
		return SendClientMessage(playerid, 0xBB0000FF, "Неверный id игрока.");
	}

	if (GetPlayerState(targetid) == PLAYER_STATE_WASTED || GetPlayerState(targetid) == PLAYER_STATE_SPECTATING) {
		return SendClientMessage(playerid, 0xBB0000FF, "Игрок в режиме spec.");
	}

    oldPlayerVirtualWorld[playerid] = GetPlayerVirtualWorld(playerid);
	oldPlayerInterior[playerid] = GetPlayerInterior(playerid);
	GetPlayerPos(playerid, oldPlayerPosition[playerid][0], oldPlayerPosition[playerid][1], oldPlayerPosition[playerid][2]);
	GetPlayerFacingAngle(playerid, oldPlayerPosition[playerid][3]);
	GetPlayerHealth(playerid, oldPlayerHealth[playerid]);
	GetPlayerArmour(playerid, oldPlayerArmour[playerid]);

    StartSpectate(playerid, targetid);
	return 1;
}

CMD:specoff(playerid, params[]) {
    if (!IsPlayerMod(playerid)) return 0;
	if (GetPlayerState(playerid) != PLAYER_STATE_SPECTATING) {
		return SendClientMessage(playerid, 0xBB0000FF, "Вы не в spec режиме.");
	}

    StopSpectate(playerid);

    SetPlayerVirtualWorld(playerid, oldPlayerVirtualWorld[playerid]);
	SetPlayerInterior(playerid, oldPlayerInterior[playerid]);
	SetPlayerPos(playerid, oldPlayerPosition[playerid][0], oldPlayerPosition[playerid][1], oldPlayerPosition[playerid][2]);
	SetPlayerFacingAngle(playerid, oldPlayerPosition[playerid][3]);
	SetPlayerHealth(playerid, oldPlayerHealth[playerid]);
	SetPlayerArmour(playerid, oldPlayerArmour[playerid]);
	return 1;
}