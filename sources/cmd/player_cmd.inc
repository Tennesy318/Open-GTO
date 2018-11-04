/*

    Команды игрока

*/

cmd:help(playerid, params[]) 
{ 
    SendClientMessage(playerid, COLOUR_RED, "Testing");
    return 1; 
} 
alias:help("commands", "cmds"); // case insensitive  

// spec system

CMD:spec(playerid, params[]) {
    if (!IsPlayerMod(playerid)) return 0;
	new targetid;
	if (sscanf(params, "u", targetid)) {
		return SendClientMessage(playerid, -1, "Используйте: /spec [ник/id]");
	}

	if (targetid == INVALID_PLAYER_ID || targetid == playerid) {
		return SendClientMessage(playerid, 0xBB0000FF, "Ошибка: неправильный id игрока.");
	}

	if (GetPlayerState(targetid) == PLAYER_STATE_WASTED || GetPlayerState(targetid) == PLAYER_STATE_SPECTATING) {
		return SendClientMessage(playerid, 0xBB0000FF, "Ошибка: игрок в режиме spec.");
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
		return SendClientMessage(playerid, 0xBB0000FF, "Ошибка: вы не в spec режиме.");
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
