//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdlib.h>
#include "globdefs.h"
#include "utils.h"
#include "proto.h"
#include "main.h"
#include "ModemRequestThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ModemRequestThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
#define   DELAY_BTWN_CMD		50

__fastcall ModemRequestThread::ModemRequestThread(bool CreateSuspended)
:TThread(CreateSuspended)
{
}

//---------------------------------------------------------------------------
// Все команды подряд опрашиваем
void __fastcall ModemRequestThread::Execute()
{
   MODEM_STRUCT ms;
  do {
        Sleep(DELAY_BTWN_CMD);
        GetModemNumber(&ms);
        Sleep(DELAY_BTWN_CMD);
        GetModemTime(&ms);
        Sleep(DELAY_BTWN_CMD);
        GetAlarmTime(&ms);
        Sleep(DELAY_BTWN_CMD);
        GetCalTime(&ms);
        Sleep(DELAY_BTWN_CMD);
        GetTimeForRelease(&ms);
        Sleep(DELAY_BTWN_CMD);
        GetBurnLen(&ms);
     }  while(0);
      frmMain->SetModemButtons(true);     
}

//---------------------------------------------------------------------------
