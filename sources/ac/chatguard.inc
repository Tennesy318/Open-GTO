new ChatGuardEnabled = CHAT_GUARD_ENABLED;

#define SPACE_CHARS ' ', '\t', '\r', '\n'

stock trimSideSpaces ( string[] )
{
    new c, len = strlen(string);

    for ( ; c < len; c++ ) // вырежем пробелы в начале
    {
        switch ( string[c] )
        {
            case SPACE_CHARS : continue;
            default:
            {
                if ( c != 0 ) strmid( string, string, c, len, len );
                break;
            }
        }
    }

    for ( c = len - c - 1; c >= 0; c-- ) // вырежем пробелы в конце
    {
        switch ( string[c] )
        {
            case SPACE_CHARS : continue;
            default:
            {
                string[c + 1] = 0;
                break;
            }
        }
    }
}

#define cells *4

stock spaceGroupsToSpaces ( string[] )
{
    new len = strlen(string), c = len - 1, spaces;

    for ( ; c >= 0; c-- )
    {
        switch ( string[c] )
        {
            case SPACE_CHARS : spaces++;
            default :
            {
                if ( spaces > 1 )
                {
                    memcpy( string, string[c + spaces + 1], (c + 2) cells, (len - c - spaces - 1) cells, len );
                    len -= spaces - 1;
                }

                if ( spaces > 0 )
                {
                    string[c + 1] = ' ';
                    spaces        =  0;
                }
            }
        }
    }

    if ( spaces > 1 )
    {
        memcpy( string, string[c + spaces + 1], (c + 2) cells, (len - c - spaces - 1) cells, len );
        len -= spaces - 1;
    }
    if ( spaces > 0 ) string[c + 1] = ' ';

    string[len] = 0;
}

#undef SPACE_CHARS

stock containsAnyIP ( string[] )
{
    new digits, digitGroups;

    for ( new pos; ; pos++ )
    {
        switch ( string[pos] )
        {
            case 0 : break;
            case '0'..'9', 'o', 'O', 'о', 'О', 'З', 'з' : digits++;
            default :
            {
                if ( digits >= 2 )
                {
                    digitGroups++;
                    digits = 0;
                }
            }
        }
    }

    if ( digits >= 2 ) digitGroups++;
    if ( digitGroups >= 4 ) return 1;

    return 0;
}

stock forbiddenDomain[][] =
{
    ".net", ".nеt",
    ".com", ".сom", ".соm", ".cоm",
    ".ru", ".ру",
    ".kz", ".кz", ".kз", ".кз",
    ".info", ".infо"
};

/*
    Вернет 1, если строка содержит любой домен из списка выше.
------------
    Иначе, вернет 0.
*/

stock containsDomainName ( string[] )
{
    new strLen = strlen(string);

    for ( new d = sizeof(forbiddenDomain) - 1, foundPos, domainLen; d >= 0; d-- )
    {
        foundPos  = -1;
        domainLen = strlen(forbiddenDomain[d]);

        for ( ; ( foundPos = strfind( string, forbiddenDomain[d], true, foundPos + 1 ) ) >= 0;  )
        {
            if ( foundPos + domainLen >= strLen ) return 1;

            switch ( string[ foundPos + domainLen ] )
            {
                case 0..64, 91..96, 123..191 : return 1;
            }
        }
    }

    return 0;
}

stock forbiddenName [ MAX_PLAYERS char ];

/*
    Вернет 1, если ник игрока содержит доменное имя или любой реальный IP.
-------------
    Иначе вернет 0.
*/

stock playerHasForbiddenName ( playerid )
{
    if ( forbiddenName{playerid} == 0 )
    {
        new name[MAX_PLAYER_NAME+1];
        GetPlayerName( playerid, name, MAX_PLAYER_NAME );

        if ( containsAnyIP(name) || containsDomainName(name) )
        {
            forbiddenName{playerid} = 1;
            return 1;
        }

        forbiddenName{playerid} = -1;
        return 0;
    }
    else
    {
        if ( forbiddenName{playerid} == 1 ) return 1;
        else return 0;
    }
}

