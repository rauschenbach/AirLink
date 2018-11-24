//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <io.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include "my_cmd.h"
#include <errno.h>
#include <stddef.h>		/* _threadid variable */
#include <process.h>		/* _beginthread, _endthread */
#include <time.h>		/* time, _ctime */
#include "const.h"
#include "main.h"
#include "utils.h"
#include "about.h"
#include "proto.h"
#include "FindStationsThread.h"
#include "CheckFileThread.h"
#include "OpenFileThread.h"
#include "SaveFileThread.h"
#include "ModemRequestThread.h"
#include "ModemCommandThread.h"
#include "WriteCommandThread.h"
#include "number.h"
#include "version.h"
#include "config.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "light"
#pragma link "LPComponent"
#pragma link "LPDrawLayers"
#pragma link "SLComponentCollection"
#pragma link "SLScope"
#pragma link "BMSpinEdit"
#pragma link "light"
#pragma resource "*.dfm"

static myLangID lang;


extern get_dsp_status(void *);
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent * Owner):TForm(Owner), index(0),
enable_measure(false), timer_tick(0), test_run(false), bEndThread(true),
run_ok(false), MyThread(NULL), enable_log(true), big_timer(0), first_run(true), end_aqq(false)
{
    memset(&modem_inner_state, 0, sizeof(modem_inner_state));	/* ���������� ��� ��������� */
    lang = lang_eng;
}

