/*

    Speedhack hack

*/

stock speedhack_OnPlayerUpdate(playerid)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        if(!IsPlayerAdmin(playerid))
        {
            static SPEEDPLAYER[MAX_PLAYERS];
            if(GetPlayerSpeed(playerid) - SPEEDPLAYER[playerid] > VehicleInfo[vehicle_speed])
            {
                new string[128];
                format(string, sizeof(string), "Speedhack");
                KickPlayer(playerid, string);
                return true;
            }
            SPEEDPLAYER[playerid] = GetPlayerSpeed(playerid);
        }
    }  
    return 1;
}  