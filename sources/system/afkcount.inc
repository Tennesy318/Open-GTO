#if defined _afkcount_included
	#endinput
#endif

#define _afkcount_included
#pragma library afkcount

stock afkcount_OnGameModeInit()
{
	SetTimer("AFKSystem", 1000, 1);
	return 1;
}

stock afkcount_OnPlayerConnect(playerid)
{
	SetPVarInt(playerid, "PlayerInAFK", -2);
	return 1;
}

stock afkcount_OnPlayerSpawn(playerid)
{
	SetPVarInt(playerid, "PlayerInAFK", 0);
	return 1;
}

stock afkcount_OnPlayerUpdate(playerid)
{
	if(GetPVarInt(playerid, "PlayerInAFK") > -2)
	{
		if(GetPVarInt(playerid, "PlayerInAFK") > 2) SetPlayerChatBubble(playerid, "{FF0000}АФК: {FFFFFF}завершено", COLOUR_WHITE, 20.0, 500);
		SetPVarInt(playerid, "PlayerInAFK", 0);
	}
	return 1;
}


forward AFKSystem();
public AFKSystem()
{
	for(new playerid;playerid < GetMaxPlayers();playerid++)
	{
		if(IsPlayerConnected(playerid))
		{
			if(GetPVarInt(playerid, "PlayerInAFK") == 0) SetPVarInt(playerid, "PlayerInAFK", -1);
			else if(GetPVarInt(playerid, "PlayerInAFK") == -1)
			{
				SetPVarInt(playerid, "PlayerInAFK", 1);
				new string[56];
				format(string, sizeof(string), "{FF0000}АФК: {FFFFFF}%s", ConvertSeconds(GetPVarInt(playerid, "PlayerInAFK")));
				SetPlayerChatBubble(playerid, string, 0xFFFF00AA, 20.0, 1200);
			}
			else if(GetPVarInt(playerid, "PlayerInAFK") > 0)
			{
				new string[56];
				SetPVarInt(playerid, "PlayerInAFK", GetPVarInt(playerid, "PlayerInAFK")+1);
				format(string, sizeof(string), "{FF0000}АФК: {FFFFFF}%s", ConvertSeconds(GetPVarInt(playerid, "PlayerInAFK")));
				SetPlayerChatBubble(playerid, string, 0xFFFF00AA, 20.0, 1200);
			}
		}
	}
}

stock ConvertSeconds(time)
{
	new string[128];
	if(time < 60) format(string, sizeof(string), "%d секунд", time);
	else if(time == 60) string = "1 минуту";
	else if(time > 60 && time < 3600)
	{
		new Float: minutes;
		new seconds;
		minutes = time / 60;
		seconds = time % 60;
		format(string, sizeof(string), "%.0f:%d", minutes, seconds);
	}
	else if(time == 3600) string = "1 час";
	else if(time > 3600)
	{
		new Float: hours;
		new minutes_int;
		new Float: minutes;
		new seconds;
		hours = time / 3600;
		minutes_int = time % 3600;
		minutes = minutes_int / 60;
		seconds = minutes_int % 60;
		format(string, sizeof(string), "%.0f:%.0f:%d", hours, minutes, seconds);
	}
	return string;
}