//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include <Chart.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Series.hpp>
#include <Mask.hpp>
#include <ToolWin.hpp>
#include <Menus.hpp>
#include <ImgList.hpp>
#include <time.h>
#include "my_cmd.h"
#include "LPComponent.h"
#include "LPDrawLayers.h"
#include "SLComponentCollection.h"
#include "SLScope.h"
#include "ComPort.h"
#include "ReadPortThread.h"
#include <Dialogs.hpp>
#include "BMSpinEdit.h"
#include "light.h"
#include <FileCtrl.hpp>


#define DATA_SIZE               1

#define CM_READ_DATA            WM_USER+401
#define CM_NO_DATA              WM_USER+402 // Нет данных
#define CM_SHOW_TEST_RESULT     WM_USER+403 // результат тестирования
#define CM_SHOW_LINK            WM_USER+404
#define CM_SHOW_STATUS          WM_USER+405
#define CM_SHOW_WORK_TIME       WM_USER+406
#define CM_SHOW_PORT_COUNTS     WM_USER+407
#define CM_SHOW_PARAM_DATA      WM_USER+408

#define CLEAR_DATA              1


#define INFO_BOX(str) 	    Application->MessageBox(str, frmMain->Caption.c_str(), MB_OK | MB_ICONINFORMATION)
#define ERROR_BOX(str)      Application->MessageBox(str, frmMain->Caption.c_str(), MB_OK | MB_ICONERROR)
#define WARN_BOX(str)       Application->MessageBox(str, frmMain->Caption.c_str(), MB_OK | MB_ICONWARNING)
#define YESNO_BOX(str)	    Application->MessageBox(str, frmMain->Caption.c_str(), MB_YESNO | MB_ICONQUESTION)	
#define YESNOCANCEL_BOX(str)	    Application->MessageBox(str, frmMain->Caption.c_str(), MB_YESNOCANCEL | MB_ICONQUESTION)	


