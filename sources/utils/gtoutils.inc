//
// Created:     05.09.06
// Aurthor:    Iain Gilbert
//
/*
	Модифицировал ZiGGi
*/

#if defined _gtoutils_included
  #endinput
#endif

#define _gtoutils_included
#pragma library gtoutils


#define command_register(%0,%1,%2,%3) if (!strcmp(%0,%1, true,%2) && ((%0[%2] == ' ') || (%0[%2] == 0))) return %3_OnPlayerCommandText(playerid,%0)
#define command_registerNR(%0,%1,%2,%3) if (!strcmp(%0,%1, true,%2) && ((%0[%2] == ' ') || (%0[%2] == 0))) %3_OnPlayerCommandText(playerid,%0)
#define GivePVarInt(%1,%2,%3) SetPVarInt(%1,%2, GetPVarInt(%1,%2)+%3)
#define set(%0,%1) strmid(%0,%1, 0, 160, MAX_STRING + 32)


stock strcmpEx(const string1[], const string2[], bool:ignorecase=false, length=cellmax)
{
    if (string1[0])
    {
        if (string2[0])
        {
            return strcmp(string1, string2, ignorecase, length);
        }
        else
        {
            // Positive as st1 is greater (strcmp spec).
            return 1;
        }
    }
    else
    {
        if (string2[0])
        {
            // Negative as str2 is greater.
            return -1;
        }
        else
        {
            // The strings are the same (empty).
            return 0;
        }
    }
}
#define strcmp strcmpEx

// from hardforum.ru/t47097/
stock DateToNum(year, month, day, hour=-1, minute=-1, second=-1)
{
	// count day in month
	static cdm[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
	
	// first sa-mp release
	year -= 2006;
	
	if (month < 1)
	{
		month = 1;
	}
	else if (month > 12) 
	{
		year += (month-1) / 12;
		month = ((month-1) % 12) + 1;
	}
	
	// convert [y, mo, d] -> num
	new num = 365 * year + (year / 4) - (year / 100) + (year / 400) + cdm[month - 1] + day;
	
	if (month > 2 && is_leap_year(year))
	{
		num++;
	}
	
	// convert day to second
	num *= 24 * 60 * 60;
	
	// add to num: [h, mi, s] -> num
	if (hour != -1 && minute != -1 && second != -1)
	{
		num += (hour * 60 * 60 + minute * 60 + second);
	}
	
	return num;
}

stock is_leap_year(year)
{
	return (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);
}

stock SendClientMessageToBeside(playerid, dist, text[])
{
	new string[MAX_STRING],
		Float:pos[3],
		color = GetPlayerColor(playerid);
	
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	format(string, sizeof(string), "$ %s"CHAT_SHOW_ID" говорит: {FFFFFF}%s", oGetPlayerName(playerid), playerid, text);
	foreach (Player, i)
	{
		if (IsPlayerInRangeOfPoint(i, dist, pos[0], pos[1], pos[2]))
		{
			SendClientMessage(i, color, string);
		}
	}
	return;
}

stock PlayerPlaySoundOnPlayer(playerid, soundid)
{
	new Float:pos[3];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	return PlayerPlaySound(playerid, soundid, pos[0], pos[1], pos[2]);
}

stock FormatPosition(position)
{
	new string[MAX_STRING];
	switch (position)
	{
		case 1: set(string, "1st!");
		case 2: set(string, "2nd!");
		case 3: set(string, "3rd!");
		default: format(string, sizeof(string), "%dth", position);
	}
	return string;
}

stock strcharsplit(const string[], &index, seperator=' ')
{
	new result[20], i = 0;
	if (index != 0 && string[index] != '\0') index++;
	while (string[index] && string[index] != seperator && string[index] != '\r' && string[index] != '\n')
	{
		result[i++] = string[index++];
	}
	return result;
}

stock Vary(source, varyamount)
{
	return source + random((varyamount*2)+1) - varyamount;
}

stock mathrandom(min, max)
{
	return (random(max - min + 1) + min);
}

stock NameCharCheck(string[MAX_PLAYER_NAME+1])
{
	if (!strcmp(string, "Unknown", true) || IsNumeric(string)) return 0;
	for (new i = strlen(string)-1; i >= 0; i--)
	{
		switch (string[i])
		{
			case ALLOWED_NICK_SYMBOLS: continue;
			default: return 0;
		}
	}
	if (IsIP(string))
	{
		return 0;
	}
	return 1;
}

stock PlayerCount()
{
	new count = 0;
	foreach (Player, playerid)
	{
		count++;
	}
	return count;
}

stock SetPlayerPosEx(playerid, Float:X, Float:Y, Float:Z, Float:Angle, Interior, World=0)
{
    SetPlayerInterior(playerid, Interior);
    SetPlayerFacingAngle(playerid, Angle);
	SetPlayerVirtualWorld(playerid, World);
    oSetPlayerPos(playerid, X, Y, Z);
    SetCameraBehindPlayer(playerid);
}

stock StringCharCheck(string[])
{
	for (new i = strlen(string)-1; i >= 0; i--)
	{
		switch (string[i])
		{
			case ALLOWED_STRING_SYMBOLS: continue;
			default: return 0;
		}
	}
	return 1;
}

stock IsNumeric(const string[])
{
	for (new i = strlen(string)-1; i >= 0; i--)
	{
		switch (string[i])
		{
			case '0'..'9': continue;
			default: return 0;
		}
	}
	return 1;
}

stock IsIP(string[])
{
	new bufer[MAX_STRING], start_pos = 0, end_pos = 0, len = strlen(string);
	do
	{
		end_pos = strfind(string, ".", false, end_pos+1);
		if (end_pos == -1)
		{
			end_pos = len;
		}
		strmid(bufer, string, start_pos, end_pos);
		if (IsNumeric(bufer) && strlen(bufer) <= 3 && strval(bufer) >= 0 && strval(bufer) <= 255)
		{
			start_pos = end_pos+1;
		}
		else
		{
			return 0;
		}
	} while (end_pos != len);
	return 1;
}

stock GetVehicleSpeed(vehicleid)
{
	new Float:pos[3];
	GetVehicleVelocity(vehicleid, pos[0], pos[1], pos[2]);
	return floatround( floatsqroot(pos[0]*pos[0] + pos[1]*pos[1] + pos[2]*pos[2]) * 100 );
}

#if defined USE_PASSWORD_ENCRYPT
// encrypt(string[]) by Alex "Y_Less" Cole, Based on code by Jeremy Cole
// modified by ZiGGi
stock encrypt(string[])
{
	new size = strlen(ENCRYPTION_KEY),
		retval[MAX_PASS_LEN],
		j = strlen(string),
		k = ((j >> 4) + 1) << 4,
		sum = j,
		tmp[] = {0, 0};
	
	for (new i = 0; i < k; i++)
	{
		tmp[0] = (i < j) ? string[i] : ' ';
		sum = ((sum + strfind(ENCRYPTION_KEY, tmp) + 1) % size);
		retval[i] = ENCRYPTION_KEY[sum];
	}
	return retval;
}
#endif

stock HideDialog(playerid)
{
	ShowPlayerDialog(playerid, -1, 0, " ", " ", " ", "");
}
