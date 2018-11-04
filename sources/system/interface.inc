/*

    interface check

*/

stock interface_check(playerid)
{
    new inter = GetPlayerInterface(playerid);
    if (inter == INTERFACE_ON)
    {
        TextDrawShowForPlayer(playerid,level_TextDraw_Level[playerid]);
        TextDrawShowForPlayer(playerid, weapon_TextDraw_Level[playerid]);
        TextDrawShowForPlayer(playerid,level_TextDraw_XP[playerid]);
        UpdatePlayerWeaponTextDraws(playerid);
    }
    else if (inter == INTERFACE_OFF)
    {
        wskill_HideTextDraw(playerid);
        level_HideTextDraws(playerid);
    }
    return 1;
}