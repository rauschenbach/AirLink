//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ThdTimer.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TThreadedTimer *)
{
        new TThreadedTimer(NULL);
}
//-�����������----------------------------------------------------------------
__fastcall TThreadedTimer::TThreadedTimer(TComponent* TheOwner)
        : TComponent(TheOwner),
        FEnabled(true),
        FInterval(1000),
        FOnTimer(NULL),
        FPriority(tpNormal)
{
   FTimerThread=new TTimerThread(false);
   FTimerThread->OwnerTimer=this;
}
//����������----------------------------------------------------------------
__fastcall TThreadedTimer::~TThreadedTimer()
{
     FEnabled=false;
     UpdateTimer();
     delete FTimerThread;
}                      
//---------------------------------------------------------------------------
void __fastcall TThreadedTimer::Timer()
{
   if(FOnTimer) FOnTimer(this);
}
//---------------------------------------------------------------------------
void __fastcall TThreadedTimer::UpdateTimer()
{
 //��������� ���������� ������
 if(!FTimerThread->Suspended) FTimerThread->Suspend();
  if(FInterval && FEnabled && FOnTimer)
   if(FTimerThread->Suspended) FTimerThread->Resume();
}
//---------------------------------------------------------------------------
void __fastcall TThreadedTimer::SetEnabled(const bool Value)
{//����� Enabled
 if(Value !=FEnabled)
  {
   FEnabled=Value;
   UpdateTimer();
  }
}
//---------------------------------------------------------------------------
void __fastcall TThreadedTimer::SetInterval(const WORD Value)
{//����� Interval
 if(Value !=FInterval)
  {
   FInterval=Value;
   UpdateTimer();
  }
}
//---------------------------------------------------------------------------
void __fastcall TThreadedTimer::SetOnTimer(const TNotifyEvent Value)
{//����� OnTimer
 FOnTimer=Value;
 UpdateTimer();
}
//---------------------------------------------------------------------------
void __fastcall TThreadedTimer::SetPriority(const TThreadPriority Value)
{//����� Priority
   if(Value !=FPriority)
   {
    FPriority=Value;
    UpdateTimer();
   }
}
//---------------------------------------------------------------------------
void __fastcall TTimerThread::Execute()
{//����� ������� ������
 Priority=OwnerTimer->Priority;
 do
  {
   SleepEx(OwnerTimer->Interval,false);
   Synchronize(OwnerTimer->Timer);
  }while (!Terminated);
}
//---------------------------------------------------------------------------
namespace Thdtimer
{
        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[1] = {__classid(TThreadedTimer)};
                 RegisterComponents("User", classes, 0);
        }
}
//---------------------------------------------------------------------------
