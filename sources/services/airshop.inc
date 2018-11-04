/*

	Описание: магазин воздушного транспорта

*/


stock airshop_OnGameModeInit()
{
	airshop_ChangeVehicles();
	return 1;
}

stock airshop_OnPlayerStateChange(playerid, newstate, oldstate)
{
	#pragma unused newstate, oldstate
	if (airshop_IsShopVehicle( GetPlayerVehicleID(playerid) )) {
		airshop_ShowBuyDialog(playerid);
	}
	return 1;
}

stock airshop_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem, inputtext
	if (dialogid == airshop_DialogID) {
		RemovePlayerFromVehicle(playerid);
		if (!response) {
			return 0;
		}
		if (GetPlayerVehicleCount(playerid) >= GetPlayerVehicleMaximumCount(playerid)) {
			show_Msg_Dialog(playerid, "Магазин воздушного транспорта", "У вас максимальное количество транспорта", "ОК");
			return 0;
		}
		
		new vehicleid = GetPlayerVehicleID(playerid);
		new cost = GetVehicleCost( GetVehicleModel(vehicleid) );
		
		if (oGetPlayerMoney(playerid) < cost) {
			show_Msg_Dialog(playerid, "Магазин воздушного транспорта", "У вас недостаточно денег", "ОК");
			return 0;
		}
		
		oGivePlayerMoney(playerid, -cost, 1);
		buyAVehicle(playerid, vehicleid);
		
		show_Msg_Dialog(playerid, "Магазин воздушного транспорта", "\
			Вы успешно купили этот воздушный транспорт.\n\
			Чтобы вызвать воздушный транспорт, зайдите в меню пользователя и выберите его.",
			"ОК"
		);
		return 1;
	}
	return 1;
}

stock airshop_OnVehicleSpawn(vehicleid)
{
	if (airshop_IsShopVehicle(vehicleid)) {
		SetVehicleFuel(vehicleid, 0);
	}
	return 1;
}

stock airshop_SetVehiclesToRespawn()
{
	for (new i = 0; i < sizeof(airshop_Vehicles); i++) {
		new Float:dist = GetVehicleDistanceFromPoint(airshop_Vehicles[i][vshop_ID], airshop_Vehicles[i][vshop_X], airshop_Vehicles[i][vshop_Y], airshop_Vehicles[i][vshop_Z]);
		if (dist >= 4.0) {
			SetVehicleToRespawn(airshop_Vehicles[i][vshop_ID]);
		}
	}
}

stock airshop_ChangeVehicles()
{
	new string[MAX_STRING], model;
	for (new i = 0; i < sizeof(airshop_Vehicles); i++) {
		if (airshop_Vehicles[i][vshop_ID] != 0) {
			// если кто-то есть в транспорте
			foreach (new playerid : Player) {
				if (airshop_Vehicles[i][vshop_ID] == GetPlayerVehicleID(playerid)) {
					HideDialog(playerid);
					RemovePlayerFromVehicle(playerid);
				}
			}
			// удаляем транспорт
			DestroyVehicle(airshop_Vehicles[i][vshop_ID]);
			Delete3DTextLabel(airshop_Vehicles[i][vshop_Text3D]);
		}
		
		model = airshop_VehiclesModels[ random( sizeof(airshop_VehiclesModels) ) ];
		airshop_Vehicles[i][vshop_ID] = CreateVehicle(model,
			airshop_Vehicles[i][vshop_X], airshop_Vehicles[i][vshop_Y], airshop_Vehicles[i][vshop_Z], airshop_Vehicles[i][vshop_A],
			colors_Array[ random( sizeof(colors_Array) ) ][color_vehicle], colors_Array[ random( sizeof(colors_Array) ) ][color_vehicle], 0
		);
		SetVehicleFuel(airshop_Vehicles[i][vshop_ID], 0);
		
		format(string, sizeof(string), "{CCFF66}%s\n{CCCCCC}Цена: {FFFFFF}$%d\n{999999}Сядьте для покупки", GetVehicleName(model), GetVehicleCost(model));
		airshop_Vehicles[i][vshop_Text3D] = Create3DTextLabel(string, COLOUR_WHITE, airshop_Vehicles[i][vshop_X], airshop_Vehicles[i][vshop_Y], airshop_Vehicles[i][vshop_Z], 20.0, 0, 1);
		Attach3DTextLabelToVehicle(airshop_Vehicles[i][vshop_Text3D], airshop_Vehicles[i][vshop_ID], 0.0, 0.0, 0.2);
	}
}

stock airshop_OneHourTimer()
{
	static hours;
	hours++;
	
	if (hours >= AIRSHOP_CAR_CHANGE_TIME) {
		hours = 0;
		airshop_ChangeVehicles();
	}
}

stock buyAVehicle(playerid, vehicleid)
{
	new model = GetVehicleModel(vehicleid);
	AddPlayerVehicle(playerid, model, colors_Array[ random( sizeof(colors_Array) ) ][color_vehicle], colors_Array[ random( sizeof(colors_Array) ) ][color_vehicle], float(GetMaxVehicleFuel(model)));
	return 1;
}

stock airshop_ShowBuyDialog(playerid)
{
	new model = GetVehicleModel(GetPlayerVehicleID(playerid));
	new string[MAX_STRING];
	format(string, sizeof(string),
		"Вы хотите купить воздушный транспорт '%s' за $%d?",
		GetVehicleName(model), GetVehicleCost(model)
	);
	return ShowPlayerDialog(playerid, airshop_DialogID, DIALOG_STYLE_MSGBOX,
		"Магазин воздушного транспорта",
		string,
		"Купить", "Выйти"
	);
}

stock airshop_IsShopVehicle(vehicleid)
{
	for (new i = 0; i < sizeof(airshop_Vehicles); i++) {
		if (airshop_Vehicles[i][vshop_ID] == vehicleid) {
			return 1;
		}
	}
	return 0;
}