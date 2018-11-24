//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "globdefs.h"
#include "utils.h"
#include "OpenFileThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall OpenFileThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

#define    param_struct frmMain->param_struct
__fastcall OpenFileThread::OpenFileThread(String name, bool CreateSuspended)

:TThread(CreateSuspended)
{
    FName = name;
}


//---------------------------------------------------------------------------
// ��������: ��������� �� �����
//---------------------------------------------------------------------------
void __fastcall OpenFileThread::Execute()
{
    HANDLE reg_file;
    char buf[128], *p;
    char str[MAX_FILE_SIZE];
    TIME_DATE time;
    s32 sec;
    int j, ret = -1, x;		/* ret - ��������� ���������� */
    unsigned long bw;		/* ��������� ��� �������� ����  */
    myLangID lang;



    do {
	lang = frmMain->GetLangID();

	// ��������� ���� � �����������
	reg_file = CreateFile(FName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (reg_file == INVALID_HANDLE_VALUE) {
	    if (lang == lang_rus)
		ERROR_BOX("�� ���� ������� ���� ����������!");
	    else
		ERROR_BOX("Can't open parameters file!");
	    break;
	}
	// ������ ������ �� ����� ���������
	if (ReadFile(reg_file, str, MAX_FILE_SIZE - 1, &bw, NULL) == false) {
	    if (lang == lang_rus)
		ERROR_BOX("�� ���� ��������� ���� ����������!");
	    else
		ERROR_BOX("Can't read parameters file!");
	    break;
	}
	str[bw] = 0;

	// ������� ����
	if (CloseHandle(reg_file) == false) {
	    if (lang == lang_rus)
		ERROR_BOX("�� ���� ������� ���� ����������!");
	    else
		ERROR_BOX("Can't close parameters file!");
	    break;
	}
///////////////////////////////////////////////////////////////////////////////////////////////
// 0...������ ����� ������ ������, ��� ������ ���������� � "//"
///////////////////////////////////////////////////////////////////////////////////////////////

	// ��������� - ������ ������ ������� ������ - ��� ����� �������� �����
	if (str[0] == '/' && str[1] == '/')
	    p = &str[2];
	else
	    p = &str[0];


	for (j = 0; j < 80; j++) {
	    buf[j] = *(p + j);	// ������� � �����            
	    if (*(p + j) == '\n' || *(p + j) == '\r') {	// ������� ������ DOS
		buf[j] = 0;
		break;
	    }
	}
	memcpy(param_struct.my_str, buf, strlen(buf));

///////////////////////////////////////////////////////////////////////////////////////////////
// 1...��������� ������ - ������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	// ������� ������ DOS
		x++;
		if (x == POS_NUM_STR) {
		    break;
		}
	    }
	}


	/* 5 ����� �� ����� */
	strncpy(buf, str + j + 1, 6);
	buf[5] = 0;
	param_struct.pos = atoi(buf);


///////////////////////////////////////////////////////////////////////////////////////////////
// 2...��������� ������ ������� ������ ����������� ����� 1-�� ��������
///////////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	// ������� ������ DOS
		x++;
		if (x == BEGIN_REG_NUM_STR) {
		    break;
		}
	    }
	}

	buf[2] = 0;

	/* ������� 2 ����� �� ����� */
	strncpy(buf, str + j + 1, 2);
	time.day = atoi(buf);

	/* ����� */
	strncpy(buf, str + j + 4, 2);
	time.mon = atoi(buf);

	/* ��� */
	strncpy(buf, str + j + 7, 2);
	time.year = atoi(buf) + 2000;
	/* ���� */
	strncpy(buf, str + j + 10, 2);
	time.hour = atoi(buf);

	/* ������ */
	strncpy(buf, str + j + 13, 2);
	time.min = atoi(buf);

	/* ������� */
	strncpy(buf, str + j + 16, 2);
	time.sec = atoi(buf);


	// 1. ��������� �� ����� ������ �����������
	sec = td_to_sec(&time);
	if (sec < 0) {
	    sec_to_str(sec, buf);
	    if (lang == lang_rus)
		sprintf(str, "����� ������ ����������� (%s) ������ �������!", buf);
	    else
		sprintf(str, "Recording start time (%s) set incorrect!", buf);
		ERROR_BOX(str);
	    break;
	}

	param_struct.start_time = sec;

