/*

    fakekill hack

*/

stock fk_OnPlayerDeath(playerid, killerid, reason)
{
	if(reason != 255 && reason != WEAPON_COLLISION || killerid != INVALID_PLAYER_ID)
	{
		new string[128];
        format(string, sizeof(string), "FakeKill");
        KickPlayer(playerid, string);
	}
}