#define INCORRECT_CMD_CHARS '.', '?'

stock incorrectCmdAttempt ( string[] )
{
    switch ( string[0] )
    {
        case INCORRECT_CMD_CHARS :
        {
            switch ( string[1] )
            {
                case 65..90, 97..122, 192..255 : return 1;
            }
        }
    }

    return 0;
}

#undef INCORRECT_CMD_CHARS

#define CHAT_STR_SIZE           128 // макс кол-во символов в сообщении чата
#define CHAT_HISTORY_SIZE       20 // кол-во сохраненных сообщений чата
#define MAX_MESSAGES_PER_TIME   3 // максимум сообщений за, указанную ниже, единицу времени
#define MAX_MESSAGES_TIME       3000 // мс. За указанное время должно быть не более MAX_FAST_MESSAGES сообщений игрока

enum chatMsInfo // инфо о каждом сообщении чата
{
    chTick,
    chPosterID,
    chText [ CHAT_STR_SIZE ]
}

// массив, где хранятся посл CHAT_HISTORY_SIZE сообщений чата
stock ms [ CHAT_HISTORY_SIZE ] [ chatMsInfo ];

/*
    Строка source[] будет разделена на несколько подстрок
    с помощью символа delimiter. Нужная подстрока под номером (индексом)
    substrIndex будет помещена в строку dest[]
--------------
    Ничего не возвращает.
*/

stock sparam
(
    dest[],             maxSize     = sizeof(dest),
    const source[],     delimiter   = ' ',
    substrIndex = 0,    withRest    = 0
)
{
    dest[0] = 0; // очистим строку назначения

    for ( new cur, pre, i = -1; ; cur++ ) // пробежимся по каждому символу в строке source
    {
        if ( source[cur] == 0 ) // если текущий символ в source - это символ конца строки
        {
            if ( ++i == substrIndex ) // если индекс текущей подстроки и есть sourceIndex
                // скопируем в dest нужную подстроку из source
                strmid( dest, source, pre, ( withRest ? strlen(source) : cur ), maxSize );

            goto sparam_end;
        }

        if ( source[cur] == delimiter ) // если текущий символ в source - это символ для разделения строки
        {
            if ( ++i == substrIndex ) // если индекс текущей подстроки и есть sourceIndex
            {
                // скопируем в dest нужную подстроку из source
                strmid( dest, source, pre, ( withRest ? strlen(source) : cur ), maxSize );
                goto sparam_end;
            }

            pre = cur + 1;
        }
    }

    sparam_end:
    return; // завершим работу функции
}

/*
    Обновит историю сообщений чата
----------
    Ничего не вернет.
*/

stock updateMsHistory ( playerid, msTick, text[] )
{
    // сдвиг всей истории на 1 слот вперед
    for ( new i = 1; i < CHAT_HISTORY_SIZE; i++ )
        memcpy( ms[i], ms[i - 1], 0, sizeof(ms[]) cells );

    // добавим текст и автора в историю сообщений чата
    ms[0][chTick]     = msTick;
    ms[0][chPosterID] = playerid;
    strmid( ms[0][chText], text, 0, strlen(text), CHAT_STR_SIZE );
}

/*
    Вернет 1, если игрок слишком быстро набирает сообщения подряд.
-------------
    Иначе вернет 0.
*/

stock tooManyMessagesForShortTime ( playerid, lastMsTick )
{
    // найдем самое первое сообщение игрока в истории чата из его всех быстрых сообщений
    new m, messages;

    for ( ; m < CHAT_HISTORY_SIZE; m++ )
        if ( ms[m][chPosterID] == playerid && ++messages > MAX_MESSAGES_PER_TIME ) break;

    if ( m >= CHAT_HISTORY_SIZE ) m--;
    if ( messages > MAX_MESSAGES_PER_TIME && lastMsTick - ms[m][chTick] < MAX_MESSAGES_TIME ) return 1;

    return 0;
}

#undef cells
#undef CHAT_STR_SIZE
#undef MAX_MESSAGES_PER_TIME
#undef MAX_MESSAGES_TIME











