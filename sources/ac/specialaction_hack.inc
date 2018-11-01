/*

    Speedhack hack

*/

#define SetPlayerSpecialAction PSpecAct_SetPlayerSpecialAction
#define GetPlayerSpecialAction PSpecAct_GetPlayerSpecialAction
static
	gPlayerSpecialAction[MAX_PLAYERS char];
	
forward SpecialAction(playerid);
public SpecialAction(playerid)
{
	static
		current_action;

	current_action = GetPlayerSpecialAction(playerid);

	if (current_action == SPECIAL_ACTION_DUCK ||
		current_action == SPECIAL_ACTION_ENTER_VEHICLE ||
		current_action == SPECIAL_ACTION_EXIT_VEHICLE) 
	{
		return 0;
	}

	if (current_action != gPlayerSpecialAction[playerid])	
	{
		if (current_action == SPECIAL_ACTION_NONE) {
			gPlayerSpecialAction[playerid] = SPECIAL_ACTION_NONE;
		} else {
			SetPlayerSpecialAction(playerid, gPlayerSpecialAction[playerid]);

			new string[128];
			format(string, sizeof(string), "SpecialAction");
			KickPlayer(playerid, string);
			return 1;
		}
	}
	return 0;
}

stock PSpecAct_SetPlayerSpecialAction(playerid, actionid)
{
	gPlayerSpecialAction[playerid] = actionid;
	return SetPlayerSpecialAction(playerid, actionid);
}

stock PSpecAct_GetPlayerSpecialAction(playerid)
{
	return GetPlayerSpecialAction(playerid);
}