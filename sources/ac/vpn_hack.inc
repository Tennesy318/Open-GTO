/*

    Weapon hack

*/

#include <a_http>

stock vpn_OnPlayerConnect(playerid)
{
	new ip[16], string[59];
	GetPlayerIp(playerid, ip, sizeof ip);
	format(string, sizeof string, "www.shroomery.org/ythan/proxycheck.php?ip=%s", ip);
	HTTP(playerid, HTTP_GET, string, "", "MyHttpResponse");
    return 1;
}

forward MyHttpResponse(playerid, response_code, data[]);
public MyHttpResponse(playerid, response_code, data[])
{
	new name[MAX_PLAYERS],string[256];
	new ip[16];
	GetPlayerName(playerid, name, sizeof(name));
	GetPlayerIp(playerid, ip, sizeof ip);
	if(strcmp(ip, "127.0.0.1", true) == 0)
	{
        return 1;
	}
	if(response_code == 200)
	{	
		if(data[0] == 'Y')
		{
	    	SendClientMessage(playerid, 0xFF0000FF, "Вы кикнуты. Выключите VPN.");
			format(string, sizeof(string), "Использование VPN");
			KickPlayer(playerid, string);
		}
		if(data[0] == 'N')
		{
			return 1;
		}
		if(data[0] == 'X')
		{
			printf("Не верный формат IP адреса");
		}
		else
		{
			printf("Ошибка запроса! Код ответа: %d", response_code);
		}
	}
	return 1;
}