//---------------------------------------------------------------------------
// ������� �������, ��������� �����
int __fastcall TfrmMain::Querry(String name, u8 * send, int tx, u8 * recv, int rx, int *baud)
{
    int i;
    unsigned long num;
    bool res = false;
    static int first = 0;
    char str[128];
    int rate[] = { 115200, 230400, 460800, 921600 };

    for (i = 0; i < 4; i++) {
	PortHandle = CreateFile(name.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (PortHandle != INVALID_HANDLE_VALUE) {
	    sprintf(str, "baud=%d parity=N data=8 stop=1", rate[i]);
	    BuildCommDCB(str, &dcb);
	    SetCommState(PortHandle, &dcb);
	    m_Timeouts.ReadIntervalTimeout = 10;
	    m_Timeouts.ReadTotalTimeoutMultiplier = m_Timeouts.ReadTotalTimeoutConstant = 25;
	    m_Timeouts.WriteTotalTimeoutMultiplier = m_Timeouts.WriteTotalTimeoutConstant = 5;
	    SetCommTimeouts(PortHandle, &m_Timeouts);
	    WriteFile(PortHandle, send, tx, &num, NULL);

	    Sleep(5);
	    num = 0;
	    res = ReadFile(PortHandle, recv, rx, &num, NULL);
	    CloseHandle(PortHandle);
	    if (res && num) {
		*baud = rate[i];
		break;
	    }
	}
    }
    return (int) num;		// ������� ���������
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnCloseClick(TObject * Sender)
{
    bEndThread = true;
    TerminateAllThreads();
    DisableControl();
    Close();
}

//---------------------------------------------------------------------------
// ������ ����������������
void __fastcall TfrmMain::btnTestClick(TObject * Sender)
{
    WriteCommandThread *thread;
    test_result.t0 = 0;
    test_result.tick = 0;
    test_result.delay = time(NULL);
    first_run = false;		// ���������

    if (lang == lang_rus)
	LogOut("�������� ������������...���������!");
    else
	LogOut("Begin SelfTest...wait!");

    enable_log = false;
    thread = new WriteCommandThread(InitTest, NULL, false, false);
    thread->WaitFor();
    delete thread;
}

//---------------------------------------------------------------------------
// ����c�� � Memo
void __fastcall TfrmMain::PrintLog(String text, u8 * buf, int len)
{
    int i;
    String str;
    char buf1[1024];

    for (i = 0; i < len; i++)
	str += String(IntToHex((u8) buf[i], 2) + " ");
    LogOut((text + str).c_str());
}

//---------------------------------------------------------------------------
// ����� � ���
void __fastcall TfrmMain::LogOut(char *text, bool log_only)
{
    int i, len;
    char buf[1024];
    String str;
    char crlf[] = "\r\n";
    static String old;
    unsigned long bw;

    str = TimeString() + text;

    // ��������� � �����
    memset(buf, 0, sizeof(buf));
    memcpy(buf, str.c_str(), str.Length());

    // ������ ������� ������
    for (i = 0; i < str.Length(); i++) {
	if (buf[i] == '\x0D' || buf[i] == '\x0A') {
	    buf[i] = 0;
	    break;
	}
    }

    if (!log_only && enable_log) {
	memoLog->Lines->Add(buf);
    }

    if (log_fd != INVALID_HANDLE_VALUE && old != String(text)) {
	old = String(text);
	WriteFile(log_fd, buf, strlen(buf), &bw, NULL);
	WriteFile(log_fd, crlf, strlen(crlf), &bw, NULL);	// ��������� ������� ������
    }
}

//---------------------------------------------------------------------------
// �������� ������
void __fastcall TfrmMain::EnableControl(void)
{
    int num, baud;
    enable_log = true;		// ����� ������
    start_time = time(NULL);
    bEndThread = true;
    TerminateAllThreads();
    btnStartThread->Enabled = true;
    btnTest->Enabled = true;

    num = port_set[cbPortName->ItemIndex].port_num;
    baud = port_set[cbPortName->ItemIndex].baud;
    if (PortInit(num, baud)) {
	LogOut("Port init OK");
    }
    // ������ �������� � ���������
//    frmAbout->lbGnsVer->Caption = "GNS110 firmware\t" + port_set[cbPortName->ItemIndex].ver;

    if (port_set[cbPortName->ItemIndex].v != get_version() || port_set[cbPortName->ItemIndex].r != get_revision()) {


	if (lang == lang_rus)
	    LogOut("������ GNS AirLink ���������� �� ������ �������� ������������!");
	else
	    LogOut("GNS AirLink version differs from recorder's firmware version!");


	// ������ ������� ������ ������ ��������
	if (port_set[cbPortName->ItemIndex].v > get_version() || port_set[cbPortName->ItemIndex].r > get_revision()) {
	    if (lang == lang_rus)
		LogOut("�������� GNS AirLink �� ����� ������!");
	    else
		LogOut("Update GNS AirLink version!");


	} else if (port_set[cbPortName->ItemIndex].v < get_version() || port_set[cbPortName->ItemIndex].r < get_revision()) {
	    if (lang == lang_rus)
		LogOut("�������� �������� ������������ �� ����� ������!");
	    else
		LogOut("Update recorder's firmware!");
	}
    }

    bEndThread = false;
    MyThread = new ReadPortThread(false);
    MyThread->Priority = tpHighest;	// ����� ����!

    run_ok = true;
}

//---------------------------------------------------------------------------
// ����c�� ����� ����������
void __fastcall TfrmMain::TimeUTC(void)
{
    int i;
    char str[128];
    time_t t;

    t = time(NULL);
    sec_to_str(t, str);;

    lbUTCTime->Caption = str;
}

//---------------------------------------------------------------------------
// ������� �����
// ���� ����� ����������� ����� ��� �� 30 ������ - ������� ��������
void __fastcall TfrmMain::TimeGNS110(long t)
{
    char buf[128];
    time_t n;
    static int i = 0;

    n = time(NULL);
    sec_to_str(t, buf);

    if (abs(t - n) > 30) {
	lbStatus1_0->Font->Color = clRed;

	if (i++ % 2 == 0) {
	    lbTimeGNS110->Font->Color = clRed;
	} else {
	    lbTimeGNS110->Font->Color = clWindowText;
	}
    } else {
	lbStatus1_0->Font->Color = clGray;
	lbTimeGNS110->Font->Color = clWindowText;
    }
    lbTimeGNS110->Caption = buf;
}

//---------------------------------------------------------------------------
// ������-������� ����������, ����� ������ ������ ����� ��� ���������
void __fastcall TfrmMain::btnConstClick(TObject * Sender)
{
    frmConst->Left = this->Left + 200;
    frmConst->Top = this->Top + 50;
    frmConst->ShowModal();
}

//---------------------------------------------------------------------------
// �������� ����� � �������������
void __fastcall TfrmMain::btnSyncClick(TObject * Sender)
{
    static time_t t0;
    t0 = time(NULL) + 1;	// +1 �������

    WriteCommandThread *thread;
    thread = new WriteCommandThread(TimeSync, &t0, false, false);
    thread->WaitFor();
    delete thread;
}
          
//---------------------------------------------------------------------------
// ��� �������� ��������� ������� LOG - ����
void __fastcall TfrmMain::FormActivate(TObject * Sender)
{
    char str[256];
    time_t t0;
    TIME_DATE td;
    InitializeCriticalSection(&time_cs);


    this->Caption = "GNS AirLink";
    Application->Title = "GNS AirLink. GNS & Modem control!";

    t0 = time(NULL);

    CreateParamData(TIME_60_MIN);
    param_struct.am3_modem_type = 0;
    param_struct.modem_num = 0;

    ChangeLangID();

    ShowParamData(&param_struct);

    menuStandardClick(this);
    menuSave->Enabled = true;

    pcChangeMode->ActivePageIndex = 1;	// ������ �� ������ �������
    StartTime = t0;		// ����� ������� ��������� ��������

    save_param.h_memo = memoLog->Height;
    save_param.h_status = pnStatus->Height;
    save_param.h_contr = gbContr->Height;
    save_param.h_mode = pcChangeMode->Height;

    ChangeLangID();


    // ��������� log ����
    sec_to_td(t0, &td);
    CreateDirectory("LOGS", NULL);
    sprintf(str, "LOGS\\LOG_%02d%02d%02d_%02d%02d.log\0", td.day, td.month, td.year - 2000, td.hour, td.min);
    log_fd = CreateFile(str, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (lang == lang_rus)
	sprintf(str, "�������� ��������� GNS AirLink ver: %01d.%02d\0\r\n", get_version(), get_revision());
    else
	sprintf(str, "Run program GNS AirLink ver: %01d.%02d\0\r\n", get_version(), get_revision());
    LogOut(str);
    tmFind->Enabled = true;	// ������ ������ �������
}

//---------------------------------------------------------------------------
// ������� ��������� ������������ ������
// ��������� ������
void __fastcall TfrmMain::ShowTestModem(void *su)
{
    char buf[256];
    DEV_STATUS_STRUCT *status;

    test_modem.tick = 0;
    test_modem.t0 == 0;

    UnhideButtons();

    if (su != NULL) {
	status = (DEV_STATUS_STRUCT *) su;

	// �������-������� ������ ��� ���
	if (status->st_main & 0x02) {
	    if (lang == lang_rus)
		LogOut("������������ ������ ���������, ��� ������ ��� ����� ����������!\n");
	    else
		LogOut("Modem test finished, no modem or modem error!\n");
	} else {
	    if (lang == lang_rus)
		LogOut("������������ ������ ���������, ����� ������ ���������� �� ����� ������!\n");
	    else
		LogOut("Modem test finished, modem alarm time setup on one day ahead!\n");
	}
    }
}

//---------------------------------------------------------------------------
// ����� ������
void __fastcall TfrmMain::TerminateAllThreads(void)
{
    TerminateScope();		// ������������� ���������� � ������ �����

    // ��������� �����
    if (MyThread != NULL) {
	MyThread->WaitFor();
	delete MyThread;
	MyThread = NULL;
    }
    // ������� ����
    PortClose();
}

//---------------------------------------------------------------------------
// ��������� ��������� ��� ���?
int __fastcall TfrmMain::CanPowerOffModem(void)
{
    int res = 0;

    // ������� �����?
    if (lbStatus2_1->Font->Color == clGreen) {
	if (lang == lang_rus)
	    res = YESNOCANCEL_BOX("����� ��������� ���������. ��������� �����?");
	else
	    res = YESNOCANCEL_BOX("Modem is still on. Off modem?");

	if (res == IDYES)
	    res = 1;
	else if (res == IDNO)
	    res = 0;
	else
	    res = -1;
    }
    return res;
}

//---------------------------------------------------------------------------
// ����� DSP
void __fastcall TfrmMain::btnResetClick(TObject * Sender)
{
    WriteCommandThread *thread;
    int res;

    res = CanPowerOffModem();
    if (res == 1) {		// �������� ������� �����
	thread = new WriteCommandThread(ModemOff, NULL, false, false);
	thread->WaitFor();
	delete thread;
    } else if (res == -1) {
	return;
    }

    Sleep(250);
    thread = new WriteCommandThread(ResetDSP, NULL, false, false);
    thread->WaitFor();
    delete thread;

    // �������� ����� - ����!
    bEndThread = true;
    TerminateAllThreads();
    DisableControl();
    first_run = true;
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnPowerOffClick(TObject * Sender)
{
    WriteCommandThread *thread;
    int res;

    res = CanPowerOffModem();
    if (res == 1) {		// �������� ������� �����
	thread = new WriteCommandThread(ModemOff, NULL, false, false);
	thread->WaitFor();
	delete thread;
    } else if (res == -1) {
	return;
    }

    Sleep(250);
    thread = new WriteCommandThread(PowerOff, NULL, false, false);
    thread->WaitFor();
    delete thread;

    // �������� ����� - ����!
    bEndThread = true;
    TerminateAllThreads();
    DisableControl();
    first_run = true;
}

//---------------------------------------------------------------------------
// �������� ����� � �������� ����� �� �����
// �������� ����� 8-� �������
void __fastcall TfrmMain::btnModemOnOffClick(TObject * Sender)
{
    WriteCommandThread *thread;
    DEV_STATUS_STRUCT status;
    bool bit;

    get_dsp_status(&status);
    first_run = false;

    bit = (status.ports & RELE_MODEM_BIT ? true : false);


    if (!bit) {
	enable_log = true;

	if (lang == lang_rus)
	    LogOut("��������� � ���� ������...���������!");
	else
	    LogOut("Modem Power on and selftest...wait!");

	test_modem.t0 = 0;
	test_modem.tick = 0;
	test_modem.delay = time(NULL);
	thread = new WriteCommandThread(ModemOn, NULL, false, false);
	thread->WaitFor();
	delete thread;
    } else {
	enable_log = true;

	if (lang == lang_rus)
	    LogOut("���������� ������");
	else
	    LogOut("Modem power off");

	thread = new WriteCommandThread(ModemOff, NULL, false, false);
	thread->WaitFor();
	delete thread;
    }
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnBurnClick(TObject * Sender)
{
    WriteCommandThread *thread;
    DEV_STATUS_STRUCT status;
    bool bit;

    get_dsp_status(&status);

    bit = (status.ports & RELE_BURN_BIT ? true : false);

    // ���� �����
    if (bit) {
	thread = new WriteCommandThread(BurnOff, NULL, false, false);
	thread->WaitFor();
	delete thread;
    } else {			/*if(!(status.ports & RELE_BURN_BIT)) */
// �������� - ��������
	thread = new WriteCommandThread(BurnOn, NULL, false, false);
	thread->WaitFor();
	delete thread;
    }
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnBurnOffClick(TObject * Sender)
{
    WriteCommandThread *thread;
    thread = new WriteCommandThread(BurnOff, NULL, false, false);
    thread->WaitFor();
    delete thread;
}

//---------------------------------------------------------------------------
// �����
void __fastcall TfrmMain::menuExitClick(TObject * Sender)
{
    Close();
}

//---------------------------------------------------------------------------

void __fastcall TfrmMain::menuAboutClick(TObject * Sender)
{
    frmAbout->Left = this->Left + 400;
    frmAbout->Top = this->Top + 50;
    frmAbout->ShowModal();
}

//---------------------------------------------------------------------------
// ������� ������� ��� ����������
// ���������� �� 5 ����� + 10 ����� �� �����
void __fastcall TfrmMain::CreateParamData(TIME_ENUM param)
{
    time_t t;

    // ������� �� 2
    pcChangeMode->ActivePage = TabSheet2;

    //  �������� ����� ��  "������"
    t = time(NULL);

    
    switch (param) {
    case TIME_10_MIN:
	param_struct.start_time = (t - t % 60) + 420;	// �� 5 ����� ����� "������"
	param_struct.finish_time = param_struct.start_time + RECORD_TIME * 2;
	param_struct.data_file_len = 1;
	break;

    case TIME_1_DAY: // 1 ����
	param_struct.start_time = (t - t % 300) + 600;	// �� 10 ����� ����� "������"
	param_struct.finish_time = param_struct.start_time + RECORD_ONE_DAY;
	param_struct.data_file_len = 4;
	break;

    case TIME_1_WEEK: // ������
	param_struct.start_time = (t - t % 300) + 600;	// �� 10 ����� ����� "������"
	param_struct.finish_time = param_struct.start_time + RECORD_ONE_WEEK;
	param_struct.data_file_len = 24;
	break;
               
    case TIME_1_MONTH:  // �����
	param_struct.start_time = (t - t % 300) + 300;	// �� 5 ����� ����� "������"
	param_struct.finish_time = param_struct.start_time + RECORD_ONE_MONTH;
	param_struct.data_file_len = 1;
	break;


    case TIME_60_MIN: // 60 �����
    default:
	param_struct.start_time = (t - t % 300) + 600;	// �� 10 ����� ����� "������"
	param_struct.finish_time = param_struct.start_time + 3600;
	param_struct.data_file_len = 1;
	break;
    }
    param_struct.burn_time = param_struct.finish_time + TIME_BURN_AFTER_FINISH;
    param_struct.popup_len = POPUP_DURATION_AIRLINK;
    param_struct.releburn_time = RELEBURN_TIME_AIRLINK;
    param_struct.modem_num = 1;
    param_struct.am3_popup_time = param_struct.burn_time + param_struct.popup_len;
    param_struct.am3_cal_h0 = 8;
    param_struct.am3_cal_m0 = 0;
    param_struct.am3_cal_h1 = 9;
    param_struct.am3_cal_m1 = 0;
    param_struct.sample_freq = 250;
    param_struct.power_cons = 1;	// �������
    param_struct.pga_adc = 1;
    param_struct.num_bytes = 3;
    param_struct.on_off_channels = 0x0F;
}

//---------------------------------------------------------------------------
// ������� ��������� �� �����
void __fastcall TfrmMain::ShowParamData(void *p)
{
    char buf[512];
    u8 i;
    int j;
    param_file_struct *param;
    TIME_DATE td;
    SYSTEMTIME st;


    //--------------- ��� ������ ��������� ��������� ����
    cbModemNumClick(this);
    mePopupLenChange(this);
    meAm3Cal0Change(this);
    meAm3Cal1Change(this);
    cbFreqClick(this);
    cbConstRegClick(this);

    //--------------- �������� ����������� ����
    memset(&st, 0, sizeof(SYSTEMTIME));
    st.wDay = 1;
    st.wMonth = 1;
    st.wYear = 2010;
    dtStartDate->MinDate = SystemTimeToDateTime(st);
    dtFinishDate->MinDate = SystemTimeToDateTime(st);
    dtBurnDate->MinDate = SystemTimeToDateTime(st);
    dtAm3PopupDate->MinDate = SystemTimeToDateTime(st);


    //--------------- �������� ������������ ����
    memset(&st, 0, sizeof(SYSTEMTIME));
    st.wDay = 19;
    st.wMonth = 1;
    st.wYear = 2038;
    st.wHour = 3;
    st.wMinute = 14;
    st.wSecond = 8;
    dtStartDate->MaxDate = SystemTimeToDateTime(st);
    dtFinishDate->MaxDate = SystemTimeToDateTime(st);
    dtBurnDate->MaxDate = SystemTimeToDateTime(st);
    dtAm3PopupDate->MaxDate = SystemTimeToDateTime(st);


    //--------------- �� ����� �� ������� ��� ������
    dtModemDate->Date = SystemTimeToDateTime(st);
    dtModemTime->Time = SystemTimeToDateTime(st);
    dtAlarmDate->Date = dtModemDate->Date + 1.0;
    dtAlarmTime->Time = dtModemTime->Time;


    if (p == NULL)
	return;

    param = (param_file_struct *) p;


    //-------------�������� ������
    if (param->my_str != NULL)
	edSampleString->Text = String(param->my_str);

    //----------- ������� ���������
    edPosition->Text = IntToStr(param->pos);

    //----------- ������ �����������
    memset(&st, 0, sizeof(SYSTEMTIME));
    sec_to_st(param->start_time, &st);
    dtStartDate->Date = SystemTimeToDateTime(st);
    dtStartTime->Time = SystemTimeToDateTime(st);


    //----------- ��������� �����������
    memset(&st, 0, sizeof(SYSTEMTIME));
    sec_to_st(param->finish_time, &st);
    dtFinishDate->Date = SystemTimeToDateTime(st);
    dtFinishTime->Time = SystemTimeToDateTime(st);


    //----------- ����� ������ ��������
    memset(&st, 0, sizeof(SYSTEMTIME));
    sec_to_st(param->burn_time, &st);
    dtBurnDate->Date = SystemTimeToDateTime(st);
    dtBurnTime->Time = SystemTimeToDateTime(st);


    //----------- ������������ �������� � ��������
    udBurnTime->Position = param->releburn_time;

    //----------- ������������ �������� � �������
    udPopupLen->Position = param->popup_len;
    mePopupLen->Text = IntToStr(param->popup_len);

    //----------- ��� ������ ��������
    cbModemNum->ItemIndex = param->am3_modem_type;

    //----------- ����� ������ ��������
    edModemNum->Text = IntToStr(param->modem_num);

    cbModemNumClick(this);

    //----------- ����� ���������� ��������
    memset(&st, 0, sizeof(SYSTEMTIME));
    sec_to_st(param->am3_popup_time, &st);
    dtAm3PopupDate->Date = SystemTimeToDateTime(st);
    dtAm3PopupTime->Time = SystemTimeToDateTime(st);


    //-----------  ������� ����� �����
    sprintf(buf, "%02d.%02d", param->am3_cal_h0 % 24, param->am3_cal_m0 % 60);
    meAm3Cal0->SetTextBuf(buf);
    sprintf(buf, "%02d.%02d", param->am3_cal_h1 % 24, param->am3_cal_m1 % 60);
    meAm3Cal1->SetTextBuf(buf);


    // ������� ���������
    cbAdcSample->ItemIndex =
	(param->sample_freq == 4000) ? 6 : (param->sample_freq == 2000) ? 5 : \
	(param->sample_freq == 1000) ? 4 : (param->sample_freq == 500) ? 3 : \
	(param->sample_freq == 250)  ? 2 : (param->sample_freq == 125) ? 1 : 0;


    // ����������������
    cbAdcCons->ItemIndex = param->power_cons == 0 ? 0 : 1;

    // PGA
    cbAdcPGA->ItemIndex = param->pga_adc == 1 ? 0 :
	param->pga_adc == 2 ? 1 : param->pga_adc == 4 ? 2 : param->pga_adc == 8 ? 3 : param->pga_adc == 16 ? 4 : param->pga_adc == 32 ? 5 : 6;

    // ����� ���� � �����
    /////cbNumBytes->ItemIndex = param->num_bytes == 3 ? 0 : 1;

    // ���������� ������ ������� �� ���������
    cbChan4->Checked = (param->on_off_channels & 0x08) ? true : false;
    cbChan3->Checked = (param->on_off_channels & 0x04) ? true : false;
    cbChan2->Checked = (param->on_off_channels & 0x02) ? true : false;
    cbChan1->Checked = (param->on_off_channels & 0x01) ? true : false;


    // ������� ����� ������� - �� ������
    seFreq->Value = param->filter_freq;
    if (param->filter_freq == 0) {
	cbFreq->Checked = false;
    } else {
	cbFreq->Checked = true;
    }

    // ���������� ����������� (��/���)
///    cbConstReg->ItemIndex = (param->const_reg_flag == 0) ? 0 : 1;

    cbConstReg->Checked = (param->const_reg_flag == 0) ? false : true;


    /// memcpy(&param_struct, param, sizeof(param_struct));
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::menu10MinClick(TObject * Sender)
{
    CreateParamData(TIME_10_MIN);
    ShowParamData(&param_struct);
//    edSampleString->Text = "���� ���������� ��� 10-�� �������� ������";
    menuSave->Enabled = true;

}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::menu60MinClick(TObject * Sender)
{
    CreateParamData(TIME_60_MIN);
    ShowParamData(&param_struct);
    //    edSampleString->Text = "���� ���������� ��� ������� ������";
    menuSave->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::menu1DayClick(TObject * Sender)
{
    CreateParamData(TIME_1_DAY);
    ShowParamData(&param_struct);
//    edSampleString->Text = "���� ���������� ��� �������� ������";
    menuSave->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::menu1WeekClick(TObject * Sender)
{
    CreateParamData(TIME_1_WEEK);
    ShowParamData(&param_struct);
//    edSampleString->Text = "���� ���������� ��� ��������� ������";
    menuSave->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::menu1MonthClick(TObject * Sender)
{
    CreateParamData(TIME_1_MONTH);
    ShowParamData(&param_struct);
    //    edSampleString->Text = "���� ���������� ��� �������� ������";
    menuSave->Enabled = true;
}

//---------------------------------------------------------------------------

// ��������� �� SD �����
void __fastcall TfrmMain::menuSaveClick(TObject * Sender)
{
    SaveFileThread *thread;

    pcChangeMode->ActivePage = TabSheet2;

    thread = new SaveFileThread(false);
    thread->FreeOnTerminate = true;
}

//---------------------------------------------------------------------------
// ���� ������ �������� - 7 ������
// ���� ��� - 5
void __fastcall TfrmMain::FormResize(TObject * Sender)
{
    int w, h, d, i;
    char str[128];
    int w2;

    w = pnUp->Width;
    h = this->Height;
    d = 5;


    // 1-� �������
    if (gbCounts->Visible) {
        i =  w / 7 - d;
       	gbParams->Width = i;
       	gbTimes->Width = i;


	gbMyCounts->Width = i;
	gbCounts->Width = i;
	gbEnviron->Width = w / 7 * 3 + d;
    } else {
        i = w / 5 - d;
	gbParams->Width = i;
	gbTimes->Width = i;
	gbEnviron->Width = w / 5 * 3 + d;
    }
    i = gbTimes->Width - 75 - 2;
    lbUTCTime->Width = i;
    lbTimeGNS110->Width = i;
    lbGpsTime->Width = i;
    lbGpsLat->Width = i;
    lbGpsLon->Width = i;


    // ������ �����
    if (gbAdc->Visible) {
	gbStatus0->Width = w / 6 - 2;
	gbStatus1->Width = w / 6 - 2;
	gbStatus2->Width = w / 3 - 2;
	gbAdc->Width = w / 6 - 2;
	gbResetCause->Width = w / 6 - 2;
    } else {
	gbStatus0->Width = w / 5 - 2;
	gbStatus1->Width = w / 5 - 2;
	gbStatus2->Width = w / 5 * 2;

	gbResetCause->Width = w / 5 - 2;
    }

    // 2-� �������
    w2 = gbFileParams->Width / 10 - d;

    // 1 ���
    pnPosition->Width = w2 * 3;
    pnModemNum->Left = pnPosition->Width;

    pnStartDate->Width = w2 * 3;
    pnBurnTime->Left = pnStartDate->Width;

    pnFinishDate->Width = w2 * 3;
    pnPopupLen->Left = pnFinishDate->Width;

    pnBurnDate->Width = w2 * 3;
    pnAm3PopupDate->Left = pnBurnDate->Width;

    pnConstReg->Width = w2 * 3;
    pnAm3Cal->Left = pnConstReg->Width;

    pnDisk->Width = w2 * 3;

    pnModemNum->Width = w2 * 3;
    pnBurnTime->Width = w2 * 3;
    pnPopupLen->Width = w2 * 3;
    pnAm3PopupDate->Width = w2 * 3;
    pnAm3Cal->Width = w2 * 3;
    edSampleString->Width = pnConstReg->Width + pnAm3Cal->Width - pnComments->Width;
    pnDisk->Width =pnConstReg->Width + pnAm3Cal->Width;

    // 3 ���

    w2 = pnPosition->Width + pnModemNum->Width;
    pnAdcFreq->Left = w2;
    pnAdcEnergo->Left = w2;
    pnAdcPga->Left = w2;
    pnNumBytes->Left = w2;
    pnChannels->Left = w2;
    pnFileLen->Left = w2;
    pnFiltFreq->Left = w2;


    w2 = gbFileParams->Width - pnDisk->Width - 15;
    pnAdcFreq->Width = w2;
    pnAdcEnergo->Width = w2;
    pnAdcPga->Width = w2;
    pnNumBytes->Width = w2;
    pnChannels->Width = w2;
    pnFileLen->Width = w2;
    pnFiltFreq->Width = w2;


    // 3-� �������
    // 1-� ���
    w2 = gbModem->Width / 3 - d;
    gbModemNum->Width = w2;
    gbModemRtc->Width = w2;
    gbModemAlarm->Width = w2;
    gbRandomStr->Width = w2;
    ltModemNum->Left = w2 - ltModemNum->Width - d;
    ltModemTime->Left = w2 - ltModemTime->Width - d;
    ltAlarmTime->Left = w2 - ltAlarmTime->Width - d;
    ltModemCmd->Left = w2 - ltModemCmd->Width - d;


    // 2 ���
    gbModemLightTime->Left = w2 + d;
    gbModemPopup->Left = w2 + d;
    gbModemBurnLen->Left = w2 + d;
    gbModemWriteParams->Left = w2 + d;

    gbModemLightTime->Width = w2;
    gbModemPopup->Width = w2;
    gbModemBurnLen->Width = w2;
    gbModemWriteParams->Width = w2;

    ltCalTime->Left = w2 - ltCalTime->Width - d;
    ltTimeForRelease->Left = w2 - ltTimeForRelease->Width - d;
    ltBurnLen->Left = w2 - ltBurnLen->Width - d;
    ltApplyCommand->Left = w2 - ltApplyCommand->Width - d;


    // 3-� ���
    gbModemBurnOn->Left = w2 * 2 + d;
    gbModemLampOn->Left = w2 * 2 + d;
    gbModemRadioOn->Left = w2 * 2 + d;
    gbModemPingSend->Left = w2 * 2 + d;

    gbModemBurnOn->Width = w2;
    gbModemLampOn->Width = w2;
    gbModemRadioOn->Width = w2;
    gbModemPingSend->Width = w2;

    ltBurnCmdOnOff->Left = w2 - ltBurnCmdOnOff->Width - d;
    ltLampOnOff->Left = w2 - ltLampOnOff->Width - d;
    ltRadioOnOff->Left = w2 - ltRadioOnOff->Width - d;
    ltPing->Left = w2 - ltPing->Width - d;


    pcChangeMode->Width = w - 10;
    gbScope->Height = TabSheet1->Height - gbContr->Height - 5;


/*
    w=frmMain->Width;
    h=frmMain->Height;
    sprintf(str,"W=%d H=%d", w, h);
    memoLog->Lines->Add(str);
    */
}

//---------------------------------------------------------------------------
// ���������� ����� �������
void __fastcall TfrmMain::btnSetNameClick(TObject * Sender)
{
    frmNumber->Left = this->Left + 210;
    frmNumber->Top = this->Top + 50;
    frmNumber->ShowModal();
}

//---------------------------------------------------------------------------
// ������ �� ����� �� ���������
void __fastcall TfrmMain::FormCloseQuery(TObject * Sender, bool & CanClose)
{
    int res;

    if (!bEndThread) {
	if (lang == lang_rus)
	    res = YESNO_BOX("������ ��������� � ������������� ������! ����� �� ���������?");
	else
	    res = YESNO_BOX("Device will stay in interractive mode! Logout from the programm?");


	if (res == IDYES) {
	    bEndThread = true;
	    TerminateAllThreads();
	    CanClose = true;
	} else {
	    CanClose = false;
	}
    } else {
	CanClose = true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormDestroy(TObject * Sender)
{

    char str[128];
    sprintf(str, "GNS AirLink close");
    LogOut(str);

    CloseHandle(log_fd);
    DeleteCriticalSection(&time_cs);
}

//---------------------------------------------------------------------------
// ������� ������ �����
// ��� �������?
void __fastcall TfrmMain::btnStartThreadClick(TObject * Sender)
{
    DEV_STATUS_STRUCT status;
    bool bit;


    get_dsp_status(&status);

    bit = (status.st_main & 0x40 ? false : true);

    // ������������� ������������
    if (status.st_main & 0x10) {
	TerminateScope();
	if (lang == lang_rus)
	    WARN_BOX("������ ����������� ����������, ����������� ����������!");
	else
	    WARN_BOX("Can't run oscilloscope, Recorder ADC fault!");
	return;
    }
    // �����
    if (bit) {			// ���� �������
	TerminateScope();
    } else {

	WriteCommandThread *thread;


	// �������
	if (cbAdcFreq->ItemIndex == 4){
	    start.freq = 4000;
	} else if (cbAdcFreq->ItemIndex == 3) {
	    start.freq = 2000;
	} else if (cbAdcFreq->ItemIndex == 2) {
	    start.freq = 1000;
	} else if (cbAdcFreq->ItemIndex == 1) {
	    start.freq = 500;
	} else if (cbAdcFreq->ItemIndex == 0) {
	    start.freq = 250;
	} else {
	    start.freq = 250;
	}
	start.pga = 1 << cbPGA->ItemIndex;

	start.mode = 2;

	start.cons = cbConsum->ItemIndex;
	start.chop = cbChop->ItemIndex;

	start.float_data.fPar = seFltFreq->Value;	//   freq:  0.001 -  25.0000 - fil (DCAA)
	thread = new WriteCommandThread(StartDevice, &start, false, false);

	thread->WaitFor();
	delete thread;

	// �� ���� ����� ��� �������
	save_param.h_memo = memoLog->Height;
	save_param.h_status = pnStatus->Height;
	save_param.h_contr = gbContr->Height;
	save_param.h_mode = pcChangeMode->Height;

	pnStatus->Visible = false;
	pcChangeMode->Height = frmMain->Height - tbButtons->Height - pnUp->Height - 40;
	extern s64 ttt0;
	extern s64 ttt1;
	extern int count;
	ttt0 = get_msec_ticks();
	ttt1 = get_msec_ticks();
	count = 0;
	cbTimeLimitChange(this);
    }
}

//---------------------------------------------------------------------------
//  �������� EEPROM
void __fastcall TfrmMain::btnSetToZeroClick(TObject * Sender)
{
    WriteCommandThread *thread;
    int res;

    if (lang == lang_rus)
	res = YESNO_BOX("�������� EEPROM?");
    else
	res = YESNO_BOX("Reset EEPROM?");

    if (res == IDYES) {
	thread = new WriteCommandThread(SetTimesToZero, NULL, false, false);
	thread->WaitFor();
	delete thread;
	if (lang == lang_rus)
	    LogOut("��������� ������������ �������!");
	else
	    LogOut("Please reset the device!");
    }
}

//---------------------------------------------------------------------------
// ��������� ��������� �������
void __fastcall TfrmMain::sbRunModuleClick(TObject * Sender)
{
    String met;

    if (cbPortName->ItemIndex >= 0)
	met = cbPortName->Items[cbPortName->ItemIndex].Text;
    gns_num = frmMain->port_set[cbPortName->ItemIndex].gns_name;

    // ���� ����� �������
    if (cbPortName->ItemIndex >= 0 && bEndThread) {
	EnableControl();
	tmFind->Enabled = false;
	cbPortName->Enabled = false;
	sbRunModule->Down = true;
	GetWorkDisk(met);

	if (lang == lang_rus)
	    met = "���������� ������� " + met;
	else
	    met = "Connect to recorder " + met;
    } else if (!bEndThread) {	// ���������� �������
	bEndThread = true;
	TerminateAllThreads();
	DisableControl();
	cbPortName->Enabled = true;
	sbRunModule->Down = false;

	if (lang == lang_rus)
	    met = "��������� ������� " + met;
	else
	    met = "Disconnect from recorder " + met;

    }
    LogOut(met.c_str());
}

//---------------------------------------------------------------------------
// ����� ������
void __fastcall TfrmMain::btnModemRequestClick(TObject * Sender)
{
    ModemRequestThread *thread;

    SetModemButtons(false);
    SetModemLights(false);

    cbUpdateTime->Checked = false;
    if (lang == lang_rus)
	LogOut("������ ���������� ������...���������!");
    else
	LogOut("Request modem parameters...wait!");


    thread = new ModemRequestThread(true);
    thread->FreeOnTerminate = true;
    thread->Resume();
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnGetModemNumClick(TObject * Sender)
{
    ltModemNum->State = false;
    WriteCommandThread *thread;
    thread = new WriteCommandThread(GetModemNumber, &modem, false, true);
    thread->FreeOnTerminate = true;
    thread->Resume();
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnGetModemTimeClick(TObject * Sender)
{
    ltModemTime->State = false;
    WriteCommandThread *thread;
    thread = new WriteCommandThread(GetModemTime, &modem, false, true);
    thread->FreeOnTerminate = true;
    thread->Resume();
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnGetAlarmTimeClick(TObject * Sender)
{
    ltAlarmTime->State = false;
    WriteCommandThread *thread;
    thread = new WriteCommandThread(GetAlarmTime, &modem, false, true);
    thread->FreeOnTerminate = true;
    thread->Resume();
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnGetCalTimeClick(TObject * Sender)
{
    ltCalTime->State = false;
    WriteCommandThread *thread;
    thread = new WriteCommandThread(GetCalTime, &modem, false, true);
    thread->FreeOnTerminate = true;
    thread->Resume();
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnSetCalTimeClick(TObject * Sender)
{
    char str[128];
    int sec, msec;

    ltCalTime->State = false;
    WriteCommandThread *thread;

    // ������� ����� ����� �������
    DecodeTime(dtCalTime0->Time, modem.am3_h0_time, modem.am3_m0_time, sec, msec);
    DecodeTime(dtCalTime1->Time, modem.am3_h1_time, modem.am3_m1_time, sec, msec);

    thread = new WriteCommandThread(SetCalTime, &modem, true, true);
    thread->FreeOnTerminate = true;
    thread->Resume();
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnGetTimeForReleaseClick(TObject * Sender)
{
    WriteCommandThread *thread;

    ltTimeForRelease->State = false;
    thread = new WriteCommandThread(GetTimeForRelease, &modem, false, true);
    thread->FreeOnTerminate = true;
    thread->Resume();
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnSetTimeForReleaseClick(TObject * Sender)
{
    char str[128];
    WriteCommandThread *thread;

    ltTimeForRelease->State = false;
    meTimeForRelease->GetTextBuf(str, 4);
    modem.time_for_release = atoi(str);

    thread = new WriteCommandThread(SetTimeForRelease, &modem, true, true);
    thread->FreeOnTerminate = true;
    thread->Resume();
}


//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnGetBurnLenClick(TObject * Sender)
{
    ltBurnLen->State = false;
    WriteCommandThread *thread;
    thread = new WriteCommandThread(GetBurnLen, &modem, false, true);
    thread->FreeOnTerminate = true;
    thread->Resume();
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnSetBurnLenClick(TObject * Sender)
{
    char str[128];
    WriteCommandThread *thread;

    ltBurnLen->State = false;
    meBurnLen->GetTextBuf(str, 3);
    modem.burn_len = StrToInt(str);
    thread = new WriteCommandThread(SetBurnLen, &modem, true, true);
    thread->FreeOnTerminate = true;
    thread->Resume();
}

//---------------------------------------------------------------------------
 // ����� ������
void __fastcall TfrmMain::btnSetModemTimeClick(TObject * Sender)
{
    char str[128];

    ltModemTime->State = false;
    WriteCommandThread *thread;

    DecodeDate(dtModemDate->Date, modem.modem_time.wYear, modem.modem_time.wMonth, modem.modem_time.wDay);
    DecodeTime(dtModemTime->Time, modem.modem_time.wHour, modem.modem_time.wMinute, modem.modem_time.wSecond, modem.modem_time.wMilliseconds);

    thread = new WriteCommandThread(SetModemTime, &modem, true, true);
    thread->FreeOnTerminate = true;
    thread->Resume();
}

//---------------------------------------------------------------------------
// ���������� ����� ������
void __fastcall TfrmMain::btnSetModemNumClick(TObject * Sender)
{
    static u16 num;
    char str[128];

    // ����� ������
    meModemNum->GetTextBuf(str, 5);
    modem.modem_num = StrToInt(str);
    sprintf(str, "Set modem number %d", modem.modem_num);
    LogOut(str);

    ltModemNum->State = false;
    WriteCommandThread *thread;
    thread = new WriteCommandThread(SetModemNumber, &modem, true, true);
    thread->FreeOnTerminate = true;
    thread->Resume();
}

//---------------------------------------------------------------------------
// ������/�������� ����� � ������� ����� ������
void __fastcall TfrmMain::ShowModemNum(u16 num)
{
    char str[128];

    if (num != 0xffff) {
	ltModemNum->State = true;
	meModemNum->Text = IntToStr(num);
	sprintf(str, "Set modem number %d OK", num);
    } else {
	ltModemNum->State = false;
	meModemNum->Text = IntToStr(0);
	sprintf(str, "Set modem number %d Fail", num);
    }
    LogOut(str);
}

//---------------------------------------------------------------------------
// ������/�������� ����� � ������� ����� ������
void __fastcall TfrmMain::ShowModemTime(SYSTEMTIME * st)
{
    char str[128];

    // ����� ������
    if (st != NULL && st->wYear != 0) {
	TDateTime dt = SystemTimeToDateTime(*st);

	dtModemDate->Date = dt;
	dtModemTime->Time = dt;
	ltModemTime->State = true;
	sprintf(str, "Get/Set Modem time OK: %02d.%02d.%04d - %02d.%02d.%02d", st->wDay, st->wMonth, st->wYear, st->wHour, st->wMinute, st->wSecond);
    } else {
	sprintf(str, "Get/Set Modem time Fail");
    }
    LogOut(str);
}

//---------------------------------------------------------------------------
// ������/�������� ����� � ������� ����� ���������� ��������
void __fastcall TfrmMain::ShowAlarmTime(SYSTEMTIME * st)
{
    char str[128];

    // ����� ������
    if (st != NULL && st->wYear != 0) {
	TDateTime dt = SystemTimeToDateTime(*st);
	dtAlarmDate->Date = dt;
	dtAlarmTime->Time = dt;
	ltAlarmTime->State = true;
	sprintf(str, "Get/Set Alarm time OK: %02d.%02d.%04d - %02d.%02d.%02d", st->wDay, st->wMonth, st->wYear, st->wHour, st->wMinute, st->wSecond);
    } else {
	sprintf(str, "Get/Set ModemTime Fail");
    }
    LogOut(str);
}

//---------------------------------------------------------------------------
// ������/�������� ����� � ������� ����������� ����� (������� ����� �����)
void __fastcall TfrmMain::ShowCalTime(u16 h0, u16 m0, u16 h1, u16 m1)
{
    char str[128];
    SYSTEMTIME st;

    // ����������� �����
    if (h0 != -1 && m0 != -1 && h1 != -1 && m1 != -1) {
	GetSystemTime(&st);	// ����� �� ���� ������

	st.wHour = h0;
	st.wMinute = m0;
	dtCalTime0->Time = SystemTimeToDateTime(st);

	st.wHour = h1;
	st.wMinute = m1;
	dtCalTime1->Time = SystemTimeToDateTime(st);
	sprintf(str, "Get/Set calendar time OK: %02d:%02d-%02d:%02d", h0, m0, h1, m1);
	ltCalTime->State = true;
    } else {
	sprintf(str, "Get/Set calendar time Fail");
    }
    LogOut(str);
}

//---------------------------------------------------------------------------
// ������/�������� ����� � ������� ����� �� ��������
void __fastcall TfrmMain::ShowTimeForRelease(int len)
{
    char str[128];

    if (len != -1) {
	ltTimeForRelease->State = true;
	udTimeForRelease->Position = len;
	sprintf(str, "Get/Set time for release: %d min OK", len);
    } else {
	sprintf(str, "Get/Set time for release Fail");
    }
    LogOut(str);
}

//---------------------------------------------------------------------------
// ������/�������� ����� � ������� ������������ ��������
void __fastcall TfrmMain::ShowBurnLen(int len)
{
    char str[128];

    if (len != -1) {
	ltBurnLen->State = true;
	meBurnLen->Text = IntToStr(len);
	sprintf(str, "Get/Set burn len: %d sec OK", len);
    } else {
	sprintf(str, "Get/Set  burn len: %d sec Fail");
    }
    LogOut(str);
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnSetAlarmTimeClick(TObject * Sender)
{
    char str[128];

    ltAlarmTime->State = false;
    WriteCommandThread *thread;

    DecodeDate(dtAlarmDate->Date, modem.alarm_time.wYear, modem.alarm_time.wMonth, modem.alarm_time.wDay);
    DecodeTime(dtAlarmTime->Time, modem.alarm_time.wHour, modem.alarm_time.wMinute, modem.alarm_time.wSecond, modem.alarm_time.wMilliseconds);

    thread = new WriteCommandThread(SetAlarmTime, &modem, true, false);
    thread->FreeOnTerminate = true;
}

//---------------------------------------------------------------------------
s64 __fastcall TfrmMain::GetBigTimer(void)
{
    return big_timer;
}

//---------------------------------------------------------------------------
// ������ �������� ����� UTC
void __fastcall TfrmMain::timIdleTimer(TObject * Sender)
{
    // ��� � �������
    if (big_timer % 10 == 0)
	TimeUTC();

    big_timer++;
}

//---------------------------------------------------------------------------
// ������� ��� ��������� � �����
void __fastcall TfrmMain::GetModemParameters(void)
{
    char str[128];
    u16 sec, msec;

    // ����� ������
    meModemNum->GetTextBuf(str, 5);
    modem.modem_num = StrToInt(str);


    // ����� ������
    DecodeDate(dtModemDate->Date, modem.modem_time.wYear, modem.modem_time.wMonth, modem.modem_time.wDay);
    DecodeTime(dtModemTime->Time, modem.modem_time.wHour, modem.modem_time.wMinute, modem.modem_time.wSecond, modem.modem_time.wMilliseconds);

    // ��������� �����
    DecodeDate(dtAlarmDate->Date, modem.alarm_time.wYear, modem.alarm_time.wMonth, modem.alarm_time.wDay);
    DecodeTime(dtAlarmTime->Time, modem.alarm_time.wHour, modem.alarm_time.wMinute, modem.alarm_time.wSecond, modem.alarm_time.wMilliseconds);


    // ������� ����� ����� �������
    DecodeTime(dtCalTime0->Time, modem.am3_h0_time, modem.am3_m0_time, sec, msec);
    DecodeTime(dtCalTime1->Time, modem.am3_h1_time, modem.am3_m1_time, sec, msec);

    // ����� ��������
    meTimeForRelease->GetTextBuf(str, 4);
    modem.time_for_release = atoi(str);

    // ����� ��������
    meBurnLen->GetTextBuf(str, 3);
    modem.burn_len = StrToInt(str);

}

//---------------------------------------------------------------------------
// ���� ���������
void __fastcall TfrmMain::btnStopClick(TObject * Sender)
{
    TerminateScope();
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnModemCommandClick(TObject * Sender)
{
    GetModemParameters();
    SetModemButtons(false);
    SetModemLights(false);

    ModemCommandThread *thread;
    cbUpdateTime->Checked = false;
    if (lang == lang_rus)
	LogOut("������ ���������� � �����...���������!");
    else
	LogOut("Write parameters to modem...wait!");

    thread = new ModemCommandThread(&modem, true);
    thread->FreeOnTerminate = true;
    thread->Resume();
}

//---------------------------------------------------------------------------
// ������� � ����� ����� �������
void __fastcall TfrmMain::btnModemAnyStringClick(TObject * Sender)
{
    char str[128];
    int i;

    // ������� ������� �� ������
    // ������ ���������� � $ � ������������� *
    // ����������� ����� �������� ���������� �������
    edAnyCommand->GetTextBuf(str, 127);

    SendAnyCommand(str);
}

//---------------------------------------------------------------------------
// ������� ���� ����������
void __fastcall TfrmMain::menuOpenClick(TObject * Sender)
{
    OpenFileThread *thread;
    String name;

    // ��������� ����������
    odParamFile->InitialDir = String(dcbDisk->Drive) + ":";

    pcChangeMode->ActivePage = TabSheet2;


    // ����� ������ ������ �� �������
    if (odParamFile->Execute() == false)
	return;


    if (!FileExists(odParamFile->FileName))
	return;

    name = odParamFile->FileName;

    // �������� ����� � ���������� suspended
    //����� ����� ����� ��������� �� ������ FreeOnTerminate
    thread = new OpenFileThread(name, true);
    thread->FreeOnTerminate = true;
    thread->Resume();

    String data = ExtractFileDrive(name);
    dcbDisk->Drive = (data.c_str())[0];
}

//---------------------------------------------------------------------------
// �������� GPS / ��������� GPS
void __fastcall TfrmMain::btnGpsOnClick(TObject * Sender)
{
    WriteCommandThread *thread;
    DEV_STATUS_STRUCT status;
    bool bit;

    get_dsp_status(&status);

    bit = (status.ports & RELE_GPS_BIT ? true : false);

    // ���� �����
    if (bit) {
	thread = new WriteCommandThread(GpsOff, NULL, false, false);
    } else {
	thread = new WriteCommandThread(GpsOn, NULL, false, false);
    }

    thread->WaitFor();
    delete thread;
///        PageControl1->Height = frmMain->Height - Panel2->Height - tbButtons->Height - pnUp->Height - 128;
}

//---------------------------------------------------------------------------
// ��� ������ ������ ��� ��� ����
void __fastcall TfrmMain::ButtonStateInStart(bool state)
{
    //  btnSync->Enabled = state;
//    btnTest->Enabled = state;
    enable_measure = !state;	// ���� ���� ����������
    cbTimeLimitChange(this);
}

//---------------------------------------------------------------------------

// ���������� ���������
// ������������� ���������� � ������ �����
void __fastcall TfrmMain::TerminateScope(void)
{
    if (run_ok && enable_measure) {
	WriteCommandThread *thread;
	thread = new WriteCommandThread(StopDevice, NULL, false, false);
	thread->WaitFor();
	delete thread;
	Sleep(50);
	thread = new WriteCommandThread(ClearBuf, NULL, false, false);
	thread->WaitFor();
	delete thread;

	memoLog->Height = save_param.h_memo;
	pnStatus->Height = save_param.h_status;
	gbContr->Height = save_param.h_contr;
	pcChangeMode->Height = save_param.h_mode;

	if (lang == lang_rus)
	    slsDisplay->Title->Text = "���";
	else
	    slsDisplay->Title->Text = "ADC";

	pnStatus->Visible = true;

    }
}

//---------------------------------------------------------------------------
// �������� �����-����� ���������� ��������!
void __fastcall TfrmMain::sbInfoDblClick(TObject * Sender)
{
    memoLog->Clear();
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::UnhideButtons(void)
{
    btnBurn->Enabled = true;

    btnSync->Enabled = true;
    btnTest->Enabled = true;
    btnModemOnOff->Enabled = true;
    btnModemRequest->Enabled = true;
    btnModemCommand->Enabled = true;
    btnGpsOn->Enabled = true;
    btnStartThread->Enabled = true;
    btnConst->Enabled = true;
    btnSetName->Enabled = true;
    btnSetToZero->Enabled = true;
    btnResetWorkTime->Enabled = true;
    test_run = false;
    enable_log = true;		// ����� ������
}

//---------------------------------------------------------------------------
// ����� �������
void __fastcall TfrmMain::tmFindTimer(TObject * Sender)
{
    if (get_num_station() > 0) {
	tmFind->Enabled = false;
	sbRunModule->Enabled = true;	// ������������ ������ ������������
    } else {
	if (!no_enter()) {	// ������ ������
	    sbRunModule->Enabled = false;
	    sbRunModule->Down = false;
	    FindStationsThread *thread = new FindStationsThread(false);
	    thread->FreeOnTerminate = true;
	}
    }
}

//---------------------------------------------------------------------------
// ���������� ��������� �����
void __fastcall TfrmMain::CMShowLink(TMessage & Message)
{
    XCHG_ERR_COUNT *in, *all;
    int t0;
    static int t1 = 0;
    static struct {
	int last;
	int now;
    } err = {
    0, 0};

    t0 = get_sec_ticks() / 10;	// �������� ����� �� 10 ������

    in = (XCHG_ERR_COUNT *) Message.WParam;
    all = (XCHG_ERR_COUNT *) Message.LParam;

    pbLinkQuality->Max = in->tx_ok + in->rx_err;
    pbLinkQuality->Position = in->tx_ok;
    pbLinkQuality->Brush->Color = clRed;
    SendMessage(pbLinkQuality->Handle, PBM_SETBARCOLOR, 0, clLime);

    pnXchgOkMy->Caption = IntToStr(all->tx_ok);
    pnXchgErrMy->Caption = IntToStr(all->rx_err);

    if (bEndThread) {
	pnXchgOkMy->Caption = "";
	pnXchgErrMy->Caption = "";
	pbLinkQuality->Visible = false;
    }

    if (t0 != t1 && in->rx_err) {
	t1 = t0;
	err.now = all->rx_err - err.last;
	err.last = err.now;

	if (err.now) {
	    char buf[128];
	    if (lang == lang_rus)
		sprintf(buf, "������ � ������ (%d) �� ��������� 10 ������", err.now);
	    else
		sprintf(buf, "Exchange errors (%d) for last 10 sec", err.now);
	    LogOut(buf);
	}
    }
}

//---------------------------------------------------------------------------
// ���� ��� ������ ���� ������� �������� - ������� ��!
void __fastcall TfrmMain::ShowStatusIfChange(void *v, u8 show)
{
    DEV_STATUS_STRUCT *status;
    u8 b0, b1, b2, b4;

    enable_log = true;
    UnhideButtons();

    if (v != NULL) {
	char str[128];
	status = (DEV_STATUS_STRUCT *) v;

	// ����� ��������� � ���?
	if (status->quartz == 8192000) {
	    quartz_freq = 8.192;
	    if (lang == lang_rus)
		lbStatus2_4->Caption = "������ ���������� 8.192 ���";
	    else
		lbStatus2_4->Caption = "Generator 8.192 MHz error";

	    lbStatus2_5->Visible = false;
	} else {
	    quartz_freq = 19.2;
	    if (lang == lang_rus)
		lbStatus2_4->Caption = "������ ���������� 19.2 ���";
	    else
		lbStatus2_4->Caption = "Generator 19.2 MHz error";

	    lbStatus2_5->Visible = true;
	}


	// ������� ����������, ��������� � ����
	sprintf(str, "%2.3f", quartz_freq);

	pnQuartzFreq->Caption = str;

	if (status->cclk) {
	    sprintf(str, "%3d", status->cclk);
	    pnCclk->Caption = str;
	} else {
	    pnCclk->Caption = "192";
	}



	if (status->sclk) {
	    sprintf(str, "%3d", status->sclk);
	    pnSclk->Caption = str;
	} else {
	    pnSclk->Caption = "48";
	}


	// ������� ������
	if (show & 0x01) {
	    b0 = status->st_main;

	    //------------- �����
	    if (b0 & 0x01) {
		if (lang == lang_rus)
		    LogOut("��� ������� RTC!");
		else
		    LogOut("RTC time is not setup!");
	    } else {
		if (lang == lang_rus)
		    LogOut("����� RTC OK!");
		else
		    LogOut("RTC time OK!");
	    }


	    //------------- ������ � �������. ������ ������ ������!
	    if (b0 & 0x04) {
		if (lang == lang_rus)
		    LogOut("������ � �������!");
		else
		    LogOut("Command error!");
	    }
	    //------------- ������������ ���!
	    if (b0 & 16) {
		if (lang == lang_rus)
		    LogOut("������������� ��� ������������!");
		else
		    LogOut("Recorder ADC fault!");
	    }
	    //------------- ������������ ������! ������ ������
	    if (b0 & 0x20) {
		if (lang == lang_rus)
		    LogOut("������������ ������!");
		else
		    LogOut("Memory overflow!");
	    }
	    //------------- ���
	    if (!(b0 & 0x40)) {
		if (lang == lang_rus)
		    LogOut("���������� �������!");
		else
		    LogOut("Oscilloscope is on!");
	    } else {
		if (lang == lang_rus)
		    LogOut("���������� ��������!");
		else
		    LogOut("Oscilloscope is off!");
	    }
	}
	// ����������������
	if (show & 0x02) {
	    b1 = status->st_test0;

	    //------------- RTC
	    if (b1 & 0x01) {
		if (lang == lang_rus)
		    LogOut("������ RTC, ��� ������ � RTC ��� ���� �������!");
		else
		    LogOut("RTC error, no data from RTC or RTC delays!");
	    } else {
		LogOut("RTC OK!");
	    }

	    //------------- ������ ��������
	    if (b1 & 0x02) {
		if (lang == lang_rus)
		    LogOut("������ ������� ��������, ��� ������ � ������� ��������!");
		else
		    LogOut("Pressure sensor error, no data from sensor!");
	    } else {
		if (lang == lang_rus)
		    LogOut("������ �������� OK!");
		else
		    LogOut("Pressure sensor OK!");
	    }

	    //------------- ������
	    if (b1 & 0x04) {
		if (lang == lang_rus)
		    LogOut("������ �������������!");
		else
		    LogOut("Accelerometer error!");
	    } else {
		if (lang == lang_rus)
		    LogOut("������������ OK!");
		else
		    LogOut("Accelerometer OK!");
	    }

	    //------------- �����
	    if (b1 & 0x08) {
		if (lang == lang_rus)
		    LogOut("������ �������!");
		else
		    LogOut("Compass error!");
	    } else {
		if (lang == lang_rus)
		    LogOut("������ OK!");
		else
		    LogOut("Compass OK!");
	    }


	    //------------- GPS
	    if (b1 & 0x10) {
		if (lang == lang_rus)
		    LogOut("������ ������ GPS, ��� ������ GPS �� ������������: ��� ������ NMEA!");
		else
		    LogOut("GPS module error: no NMEA string!");

	    } else {
		LogOut("GPS OK!");
	    }


	    //------------- EEPROM
	    if (b1 & 0x20) {
		if (lang == lang_rus)
		    LogOut("������ EEPROM!");
		else
		    LogOut("EEPROM error!");
	    } else {
		LogOut("EEPROM OK!");
	    }


	    //------------- ����� SD
	    if (b1 & 0x40) {
		if (lang == lang_rus)
		    LogOut("������ SD �����, ��������� �������� ������� �� SD �����!");
		else
		    LogOut("SD card error, check filesystem on SD!");
	    } else {
		if (lang == lang_rus)
		    LogOut("SD ����� OK!");
		else
		    LogOut("SD card OK!");
	    }

	    //------------- Flash
	    if (b1 & 0x80) {
		if (lang == lang_rus)
		    LogOut("������ FLASH!");
		else
		    LogOut("FLASH error!");
	    } else {
		LogOut("FLASH OK!");
	    }
	}
//----------
	// ����������
	if (show & 0x04) {
	    b2 = status->st_test1;


	    //------------- ������ � eeprom
	    if (b2 & 0x08) {
		if (lang == lang_rus)
		    LogOut("�� ��������� ������ � EEPROM!");
		else
		    LogOut("EEPROM data is not correct!");

	    } else {
		if (lang == lang_rus)
		    LogOut("������ � EEPROM OK!");
		else
		    LogOut("EEPROM data OK!");
	    }



	    //------------- 19.2
	    if (b2 & 0x10) {
		LogOut("������ ���������� 19.2 ���: ��������� �� ��������������!");
	    } else {
		LogOut("��������� 19.2 ��� ��!");
	    }


	    //------------- 4,096
	    if (b2 & 0x20) {
		LogOut("������ ���������� 4.096 ���: ��������� �� ��������������!!");
	    } else {
		LogOut("��������� 4.096 ��� ��!");
	    }


	    //------------- PPS
	    if (b2 & 0x40) {
		LogOut("��� ��������� PPS �� �����!");
	    } else {
		LogOut("�������� PPS �� ����� OK!");
	    }

	    //------------- TIM3
	    if (b2 & 0x80) {
		LogOut("������ ������� 3!");
	    } else {
		LogOut("������3 OK!");
	    }
	}
	if (show & 8) {
	    b4 = status->st_reset;
	    String s;
	    if (lang == lang_rus) {
		s = "������� ����������� ������: ";

		if (b4 & 1)
		    s += "���������� �������";
		else if (b4 & 2)
		    s += "������� �����";
		else if (b4 & 4)
		    s += "�������� �������";
		else if (b4 & 8)
		    s += "WDT �����";
		else if (b4 & 16)
		    s += "���������� ��������� ����� (> 10 ���)";
		else if (b4 & 32)
		    s += "�������������� �����";
	    } else {
		s = "Last disconnection reason: ";

		if (b4 & 1)
		    s += "Power Off";
		else if (b4 & 2)
		    s += "External reset";
		else if (b4 & 4)
		    s += "Brown out detect";
		else if (b4 & 8)
		    s += "WDT reset";
		else if (b4 & 16)
		    s += "Long absence of communication (> 10 min)";
		else if (b4 & 32)
		    s += "Emergency reset";

	    }


	    LogOut(s.c_str());
	}
	if (lang == lang_rus)
	    LogOut("������������ ���������!");
	else
	    LogOut("SelfTest finished!");
    }
}

//---------------------------------------------------------------------------
// ������� ������!
void __fastcall TfrmMain::ShowStatus(void *v)
{
    char str[128];
    u8 byte;
    static int i = 0, t1;
    static bool tb = false, tm = false, tp = false;
    int t0, ttt;
    s16 t, volt, amp;
    double p, r, h, T;
    SYSTEMTIME st;
    DEV_STATUS_STRUCT *status;

    t0 = time(NULL);

    if (v != NULL) {
	status = (DEV_STATUS_STRUCT *) v;
	byte = status->st_main;

////////////////////////////////////////////////////////////////////////////////
//              ������� c����c-0 ����
////////////////////////////////////////////////////////////////////////////////
	if (byte & 1) {
	    lbStatus0_0->Font->Color = clRed;
	} else {
	    lbStatus0_0->Font->Color = clGray;
	}
	// ������ ������
	if (byte & 2) {
	    if (first_run)
		lbStatus0_1->Font->Color = clGray;
	    else
		lbStatus0_1->Font->Color = clRed;
	} else {
	    lbStatus0_1->Font->Color = clGray;
	}

	if (byte & 4) {
	    lbStatus0_2->Font->Color = clRed;
	} else {
	    lbStatus0_2->Font->Color = clGray;
	}

	if (byte & 8) {
	    lbStatus0_3->Font->Color = clRed;
	} else {
	    lbStatus0_3->Font->Color = clGray;
	}

	// GNS ����������
	if (byte & 16) {
	    lbStatus0_4->Font->Color = clRed;
	} else {
	    lbStatus0_4->Font->Color = clGray;
	}

	// ������������ ������
	if (byte & 32) {
	    lbStatus0_5->Font->Color = clRed;
	} else {
	    lbStatus0_5->Font->Color = clGray;
	}

	// GNS ������� �� ����� ���������
	if (!(byte & 0x40)) {
	    lbStatus0_6->Font->Color = clGreen;
	    btnStartThread->ImageIndex = 6;
	    ButtonStateInStart(false);
	} else {
	    lbStatus0_6->Font->Color = clGray;
	    btnStartThread->ImageIndex = 5;
	    ButtonStateInStart(true);
	}

	// ���� ���������������� - ������
	if (byte & 128) {
	    // ������� ��������
	    if (t0 % 2 == 0) {
		lbStatus0_7->Font->Color = clGray;
	    } else {
		lbStatus0_7->Font->Color = clGreen;
	    }
	    test_result.t0 = 1;
	    test_result.tick++;
	} else {
	    lbStatus0_7->Font->Color = clGray;
	    test_result.t0 = 0;
	    enable_log = true;
	}

	// ���� ������
	if (test_result.tick > 0 && test_result.t0 == 0) {
	    test_result.tick = 0;
	    ShowStatusIfChange(status, 1 + 2 + 3);
	}
////////////////////////////////////////////////////////////////////////////////
//              ���������������� 0
////////////////////////////////////////////////////////////////////////////////
	byte = status->st_test0;

	// RTC
	if (byte & 1) {
	    lbStatus1_0->Font->Color = clRed;
	} else {
	    lbStatus1_0->Font->Color = clGray;
	}
	// P & T
	if (byte & 2) {
	    lbStatus1_1->Font->Color = clRed;
	} else {
	    lbStatus1_1->Font->Color = clGray;
	}

	// ������ + �������������
	if (byte & 4) {
	    lbStatus1_2->Font->Color = clRed;
	} else {
	    lbStatus1_2->Font->Color = clGray;
	}

	// ������ ������ ������ � ������ �������
	if (byte & 8) {
	    lbStatus1_3->Font->Color = clRed;
	} else {
	    lbStatus1_3->Font->Color = clGray;
	}

	if (byte & 16) {
	    lbStatus1_4->Font->Color = clRed;
	} else {
	    lbStatus1_4->Font->Color = clGray;
	}

	if (byte & 32) {
	    lbStatus1_5->Font->Color = clRed;
	} else {
	    lbStatus1_5->Font->Color = clGray;
	}

	if (byte & 64) {
	    lbStatus1_6->Font->Color = clRed;
	} else {
	    lbStatus1_6->Font->Color = clGray;
	}

	if (byte & 128) {
	    lbStatus1_7->Font->Color = clRed;
	} else {
	    lbStatus1_7->Font->Color = clGray;
	}
////////////////////////////////////////////////////////////////////////////////
//      ������ ����������
////////////////////////////////////////////////////////////////////////////////
	byte = status->st_test1;
	if (byte & 0x01) {	// GPS ������� / ��������
	    lbStatus2_0->Font->Color = clGreen;
	} else {
	    if (t0 % 4 == 0) {
		frmMain->lbGpsTime->Caption = "";
		frmMain->lbGpsLat->Caption = "";
		frmMain->lbGpsLon->Caption = "";
	    }
	    lbStatus2_0->Font->Color = clGray;
	}


	if (byte & 0x02) {	// ����� ������� / ��������
	    lbStatus2_1->Font->Color = clGreen;
	} else {
	    lbStatus2_1->Font->Color = clGray;
	    SetModemLights(false);
	}

	if (byte & 0x04) {	// ���� ���� ������
	    lbStatus2_2->Font->Color = clGreen;
	    test_modem.t0 = 1;
	    test_modem.tick++;
	} else {
	    test_modem.t0 = 0;
	    lbStatus2_2->Font->Color = clGray;
	}

	// ���� ������ ������
	if (test_modem.tick && test_modem.t0 == 0) {
	    test_modem.tick = 0;
	    ShowTestModem(status);
	}
	// ���� EEPROM
	if (byte & 0x08) {
	    lbStatus2_3->Font->Color = clRed;
	} else {
	    lbStatus2_3->Font->Color = clGray;
	}

	if (!first_run) {	// � ������ �������� �� ����������
	    // ���. 19 ���
	    if (byte & 0x10) {
		lbStatus2_4->Font->Color = clRed;
	    } else {
		lbStatus2_4->Font->Color = clGray;
	    }

	    // ���. 4 ���
	    if (byte & 0x20) {
		lbStatus2_5->Font->Color = clRed;
	    } else {
		lbStatus2_5->Font->Color = clGray;
	    }

	    // Timer 4
	    if (byte & 0x40) {
		lbStatus2_6->Font->Color = clRed;
	    } else {
		lbStatus2_6->Font->Color = clGray;
	    }
	    // Timer 3
	    if (byte & 0x80) {
		lbStatus2_7->Font->Color = clRed;
	    } else {
		lbStatus2_7->Font->Color = clGray;
	    }
	}
////////////////////////////////////////////////////////////////////////////////
//                      ���
////////////////////////////////////////////////////////////////////////////////
	byte = status->st_adc;
	if (byte & 0x01)
	    ltAdc1->State = false;
	else
	    ltAdc1->State = true;

	if (byte & 0x02)
	    ltAdc2->State = false;
	else
	    ltAdc2->State = true;

	if (byte & 0x04)
	    ltAdc3->State = false;
	else
	    ltAdc3->State = true;

	if (byte & 0x08)
	    ltAdc4->State = false;
	else
	    ltAdc4->State = true;

///////////////////////// ���������� ���� � ����������
	byte = status->ports;

	if (byte & 0x01) {	//GPS �������
	    //     lbRele0->Font->Color = clGreen;
	    btnGpsOn->ImageIndex = 17;

	    if (lang == lang_rus)
		btnGpsOn->Hint = "������ GPS ���������";
	    else
		btnGpsOn->Hint = "GPS OFF";

	} else {
	    //           lbRele0->Font->Color = clGray;
	    btnGpsOn->ImageIndex = 16;

	    if (lang == lang_rus)
		btnGpsOn->Hint = "������ GPS ��������";
	    else
		btnGpsOn->Hint = "GPS ON";

	}

	if (status->st_test1 & 0x4) {	// ���� ������������
	    btnModemOnOff->Enabled = false;
	} else if (pcChangeMode->TabIndex != 1) {
	    btnModemOnOff->Enabled = true;
	    if (byte & 0x02) {	//�����
		lbRele1->Font->Color = clGreen;	// �������
		btnModemOnOff->ImageIndex = 8;

		if (lang == lang_rus)
		    btnModemOnOff->Hint = "����� ���������";
		else
		    btnModemOnOff->Hint = "Modem OFF";

	    } else {
		lbRele1->Font->Color = clGray;	//��������
		btnModemOnOff->ImageIndex = 7;

		if (lang == lang_rus)
		    btnModemOnOff->Hint = "����� ��������";
		else
		    btnModemOnOff->Hint = "Modem ON";

	    }
	}
	// �������
	if (byte & 0x04) {	// �������
	    if (t0 % 2 == 0)
		lbRele2->Font->Color = clRed;
	    else
		lbRele2->Font->Color = clGray;

	    btnBurn->ImageIndex = 9;

	    if (lang == lang_rus)
		btnBurn->Hint = "��������� �������!";
	    else
		btnBurn->Hint = "Burning wire voltage OFF";

	} else {
	    lbRele2->Font->Color = clGray;
	    btnBurn->ImageIndex = 10;

	    if (lang == lang_rus)
		btnBurn->Hint = "�������� �������!";
	    else
		btnBurn->Hint = "Burning wire voltage ON";

	}

	if (byte & 0x08) {	// ���������� �������
	    lbRele3->Font->Color = clGreen;
	} else {
	    lbRele3->Font->Color = clGray;
	}

	if (byte & 0x10) {	// �������� �� COM
	    lbRele4->Font->Color = clGreen;
	} else {
	    lbRele4->Font->Color = clGray;
	}

	if (byte & 0x20) {	// �������� �� �����
	    lbRele5->Font->Color = clGreen;
	} else {
	    lbRele5->Font->Color = clGray;
	}

	if (byte & 0x40) {	// USB
	    lbRele6->Font->Color = clGreen;
	} else {
	    lbRele6->Font->Color = clGray;
	}

	if (byte & 0x80) {	// WUSB
	    lbRele7->Font->Color = clGreen;
	} else {
	    lbRele7->Font->Color = clGray;
	}
	// �����
	byte = status->st_reset;

	// ������� c����c-0 ����
	if (byte) {
	    if (byte == 1) {
		lbStatusReset_0->Font->Color = clBlue;
	    } else if (byte == 2) {
		lbStatusReset_1->Font->Color = clBlue;
	    } else if (byte == 4) {
		lbStatusReset_2->Font->Color = clRed;
	    } else if (byte == 8) {
		lbStatusReset_3->Font->Color = clRed;
	    } else if (byte == 16) {
		lbStatusReset_4->Font->Color = clRed;
	    } else if (byte == 32) {
		lbStatusReset_5->Font->Color = clRed;
	    }
	} else {
	    lbStatusReset_0->Font->Color = clGray;
	    lbStatusReset_1->Font->Color = clGray;
	    lbStatusReset_2->Font->Color = clGray;
	    lbStatusReset_3->Font->Color = clGray;
	    lbStatusReset_4->Font->Color = clGray;
	    lbStatusReset_5->Font->Color = clGray;
	}

	if (cbUpdateTime->Checked) {
	    GetSystemTime(&st);
	    dtModemTime->Time = SystemTimeToDateTime(st);
	    dtModemDate->Date = SystemTimeToDateTime(st);
	}
	// U �������-���� � ���� �� 20% (�� 12 �����)
	volt = status->regpwr_volt;
	pnSupplyV->Caption = FloatToStrF(volt / 1000.0, ffFixed, 5, 1);
	if (volt < 7500 && !bEndThread && t0 != t1) {
	    pnSupplyV->Color = clRed;
	    pnSupplyV->Font->Color = clYellow;
	    if (t1 % 60 == 0) {
		if (lang == lang_rus)
		    LogOut("��������! ���������� ������� ����� 7.5 �!");
		else
		    LogOut("Warning! Power supply voltage is less than 7.5 V!");
	    }
	} else if (volt > 16000 && !bEndThread && t0 != t1) {
	    pnSupplyV->Color = clRed;
	    pnSupplyV->Font->Color = clYellow;
	    if (t1 % 60 == 0) {
		if (lang == lang_rus)
		    LogOut("��������! ���������� ������� ����� 15.0 �!");
		else
		    LogOut("Warning! Power supply voltage is more than 15.0 V!");
	    }
	} else {
	    pnSupplyV->Color = clBtnFace;
	    pnSupplyV->Font->Color = clWindowText;
	}

	amp = status->ireg_sense;	// I �������
	pnSupplyA->Caption = IntToStr(amp);

	// U burn-���� � ���� �� 30% (�� 12 �����) - ����� ���� ���!
	volt = status->burn_volt;
	pnBurnV->Caption = FloatToStrF((float) volt / 1000.0, ffFixed, 5, 1);
	if (volt < 8500 && !bEndThread && t0 != t1) {
	    pnBurnV->Color = clRed;
	    pnBurnV->Font->Color = clYellow;

	    if (tb == false) {
		if (lang == lang_rus)
		    LogOut("��������! ���������� �������� ����� 8.5 �!");
		else
		    LogOut("Warning! Burn wire voltage is less than 8.5 V!");
		tb = true;
	    }
	} else if (volt > 16000 && !bEndThread && t0 != t1) {
	    pnBurnV->Color = clRed;
	    pnBurnV->Font->Color = clYellow;

	    if (tb == false) {
		if (lang == lang_rus)
		    LogOut("��������! ���������� �������� ����� 16.0 �!");
		else
		    LogOut("Warning! Burn wire voltage is more than 16.0 V!");
		tb = true;
	    }
	} else {
	    pnBurnV->Color = clBtnFace;
	    pnBurnV->Font->Color = clWindowText;

	    if (volt > 10000 && volt < 18000 & tb == true) {
		if (lang == lang_rus)
		    LogOut("���������� �������� � �����!");
		else
		    LogOut("Burn wire voltage is normal!");
		tb = false;
	    }
	}


	amp = status->iburn_sense;	// I burn
	if (volt < 4000 || t0 != t1 || /*abs */ (amp) <= 3) {	//�� ���������� ���� < 4� (����������)
	    pnBurnA->Caption = "0";
	} else {
	    pnBurnA->Caption = IntToStr(amp);
	}

	// ���� ����� ����� > 7
	if (port_set[cbPortName->ItemIndex].board == 'B' || port_set[cbPortName->ItemIndex].board == 'C') {
	    volt = status->am_power_volt;
	    if (volt < 7000 && !bEndThread && t0 != t1) {
		pnModemV->Caption = FloatToStrF((float) volt / 1000.0, ffFixed, 5, 1);
		pnModemV->Color = clRed;
		pnModemV->Font->Color = clYellow;

		if (tm == false) {
		    if (lang == lang_rus)
			LogOut("��������! ���������� ������� ������������� ������ ����� 7.0 �!");
		    else
			LogOut("Warning! Modem power supply voltage is less than 7.0 V!");
		    tm = true;
		}

	    } else if (volt > 16000 && !bEndThread && t0 != t1) {
		pnModemV->Caption = FloatToStrF((float) volt / 1000.0, ffFixed, 5, 1);
		pnModemV->Color = clRed;
		pnModemV->Font->Color = clYellow;
		if (lang == lang_rus)
		    LogOut("��������! ���������� ������� ������������� ������ ����� 14.0 �!");
		else
		    LogOut("Warning! Modem power supply voltage is more than 14.0 V!");

	    } else {
		pnModemV->Caption = FloatToStrF((float) volt / 1000.0, ffFixed, 5, 1);
		pnModemV->Color = clBtnFace;
		pnModemV->Font->Color = clWindowText;

		if (volt > 7000 && volt < 16000 & tm == true) {
		    if (lang == lang_rus)
			LogOut("���������� ������� ������������� ������ � �����!");
		    else
			LogOut("Modem power supply voltage is normal!");
		    tm = false;
		}
	    }
	} else {
	    pnModemV->Caption = "0";
	    pnModemV->Font->Color = clWindowText;
	}

	amp = status->iam_sense;
	if (abs(amp) > 3)
	    pnModemA->Caption = IntToStr(amp);
	else
	    pnModemA->Caption = +"0";

	volt = status->burn_ext_volt;

	// ������� ��������
	if (fabs(volt) > 2000.0) {
	    if (t0 % 2 == 0) {
		pnBurnExtV->Color = clRed;
		pnBurnExtV->Font->Color = clYellow;
	    } else {
		pnBurnExtV->Color = clBtnFace;
		pnBurnExtV->Font->Color = clWindowText;
	    }
	} else {
	    pnBurnExtV->Color = clBtnFace;
	    pnBurnExtV->Font->Color = clWindowText;
	}
	// ������� �������
	pnBurnExtV->Caption = FloatToStrF((float) volt / 1000.0, ffFixed, 5, 1);

	// ����������� 1
	pnTemp1->Caption = FloatToStrF(status->temper1 / 10.0, ffFixed, 3, 1);

	// ��������
	pnPressure->Caption = FloatToStrF(status->press / 1000.0, ffFixed, 5, 1);


//////////////////////////////////////////////////////////////////////////////////////////
//                      ���� � ����������� 0
//////////////////////////////////////////////////////////////////////////////////////////
	p = status->pitch / 10.0;
	r = status->roll / 10.0;
	h = status->head / 10.0;
	T = status->temper0 / 10.0;

	// ������ �������
	if (status->st_test0 & 0x08) {
	    pnPitch->Caption = "n/a";
	    pnRoll->Caption = "n/a";
	    pnTemp0->Caption = "n/a";	// ����������� 0
	    pnHead->Caption = "n/a";

	    if (t0 != t1) {
		pnPitch->Color = clRed;
		pnPitch->Font->Color = clYellow;
		pnRoll->Color = clRed;
		pnRoll->Font->Color = clYellow;
		pnHead->Color = clRed;
		pnHead->Font->Color = clYellow;
		pnTemp0->Color = clRed;
		pnTemp0->Font->Color = clYellow;
	    } else {
		pnPitch->Color = clBtnFace;
		pnPitch->Font->Color = clWindowText;
		pnRoll->Color = clBtnFace;
		pnRoll->Font->Color = clWindowText;
		pnHead->Color = clBtnFace;
		pnHead->Font->Color = clWindowText;
		pnTemp0->Color = clBtnFace;
		pnTemp0->Font->Color = clWindowText;
	    }
	} else {
	    pnPitch->Caption = FloatToStrF(p, ffFixed, 3, 1);
	    if (fabs(p) > 15.0) {
		if (t0 % 2 == 0) {
		    pnPitch->Color = clRed;
		    pnPitch->Font->Color = clYellow;
		} else {
		    pnPitch->Color = clBtnFace;
		    pnPitch->Font->Color = clWindowText;
		}
	    } else {
		pnPitch->Color = clBtnFace;
		pnPitch->Font->Color = clWindowText;
	    }

	    pnRoll->Caption = FloatToStrF(r, ffFixed, 3, 1);
	    if (fabs(r) > 15.0) {
		if (t0 % 2 == 0) {
		    pnRoll->Color = clRed;
		    pnRoll->Font->Color = clYellow;
		} else {
		    pnRoll->Color = clBtnFace;
		    pnRoll->Font->Color = clWindowText;
		}
	    } else {
		pnRoll->Color = clBtnFace;
		pnRoll->Font->Color = clWindowText;
	    }

	    pnHead->Caption = FloatToStrF(h, ffFixed, 3, 1);
	    pnHead->Color = clBtnFace;
	    pnHead->Font->Color = clWindowText;

	    pnTemp0->Caption = FloatToStrF(T, ffFixed, 3, 1);	// ����������� 0
	    pnTemp0->Color = clBtnFace;
	    pnTemp0->Font->Color = clWindowText;

	}

	// ����� � ���� ��� � ������
	if (t0 % 60 == 0 && t0 != t1)
	    WriteDataToFile(status);


	// �������, � ����� �� ������ ������ ���������
	// 1 - ����������
	// 2 - ����� ���������
	// 3 - ����� �������
	// 4 - ����� ������������ ��� ������������ ������
	if (!(status->st_main & 0x80)) {	// ���� ���� ������������
	    int ind = pcChangeMode->TabIndex;
	    if (ind == 0) {
		OscilMenu(this);
	    } else if (ind == 1) {
		OperMenu(this);
		TerminateScope();
	    } else if (ind == 2) {
		CtrlMenu(this);
		TerminateScope();
	    }
	} else {
	    TestMenu(this);
	    TerminateScope();
	}

	// 1 - ����� ��������
	// 2 - ����� ������� + ���� ������
	// 3 - ����� ������� - ���� ������
	if (status->st_test1 & 0x02) {
	    if (!(status->st_test1 & 0x04)) {	// ��� ����� � ��� ������
		SetModemButtons(true);

		if (!(status->st_main & 0x02))
		    SetModemLights(true);
	    } else {
		SetModemButtons(false);
		SetModemLights(false);
	    }
	} else {
	    SetModemButtons(false);
	    SetModemLights(false);
	}


	if (t0 != t1) {
#if !defined		GNS110_PROJECT
	    TimeGNS110(status->gns_rtc);	/* ����� RTC ������� */
#endif
	}


	i++;
	t1 = t0;


    } else {			// ������� ���
	SetModemButtons(false);
	SetModemLights(false);

	pnSupplyV->Color = clBtnFace;
	pnSupplyV->Font->Color = clWindowText;
	pnBurnV->Color = clBtnFace;
	pnBurnV->Font->Color = clWindowText;
	pnBurnExtV->Color = clBtnFace;
	pnBurnExtV->Font->Color = clWindowText;
	pnModemV->Color = clBtnFace;
	pnModemV->Font->Color = clWindowText;
	pnPitch->Color = clBtnFace;
	pnPitch->Font->Color = clWindowText;
	pnRoll->Color = clBtnFace;
	pnRoll->Font->Color = clWindowText;


	lbStatus0_0->Font->Color = clGray;
	lbStatus0_1->Font->Color = clGray;
	lbStatus0_2->Font->Color = clGray;
	lbStatus0_3->Font->Color = clGray;
	lbStatus0_4->Font->Color = clGray;
	lbStatus0_5->Font->Color = clGray;
	lbStatus0_6->Font->Color = clGray;
	lbStatus0_7->Font->Color = clGray;

	// ����������������
	lbStatus1_0->Font->Color = clGray;
	lbStatus1_1->Font->Color = clGray;
	lbStatus1_2->Font->Color = clGray;
	lbStatus1_3->Font->Color = clGray;
	lbStatus1_4->Font->Color = clGray;
	lbStatus1_5->Font->Color = clGray;
	lbStatus1_6->Font->Color = clGray;
	lbStatus1_7->Font->Color = clGray;

	// ������ ����������
	lbStatus2_0->Font->Color = clGray;
	lbStatus2_1->Font->Color = clGray;
	lbStatus2_2->Font->Color = clGray;
	lbStatus2_3->Font->Color = clGray;
	lbStatus2_4->Font->Color = clGray;
	lbStatus2_5->Font->Color = clGray;
	lbStatus2_6->Font->Color = clGray;
	lbStatus2_7->Font->Color = clGray;


	lbRele0->Font->Color = clGray;
	lbRele1->Font->Color = clGray;
	lbRele2->Font->Color = clGray;
	lbRele3->Font->Color = clGray;
	lbRele4->Font->Color = clGray;
	lbRele5->Font->Color = clGray;
	lbRele6->Font->Color = clGray;
	lbRele7->Font->Color = clGray;


	// ������� ������
	lbStatusReset_0->Font->Color = clGray;
	lbStatusReset_1->Font->Color = clGray;
	lbStatusReset_2->Font->Color = clGray;
	lbStatusReset_3->Font->Color = clGray;
	lbStatusReset_4->Font->Color = clGray;
	lbStatusReset_5->Font->Color = clGray;

	// ������+����� ������+����� GNS
	lbTimeGNS110->Caption = "";

	if (lang == lang_rus)
	    sbInfo->Panels->Items[1]->Text = "����� ������ � ������� ������";
	else
	    sbInfo->Panels->Items[1]->Text = "Working time for the current connection";

	// �����
	pnSupplyV->Caption = "";
	pnSupplyV->Color = clBtnFace;
	pnSupplyV->Font->Color = clWindowText;

	pnSupplyA->Caption = "";
	pnSupplyA->Color = clBtnFace;
	pnSupplyA->Font->Color = clWindowText;

	pnBurnV->Caption = "";
	pnBurnV->Color = clBtnFace;
	pnBurnV->Font->Color = clWindowText;

	pnBurnA->Caption = "";
	pnBurnA->Color = clBtnFace;
	pnBurnA->Font->Color = clWindowText;

	pnModemV->Caption = "";
	pnModemV->Color = clBtnFace;
	pnModemV->Font->Color = clWindowText;

	pnModemA->Caption = "";
	pnModemA->Color = clBtnFace;
	pnModemA->Font->Color = clWindowText;

	pnBurnExtV->Caption = "";
	pnBurnExtV->Color = clBtnFace;
	pnBurnExtV->Font->Color = clWindowText;

	pnTemp1->Caption = "";
	pnTemp1->Color = clBtnFace;
	pnTemp1->Font->Color = clWindowText;

	pnTemp0->Caption = "";
	pnTemp0->Color = clBtnFace;
	pnTemp0->Font->Color = clWindowText;

	pnPressure->Caption = "";
	pnPressure->Color = clBtnFace;
	pnPressure->Font->Color = clWindowText;

	pnPitch->Caption = "";
	pnPitch->Color = clBtnFace;
	pnPitch->Font->Color = clWindowText;


	pnQuartzFreq->Caption = "";
	pnQuartzFreq->Color = clBtnFace;
	pnQuartzFreq->Font->Color = clWindowText;


	pnSclk->Caption = "";
	pnSclk->Color = clBtnFace;
	pnSclk->Font->Color = clWindowText;

	pnCclk->Caption = "";
	pnCclk->Color = clBtnFace;
	pnCclk->Font->Color = clWindowText;

	pnRoll->Caption = "";
	pnRoll->Color = clBtnFace;
	pnRoll->Font->Color = clWindowText;


	pnHead->Caption = "";
	pnHead->Color = clBtnFace;
	pnHead->Font->Color = clWindowText;

	// ����������
/*
	btnBurn->Hint = "������� ���/����";
	btnModemOnOff->Hint = "����� ���/����";
	btnGpsOn->Hint = "������ GPS ���/����";
	btnStartThread->Hint = "�����/���� ���������";
*/
    }
}

//---------------------------------------------------------------------------
// �������� ������ � ����
void __fastcall TfrmMain::WriteDataToFile(void *v)
{
    char str[128];
    DEV_STATUS_STRUCT *status;

    if (log_fd != INVALID_HANDLE_VALUE && v != NULL) {
	status = (DEV_STATUS_STRUCT *) v;
	sprintf(str, "U pow %2.3f, V\tI q %d mA\tU burn %2.3f V\tI burn %d mA\tU ext %2.3f V\tU mod %2.3f V\tI mod %d mA\r\n",
		status->regpwr_volt / 1000.0,
		status->ireg_sense, status->burn_volt / 1000.0, status->iburn_sense, status->burn_ext_volt / 1000.0, status->am_power_volt / 1000.0,
		status->iam_sense);

	LogOut(str);
    }
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::ShowWorkTime(void *v)
{
    char str[128];
    DEV_WORK_TIME_STRUCT *wt;
    int h, m;

    if (v != NULL) {
	wt = (DEV_WORK_TIME_STRUCT *) v;

	m = ((u32) wt->time_work / 60) % 60;
	h = ((u32) wt->time_work / 3600) % 999;
	sprintf(str, "%03d:%02d", h, m);

	if (lang == lang_rus)
	    sbInfo->Panels->Items[2]->Text = "��������� (��:��)   " + String(str);
	else
	    sbInfo->Panels->Items[2]->Text = "Acqusition (hh:mm)   " + String(str);

	m = ((u32) wt->time_cmd / 60) % 60;
	h = ((u32) wt->time_cmd / 3600) % 999;
	sprintf(str, "%03d:%02d", h, m);
	if (lang == lang_rus)
	    sbInfo->Panels->Items[3]->Text = "����� PC (��:��)   " + String(str);
	else
	    sbInfo->Panels->Items[3]->Text = "PC mode (hh:mm)   " + String(str);

	m = ((u32) wt->time_modem / 60) % 60;
	h = ((u32) wt->time_modem / 3600) % 999;
	sprintf(str, "%03d:%02d", h, m);
	if (lang == lang_rus)
	    sbInfo->Panels->Items[4]->Text = "����� (��:��)   " + String(str);
	else
	    sbInfo->Panels->Items[4]->Text = "Modem (hh:mm)   " + String(str);

    } else {
	if (lang == lang_rus) {
	    sbInfo->Panels->Items[2]->Text = "��������� (��:��)";
	    sbInfo->Panels->Items[3]->Text = "����� PC (��:��)";
	    sbInfo->Panels->Items[4]->Text = "����� (��:��)";
	} else {
	    sbInfo->Panels->Items[2]->Text = "Acqusition (hh:mm)";
	    sbInfo->Panels->Items[3]->Text = "PC mode (hh:mm)";
	    sbInfo->Panels->Items[4]->Text = "Modem (hh:mm)";
	}
    }
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::ShowPortCounts(void *v)
{
    char str[128];
    PORT_COUNT_STRUCT *cnt, my_count;

    PortGetXchgCounts(&my_count);	//�������� ����� ������
    pnRxPackMy->Caption = IntToStr(my_count.rx_pack);
    pnRxCmdErrMy->Caption = IntToStr(my_count.rx_cmd_err);
    pnTxPackMy->Caption = IntToStr(my_count.tx_pack);


    if (v != NULL) {
	cnt = (PORT_COUNT_STRUCT *) v;

	pnRxPack->Caption = IntToStr(cnt->rx_pack);
	pnRxCmdErr->Caption = IntToStr(cnt->rx_cmd_err);
	pnRxStatErr->Caption = IntToStr(cnt->rx_stat_err);
	pnTxPack->Caption = IntToStr(cnt->tx_pack);
	pnRxCrcErr->Caption = IntToStr(cnt->rx_crc_err);
	curr_time = time(NULL);
	curr_time = curr_time - start_time;

	sec_to_simple_str(curr_time, str);

	if (lang == lang_rus)
	    sbInfo->Panels->Items[1]->Text = "����� ������ � ������� ������: " + String(str);
	else
	    sbInfo->Panels->Items[1]->Text = "Working time for the current connection: " + String(str);

	pbLinkQuality->Visible = true;

    } else {			// ������� ���
	pnRxPack->Caption = "";
	pnRxCmdErr->Caption = "";
	pnRxStatErr->Caption = "";
	pnTxPack->Caption = "";
	pnRxCrcErr->Caption = "";

	pnRxPackMy->Caption = "";
	pnRxCmdErrMy->Caption = "";
	pnXchgErrMy->Caption = "";
	pnTxPackMy->Caption = "";
	pnXchgOkMy->Caption = "";
    }

    if (frmMain->bEndThread) {
	pnXchgOkMy->Caption = "";
	pnXchgErrMy->Caption = "";
	pbLinkQuality->Visible = false;
    }
}

////////////////////////////////////////////////////////////////////////////////
//           �������, ���������� �� ��������� SendMessage,PostMessage
////////////////////////////////////////////////////////////////////////////////
// ������� �������� ������ ���� � gns110
// �������� ����� �����������
void __fastcall TfrmMain::CMShowPortCounts(TMessage & Message)
{
    ShowPortCounts((void *) Message.WParam);
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::CMShowParamData(TMessage & Message)
{
    ShowParamData((void *) Message.WParam);
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::CMShowWorkTime(TMessage & Message)
{
    ShowWorkTime((void *) Message.WParam);
}

//---------------------------------------------------------------------------
// ��������� ��������� � ������������ ������
void __fastcall TfrmMain::CMShowStatus(TMessage & Message)
{
    ShowStatus((void *) Message.WParam);
}

//---------------------------------------------------------------------------
// ��� ������ - ��������� �� ��������� ������
void __fastcall TfrmMain::CMNoData(TMessage & Message)
{
    // ����, ��� ���� ��������
    bEndThread = true;
    TerminateAllThreads();
    DisableControl();
}

//---------------------------------------------------------------------------
// �������� ��� ��������� ������
void __fastcall TfrmMain::cbFreqClick(TObject * Sender)
{
    if (cbFreq->Checked == false) {
	seFreq->Value = 0;
	seFreq->Enabled = false;
	pnFiltFreq->Font->Color = clInactiveCaption;
    } else {
	seFreq->Enabled = true;
	pnFiltFreq->Font->Color = clWindowText;
    }
}

//---------------------------------------------------------------------------
// ������� ����� ����� - ��������� ������������ ����� ��� �������
void __fastcall TfrmMain::meAm3Cal0Change(TObject * Sender)
{
    char str[32];
    char buf[8];
    short h, m;


    meAm3Cal0->GetTextBuf(str, 6);

    memcpy(buf, str, 3);
    buf[2] = 0;
    h = atoi(buf);
    if (h > 24) {
	h = 0;
    }

    memcpy(buf, str + 3, 3);
    buf[2] = 0;
    m = atoi(buf);
    if (m > 59) {
	m = 0;
    }

    sprintf(str, "%02d:%02d", h, m);
    meAm3Cal0->Text = str;
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::meAm3Cal1Change(TObject * Sender)
{
    char str[32];
    char buf[8];
    short h, m;

    meAm3Cal1->GetTextBuf(str, 6);

    memcpy(buf, str, 3);
    buf[2] = 0;
    h = atoi(buf);
    if (h > 24) {
	h = 0;
    }

    memcpy(buf, str + 3, 3);
    buf[2] = 0;
    m = atoi(buf);
    if (m > 59) {
	m = 0;
    }

    sprintf(str, "%02d:%02d", h, m);
    meAm3Cal1->Text = str;
}

//---------------------------------------------------------------------------
// �������� ����� ������ �� ������
void __fastcall TfrmMain::edModemNumExit(TObject * Sender)
{
    char buf[32];
    int i;

    edModemNum->GetTextBuf(buf, 5);
    i = StrToInt(String(buf));

    udModemNum->Position = i;
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::cbConstRegClick(TObject * Sender)
{
    if (cbConstReg->Checked == false) {
	pnConstReg->Font->Color = clInactiveCaption;
	pnFinishDate->Font->Color = clWindowText;
	dtFinishDate->Enabled = true;
	dtFinishTime->Enabled = true;
    } else {
	pnConstReg->Font->Color = clWindowText;
	pnFinishDate->Font->Color = clInactiveCaption;
	dtFinishDate->Enabled = false;
	dtFinishTime->Enabled = false;
    }
}

//---------------------------------------------------------------------------
// ���������� ����� ������
void __fastcall TfrmMain::cbModemNumClick(TObject * Sender)
{
    // ��� ������
    if (cbModemNum->ItemIndex == 0) {
	dtAm3PopupDate->Enabled = false;
	dtAm3PopupTime->Enabled = false;
	meAm3Cal0->Enabled = false;
	meAm3Cal1->Enabled = false;
	pnModemNum->Font->Color = clInactiveCaption;
	pnAm3PopupDate->Font->Color = clInactiveCaption;
	pnAm3Cal->Font->Color = clInactiveCaption;
	udModemNum->Enabled = false;
	edModemNum->Enabled = false;
	cbChangeModemName->Enabled = false;
    } else {
	edModemNum->Enabled = true;
	udModemNum->Enabled = true;
	dtAm3PopupDate->Enabled = true;
	dtAm3PopupTime->Enabled = true;
	cbChangeModemName->Enabled = true;
	meAm3Cal0->Enabled = true;
	meAm3Cal1->Enabled = true;
	pnModemNum->Font->Color = clWindowText;
	pnAm3PopupDate->Font->Color = clWindowText;
	pnAm3Cal->Font->Color = clWindowText;
    }
    cbChangeModemNameClick(this);
}

//---------------------------------------------------------------------------
bool __fastcall TfrmMain::VolumeIsFat(String disk)
{
    bool res = false;
    char VName[255];
    u32 VolumeSerialNumber;
    u32 MaximumComponentLength;
    u32 FileSystemFlags;
    char FSName[255];

    disk += "\\";

    do {
	if (GetVolumeInformation(disk.c_str(), VName, 255, NULL, 0, 0, FSName, 255) == false)
	    break;

            // �������� ������ ��� ����� ��������
	if ((strcmpi(FSName, "FAT32") != 0) && (strcmpi(FSName, "ExFAT") !=0 ))
	  	  break;

	res = true;
    } while (0);
    return res;
}

//---------------------------------------------------------------------------
// �������� ����� ������� �� ���
void __fastcall TfrmMain::meTimeForReleaseChange(TObject * Sender)
{
    char buf[32];
    int i;
    bool res = true;

    meTimeForRelease->GetTextBuf(buf, 5);

    for (i = 0; i < strlen(buf); i++) {
	if (!(isdigit(buf[i]))) {
	    buf[i] = '0';
	    res = false;
	}
    }
    if (res == false)

	meTimeForRelease->Text = buf;
}

//---------------------------------------------------------------------------
// �������� ������������ ��������
void __fastcall TfrmMain::meBurnLenChange(TObject * Sender)
{
    char buf[32];
    int i;
    bool res = true;

    meBurnLen->GetTextBuf(buf, 3);

    for (i = 0; i < strlen(buf); i++) {
	if (!(isdigit(buf[i]))) {
	    buf[i] = '0';
	    res = false;
	}
    }
    if (res == false)
	meBurnLen->Text = buf;
}

//---------------------------------------------------------------------------
// �������� ������������ ��������   - 4 �����
void __fastcall TfrmMain::edBurnTimeChange(TObject * Sender)
{
    char buf[32];
    int i;
    bool res = true;

    edBurnTime->GetTextBuf(buf, 5);

    for (i = 0; i < strlen(buf); i++) {
	if (!(isdigit(buf[i]))) {
	    buf[i] = '0';
	    res = false;
	}
    }
    if (res == false)
	edBurnTime->Text = buf;
}

//---------------------------------------------------------------------------
// ������������ ��������
void __fastcall TfrmMain::mePopupLenChange(TObject * Sender)
{
    char buf[32];
    int i;
    bool res = true;

    mePopupLen->GetTextBuf(buf, 5);

    for (i = 0; i < strlen(buf); i++) {
	if (!(isdigit(buf[i]))) {
	    buf[i] = '0';
	    res = false;
	}
    }
    if (res == false)
	mePopupLen->Text = buf;
}

//---------------------------------------------------------------------------
// ����� ������
void __fastcall TfrmMain::edModemNumChange(TObject * Sender)
{
    char buf[32];
    int i;
    bool res = true;

    edModemNum->GetTextBuf(buf, 5);

    for (i = 0; i < strlen(buf); i++) {
	if (!(isdigit(buf[i]))) {
	    buf[i] = '0';
	    res = false;
	}
    }
    if (res == false)
	edModemNum->Text = buf;
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::edBurnTimeExit(TObject * Sender)
{
    char buf[32];
    int i;

    edBurnTime->GetTextBuf(buf, 5);
    i = StrToInt(String(buf));

    udBurnTime->Position = i;
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::mePopupLenExit(TObject * Sender)
{
    char buf[32];
    int i;

    mePopupLen->GetTextBuf(buf, 5);
    i = StrToInt(String(buf));

    udPopupLen->Position = i;
}

//---------------------------------------------------------------------------
// ������� ���������
void __fastcall TfrmMain::edPositionChange(TObject * Sender)
{
    char buf[32];
    int i;
    bool res = true;

    edPosition->GetTextBuf(buf, 5);

    for (i = 0; i < strlen(buf); i++) {
	if (!(isdigit(buf[i]))) {
	    buf[i] = '0';
	    res = false;
	}
    }
    if (res == false)
	edPosition->Text = buf;
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::Splitter1Moved(TObject * Sender)
{
    frmMain->Resize();
}

//---------------------------------------------------------------------------
// �������� �����
void __fastcall TfrmMain::btnRadioOnClick(TObject * Sender)
{
    ltRadioOnOff->State = false;
    WriteCommandThread *thread;

    if (modem_inner_state.radio) {
	thread = new WriteCommandThread(RadioOff, &modem, false, true);
	btnRadioOn->Kind = bkRetry;
	if (lang == lang_rus)
	    btnRadioOn->Caption = "���";
	else
	    btnRadioOn->Caption = "On";
    } else {
	thread = new WriteCommandThread(RadioOn, &modem, false, true);
	btnRadioOn->Kind = bkAbort;
	if (lang == lang_rus)
	    btnRadioOn->Caption = "����";
	else
	    btnRadioOn->Caption = "Off";

    }

    modem_inner_state.radio = !modem_inner_state.radio;
    thread->FreeOnTerminate = true;
    thread->Resume();
}

//---------------------------------------------------------------------------
// �������� �����
void __fastcall TfrmMain::btnLampOnClick(TObject * Sender)
{
    ltLampOnOff->State = false;
    WriteCommandThread *thread;

    if (modem_inner_state.lamp) {	// ��������
	thread = new WriteCommandThread(LampOff, &modem, false, true);
	btnLampOn->Kind = bkRetry;
	if (lang == lang_rus)
	    btnLampOn->Caption = "���";
	else
	    btnLampOn->Caption = "On";
    } else {
	thread = new WriteCommandThread(LampOn, &modem, false, true);
	btnLampOn->Kind = bkAbort;

	if (lang == lang_rus)
	    btnLampOn->Caption = "����";
	else
	    btnLampOn->Caption = "Off";

    }
    modem_inner_state.lamp = !modem_inner_state.lamp;
    thread->FreeOnTerminate = true;
    thread->Resume();
}

//---------------------------------------------------------------------------
//������� ��� / ����
void __fastcall TfrmMain::btnBurnCmdOnClick(TObject * Sender)
{
    ltBurnCmdOnOff->State = false;
    WriteCommandThread *thread;

    if (modem_inner_state.burn) {	// ���� �������� - ���������
	thread = new WriteCommandThread(BurnCmdOff, &modem, false, true);
	btnBurnCmdOn->Kind = bkRetry;
	if (lang == lang_rus)
	    btnBurnCmdOn->Caption = "���";
	else
	    btnBurnCmdOn->Caption = "On";
    } else {			// ��������
	thread = new WriteCommandThread(BurnCmdOn, &modem, false, true);
	btnBurnCmdOn->Kind = bkAbort;
	if (lang == lang_rus)
	    btnBurnCmdOn->Caption = "����";
	else
	    btnBurnCmdOn->Caption = "Off";

    }
    modem_inner_state.burn = !modem_inner_state.burn;
    thread->FreeOnTerminate = true;
    thread->Resume();
}

//---------------------------------------------------------------------------
// ������� ����:  ���� 13  ���� 9 ���� 11
void __fastcall TfrmMain::btnPing11Click(TObject * Sender)
{
    void *fptr[] = { SendPing9, SendPing11, SendPing13 };
    static int num = udPingCount->Position;
    int i;
    WriteCommandThread *thread;

    i = cbPingFreq->ItemIndex;
    if (i < 0 || i > 2)
	return;

    ltPing->State = false;

    thread = new WriteCommandThread(fptr[i], &num, false, true);
    thread->FreeOnTerminate = true;
    thread->Resume();
}

//---------------------------------------------------------------------------
//  �������� ����� ������
void __fastcall TfrmMain::btnResetWorkTimeClick(TObject * Sender)
{
    WriteCommandThread *thread;
    thread = new WriteCommandThread(SetWorkTime, NULL, false, false);
    thread->WaitFor();
    delete thread;
    big_timer = 500;
}

//---------------------------------------------------------------------------
// �� ���������� �������������� ���������
void __fastcall TfrmMain::menuStandardClick(TObject * Sender)
{
    gbAdc->Visible = false;
    gbCounts->Visible = false;
    gbMyCounts->Visible = false;
    frmMain->FormResize(this);

    cbConstReg->Checked = false;
    cbConstReg->Enabled = false;
}

//---------------------------------------------------------------------------
// �������� �������������� ���������
void __fastcall TfrmMain::menuAdvancedClick(TObject * Sender)
{
    gbAdc->Visible = true;
    gbCounts->Visible = true;
    gbMyCounts->Visible = true;
    frmMain->FormResize(this);
    cbConstReg->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::cbChangeModemNameClick(TObject * Sender)
{
    static int save_num = 0;

    if (cbChangeModemName->Checked && cbModemNum->ItemIndex == 2) {
	save_num = udModemNum->Position;
	udModemNum->Position = 0;
	edModemNum->Enabled = false;
	udModemNum->Enabled = false;
    } else if (cbModemNum->ItemIndex != 0) {
	udModemNum->Position = save_num;
	edModemNum->Enabled = true;
	udModemNum->Enabled = true;
    }
}

//---------------------------------------------------------------------------
// ������� ����
void __fastcall TfrmMain::menuOpenLogsClick(TObject * Sender)
{
    String name;

    // �����������, ��� ����������� ���-�����
    odOpenLogs->InitialDir = ExtractFilePath(Application->ExeName) + "LOGS";

    // ����� ������ ������ �� �������
    if (odOpenLogs->Execute() == false)
	return;

    if (!FileExists(odOpenLogs->FileName))
	return;

    name = odOpenLogs->FileName;
    ShellExecute(this->Handle, "open", "notepad.exe", name.c_str(), NULL, SW_SHOWNORMAL);
}

//---------------------------------------------------------------------------
// ���������� ������� ����������/���� ��� ��������
void __fastcall TfrmMain::GetWorkDisk(String met)
{
    bool res = false;
    u32 VolumeSerialNumber;
    u32 MaximumComponentLength;
    u32 FileSystemFlags;
    char disk;
    char fs_name_str[255];
    char drv_name_str[255];
    int i;
    u32 type;
    char *drives[] = { "C:\\", "D:\\", "E:\\", "F:\\", "G:\\", "H:\\", "I:\\", "J:\\", "K:\\", "L:\\",
	"M:\\", "N:\\", "O:\\", "P:\\", "Q:\\", "R:\\", "S:\\", "T:\\", "U:\\", " V:\\",
	"W:\\", "X:\\", "Y:\\", "Z:\\"
    };

    // ���������� ��� �����
    for (i = 0; i < sizeof(drives) / sizeof(drives[0]); i++) {
	type = GetDriveType(drives[i]);
	if (type == DRIVE_REMOVABLE) {
	    res = GetVolumeInformation(drives[i], drv_name_str, 255, NULL, 0, 0, fs_name_str, 255);

	    if (res == false) {
		DWORD dwRC;
		DWORD dwError;
		char *lpMsgBuf;
		char str[1024];
		dwError = GetLastError();

		// ���� "���������� �� ������ - �� ������ � ���!"
		if (dwError != ERROR_NOT_READY) {
		    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
				  NULL, dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) & lpMsgBuf, 0, NULL);
		    sprintf(str, "DISK: %s. %s", drives[i], lpMsgBuf);
		    ERROR_BOX(str);
		    LogOut(str);
		}
	    } else {
		// ���� ����� ���� ���������
		if (strncmp(drv_name_str, met.c_str(), 7) == 0) {
		    // �� ������ ����� ����� ����
		    memcpy(&disk, drives[i], 1);
		    dcbDisk->TextCase = dcbDisk->TextCase;
		    dcbDisk->Drive = disk;
		    odParamFile->InitialDir = drives[i];
		    sdParamFile->InitialDir = drives[i];
		    sprintf(drv_name_str, "Disk %c: attached on %s", disk, met.c_str());
		    LogOut(drv_name_str);

#if 0
		    // �������� ����� � ���������� suspended
		    //����� ����� ����� ��������� �� ������ FreeOnTerminate
		    String name = String(drives[i]) + "recparam.cfg";
		    OpenFileThread *thread = new OpenFileThread(name, true);
		    thread->FreeOnTerminate = true;
		    thread->Resume();
#endif
		}
	    }
	}
    }
}

//---------------------------------------------------------------------------
// ������ � ������ �����������
void __fastcall TfrmMain::OscilMenu(TObject * Sender)
{
    btnReset->Enabled = true;	// ����� ������
    btnPowerOff->Enabled = true;	// ���� ������
    btnStartThread->Enabled = true;	// ����� / ���� ������

    // ��� ���������-����
    btnTest->Enabled = false;
    btnModemOnOff->Enabled = false;
    btnModemRequest->Enabled = false;
    btnModemCommand->Enabled = false;
    btnBurn->Enabled = false;
    btnGpsOn->Enabled = false;
    btnSync->Enabled = false;
    btnConst->Enabled = false;
    btnSetName->Enabled = false;
    btnSetToZero->Enabled = false;
    btnResetWorkTime->Enabled = false;
}

//---------------------------------------------------------------------------
// ������ � ������ ���������
void __fastcall TfrmMain::OperMenu(TObject * Sender)
{
    btnReset->Enabled = true;	// ����� ������
    btnPowerOff->Enabled = true;	// ���� ������
    btnTest->Enabled = true;	// ������������ ������
    btnSync->Enabled = true;	// ������������� ������

    // ��� ���������-����
    btnModemOnOff->Enabled = false;
    btnModemRequest->Enabled = false;
    btnModemCommand->Enabled = false;
    btnBurn->Enabled = false;
    btnGpsOn->Enabled = false;
    btnStartThread->Enabled = false;
    btnConst->Enabled = false;
    btnSetName->Enabled = false;
    btnSetToZero->Enabled = false;
    btnResetWorkTime->Enabled = false;
}

//---------------------------------------------------------------------------
// ������ � ������ �������
void __fastcall TfrmMain::CtrlMenu(TObject * Sender)
{
    // ��� ������, �� ����������� �����
    btnReset->Enabled = true;	// ����� ������
    btnPowerOff->Enabled = true;	// ���� ������
    btnTest->Enabled = true;	// ������������ ������
    btnSync->Enabled = true;	// ������������� ������
    btnModemOnOff->Enabled = true;
    btnModemRequest->Enabled = true;
    btnModemCommand->Enabled = true;
    btnBurn->Enabled = true;
    btnGpsOn->Enabled = true;
    btnConst->Enabled = true;
    btnSetName->Enabled = true;
    btnSetToZero->Enabled = true;
    btnResetWorkTime->Enabled = true;
    btnStartThread->Enabled = false;
}

//---------------------------------------------------------------------------
// ��� ������ ���������
void __fastcall TfrmMain::OffMenu(TObject * Sender)
{
    btnReset->Enabled = false;
    btnPowerOff->Enabled = false;
    btnTest->Enabled = false;
    btnModemOnOff->Enabled = false;
    btnModemRequest->Enabled = false;
    btnModemCommand->Enabled = false;
    btnBurn->Enabled = false;
    btnGpsOn->Enabled = false;
    btnStartThread->Enabled = false;
    btnSync->Enabled = false;
    btnConst->Enabled = false;
    btnSetName->Enabled = false;
    btnSetToZero->Enabled = false;
    btnResetWorkTime->Enabled = false;
}

//---------------------------------------------------------------------------
// ������������
void __fastcall TfrmMain::TestMenu(TObject * Sender)
{
    btnReset->Enabled = true;	// ����� ������
    btnPowerOff->Enabled = true;	// ���� ������

    btnTest->Enabled = false;
    btnModemOnOff->Enabled = false;
    btnModemRequest->Enabled = false;
    btnModemCommand->Enabled = false;
    btnBurn->Enabled = false;
    btnGpsOn->Enabled = false;
    btnStartThread->Enabled = false;
    btnSync->Enabled = false;
    btnConst->Enabled = false;
    btnSetName->Enabled = false;
    btnSetToZero->Enabled = false;
    btnResetWorkTime->Enabled = false;

    test_run = true;
    enable_log = false;		// ������ ������
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::DisableControl(void)
{
    run_ok = false;
    reset_num_station();
    cbPortName->Items->Clear();
    lbTimeGNS110->Caption = "";
    cbAdcFreq->ItemIndex = 0;
    cbPGA->ItemIndex = 0;
    seFltFreq->Value = 0;

    OffMenu(this);

    ShowStatus(NULL);
    ShowWorkTime(NULL);
    ShowPortCounts(NULL);
    tmFind->Enabled = true;
    sbRunModule->Down = false;
    cbPortName->Enabled = true;
}

//---------------------------------------------------------------------------
// ������� ������ � ��������� ��� ������
void __fastcall TfrmMain::SetModemButtons(bool state)
{
    btnModemRequest->Enabled = state;
    btnModemCommand->Enabled = state;
    btnGetModemNum->Enabled = state;
    btnSetModemNum->Enabled = state;
    btnGetModemTime->Enabled = state;
    btnSetModemTime->Enabled = state;
    btnGetAlarmTime->Enabled = state;
    btnSetAlarmTime->Enabled = state;
    btnGetCalTime->Enabled = state;
    btnSetCalTime->Enabled = state;

    btnRadioOn->Enabled = state;
    btnLampOn->Enabled = state;
    btnBurnCmdOn->Enabled = state;
    btnPing11->Enabled = state;

    btnGetTimeForRelease->Enabled = state;
    btnSetTimeForRelease->Enabled = state;
    btnGetBurnLen->Enabled = state;
    btnSetBurnLen->Enabled = state;
    btnModemAnyString->Enabled = state;
    btnApplyCommand->Enabled = state;
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::SetModemLights(bool state)
{
    ltModemNum->State = state;
    ltModemTime->State = state;
    ltAlarmTime->State = state;
    ltCalTime->State = state;
    ltBurnLen->State = state;
    ltTimeForRelease->State = state;
    ltRadioOnOff->State = state;
    ltLampOnOff->State = state;
    ltBurnCmdOnOff->State = state;
    ltPing->State = state;
    ltApplyCommand->State = state;
}

//---------------------------------------------------------------------------
// ������� ������������� ��� ������
void __fastcall TfrmMain::btnApplyCommandClick(TObject * Sender)
{
    WriteCommandThread *thread;
    static char *str = "$RSAPR,,*162f\r\n";
    ltApplyCommand->State = false;
    thread = new WriteCommandThread(SendAnyCommand, str, false, true);
    thread->FreeOnTerminate = true;
    thread->Resume();
}

//---------------------------------------------------------------------------
// �������� ���������� �� ������������
void __fastcall TfrmMain::SpeedButton1Click(TObject * Sender)
{
    int t0;
    param_file_struct param;
    char buf1[32], buf2[32];
    char str[256];
    SYSTEMTIME st;

    t0 = time(NULL);

    // ��������� ����� ������
    dtStartDate->GetTextBuf(buf1, 10);
    dtStartTime->GetTextBuf(buf2, 10);
    param.start_time = bufs_to_st(buf1, buf2, &st);

    // ��������� ����� ���������
    dtFinishDate->GetTextBuf(buf1, 10);
    dtFinishTime->GetTextBuf(buf2, 10);
    param.finish_time = bufs_to_st(buf1, buf2, &st);

    // ��������� ����� ������ ��������
    dtBurnDate->GetTextBuf(buf1, 10);
    dtBurnTime->GetTextBuf(buf2, 10);
    param.burn_time = bufs_to_st(buf1, buf2, &st);

    // ������������ ��������
    edBurnTime->GetTextBuf(buf1, 4);
    param.releburn_time = atoi(buf1);

    //������������ ��������
    mePopupLen->GetTextBuf(buf1, 5);
    param.popup_len = atoi(buf1) * 60;

    // ����� ������
    edModemNum->GetTextBuf(buf1, 5);
    param.modem_num = atoi(buf1);

    // ����� ���������� ��������
    dtAm3PopupDate->GetTextBuf(buf1, 10);
    dtAm3PopupTime->GetTextBuf(buf2, 10);
    param.am3_popup_time = bufs_to_st(buf1, buf2, &st);

    // ���������� � ��������
    if ((int) param.finish_time - t0 < 300 && !param.const_reg_flag) {
	sec_to_str(param.finish_time, buf1);
	sec_to_str(t0, buf2);
	if (lang == lang_rus)
	    sprintf(str, "WARNING: ����� ��������� (%s) ������ ���� ��� ������� �� 5 ����� ������ �������� ������� (%s)!", buf1, buf2);
	else
	    sprintf(str, "WARNING: End of recording (%s) must be at least 5 minutes more than current time(%s)!", buf1, buf2);
	LogOut(str);
    }

    if ((int) param.finish_time - (int) param.start_time < RECORD_TIME && !param.const_reg_flag) {
	sec_to_str(param.finish_time, buf1);
	sec_to_str(param.start_time, buf2);

	if (lang == lang_rus)
	    sprintf(str, "WARNING: ����� ������ ����� 5-�� �����! ������ ������: (%s), ��������� ������: (%s)", buf1, buf2);
	else
	    sprintf(str, "WARNING: Record time is less than 5 minutes! start time: (%s), finish time (%s)", buf1, buf2);


	LogOut(str);
    }

    if ((int) param.burn_time - (int) param.finish_time < TIME_BURN_AFTER_FINISH && !param.const_reg_flag) {
	sec_to_str(param.burn_time, buf1);
	sec_to_str(param.finish_time, buf2);
	if (lang == lang_rus)
	    sprintf(str, "WARNING: ����� ������ �������� (%s) ������ ���� �� 2 ������� ����� ������� ��������� (%s)!", buf1, buf2);
	else
	    sprintf(str, "WARNING: Burn wire time (%s) must be on 2 seconds later than end of recording (%s)!", buf1, buf2);
	LogOut(str);
    } else if ((int) param.burn_time - t0 < RECORD_TIME) {
	sec_to_str(param.burn_time, buf1);
	sec_to_str(param.finish_time, buf2);
	if (lang == lang_rus)
	    sprintf(str, "WARNING: ��� ������� �� ������ ��� ���������� ����� \"���������� �����������\"\n");
	else
	    sprintf(str, "WARNING: no time for recording when option is ON \"Constant recoding\"\n");
	LogOut(str);
    }

    if ((int) param.releburn_time < (RELEBURN_TIME_AIRLINK / 30)) {
	if (lang == lang_rus)
	    sprintf(str, "WARNING: ������������ �������� (%d) ������ ���� ����� 2 ������!", param.releburn_time);
	else
	    sprintf(str, "WARNING: Burn wire time (%d) must be more than 2 seconds!", param.releburn_time);
	LogOut(str);
    }

    if ((int) param.popup_len < POPUP_DURATION_AIRLINK * 60) {
	if (lang == lang_rus)
	    sprintf(str, "WARNING: ������������ �������� (%d ���) ������ ���� ����� 1 ������!", param.popup_len);
	else
	    sprintf(str, "WARNING: Popup time (%d min) must be more than 1 minute!", param.popup_len);
	LogOut(str);
    }
    // �����
    if ((int) param.modem_num >= 0 && (int) param.am3_popup_time < t0 + 60) {
	sec_to_str(param.am3_popup_time, buf1);
	sec_to_str(t0, buf2);
	if (lang == lang_rus)
	    sprintf(str, "WARNING: ����� ���������� �������� (%s) ������ ���� ����� �������� ������� (%s)!", buf1, buf2);
	else
	    sprintf(str, "WARNING: Modem alarm time (%s) must be later than current time (%s)!", buf1, buf2);
	LogOut(str);
    }
}

//---------------------------------------------------------------------------
// �������� ���������� �� ������������
void __fastcall TfrmMain::btnCheckParamsClick(TObject * Sender)
{
    // ���������
    String disk;
    CheckFileThread *thread;
    disk = String(dcbDisk->Drive) + ":";

    // �������� ����� � ���������� suspended
    //����� ����� ����� ��������� �� ������ FreeOnTerminate
    thread = new CheckFileThread(disk, &param_struct, true);
    thread->FreeOnTerminate = true;
    thread->Resume();
}

//---------------------------------------------------------------------------
// ����������� ������� ��� �������
// �������, � ����������� �� �������!
void __fastcall TfrmMain::CMReadData(TMessage & Message)
{
    double x[NUM_ADS1282_PACK];
    double y[NUM_ADS1282_PACK];
    double z[NUM_ADS1282_PACK];
    double h[NUM_ADS1282_PACK];
    double t[NUM_ADS1282_PACK];
    ADS1282_PACK_STRUCT *pack;
    int i;
    double freq_s;


    pack = (ADS1282_PACK_STRUCT *) Message.WParam;

    freq_s = (1 << pack->adc) * 62.5;	/* ������� */

    if (lang = lang_rus)
	slsDisplay->Title->Text = "��� " + IntToStr((int) freq_s) + " ��";
    else
	slsDisplay->Title->Text = "ADC " + IntToStr((int) freq_s) + " Hz";


    // �������� Z � X
    for (i = 0; i < NUM_ADS1282_PACK; i++) {
//        t[i] = longTime + i * 0.004 / j;      // 250

	t[i] = pack->sec % 86400 + pack->msec / 1000. + i / freq_s;///FREQ_CONST;
	z[i] = (int) ((pack->data[i].x) << 8) / 256;
	y[i] = (int) ((pack->data[i].y) << 8) / 256;
	x[i] = (int) ((pack->data[i].z) << 8) / 256;
	h[i] = (int) ((pack->data[i].h) << 8) / 256;
    }

    slsDisplay->Channels->Items[0]->Data->AddXYData(t, x, NUM_ADS1282_PACK);
    slsDisplay->Channels->Items[1]->Data->AddXYData(t, y, NUM_ADS1282_PACK);
    slsDisplay->Channels->Items[2]->Data->AddXYData(t, z, NUM_ADS1282_PACK);
    slsDisplay->Channels->Items[3]->Data->AddXYData(t, h, NUM_ADS1282_PACK);
}

//---------------------------------------------------------------------------
// ����� ����� �� ������ �����������
void __fastcall TfrmMain::cbTimeLimitChange(TObject * Sender)
{
    int points;
    int net;

    // ����� ����� �� ������
    points =cbTimeLimit->ItemIndex == 0 ? 1000 : cbTimeLimit->ItemIndex == 1 ? 2000 : cbTimeLimit->ItemIndex == 2 ? 5000 : cbTimeLimit->ItemIndex ==
	3 ? 10000 : 20000;

    slsDisplay->SizeLimit = points;
}

//---------------------------------------------------------------------------
// ������ ���������� � ������� ��c����������!
// �������� ������� � ���� ������ �������
void __fastcall TfrmMain::SLScope1XAxisCustomLabel(TObject * Sender, Real SampleValue, AnsiString & AxisLabel)
{
    char str[32];
    u32 h = 0, m = 0, s = 0;
    TIME_DATE td;
    int i;

    i = SampleValue;
    h = (i / 3600) % 24;
    m = (i / 60) % 60;
    s = i % 60;
    sprintf(str, "%02d:%02d:%02d", h, m, s);

    AxisLabel = str;
}

//---------------------------------------------------------------------------
myLangID __fastcall TfrmMain::GetLangID(void)
{
    return lang;
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::menuRusClick(TObject * Sender)
{
    lang = lang_rus;
    ChangeLangID();
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::menuEngClick(TObject * Sender)
{
    lang = lang_eng;
    ChangeLangID();
}

//---------------------------------------------------------------------------
// �������� ���� ����������
void __fastcall TfrmMain::ChangeLangID(void)
{
    if (lang == lang_rus) {
	// ������� �������
	btnReset->Hint = "������������";
	btnPowerOff->Hint = "���������";
	btnTest->Hint = "����������������";
	btnModemOnOff->Hint = "����� ���/����";
	btnModemRequest->Hint = "�������� �����";
	btnModemCommand->Hint = "�������� � �����";
	btnBurn->Hint = "������� ���/����";
	btnGpsOn->Hint = "GPS ���/����";
	btnStartThread->Hint = "����������� �����/����";
	btnSync->Hint = "������������� �� �������� ��";
	btnConst->Hint = "�������� ���������";
	btnSetName->Hint = "������ ����� �������";
	btnSetToZero->Hint = "�������� �������� ��������� � EEPROM";
	btnResetWorkTime->Hint = "�������� ����� ������ ���������";

	// ����
	MenuFile->Caption = "�&���";
	menuOpenLogs->Caption = "������� ���� �����";
	menuOpen->Caption = "������� ���� ����������";
	menuSave->Caption = "�������� ���� ����������";
	menu10Min->Caption = "������� ���� 10-�� �������� ������";
	menu60Min->Caption = "������� ���� ������� ������";
	menu1Day->Caption = "������� ���� �������� ������";
	menu1Week->Caption = "������� ���� ��������� ������";
	menu1Month->Caption = "������� ���� �������� ������";
	menuExit->Caption = "�����";
	menuCtrl->Caption = "������&����";
	menuOperator->Caption = "����� ���������";
	menuAdjust->Caption = "����� �������";
	menuLang->Caption = "����";
	menuRus->Caption = "�������";
	menuEng->Caption = "����������";
	menuRus->Checked = true;
	menuHelp->Caption = "��&�����";
	menuAbout->Caption = "� ���������";

	// ������������ ������������
	pnConfig1->Caption = "������������ ������������";

	// ������������ �������
	gbParams->Caption = "������������ �������";
	sbRunModule->Hint = "����������� � �������/���������� �� �������";

	// ����� ����������
	gbTimes->Caption = "����� / ���������� GPS";
	pnUTCTime->Caption = "����� PC*";
	pnTimeGNS110->Caption = "����� GNS";
	pnGpsTime->Caption = "����� GPS";
	pnGpsLat->Caption = "������";
	pnGpsLon->Caption = "�������";

	// ��������� �������
	gbEnviron->Caption = "��������� �������";
	pnQuartz->Caption = "���";
	gbFreqs->Caption = "�������, ���";

	// �������
	// ���������
	gbOrientation->Caption = "��������� �������";
	// �����
	gbEnvironement->Caption = "�����";
	pnPitchName->Caption = "����,�";
	pnRollName->Caption = "������,�";
	pnHeadName->Caption = "������,�";
	//-----------------------------------------
	// ��������
	TabSheet1->Caption = "�����������";
	gbScope->Caption = "������";
	gbContr->Caption = "��������� ���";
	lbAdcFreqName->Caption = "������� ���";
	lbFiltName->Caption = "���, ��";
	lbNumPoint->Caption = "����� �����.";
	slsDisplay->Title->Text = "���";
	slsDisplay->YAxis->AxisLabel->Text = "������ ���";
	slsDisplay->XAxis->AxisLabel->Text = "�����, �";
	slsDisplay->Legend->Channels->Caption->Text = "������";

	TabSheet2->Caption = "����� ���������";
	gbFileParams->Caption = "���� ����������";
	pnComments->Caption = "����������� (80 ����.)";
	sprintf(param_struct.my_str, "%s", "����������� (80 ��������), �� �������������");
	edSampleString->Text = param_struct.my_str;
	pnPosition->Caption = "������� ���������";
	pnStartDate->Caption = "������ ����������� *";
	pnFinishDate->Caption = "��������� ����������� *";
	pnBurnDate->Caption = "������ �������� *";
	pnConstReg->Caption = "���������� �����������";
	lbUtcTimeComment->Caption = "     * ����� UTC";
	btnCheckParams->Caption = "��������";
	pnModemNum->Caption = "��� ������: ";
	cbModemNum->Items->Clear();
	cbModemNum->Items->Add("���");
	cbModemNum->Items->Add("������");
	cbModemNum->Items->Add("�������");
	cbModemNum->Items->Add("Bentos");
	cbModemNum->ItemIndex = 2;

	cbChangeModemName->Caption = "�� ������ �";
	pnBurnTime->Caption = "������������ ��������, �";
	pnPopupLen->Caption = "������������ ��������, �";
	pnAm3PopupDate->Caption = "������ �������� ������� *";
	pnAm3Cal->Caption = "������� ����� ����� *";
	pnAdcFreq->Caption = "������� ��������� ���, ��";
	pnAdcEnergo->Caption = "�����������������  ���";
	pnAdcPga->Caption = "PGA ���";
	lbConsum->Caption = "�����������";


	cbAdcCons->Items->Clear();
	cbAdcCons->Items->Add("����������");
	cbAdcCons->Items->Add("�������");
	cbAdcCons->ItemIndex = 1;

	pnNumBytes->Caption = "����� ���� � ����� ������";
	pnChannels->Caption = "���������� ������";
	pnFileLen->Caption = "������������ ����� ������";
	cbDataFileLen->Items->Clear();
	cbDataFileLen->Items->Add("1 ���");
	cbDataFileLen->Items->Add("4 ����");
	cbDataFileLen->Items->Add("1 �����");
	cbDataFileLen->ItemIndex = 1;


	pnFiltFreq->Caption = "������� ����� ���, ��";





	//------------------
	TabSheet3->Caption = "����� �������";

	gbModem->Caption = "�����";
	gbModemNum->Caption = "����� ������";
	gbModemRtc->Caption = "����� RTC ������ (��.��.���� ��:��) *";
	gbModemAlarm->Caption = "������ �������� ������� (��.��.���� ��:��) *";
	gbModemLightTime->Caption = "������� ����� ����� *";
	gbModemPopup->Caption = "����� ������� �� ��� (���)";
	gbModemBurnLen->Caption = "������������ �������� ��������� (�)";
	gbModemWriteParams->Caption = "�������� ��������� � �����";
	gbModemBurnOn->Caption = "��������/��������� �������";
	gbModemLampOn->Caption = "��������/��������� �����";
	gbModemRadioOn->Caption = "��������/��������� �����";
	gbModemPingSend->Caption = "������� �������(�) �� ������������� ������";
	cbPingFreq->Items->Clear();
	cbPingFreq->Items->Add("9 ���");
	cbPingFreq->Items->Add("11 ���");
	cbPingFreq->Items->Add("13 ���");
	cbPingFreq->ItemIndex = 1;
	lbUtcTimeMet->Caption = "����� UTC";
	gbRandomStr->Caption = "������� ������������ �������";
	//------------------
        // ��������
	gbMyCounts->Caption = "�������� ������ PC";
	pnPcTotalRx->Caption = "����� �������";
	pnPcTotalTx->Caption = "����� ��������";
	pnPcCmdError->Caption = "������ � �������";
	pnPcCntPack->Caption = "������� �������";
	pnPcXchgErr->Caption = "������ ������";

	gbCounts->Caption = "�������� ������ GNS110";
	pnGnsTotalRx->Caption = "����� �������";
	pnGnsTotalTx->Caption = "����� ��������";
	pnGnsCmdError->Caption = "������ � �������";
	pnGnsFrameError->Caption = "������ �����";
	pnGnsCrcError->Caption = "������ CRC";
	//--------------
	// ��������� ���
	gbAdc->Caption = "������� ���";
	pnAdcNum->Caption = "���";
	pnAdcStatus->Caption = "���������";


	//--------------


	// ������� � ������
	pnStatusAndErrors->Caption = "������ � ������";
	gbStatus0->Caption = "������� ������";
	lbStatus0_0->Caption = "��� �������";
	lbStatus0_1->Caption = "������ ������";
	lbStatus0_2->Caption = "������ � �������";
	lbStatus0_3->Caption = "�� ������ ���� �����������";
	lbStatus0_4->Caption = "������������� ��� ������������";
	lbStatus0_5->Caption = "������������ ������ ������������";
	lbStatus0_6->Caption = "����������� �������";
	lbStatus0_7->Caption = "���������������� ������������";

	gbStatus1->Caption = "���������������� ���������";
	lbStatus1_0->Caption = "������ RTC";
	lbStatus1_1->Caption = "������ ������� ��������";
	lbStatus1_2->Caption = "������ �������������";
	lbStatus1_3->Caption = "������ �������";
	lbStatus1_4->Caption = "������ ������ GPS";
	lbStatus1_5->Caption = "������ EEPROM";
	lbStatus1_6->Caption = "������ SD �����";
	lbStatus1_7->Caption = "������ Flash";

	gbStatus2->Caption = "������ ����������";
	lbStatus2_0->Caption = "GPS �������";
	lbStatus2_1->Caption = "����� �������";
	lbStatus2_2->Caption = "������������ ������";
	lbStatus2_3->Caption = "������������ ������ � EEPROM";
	lbStatus2_4->Caption = "������ ��������� 19.2 ���";
	lbStatus2_5->Caption = "������ ��������� 4.096 ���";
	lbStatus2_6->Caption = "��� PPS �� �����";
	lbStatus2_7->Caption = "������ ������� TIM3";

	gbResetCause->Caption = "������� ������ ����������";
	lbStatusReset_0->Caption = "���������� �������";
	lbStatusReset_1->Caption = "������� �����";
	lbStatusReset_2->Caption = "�������� �������";
	lbStatusReset_3->Caption = "WDT �����";
	lbStatusReset_4->Caption = "���������� ���������� �����";
	lbStatusReset_5->Caption = "�������������� �����";

	lbRele2->Caption = "������� �������";
	lbRele3->Caption = "���������� �������";
	lbRele6->Caption = "��������� USB";
	lbRele7->Caption = "��c��������� WUSB";

	//-----------------
	sbInfo->Panels->Items[2]->Text = "��������� (��:��)";
	sbInfo->Panels->Items[3]->Text = "����� PC (��:��)";
	sbInfo->Panels->Items[4]->Text = "����� (��:��)";
	sbInfo->Panels->Items[1]->Text = "����� ������ � ������� ������";


    } else {
	// ������� �������
	btnReset->Hint = "Reset";
	btnPowerOff->Hint = "Shut Down";
	btnTest->Hint = "Self-Test";
	btnModemOnOff->Hint = "Modem on / Modem off";
	btnModemRequest->Hint = "Query modem";
	btnModemCommand->Hint = "Write to modem";
	btnBurn->Hint = "Burning wire voltage ON/ OFF";
	btnGpsOn->Hint = "GPS on / GPS off";
	btnStartThread->Hint = "Oscilloscope on / Oscilloscope off";
	btnSync->Hint = "Synchronize with PC time";
	btnConst->Hint = "Write the constants";
	btnSetName->Hint = "Enter the SPN number";
	btnSetToZero->Hint = "Write initial constants to recorder's EEPROM";
	btnResetWorkTime->Hint = "Reset devices operating time";

	// ����
	MenuFile->Caption = "&File";
	menuOpenLogs->Caption = "Open log file";
	menuOpen->Caption = "Open settings file";
	menuSave->Caption = "Write settings file";
	menu10Min->Caption = "Create a 10-minute file";
	menu60Min->Caption = "Create an hour file";
	menu1Day->Caption = "Create a daily file";
	menu1Week->Caption = "Create a weekly file";
	menu1Month->Caption = "Create a monthly file";
	menuExit->Caption = "Exit";
	menuCtrl->Caption = "Control";
	menuOperator->Caption = "Operator mode";
	menuAdjust->Caption = "Testing mode";
	menuLang->Caption = "Language";
	menuRus->Caption = "Russian";
	menuEng->Caption = "English";
	menuEng->Checked = true;
	menuHelp->Caption = "Help";
	menuAbout->Caption = "About...";

	// ������������ ������������
	pnConfig1->Caption = "Equipment profile";


	// ������������ �������
	gbParams->Caption = "Connected SPN";
	sbRunModule->Hint = "Connect to SPN / Disconnect from SPN";

	// ����� ����������
	gbTimes->Caption = "Time / GPS coordinates";
	pnUTCTime->Caption = "PC Time";
	pnGpsTime->Caption = "GPS Time";
	pnGpsLat->Caption = "Latitude";
	pnGpsLon->Caption = "Longitude";

     //	Label3->Caption = "Recorder Time";        

	// ��������� �������
	gbEnviron->Caption = "Recorder parameters";
	pnQuartz->Caption = "MHz";
	gbFreqs->Caption = "Frequencies, MHz";

	// �������
	// ���������
	gbOrientation->Caption = "Device orientation";
	// �����
	gbEnvironement->Caption = "Environment";
	pnPitchName->Caption = "Pitch,�";
	pnRollName->Caption = "Roll,�";
	pnHeadName->Caption = "Azimuth,�";
	//-----------------------------------------
	// ��������
	TabSheet1->Caption = "Oscilloscope";
	gbScope->Caption = "Information";
	gbContr->Caption = "ADC Settings";
	lbAdcFreqName->Caption = "Sampling Rate";

	lbConsum->Caption = "Consumption";

	lbFiltName->Caption = "Filter, Hz";
	lbNumPoint->Caption = "Num Points";
	slsDisplay->Title->Text = "ADC";
	slsDisplay->YAxis->AxisLabel->Text = "ADC Data";
	slsDisplay->XAxis->AxisLabel->Text = "Time, s";
	slsDisplay->Legend->Channels->Caption->Text = "Channels";


	TabSheet2->Caption = "Operator mode";
	gbFileParams->Caption = "File of acqusition parameters";
	pnComments->Caption = "Comments (80 characters)";

	sprintf(param_struct.my_str, "%s", "Comments (80 characters), do not edit");
	edSampleString->Text = param_struct.my_str;
	pnPosition->Caption = "SPN survey location num";
	pnStartDate->Caption = "Start recording time *";
	pnFinishDate->Caption = "End recording time *";
	pnBurnDate->Caption = "Burn wire start time *";
	pnConstReg->Caption = "Continuous recording";
	lbUtcTimeComment->Caption = "     * UTC Time";
	btnCheckParams->Caption = "Check";
	pnModemNum->Caption = "Modem Type: ";
	cbModemNum->Items->Clear();
	cbModemNum->Items->Add("None");
	cbModemNum->Items->Add("Old");
	cbModemNum->Items->Add("AM3");
	cbModemNum->Items->Add("Bentos");
	cbModemNum->ItemIndex = 2;

	//   cbChangeModemNameClick(this);

	cbChangeModemName->Caption = "Not change #";
	pnBurnTime->Caption = "Burning wire duration, sec";
	pnPopupLen->Caption = "SPN rising time, min";
	pnAm3PopupDate->Caption = "Modem burn wire start time *";
	pnAm3Cal->Caption = "Daytime *";
	pnAdcFreq->Caption = "ADC sampling rate, Hz";
	pnAdcEnergo->Caption = "ADC power consumption";
	pnAdcPga->Caption = "PGA ADC";
	cbAdcCons->Items->Clear();
	cbAdcCons->Items->Add("Low");
	cbAdcCons->Items->Add("Normal");
	cbAdcCons->ItemIndex = 1;

	pnNumBytes->Caption = "Number of bytes in data sample";
	pnChannels->Caption = "Channels ON";
	pnFileLen->Caption = "Size of data file";
	cbDataFileLen->Clear();
	cbDataFileLen->Items->Add("1 hour");
	cbDataFileLen->Items->Add("4 hours");
	cbDataFileLen->Items->Add("1 day");
	cbDataFileLen->ItemIndex = 1;
	pnFiltFreq->Caption = "Filter low cut frequency, Hz";


	//--------------
	TabSheet3->Caption = "Testing mode";
	gbModem->Caption = "Modem";
	gbModemNum->Caption = "Modem number";
	gbModemRtc->Caption = "Modem RTC time (dd:mm:yyyy hh:mm) *";
	gbModemAlarm->Caption = "Modem burn wire start time dd:mm:yyyy hh:mm) *";
	gbModemLightTime->Caption = "Light Time *";
	gbModemPopup->Caption = "SPN rising duration (min)";
	gbModemBurnLen->Caption = "Burn wire duration (sec)";
	gbModemWriteParams->Caption = "Write parameters to modem";
	gbModemBurnOn->Caption = "Burn wire ON/OFF";
	gbModemLampOn->Caption = "Lamp ON/OFF";
	gbModemRadioOn->Caption = "Radio ON/OFF";
	gbModemPingSend->Caption = "Send acoustic ping";
	cbPingFreq->Items->Clear();
	cbPingFreq->Items->Add("9 kHz");
	cbPingFreq->Items->Add("11 kHz");
	cbPingFreq->Items->Add("13 kHz");
	cbPingFreq->ItemIndex = 1;;
	lbUtcTimeMet->Caption = "UTC time";
	gbRandomStr->Caption = "Send specified here command to modem";
	//--------------
	// ��������
	gbMyCounts->Caption = "PC counts";
	pnPcTotalRx->Caption = "Total received";
	pnPcTotalTx->Caption = "Total transmited";
	pnPcCmdError->Caption = "Errors in command";
	pnPcCntPack->Caption = "Counts packets";
	pnPcXchgErr->Caption = "Errors of exchange";

	gbCounts->Caption = "SPN counts";
	pnGnsTotalRx->Caption = "Total received";
	pnGnsTotalTx->Caption = "Total transmited";
	pnGnsCmdError->Caption = "Errors in command";
	pnGnsFrameError->Caption = "Frame errors";
	pnGnsCrcError->Caption = "CRC errors";

	//--------------
	// ��������� ���
	gbAdc->Caption = "Working ADC";
	pnAdcNum->Caption = "ADC";
	pnAdcStatus->Caption = "Status";

	//--------------
	// ������� � ������
	pnStatusAndErrors->Caption = "Status and errors";
	gbStatus0->Caption = "Main Status";
	lbStatus0_0->Caption = "RTC is not setup ";
	lbStatus0_1->Caption = "Modem error";
	lbStatus0_2->Caption = "Command error";
	lbStatus0_3->Caption = "Parameters file not found";
	lbStatus0_4->Caption = "Recorder ADC fault";
	lbStatus0_5->Caption = "Memory overflow";
	lbStatus0_6->Caption = "Oscilloscope is on";
	lbStatus0_7->Caption = "Self testing is in progress";

	gbStatus1->Caption = "Self-testing of devices";
	lbStatus1_0->Caption = "RTC error";
	lbStatus1_1->Caption = "Pressure sensor error";
	lbStatus1_2->Caption = "Accelerometer error";
	lbStatus1_3->Caption = "Compass error";
	lbStatus1_4->Caption = "GPS receiver error";
	lbStatus1_5->Caption = "EEPROM error";
	lbStatus1_6->Caption = "SD card error";
	lbStatus1_7->Caption = "Flash error";

	gbStatus2->Caption = "Other devices";
	lbStatus2_0->Caption = "GPS on";
	lbStatus2_1->Caption = "Modem on";
	lbStatus2_2->Caption = "Testing the modem";
	lbStatus2_3->Caption = "EEPROM has incorrect data";
	lbStatus2_4->Caption = "Generator 19.2 MHz error";
	lbStatus2_5->Caption = "Generator 4.096 MHz error";
	lbStatus2_6->Caption = "No PPS";
	lbStatus2_7->Caption = "TIM3 timer error";

	gbResetCause->Caption = "Disconnection reason";
	lbStatusReset_0->Caption = "Power off";
	lbStatusReset_1->Caption = "External reset";
	lbStatusReset_2->Caption = "Reduced power supply";
	lbStatusReset_3->Caption = "WDT reset";
	lbStatusReset_4->Caption = "Absence of communication";
	lbStatusReset_5->Caption = "Emergency reset";

	lbRele2->Caption = "Burn ON";
	lbRele3->Caption = "Analog Supply";
	lbRele6->Caption = "Wire USB";
	lbRele7->Caption = "Wireless WUSB";


	//----------------------------------
	sbInfo->Panels->Items[2]->Text = "Acqusition (hh:mm)";
	sbInfo->Panels->Items[3]->Text = "PC mode (hh:mm)";
	sbInfo->Panels->Items[4]->Text = "Modem (hh:mm)";
	sbInfo->Panels->Items[1]->Text = "Working time for the current connection";
    }
    cbModemNumClick(this);
}

//---------------------------------------------------------------------------