//---------------------------------------------------------------------------
// Режимы наладки
enum mode {
        off_mode,
        cmd_mode,
        oper_mode,
        ctrl_mode
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
        TStatusBar *sbInfo;
        TToolBar *tbButtons;
        TToolButton *btnReset;
        TToolButton *btnConst;
        TToolButton *btnSync;
        TToolButton *ToolButton4;
        TToolButton *ToolButton1;
        TPanel *pnUp;
        TGroupBox *gbTimes;
        TGroupBox *gbParams;
        TPanel *pnConfig1;
        TToolButton *btnPowerOff;
        TToolButton *btnModemOnOff;
        TToolButton *btnBurn;
        TPageControl *pcChangeMode;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TGroupBox *gbFileParams;
        TPanel *pnStartDate;
        TPanel *pnFinishDate;
        TPanel *pnBurnDate;
        TPanel *pnPopupLen;
        TPanel *pnModemNum;
        TPanel *pnAm3PopupDate;
        TPanel *pnAm3Cal;
        TEdit *edSampleString;
        TPanel *pnBurnTime;
        TPanel *pnAdcFreq;
        TPanel *pnAdcPga;
        TPanel *pnAdcEnergo;
        TPanel *pnNumBytes;
        TPanel *pnChannels;
        TPanel *pnFileLen;
        TSaveDialog *sdParamFile;
        TMainMenu *menuMain;
        TMenuItem *MenuFile;
        TMenuItem *menuSave;
        TMenuItem *N3;
        TMenuItem *menu10Min;
        TMenuItem *menu60Min;
        TMenuItem *menu1Day;
        TMenuItem *menu1Week;
        TMenuItem *N7;
        TMenuItem *menuExit;
        TMenuItem *menuCtrl;
        TMenuItem *menuOperator;
        TMenuItem *menuHelp;
        TMenuItem *menuAbout;
        TToolButton *btnSetName;
        TToolButton *ToolButton5;
        TMemo *memoLog;
        TTabSheet *TabSheet3;
        TToolButton *btnStartThread;
        TMenuItem *menuAdjust;
        TToolButton *btnSetToZero;
        TPanel *pnStatus;
        TGroupBox *gbStatus1;
        TLabel *lbStatus1_0;
        TLabel *lbStatus1_1;
        TLabel *lbStatus1_2;
        TLabel *lbStatus1_3;
        TLabel *lbStatus1_4;
        TLabel *lbStatus1_5;
        TLabel *lbStatus1_6;
        TLabel *lbStatus1_7;
        TGroupBox *gbStatus0;
        TLabel *lbStatus0_3;
        TLabel *lbStatus0_4;
        TLabel *lbStatus0_5;
        TLabel *lbStatus0_6;
        TLabel *lbStatus0_7;
        TPanel *pnStatusAndErrors;
        TGroupBox *gbResetCause;
        TLabel *lbStatusReset_0;
        TLabel *lbStatusReset_1;
        TLabel *lbStatusReset_2;
        TLabel *lbStatusReset_3;
        TLabel *lbStatusReset_4;
        TLabel *lbStatusReset_5;
        TLabel *Label17;
        TLabel *Label18;
        TGroupBox *gbCounts;
        TPanel *pnGnsTotalRx;
        TPanel *pnGnsTotalTx;
        TPanel *pnTxPack;
        TPanel *pnGnsFrameError;
        TPanel *pnRxStatErr;
        TPanel *pnGnsCmdError;
        TPanel *pnRxCmdErr;
        TPanel *pnGnsCrcError;
        TPanel *pnRxCrcErr;
        TPanel *pnRxPack;
        TGroupBox *gbMyCounts;
        TPanel *pnPcTotalRx;
        TPanel *pnPcTotalTx;
        TPanel *pnTxPackMy;
        TPanel *pnPcCntPack;
        TPanel *pnXchgOkMy;
        TPanel *pnPcCmdError;
        TPanel *pnRxCmdErrMy;
        TPanel *pnPcXchgErr;
        TPanel *pnXchgErrMy;
        TPanel *pnRxPackMy;
        TToolButton *btnTest;
        TGroupBox *gbModem;
        TSpeedButton *sbRunModule;
        TPanel *pnFiltFreq;
        TPanel *pnConstReg;
        TGroupBox *gbModemNum;
        TGroupBox *gbModemRtc;
        TGroupBox *gbModemAlarm;
        TGroupBox *gbModemLightTime;
        TLabel *Label13;
        TDateTimePicker *dtModemTime;
        TDateTimePicker *dtAlarmTime;
        TGroupBox *gbModemPopup;
        TGroupBox *gbModemBurnLen;
        TUpDown *udTimeForRelease;
        TUpDown *udBurnLen;
        TGroupBox *gbContr;
        TLabel *Label4;
        TLabel *lbFiltName;
        TComboBox *cbPGA;
        TBMSpinEdit *seFltFreq;
        TToolButton *btnModemRequest;
        TLight *ltModemNum;
        TLight *ltModemTime;
        TLight *ltAlarmTime;
        TLight *ltCalTime;
        TLight *ltTimeForRelease;
        TLight *ltBurnLen;
        TBitBtn *btnGetModemTime;
        TBitBtn *btnSetModemTime;
        TBitBtn *btnGetAlarmTime;
        TBitBtn *btnSetAlarmTime;
        TBitBtn *btnGetCalTime;
        TBitBtn *btnSetCalTime;
        TBitBtn *btnGetTimeForRelease;
        TBitBtn *btnSetTimeForRelease;
        TBitBtn *btnGetBurnLen;
        TBitBtn *btnSetBurnLen;
        TDateTimePicker *dtModemDate;
        TDateTimePicker *dtAlarmDate;
        TDateTimePicker *dtCalTime1;
        TDateTimePicker *dtCalTime0;
        TGroupBox *gbScope;
        TSLScope *slsDisplay;
        TToolButton *btnModemCommand;
        TOpenDialog *odParamFile;
        TMenuItem *menuOpen;
        TToolButton *btnGpsOn;
        TToolButton *ToolButton6;
        TGroupBox *gbStatus2;
        TLabel *lbStatus2_0;
        TLabel *lbStatus2_3;
        TLabel *lbStatus2_4;
        TLabel *lbStatus2_5;
        TLabel *lbStatus2_6;
        TLabel *lbStatus2_7;
        TLabel *lbAdcFreqName;
        TComboBox *cbAdcFreq;
        TTimer *timIdle;
        TTimer *tmFind;
        TComboBox *cbAdcSample;
        TComboBox *cbAdcCons;
        TCheckBox *cbConstReg;
        TBMSpinEdit *seFreq;
        TCheckBox *cbFreq;
        TComboBox *cbAdcPGA;
        TComboBox *cbNumBytes;
        TComboBox *cbDataFileLen;
        TCheckBox *cbChan1;
        TCheckBox *cbChan2;
        TCheckBox *cbChan3;
        TCheckBox *cbChan4;
        TDateTimePicker *dtStartDate;
        TDateTimePicker *dtStartTime;
        TDateTimePicker *dtFinishDate;
        TDateTimePicker *dtFinishTime;
        TDateTimePicker *dtBurnDate;
        TDateTimePicker *dtBurnTime;
        TUpDown *udBurnTime;
        TUpDown *udPopupLen;
        TEdit *edModemNum;
        TDateTimePicker *dtAm3PopupDate;
        TDateTimePicker *dtAm3PopupTime;
        TMaskEdit *meAm3Cal0;
        TMaskEdit *meAm3Cal1;
        TLabel *lbUtcTimeMet;
        TLabel *Label11;
        TComboBox *cbModemNum;
        TEdit *meTimeForRelease;
        TEdit *meBurnLen;
        TEdit *edBurnTime;
        TEdit *mePopupLen;
        TUpDown *udModemNum;
        TEdit *meModemNum;
        TUpDown *udmeModemNum;
        TPanel *pnPosition;
        TEdit *edPosition;
        TSplitter *Splitter1;
        TImageList *imgList;
        TGroupBox *gbModemBurnOn;
        TLight *ltBurnCmdOnOff;
        TBitBtn *btnBurnCmdOn;
        TGroupBox *gbModemLampOn;
        TLight *ltLampOnOff;
        TBitBtn *btnLampOn;
        TGroupBox *gbModemRadioOn;
        TLight *ltRadioOnOff;
        TBitBtn *btnRadioOn;
        TGroupBox *gbModemPingSend;
        TLight *ltPing;
        TBitBtn *btnPing11;
        TEdit *edPingCount;
        TUpDown *udPingCount;
        TGroupBox *gbEnviron;
        TGroupBox *gbEnvironement;
        TPanel *Panel29;
        TPanel *pnTemp1;
        TPanel *Panel31;
        TPanel *pnPressure;
        TPanel *Panel42;
        TPanel *pnTemp0;
        TGroupBox *gbOrientation;
        TPanel *pnPitchName;
        TPanel *pnPitch;
        TPanel *pnRollName;
        TPanel *pnRoll;
        TPanel *pnHeadName;
        TPanel *pnHead;
        TToolButton *btnResetWorkTime;
        TGroupBox *gbAdc;
        TPanel *pnAdcNum;
        TPanel *Panel3;
        TPanel *Panel6;
        TPanel *Panel9;
        TPanel *Panel11;
        TPanel *Panel13;
        TLight *ltAdc1;
        TPanel *Panel14;
        TLight *ltAdc2;
        TPanel *Panel15;
        TLight *ltAdc3;
        TPanel *Panel16;
        TLight *ltAdc4;
        TPanel *pnAdcStatus;
        TListBox *cbPortName;
        TGroupBox *gbModemWriteParams;
        TLight *ltApplyCommand;
        TBitBtn *btnApplyCommand;
        TComboBox *cbPingFreq;
        TMenuItem *menuOpenLogs;
        TOpenDialog *odOpenLogs;
        TCheckBox *cbChangeModemName;
        TLabel *Label1;
        TPanel *pnComments;
        TProgressBar *pbLinkQuality;
        TGroupBox *gbRandomStr;
        TLight *ltModemCmd;
        TEdit *edAnyCommand;
        TBitBtn *btnModemAnyString;
        TPanel *pnDisk;
        TDriveComboBox *dcbDisk;
        TBitBtn *btnCheckParams;
        TLabel *Label5;
        TSpeedButton *SpeedButton1;
        TSpeedButton *sbOpenLogPath;
        TOpenDialog *odOpenLogPath;
        TLabel *lbStatus2_1;
        TLabel *lbStatus2_2;
        TLabel *lbStatus0_2;
        TBevel *Bevel1;
        TLabel *lbStatus0_0;
        TLabel *lbRele1;
        TLabel *lbRele4;
        TLabel *lbRele5;
        TLabel *lbRele2;
        TLabel *lbRele3;
        TLabel *lbRele6;
        TLabel *lbRele7;
        TLabel *lbNumPoint;
        TComboBox *cbTimeLimit;
        TCheckBox *cbUpdateTime;
        TLabel *lbStatus0_1;
        TLabel *lbRele0;
        TMenuItem *menu1Month;
        TGroupBox *gbFreqs;
        TPanel *Panel18;
        TPanel *pnCclk;
        TPanel *Panel26;
        TPanel *pnSclk;
        TMenuItem *menuLang;
        TMenuItem *menuRus;
        TMenuItem *N9;
        TMenuItem *menuEng;
        TLabel *lbConsum;
        TComboBox *cbConsum;
        TLabel *Label7;
        TComboBox *cbChop;
        TPanel *pnUTCTime;
        TPanel *pnTimeGNS110;
        TPanel *pnGpsTime;
        TPanel *pnGpsLat;
        TPanel *pnGpsLon;
        TPanel *lbGpsLon;
        TPanel *lbGpsLat;
        TPanel *lbGpsTime;
        TPanel *lbTimeGNS110;
        TPanel *lbUTCTime;
        TPanel *pnQuartz;
        TPanel *pnQuartzFreq;
        TPanel *Panel22;
        TPanel *pnSupplyV;
        TPanel *Panel28;
        TPanel *pnSupplyA;
        TPanel *Panel24;
        TPanel *pnBurnV;
        TPanel *Panel25;
        TPanel *pnBurnA;
        TPanel *Panel53;
        TPanel *pnBurnExtV;
        TPanel *Panel23;
        TPanel *pnModemV;
        TPanel *Panel30;
        TPanel *pnModemA;
        TLabel *lbUtcTimeComment;
        TBitBtn *btnSetModemNum;
        TBitBtn *btnGetModemNum;

