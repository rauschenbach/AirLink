//---------------------------------------------------------------------------
#ifndef ThdTimerH
#define ThdTimerH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class PACKAGE TTimerThread;

//Поточный таймер
class TThreadedTimer : public TComponent
{
 friend TTimerThread; //Дружественный класс
private:
     //Члены данных и методы записи

     bool               FEnabled;
     WORD               FInterval;
     TNotifyEvent       FOnTimer;
     TTimerThread      *FTimerThread;
     TThreadPriority    FPriority;
     void   __fastcall  SetEnabled(const bool Value);
     void   __fastcall  SetInterval(const WORD Value);
     void   __fastcall  SetOnTimer(const TNotifyEvent Value);
     void   __fastcall  SetPriority(const TThreadPriority Value);
     //Специальные методы класса таймера
     void   __fastcall UpdateTimer();
     void   __fastcall Timer();

public:
     //Конструктор и деструктор
     virtual __fastcall  TThreadedTimer(TComponent* Owner);
     virtual __fastcall ~TThreadedTimer();
__published:
     //Свойства и события
   __property  bool Enabled=
       {read=FEnabled, write=SetEnabled,default=true};

   __property  WORD Interval=
       {read=FInterval, write=SetInterval,default=1000};

   __property  TThreadPriority Priority=
       {read=FPriority, write=SetPriority,default=3};

   __property  TNotifyEvent OnTimer=
       {read=FOnTimer, write=SetOnTimer,default=NULL};
};

//Таймерный поток
class TTimerThread:public TThread
{
 public:
  TThreadedTimer *OwnerTimer;
  //Конструктор и деструктор
  virtual __fastcall  TTimerThread(bool CreateSuspensed):
    TThread(CreateSuspensed){};
  virtual __fastcall ~TTimerThread(){};
  //Процедура, которая выполняется в потоке
  virtual void __fastcall Execute();
};
//---------------------------------------------------------------------------
#endif
