new Gruz, GruzRab[MAX_PLAYERS], GruzSkinRab[MAX_PLAYERS];

stock cargo_OnGameModeInit()
{
        Gruz = CreatePickup(1559, 23, 215.8651,14.5055,2.5708, -1); 
        Create3DTextLabel("Устроиться на работу",COLOUR_GREEN, 215.8651,14.5055,2.5708, 10, 0, 1); 
        return 1;
}

stock cargo_OnPlayerEnterRaceCheckpoint(playerid)
{
	if(GruzRab[playerid] == 1)
	{
		ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1,0,1,1,1,1); // Анимация
		SetPlayerSpecialAction (playerid, SPECIAL_ACTION_CARRY); // Специальная анимация не дающая игроку любые возможности движение кроме ходьбы
		SetPlayerAttachedObject(playerid, 2, 2060, 5, 0.01, 0.1, 0.2, 100, 10, 85); // объект
		SendClientMessage(playerid, COLOUR_GREEN, "Вы взяли груз, отнесите его на 'Красный' чекпоинт");
		DisablePlayerCheckpoint(playerid); // убратие чекпоинта
		GruzRab[playerid] = 2; // переменная для следующего чекпоинта
		SetPlayerRaceCheckpoint(playerid, 2, 206.5291,-7.8562,2.5781, 0.0, 0.0, 0.0, 5); // сам чекпоинт (занести в определенное место!)
		return true;
	}
	if(GruzRab[playerid] == 2)
	{
		RemovePlayerAttachedObject(playerid, 2); // удаление объекта
		SetPlayerSpecialAction (playerid, SPECIAL_ACTION_NONE); // убратие функции специальной (выше писал)
		new dollar = 1000, string[128]; // переменная для рандома
		oGivePlayerMoney(playerid, dollar); // поставите свою PlayerInfo и т.д
		format(string,sizeof(string), "{FFFFFF}Вы заработали {00FF00}%d$", dollar);
		SendClientMessage(playerid, -1, string);
		DisablePlayerCheckpoint(playerid);
		GruzRab[playerid] = 1;
		SetPlayerRaceCheckpoint(playerid, 2, 212.4893,23.5777,2.5708, 0.0, 0.0, 0.0, 5); // забрать груз.
		ApplyAnimation(playerid, "PED", "IDLE_tired", 4.1,0,1,1,0,1); // восстановление анимации.
		return true;
	}
	return 1;
}

stock cargo_OnPlayerPickUpPickup(playerid, pickupid)
{
	//=== Грузчик
	if(pickupid == Gruz) // не буду объяснять и так всё понятно.
	{
		if(GruzRab[playerid] == 0)// если вы не работаете
		{
			ShowPlayerDialog(playerid, cargo_DialogID, DIALOG_STYLE_MSGBOX, "Устроиться на работу", "Вы желаете устроиться на работу?", "Да", "Нет");
		}
		else // если вы работаете.
		{
			ShowPlayerDialog(playerid, cargo_DialogID, DIALOG_STYLE_MSGBOX, "Уволиться с работы", "Вы желаете уволиться с работы?", "Да", "Нет");
		}
	}
	return 1;
}

stock cargo_OnDialogResponse(playerid, dialogid, response)
{
	switch (dialogid)
	{
		case cargo_DialogID:
		{
			if(!response) return true;
			if(GruzRab[playerid] == 0)
			{
				GruzRab[playerid] = 1;
				GruzSkinRab[playerid] = GetPlayerSkin(playerid); // а вот для чего и нужен был он - узнать ваш скин , а после увольнения восстановить его.
				SetPlayerSkin(playerid, 36);
				SendClientMessage(playerid, COLOUR_GREEN, "Вы устроились на работу!");
				SendClientMessage(playerid, COLOUR_GREEN, "На карте отмечен 'Красный' чекпоинт, зайдите на него.");
				SendClientMessage(playerid, COLOUR_GREEN, "После появится другой 'Красный' чекпоинт, отнесите мешок.");
				SetPlayerRaceCheckpoint(playerid, 2, 212.4893,23.5777,2.5708, 0.0, 0.0, 0.0, 5); // этот чекпоинт для забратие груза.
				return true;
			}
			else
			{
				GruzRab[playerid] = 0;
				SetPlayerSkin(playerid, GruzSkinRab[playerid]); // вот как раз такие и возвращение скина.
				DisablePlayerRaceCheckpoint(playerid);
				SendClientMessage(playerid, COLOUR_GREEN, "Вы уволились с работы!");
			}
		}
	}
	return 1;
}