        void __fastcall FormResize(TObject *Sender);
        void __fastcall btnCloseClick(TObject *Sender);
        void __fastcall btnResetClick(TObject *Sender);
        void __fastcall btnSyncClick(TObject *Sender);
        void __fastcall btnConstClick(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall SLScope1XAxisCustomLabel(TObject *Sender,
          Real SampleValue, AnsiString &AxisLabel);
        void __fastcall btnPowerOffClick(TObject *Sender);
        void __fastcall btnModemOnOffClick(TObject *Sender);
        void __fastcall btnBurnClick(TObject *Sender);
        void __fastcall btnBurnOffClick(TObject *Sender);
        void __fastcall menuExitClick(TObject *Sender);
        void __fastcall menuAboutClick(TObject *Sender);
        void __fastcall menu10MinClick(TObject *Sender);
        void __fastcall menu60MinClick(TObject *Sender);
        void __fastcall menu1DayClick(TObject *Sender);
        void __fastcall menu1WeekClick(TObject *Sender);
        void __fastcall menuSaveClick(TObject *Sender);
        void __fastcall btnSetNameClick(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall btnStartThreadClick(TObject *Sender);
        void __fastcall btnSetToZeroClick(TObject *Sender);
        void __fastcall btnTestClick(TObject *Sender);
        void __fastcall sbRunModuleClick(TObject *Sender);
        void __fastcall btnModemRequestClick(TObject *Sender);
        void __fastcall btnGetModemNumClick(TObject *Sender);
        void __fastcall btnGetModemTimeClick(TObject *Sender);
        void __fastcall btnGetAlarmTimeClick(TObject *Sender);
        void __fastcall btnGetCalTimeClick(TObject *Sender);
        void __fastcall btnGetTimeForReleaseClick(TObject *Sender);
        void __fastcall btnGetBurnLenClick(TObject *Sender);
        void __fastcall btnSetModemNumClick(TObject *Sender);
        void __fastcall btnSetCalTimeClick(TObject *Sender);
        void __fastcall btnSetTimeForReleaseClick(TObject *Sender);
        void __fastcall btnSetBurnLenClick(TObject *Sender);
        void __fastcall btnSetModemTimeClick(TObject *Sender);
        void __fastcall btnSetAlarmTimeClick(TObject *Sender);
        void __fastcall btnStopClick(TObject *Sender);
        void __fastcall btnModemCommandClick(TObject *Sender);
        void __fastcall btnModemAnyStringClick(TObject *Sender);
        void __fastcall btnGpsOnClick(TObject *Sender);
        void __fastcall menuOpenClick(TObject *Sender);
        void __fastcall timIdleTimer(TObject *Sender);
        void __fastcall sbInfoDblClick(TObject *Sender);
        void __fastcall tmFindTimer(TObject *Sender);
        void __fastcall cbFreqClick(TObject *Sender);
        void __fastcall mePopupLenChange(TObject *Sender);
        void __fastcall meAm3Cal0Change(TObject *Sender);
        void __fastcall meAm3Cal1Change(TObject *Sender);
        void __fastcall edModemNumExit(TObject *Sender);
        void __fastcall cbConstRegClick(TObject *Sender);
        void __fastcall cbModemNumClick(TObject *Sender);
        void __fastcall meTimeForReleaseChange(TObject *Sender);
        void __fastcall meBurnLenChange(TObject *Sender);
        void __fastcall edBurnTimeChange(TObject *Sender);
        void __fastcall edModemNumChange(TObject *Sender);
        void __fastcall edBurnTimeExit(TObject *Sender);
        void __fastcall mePopupLenExit(TObject *Sender);
        void __fastcall edPositionChange(TObject *Sender);
        void __fastcall Splitter1Moved(TObject *Sender);
        void __fastcall btnRadioOnClick(TObject *Sender);
        void __fastcall btnLampOnClick(TObject *Sender);
        void __fastcall btnBurnCmdOnClick(TObject *Sender);
        void __fastcall btnPing11Click(TObject *Sender);
        void __fastcall btnResetWorkTimeClick(TObject *Sender);
        void __fastcall menuStandardClick(TObject *Sender);
        void __fastcall menuAdvancedClick(TObject *Sender);
        void __fastcall cbChangeModemNameClick(TObject *Sender);
        void __fastcall menuOpenLogsClick(TObject *Sender);
        void __fastcall btnApplyCommandClick(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall btnCheckParamsClick(TObject *Sender);
        void __fastcall cbTimeLimitChange(TObject *Sender);
        void __fastcall menu1MonthClick(TObject *Sender);
        void __fastcall menuRusClick(TObject *Sender);
        void __fastcall menuEngClick(TObject *Sender);

public:		// User declarations
        __fastcall TfrmMain(TComponent* Owner);

        void __fastcall  PrintLog(String text, u8 * buf, int len);
        void __fastcall  GetModemParameters(void);
        void __fastcall  SetModemButtons(bool);

        int  __fastcall Querry(String name, u8* send, int tx, u8* recv, int rx, int*);
	void __fastcall LogOut(char*, bool log_only = false);
        void __fastcall EnableControl(void);
        void __fastcall DisableControl(void);
        void __fastcall TimeGNS110(long);
        int __fastcall  TimeGet(void);
        void __fastcall TimeUTC(void);
        int  __fastcall TimeSyncOld(void);
        int  __fastcall DataGet(void);

        void __fastcall CreateParamData(TIME_ENUM);
        void __fastcall ShowParamData(void*);

        void __fastcall ShowModemTime(SYSTEMTIME * st);
        void __fastcall ShowAlarmTime(SYSTEMTIME * st);
        void __fastcall ShowCalTime(u16 h0, u16 m0, u16 h1, u16 m1);
        void __fastcall TerminateAllThreads(void);

        void __fastcall ShowTimeForRelease(int len);
        void __fastcall ShowBurnLen(int len);
        void __fastcall TerminateScope(void);
        void __fastcall ShowStatusIfChange(void*, u8);
private:

        ADS1282_Regs  regs;
        s64 big_timer;
        struct {
           int t0;
           int tick;
           int delay;
        } test_result, test_modem;
        struct {
           int h_memo;
           int h_status;
           int h_contr;
           int h_mode;
        } save_param;

         struct {
            bool  burn;
            bool  lamp;
            bool  radio;
            unsigned : 1; /// Проверить, что это такое!!!
         } modem_inner_state;

public:		// User declarations
        s64 __fastcall GetBigTimer(void);
        int __fastcall CanPowerOffModem(void);
        void __fastcall GetWorkDisk(String);

        void __fastcall ButtonStateInStart(bool state);
        void __fastcall ShowModemNum(u16 num);
        void __fastcall ShowTestModem(void*);
        void __fastcall HideButtons(void);
        void __fastcall UnhideButtons(void);
        void __fastcall ShowStatus(void*);
        void __fastcall ShowWorkTime(void* v);
        void __fastcall ShowPortCounts(void* v);
        bool __fastcall VolumeIsFat(String);
        void __fastcall SetModemLights(bool);
        void __fastcall WriteDataToFile(void*);

///////
        void __fastcall  OscilMenu(TObject * Sender);
        void __fastcall  OperMenu(TObject * Sender);
        void __fastcall  CtrlMenu(TObject * Sender);
        void __fastcall  OffMenu(TObject * Sender);
        void __fastcall  TestMenu(TObject * Sender);
        void __fastcall  ChangeLangID(void);
        myLangID __fastcall  GetLangID(void);
public:
        CRITICAL_SECTION time_cs;
        bool bEndThread;
        STATION_PORT_STRUCT port_set[255]; // всего 255 портов
        int   gns_num;

        String PortName;
        HANDLE PortHandle;
        COMMTIMEOUTS m_Timeouts;
        int    index;
        bool   enable_measure;
        DCB    dcb;
        u16    freq;

        u8      pga;

        DEV_ADDR_STRUCT     dev_addr;

        int                 timer_tick;
        ReadPortThread*     MyThread;
        int numPoint;
        u32                 StartTime;
        float               flt_freq, quartz_freq;
        HANDLE              log_fd;
        long                start_time, curr_time;
        bool                run_ok, gps_on, test_run, enable_log, first_run, end_aqq;
        unsigned short      hhh,mm,ss;


        MODEM_STRUCT         modem;
        START_ADC_STRUCT     start;
        param_file_struct    param_struct;

        void __fastcall     CMReadData(TMessage &Message);
        void __fastcall     CMNoData(TMessage &Message);
        void __fastcall     CMShowLink(TMessage &Message);
        void __fastcall     CMShowStatus(TMessage & Message);
        void __fastcall     CMShowWorkTime(TMessage & Message);
        void __fastcall     CMShowPortCounts(TMessage & Message);
        void __fastcall     CMShowParamData(TMessage &Message);
BEGIN_MESSAGE_MAP
  MESSAGE_HANDLER(CM_READ_DATA,  TMessage, CMReadData)
  MESSAGE_HANDLER(CM_NO_DATA,  TMessage, CMNoData)
  MESSAGE_HANDLER(CM_SHOW_LINK, TMessage, CMShowLink)
  MESSAGE_HANDLER(CM_SHOW_STATUS, TMessage, CMShowStatus)
  MESSAGE_HANDLER(CM_SHOW_WORK_TIME, TMessage, CMShowWorkTime)
  MESSAGE_HANDLER(CM_SHOW_PORT_COUNTS, TMessage, CMShowPortCounts)
  MESSAGE_HANDLER(CM_SHOW_PARAM_DATA, TMessage, CMShowParamData)
END_MESSAGE_MAP(TControl)
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
