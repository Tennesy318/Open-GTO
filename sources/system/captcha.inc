stock RandomString() {
    new string[8];
    format(string, 8, "%c%c%i%c", 65+random(26), 65+random(26), 100+random(899), 65+random(26));
    return string;
} 

stock ShowCaptcha(playerid)
{
    new string[64];
    format(string, 64, "%s", RandomString());
    SetPVarString(playerid, "Captcha", string);
    format(string, 64, "Введите, пожалуйста, код ниже:\n{FFA000}%s", string);
    ShowPlayerDialog(playerid, captcha_DialogID, 1, "\tCaptcha проверка", string, "Ввод", "");
    return 1;
} 

stock captcha_OnDialogResponse(playerid, dialogid, response, inputtext[])
{
	switch (dialogid)
	{
		case captcha_DialogID:
		{
			new string[32];
			if (!response || strlen(inputtext) < 6)
			return ShowCaptcha(playerid);

			GetPVarString(playerid, "Captcha", string, 32);
			if(strcmp(string, inputtext, true) != 0)
			return SendClientMessage(playerid, 0xFFFA00FF, "Каптча-код введён неправльно!"), ShowCaptcha(playerid);
		}
	}
	return 1;
}