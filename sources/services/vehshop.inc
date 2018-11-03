/*

	Описание: магазин транспорта
	Автор: ziggi

*/


#if defined _vehshop_included
	#endinput
#endif

#define _vehshop_included
#pragma library vehshop

stock vshop_OnGameModeInit()
{
	vshop_ChangeVehicles();
	return 1;
}

stock vshop_OnPlayerStateChange(playerid, newstate, oldstate)
{
	#pragma unused newstate, oldstate
	if (vshop_IsShopVehicle( GetPlayerVehicleID(playerid) )) {
		vshop_ShowBuyDialog(playerid);
	}
	return 1;
}

stock vshop_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem, inputtext
	if (dialogid == vshop_DialogID) {
		RemovePlayerFromVehicle(playerid);
		if (!response) {
			return 0;
		}
		if (GetPlayerVehicleCount(playerid) >= GetPlayerVehicleMaximumCount(playerid)) {
			show_Msg_Dialog(playerid, "Магазин автомобилей", "У вас максимальное количество транспорта", "ОК");
			return 0;
		}
		
		new vehicleid = GetPlayerVehicleID(playerid);
		new cost = GetVehicleCost( GetVehicleModel(vehicleid) );
		
		if (oGetPlayerMoney(playerid) < cost) {
			show_Msg_Dialog(playerid, "Магазин автомобилей", "У вас недостаточно денег", "ОК");
			return 0;
		}
		
		oGivePlayerMoney(playerid, -cost, 1);
		buyVehicle(playerid, vehicleid);
		
		show_Msg_Dialog(playerid, "Магазин автомобилей", "\
			Вы успешно купили этот автомобиль.\n\
			Чтобы вызвать купленный автомобиль, зайдите в меню пользователя и выберите его.",
			"ОК"
		);
		return 1;
	}
	return 1;
}

stock vshop_OnVehicleSpawn(vehicleid)
{
	if (vshop_IsShopVehicle(vehicleid)) {
		SetVehicleFuel(vehicleid, 0);
	}
	return 1;
}

stock vshop_SetVehiclesToRespawn()
{
	for (new i = 0; i < sizeof(vshop_Vehicles); i++) {
		new Float:dist = GetVehicleDistanceFromPoint(vshop_Vehicles[i][vshop_ID], vshop_Vehicles[i][vshop_X], vshop_Vehicles[i][vshop_Y], vshop_Vehicles[i][vshop_Z]);
		if (dist >= 4.0) {
			SetVehicleToRespawn(vshop_Vehicles[i][vshop_ID]);
		}
	}
}

stock vshop_ChangeVehicles()
{
	new string[MAX_STRING], model;
	for (new i = 0; i < sizeof(vshop_Vehicles); i++) {
		if (vshop_Vehicles[i][vshop_ID] != 0) {
			// если кто-то есть в транспорте
			foreach (new playerid : Player) {
				if (vshop_Vehicles[i][vshop_ID] == GetPlayerVehicleID(playerid)) {
					HideDialog(playerid);
					RemovePlayerFromVehicle(playerid);
				}
			}
			// удаляем транспорт
			DestroyVehicle(vshop_Vehicles[i][vshop_ID]);
			Delete3DTextLabel(vshop_Vehicles[i][vshop_Text3D]);
		}
		
		model = vshop_VehiclesModels[ random( sizeof(vshop_VehiclesModels) ) ];
		vshop_Vehicles[i][vshop_ID] = CreateVehicle(model,
			vshop_Vehicles[i][vshop_X], vshop_Vehicles[i][vshop_Y], vshop_Vehicles[i][vshop_Z], vshop_Vehicles[i][vshop_A],
			colors_Array[ random( sizeof(colors_Array) ) ][color_vehicle], colors_Array[ random( sizeof(colors_Array) ) ][color_vehicle], 0
		);
		SetVehicleFuel(vshop_Vehicles[i][vshop_ID], 0);
		
		format(string, sizeof(string), "{CCCCCC}%s\n{00AA00}Цена: {CCCCCC}$%d\n{999999}Сядьте для покупки", GetVehicleName(model), GetVehicleCost(model));
		vshop_Vehicles[i][vshop_Text3D] = Create3DTextLabel(string, COLOUR_WHITE, vshop_Vehicles[i][vshop_X], vshop_Vehicles[i][vshop_Y], vshop_Vehicles[i][vshop_Z], 20.0, 0, 1);
		Attach3DTextLabelToVehicle(vshop_Vehicles[i][vshop_Text3D], vshop_Vehicles[i][vshop_ID], 0.0, 0.0, 0.2);
	}
}

stock vshop_OneHourTimer()
{
	static hours;
	hours++;
	
	if (hours >= VEHSHOP_CAR_CHANGE_TIME) {
		hours = 0;
		vshop_ChangeVehicles();
	}
}

stock buyVehicle(playerid, vehicleid)
{
	new model = GetVehicleModel(vehicleid);
	AddPlayerVehicle(playerid, model, colors_Array[ random( sizeof(colors_Array) ) ][color_vehicle], colors_Array[ random( sizeof(colors_Array) ) ][color_vehicle], float(GetMaxVehicleFuel(model)));
	return 1;
}

stock vshop_ShowBuyDialog(playerid)
{
	new model = GetVehicleModel(GetPlayerVehicleID(playerid));
	new string[MAX_STRING];
	format(string, sizeof(string),
		"Вы хотите купить автомобиль '%s' за $%d?",
		GetVehicleName(model), GetVehicleCost(model)
	);
	return ShowPlayerDialog(playerid, vshop_DialogID, DIALOG_STYLE_MSGBOX,
		"Магазин автомобилей",
		string,
		"Купить", "Выйти"
	);
}

stock vshop_IsShopVehicle(vehicleid)
{
	for (new i = 0; i < sizeof(vshop_Vehicles); i++) {
		if (vshop_Vehicles[i][vshop_ID] == vehicleid) {
			return 1;
		}
	}
	return 0;
}
