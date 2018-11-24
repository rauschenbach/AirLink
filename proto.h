#ifndef ProtoH
#define ProtoH
//---------------------------------------------------------------------------

#include <windows.h>
#include "ComPort.h"
#include "globdefs.h"
#include "my_cmd.h"

bool PortInit(int, u32);
bool PortClose(void);

int  TimeSync(long*);
int  InitTest(void*);
int  ResetDSP(void*);
int  PowerOff(void*);
int  ModemOn(void*);
int  ClearBuf(void *);
int  ModemShiftTime(void *);
int  GpsOn(void *);
int  GpsOff(void *);
int  NmeaGet(void*);

int  ModemOff(void*);
int  StopDevice(void*);
int  SetConst(void*);
int  BurnOn(void*);
int  BurnOff(void*);
int  SetId(void*);
int  SetTimesToZero(void*);
void PortGetXchgCounts(void*);
void PortGetXchgErr(XCHG_ERR_COUNT*);
int  StartDevice(START_ADC_STRUCT*);

int  TimeGet(RTC_TIME_STRUCT*);
int  GetConst(void*);
int  CountsGet(PORT_COUNT_STRUCT*);
int  GetWorkTime(DEV_WORK_TIME_STRUCT*);
int  SetWorkTime(DEV_WORK_TIME_STRUCT*);

int  DataGet(void *);
int  StatusGet(DEV_STATUS_STRUCT *);


int GetModemNumber(void *);
int GetModemTime(void *);
int GetAlarmTime(void *);
int GetCalTime(void *);
int GetTimeForRelease(void *);
int GetBurnLen(void *);

int SetModemNumber(void *);
int SetCalTime(void *);
int SetTimeForRelease(void *);
int SetBurnLen(void *);
int SetModemTime(void *);
int SetAlarmTime(void *);

int SendAnyCommand(char *);

int RadioOn(void *);
int RadioOff(void *);
int LampOn(void *);
int LampOff(void *);
int BurnCmdOn(void *);
int BurnCmdOff(void *);
int SendPing11(void *);
int SendPing13(void *);
int SendPing9(void *);

//---------------------------------------------------------------------------
#endif
