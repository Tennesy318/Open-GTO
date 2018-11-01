/*

    Weapon hack

*/

stock wh_OnPlayerUpdate(playerid)
{
    if(IsPlayerAdmin(playerid)) return 0;
    if(GetPlayerWeapon(playerid) == WEAPON_MINIGUN)
    {
        new string[128];
        format(string, sizeof(string), "Weapon cheat");
        KickPlayer(playerid, string);
    }
    return 1;
}