///////////////////////////////////////////////////////////////////////////////////////////////
// ���� 3-� ������� ������ -  ����� ��������� ����������� 
///////////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	// ������� ������ DOS
		x++;
		if (x == END_REG_NUM_STR) {
		    break;
		}
	    }
	}

	/* 3...��������� ������ ������� ��������� ����������� */
	buf[2] = 0;

	// ������� 2 ����� �� �����
	strncpy(buf, str + j + 1, 2);
	time.day = atoi(buf);

	// �����
	strncpy(buf, str + j + 4, 2);
	time.mon = atoi(buf);

	// ���
	strncpy(buf, str + j + 7, 2);
	time.year = atoi(buf) + 2000;

	// ����
	strncpy(buf, str + j + 10, 2);
	time.hour = atoi(buf);

	// ������
	strncpy(buf, str + j + 13, 2);
	time.min = atoi(buf);

	// �������
	strncpy(buf, str + j + 16, 2);
	time.sec = atoi(buf);

	// 3. ����� ��������� �����������
	sec = td_to_sec(&time);
	if (sec < 0) {
	    sec_to_str(sec, buf);
	    if (lang == lang_rus)
		sprintf(str, "����� ��������� ����������� (%s) ������ �������!", buf);
	    else
		sprintf(str, "End of recording time (%s) set incorrect!", buf);
		ERROR_BOX(str);
	    break;
	}			
	param_struct.finish_time = sec;

//////////////////////////////////////////////////////////////////////////////////////////
//���� 4-� ������� ������ 
//////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* ������� ������ (DOS ��� UNIX ?) */
		x++;
		if (x == BEGIN_BURN_NUM_STR) {
		    break;
		}
	    }
	}

	// 3... ��������� ������ ������� ��������
	buf[2] = 0;

	// ������� 2 ����� �� �����
	strncpy(buf, str + j + 1, 2);
	time.day = atoi(buf);

	// �����
	strncpy(buf, str + j + 4, 2);
	time.mon = atoi(buf);

	// ���
	strncpy(buf, str + j + 7, 2);
	time.year = atoi(buf) + 2000;

	// ����
	strncpy(buf, str + j + 10, 2);
	time.hour = atoi(buf);

	// ������
	strncpy(buf, str + j + 13, 2);
	time.min = atoi(buf);

	// �������
	strncpy(buf, str + j + 16, 2);
	time.sec = atoi(buf);

	// 3. ��������� � ������� ������� ������ ��������
	sec = td_to_sec(&time);
	if (sec < 0 || sec <= (int) param_struct.finish_time) {
	    sec_to_str(sec, buf);
	    if (lang == lang_rus)
		sprintf(str, "����� ������ ��������(%s)������ �������!", buf);
	    else
		sprintf(str, "Burn wire time (%s) set incorrect!", buf);
		ERROR_BOX(str);
	    break;
	}
	param_struct.burn_time = sec;

/////////////////////////////////////////////////////////////////////////////////////////
// ���� 5-� ������� ������ ������������ ��������
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* ������� ������ (DOS ��� UNIX ?) */
		x++;
		if (x == BURN_LEN_NUM_STR) {
		    break;
		}
	    }
	}

	strncpy(buf, str + j + 1, 4);	/* ������������ �������� - 3 ����� */
	sec = atoi(buf);
	if (sec < 1) {
	    if (lang == lang_rus)
		ERROR_BOX("������������ �������� ������ �������. ������ ���� ����� 1 �������!");
	    else
		ERROR_BOX("Burn wire duration set incorrect. Must be more than 1 second!");
	    break;
	}
	param_struct.releburn_time = sec;

/////////////////////////////////////////////////////////////////////////////////////////
// ���� 6-� ������� ������ ������������ ��������
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* ������� ������ (DOS ��� UNIX ?) */
		x++;
		if (x == POPUP_LEN_NUM_STR) {
		    break;
		}
	    }
	}

	strncpy(buf, str + j + 1, 4);	/* ������������ ��������  � ������� - 3 ����� */
	sec = atoi(buf);
	if (sec < 1) {
	    if (lang == lang_rus)
		ERROR_BOX("������������ �������� ������ �������. ������ ���� ����� 1 ������!");
	    else
		ERROR_BOX("Popup duration set incorrect. Must be more than 1 minute!");
	    break;
	}
	param_struct.popup_len = sec;

