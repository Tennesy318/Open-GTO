/*
	Created: 05.09.06
	Aurthor: Iain Gilbert
	Modified by ziggi
*/


#if defined _weapons_included
	#endinput
#endif

#define _weapons_included
#pragma library weapons


#include "base"

#define MAX_BULLETS				9000

stock WeaponLoadAll()
{
	if (ini_Exist(ConfigDB))
	{
		new file_weapons_cfg = ini_Open(ConfigDB);
		ini_Get(file_weapons_cfg, "Weapon_DB", WeaponDB);
		ini_Close(file_weapons_cfg);
	}

	new file_weapons, weapondbname[MAX_STRING];
	for (new i = 0; i < sizeof(Weapons); i++)
	{
		format(weapondbname, sizeof(weapondbname), "%sid_%d"GTO_FILES_FORMAT, WeaponDB, Weapons[i][Weapon_ID]);
		if (!ini_Exist(weapondbname))
		{
			continue;
		}
		file_weapons = ini_Open(weapondbname);
		ini_Get(file_weapons, "Name", Weapons[i][Weapon_Name], MAX_NAME);
		ini_GetInt(file_weapons, "IsAllowed", Weapons[i][Weapon_Allowed]);
		ini_GetInt(file_weapons, "Level", Weapons[i][Weapon_Level]);
		ini_GetInt(file_weapons, "Price", Weapons[i][Weapon_Cost]);
		ini_Close(file_weapons);
	}
	return 1;
}

stock WeaponSaveAll()
{
	new file_weapons_cfg = (!ini_Exist(ConfigDB)) ? ini_Create(ConfigDB) : ini_Open(ConfigDB);
	ini_Set(file_weapons_cfg, "Weapon_DB", WeaponDB);
	ini_Close(file_weapons_cfg);

	new file_weapons, weapondbname[MAX_STRING];
	for (new i = 0; i < sizeof(Weapons); i++)
	{
		format(weapondbname, sizeof(weapondbname), "%sid_%d"GTO_FILES_FORMAT, WeaponDB, Weapons[i][Weapon_ID]);
		file_weapons = (!ini_Exist(weapondbname)) ? ini_Create(weapondbname) : ini_Open(weapondbname);
		ini_Set(file_weapons, "Name", Weapons[i][Weapon_Name]);
		ini_SetInt(file_weapons, "IsAllowed", Weapons[i][Weapon_Allowed]);
		ini_SetInt(file_weapons, "Level", Weapons[i][Weapon_Level]);
		ini_SetInt(file_weapons, "Price", Weapons[i][Weapon_Cost]);
		ini_Close(file_weapons);
	}
	return 1;
}

stock weapons_OnGameModeInit()
{
	for (new id = 0; id < sizeof(Ammunations); id++)
	{
		CreatePickup(1247, 1, Ammunations[id][Coord_X], Ammunations[id][Coord_Y], Ammunations[id][Coord_Z]);
		CreatePickupText("Оружие", Ammunations[id][Coord_X], Ammunations[id][Coord_Y], Ammunations[id][Coord_Z]);
	}
	GameMSG("SERVER: Weapons module init");
}

stock weapons_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	#pragma unused oldkeys, newkeys
	weapons_ShowDialog_Select(playerid);
	return 1;
}

stock IsPlayerAtAmmunation(playerid)
{
	for (new id = 0; id < sizeof(Ammunations); id++)
	{
		if (IsPlayerInRangeOfPoint(playerid, 2, Ammunations[id][Coord_X], Ammunations[id][Coord_Y], Ammunations[id][Coord_Z]))
		{
			return id;
		}
	}
	return -1;
}

stock oGetWeaponName(weaponid)
{
	new name[MAX_NAME],
		lookupid = GetWeaponLookupID(weaponid);

	if (lookupid == -1)
	{
		return name;
	}
	set(name, Weapons[lookupid][Weapon_Name]);
	return name;
}

stock GetWeaponMaxAmmo(weaponid)
{
	new lookupid = GetWeaponLookupID(weaponid);
	if (lookupid == -1)
	{
		return 0;
	}
	if (Weapons[lookupid][Weapon_IsFirearm] == 1)
	{
		return MAX_BULLETS;
	}
	return 1;
}

stock IsPlayerAllowedWeapon(playerid, weaponid)
{
	new lookupid = GetWeaponLookupID(weaponid);
	if (lookupid == -1 || Weapons[lookupid][Weapon_Allowed] == 0 || Weapons[lookupid][Weapon_Level] > GetPlayerLevel(playerid))
	{
		return 0;
	}
	return 1;
}

