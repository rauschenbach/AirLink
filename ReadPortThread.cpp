//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include <math.h>
#include "proto.h"
#include "main.h"
#include "utils.h"
#include "ReadPortThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ReadPortThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
// иначе при закрытии процесса - ошибка(данных уже нету!)
static XCHG_ERR_COUNT in, out, sum;
static PORT_COUNT_STRUCT cnt;
static RTC_TIME_STRUCT rtc;
static ADS1282_PACK_STRUCT ads1282_data, pack;
static DEV_WORK_TIME_STRUCT wt;
static NMEA_RX_BUF nmea;
static NMEA_params info;
static int show = 0;
static DEV_STATUS_STRUCT status;

#define TIMER_HSEC_DIVIDER	        (5)
#define TIMER_SEC_DIVIDER		(10)
#define TIMER_MIN_DIVIDER		(600)

void get_dsp_status(void *p)
{
  memcpy(p, &status, sizeof(DEV_STATUS_STRUCT));
}

s64    ttt0, ttt1;
int count = 0;

__fastcall ReadPortThread::ReadPortThread(bool CreateSuspended)
:TThread(CreateSuspended)
{
}

//---------------------------------------------------------------------------
// Наш таймер в main form считает по 100 мс
void __fastcall ReadPortThread::Execute()
{
    char buf[256];
    int not_connect = 0;
    int res;
    int i;
    int g;
    float m;
    int num = 0;
    char c;
    s64 timer = 0;
    s64  d;

    memset(&in, 0, sizeof(XCHG_ERR_COUNT));
    memset(&out, 0, sizeof(XCHG_ERR_COUNT));
    memset(&sum, 0, sizeof(XCHG_ERR_COUNT));

    do {
	if (frmMain->bEndThread) {
	    break;
	}
	bPick = false;

        /* Не опрашиваем в проекте для океанологии */
	/* раз в полсекунды спрашиваем время */
	if (timer % TIMER_HSEC_DIVIDER == 0 && TimeGet(&rtc) == 0) {
	    frmMain->TimeGNS110(rtc.time);
        }

	/* раз в полсесекунды спрашиваем счетчики */
	if (timer % TIMER_HSEC_DIVIDER == 0 && CountsGet(&cnt) == 0) {
	    ::PostMessage(frmMain->Handle, CM_SHOW_PORT_COUNTS, (WPARAM) & cnt, 0);	// Вывести счетчики пакетов
         }


	// раз в минуту берем рабочее время (они считаеца по минутам и часам)
	if (timer % TIMER_MIN_DIVIDER == 0 && GetWorkTime(&wt) == 0) {
	    ::PostMessage(frmMain->Handle, CM_SHOW_WORK_TIME, (WPARAM) & wt, 0);
         }


	// Если есть данные-читаем до получения статуса "нет данных"
	// подобраьт время
	while (1) {

           // если есть данные - как часто отправляем?
	    if (DataGet(&ads1282_data) == 0) {
                int k;
                count++;

                // в зависимости от частыты - сделаем прорежывание
                k = (1 << ads1282_data.adc);
                memcpy(&pack, &ads1282_data, sizeof(ADS1282_PACK_STRUCT));

                if (k)
		  ::PostMessage(frmMain->Handle, CM_READ_DATA, (WPARAM) &pack, 0);

               d = get_msec_ticks() - ttt0;

                if(count % 2 == 0 && d > 0) {
                     num = count * 1000 / d ; // за 1 секунду
                  }

	    } else {
		break;
	    }
	}


	// Если включен прием NMEA
	// раз в полсекунды (иначе сбиваеца)
	if (status.ports & 1 && timer % TIMER_HSEC_DIVIDER == 0 && NmeaGet(&nmea) == 0 && nmea.str[0] == '$') {
	    String s = "Navigate data from GPS module: " + String(nmea.str);
	    frmMain->LogOut(s.c_str());
	    if (parse_nmea_string(nmea.str, &info) == 0) {
	        int temp = (info.utc.wYear > 2000)? info.utc.wYear - 2000 : info.utc.wYear - 1900;
		sprintf(buf, "%02d.%02d.%02d %02d:%02d:%02d", info.utc.wDay, info.utc.wMonth, temp, info.utc.wHour, info.utc.wMinute,
			info.utc.wSecond);
		frmMain->lbGpsTime->Caption = buf;	// время GPS


		c = info.lat >= 0 ? 'N' : 'S';
		info.lat = fabs(info.lat);
		g = (int) info.lat / 100;
		m = info.lat / 100 - g;
		m *= 100;

		sprintf(buf, "%d° %4.4f' %c", g, m, c);
		frmMain->lbGpsLat->Caption = buf;

		c = info.lon >= 0 ? 'E' : 'W';
		info.lon = fabs(info.lon);
		g = (int) info.lon / 100;
		m = info.lon / 100 - g;
		m *= 100;
		sprintf(buf, "%d° %4.4f' %c", g, m, c);
		frmMain->lbGpsLon->Caption = buf;
	    }
	}

	/* Получить статус раз в 100 тиков */
	/* раз в полсекунды */
	if (timer % TIMER_HSEC_DIVIDER == 0) {

         if(StatusGet(&status) == 0) {
	    // Show status
       	    ::SendMessage(frmMain->Handle, CM_SHOW_STATUS, (WPARAM) &status, 0);
	    not_connect = 0;
	} else /*if (res < 0) */{
	    not_connect++;
	    if (not_connect > 250) {	// нет 12 секунд статусов
		frmMain->bEndThread = true;
		::PostMessage(frmMain->Handle, CM_NO_DATA, 0, 0);
		break;
	    }
	}
     }

	// Запущен
	if (!(status.st_main & 0x40)) {
	    frmMain->cbAdcFreq->Enabled = false;
	    frmMain->cbPGA->Enabled = false;
	    frmMain->seFltFreq->Enabled = false;
            frmMain->cbConsum->Enabled = false;
            frmMain->cbChop->Enabled = false;		
	} else {
	    frmMain->cbAdcFreq->Enabled = true;
	    frmMain->cbPGA->Enabled = true;
	    frmMain->seFltFreq->Enabled = true;
            frmMain->cbConsum->Enabled = true;
            frmMain->cbChop->Enabled = true;
	}

	if (frmMain->bEndThread) {
	    break;
	}

       if (timer % TIMER_SEC_DIVIDER == 0) {
        	PortGetXchgErr(&in);	// Получили
        	filt_ok_and_error(&in, &out);	// Отфильтровали
        	sum.tx_ok += out.tx_ok;
        	sum.rx_err += out.rx_err;
        	::PostMessage(frmMain->Handle, CM_SHOW_LINK, (WPARAM) & out, (LPARAM) & sum);
        }

	if (show == 0) {
	    show = 1;
	    frmMain->ShowStatusIfChange(&status, 1 + 2 + 8);
	}

	bPick = true;
	Sleep(5);
        timer = frmMain->GetBigTimer();
    }
    while (!frmMain->bEndThread /* && !Terminated */ );
    not_connect = 0;

    show = 0;
    frmMain->LogOut("Thread stopped");
}

//---------------------------------------------------------------------------)