/////////////////////////////////////////////////////////////////////////////////////////
// ���� 7-� ������� ������. ����� ������������� ������ 
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* ������� ������ (DOS ��� UNIX ?) */
		x++;
		if (x == MODEM_NUM_NUM_STR) {
		    break;
		}
	    }
	}


	/* ����� ������������� ������ - 4 ����� �� ��� �����! */
	strncpy(buf, str + j + 1, 4);
	param_struct.modem_num = atoi(buf);

/////////////////////////////////////////////////////////////////////////////////////////
// ���� 8-� ������� ������. ����� ���������� �������� �� ������
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* ������� ������ (DOS ��� UNIX ?) */
		x++;
		if (x == ALARM_TIME_NUM_STR) {
		    break;
		}
	    }
	}


	// 6... ��������� ������ ������� ��������
	buf[2] = 0;

	// ������� 2 ����� �� �����
	strncpy(buf, str + j + 1, 2);
	time.day = atoi(buf);

	// �����
	strncpy(buf, str + j + 4, 2);
	time.mon = atoi(buf);

	// ���
	strncpy(buf, str + j + 7, 2);
	time.year = atoi(buf) + 2000;

	// ����
	strncpy(buf, str + j + 10, 2);
	time.hour = atoi(buf);

	// ������
	strncpy(buf, str + j + 13, 2);
	time.min = atoi(buf);

	// �������
	strncpy(buf, str + j + 16, 2);
	time.sec = atoi(buf);

	// 6. ��������� � ������� UTC
	sec = td_to_sec(&time);
	if ((param_struct.modem_num > 0 && sec < 1) || (param_struct.modem_num > 0 && sec < (int) param_struct.start_time)) {
	    if (lang == lang_rus)
		ERROR_BOX("����� ���������� �������� �� ������ ������ ������� ��� ������ ������� ������!");
	    else
		ERROR_BOX("Modem alarm time set incorrect or less than recording start time!");
	    break;
	}
	param_struct.am3_popup_time = sec;

/////////////////////////////////////////////////////////////////////////////////////////
// ���� 9-� ������� ������. ����� �������� ������� �����
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* ������� ������ (DOS ��� UNIX ?) */
		x++;
		if (x == DAY_TIME_NUM_STR) {
		    break;
		}
	    }
	}


	// ����� �������� ������� �����
	buf[2] = 0;

	// ������� 2 ����� �� ���
	strncpy(buf, str + j + 1, 2);
	param_struct.am3_cal_h0 = atoi(buf);

	// 2 ����� �� ������
	strncpy(buf, str + j + 4, 2);
	param_struct.am3_cal_m0 = atoi(buf);

	// ��� 2 ����� �� ���
	strncpy(buf, str + j + 7, 2);
	param_struct.am3_cal_h1 = atoi(buf);

	// 2 ����� �� ������
	strncpy(buf, str + j + 10, 2);
	param_struct.am3_cal_m1 = atoi(buf);

/////////////////////////////////////////////////////////////////////////////////////////
// ���� 10-� ������� ������. ������� ���������.
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* ������� ������ (DOS ��� UNIX ?) */
		x++;
		if (x == ADC_FREQ_NUM_STR) {
		    break;
		}
	    }
	}

	// 4 ����� �� ����� 62 125, 250, 500, 1000, 2000, 4000
	strncpy(buf, str + j + 1, 5);
	param_struct.sample_freq = atoi(buf);

	// ������ � ������� �������
	if ((param_struct.sample_freq != 62) && (param_struct.sample_freq != 125) && 
	    (param_struct.sample_freq != 250) && (param_struct.sample_freq != 500) && 
            (param_struct.sample_freq != 1000) && (param_struct.sample_freq != 2000) && 
            (param_struct.sample_freq != 4000)) {
	    if (lang == lang_rus)
		ERROR_BOX("������ ������� ������� ��������� � ����� ����������!");
	    else
		ERROR_BOX("ADC sampling rate set incorrect in parameters file!");
	    break;
	}
/////////////////////////////////////////////////////////////////////////////////////////
// ���� 11-� ������� ������. ����������������� ���
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* ������� ������ (DOS ��� UNIX ?) */
		x++;
		if (x == ADC_CONSUM_NUM_STR) {
		    break;
		}
	    }
	}

	// 3 ������� hi ��� lo
	strncpy(buf, str + j + 1, 3);

	// � ������� �������
	str_to_cap(buf, 2);

	// ��� � ��� ��������?
	if (strncmp(buf, "HI", 2) == 0) {
	    param_struct.power_cons = 1;
	} else if (strncmp(buf, "LO", 2) == 0) {
	    param_struct.power_cons = 0;
	} else {
	    break;
	}