stock IsWeaponHandToHand(weaponid)
{
	new lookupid = GetWeaponLookupID(weaponid);
	if (lookupid == -1)
	{
		return 0;
	}
	if (Weapons[lookupid][Weapon_IsFirearm] == 0)
	{
		return 1;
	}
	return 0;
}

stock GetWeaponCost(weaponid)
{
	new lookupid = GetWeaponLookupID(weaponid);
	if (lookupid == -1)
	{
		return 0;
	}
	return Weapons[lookupid][Weapon_Cost];
}

stock GetWeaponLookupID(weaponid)
{
	for (new i = 0; i < sizeof(Weapons); i++)
	{
		if (weaponid == Weapons[i][Weapon_ID])
		{
			return i;
		}
	}
	return -1;
}

stock IsWeapon(weaponid)
{
	switch (weaponid)
	{
		case 0..46: return 1;
	}
	return 0;
}

stock BuyWeapon(playerid, weaponid, bullets)
{
	new string[MAX_STRING];
	if (weaponid < 0 || weaponid > 47) {
		SendClientMessage(playerid, COLOUR_RED, lang_texts[16][7]);
		return 0;
	}
	if (bullets < 1) {
		SendClientMessage(playerid, COLOUR_RED, lang_texts[16][8]);
		return 0;
	}
	if (weaponid > 0 && weaponid < 47) {
		new
			weapon_slot = GetWeaponSlot(weaponid),
			current_weapon = GetPlayerWeaponSlotID(playerid, weapon_slot),
			current_bullets = GetPlayerWeaponSlotBullet(playerid, weapon_slot);

		if (current_bullets >= MAX_BULLETS && weaponid == current_weapon) {
			SendClientMessage(playerid, COLOUR_RED, lang_texts[16][1]);
			return 0;
		}

		if (current_bullets + bullets > MAX_BULLETS && weaponid == current_weapon) {
			SendClientMessage(playerid, COLOUR_RED, lang_texts[16][1]);
			bullets = MAX_BULLETS - current_bullets;
			if (bullets < 1) {
				return 0;
			}
		}

		if (bullets > MAX_BULLETS) {
			SendClientMessage(playerid, COLOUR_RED, lang_texts[16][1]);
			bullets = MAX_BULLETS;
		}
	}
	if (IsPlayerAtAmmunation(playerid) == -1) {
		SendClientMessage(playerid, COLOUR_RED, lang_texts[16][9]);
		return 0;
	}
	if (!IsPlayerAllowedWeapon(playerid, weaponid)) {
		format(string, sizeof(string), lang_texts[16][10], oGetWeaponName(weaponid));
		SendClientMessage(playerid, COLOUR_RED, string);
		return 0;
	}
	new purchasecost = GetWeaponCost(weaponid) * bullets;
	if (purchasecost < 1) {
		format(string, sizeof(string), lang_texts[16][11], oGetWeaponName(weaponid));
		SendClientMessage(playerid, COLOUR_RED, string);
		return 0;
	}
	if (oGetPlayerMoney(playerid) < purchasecost) {
		format(string, sizeof(string), lang_texts[16][12], purchasecost);
		SendClientMessage(playerid, COLOUR_RED, string);
		return 0;
	}
	oGivePlayerMoney(playerid,-purchasecost, 1);
	switch (weaponid) {
		case 47: oSetPlayerArmour(playerid, 100.0);
		case 37: GivePlayerOwnedWeapon(playerid, weaponid, bullets * 10); // фикс для количества патрон огнемёта
		default: GivePlayerOwnedWeapon(playerid, weaponid, bullets);
	}
	if (bullets > 1) {
		format(string, sizeof(string), lang_texts[16][13], bullets, oGetWeaponName(weaponid), purchasecost);
	} else {
		format(string, sizeof(string), lang_texts[16][14], oGetWeaponName(weaponid), purchasecost);
	}
	SendClientMessage(playerid, COLOUR_RED, string);
	SendClientMessage(playerid, COLOUR_RED, lang_texts[16][15]);
	return 1;
}

