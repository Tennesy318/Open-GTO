stock chat_OnPlayerText(playerid, text[])
{
    if (!IsPlayerLogin(playerid))
    {
        SendClientMessage(playerid, -1, lang_texts[1][46]);
        return 0;
    }
    if (chatguard_OnPlayerText(playerid, text) == 0) return 0;

    for (new i = strlen(text) - 1; i != -1; i--) {
        if (text[i] == '%') {
            text[i] = '#';
        }
    }

    new playername[MAX_PLAYER_NAME+1];
    GetPlayerName(playerid, playername, sizeof(playername));

    new vip_prefix[16];
    if(GetPlayerVIP(playerid))
    {
        strcat(vip_prefix, "[VIP] ");
    }

    new string[MAX_STRING];
    switch (text[0])
    {
        case '!':
        {
            if (GetPVarInt(playerid, "GangID") == 0 || GetPlayerMuteTime(playerid) > 0)
            {
                SendClientMessage(playerid, COLOUR_RED, lang_texts[1][14]);
                return 0;
            }
            if (strlen(text[1]) < 2) return 0;
            format(string, sizeof(string), "%s"CHAT_SHOW_ID" банде: {FFFFFF}%s", playername, playerid, text[1]);
            SendGangMessage(GetPVarInt(playerid, "GangID"), string, COLOUR_GANG_CHAT);
            format(string, sizeof(string), "Player: %s"CHAT_SHOW_ID": <GANG CHAT>: %s", playername, playerid, text[1]);
            WriteLog(ChatLog, string);
            return 0;
        }
        case '@','"':
        {
            if (strlen(text[1]) < 2) return 0;
            SendClientMessageToAdmins(playerid, text[1]);
            format(string, sizeof(string), "Player: %s"CHAT_SHOW_ID": <ADMIN TALK>: %s", playername, playerid, text[1]);
            WriteLog(ChatLog, string);
            return 0;
        }
        case '#','№':
        {
            if (strlen(text[1]) < 2) return 0;
            SendClientMessageToModers(playerid, text[1]);
            format(string, sizeof(string), "Player: %s"CHAT_SHOW_ID": <MODERATOR TALK>: %s", playername, playerid, text[1]);
            WriteLog(ChatLog, string);
            return 0;
        }
        case '$',';':
        {
            if (strlen(text[1]) < 2) return 0;
            if (GetPlayerMuteTime(playerid) > 0)
            {
                SendClientMessage(playerid, COLOUR_RED, lang_texts[1][14]);
                return 0;
            }
            SendClientMessageToBeside(playerid, 10, text[1]);
            format(string, sizeof(string), "Player: %s"CHAT_SHOW_ID": <SAY>: %s", playername, playerid, text[1]);
            WriteLog(ChatLog, string);
            return 0;
        }
    }
    if (GetPlayerMuteTime(playerid) != 0)  //Заткнут
    {
        SendClientMessage(playerid, COLOUR_RED, lang_texts[1][14]);
        return 0;
    }
    format(string, sizeof(string), "%s%s"CHAT_SHOW_ID": {FFFFFF}%s", vip_prefix, playername, playerid, text);
    SendClientMessageToAll(GetPlayerColor(playerid), string);
    format(string, sizeof(string), "Player: %s"CHAT_SHOW_ID": %s", playername, playerid, text);
    WriteLog(ChatLog, string);
    return 1;
}