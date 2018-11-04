/*

	Описание: магазин двух-колёсного транспорта

*/


stock bikeshop_OnGameModeInit()
{
	bikeshop_ChangeVehicles();
	return 1;
}

stock bikeshop_OnPlayerStateChange(playerid, newstate, oldstate)
{
	#pragma unused newstate, oldstate
	if (bikeshop_IsShopVehicle( GetPlayerVehicleID(playerid) )) {
		bikeshop_ShowBuyDialog(playerid);
	}
	return 1;
}

stock bikeshop_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem, inputtext
	if (dialogid == bikeshop_DialogID) {
		RemovePlayerFromVehicle(playerid);
		if (!response) {
			return 0;
		}
		if (GetPlayerVehicleCount(playerid) >= GetPlayerVehicleMaximumCount(playerid)) {
			show_Msg_Dialog(playerid, "Магазин мотоциклетного транспорта", "У вас максимальное количество транспорта", "ОК");
			return 0;
		}
		
		new vehicleid = GetPlayerVehicleID(playerid);
		new cost = GetVehicleCost( GetVehicleModel(vehicleid) );
		
		if (oGetPlayerMoney(playerid) < cost) {
			show_Msg_Dialog(playerid, "Магазин мотоциклетного транспорта", "У вас недостаточно денег", "ОК");
			return 0;
		}
		
		oGivePlayerMoney(playerid, -cost, 1);
		buyMVehicle(playerid, vehicleid);
		
		show_Msg_Dialog(playerid, "Магазин мотоциклетного транспорта", "\
			Вы успешно купили этот мотоциклетный транспорт.\n\
			Чтобы вызвать мотоциклетный транспорт, зайдите в меню пользователя и выберите его.",
			"ОК"
		);
		return 1;
	}
	return 1;
}

stock bikeshop_OnVehicleSpawn(vehicleid)
{
	if (bikeshop_IsShopVehicle(vehicleid)) {
		SetVehicleFuel(vehicleid, 0);
	}
	return 1;
}

stock bikeshop_SetVehiclesToRespawn()
{
	for (new i = 0; i < sizeof(bikeshop_Vehicles); i++) {
		new Float:dist = GetVehicleDistanceFromPoint(bikeshop_Vehicles[i][vshop_ID], bikeshop_Vehicles[i][vshop_X], bikeshop_Vehicles[i][vshop_Y], bikeshop_Vehicles[i][vshop_Z]);
		if (dist >= 4.0) {
			SetVehicleToRespawn(bikeshop_Vehicles[i][vshop_ID]);
		}
	}
}

stock bikeshop_ChangeVehicles()
{
	new string[MAX_STRING], model;
	for (new i = 0; i < sizeof(bikeshop_Vehicles); i++) {
		if (bikeshop_Vehicles[i][vshop_ID] != 0) {
			// если кто-то есть в транспорте
			foreach (new playerid : Player) {
				if (bikeshop_Vehicles[i][vshop_ID] == GetPlayerVehicleID(playerid)) {
					HideDialog(playerid);
					RemovePlayerFromVehicle(playerid);
				}
			}
			// удаляем транспорт
			DestroyVehicle(bikeshop_Vehicles[i][vshop_ID]);
			Delete3DTextLabel(bikeshop_Vehicles[i][vshop_Text3D]);
		}
		
		model = bikeshop_VehiclesModels[ random( sizeof(bikeshop_VehiclesModels) ) ];
		bikeshop_Vehicles[i][vshop_ID] = CreateVehicle(model,
			bikeshop_Vehicles[i][vshop_X], bikeshop_Vehicles[i][vshop_Y], bikeshop_Vehicles[i][vshop_Z], bikeshop_Vehicles[i][vshop_A],
			colors_Array[ random( sizeof(colors_Array) ) ][color_vehicle], colors_Array[ random( sizeof(colors_Array) ) ][color_vehicle], 0
		);
		SetVehicleFuel(bikeshop_Vehicles[i][vshop_ID], 0);
		
		format(string, sizeof(string), "{CCFF66}%s\n{CCCCCC}Цена: {FFFFFF}$%d\n{999999}Сядьте для покупки", GetVehicleName(model), GetVehicleCost(model));
		bikeshop_Vehicles[i][vshop_Text3D] = Create3DTextLabel(string, COLOUR_WHITE, bikeshop_Vehicles[i][vshop_X], bikeshop_Vehicles[i][vshop_Y], bikeshop_Vehicles[i][vshop_Z], 20.0, 0, 1);
		Attach3DTextLabelToVehicle(bikeshop_Vehicles[i][vshop_Text3D], bikeshop_Vehicles[i][vshop_ID], 0.0, 0.0, 0.2);
	}
}

stock bikeshop_OneHourTimer()
{
	static hours;
	hours++;
	
	if (hours >= bikeshop_CAR_CHANGE_TIME) {
		hours = 0;
		bikeshop_ChangeVehicles();
	}
}

stock buyMVehicle(playerid, vehicleid)
{
	new model = GetVehicleModel(vehicleid);
	AddPlayerVehicle(playerid, model, colors_Array[ random( sizeof(colors_Array) ) ][color_vehicle], colors_Array[ random( sizeof(colors_Array) ) ][color_vehicle], float(GetMaxVehicleFuel(model)));
	return 1;
}

stock bikeshop_ShowBuyDialog(playerid)
{
	new model = GetVehicleModel(GetPlayerVehicleID(playerid));
	new string[MAX_STRING];
	format(string, sizeof(string),
		"Вы хотите купить мотоциклетный транспорт '%s' за $%d?",
		GetVehicleName(model), GetVehicleCost(model)
	);
	return ShowPlayerDialog(playerid, bikeshop_DialogID, DIALOG_STYLE_MSGBOX,
		"Магазин мотоциклетного транспорта",
		string,
		"Купить", "Выйти"
	);
}

stock bikeshop_IsShopVehicle(vehicleid)
{
	for (new i = 0; i < sizeof(bikeshop_Vehicles); i++) {
		if (bikeshop_Vehicles[i][vshop_ID] == vehicleid) {
			return 1;
		}
	}
	return 0;
}