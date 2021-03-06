new GruzRab[MAX_PLAYERS], GruzSkinRab[MAX_PLAYERS];
new dollar = CARGO_MONEY;

stock cargo_OnGameModeInit()
{
	CreatePickup(1275, 23, 2729.9500 ,-2451.5605, 17.5937, -1); 
	CreatePickupText("������ ��������", 2729.9500, -2451.5605, 17.5937); 
	return 1;
}

stock c_OnPlayerEnterRaceCheckpoint(playerid)
{
	if(GruzRab[playerid] == 1)
	{
		ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1,0,1,1,1,1);
		SetPlayerSpecialAction (playerid, SPECIAL_ACTION_CARRY);
		SetPlayerAttachedObject(playerid, 2, 2060, 5, 0.01, 0.1, 0.2, 100, 10, 85);
		SendClientMessage(playerid, COLOUR_WHITE, "�� ����� ����, �������� ��� �� '�������' ��������");
		DisablePlayerCheckpoint(playerid);
		GruzRab[playerid] = 2;
		SetPlayerRaceCheckpoint(playerid, 2, 2776.0332,-2545.7766,13.6349, 0.0, 0.0, 0.0, 1);
		return true;
	}
	if(GruzRab[playerid] == 2)
	{
		RemovePlayerAttachedObject(playerid, 2);
		SetPlayerSpecialAction (playerid, SPECIAL_ACTION_NONE);
		new string[128]; 
		oGivePlayerMoney(playerid, dollar);
		format(string,sizeof(string), "{FFFFFF}�� ���������� {00FF00}%d$", dollar);
		SendClientMessage(playerid, -1, string);
		DisablePlayerCheckpoint(playerid);
		GruzRab[playerid] = 1;
		SetPlayerRaceCheckpoint(playerid, 2, 2845.1946,-2401.6255,12.0883, 0.0, 0.0, 0.0, 1);
		ApplyAnimation(playerid, "PED", "IDLE_tired", 4.1,0,1,1,0,1); 
		return true;
	}
	return 1;
}

stock cargo_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	#pragma unused oldkeys, newkeys
	if(GruzRab[playerid] == 0)
	{
		ShowPlayerDialog(playerid, cargo_DialogID, DIALOG_STYLE_MSGBOX, "���������� �� ������", "�� ������� ���������� �� ������?\n�� ������ ���������� ����� �� �������� 10000$", "��", "���");
	}
	else
	{
		ShowPlayerDialog(playerid, cargo_DialogID, DIALOG_STYLE_MSGBOX, "��������� � ������", "�� ������� ��������� � ������?", "��", "���");
	}
	return 1;
}

stock IsPlayerAtCargo(playerid)
{
	if (IsPlayerInRangeOfPoint(playerid, 2, 2729.9500, -2451.5605, 17.5937))
	{
		return 1;
	}
	return -1;
}


stock cargo_OnPlayerDeath(playerid)
{
	GruzRab[playerid] = 0;
	SetPlayerSkin(playerid, GruzSkinRab[playerid]);
	DisablePlayerRaceCheckpoint(playerid);
	RemovePlayerAttachedObject(playerid, 2);
	SetPlayerSpecialAction (playerid, SPECIAL_ACTION_NONE);
	SendClientMessage(playerid, COLOUR_WHITE, "�� ������, ������ �� ����� ���������� ����������!");
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
				GruzSkinRab[playerid] = GetPlayerSkin(playerid);
				SetPlayerSkin(playerid, 36);
				GruzRab[playerid] = 1;
				SendClientMessage(playerid, COLOUR_WHITE, "�� ���������� �� ������!");
				SendClientMessage(playerid, COLOUR_WHITE, "�� ����� ������� '�������' ��������, ������� �� ����.");
				SendClientMessage(playerid, COLOUR_WHITE, "����� �������� ������ '�������' ��������, �������� �����.");
				SetPlayerRaceCheckpoint(playerid, 2, 2845.1946,-2401.6255,12.0883, 0.0, 0.0, 0.0, 1);
				return true;
			}
			else
			{
				GruzRab[playerid] = 0;
				SetPlayerSkin(playerid, GruzSkinRab[playerid]);
				DisablePlayerRaceCheckpoint(playerid);
				RemovePlayerAttachedObject(playerid, 2);
				SetPlayerSpecialAction (playerid, SPECIAL_ACTION_NONE);
				SendClientMessage(playerid, COLOUR_WHITE, "�� ��������� � ������!");
			}
		}
	}
	return 1;
}