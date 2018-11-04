/*

    Команды ркон админа 
	
*/

	CMD:updateshop(playerid, params[]) {
		vshop_ChangeVehicles();
		airshop_ChangeVehicles();
		bikeshop_ChangeVehicles();
		SendClientMessage(playerid, COLOUR_GREEN, "Транспорт обновлён!");
		return 1;	
	}