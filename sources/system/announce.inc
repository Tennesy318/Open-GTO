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
   switch(random(9))
   {
      case 0: {
      SendClientMessageToAll(0x87CEEBAA,"Информация: {FFFFFF}Незнания правил не освобождает вас от ответственности!");
	  }
      case 1: {
      SendClientMessageToAll(0x87CEEBAA,"Информация: {FFFFFF}Много разных функций вы можете посмотреть, нажав на 'ALT'!");
	  }
      case 2: {
      SendClientMessageToAll(0x87CEEBAA,"Информация: {FFFFFF}По любым вопросом обращайтесь к административному составу сервера.");
	  }
      case 3: {
      SendClientMessageToAll(0x87CEEBAA,"Информация: {FFFFFF}Увидели читера? Пишите {359EFD}@ [Текст] {FFFFFF}или {359EFD}# [Текст]{FFFFFF}!");
	  }
      case 4: {
      SendClientMessageToAll(0x87CEEBAA,"Информация: {FFFFFF}Бан за использование читов идёт от 2-ух лет!");
	  }
	  case 5: {
      SendClientMessageToAll(0x87CEEBAA,"Информация: {FFFFFF}Если вы заметили,как игрок нарушает правила,зафиксируйте{359EFD}(F8) {FFFFFF}и напишите жалобу на форум.{359EFD}NorWiFi.ru");
	  }
	  case 6: {
      SendClientMessageToAll(0x87CEEBAA,"Информация: {FFFFFF}У вас появилась идея по разработке мода? Напишите её на форуме,а также комментируйте другие предложения.{359EFD}NorWiFi.ru");
	  }
	  case 7: {
      SendClientMessageToAll(0x87CEEBAA,"Информация: {FFFFFF}Вас интересует какая точка самая прибыльная,нажмите на ALT и выберите 'Информация о точках кача'{359EFD}ALT");
	  }
	  case 8: {
      SendClientMessageToAll(0x87CEEBAA,"Информация: {FFFFFF}Хотите узнать расположение точек кача? В меню транспорта есть GPS");
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