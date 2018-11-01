/*

    Команды для игрока

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