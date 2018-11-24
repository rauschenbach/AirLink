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
    memset(&modem_inner_state, 0, sizeof(modem_inner_state));	/* изначально все выключено */
    lang = lang_eng;
}

//---------------------------------------------------------------------------
// Послать команду, прочитать ответ
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
    return (int) num;		// сколько прочитали
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
// Запуск самотестирования
void __fastcall TfrmMain::btnTestClick(TObject * Sender)
{
    WriteCommandThread *thread;
    test_result.t0 = 0;
    test_result.tick = 0;
    test_result.delay = time(NULL);
    first_run = false;		// запустили

    if (lang == lang_rus)
	LogOut("Началось тестирование...подождите!");
    else
	LogOut("Begin SelfTest...wait!");

    enable_log = false;
    thread = new WriteCommandThread(InitTest, NULL, false, false);
    thread->WaitFor();
    delete thread;
}

//---------------------------------------------------------------------------
// Вывеcти в Memo
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
// Вывод в лог
void __fastcall TfrmMain::LogOut(char *text, bool log_only)
{
    int i, len;
    char buf[1024];
    String str;
    char crlf[] = "\r\n";
    static String old;
    unsigned long bw;

    str = TimeString() + text;

    // Скопируем в буфер
    memset(buf, 0, sizeof(buf));
    memcpy(buf, str.c_str(), str.Length());

    // Уберем перевод строки
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
	WriteFile(log_fd, crlf, strlen(crlf), &bw, NULL);	// Добавлять перевод строки
    }
}

//---------------------------------------------------------------------------
// Разрешим кнопки
void __fastcall TfrmMain::EnableControl(void)
{
    int num, baud;
    enable_log = true;		// можно писать
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
    // Версия Прошивки и программы
//    frmAbout->lbGnsVer->Caption = "GNS110 firmware\t" + port_set[cbPortName->ItemIndex].ver;

    if (port_set[cbPortName->ItemIndex].v != get_version() || port_set[cbPortName->ItemIndex].r != get_revision()) {


	if (lang == lang_rus)
	    LogOut("Версия GNS AirLink отличается от версии прошивки регистратора!");
	else
	    LogOut("GNS AirLink version differs from recorder's firmware version!");


	// Версия прибора меньше версии прошивки
	if (port_set[cbPortName->ItemIndex].v > get_version() || port_set[cbPortName->ItemIndex].r > get_revision()) {
	    if (lang == lang_rus)
		LogOut("Обновите GNS AirLink на более свежую!");
	    else
		LogOut("Update GNS AirLink version!");


	} else if (port_set[cbPortName->ItemIndex].v < get_version() || port_set[cbPortName->ItemIndex].r < get_revision()) {
	    if (lang == lang_rus)
		LogOut("Обновите прошивку регистратора на более свежую!");
	    else
		LogOut("Update recorder's firmware!");
	}
    }

    bEndThread = false;
    MyThread = new ReadPortThread(false);
    MyThread->Priority = tpHighest;	// самый выше!

    run_ok = true;
}

//---------------------------------------------------------------------------
// Вывеcти время компьютера
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
// Вывести время
// Если время различается более чем на 30 секунд - моргать статусом
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
// Ввести-вывести контстанты, можно нажаьт только когда нет измерений
void __fastcall TfrmMain::btnConstClick(TObject * Sender)
{
    frmConst->Left = this->Left + 200;
    frmConst->Top = this->Top + 50;
    frmConst->ShowModal();
}

//---------------------------------------------------------------------------
// Получили время и синхронизация
void __fastcall TfrmMain::btnSyncClick(TObject * Sender)
{
    static time_t t0;
    t0 = time(NULL) + 1;	// +1 секунда

    WriteCommandThread *thread;
    thread = new WriteCommandThread(TimeSync, &t0, false, false);
    thread->WaitFor();
    delete thread;
}
          
//---------------------------------------------------------------------------
// При открытии программы создаем LOG - файл
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

    pcChangeMode->ActivePageIndex = 1;	// Всегда на второй вкладке
    StartTime = t0;		// Время запуска программы сохраним

    save_param.h_memo = memoLog->Height;
    save_param.h_status = pnStatus->Height;
    save_param.h_contr = gbContr->Height;
    save_param.h_mode = pcChangeMode->Height;

    ChangeLangID();


    // Открываем log файл
    sec_to_td(t0, &td);
    CreateDirectory("LOGS", NULL);
    sprintf(str, "LOGS\\LOG_%02d%02d%02d_%02d%02d.log\0", td.day, td.month, td.year - 2000, td.hour, td.min);
    log_fd = CreateFile(str, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (lang == lang_rus)
	sprintf(str, "Запущена программа GNS AirLink ver: %01d.%02d\0\r\n", get_version(), get_revision());
    else
	sprintf(str, "Run program GNS AirLink ver: %01d.%02d\0\r\n", get_version(), get_revision());
    LogOut(str);
    tmFind->Enabled = true;	// Таймер поиска станций
}

//---------------------------------------------------------------------------
// Вывести результат тестирования модема
// Разрешить кнопки
void __fastcall TfrmMain::ShowTestModem(void *su)
{
    char buf[256];
    DEV_STATUS_STRUCT *status;

    test_modem.tick = 0;
    test_modem.t0 == 0;

    UnhideButtons();

    if (su != NULL) {
	status = (DEV_STATUS_STRUCT *) su;

	// Смотрим-снялась ошибка или нет
	if (status->st_main & 0x02) {
	    if (lang == lang_rus)
		LogOut("Тестирование модема завершено, нет модема или модем неисправен!\n");
	    else
		LogOut("Modem test finished, no modem or modem error!\n");
	} else {
	    if (lang == lang_rus)
		LogOut("Тестирование модема завершено, время модема переведено на сутки вперед!\n");
	    else
		LogOut("Modem test finished, modem alarm time setup on one day ahead!\n");
	}
    }
}

//---------------------------------------------------------------------------
// Поиск портов
void __fastcall TfrmMain::TerminateAllThreads(void)
{
    TerminateScope();		// Останавливаем устройство и чистим буфер

    // Выключаем поток
    if (MyThread != NULL) {
	MyThread->WaitFor();
	delete MyThread;
	MyThread = NULL;
    }
    // закроем порт
    PortClose();
}