/////////////////////////////////////////////////////////////////////////////////////////
// ���� 12-� ������� ������. �������� PGA
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* ������� ������ (DOS ��� UNIX ?) */
		x++;
		if (x == ADC_PGA_NUM_STR) {
		    break;
		}
	    }
	}


	// 2 ����� �� ����� PGA
	strncpy(buf, str + j + 1, 3);
	param_struct.pga_adc = atoi(buf);

	// ������ � ������� ��������
	if ((param_struct.pga_adc != 1) && (param_struct.pga_adc != 2) && (param_struct.pga_adc != 4) && (param_struct.pga_adc != 8)
	    && (param_struct.pga_adc != 16) && (param_struct.pga_adc != 32) && (param_struct.pga_adc != 64)) {

	    if (lang == lang_rus)
		ERROR_BOX("������ ������� PGA � ����� ����������!");
	    else
		ERROR_BOX("ADC PGA set incorrect in parameters file!");
	    break;
	}
/////////////////////////////////////////////////////////////////////////////////////////
// ���� 13-� ������� ������. ����� ���� � ����� ������.
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* ������� ������ (DOS ��� UNIX ?) */
		x++;
		if (x == MODEM_TYPE_NUM_STR) {
		    break;
		}
	    }
	}

	/* 2 ����� �� ����� 3 ��� 4 */
	strncpy(buf, str + j + 1, 2);
	x = atoi(buf);
	if (x > 3 && x < 0) {
	    if (lang == lang_rus)
		ERROR_BOX("������ ������� ���� ������!");
	    else
		ERROR_BOX("Error in modem type setting!");
	    break;
	}
	param_struct.am3_modem_type = x;
/////////////////////////////////////////////////////////////////////////////////////////
// ���� 14-� ������� ������. ������������ ������ ���. ������ ������
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* ������� ������ (DOS ��� UNIX ?) */
		x++;
		if (x == ADC_BITMAP_NUM_STR) {
		    break;
		}
	    }
	}


	// 4 ����� �� ����� 
	param_struct.on_off_channels = 0;
	strncpy(buf, str + j + 1, 5);

	// ������� �� ���������
	param_struct.on_off_channels = 0x0;
	if (buf[0] != '0')
	    param_struct.on_off_channels |= 0x08;
	if (buf[1] != '0')
	    param_struct.on_off_channels |= 0x04;
	if (buf[2] != '0')
	    param_struct.on_off_channels |= 0x02;
	if (buf[3] != '0')
	    param_struct.on_off_channels |= 0x01;


/////////////////////////////////////////////////////////////////////////////////////////
// ���� 15-� ������� ������. ������� ����� ������ ���� ������
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* ������� ������ (DOS ��� UNIX ?) */
		x++;
		if (x == FILE_LEN_NUM_STR) {
		    break;
		}
	    }
	}


	// 2 ����� �� ����� 
	strncpy(buf, str + j + 1, 3);
	j = atoi(buf);

	// � ���� �������� - �� ���� �� �����
	param_struct.data_file_len = (j > 0 && j < 25) ? j : 1;

/////////////////////////////////////////////////////////////////////////////////////////
// ���� 16-� ������� ������. ������� ����� �������
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* ������� ������ (DOS ��� UNIX ?) */
		x++;
		if (x == FLT_FREQ_NUM_STR) {
		    break;
		}
	    }
	}

	/* 7 ���� �� ����� � ���. ����� */
	strncpy(buf, str + j + 1, 7);
	param_struct.filter_freq = atof(buf);	/* � ���� �������� - �� 0 �� ??? */

/////////////////////////////////////////////////////////////////////////////////////////
// ���� 17-� ������� ������. ���������� �����������
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* ������� ������ (DOS ��� UNIX ?) */
		x++;
		if (x == CONST_REG_NUM_STR) {
		    break;
		}
	    }
	}

	// 2 ����� �� �����
	strncpy(buf, str + j + 1, 2);
	param_struct.const_reg_flag = ((atoi(buf) == 0) ? false : true);	/* � ���� �������� - �� 0 �� ??? */

    } while (0);

    ::PostMessage(frmMain->Handle, CM_SHOW_PARAM_DATA, (WPARAM) & param_struct, 0);
}

//---------------------------------------------------------------------------