/*
    Вернет 1, если в строке слишком много букв в верхнем регистре.
-----------
    Иначе вернет 0.
*/

#define MAX_UPPERCASES    40 // допустимый % букв в верхнем регистре

stock tooManyUpperChars ( string[] )
{
    new len = strlen(string), c = len - 1, upperChars;

    for ( ; c >= 0; c-- )
    {
        switch ( string[c] )
        {
            case 'A'..'Z', 'А'..'Я' : upperChars++;
        }
    }

    if ( float(upperChars) / float(len) * 100.0 > MAX_UPPERCASES.0 ) return 1;

    return 0;
}

#undef MAX_UPPERCASES















stock ChatGuardLoadConfig()
{
	if (!ini_Exist(ConfigDB)) return;
	new file_chg = ini_Open(ConfigDB);
	ini_GetInt(file_chg,"Chat_Guard_Enabled",ChatGuardEnabled);
	ini_Close(file_chg);
}

stock ChatGuardSaveConfig()
{
	new file_chg = (!ini_Exist(ConfigDB)) ? ini_Create(ConfigDB) : ini_Open(ConfigDB);
	ini_SetInt(file_chg,"Chat_Guard_Enabled",ChatGuardEnabled);
	ini_Close(file_chg);
	return 1;
}


stock chatguard_OnGameModeInit()
{
	ChatGuardLoadConfig();
	if (ChatGuardEnabled != 1) return;
    for ( new i; i < CHAT_HISTORY_SIZE; i++ ) ms[i][chPosterID] = -1;
	GameMSG("SERVER: (protections)ChatGuard(by MX_Master) module init");
}

#undef CHAT_HISTORY_SIZE

stock chatguard_OnPlayerConnect ( playerid )
{
	if (ChatGuardEnabled != 1) return 0;
    forbiddenName{playerid} = 0;
    return 1;
}

stock chatguard_OnPlayerDisconnect ( playerid, reason )
{
	#pragma unused reason
	if (ChatGuardEnabled != 1) return 0;
    forbiddenName{playerid} = 0;
    return 1;
}






stock chatguard_OnPlayerText ( playerid, text[] )
{
	if (ChatGuardEnabled != 1 || IsPlayerAdm(playerid)) return 1;
    new msgTick = GetTickCount();


    // проверка ника игрока на содержание любого IP/домена
    if ( playerHasForbiddenName(playerid) )
    {
        SendClientMessage( playerid, WARN_MS_COLOR, lang_texts[11][8] );
        return 0;
    }

    // сообщения чата, похожие на попытку ввода команды чата - отображаться не будут
    if ( incorrectCmdAttempt(text) )
    {
        SendClientMessage( playerid, WARN_MS_COLOR, lang_texts[11][9] );
        return 0;
    }



    // замена любых групп пробельных символов на единичные пробелы
    spaceGroupsToSpaces(text);

    // обрезка пробельных символов по краям
    trimSideSpaces(text);

    // пустые сообщения отображаться не будут
    if ( text[0] == 0 ) return 0;

    // нельзя писать соообщения, содержащие много букв в верхнем регистре
    if ( tooManyUpperChars(text) )
    {
        SendClientMessage( playerid, WARN_MS_COLOR, lang_texts[11][10] );
        return 0;
    }

    // нельзя писать сообщения, содержащие IP адреса
    if ( containsAnyIP(text) )
    {
        SendClientMessage( playerid, WARN_MS_COLOR, lang_texts[11][11] );
        return 0;
    }

    // нельзя писать сообщения, содержащие запрещенные доменные имена
    if ( containsDomainName(text) )
    {
        SendClientMessage( playerid, WARN_MS_COLOR, lang_texts[11][12] );
        return 0;
    }



    // нельзя быстро написать неск сообщений подряд
    if ( tooManyMessagesForShortTime( playerid, msgTick ) )
    {
        SendClientMessage( playerid, WARN_MS_COLOR, lang_texts[11][13] );
        return 0;
    }

    // обновление истории сообщений чата
    updateMsHistory( playerid, msgTick, text );



    // покажем сообщение в чате
    return 1;
}

#undef WARN_MS_COLOR
