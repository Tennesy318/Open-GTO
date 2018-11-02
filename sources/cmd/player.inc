/*

    ??????? ??????

*/

	CMD:commands(playerid, params[]) {
		SendClientMessage(playerid, COLOUR_PURPLE, lang_texts[15][15]);
		SendClientMessage(playerid, COLOUR_PURPLE, lang_texts[15][16]);
		SendClientMessage(playerid, COLOUR_LIGHTGREEN, lang_texts[15][17]);
		SendClientMessage(playerid, COLOUR_PURPLE, lang_texts[15][18]);
		SendClientMessage(playerid, COLOUR_PURPLE, lang_texts[15][19]);
		SendClientMessage(playerid, COLOUR_PURPLE, lang_texts[15][20]);
		SendClientMessage(playerid, COLOUR_PURPLE, lang_texts[15][24]);
		SendClientMessage(playerid, COLOUR_PURPLE, lang_texts[15][25]);
		SendClientMessage(playerid, COLOUR_PURPLE, lang_texts[15][27]);
		SendClientMessage(playerid, COLOUR_LIGHTRED, lang_texts[15][28]);
		SendClientMessage(playerid, COLOUR_WHITE, lang_texts[15][29]);
		return 1;
	}

    CMD:help(playerid, params[]) {
		SendClientMessage(playerid, COLOUR_WHITE, lang_texts[15][2]);
		SendClientMessage(playerid, COLOUR_LIGHTRED, lang_texts[15][3]);
		SendClientMessage(playerid, COLOUR_WHITE, lang_texts[15][4]);
		SendClientMessage(playerid, COLOUR_WHITE, lang_texts[15][5]);
		return 1;
	}

    CMD:info(playerid, params[]) {
		new string[MAX_STRING * 9];
		strcat(string, lang_texts[15][6], sizeof(string));
		strcat(string, lang_texts[15][7], sizeof(string));
		strcat(string, lang_texts[15][8], sizeof(string));
		strcat(string, lang_texts[15][9], sizeof(string));
		strcat(string, lang_texts[15][10], sizeof(string));
		strcat(string, lang_texts[15][11], sizeof(string));
		strcat(string, lang_texts[15][12], sizeof(string));
		strcat(string, lang_texts[15][13], sizeof(string));
		strcat(string, lang_texts[15][14], sizeof(string));
		show_Msg_Dialog(playerid, "??????????", string, "??");
		return 1;
	}

	/*

		Fan commands

	*/

	CMD:handsup(playerid, params[]) {
		if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_HANDSUP);
		}	
		return 1;
	}

	CMD:piss(playerid, params[]) {
		if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_PISS);
		}
		return 1;
	}	

	CMD:smoke(playerid, params[]) {
		if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
		}
		return 1;	
	}