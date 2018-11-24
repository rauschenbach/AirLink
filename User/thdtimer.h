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

//�������� ������
class TThreadedTimer : public TComponent
{
 friend TTimerThread; //������������� �����
private:
     //����� ������ � ������ ������

     bool               FEnabled;
     WORD               FInterval;
     TNotifyEvent       FOnTimer;
     TTimerThread      *FTimerThread;
     TThreadPriority    FPriority;
     void   __fastcall  SetEnabled(const bool Value);
     void   __fastcall  SetInterval(const WORD Value);
     void   __fastcall  SetOnTimer(const TNotifyEvent Value);
     void   __fastcall  SetPriority(const TThreadPriority Value);
     //����������� ������ ������ �������
     void   __fastcall UpdateTimer();
     void   __fastcall Timer();

public:
     //����������� � ����������
     virtual __fastcall  TThreadedTimer(TComponent* Owner);
     virtual __fastcall ~TThreadedTimer();
__published:
     //�������� � �������
   __property  bool Enabled=
       {read=FEnabled, write=SetEnabled,default=true};

   __property  WORD Interval=
       {read=FInterval, write=SetInterval,default=1000};

   __property  TThreadPriority Priority=
       {read=FPriority, write=SetPriority,default=3};

   __property  TNotifyEvent OnTimer=
       {read=FOnTimer, write=SetOnTimer,default=NULL};
};

//��������� �����
class TTimerThread:public TThread
{
 public:
  TThreadedTimer *OwnerTimer;
  //����������� � ����������
  virtual __fastcall  TTimerThread(bool CreateSuspensed):
    TThread(CreateSuspensed){};
  virtual __fastcall ~TTimerThread(){};
  //���������, ������� ����������� � ������
  virtual void __fastcall Execute();
};
//---------------------------------------------------------------------------
#endif
