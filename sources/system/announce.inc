//
// Created:		Unknown
// Aurthor:		WaRTiX1337
//

#if defined _announce_included
  #endinput
#endif

#define _announce_included
#pragma library announce

stock commercials()
{
   switch(random(0))
   {
      case 0: {
      SendClientMessageToAll(0x00CC00AA,"Open-GTO: {FFFFFF}Незнания правил не освобождает вас от ответственности!");
	  }
   }
}

stock split(const strsrc[], strdest[][], delimiter)
{
    new i, li;
    new aNum;
    new len;
    while(i <= strlen(strsrc))
    {
        if(strsrc[i] == delimiter || i == strlen(strsrc))
        {
            len = strmid(strdest[aNum], strsrc, li, i, 128);
            strdest[aNum][len] = 0;
            li = i+1;
            aNum++;
        }
        i++;
    }
    return 1;
}