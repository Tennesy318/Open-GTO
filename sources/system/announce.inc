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
      SendClientMessageToAll(0x87CEEBAA,"����������: {FFFFFF}�������� ������ �� ����������� ��� �� ���������������!");
	  }
      case 1: {
      SendClientMessageToAll(0x87CEEBAA,"����������: {FFFFFF}����� ������ ������� �� ������ ����������, ����� �� 'ALT'!");
	  }
      case 2: {
      SendClientMessageToAll(0x87CEEBAA,"����������: {FFFFFF}�� ����� �������� ����������� � ����������������� ������� �������.");
	  }
      case 3: {
      SendClientMessageToAll(0x87CEEBAA,"����������: {FFFFFF}������� ������? ������ {359EFD}@ [�����] {FFFFFF}��� {359EFD}# [�����]{FFFFFF}!");
	  }
      case 4: {
      SendClientMessageToAll(0x87CEEBAA,"����������: {FFFFFF}��� �� ������������� ����� ��� �� 2-�� ���!");
	  }
	  case 5: {
      SendClientMessageToAll(0x87CEEBAA,"����������: {FFFFFF}���� �� ��������,��� ����� �������� �������,������������{359EFD}(F8) {FFFFFF}� �������� ������ �� �����.{359EFD}NorWiFi.ru");
	  }
	  case 6: {
      SendClientMessageToAll(0x87CEEBAA,"����������: {FFFFFF}� ��� ��������� ���� �� ���������� ����? �������� � �� ������,� ����� ������������� ������ �����������.{359EFD}NorWiFi.ru");
	  }
	  case 7: {
      SendClientMessageToAll(0x87CEEBAA,"����������: {FFFFFF}��� ���������� ����� ����� ����� ����������,������� �� ALT � �������� '���������� � ������ ����'{359EFD}ALT");
	  }
	  case 8: {
      SendClientMessageToAll(0x87CEEBAA,"����������: {FFFFFF}������ ������ ������������ ����� ����? � ���� ���������� ���� GPS");
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