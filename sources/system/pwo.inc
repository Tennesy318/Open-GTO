forward MissleFly();
forward MissleLaunch();
 
new LaunchAt = 1;

stock pwo_OnGameModeInit()
{
        SetTimer("MissleFly", 100, true);
       
        SetTimer("MissleLaunch", 1000, true);
       
        CreateMissleLauncher(355.116821, 2029.626587, 25.391882);
        CreateMissleLauncher(188.230200, 2081.575400, 26.170501);
        CreateMissleLauncher(238.203912, 1698.624023, 23.875014);
        CreateMissleLauncher(15.7451134, 1720.978434, 23.875022); 
        return 1;
}
 
new Float: MisslePositions[999][4];
 
new TargetPos[999][4];
 
new Missle[999];
new MissleChase[999];
 
new MAX_MISSLES;
 
 
stock CreateMissleLauncher(Float: X, Float: Y, Float: Z)
{
    MisslePositions[MAX_MISSLES][0] = X;
    MisslePositions[MAX_MISSLES][1] = Y;
    MisslePositions[MAX_MISSLES][2] = Z;  
    new missleid = MAX_MISSLES;
	MAX_MISSLES = MAX_MISSLES += 1;
	return missleid;
}
 
 
stock Float: GetDistanceBetweenTwoPoints(Float: X, Float: Y, Float: Z, Float: X2, Float: Y2, Float: Z2)
{
    return floatsqroot(floatpower(floatabs(floatsub(X, X2)), 2) + floatpower(floatabs(floatsub(Y, Y2)), 2) + floatpower(floatabs(floatsub(Z, Z2)), 2));
}
 
 
Float: GetXYInFrontOfPlayer(playerid, &Float: X, &Float: Y, Float: distance)
{
        new Float: Z;
       
        GetPlayerPos(playerid, X, Y, Z);
       
        if(IsPlayerInAnyVehicle(playerid))
        {
            GetVehicleZAngle(GetPlayerVehicleID(playerid), Z);
        }
        else
        {
            GetPlayerFacingAngle(playerid, Z);
        }
       
        X +=(distance * floatsin(- Z, degrees));
        Y +=(distance * floatcos(- Z, degrees));
 
        return Z;
}
 
 
stock GetDistanceToPoint(playerid, Float: X ,Float: Y, Float: Z)
{
        new Float: X2, Float: Y2, Float: Z2;
 
        GetPlayerPos(playerid, X2, Y2, Z2);
       
        return floatround(GetDistanceBetweenTwoPoints(X, Y, Z, X2, Y2, Z2));
}
 
 
public MissleFly()
{
	for(new missleid = 0; missleid < MAX_MISSLES; missleid ++)
	{
		if(IsValidObject(Missle[missleid]))
		{
			new Float: X, Float: Y, Float: Z;
			GetPlayerPos(MissleChase[missleid], X, Y, Z);
			GetXYInFrontOfPlayer(MissleChase[missleid], X, Y, 5);
			TargetPos[missleid][0] = floatround(X);
			TargetPos[missleid][1] = floatround(Y);
			TargetPos[missleid][2] = floatround(Z + 3);
			MoveObject(Missle[missleid], X, Y, Z, 90);
			GetObjectPos(Missle[missleid], X, Y, Z);
			new Float: health;
			GetPlayerHealth(MissleChase[missleid], health);
			if(GetDistanceBetweenTwoPoints(X, Y, Z, TargetPos[missleid][0], TargetPos[missleid][1], TargetPos[missleid][2]) < 6 || health < 1)
			{
				DestroyMissle(Missle[missleid]);
			}
		}
	}
}
 
 
stock DestroyMissle(missleid)
{
    new Float: X, Float: Y, Float: Z;
    GetObjectPos(missleid, X, Y, Z);
    DestroyObject(missleid);
    CreateExplosion(X, Y, Z, 6, 10);
}
 
 
public MissleLaunch()
{
	for(new playerid = 0; playerid < MAX_PLAYERS; playerid ++)
	{
		new totallaunched;
		for(new missleid = 0; missleid < MAX_MISSLES; missleid ++)
		{
			if(GetDistanceToPoint(playerid, MisslePositions[missleid][0], MisslePositions[missleid][1], MisslePositions[missleid][2]) < 300)
			{
				if(IsPlayerInAnyVehicle(playerid) && IsAircraft(GetPlayerVehicleID(playerid)))
				{
					if(GetPlayerVIP(playerid))
					{
						if(LaunchAt == 1)
						{
							totallaunched = 1;
						}
					}
					if(!IsValidObject(Missle[missleid]) && totallaunched == 0)
					{
						new Float: X, Float: Y, Float: Z;
						GetPlayerPos(playerid, X, Y, Z);
						TargetPos[missleid][0] = floatround(X);
						TargetPos[missleid][1] = floatround(Y);
						TargetPos[missleid][2] = floatround(Z);
						MissleChase[missleid] = playerid;
						totallaunched = totallaunched = 1;
						Missle[missleid] = CreateObject(354, MisslePositions[missleid][0], MisslePositions[missleid][1], MisslePositions[missleid][2], 0, 0, 0);
						MoveObject(Missle[missleid], X, Y, Z, 15);
					}
				}
			}
		}
	}
}
 
 
stock IsAircraft(vehicleid)
{
	switch(GetVehicleModel(vehicleid))
	{
		case 465,425,417,497,563,592, 548,577,511,512,501,447, 460,513,520,469,487,488, 553,464,476,519,593,539:
		{
			return 1;
		}
	}
	return 0;
}