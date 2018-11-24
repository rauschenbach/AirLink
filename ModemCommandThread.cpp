//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "globdefs.h"
#include "utils.h"
#include "proto.h"
#include "main.h"
#include "ModemCommandThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ModemCommandThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
#define   DELAY_BTWN_CMD		50

__fastcall ModemCommandThread::ModemCommandThread(void* p, bool CreateSuspended)
        : TThread(CreateSuspended)
{
     parameter = p;
}
//---------------------------------------------------------------------------
// Передаем все команды подряд в модем
void __fastcall ModemCommandThread::Execute()
{
   char *str = "$RSAPR,,*162f\r\n";
   MODEM_STRUCT *ms = (MODEM_STRUCT*)parameter;
  do {
    Sleep(DELAY_BTWN_CMD);
    SetModemNumber(ms);
        Sleep(DELAY_BTWN_CMD);
    SetModemTime(ms);
        Sleep(DELAY_BTWN_CMD);
    SetAlarmTime(ms);
        Sleep(DELAY_BTWN_CMD);
    SetCalTime(ms);
        Sleep(DELAY_BTWN_CMD);
    SetTimeForRelease(ms);
        Sleep(DELAY_BTWN_CMD);
    SetBurnLen(ms);
        Sleep(DELAY_BTWN_CMD);
    SendAnyCommand(str);
   }  while(0);
      frmMain->SetModemButtons(true);
}
//---------------------------------------------------------------------------

 