//---------------------------------------------------------------------------
// Закрывать программу или нет?
int __fastcall TfrmMain::CanPowerOffModem(void)
{
    int res = 0;

    // Включен модем?
    if (lbStatus2_1->Font->Color == clGreen) {
	if (lang == lang_rus)
	    res = YESNOCANCEL_BOX("Модем останется включеным. Выключить модем?");
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
// Сброс DSP
void __fastcall TfrmMain::btnResetClick(TObject * Sender)
{
    WriteCommandThread *thread;
    int res;

    res = CanPowerOffModem();
    if (res == 1) {		// Выключим сначала модем
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

    // Основной поток - стоп!
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
    if (res == 1) {		// Выключим сначала модем
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

    // Основной поток - стоп!
    bEndThread = true;
    TerminateAllThreads();
    DisableControl();
    first_run = true;
}

//---------------------------------------------------------------------------
// Включиьт модем и сдвинуть время на сутки
// Замереть после 8-й секунды
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
	    LogOut("Включение и тест модема...подождите!");
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
	    LogOut("Выключение модема");
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

    // Если нажат
    if (bit) {
	thread = new WriteCommandThread(BurnOff, NULL, false, false);
	thread->WaitFor();
	delete thread;
    } else {			/*if(!(status.ports & RELE_BURN_BIT)) */
// выключен - включить
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
// Выход
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
// Создать времена для параметров
// Округление до 5 минут + 10 минут на старт
void __fastcall TfrmMain::CreateParamData(TIME_ENUM param)
{
    time_t t;

    // Вкладку на 2
    pcChangeMode->ActivePage = TabSheet2;

    //  получить время на  "сейчас"
    t = time(NULL);

    
    switch (param) {
    case TIME_10_MIN:
	param_struct.start_time = (t - t % 60) + 420;	// на 5 минут позже "сейчас"
	param_struct.finish_time = param_struct.start_time + RECORD_TIME * 2;
	param_struct.data_file_len = 1;
	break;

    case TIME_1_DAY: // 1 день
	param_struct.start_time = (t - t % 300) + 600;	// на 10 минут позже "сейчас"
	param_struct.finish_time = param_struct.start_time + RECORD_ONE_DAY;
	param_struct.data_file_len = 4;
	break;

    case TIME_1_WEEK: // неделя
	param_struct.start_time = (t - t % 300) + 600;	// на 10 минут позже "сейчас"
	param_struct.finish_time = param_struct.start_time + RECORD_ONE_WEEK;
	param_struct.data_file_len = 24;
	break;
               
    case TIME_1_MONTH:  // месяц
	param_struct.start_time = (t - t % 300) + 300;	// на 5 минут позже "сейчас"
	param_struct.finish_time = param_struct.start_time + RECORD_ONE_MONTH;
	param_struct.data_file_len = 1;
	break;


    case TIME_60_MIN: // 60 минут
    default:
	param_struct.start_time = (t - t % 300) + 600;	// на 10 минут позже "сейчас"
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
    param_struct.power_cons = 1;	// высокое
    param_struct.pga_adc = 1;
    param_struct.num_bytes = 3;
    param_struct.on_off_channels = 0x0F;
}

//---------------------------------------------------------------------------
// Вывести параметры на экран
void __fastcall TfrmMain::ShowParamData(void *p)
{
    char buf[512];
    u8 i;
    int j;
    param_file_struct *param;
    TIME_DATE td;
    SYSTEMTIME st;


    //--------------- для режыма оператора заполнить поля
    cbModemNumClick(this);
    mePopupLenChange(this);
    meAm3Cal0Change(this);
    meAm3Cal1Change(this);
    cbFreqClick(this);
    cbConstRegClick(this);

    //--------------- Поставим минимальную дату
    memset(&st, 0, sizeof(SYSTEMTIME));
    st.wDay = 1;
    st.wMonth = 1;
    st.wYear = 2010;
    dtStartDate->MinDate = SystemTimeToDateTime(st);
    dtFinishDate->MinDate = SystemTimeToDateTime(st);
    dtBurnDate->MinDate = SystemTimeToDateTime(st);
    dtAm3PopupDate->MinDate = SystemTimeToDateTime(st);


    //--------------- Поставим максимальную дату
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


    //--------------- На сутки от сегодня для модема
    dtModemDate->Date = SystemTimeToDateTime(st);
    dtModemTime->Time = SystemTimeToDateTime(st);
    dtAlarmDate->Date = dtModemDate->Date + 1.0;
    dtAlarmTime->Time = dtModemTime->Time;


    if (p == NULL)
	return;

    param = (param_file_struct *) p;


    //-------------тестовая строка
    if (param->my_str != NULL)
	edSampleString->Text = String(param->my_str);

    //----------- Позиция установки
    edPosition->Text = IntToStr(param->pos);

    //----------- Начало регистрации
    memset(&st, 0, sizeof(SYSTEMTIME));
    sec_to_st(param->start_time, &st);
    dtStartDate->Date = SystemTimeToDateTime(st);
    dtStartTime->Time = SystemTimeToDateTime(st);


    //----------- Окончание регистрации
    memset(&st, 0, sizeof(SYSTEMTIME));
    sec_to_st(param->finish_time, &st);
    dtFinishDate->Date = SystemTimeToDateTime(st);
    dtFinishTime->Time = SystemTimeToDateTime(st);


    //----------- Время начала пережига
    memset(&st, 0, sizeof(SYSTEMTIME));
    sec_to_st(param->burn_time, &st);
    dtBurnDate->Date = SystemTimeToDateTime(st);
    dtBurnTime->Time = SystemTimeToDateTime(st);


    //----------- длительность всплытия в секундах
    udBurnTime->Position = param->releburn_time;

    //----------- длительность всплытия в минутах
    udPopupLen->Position = param->popup_len;
    mePopupLen->Text = IntToStr(param->popup_len);

    //----------- Тип модема показать
    cbModemNum->ItemIndex = param->am3_modem_type;

    //----------- Номер модема показать
    edModemNum->Text = IntToStr(param->modem_num);

    cbModemNumClick(this);

    //----------- Время аварийного всплытия
    memset(&st, 0, sizeof(SYSTEMTIME));
    sec_to_st(param->am3_popup_time, &st);
    dtAm3PopupDate->Date = SystemTimeToDateTime(st);
    dtAm3PopupTime->Time = SystemTimeToDateTime(st);


    //-----------  Светлое время суток
    sprintf(buf, "%02d.%02d", param->am3_cal_h0 % 24, param->am3_cal_m0 % 60);
    meAm3Cal0->SetTextBuf(buf);
    sprintf(buf, "%02d.%02d", param->am3_cal_h1 % 24, param->am3_cal_m1 % 60);
    meAm3Cal1->SetTextBuf(buf);


    // Частота оцифровки
    cbAdcSample->ItemIndex =
	(param->sample_freq == 4000) ? 6 : (param->sample_freq == 2000) ? 5 : \
	(param->sample_freq == 1000) ? 4 : (param->sample_freq == 500) ? 3 : \
	(param->sample_freq == 250)  ? 2 : (param->sample_freq == 125) ? 1 : 0;


    // Энергопотрбление
    cbAdcCons->ItemIndex = param->power_cons == 0 ? 0 : 1;

    // PGA
    cbAdcPGA->ItemIndex = param->pga_adc == 1 ? 0 :
	param->pga_adc == 2 ? 1 : param->pga_adc == 4 ? 2 : param->pga_adc == 8 ? 3 : param->pga_adc == 16 ? 4 : param->pga_adc == 32 ? 5 : 6;

    // Число байт в слове
    /////cbNumBytes->ItemIndex = param->num_bytes == 3 ? 0 : 1;

    // Включенные каналы смотрим ПО вЫключеию
    cbChan4->Checked = (param->on_off_channels & 0x08) ? true : false;
    cbChan3->Checked = (param->on_off_channels & 0x04) ? true : false;
    cbChan2->Checked = (param->on_off_channels & 0x02) ? true : false;
    cbChan1->Checked = (param->on_off_channels & 0x01) ? true : false;


    // Частота среза фильтра - не ставим
    seFreq->Value = param->filter_freq;
    if (param->filter_freq == 0) {
	cbFreq->Checked = false;
    } else {
	cbFreq->Checked = true;
    }

    // Постоянная регистрация (Да/Нет)
///    cbConstReg->ItemIndex = (param->const_reg_flag == 0) ? 0 : 1;

    cbConstReg->Checked = (param->const_reg_flag == 0) ? false : true;


    /// memcpy(&param_struct, param, sizeof(param_struct));
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::menu10MinClick(TObject * Sender)
{
    CreateParamData(TIME_10_MIN);
    ShowParamData(&param_struct);
//    edSampleString->Text = "Файл параметров для 10-ти минутной записи";
    menuSave->Enabled = true;

}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::menu60MinClick(TObject * Sender)
{
    CreateParamData(TIME_60_MIN);
    ShowParamData(&param_struct);
    //    edSampleString->Text = "Файл параметров для часовой записи";
    menuSave->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::menu1DayClick(TObject * Sender)
{
    CreateParamData(TIME_1_DAY);
    ShowParamData(&param_struct);
//    edSampleString->Text = "Файл параметров для суточной записи";
    menuSave->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::menu1WeekClick(TObject * Sender)
{
    CreateParamData(TIME_1_WEEK);
    ShowParamData(&param_struct);
//    edSampleString->Text = "Файл параметров для недельной записи";
    menuSave->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::menu1MonthClick(TObject * Sender)
{
    CreateParamData(TIME_1_MONTH);
    ShowParamData(&param_struct);
    //    edSampleString->Text = "Файл параметров для месячной записи";
    menuSave->Enabled = true;
}

//---------------------------------------------------------------------------

// Сохранить на SD карту
void __fastcall TfrmMain::menuSaveClick(TObject * Sender)
{
    SaveFileThread *thread;

    pcChangeMode->ActivePage = TabSheet2;

    thread = new SaveFileThread(false);
    thread->FreeOnTerminate = true;
}

//---------------------------------------------------------------------------
// если видимы счетчики - 7 частей
// если нет - 5
void __fastcall TfrmMain::FormResize(TObject * Sender)
{
    int w, h, d, i;
    char str[128];
    int w2;

    w = pnUp->Width;
    h = this->Height;
    d = 5;


    // 1-я вкладка
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


    // нижняя часть
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

    // 2-я вкладка
    w2 = gbFileParams->Width / 10 - d;

    // 1 ряд
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

    // 3 ряд

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


    // 3-я вкладка
    // 1-й ряд
    w2 = gbModem->Width / 3 - d;
    gbModemNum->Width = w2;
    gbModemRtc->Width = w2;
    gbModemAlarm->Width = w2;
    gbRandomStr->Width = w2;
    ltModemNum->Left = w2 - ltModemNum->Width - d;
    ltModemTime->Left = w2 - ltModemTime->Width - d;
    ltAlarmTime->Left = w2 - ltAlarmTime->Width - d;
    ltModemCmd->Left = w2 - ltModemCmd->Width - d;


    // 2 ряд
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


    // 3-й ряд
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
// Установить номер станции
void __fastcall TfrmMain::btnSetNameClick(TObject * Sender)
{
    frmNumber->Left = this->Left + 210;
    frmNumber->Top = this->Top + 50;
    frmNumber->ShowModal();
}

//---------------------------------------------------------------------------
// Запрос на выход из программы
void __fastcall TfrmMain::FormCloseQuery(TObject * Sender, bool & CanClose)
{
    int res;

    if (!bEndThread) {
	if (lang == lang_rus)
	    res = YESNO_BOX("Прибор останется в интерактивном режиме! Выйти из программы?");
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
// Нажатие кнопки Старт
// Что выбрано?
void __fastcall TfrmMain::btnStartThreadClick(TObject * Sender)
{
    DEV_STATUS_STRUCT status;
    bool bit;


    get_dsp_status(&status);

    bit = (status.st_main & 0x40 ? false : true);

    // Неисправность регистратора
    if (status.st_main & 0x10) {
	TerminateScope();
	if (lang == lang_rus)
	    WARN_BOX("Запуск осцилографа невозможен, регистратор неисправен!");
	else
	    WARN_BOX("Can't run oscilloscope, Recorder ADC fault!");
	return;
    }
    // Старт
    if (bit) {			// если запущен
	TerminateScope();
    } else {

	WriteCommandThread *thread;


	// Частота
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

	// На весь экран при запуске
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
//  Сбросить EEPROM
void __fastcall TfrmMain::btnSetToZeroClick(TObject * Sender)
{
    WriteCommandThread *thread;
    int res;

    if (lang == lang_rus)
	res = YESNO_BOX("Сбросить EEPROM?");
    else
	res = YESNO_BOX("Reset EEPROM?");

    if (res == IDYES) {
	thread = new WriteCommandThread(SetTimesToZero, NULL, false, false);
	thread->WaitFor();
	delete thread;
	if (lang == lang_rus)
	    LogOut("Требуется перезагрузка прибора!");
	else
	    LogOut("Please reset the device!");
    }
}

//---------------------------------------------------------------------------
// Запустить выбранную станцию
void __fastcall TfrmMain::sbRunModuleClick(TObject * Sender)
{
    String met;

    if (cbPortName->ItemIndex >= 0)
	met = cbPortName->Items[cbPortName->ItemIndex].Text;
    gns_num = frmMain->port_set[cbPortName->ItemIndex].gns_name;

    // Если нашел станции
    if (cbPortName->ItemIndex >= 0 && bEndThread) {
	EnableControl();
	tmFind->Enabled = false;
	cbPortName->Enabled = false;
	sbRunModule->Down = true;
	GetWorkDisk(met);

	if (lang == lang_rus)
	    met = "Подключить станцию " + met;
	else
	    met = "Connect to recorder " + met;
    } else if (!bEndThread) {	// остановить станцию
	bEndThread = true;
	TerminateAllThreads();
	DisableControl();
	cbPortName->Enabled = true;
	sbRunModule->Down = false;

	if (lang == lang_rus)
	    met = "Отключить станцию " + met;
	else
	    met = "Disconnect from recorder " + met;

    }
    LogOut(met.c_str());
}

//---------------------------------------------------------------------------
// Опрос модема
void __fastcall TfrmMain::btnModemRequestClick(TObject * Sender)
{
    ModemRequestThread *thread;

    SetModemButtons(false);
    SetModemLights(false);

    cbUpdateTime->Checked = false;
    if (lang == lang_rus)
	LogOut("Запрос параметров модема...подождите!");
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

    // Светлое время суток получим
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
 // Время модема
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
// Установить номер модема
void __fastcall TfrmMain::btnSetModemNumClick(TObject * Sender)
{
    static u16 num;
    char str[128];

    // номер модема
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
// Зачечь/погасить лампу и вывести номер модема
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
// Зачечь/погасить лампу и вывести время модема
void __fastcall TfrmMain::ShowModemTime(SYSTEMTIME * st)
{
    char str[128];

    // Время модема
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
// Зачечь/погасить лампу и вывести время аварийного всплытия
void __fastcall TfrmMain::ShowAlarmTime(SYSTEMTIME * st)
{
    char str[128];

    // Время модема
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
// Зачечь/погасить лампу и вывести календарное время (светлое время суток)
void __fastcall TfrmMain::ShowCalTime(u16 h0, u16 m0, u16 h1, u16 m1)
{
    char str[128];
    SYSTEMTIME st;

    // Календарное время
    if (h0 != -1 && m0 != -1 && h1 != -1 && m1 != -1) {
	GetSystemTime(&st);	// Чтобы не было мусора

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
// Зачечь/погасить лампу и вывести время на всплытие
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
// Зачечь/погасить лампу и вывести длительность пережыга
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
// Всегда выводить время UTC
void __fastcall TfrmMain::timIdleTimer(TObject * Sender)
{
    // Раз в секунду
    if (big_timer % 10 == 0)
	TimeUTC();

    big_timer++;
}

//---------------------------------------------------------------------------
// Соберем все параметры с формы
void __fastcall TfrmMain::GetModemParameters(void)
{
    char str[128];
    u16 sec, msec;

    // номер модема
    meModemNum->GetTextBuf(str, 5);
    modem.modem_num = StrToInt(str);


    // Время модема
    DecodeDate(dtModemDate->Date, modem.modem_time.wYear, modem.modem_time.wMonth, modem.modem_time.wDay);
    DecodeTime(dtModemTime->Time, modem.modem_time.wHour, modem.modem_time.wMinute, modem.modem_time.wSecond, modem.modem_time.wMilliseconds);

    // Аварийное время
    DecodeDate(dtAlarmDate->Date, modem.alarm_time.wYear, modem.alarm_time.wMonth, modem.alarm_time.wDay);
    DecodeTime(dtAlarmTime->Time, modem.alarm_time.wHour, modem.alarm_time.wMinute, modem.alarm_time.wSecond, modem.alarm_time.wMilliseconds);


    // Светлое время суток получим
    DecodeTime(dtCalTime0->Time, modem.am3_h0_time, modem.am3_m0_time, sec, msec);
    DecodeTime(dtCalTime1->Time, modem.am3_h1_time, modem.am3_m1_time, sec, msec);

    // Время всплытия
    meTimeForRelease->GetTextBuf(str, 4);
    modem.time_for_release = atoi(str);

    // Время пережыга
    meBurnLen->GetTextBuf(str, 3);
    modem.burn_len = StrToInt(str);

}

//---------------------------------------------------------------------------
// Стоп измерения
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
	LogOut("Запись параметров в модем...подождите!");
    else
	LogOut("Write parameters to modem...wait!");

    thread = new ModemCommandThread(&modem, true);
    thread->FreeOnTerminate = true;
    thread->Resume();
}

//---------------------------------------------------------------------------
// Послать в модем любую команду
void __fastcall TfrmMain::btnModemAnyStringClick(TObject * Sender)
{
    char str[128];
    int i;

    // Получим команду из буфера
    // Должна начинаться с $ и заканчиваться *
    // Контрольную сумму поставит вызываемая функция
    edAnyCommand->GetTextBuf(str, 127);

    SendAnyCommand(str);
}

//---------------------------------------------------------------------------
// Открыть файл параметров
void __fastcall TfrmMain::menuOpenClick(TObject * Sender)
{
    OpenFileThread *thread;
    String name;

    // начальная директория
    odParamFile->InitialDir = String(dcbDisk->Drive) + ":";

    pcChangeMode->ActivePage = TabSheet2;


    // Чтобы лишних скобок не ставить
    if (odParamFile->Execute() == false)
	return;


    if (!FileExists(odParamFile->FileName))
	return;

    name = odParamFile->FileName;

    // вызывать поток с параметром suspended
    //иначе потом может закончица до вызова FreeOnTerminate
    thread = new OpenFileThread(name, true);
    thread->FreeOnTerminate = true;
    thread->Resume();

    String data = ExtractFileDrive(name);
    dcbDisk->Drive = (data.c_str())[0];
}

//---------------------------------------------------------------------------
// Включить GPS / Выключить GPS
void __fastcall TfrmMain::btnGpsOnClick(TObject * Sender)
{
    WriteCommandThread *thread;
    DEV_STATUS_STRUCT status;
    bool bit;

    get_dsp_status(&status);

    bit = (status.ports & RELE_GPS_BIT ? true : false);

    // Если нажат
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
// При работе кнопкм вкл или выкл
void __fastcall TfrmMain::ButtonStateInStart(bool state)
{
    //  btnSync->Enabled = state;
//    btnTest->Enabled = state;
    enable_measure = !state;	// если нету осцилограф
    cbTimeLimitChange(this);
}

//---------------------------------------------------------------------------

// Прекратить рисование
// Останавливаем устройство и чистим буфер
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
	    slsDisplay->Title->Text = "АЦП";
	else
	    slsDisplay->Title->Text = "ADC";

	pnStatus->Visible = true;

    }
}

//---------------------------------------------------------------------------
// очистить вывод-иначе невозможно работать!
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
    enable_log = true;		// можно писать
}

//---------------------------------------------------------------------------
// Поиск станций
void __fastcall TfrmMain::tmFindTimer(TObject * Sender)
{
    if (get_num_station() > 0) {
	tmFind->Enabled = false;
	sbRunModule->Enabled = true;	// Разблокируем кнопку подклбючения
    } else {
	if (!no_enter()) {	// Запуск потока
	    sbRunModule->Enabled = false;
	    sbRunModule->Down = false;
	    FindStationsThread *thread = new FindStationsThread(false);
	    thread->FreeOnTerminate = true;
	}
    }
}

//---------------------------------------------------------------------------
// Отрисовать индикатор связи
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

    t0 = get_sec_ticks() / 10;	// получили время за 10 секунд

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
		sprintf(buf, "Ошибки в обмене (%d) за последние 10 секунд", err.now);
	    else
		sprintf(buf, "Exchange errors (%d) for last 10 sec", err.now);
	    LogOut(buf);
	}
    }
}

//---------------------------------------------------------------------------
// Если три первых байт статуса меняются - вывести их!
void __fastcall TfrmMain::ShowStatusIfChange(void *v, u8 show)
{
    DEV_STATUS_STRUCT *status;
    u8 b0, b1, b2, b4;

    enable_log = true;
    UnhideButtons();

    if (v != NULL) {
	char str[128];
	status = (DEV_STATUS_STRUCT *) v;

	// какой генератор у нас?
	if (status->quartz == 8192000) {
	    quartz_freq = 8.192;
	    if (lang == lang_rus)
		lbStatus2_4->Caption = "Ошибка генератора 8.192 МГц";
	    else
		lbStatus2_4->Caption = "Generator 8.192 MHz error";

	    lbStatus2_5->Visible = false;
	} else {
	    quartz_freq = 19.2;
	    if (lang == lang_rus)
		lbStatus2_4->Caption = "Ошибка генератора 19.2 МГц";
	    else
		lbStatus2_4->Caption = "Generator 19.2 MHz error";

	    lbStatus2_5->Visible = true;
	}


	// Частота генератора, периферии и ядра
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


	// Главный статус
	if (show & 0x01) {
	    b0 = status->st_main;

	    //------------- время
	    if (b0 & 0x01) {
		if (lang == lang_rus)
		    LogOut("Нет времени RTC!");
		else
		    LogOut("RTC time is not setup!");
	    } else {
		if (lang == lang_rus)
		    LogOut("Время RTC OK!");
		else
		    LogOut("RTC time OK!");
	    }


	    //------------- ошибка в команде. Только ошыбку писать!
	    if (b0 & 0x04) {
		if (lang == lang_rus)
		    LogOut("Ошибка в команде!");
		else
		    LogOut("Command error!");
	    }
	    //------------- Неиспраность АЦП!
	    if (b0 & 16) {
		if (lang == lang_rus)
		    LogOut("Неисправность АЦП регистратора!");
		else
		    LogOut("Recorder ADC fault!");
	    }
	    //------------- Переполнение памяти! Только ошибка
	    if (b0 & 0x20) {
		if (lang == lang_rus)
		    LogOut("Переполнение памяти!");
		else
		    LogOut("Memory overflow!");
	    }
	    //------------- Осц
	    if (!(b0 & 0x40)) {
		if (lang == lang_rus)
		    LogOut("Осцилограф включен!");
		else
		    LogOut("Oscilloscope is on!");
	    } else {
		if (lang == lang_rus)
		    LogOut("Осцилограф выключен!");
		else
		    LogOut("Oscilloscope is off!");
	    }
	}
	// Самотестирование
	if (show & 0x02) {
	    b1 = status->st_test0;

	    //------------- RTC
	    if (b1 & 0x01) {
		if (lang == lang_rus)
		    LogOut("Ошибка RTC, нет данных с RTC или часы отстают!");
		else
		    LogOut("RTC error, no data from RTC or RTC delays!");
	    } else {
		LogOut("RTC OK!");
	    }

	    //------------- датчик давления
	    if (b1 & 0x02) {
		if (lang == lang_rus)
		    LogOut("Ошибка датчика давления, нет данных с датчика давления!");
		else
		    LogOut("Pressure sensor error, no data from sensor!");
	    } else {
		if (lang == lang_rus)
		    LogOut("Датчик давления OK!");
		else
		    LogOut("Pressure sensor OK!");
	    }

	    //------------- компас
	    if (b1 & 0x04) {
		if (lang == lang_rus)
		    LogOut("Ошибка акселерометра!");
		else
		    LogOut("Accelerometer error!");
	    } else {
		if (lang == lang_rus)
		    LogOut("Акселерометр OK!");
		else
		    LogOut("Accelerometer OK!");
	    }

	    //------------- модем
	    if (b1 & 0x08) {
		if (lang == lang_rus)
		    LogOut("Ошибка компаса!");
		else
		    LogOut("Compass error!");
	    } else {
		if (lang == lang_rus)
		    LogOut("Компас OK!");
		else
		    LogOut("Compass OK!");
	    }


	    //------------- GPS
	    if (b1 & 0x10) {
		if (lang == lang_rus)
		    LogOut("Ошибка модуля GPS, или модуль GPS не тестировался: нет строки NMEA!");
		else
		    LogOut("GPS module error: no NMEA string!");

	    } else {
		LogOut("GPS OK!");
	    }


	    //------------- EEPROM
	    if (b1 & 0x20) {
		if (lang == lang_rus)
		    LogOut("Ошибка EEPROM!");
		else
		    LogOut("EEPROM error!");
	    } else {
		LogOut("EEPROM OK!");
	    }


	    //------------- Карта SD
	    if (b1 & 0x40) {
		if (lang == lang_rus)
		    LogOut("Ошибка SD карты, проверьте файловую систему на SD карте!");
		else
		    LogOut("SD card error, check filesystem on SD!");
	    } else {
		if (lang == lang_rus)
		    LogOut("SD карта OK!");
		else
		    LogOut("SD card OK!");
	    }

	    //------------- Flash
	    if (b1 & 0x80) {
		if (lang == lang_rus)
		    LogOut("Ошибка FLASH!");
		else
		    LogOut("FLASH error!");
	    } else {
		LogOut("FLASH OK!");
	    }
	}
//----------
	// Устройства
	if (show & 0x04) {
	    b2 = status->st_test1;


	    //------------- Данные в eeprom
	    if (b2 & 0x08) {
		if (lang == lang_rus)
		    LogOut("Не коректные данные в EEPROM!");
		else
		    LogOut("EEPROM data is not correct!");

	    } else {
		if (lang == lang_rus)
		    LogOut("Данные в EEPROM OK!");
		else
		    LogOut("EEPROM data OK!");
	    }



	    //------------- 19.2
	    if (b2 & 0x10) {
		LogOut("Ошибка генератора 19.2 МГц: генератор не подстраивается!");
	    } else {
		LogOut("Генератор 19.2 МГц ОК!");
	    }


	    //------------- 4,096
	    if (b2 & 0x20) {
		LogOut("Ошибка генератора 4.096 МГц: генератор не подстраивается!!");
	    } else {
		LogOut("Генератор 4.096 МГц ОК!");
	    }


	    //------------- PPS
	    if (b2 & 0x40) {
		LogOut("Нет импульсов PPS на входе!");
	    } else {
		LogOut("Импульсы PPS на входе OK!");
	    }

	    //------------- TIM3
	    if (b2 & 0x80) {
		LogOut("Ошибка Таймера 3!");
	    } else {
		LogOut("Таймер3 OK!");
	    }
	}
	if (show & 8) {
	    b4 = status->st_reset;
	    String s;
	    if (lang == lang_rus) {
		s = "Причина предыдущего сброса: ";

		if (b4 & 1)
		    s += "Выключение питания";
		else if (b4 & 2)
		    s += "Внешний сброс";
		else if (b4 & 4)
		    s += "Снижение питания";
		else if (b4 & 8)
		    s += "WDT сброс";
		else if (b4 & 16)
		    s += "Длительное отсутсвие связи (> 10 мин)";
		else if (b4 & 32)
		    s += "Непредвиденный сброс";
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
	    LogOut("Тестирование завершено!");
	else
	    LogOut("SelfTest finished!");
    }
}

//---------------------------------------------------------------------------
// Вывести статус!
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
//              Главный cтатуc-0 байт
////////////////////////////////////////////////////////////////////////////////
	if (byte & 1) {
	    lbStatus0_0->Font->Color = clRed;
	} else {
	    lbStatus0_0->Font->Color = clGray;
	}
	// Ошибка модема
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

	// GNS неисправен
	if (byte & 16) {
	    lbStatus0_4->Font->Color = clRed;
	} else {
	    lbStatus0_4->Font->Color = clGray;
	}

	// Переполнение памяти
	if (byte & 32) {
	    lbStatus0_5->Font->Color = clRed;
	} else {
	    lbStatus0_5->Font->Color = clGray;
	}

	// GNS включен во время измерений
	if (!(byte & 0x40)) {
	    lbStatus0_6->Font->Color = clGreen;
	    btnStartThread->ImageIndex = 6;
	    ButtonStateInStart(false);
	} else {
	    lbStatus0_6->Font->Color = clGray;
	    btnStartThread->ImageIndex = 5;
	    ButtonStateInStart(true);
	}

	// Идет самотестирование - мигать
	if (byte & 128) {
	    // Моргать надписью
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

	// Тест прошел
	if (test_result.tick > 0 && test_result.t0 == 0) {
	    test_result.tick = 0;
	    ShowStatusIfChange(status, 1 + 2 + 3);
	}
////////////////////////////////////////////////////////////////////////////////
//              Самотестирование 0
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

	// компас + аккселерометр
	if (byte & 4) {
	    lbStatus1_2->Font->Color = clRed;
	} else {
	    lbStatus1_2->Font->Color = clGray;
	}

	// Ошибка модема только в режиме наладки
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
//      Прочие устройства
////////////////////////////////////////////////////////////////////////////////
	byte = status->st_test1;
	if (byte & 0x01) {	// GPS включен / выключен
	    lbStatus2_0->Font->Color = clGreen;
	} else {
	    if (t0 % 4 == 0) {
		frmMain->lbGpsTime->Caption = "";
		frmMain->lbGpsLat->Caption = "";
		frmMain->lbGpsLon->Caption = "";
	    }
	    lbStatus2_0->Font->Color = clGray;
	}


	if (byte & 0x02) {	// Модем включен / выключен
	    lbStatus2_1->Font->Color = clGreen;
	} else {
	    lbStatus2_1->Font->Color = clGray;
	    SetModemLights(false);
	}

	if (byte & 0x04) {	// Идет тест модема
	    lbStatus2_2->Font->Color = clGreen;
	    test_modem.t0 = 1;
	    test_modem.tick++;
	} else {
	    test_modem.t0 = 0;
	    lbStatus2_2->Font->Color = clGray;
	}

	// Тест модема прошел
	if (test_modem.tick && test_modem.t0 == 0) {
	    test_modem.tick = 0;
	    ShowTestModem(status);
	}
	// Тест EEPROM
	if (byte & 0x08) {
	    lbStatus2_3->Font->Color = clRed;
	} else {
	    lbStatus2_3->Font->Color = clGray;
	}

	if (!first_run) {	// в первом запускке не показывать
	    // Ген. 19 МГц
	    if (byte & 0x10) {
		lbStatus2_4->Font->Color = clRed;
	    } else {
		lbStatus2_4->Font->Color = clGray;
	    }

	    // Ген. 4 МГц
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
//                      АЦП
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

///////////////////////// Включенные реле и устройства
	byte = status->ports;

	if (byte & 0x01) {	//GPS включен
	    //     lbRele0->Font->Color = clGreen;
	    btnGpsOn->ImageIndex = 17;

	    if (lang == lang_rus)
		btnGpsOn->Hint = "Модуль GPS вЫключить";
	    else
		btnGpsOn->Hint = "GPS OFF";

	} else {
	    //           lbRele0->Font->Color = clGray;
	    btnGpsOn->ImageIndex = 16;

	    if (lang == lang_rus)
		btnGpsOn->Hint = "Модуль GPS включить";
	    else
		btnGpsOn->Hint = "GPS ON";

	}

	if (status->st_test1 & 0x4) {	// идет тестирование
	    btnModemOnOff->Enabled = false;
	} else if (pcChangeMode->TabIndex != 1) {
	    btnModemOnOff->Enabled = true;
	    if (byte & 0x02) {	//Модем
		lbRele1->Font->Color = clGreen;	// Включен
		btnModemOnOff->ImageIndex = 8;

		if (lang == lang_rus)
		    btnModemOnOff->Hint = "Модем вЫключить";
		else
		    btnModemOnOff->Hint = "Modem OFF";

	    } else {
		lbRele1->Font->Color = clGray;	//вЫключен
		btnModemOnOff->ImageIndex = 7;

		if (lang == lang_rus)
		    btnModemOnOff->Hint = "Модем включить";
		else
		    btnModemOnOff->Hint = "Modem ON";

	    }
	}
	// Пережиг
	if (byte & 0x04) {	// Пережыг
	    if (t0 % 2 == 0)
		lbRele2->Font->Color = clRed;
	    else
		lbRele2->Font->Color = clGray;

	    btnBurn->ImageIndex = 9;

	    if (lang == lang_rus)
		btnBurn->Hint = "Выключить пережиг!";
	    else
		btnBurn->Hint = "Burning wire voltage OFF";

	} else {
	    lbRele2->Font->Color = clGray;
	    btnBurn->ImageIndex = 10;

	    if (lang == lang_rus)
		btnBurn->Hint = "Включить пережиг!";
	    else
		btnBurn->Hint = "Burning wire voltage ON";

	}

	if (byte & 0x08) {	// Аналоговое питание
	    lbRele3->Font->Color = clGreen;
	} else {
	    lbRele3->Font->Color = clGray;
	}

	if (byte & 0x10) {	// Селектор на COM
	    lbRele4->Font->Color = clGreen;
	} else {
	    lbRele4->Font->Color = clGray;
	}

	if (byte & 0x20) {	// Селектор на модем
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
	// Сброс
	byte = status->st_reset;

	// Главный cтатуc-0 байт
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
	// U питания-ниже и выше на 20% (от 12 вольт)
	volt = status->regpwr_volt;
	pnSupplyV->Caption = FloatToStrF(volt / 1000.0, ffFixed, 5, 1);
	if (volt < 7500 && !bEndThread && t0 != t1) {
	    pnSupplyV->Color = clRed;
	    pnSupplyV->Font->Color = clYellow;
	    if (t1 % 60 == 0) {
		if (lang == lang_rus)
		    LogOut("Внимание! Напряжение питания менее 7.5 В!");
		else
		    LogOut("Warning! Power supply voltage is less than 7.5 V!");
	    }
	} else if (volt > 16000 && !bEndThread && t0 != t1) {
	    pnSupplyV->Color = clRed;
	    pnSupplyV->Font->Color = clYellow;
	    if (t1 % 60 == 0) {
		if (lang == lang_rus)
		    LogOut("Внимание! Напряжение питания более 15.0 В!");
		else
		    LogOut("Warning! Power supply voltage is more than 15.0 V!");
	    }
	} else {
	    pnSupplyV->Color = clBtnFace;
	    pnSupplyV->Font->Color = clWindowText;
	}

	amp = status->ireg_sense;	// I питания
	pnSupplyA->Caption = IntToStr(amp);

	// U burn-ниже и выше на 30% (от 12 вольт) - пишем один раз!
	volt = status->burn_volt;
	pnBurnV->Caption = FloatToStrF((float) volt / 1000.0, ffFixed, 5, 1);
	if (volt < 8500 && !bEndThread && t0 != t1) {
	    pnBurnV->Color = clRed;
	    pnBurnV->Font->Color = clYellow;

	    if (tb == false) {
		if (lang == lang_rus)
		    LogOut("Внимание! Напряжение пережига менее 8.5 В!");
		else
		    LogOut("Warning! Burn wire voltage is less than 8.5 V!");
		tb = true;
	    }
	} else if (volt > 16000 && !bEndThread && t0 != t1) {
	    pnBurnV->Color = clRed;
	    pnBurnV->Font->Color = clYellow;

	    if (tb == false) {
		if (lang == lang_rus)
		    LogOut("Внимание! Напряжение пережига более 16.0 В!");
		else
		    LogOut("Warning! Burn wire voltage is more than 16.0 V!");
		tb = true;
	    }
	} else {
	    pnBurnV->Color = clBtnFace;
	    pnBurnV->Font->Color = clWindowText;

	    if (volt > 10000 && volt < 18000 & tb == true) {
		if (lang == lang_rus)
		    LogOut("Напряжение пережига в норме!");
		else
		    LogOut("Burn wire voltage is normal!");
		tb = false;
	    }
	}


	amp = status->iburn_sense;	// I burn
	if (volt < 4000 || t0 != t1 || /*abs */ (amp) <= 3) {	//не отображать если < 4В (предыдущий)
	    pnBurnA->Caption = "0";
	} else {
	    pnBurnA->Caption = IntToStr(amp);
	}

	// Если номер платы > 7
	if (port_set[cbPortName->ItemIndex].board == 'B' || port_set[cbPortName->ItemIndex].board == 'C') {
	    volt = status->am_power_volt;
	    if (volt < 7000 && !bEndThread && t0 != t1) {
		pnModemV->Caption = FloatToStrF((float) volt / 1000.0, ffFixed, 5, 1);
		pnModemV->Color = clRed;
		pnModemV->Font->Color = clYellow;

		if (tm == false) {
		    if (lang == lang_rus)
			LogOut("Внимание! Напряжение питания акустического модема менее 7.0 В!");
		    else
			LogOut("Warning! Modem power supply voltage is less than 7.0 V!");
		    tm = true;
		}

	    } else if (volt > 16000 && !bEndThread && t0 != t1) {
		pnModemV->Caption = FloatToStrF((float) volt / 1000.0, ffFixed, 5, 1);
		pnModemV->Color = clRed;
		pnModemV->Font->Color = clYellow;
		if (lang == lang_rus)
		    LogOut("Внимание! Напряжение питания акустического модема более 14.0 В!");
		else
		    LogOut("Warning! Modem power supply voltage is more than 14.0 V!");

	    } else {
		pnModemV->Caption = FloatToStrF((float) volt / 1000.0, ffFixed, 5, 1);
		pnModemV->Color = clBtnFace;
		pnModemV->Font->Color = clWindowText;

		if (volt > 7000 && volt < 16000 & tm == true) {
		    if (lang == lang_rus)
			LogOut("Напряжение питания акустического модема в норме!");
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

	// Моргать надписью
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
	// внешний пережыг
	pnBurnExtV->Caption = FloatToStrF((float) volt / 1000.0, ffFixed, 5, 1);

	// температура 1
	pnTemp1->Caption = FloatToStrF(status->temper1 / 10.0, ffFixed, 3, 1);

	// давление
	pnPressure->Caption = FloatToStrF(status->press / 1000.0, ffFixed, 5, 1);


//////////////////////////////////////////////////////////////////////////////////////////
//                      углы и температура 0
//////////////////////////////////////////////////////////////////////////////////////////
	p = status->pitch / 10.0;
	r = status->roll / 10.0;
	h = status->head / 10.0;
	T = status->temper0 / 10.0;

	// ошибка компаса
	if (status->st_test0 & 0x08) {
	    pnPitch->Caption = "n/a";
	    pnRoll->Caption = "n/a";
	    pnTemp0->Caption = "n/a";	// температура 0
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

	    pnTemp0->Caption = FloatToStrF(T, ffFixed, 3, 1);	// температура 0
	    pnTemp0->Color = clBtnFace;
	    pnTemp0->Font->Color = clWindowText;

	}

	// Пишем в файл раз в минуту
	if (t0 % 60 == 0 && t0 != t1)
	    WriteDataToFile(status);


	// Смотрим, в каком мы режиме сейчас находимся
	// 1 - осцилограф
	// 2 - режим оператора
	// 3 - режим наладки
	// 4 - режим тестирования или тестирования модема
	if (!(status->st_main & 0x80)) {	// если нету тестирования
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

	// 1 - Модем выключен
	// 2 - Модем включен + тест модема
	// 3 - Модем включен - тест модема
	if (status->st_test1 & 0x02) {
	    if (!(status->st_test1 & 0x04)) {	// нет теста и нет ошибки
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
	    TimeGNS110(status->gns_rtc);	/* Время RTC прибора */
#endif
	}


	i++;
	t1 = t0;


    } else {			// Обнулим все
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

	// Самотестирование
	lbStatus1_0->Font->Color = clGray;
	lbStatus1_1->Font->Color = clGray;
	lbStatus1_2->Font->Color = clGray;
	lbStatus1_3->Font->Color = clGray;
	lbStatus1_4->Font->Color = clGray;
	lbStatus1_5->Font->Color = clGray;
	lbStatus1_6->Font->Color = clGray;
	lbStatus1_7->Font->Color = clGray;

	// Прочие устройства
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


	// Причина сброса
	lbStatusReset_0->Font->Color = clGray;
	lbStatusReset_1->Font->Color = clGray;
	lbStatusReset_2->Font->Color = clGray;
	lbStatusReset_3->Font->Color = clGray;
	lbStatusReset_4->Font->Color = clGray;
	lbStatusReset_5->Font->Color = clGray;

	// версия+время работы+время GNS
	lbTimeGNS110->Caption = "";

	if (lang == lang_rus)
	    sbInfo->Panels->Items[1]->Text = "Время работы в текущем сеансе";
	else
	    sbInfo->Panels->Items[1]->Text = "Working time for the current connection";

	// среда
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

	// Подстказки
/*
	btnBurn->Hint = "Пережиг вкл/выкл";
	btnModemOnOff->Hint = "Модем вкл/выкл";
	btnGpsOn->Hint = "Модуль GPS вкл/выкл";
	btnStartThread->Hint = "Старт/Стоп измерения";
*/
    }
}

//---------------------------------------------------------------------------
// записать данные в файл
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
	    sbInfo->Panels->Items[2]->Text = "Измерения (чч:мм)   " + String(str);
	else
	    sbInfo->Panels->Items[2]->Text = "Acqusition (hh:mm)   " + String(str);

	m = ((u32) wt->time_cmd / 60) % 60;
	h = ((u32) wt->time_cmd / 3600) % 999;
	sprintf(str, "%03d:%02d", h, m);
	if (lang == lang_rus)
	    sbInfo->Panels->Items[3]->Text = "Режим PC (чч:мм)   " + String(str);
	else
	    sbInfo->Panels->Items[3]->Text = "PC mode (hh:mm)   " + String(str);

	m = ((u32) wt->time_modem / 60) % 60;
	h = ((u32) wt->time_modem / 3600) % 999;
	sprintf(str, "%03d:%02d", h, m);
	if (lang == lang_rus)
	    sbInfo->Panels->Items[4]->Text = "Модем (чч:мм)   " + String(str);
	else
	    sbInfo->Panels->Items[4]->Text = "Modem (hh:mm)   " + String(str);

    } else {
	if (lang == lang_rus) {
	    sbInfo->Panels->Items[2]->Text = "Измерения (чч:мм)";
	    sbInfo->Panels->Items[3]->Text = "Режим PC (чч:мм)";
	    sbInfo->Panels->Items[4]->Text = "Модем (чч:мм)";
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

    PortGetXchgCounts(&my_count);	//получить акеты обмена
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
	    sbInfo->Panels->Items[1]->Text = "Время работы в текущем сеансе: " + String(str);
	else
	    sbInfo->Panels->Items[1]->Text = "Working time for the current connection: " + String(str);

	pbLinkQuality->Visible = true;

    } else {			// Обнулим все
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
//           Команды, отвечающие на сообщения SendMessage,PostMessage
////////////////////////////////////////////////////////////////////////////////
// Вывести счетчики обмена свои и gns110
// Качество связи индикатором
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
// Принимаем сообщение и отрисовываем статус
void __fastcall TfrmMain::CMShowStatus(TMessage & Message)
{
    ShowStatus((void *) Message.WParam);
}

//---------------------------------------------------------------------------
// Нет данных - сообщение от читающего потока
void __fastcall TfrmMain::CMNoData(TMessage & Message)
{
    // Ждем, что порт выключен
    bEndThread = true;
    TerminateAllThreads();
    DisableControl();
}

//---------------------------------------------------------------------------
// Включить или выключить фильтр
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
// Светлое время суток - запретить неправильные числа для времени
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
// Получить номер модема из буфера
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
// Показывать номер модема
void __fastcall TfrmMain::cbModemNumClick(TObject * Sender)
{
    // нет модема
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

            // сравнить строки без учета регистра
	if ((strcmpi(FSName, "FAT32") != 0) && (strcmpi(FSName, "ExFAT") !=0 ))
	  	  break;

	res = true;
    } while (0);
    return res;
}

//---------------------------------------------------------------------------
// Изменить время подъема со дна
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
// Изменить длительность пережига
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
// Изменить длительность пережига   - 4 цыфры
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
// Длительность всплытия
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
// Номер модема
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
// Позиция установки
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
// Включить радио
void __fastcall TfrmMain::btnRadioOnClick(TObject * Sender)
{
    ltRadioOnOff->State = false;
    WriteCommandThread *thread;

    if (modem_inner_state.radio) {
	thread = new WriteCommandThread(RadioOff, &modem, false, true);
	btnRadioOn->Kind = bkRetry;
	if (lang == lang_rus)
	    btnRadioOn->Caption = "Вкл";
	else
	    btnRadioOn->Caption = "On";
    } else {
	thread = new WriteCommandThread(RadioOn, &modem, false, true);
	btnRadioOn->Kind = bkAbort;
	if (lang == lang_rus)
	    btnRadioOn->Caption = "Выкл";
	else
	    btnRadioOn->Caption = "Off";

    }

    modem_inner_state.radio = !modem_inner_state.radio;
    thread->FreeOnTerminate = true;
    thread->Resume();
}

//---------------------------------------------------------------------------
// Включить лампу
void __fastcall TfrmMain::btnLampOnClick(TObject * Sender)
{
    ltLampOnOff->State = false;
    WriteCommandThread *thread;

    if (modem_inner_state.lamp) {	// включено
	thread = new WriteCommandThread(LampOff, &modem, false, true);
	btnLampOn->Kind = bkRetry;
	if (lang == lang_rus)
	    btnLampOn->Caption = "Вкл";
	else
	    btnLampOn->Caption = "On";
    } else {
	thread = new WriteCommandThread(LampOn, &modem, false, true);
	btnLampOn->Kind = bkAbort;

	if (lang == lang_rus)
	    btnLampOn->Caption = "Выкл";
	else
	    btnLampOn->Caption = "Off";

    }
    modem_inner_state.lamp = !modem_inner_state.lamp;
    thread->FreeOnTerminate = true;
    thread->Resume();
}

//---------------------------------------------------------------------------
//Пережиг вкл / выкл
void __fastcall TfrmMain::btnBurnCmdOnClick(TObject * Sender)
{
    ltBurnCmdOnOff->State = false;
    WriteCommandThread *thread;

    if (modem_inner_state.burn) {	// если включено - выключить
	thread = new WriteCommandThread(BurnCmdOff, &modem, false, true);
	btnBurnCmdOn->Kind = bkRetry;
	if (lang == lang_rus)
	    btnBurnCmdOn->Caption = "Вкл";
	else
	    btnBurnCmdOn->Caption = "On";
    } else {			// включить
	thread = new WriteCommandThread(BurnCmdOn, &modem, false, true);
	btnBurnCmdOn->Kind = bkAbort;
	if (lang == lang_rus)
	    btnBurnCmdOn->Caption = "Выкл";
	else
	    btnBurnCmdOn->Caption = "Off";

    }
    modem_inner_state.burn = !modem_inner_state.burn;
    thread->FreeOnTerminate = true;
    thread->Resume();
}

//---------------------------------------------------------------------------
// Послать пинг:  Пинг 13  Пинг 9 Пинг 11
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
//  Сбросить Время работы
void __fastcall TfrmMain::btnResetWorkTimeClick(TObject * Sender)
{
    WriteCommandThread *thread;
    thread = new WriteCommandThread(SetWorkTime, NULL, false, false);
    thread->WaitFor();
    delete thread;
    big_timer = 500;
}

//---------------------------------------------------------------------------
// Не показывать дополнительные параметры
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
// показаьт дополнительные параметры
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
// Открыть логи
void __fastcall TfrmMain::menuOpenLogsClick(TObject * Sender)
{
    String name;

    // Директориея, где содержаться лог-файлы
    odOpenLogs->InitialDir = ExtractFilePath(Application->ExeName) + "LOGS";

    // Чтобы лишних скобок не ставить
    if (odOpenLogs->Execute() == false)
	return;

    if (!FileExists(odOpenLogs->FileName))
	return;

    name = odOpenLogs->FileName;
    ShellExecute(this->Handle, "open", "notepad.exe", name.c_str(), NULL, SW_SHOWNORMAL);
}

//---------------------------------------------------------------------------
// Установить рабочую директорию/диск для диалогов
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

    // Перебираем все диски
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

		// Если "устройство не готово - то только в лог!"
		if (dwError != ERROR_NOT_READY) {
		    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
				  NULL, dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) & lpMsgBuf, 0, NULL);
		    sprintf(str, "DISK: %s. %s", drives[i], lpMsgBuf);
		    ERROR_BOX(str);
		    LogOut(str);
		}
	    } else {
		// Если метки тома совпадают
		if (strncmp(drv_name_str, met.c_str(), 7) == 0) {
		    // По адресу будет буква тома
		    memcpy(&disk, drives[i], 1);
		    dcbDisk->TextCase = dcbDisk->TextCase;
		    dcbDisk->Drive = disk;
		    odParamFile->InitialDir = drives[i];
		    sdParamFile->InitialDir = drives[i];
		    sprintf(drv_name_str, "Disk %c: attached on %s", disk, met.c_str());
		    LogOut(drv_name_str);

#if 0
		    // вызывать поток с параметром suspended
		    //иначе потом может закончица до вызова FreeOnTerminate
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
// Кнопки в режыме осцылографа
void __fastcall TfrmMain::OscilMenu(TObject * Sender)
{
    btnReset->Enabled = true;	// сброс всегда
    btnPowerOff->Enabled = true;	// выкл всегда
    btnStartThread->Enabled = true;	// старт / стоп всегда

    // Все остальные-выкл
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
// Кнопки в режыме оператора
void __fastcall TfrmMain::OperMenu(TObject * Sender)
{
    btnReset->Enabled = true;	// сброс всегда
    btnPowerOff->Enabled = true;	// выкл всегда
    btnTest->Enabled = true;	// тестирование всегда
    btnSync->Enabled = true;	// синхронизация всегда

    // Все остальные-выкл
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
// Кнопки в режыме наладки
void __fastcall TfrmMain::CtrlMenu(TObject * Sender)
{
    // Все кнопки, за исколчением старт
    btnReset->Enabled = true;	// сброс всегда
    btnPowerOff->Enabled = true;	// выкл всегда
    btnTest->Enabled = true;	// тестирование всегда
    btnSync->Enabled = true;	// синхронизация всегда
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
// Все кнопки выключены
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
// Тестирование
void __fastcall TfrmMain::TestMenu(TObject * Sender)
{
    btnReset->Enabled = true;	// сброс всегда
    btnPowerOff->Enabled = true;	// выкл всегда

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
    enable_log = false;		// нельзя писать
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
// Убирать данные с элементов для модема
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
// Заслать подтверждения для команд
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
// Проверка параметров на допустимость
void __fastcall TfrmMain::SpeedButton1Click(TObject * Sender)
{
    int t0;
    param_file_struct param;
    char buf1[32], buf2[32];
    char str[256];
    SYSTEMTIME st;

    t0 = time(NULL);

    // Определим время старта
    dtStartDate->GetTextBuf(buf1, 10);
    dtStartTime->GetTextBuf(buf2, 10);
    param.start_time = bufs_to_st(buf1, buf2, &st);

    // Определим время окончания
    dtFinishDate->GetTextBuf(buf1, 10);
    dtFinishTime->GetTextBuf(buf2, 10);
    param.finish_time = bufs_to_st(buf1, buf2, &st);

    // Определим время начала пережыга
    dtBurnDate->GetTextBuf(buf1, 10);
    dtBurnTime->GetTextBuf(buf2, 10);
    param.burn_time = bufs_to_st(buf1, buf2, &st);

    // Длительность пережыга
    edBurnTime->GetTextBuf(buf1, 4);
    param.releburn_time = atoi(buf1);

    //Длительность всплытия
    mePopupLen->GetTextBuf(buf1, 5);
    param.popup_len = atoi(buf1) * 60;

    // номер модема
    edModemNum->GetTextBuf(buf1, 5);
    param.modem_num = atoi(buf1);

    // Время авраийного всплытия
    dtAm3PopupDate->GetTextBuf(buf1, 10);
    dtAm3PopupTime->GetTextBuf(buf2, 10);
    param.am3_popup_time = bufs_to_st(buf1, buf2, &st);

    // Сравниваем с временем
    if ((int) param.finish_time - t0 < 300 && !param.const_reg_flag) {
	sec_to_str(param.finish_time, buf1);
	sec_to_str(t0, buf2);
	if (lang == lang_rus)
	    sprintf(str, "WARNING: Время окончания (%s) должно быть как минимум на 5 минут больше текущего времени (%s)!", buf1, buf2);
	else
	    sprintf(str, "WARNING: End of recording (%s) must be at least 5 minutes more than current time(%s)!", buf1, buf2);
	LogOut(str);
    }

    if ((int) param.finish_time - (int) param.start_time < RECORD_TIME && !param.const_reg_flag) {
	sec_to_str(param.finish_time, buf1);
	sec_to_str(param.start_time, buf2);

	if (lang == lang_rus)
	    sprintf(str, "WARNING: Время записи менее 5-ти минут! начало записи: (%s), окончание записи: (%s)", buf1, buf2);
	else
	    sprintf(str, "WARNING: Record time is less than 5 minutes! start time: (%s), finish time (%s)", buf1, buf2);


	LogOut(str);
    }

    if ((int) param.burn_time - (int) param.finish_time < TIME_BURN_AFTER_FINISH && !param.const_reg_flag) {
	sec_to_str(param.burn_time, buf1);
	sec_to_str(param.finish_time, buf2);
	if (lang == lang_rus)
	    sprintf(str, "WARNING: Время начала пережига (%s) должно быть на 2 секунды позже времени окончания (%s)!", buf1, buf2);
	else
	    sprintf(str, "WARNING: Burn wire time (%s) must be on 2 seconds later than end of recording (%s)!", buf1, buf2);
	LogOut(str);
    } else if ((int) param.burn_time - t0 < RECORD_TIME) {
	sec_to_str(param.burn_time, buf1);
	sec_to_str(param.finish_time, buf2);
	if (lang == lang_rus)
	    sprintf(str, "WARNING: нет времени на запись при включенной опции \"Постоянная регистрация\"\n");
	else
	    sprintf(str, "WARNING: no time for recording when option is ON \"Constant recoding\"\n");
	LogOut(str);
    }

    if ((int) param.releburn_time < (RELEBURN_TIME_AIRLINK / 30)) {
	if (lang == lang_rus)
	    sprintf(str, "WARNING: Длительность пережига (%d) должно быть более 2 секунд!", param.releburn_time);
	else
	    sprintf(str, "WARNING: Burn wire time (%d) must be more than 2 seconds!", param.releburn_time);
	LogOut(str);
    }

    if ((int) param.popup_len < POPUP_DURATION_AIRLINK * 60) {
	if (lang == lang_rus)
	    sprintf(str, "WARNING: Длительность всплытия (%d мин) должна быть более 1 минуты!", param.popup_len);
	else
	    sprintf(str, "WARNING: Popup time (%d min) must be more than 1 minute!", param.popup_len);
	LogOut(str);
    }
    // модем
    if ((int) param.modem_num >= 0 && (int) param.am3_popup_time < t0 + 60) {
	sec_to_str(param.am3_popup_time, buf1);
	sec_to_str(t0, buf2);
	if (lang == lang_rus)
	    sprintf(str, "WARNING: Время аварийного всплытия (%s) должно быть позже текущего времени (%s)!", buf1, buf2);
	else
	    sprintf(str, "WARNING: Modem alarm time (%s) must be later than current time (%s)!", buf1, buf2);
	LogOut(str);
    }
}

//---------------------------------------------------------------------------
// Проверка параметров на допустимость
void __fastcall TfrmMain::btnCheckParamsClick(TObject * Sender)
{
    // проверить
    String disk;
    CheckFileThread *thread;
    disk = String(dcbDisk->Drive) + ":";

    // вызывать поток с параметром suspended
    //иначе потом может закончица до вызова FreeOnTerminate
    thread = new CheckFileThread(disk, &param_struct, true);
    thread->FreeOnTerminate = true;
    thread->Resume();
}

//---------------------------------------------------------------------------
// Пересчитаем сколько это страниц
// Выводим, в зависимости от частоты!
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

    freq_s = (1 << pack->adc) * 62.5;	/* частота */

    if (lang = lang_rus)
	slsDisplay->Title->Text = "АЦП " + IntToStr((int) freq_s) + " Гц";
    else
	slsDisplay->Title->Text = "ADC " + IntToStr((int) freq_s) + " Hz";


    // Поменять Z и X
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
// Число точек на экране осцилографа
void __fastcall TfrmMain::cbTimeLimitChange(TObject * Sender)
{
    int points;
    int net;

    // число точек на экране
    points =cbTimeLimit->ItemIndex == 0 ? 1000 : cbTimeLimit->ItemIndex == 1 ? 2000 : cbTimeLimit->ItemIndex == 2 ? 5000 : cbTimeLimit->ItemIndex ==
	3 ? 10000 : 20000;

    slsDisplay->SizeLimit = points;
}

//---------------------------------------------------------------------------
// Теперь приявязать к времени диcкретизации!
// первести секунды в часы минуты секунды
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
// Изменить язык интерфейса
void __fastcall TfrmMain::ChangeLangID(void)
{
    if (lang == lang_rus) {
	// Верхние кнопари
	btnReset->Hint = "Перезагрузка";
	btnPowerOff->Hint = "Выключить";
	btnTest->Hint = "Самотестирование";
	btnModemOnOff->Hint = "Модем вкл/выкл";
	btnModemRequest->Hint = "Опросить модем";
	btnModemCommand->Hint = "Записать в модем";
	btnBurn->Hint = "Пережиг вкл/выкл";
	btnGpsOn->Hint = "GPS вкл/выкл";
	btnStartThread->Hint = "Осциллограф Старт/Стоп";
	btnSync->Hint = "Синхронизация со временем ПК";
	btnConst->Hint = "Записать константы";
	btnSetName->Hint = "Ввести номер станции";
	btnSetToZero->Hint = "Записать исходные константы в EEPROM";
	btnResetWorkTime->Hint = "Сбросить время работы устройств";

	// Меню
	MenuFile->Caption = "Ф&айл";
	menuOpenLogs->Caption = "Открыть файл логов";
	menuOpen->Caption = "Открыть файл параметров";
	menuSave->Caption = "Записать файл параметров";
	menu10Min->Caption = "Создать файл 10-ти минутной записи";
	menu60Min->Caption = "Создать файл часовой записи";
	menu1Day->Caption = "Создать файл суточной записи";
	menu1Week->Caption = "Создать файл недельной записи";
	menu1Month->Caption = "Создать файл месячной записи";
	menuExit->Caption = "Выход";
	menuCtrl->Caption = "Управл&ение";
	menuOperator->Caption = "Режим оператора";
	menuAdjust->Caption = "Режим наладки";
	menuLang->Caption = "Язык";
	menuRus->Caption = "Русский";
	menuEng->Caption = "Английский";
	menuRus->Checked = true;
	menuHelp->Caption = "Сп&равка";
	menuAbout->Caption = "О программе";

	// Конфиругация оборубования
	pnConfig1->Caption = "Конфигурация оборудования";

	// Подключенная станция
	gbParams->Caption = "Подключенная станция";
	sbRunModule->Hint = "Подключение к станции/отключение от станции";

	// Время координаты
	gbTimes->Caption = "Время / Координаты GPS";
	pnUTCTime->Caption = "Время PC*";
	pnTimeGNS110->Caption = "Время GNS";
	pnGpsTime->Caption = "Время GPS";
	pnGpsLat->Caption = "Широта";
	pnGpsLon->Caption = "Долгота";

	// Параметры станции
	gbEnviron->Caption = "Параметры станции";
	pnQuartz->Caption = "МГц";
	gbFreqs->Caption = "Частоты, МГц";

	// Питание
	// Положение
	gbOrientation->Caption = "Положение прибора";
	// Среда
	gbEnvironement->Caption = "Среда";
	pnPitchName->Caption = "Крен,°";
	pnRollName->Caption = "Наклон,°";
	pnHeadName->Caption = "Азимут,°";
	//-----------------------------------------
	// Закладки
	TabSheet1->Caption = "Осциллограф";
	gbScope->Caption = "Данные";
	gbContr->Caption = "Настройки АЦП";
	lbAdcFreqName->Caption = "Частота АЦП";
	lbFiltName->Caption = "ФВЧ, Гц";
	lbNumPoint->Caption = "Точек осцил.";
	slsDisplay->Title->Text = "АЦП";
	slsDisplay->YAxis->AxisLabel->Text = "Данные АЦП";
	slsDisplay->XAxis->AxisLabel->Text = "Время, с";
	slsDisplay->Legend->Channels->Caption->Text = "Каналы";

	TabSheet2->Caption = "Режим оператора";
	gbFileParams->Caption = "Файл параметров";
	pnComments->Caption = "Комментарии (80 симв.)";
	sprintf(param_struct.my_str, "%s", "Комментарии (80 символов), не редактировать");
	edSampleString->Text = param_struct.my_str;
	pnPosition->Caption = "Позиция установки";
	pnStartDate->Caption = "Начало регистрации *";
	pnFinishDate->Caption = "Окончание регистрации *";
	pnBurnDate->Caption = "Начало пережига *";
	pnConstReg->Caption = "Постоянная регистрация";
	lbUtcTimeComment->Caption = "     * Время UTC";
	btnCheckParams->Caption = "Сравнить";
	pnModemNum->Caption = "Тип модема: ";
	cbModemNum->Items->Clear();
	cbModemNum->Items->Add("Нет");
	cbModemNum->Items->Add("Старый");
	cbModemNum->Items->Add("Штатный");
	cbModemNum->Items->Add("Bentos");
	cbModemNum->ItemIndex = 2;

	cbChangeModemName->Caption = "Не менять №";
	pnBurnTime->Caption = "Длительность пережига, с";
	pnPopupLen->Caption = "Длительность всплытия, м";
	pnAm3PopupDate->Caption = "Начало пережига модемом *";
	pnAm3Cal->Caption = "Светлое время суток *";
	pnAdcFreq->Caption = "Частота оцифровки АЦП, Гц";
	pnAdcEnergo->Caption = "Энергопотребление  АЦП";
	pnAdcPga->Caption = "PGA АЦП";
	lbConsum->Caption = "Потребление";


	cbAdcCons->Items->Clear();
	cbAdcCons->Items->Add("Пониженное");
	cbAdcCons->Items->Add("Штатное");
	cbAdcCons->ItemIndex = 1;

	pnNumBytes->Caption = "Число байт в слове данных";
	pnChannels->Caption = "Включенные каналы";
	pnFileLen->Caption = "Длительность файла записи";
	cbDataFileLen->Items->Clear();
	cbDataFileLen->Items->Add("1 час");
	cbDataFileLen->Items->Add("4 часа");
	cbDataFileLen->Items->Add("1 сутки");
	cbDataFileLen->ItemIndex = 1;


	pnFiltFreq->Caption = "Частота среза ФВЧ, Гц";





	//------------------
	TabSheet3->Caption = "Режим наладки";

	gbModem->Caption = "Модем";
	gbModemNum->Caption = "Номер модема";
	gbModemRtc->Caption = "Время RTC модема (дд.мм.гггг чч:мм) *";
	gbModemAlarm->Caption = "Начало пережига модемом (дд.мм.гггг чч:мм) *";
	gbModemLightTime->Caption = "Светлое время суток *";
	gbModemPopup->Caption = "Время подъема со дна (мин)";
	gbModemBurnLen->Caption = "Длительность пережига проволоки (с)";
	gbModemWriteParams->Caption = "Записать параметры в модем";
	gbModemBurnOn->Caption = "Включить/Выключить пережиг";
	gbModemLampOn->Caption = "Включить/Выключить лампу";
	gbModemRadioOn->Caption = "Включить/Выключить радио";
	gbModemPingSend->Caption = "Послать импульс(ы) по акустическому каналу";
	cbPingFreq->Items->Clear();
	cbPingFreq->Items->Add("9 кГц");
	cbPingFreq->Items->Add("11 кГц");
	cbPingFreq->Items->Add("13 кГц");
	cbPingFreq->ItemIndex = 1;
	lbUtcTimeMet->Caption = "Время UTC";
	gbRandomStr->Caption = "Послать произвольную команду";
	//------------------
        // счетчики
	gbMyCounts->Caption = "Счетчики обмена PC";
	pnPcTotalRx->Caption = "Всего принято";
	pnPcTotalTx->Caption = "Всего передано";
	pnPcCmdError->Caption = "Ошибки в команде";
	pnPcCntPack->Caption = "Счетных пакетов";
	pnPcXchgErr->Caption = "Ошибок обмена";

	gbCounts->Caption = "Счетчики обмена GNS110";
	pnGnsTotalRx->Caption = "Всего принято";
	pnGnsTotalTx->Caption = "Всего передано";
	pnGnsCmdError->Caption = "Ошибки в команде";
	pnGnsFrameError->Caption = "Ошибки кадра";
	pnGnsCrcError->Caption = "Ошибка CRC";
	//--------------
	// Исправные АЦП
	gbAdc->Caption = "Рабочие АЦП";
	pnAdcNum->Caption = "АЦП";
	pnAdcStatus->Caption = "Состояние";


	//--------------


	// Статусы и ощибки
	pnStatusAndErrors->Caption = "Статус и ошибки";
	gbStatus0->Caption = "Главный статус";
	lbStatus0_0->Caption = "Нет времени";
	lbStatus0_1->Caption = "Ошибка модема";
	lbStatus0_2->Caption = "Ошибка в команде";
	lbStatus0_3->Caption = "Не найден файл регистрации";
	lbStatus0_4->Caption = "Неисправность АЦП регистратора";
	lbStatus0_5->Caption = "Переполнение памяти регистратора";
	lbStatus0_6->Caption = "Осциллограф включен";
	lbStatus0_7->Caption = "Самотестирование регистратора";

	gbStatus1->Caption = "Самотестирование устройств";
	lbStatus1_0->Caption = "Ошибка RTC";
	lbStatus1_1->Caption = "Ошибка датчика давления";
	lbStatus1_2->Caption = "Ошибка акселерометра";
	lbStatus1_3->Caption = "Ошибка компаса";
	lbStatus1_4->Caption = "Ошибка модуля GPS";
	lbStatus1_5->Caption = "Ошибка EEPROM";
	lbStatus1_6->Caption = "Ошибка SD карты";
	lbStatus1_7->Caption = "Ошибка Flash";

	gbStatus2->Caption = "Прочие устройства";
	lbStatus2_0->Caption = "GPS включен";
	lbStatus2_1->Caption = "Модем включен";
	lbStatus2_2->Caption = "Тестирование модема";
	lbStatus2_3->Caption = "Некорректные данные в EEPROM";
	lbStatus2_4->Caption = "Ошибка генератор 19.2 МГц";
	lbStatus2_5->Caption = "Ошибка генератор 4.096 МГц";
	lbStatus2_6->Caption = "Нет PPS на входе";
	lbStatus2_7->Caption = "Ошибка таймера TIM3";

	gbResetCause->Caption = "Причина обрыва соединения";
	lbStatusReset_0->Caption = "Выключение питания";
	lbStatusReset_1->Caption = "Внешний сброс";
	lbStatusReset_2->Caption = "Снижение питания";
	lbStatusReset_3->Caption = "WDT сброс";
	lbStatusReset_4->Caption = "Длительное отсутствие связи";
	lbStatusReset_5->Caption = "Непредвиденный сброс";

	lbRele2->Caption = "Пережиг включен";
	lbRele3->Caption = "Аналоговое питание";
	lbRele6->Caption = "Проводной USB";
	lbRele7->Caption = "Беcпроводной WUSB";

	//-----------------
	sbInfo->Panels->Items[2]->Text = "Измерения (чч:мм)";
	sbInfo->Panels->Items[3]->Text = "Режим PC (чч:мм)";
	sbInfo->Panels->Items[4]->Text = "Модем (чч:мм)";
	sbInfo->Panels->Items[1]->Text = "Время работы в текущем сеансе";


    } else {
	// Верхние кнопари
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

	// Меню
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

	// Конфиругация оборубования
	pnConfig1->Caption = "Equipment profile";


	// Подключенная станция
	gbParams->Caption = "Connected SPN";
	sbRunModule->Hint = "Connect to SPN / Disconnect from SPN";

	// Время координаты
	gbTimes->Caption = "Time / GPS coordinates";
	pnUTCTime->Caption = "PC Time";
	pnGpsTime->Caption = "GPS Time";
	pnGpsLat->Caption = "Latitude";
	pnGpsLon->Caption = "Longitude";

     //	Label3->Caption = "Recorder Time";        

	// Параметры станции
	gbEnviron->Caption = "Recorder parameters";
	pnQuartz->Caption = "MHz";
	gbFreqs->Caption = "Frequencies, MHz";

	// Питание
	// Положение
	gbOrientation->Caption = "Device orientation";
	// Среда
	gbEnvironement->Caption = "Environment";
	pnPitchName->Caption = "Pitch,°";
	pnRollName->Caption = "Roll,°";
	pnHeadName->Caption = "Azimuth,°";
	//-----------------------------------------
	// Закладки
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
	// счетчики
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
	// Исправные АЦП
	gbAdc->Caption = "Working ADC";
	pnAdcNum->Caption = "ADC";
	pnAdcStatus->Caption = "Status";

	//--------------
	// Статусы и ощибки
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
