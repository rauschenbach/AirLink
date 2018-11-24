//---------------------------------------------------------------------------
// �������� ����� �� ����������
#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include "main.h"
#include "globdefs.h"
#include "utils.h"
#include "CheckFileThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall CheckFileThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
// ������  ���� - � ������� ����������, ������, ������ ��������� 
__fastcall CheckFileThread::CheckFileThread(String d, void *p, bool CreateSuspended)
:TThread(CreateSuspended)
{
    dir = d;			// ���������� � ������� ����������
    check_param_struct = (param_file_struct *) p;
}

//---------------------------------------------------------------------------
void __fastcall CheckFileThread::Execute()
{
    HANDLE check_file;
    char buf[128];
    char str[MAX_FILE_SIZE];
    TIME_DATE time;
    String FName;
    String err;
    s32 sec;
    int j, res = -1, x;		/* ret - ��������� ���������� */
    unsigned long bw;		/* ��������� ��� �������� ����  */
    myLangID lang;

    // ����� ��������
    ::PostMessage(frmMain->Handle, CM_SHOW_PARAM_DATA, (WPARAM) check_param_struct, 0);

    do {
	lang = frmMain->GetLangID();

	// ��������� ���� � �����������
	FName = dir + "\\recparam.cfg";
	check_file = CreateFile(FName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (check_file == INVALID_HANDLE_VALUE) {
	    if (lang == lang_rus)
		sprintf(buf, "�� ���� ������� ���� ���������� �� ����� (%s)!", dir.c_str());
	    else
		sprintf(buf, "Can't open parameters file on disk (%s)!", dir.c_str());
	    err = String(buf);
	    break;
	}
	// ������ ������ �� ����� ���������
	if (ReadFile(check_file, str, MAX_FILE_SIZE - 1, &bw, NULL) == false) {
	    if (lang == lang_rus)
		err = "�� ���� ��������� ���� ����������!";
	    else
		err = "Can't read parameters file!";
	    break;
	}
	str[bw] = 0;

	// ������� ����
	if (CloseHandle(check_file) == false) {
	    if (lang == lang_rus)
		err = "�� ���� ������� ���� ����������!";
	    else
		err = "Can't close parameters file!";
	    break;
	}
///////////////////////////////////////////////////////////////////////////////////////////////
// 0...������ ����� ������ ������, ��� ������ ���������� � "//"
///////////////////////////////////////////////////////////////////////////////////////////////


	// ��������� - ������ ������ ������� ������ - ��� ����� �������� �����
	if (str[0] == '/' && str[1] == '/') {
	    for (j = 2; j < 80; j++) {
		buf[j - 2] = str[j];	// ������� � �����
		if (str[j] == '\n' || str[j] == '\r') {	// ������� ������ DOS
		    buf[j - 2] = 0;
		    break;
		}
	    }
	}
	frmMain->edSampleString->Text = buf;
	memcpy(my_param_struct.my_str, buf, strlen(buf));


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
	my_param_struct.pos = atoi(buf);


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

	my_param_struct.start_time = sec;

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

	my_param_struct.finish_time = sec;

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
	if (sec < 0 || sec <= (int) my_param_struct.finish_time) {
	    sec_to_str(sec, buf);
	    if (lang == lang_rus)
		sprintf(str, "����� ������ ��������(%s)������ �������!", buf);
	    else
		sprintf(str, "Burn wire start time (%s) set incorrect!", buf);
	    ERROR_BOX(str);
	    break;
	}
	my_param_struct.burn_time = sec;

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
	my_param_struct.releburn_time = sec;

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
	my_param_struct.popup_len = sec;

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
	my_param_struct.modem_num = atoi(buf);

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
	if ((my_param_struct.modem_num > 0 && sec < 1) || (my_param_struct.modem_num > 0 && sec < (int) my_param_struct.start_time)) {
	    if (lang == lang_rus)
		ERROR_BOX("����� ���������� �������� �� ������ ������ ������� ��� ������ ������� ������!");
	    else
		ERROR_BOX("Modem alarm time set incorrect or less than recording start time!");
	    break;
	}
	my_param_struct.am3_popup_time = sec;

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
	my_param_struct.am3_cal_h0 = atoi(buf);

	// 2 ����� �� ������
	strncpy(buf, str + j + 4, 2);
	my_param_struct.am3_cal_m0 = atoi(buf);

	// ��� 2 ����� �� ���
	strncpy(buf, str + j + 7, 2);
	my_param_struct.am3_cal_h1 = atoi(buf);

	// 2 ����� �� ������
	strncpy(buf, str + j + 10, 2);
	my_param_struct.am3_cal_m1 = atoi(buf);

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

	// 4 ����� �� ����� 125, 250, 500, 1000, 2000, 4000
	strncpy(buf, str + j + 1, 5);
	my_param_struct.sample_freq = atoi(buf);

	// ������ � ������� �������
	if ((my_param_struct.sample_freq != 62) && (my_param_struct.sample_freq != 125) && 
	    (my_param_struct.sample_freq != 250) && (my_param_struct.sample_freq != 500) && 
            (my_param_struct.sample_freq != 1000) && (my_param_struct.sample_freq != 2000) && 
            (my_param_struct.sample_freq != 4000)) {
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
	    my_param_struct.power_cons = 1;
	} else if (strncmp(buf, "LO", 2) == 0) {
	    my_param_struct.power_cons = 0;
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
	my_param_struct.pga_adc = atoi(buf);

	// ������ � ������� ��������
	if ((my_param_struct.pga_adc != 1) && (my_param_struct.pga_adc != 2) && (my_param_struct.pga_adc != 4) && (my_param_struct.pga_adc != 8)
	    && (my_param_struct.pga_adc != 16) && (my_param_struct.pga_adc != 32) && (my_param_struct.pga_adc != 64)) {
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
	my_param_struct.am3_modem_type = x;
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
	my_param_struct.on_off_channels = 0;
	strncpy(buf, str + j + 1, 5);

	// ������� �� ���������
	my_param_struct.on_off_channels = 0x0;
	if (buf[0] != '0')
	    my_param_struct.on_off_channels |= 0x08;
	if (buf[1] != '0')
	    my_param_struct.on_off_channels |= 0x04;
	if (buf[2] != '0')
	    my_param_struct.on_off_channels |= 0x02;
	if (buf[3] != '0')
	    my_param_struct.on_off_channels |= 0x01;


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
	my_param_struct.data_file_len = (j > 0 && j < 25) ? j : 1;

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
	my_param_struct.filter_freq = atof(buf);	/* � ���� �������� - �� 0 �� ??? */

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
	my_param_struct.const_reg_flag = ((atoi(buf) == 0) ? false : true);	/* � ���� �������� - �� 0 �� ??? */
	res = 0;

	// ���������  �� �����������
	if (res == 0) {
	    if (strncmp(my_param_struct.my_str, check_param_struct->my_str, strlen(check_param_struct->my_str) - 5) != 0) {
		if (lang == lang_rus)
		    err += "������ � ����������, ������ ����: " + String(check_param_struct->my_str);
		else
		    err += "Error in coments, need be: " + String(check_param_struct->my_str);
		res++;
	    }
	    // �������
	    if (my_param_struct.pos != check_param_struct->pos) {
		if (lang == lang_rus)
		    err += "������ � �������, ������ ����: " + IntToStr(check_param_struct->pos);
		else
		    err += "\nError in position, need be: " + IntToStr(check_param_struct->pos);
		res++;
	    }
	    // ������ �����������
	    if (my_param_struct.start_time != check_param_struct->start_time) {
		sec_to_str(check_param_struct->start_time, str);
		if (lang == lang_rus)
		    err += "\n������ ������� ������, ������ ����: " + String(str);
		else
		    err += "\nError in Start time, need be: " + String(str);
		res++;
	    }
	    // ��������� �����������
	    if (my_param_struct.finish_time != check_param_struct->finish_time) {
		sec_to_str(check_param_struct->finish_time, str);
		if (lang == lang_rus)
		    err += "\n������ ������� ���������, ������ ����: " + String(str);
		else
		    err += "\nError in Finish time, need be: " + String(str);
		res++;
	    }
	    // ������ ��������
	    if (my_param_struct.burn_time != check_param_struct->burn_time) {
		sec_to_str(check_param_struct->burn_time, str);
		if (lang == lang_rus)
		    err += "\n������ ������� ��������, ������ ����: " + String(str);
		else
		    err += "\nError in Burn time, need be: " + String(str);
		res++;
	    }
	    // ������������ ��������
	    if (my_param_struct.releburn_time != check_param_struct->releburn_time) {
		if (lang == lang_rus)
		    err += "\n������ ����������������� ��������, ������ ����: " + IntToStr(check_param_struct->releburn_time);
		else
		    err += "\nError in Burn len, need be: " + IntToStr(check_param_struct->releburn_time);
		res++;
	    }
	    // ����������� ��������
	    if (my_param_struct.popup_len != check_param_struct->popup_len) {
		if (lang == lang_rus)
		    err += "\n������ ����������������� ��������, ������ ����: " + IntToStr(check_param_struct->popup_len);
		else
		    err += "\nError in Popup len, need be: " + IntToStr(check_param_struct->popup_len);
		res++;
	    }
	    // ������� ����� �����
	    if (my_param_struct.am3_cal_h0 != check_param_struct->am3_cal_h0 &&
		my_param_struct.am3_cal_m0 != check_param_struct->am3_cal_m0 &&
		my_param_struct.am3_cal_h1 != check_param_struct->am3_cal_h1 && my_param_struct.am3_cal_m1 != check_param_struct->am3_cal_m1) {
		sprintf(str, "%02d:%02d - %02d:%02d",
			check_param_struct->am3_cal_h0, check_param_struct->am3_cal_m0, check_param_struct->am3_cal_h1, check_param_struct->am3_cal_m1);
		if (lang == lang_rus)
		    err += "\n������ �������� ������� �����, ������ ����: " + String(str);
		else
		    err += "\nError in Daytime, need be: " + String(str);
		res++;
	    }
	    // �����������������
	    if (my_param_struct.power_cons != check_param_struct->power_cons) {
		if (lang == lang_rus)

		    err += "\n������ �����������, ������ ����: " + IntToStr(check_param_struct->power_cons);
		else
		    err += "\nError in Power consumption, need be: " + IntToStr(check_param_struct->power_cons);
		res++;
	    }
	    // PGA
	    if (my_param_struct.pga_adc != check_param_struct->pga_adc) {
		if (lang == lang_rus)
		    err += "\n������ PGA, ������ ����: " + IntToStr(check_param_struct->pga_adc);
		else
		    err += "\nError in PGA, need be: " + IntToStr(check_param_struct->pga_adc);
		res++;
	    }
	    // ������
	    if (my_param_struct.on_off_channels != check_param_struct->on_off_channels) {
		if (lang == lang_rus)
		    err += "\n������ �������� ���������� �������, ������ ����: " + IntToStr(check_param_struct->on_off_channels);
		else
		    err += "\nError in Channel bitmap, need be: " + IntToStr(check_param_struct->on_off_channels);
		res++;
	    }
	    // ������� �������
	    if (my_param_struct.filter_freq != check_param_struct->filter_freq) {
		if (lang == lang_rus)
		    err += "\n������ ������� �������, ������ ����: " + FloatToStr(check_param_struct->filter_freq);
		else
		    err += "\nError in Filter freq, need be: " + FloatToStr(check_param_struct->filter_freq);
		res++;
	    }
	    // ���������� �����������
	    if (my_param_struct.const_reg_flag != check_param_struct->const_reg_flag) {
		if (lang == lang_rus)
		    err += "\n������ � ���������� �����������, ������ ����: " + IntToStr(check_param_struct->const_reg_flag);
		else
		    err += "\nError in Const reg, need be: " + IntToStr(check_param_struct->const_reg_flag);
		res++;
	    }
	    // ������� ���������
	    if (my_param_struct.sample_freq != check_param_struct->sample_freq) {
		if (lang == lang_rus)
		    err += "\n������ ������� ������������� ���, ������ ����: " + IntToStr(check_param_struct->sample_freq);
		else
		    err += "\nError in Sample freq, need be: " + IntToStr(check_param_struct->sample_freq);
		res++;
	    }
	    // ��� ������
	    if (my_param_struct.am3_modem_type != check_param_struct->am3_modem_type) {
		if (lang == lang_rus)
		    err += "\n������ ���� ������, ������ ����: " + IntToStr(check_param_struct->am3_modem_type);
		else
		    err += "\nError in Modem type, need be: " + IntToStr(check_param_struct->am3_modem_type);
		res++;
	    }
	    // ����� ������
	    if (my_param_struct.modem_num != check_param_struct->modem_num) {
		if (lang == lang_rus)
		    err += "\n������ � ������ ������, ������ ����: " + IntToStr(check_param_struct->modem_num);
		else
		    err += "\nError in Modem number, need be: " + IntToStr(check_param_struct->modem_num);
		res++;
	    }
	    // ����� ������� �� ������
	    if (my_param_struct.am3_popup_time != check_param_struct->am3_popup_time) {
		sec_to_str(check_param_struct->am3_popup_time, str);
		if (lang == lang_rus)
		    err += "\n������ ������� ���������� �������� �� ������, ������ ����: " + String(str);
		else
		    err += "\nError in Modem alarm time, need be: " + String(str);
		res++;
	    }
	}
    } while (0);

    if (res)
	ERROR_BOX(err.c_str());
    else {
	if (lang == lang_rus)
	    INFO_BOX("��������� � ����� ���������, ������ � �������������� �� �������!");
	else
	    INFO_BOX("Parameters in file are checked, errors not found!");
    }
}

//---------------------------------------------------------------------------
