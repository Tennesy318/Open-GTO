/*

    Команды игрока

*/

CMD:duel(playerid, params[])
{
    new target,string[13];
    if(sscanf(params, "d",target)) return SendClientMessage(playerid, COLOUR_GREY, "Введите: /duel [id]");
    if(InDuel[duel1] == 1) return SendClientMessage(playerid, -1, "{ff0000}[Ошибка]:{ffffff}Игрок уже на дуэли");
    if(InDuel[duel1] == 2) return SendClientMessage(playerid, -1, "{ff0000}[Ошибка]: {ffffff}Игрок уже на дуэли");
    duel2 = target;
    duel1 = playerid;
    Duel_money[playerid] = 100;
    format(string,sizeof(string),"bet:~n~%d$",Duel_money[playerid]);
    TextDrawSetString(DUEL_TD[13],string);
    for(new i; i<29; i++) TextDrawShowForPlayer(target,DUEL_TD[i]);
    SelectTextDraw(target,0xAFAFAFAA);
    return true;
}