new tank, Text3D:tank_text, minigun;

stock ml_OnGameModeInit()
{
	tank = CreateVehicle(432,-2121.9365,-116.6598,35.3276,180.0,43,300, 60);
	tank_text = Create3DTextLabel( "SUPER TANK(NET)\n61 LEVEL", 0xFF0000AA, 7.77, 7.77, 7.77, 100.0, 0, 1 );
	SetVehicleHealth(tank, 15000);
	minigun = CreateObject( 2985, 0, 0, 0, 0, 0, 0 ); 
    AttachObjectToVehicle(minigun, tank, 0.74, 3.37, -0.25, 0.00, 0.00, 89.47 ); 
	Attach3DTextLabelToVehicle( tank_text, tank, 0.0, 0.0, 1.0 );
	SetVehicleFuel(tank, -1);
	return 1;
}

stock ml_OnPlayerStateChange(playerid)
{
    if(GetPlayerVehicleID(playerid == tank))
    {
		if(GetPlayerScore(playerid) == MAX_LEVEL)
		{
			return 1;
		}
		if(GetPlayerVIP(playerid))
		{
			return 1;
		}
		else
		{
			RemovePlayerFromVehicle(playerid);
			new string[128];
			format(string, sizeof(string), "Этот танк доступен только на %d уровне", MAX_LEVEL);
			SendClientMessage(playerid, COLOUR_RED, string);
		}
	}
	return 1;
}