stock weapons_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch (dialogid)
	{
		case weapons_Select_DialogID: // Выбираем оружие из списка
		{
			if (!response)
			{
				return 0;
			}
			new weaponid = GetSelectedWeaponID(playerid, listitem);
			SetPVarInt(playerid, "Buy_Weapon_ID", weaponid);
			weapons_ShowDialog_Buy(playerid, weaponid);
			return 1;
		}
		case weapons_Buy_DialogID: // Покупаем, вводим патроны
		{
			if (!response)
			{
				return weapons_ShowDialog_Select(playerid);
			}
			new bullets = strval(inputtext);
			if (GetPVarInt(playerid, "weapons_Buy_One_Bullet") == 1)
			{
				bullets = 1;
				DeletePVar(playerid, "weapons_Buy_One_Bullet");
			}
			BuyWeapon(playerid, GetPVarInt(playerid, "Buy_Weapon_ID"), bullets);
			weapons_ShowDialog_Select(playerid);
			return 1;
		}
	}
	return 1;
}

stock weapons_ShowDialog_Select(playerid)
{
	new string[ sizeof(Weapons) * (MAX_NAME + 12 + 4) ];
	for (new weaponid = 1; weaponid < sizeof(Weapons); weaponid++)
	{
		if (!IsPlayerAllowedWeapon(playerid, weaponid))
		{
			continue;
		}
		format(string, sizeof(string), "%s%s, цена $%d\n", string, oGetWeaponName(weaponid), GetWeaponCost(weaponid));
	}
	return ShowPlayerDialog(playerid, weapons_Select_DialogID, DIALOG_STYLE_LIST,
		"Меню оружия",
		string,
		"Выбрать", "Выход"
	);
}

stock weapons_ShowDialog_Buy(playerid, weaponid)
{
	new string[MAX_STRING], dialog_style = DIALOG_STYLE_INPUT;
	if (Weapons[ GetWeaponLookupID(weaponid) ][Weapon_IsFirearm] == 0)
	{
		format(string, sizeof(string), "Оружие: %s\nЦена: $%d", oGetWeaponName(weaponid), GetWeaponCost(weaponid));
		dialog_style = DIALOG_STYLE_MSGBOX;
		SetPVarInt(playerid, "weapons_Buy_One_Bullet", 1);
	}
	else if (Weapons[ GetWeaponLookupID(weaponid) ][Weapon_IsFirearm] == 1)
	{
		new
			weapon_slot = GetWeaponSlot(weaponid),
			max_bullets = oGetPlayerMoney(playerid) / GetWeaponCost(weaponid);

		if (weaponid == GetPlayerWeaponSlotID(playerid, weapon_slot)) {
			new current_bullets = GetPlayerWeaponSlotBullet(playerid, weapon_slot);
			if (max_bullets + current_bullets > MAX_BULLETS) {
				max_bullets = MAX_BULLETS - current_bullets;
			}
		} else {
			if (max_bullets > MAX_BULLETS) {
				max_bullets = MAX_BULLETS;
			}
		}

		format(string, sizeof(string),
			"Оружие: %s\nЦена за 1 патрон: $%d\nВы можете купить %d патронов\n\nВведите количество патронов:",
			oGetWeaponName(weaponid), GetWeaponCost(weaponid), max_bullets
		);
	}
	return ShowPlayerDialog(playerid, weapons_Buy_DialogID, dialog_style,
		"Покупка оружия",
		string,
		"Купить", "Назад"
	);
}

// узнаёт ид оружия по нажатию в диалоге
stock GetSelectedWeaponID(playerid, listitem)
{
	new k = 0;
	for (new weaponid = 1; weaponid < sizeof(Weapons); weaponid++)
	{
		if (IsPlayerAllowedWeapon(playerid, weaponid))
		{
			k++;
			if (listitem+1 == k)
			{
				return weaponid;
			}
		}
	}
	return 0;
}
//

// показывает доступное оружие на уровне
stock ShowWeaponsOnLevel(playerid, newlevel, oldlevel)
{
	new string[MAX_STRING],
		wepfound = 0;

	for (new weaponid = 1; weaponid < sizeof(Weapons); weaponid++)
	{
		new lookupid = GetWeaponLookupID(weaponid);
		if (lookupid == -1 || Weapons[lookupid][Weapon_Allowed] == 0)
		{
			continue;
		}
		if (Weapons[lookupid][Weapon_Level] > oldlevel && Weapons[lookupid][Weapon_Level] <= newlevel)
		{
			if (wepfound == 0)
			{
				SendClientMessage(playerid, COLOUR_GREEN, lang_texts[9][24]);
				wepfound = 1;
			}
			format(string, sizeof(string), lang_texts[9][25], oGetWeaponName(weaponid), GetWeaponCost(weaponid));
			SendClientMessage(playerid, COLOUR_MISC, string);
		}
	}
	return 1;
}
//
