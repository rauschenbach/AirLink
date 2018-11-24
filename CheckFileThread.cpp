//---------------------------------------------------------------------------
// Проверка файла на совпадение
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
// Первый  файл - с которым сравниваем, второй, коорый прочитаем 
__fastcall CheckFileThread::CheckFileThread(String d, void *p, bool CreateSuspended)
:TThread(CreateSuspended)
{
    dir = d;			// директория с которой сравниваем
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
    int j, res = -1, x;		/* ret - результат выполнения */
    unsigned long bw;		/* Прочитано или записано байт  */
    myLangID lang;

    // Могли изменить
    ::PostMessage(frmMain->Handle, CM_SHOW_PARAM_DATA, (WPARAM) check_param_struct, 0);

    do {
	lang = frmMain->GetLangID();

	// Открываем файл с параметрами
	FName = dir + "\\recparam.cfg";
	check_file = CreateFile(FName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (check_file == INVALID_HANDLE_VALUE) {
	    if (lang == lang_rus)
		sprintf(buf, "Не могу открыть файл параметров на диске (%s)!", dir.c_str());
	    else
		sprintf(buf, "Can't open parameters file on disk (%s)!", dir.c_str());
	    err = String(buf);
	    break;
	}
	// Читаем строки со всеми временами
	if (ReadFile(check_file, str, MAX_FILE_SIZE - 1, &bw, NULL) == false) {
	    if (lang == lang_rus)
		err = "Не могу прочитать файл параметров!";
	    else
		err = "Can't read parameters file!";
	    break;
	}
	str[bw] = 0;

	// Закроем файл
	if (CloseHandle(check_file) == false) {
	    if (lang == lang_rus)
		err = "Не могу закрыть файл параметров!";
	    else
		err = "Can't close parameters file!";
	    break;
	}
///////////////////////////////////////////////////////////////////////////////////////////////
// 0...Читаем самую первую строку, она должна начинаться с "//"
///////////////////////////////////////////////////////////////////////////////////////////////


	// Разбираем - найдем первый перевод строки - там будет записано время
	if (str[0] == '/' && str[1] == '/') {
	    for (j = 2; j < 80; j++) {
		buf[j - 2] = str[j];	// соберем в буфер
		if (str[j] == '\n' || str[j] == '\r') {	// перевод строки DOS
		    buf[j - 2] = 0;
		    break;
		}
	    }
	}
	frmMain->edSampleString->Text = buf;
	memcpy(my_param_struct.my_str, buf, strlen(buf));


///////////////////////////////////////////////////////////////////////////////////////////////
// 1...Разбираем строку - Позиция установки
///////////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	// перевод строки DOS
		x++;
		if (x == POS_NUM_STR) {
		    break;
		}
	    }
	}


	/* 5 цифры на число */
	strncpy(buf, str + j + 1, 6);
	buf[5] = 0;
	my_param_struct.pos = atoi(buf);


///////////////////////////////////////////////////////////////////////////////////////////////
// 2...Разбираем строку времени начала регистрации после 1-го перевода
///////////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	// перевод строки DOS
		x++;
		if (x == BEGIN_REG_NUM_STR) {
		    break;
		}
	    }
	}

	buf[2] = 0;

	/* сначала 2 цифры на число */
	strncpy(buf, str + j + 1, 2);
	time.day = atoi(buf);

	/* месяц */
	strncpy(buf, str + j + 4, 2);
	time.mon = atoi(buf);

	/* год */
	strncpy(buf, str + j + 7, 2);
	time.year = atoi(buf) + 2000;
	/* часы */
	strncpy(buf, str + j + 10, 2);
	time.hour = atoi(buf);

	/* минуты */
	strncpy(buf, str + j + 13, 2);
	time.min = atoi(buf);

	/* секунды */
	strncpy(buf, str + j + 16, 2);
	time.sec = atoi(buf);


	// 1. перевести во время начала регистрации
	sec = td_to_sec(&time);
	if (sec < 0) {
	    sec_to_str(sec, buf);
	    if (lang == lang_rus)
		sprintf(str, "Время начала регистрации (%s) задано неверно!", buf);
	    else
		sprintf(str, "Recording start time (%s) set incorrect!", buf);
	    ERROR_BOX(str);
	    break;
	}

	my_param_struct.start_time = sec;

///////////////////////////////////////////////////////////////////////////////////////////////
// ищем 3-й перевод строки -  время окончания регистрации 
///////////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	// перевод строки DOS
		x++;
		if (x == END_REG_NUM_STR) {
		    break;
		}
	    }
	}

	/* 3...Разбираем строку времени окончания регистрации */
	buf[2] = 0;

	// сначала 2 цифры на число
	strncpy(buf, str + j + 1, 2);
	time.day = atoi(buf);

	// месяц
	strncpy(buf, str + j + 4, 2);
	time.mon = atoi(buf);

	// год
	strncpy(buf, str + j + 7, 2);
	time.year = atoi(buf) + 2000;

	// часы
	strncpy(buf, str + j + 10, 2);
	time.hour = atoi(buf);

	// минуты
	strncpy(buf, str + j + 13, 2);
	time.min = atoi(buf);

	// секунды
	strncpy(buf, str + j + 16, 2);
	time.sec = atoi(buf);

	// 3. Время окончания регистрации
	sec = td_to_sec(&time);
	if (sec < 0) {
	    sec_to_str(sec, buf);
	    if (lang == lang_rus)
		sprintf(str, "Время окончания регистрации (%s) задано неверно!", buf);
	    else
		sprintf(str, "End of recording time (%s) set incorrect!", buf);
	    ERROR_BOX(str);
	    break;
	}

	my_param_struct.finish_time = sec;

//////////////////////////////////////////////////////////////////////////////////////////
//ищем 4-й перевод строки 
//////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* перевод строки (DOS или UNIX ?) */
		x++;
		if (x == BEGIN_BURN_NUM_STR) {
		    break;
		}
	    }
	}

	// 3... Разбираем строку времени всплытия
	buf[2] = 0;

	// сначала 2 цифры на число
	strncpy(buf, str + j + 1, 2);
	time.day = atoi(buf);

	// месяц
	strncpy(buf, str + j + 4, 2);
	time.mon = atoi(buf);

	// год
	strncpy(buf, str + j + 7, 2);
	time.year = atoi(buf) + 2000;

	// часы
	strncpy(buf, str + j + 10, 2);
	time.hour = atoi(buf);

	// минуты
	strncpy(buf, str + j + 13, 2);
	time.min = atoi(buf);

	// секунды
	strncpy(buf, str + j + 16, 2);
	time.sec = atoi(buf);

	// 3. перевести в секунды времени начала пережига
	sec = td_to_sec(&time);
	if (sec < 0 || sec <= (int) my_param_struct.finish_time) {
	    sec_to_str(sec, buf);
	    if (lang == lang_rus)
		sprintf(str, "Время начала пережига(%s)задано неверно!", buf);
	    else
		sprintf(str, "Burn wire start time (%s) set incorrect!", buf);
	    ERROR_BOX(str);
	    break;
	}
	my_param_struct.burn_time = sec;

/////////////////////////////////////////////////////////////////////////////////////////
// ищем 5-й перевод строки длительность пережига
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* перевод строки (DOS или UNIX ?) */
		x++;
		if (x == BURN_LEN_NUM_STR) {
		    break;
		}
	    }
	}

	strncpy(buf, str + j + 1, 4);	/* Длительность пережига - 3 цифры */
	sec = atoi(buf);
	if (sec < 1) {
	    if (lang == lang_rus)
		ERROR_BOX("Длительность пережига задана неверно. Должно быть более 1 секунды!");
	    else
		ERROR_BOX("Burn wire duration set incorrect. Must be more than 1 second!");

	    break;
	}
	my_param_struct.releburn_time = sec;

/////////////////////////////////////////////////////////////////////////////////////////
// ищем 6-й перевод строки длительность всплытия
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* перевод строки (DOS или UNIX ?) */
		x++;
		if (x == POPUP_LEN_NUM_STR) {
		    break;
		}
	    }
	}

	strncpy(buf, str + j + 1, 4);	/* Длительность всплытия  в минутах - 3 цыфры */
	sec = atoi(buf);
	if (sec < 1) {
	    if (lang == lang_rus)
		ERROR_BOX("Длительность всплытия задана неверно. Должно быть более 1 минуты!");
	    else
		ERROR_BOX("Popup duration set incorrect. Must be more than 1 minute!");

	    break;
	}
	my_param_struct.popup_len = sec;

/////////////////////////////////////////////////////////////////////////////////////////
// ищем 7-й перевод строки. Номер акустического модема 
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* перевод строки (DOS или UNIX ?) */
		x++;
		if (x == MODEM_NUM_NUM_STR) {
		    break;
		}
	    }
	}


	/* Номер акустического модема - 4 цыфры на это число! */
	strncpy(buf, str + j + 1, 4);
	my_param_struct.modem_num = atoi(buf);

/////////////////////////////////////////////////////////////////////////////////////////
// ищем 8-й перевод строки. Время аварийного всплытия от модема
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* перевод строки (DOS или UNIX ?) */
		x++;
		if (x == ALARM_TIME_NUM_STR) {
		    break;
		}
	    }
	}


	// 6... Разбираем строку времени всплытия
	buf[2] = 0;

	// сначала 2 цифры на число
	strncpy(buf, str + j + 1, 2);
	time.day = atoi(buf);

	// месяц
	strncpy(buf, str + j + 4, 2);
	time.mon = atoi(buf);

	// год
	strncpy(buf, str + j + 7, 2);
	time.year = atoi(buf) + 2000;

	// часы
	strncpy(buf, str + j + 10, 2);
	time.hour = atoi(buf);

	// минуты
	strncpy(buf, str + j + 13, 2);
	time.min = atoi(buf);

	// секунды
	strncpy(buf, str + j + 16, 2);
	time.sec = atoi(buf);

	// 6. перевести в секунды UTC
	sec = td_to_sec(&time);
	if ((my_param_struct.modem_num > 0 && sec < 1) || (my_param_struct.modem_num > 0 && sec < (int) my_param_struct.start_time)) {
	    if (lang == lang_rus)
		ERROR_BOX("Время аварийного всплытия от модема задано неверно или меньше времени старта!");
	    else
		ERROR_BOX("Modem alarm time set incorrect or less than recording start time!");
	    break;
	}
	my_param_struct.am3_popup_time = sec;

/////////////////////////////////////////////////////////////////////////////////////////
// ищем 9-й перевод строки. Время светлого времени суток
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* перевод строки (DOS или UNIX ?) */
		x++;
		if (x == DAY_TIME_NUM_STR) {
		    break;
		}
	    }
	}


	// Время светлого времени суток
	buf[2] = 0;

	// сначала 2 цифры на час
	strncpy(buf, str + j + 1, 2);
	my_param_struct.am3_cal_h0 = atoi(buf);

	// 2 цифры на минуты
	strncpy(buf, str + j + 4, 2);
	my_param_struct.am3_cal_m0 = atoi(buf);

	// еще 2 цифры на час
	strncpy(buf, str + j + 7, 2);
	my_param_struct.am3_cal_h1 = atoi(buf);

	// 2 цифры на минуты
	strncpy(buf, str + j + 10, 2);
	my_param_struct.am3_cal_m1 = atoi(buf);

/////////////////////////////////////////////////////////////////////////////////////////
// ищем 10-й перевод строки. Частота оцифровки.
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* перевод строки (DOS или UNIX ?) */
		x++;
		if (x == ADC_FREQ_NUM_STR) {
		    break;
		}
	    }
	}

	// 4 цифры на число 125, 250, 500, 1000, 2000, 4000
	strncpy(buf, str + j + 1, 5);
	my_param_struct.sample_freq = atoi(buf);

	// Ошибка в задании частоты
	if ((my_param_struct.sample_freq != 62) && (my_param_struct.sample_freq != 125) && 
	    (my_param_struct.sample_freq != 250) && (my_param_struct.sample_freq != 500) && 
            (my_param_struct.sample_freq != 1000) && (my_param_struct.sample_freq != 2000) && 
            (my_param_struct.sample_freq != 4000)) {
	    if (lang == lang_rus)
		ERROR_BOX("Ошибка задания частоты оцифровки в файле параметров!");
	    else
		ERROR_BOX("ADC sampling rate set incorrect in parameters file!");
	    break;
	}
/////////////////////////////////////////////////////////////////////////////////////////
// ищем 11-й перевод строки. Энергопотребление АЦП
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* перевод строки (DOS или UNIX ?) */
		x++;
		if (x == ADC_CONSUM_NUM_STR) {
		    break;
		}
	    }
	}

	// 3 символа hi или lo
	strncpy(buf, str + j + 1, 3);

	// В верхний регистр
	str_to_cap(buf, 2);

	// Что у нас записано?
	if (strncmp(buf, "HI", 2) == 0) {
	    my_param_struct.power_cons = 1;
	} else if (strncmp(buf, "LO", 2) == 0) {
	    my_param_struct.power_cons = 0;
	} else {
	    break;
	}


/////////////////////////////////////////////////////////////////////////////////////////
// ищем 12-й перевод строки. Усиление PGA
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* перевод строки (DOS или UNIX ?) */
		x++;
		if (x == ADC_PGA_NUM_STR) {
		    break;
		}
	    }
	}


	// 2 цифры на число PGA
	strncpy(buf, str + j + 1, 3);
	my_param_struct.pga_adc = atoi(buf);

	// Ошибка в задании усиления
	if ((my_param_struct.pga_adc != 1) && (my_param_struct.pga_adc != 2) && (my_param_struct.pga_adc != 4) && (my_param_struct.pga_adc != 8)
	    && (my_param_struct.pga_adc != 16) && (my_param_struct.pga_adc != 32) && (my_param_struct.pga_adc != 64)) {
	    if (lang == lang_rus)
		ERROR_BOX("Ошибка задания PGA в файле параметров!");
	    else
		ERROR_BOX("ADC PGA set incorrect in parameters file!");
	    break;
	}
/////////////////////////////////////////////////////////////////////////////////////////
// ищем 13-й перевод строки. Число байт в слове данных.
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* перевод строки (DOS или UNIX ?) */
		x++;
		if (x == MODEM_TYPE_NUM_STR) {
		    break;
		}
	    }
	}

	/* 2 цифры на число 3 или 4 */
	strncpy(buf, str + j + 1, 2);
	x = atoi(buf);
	if (x > 3 && x < 0) {
	    if (lang == lang_rus)
		ERROR_BOX("Ошибка задания типа модема!");
	    else
		ERROR_BOX("Error in modem type setting!");
	    break;
	}
	my_param_struct.am3_modem_type = x;
/////////////////////////////////////////////////////////////////////////////////////////
// ищем 14-й перевод строки. Используемые каналы АЦП. Справа налево
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* перевод строки (DOS или UNIX ?) */
		x++;
		if (x == ADC_BITMAP_NUM_STR) {
		    break;
		}
	    }
	}


	// 4 цифры на число 
	my_param_struct.on_off_channels = 0;
	strncpy(buf, str + j + 1, 5);

	// Смотрим ПО выключеию
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
// ищем 15-й перевод строки. Сколько часов писать файл данных
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* перевод строки (DOS или UNIX ?) */
		x++;
		if (x == FILE_LEN_NUM_STR) {
		    break;
		}
	    }
	}


	// 2 цифры на число
	strncpy(buf, str + j + 1, 3);
	j = atoi(buf);

	// В этих пределах - от часа до суток
	my_param_struct.data_file_len = (j > 0 && j < 25) ? j : 1;

/////////////////////////////////////////////////////////////////////////////////////////
// ищем 16-й перевод строки. Частота среза фильтра
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* перевод строки (DOS или UNIX ?) */
		x++;
		if (x == FLT_FREQ_NUM_STR) {
		    break;
		}
	    }
	}

	/* 7 цифр на число и дес. точку */
	strncpy(buf, str + j + 1, 7);
	my_param_struct.filter_freq = atof(buf);	/* В этих пределах - от 0 до ??? */

/////////////////////////////////////////////////////////////////////////////////////////
// ищем 17-й перевод строки. Постоянная регистрация
/////////////////////////////////////////////////////////////////////////////////////////
	x = 0;
	for (j = 0; j < bw - 1; j++) {
	    if (str[j] == '\n') {	/* перевод строки (DOS или UNIX ?) */
		x++;
		if (x == CONST_REG_NUM_STR) {
		    break;
		}
	    }
	}

	// 2 цыфры на число
	strncpy(buf, str + j + 1, 2);
	my_param_struct.const_reg_flag = ((atoi(buf) == 0) ? false : true);	/* В этих пределах - от 0 до ??? */
	res = 0;

	// проверяем  на соответсвие
	if (res == 0) {
	    if (strncmp(my_param_struct.my_str, check_param_struct->my_str, strlen(check_param_struct->my_str) - 5) != 0) {
		if (lang == lang_rus)
		    err += "Ошибка в коментарии, должно быть: " + String(check_param_struct->my_str);
		else
		    err += "Error in coments, need be: " + String(check_param_struct->my_str);
		res++;
	    }
	    // позиция
	    if (my_param_struct.pos != check_param_struct->pos) {
		if (lang == lang_rus)
		    err += "Ошибка в позиции, должно быть: " + IntToStr(check_param_struct->pos);
		else
		    err += "\nError in position, need be: " + IntToStr(check_param_struct->pos);
		res++;
	    }
	    // начало регистрации
	    if (my_param_struct.start_time != check_param_struct->start_time) {
		sec_to_str(check_param_struct->start_time, str);
		if (lang == lang_rus)
		    err += "\nОшибка времени старта, должно быть: " + String(str);
		else
		    err += "\nError in Start time, need be: " + String(str);
		res++;
	    }
	    // окончание регистрации
	    if (my_param_struct.finish_time != check_param_struct->finish_time) {
		sec_to_str(check_param_struct->finish_time, str);
		if (lang == lang_rus)
		    err += "\nОшибка времени окончания, должно быть: " + String(str);
		else
		    err += "\nError in Finish time, need be: " + String(str);
		res++;
	    }
	    // начало пережыга
	    if (my_param_struct.burn_time != check_param_struct->burn_time) {
		sec_to_str(check_param_struct->burn_time, str);
		if (lang == lang_rus)
		    err += "\nОшибка времени пережига, должно быть: " + String(str);
		else
		    err += "\nError in Burn time, need be: " + String(str);
		res++;
	    }
	    // длительность пережыга
	    if (my_param_struct.releburn_time != check_param_struct->releburn_time) {
		if (lang == lang_rus)
		    err += "\nОшибка продолжительности пережига, должно быть: " + IntToStr(check_param_struct->releburn_time);
		else
		    err += "\nError in Burn len, need be: " + IntToStr(check_param_struct->releburn_time);
		res++;
	    }
	    // длительнсть всплытия
	    if (my_param_struct.popup_len != check_param_struct->popup_len) {
		if (lang == lang_rus)
		    err += "\nОшибка продолжительности всплытия, должно быть: " + IntToStr(check_param_struct->popup_len);
		else
		    err += "\nError in Popup len, need be: " + IntToStr(check_param_struct->popup_len);
		res++;
	    }
	    // светлое врема суток
	    if (my_param_struct.am3_cal_h0 != check_param_struct->am3_cal_h0 &&
		my_param_struct.am3_cal_m0 != check_param_struct->am3_cal_m0 &&
		my_param_struct.am3_cal_h1 != check_param_struct->am3_cal_h1 && my_param_struct.am3_cal_m1 != check_param_struct->am3_cal_m1) {
		sprintf(str, "%02d:%02d - %02d:%02d",
			check_param_struct->am3_cal_h0, check_param_struct->am3_cal_m0, check_param_struct->am3_cal_h1, check_param_struct->am3_cal_m1);
		if (lang == lang_rus)
		    err += "\nОшибка светлого времени суток, должно быть: " + String(str);
		else
		    err += "\nError in Daytime, need be: " + String(str);
		res++;
	    }
	    // энергопотребление
	    if (my_param_struct.power_cons != check_param_struct->power_cons) {
		if (lang == lang_rus)

		    err += "\nОшибка потреблении, должно быть: " + IntToStr(check_param_struct->power_cons);
		else
		    err += "\nError in Power consumption, need be: " + IntToStr(check_param_struct->power_cons);
		res++;
	    }
	    // PGA
	    if (my_param_struct.pga_adc != check_param_struct->pga_adc) {
		if (lang == lang_rus)
		    err += "\nОшибка PGA, должно быть: " + IntToStr(check_param_struct->pga_adc);
		else
		    err += "\nError in PGA, need be: " + IntToStr(check_param_struct->pga_adc);
		res++;
	    }
	    // каналы
	    if (my_param_struct.on_off_channels != check_param_struct->on_off_channels) {
		if (lang == lang_rus)
		    err += "\nОшибка описания включенных каналов, должно быть: " + IntToStr(check_param_struct->on_off_channels);
		else
		    err += "\nError in Channel bitmap, need be: " + IntToStr(check_param_struct->on_off_channels);
		res++;
	    }
	    // частота фильтра
	    if (my_param_struct.filter_freq != check_param_struct->filter_freq) {
		if (lang == lang_rus)
		    err += "\nОшибка частоты фильтра, должно быть: " + FloatToStr(check_param_struct->filter_freq);
		else
		    err += "\nError in Filter freq, need be: " + FloatToStr(check_param_struct->filter_freq);
		res++;
	    }
	    // постоянноя регистрация
	    if (my_param_struct.const_reg_flag != check_param_struct->const_reg_flag) {
		if (lang == lang_rus)
		    err += "\nОшибка в постоянной регистрации, должно быть: " + IntToStr(check_param_struct->const_reg_flag);
		else
		    err += "\nError in Const reg, need be: " + IntToStr(check_param_struct->const_reg_flag);
		res++;
	    }
	    // частота оцыфровки
	    if (my_param_struct.sample_freq != check_param_struct->sample_freq) {
		if (lang == lang_rus)
		    err += "\nОшибка частоты дискретизации АЦП, должно быть: " + IntToStr(check_param_struct->sample_freq);
		else
		    err += "\nError in Sample freq, need be: " + IntToStr(check_param_struct->sample_freq);
		res++;
	    }
	    // Тип модема
	    if (my_param_struct.am3_modem_type != check_param_struct->am3_modem_type) {
		if (lang == lang_rus)
		    err += "\nОшибка типа модема, должно быть: " + IntToStr(check_param_struct->am3_modem_type);
		else
		    err += "\nError in Modem type, need be: " + IntToStr(check_param_struct->am3_modem_type);
		res++;
	    }
	    // номер модема
	    if (my_param_struct.modem_num != check_param_struct->modem_num) {
		if (lang == lang_rus)
		    err += "\nОшибка в номере модема, должно быть: " + IntToStr(check_param_struct->modem_num);
		else
		    err += "\nError in Modem number, need be: " + IntToStr(check_param_struct->modem_num);
		res++;
	    }
	    // Время подъема по модему
	    if (my_param_struct.am3_popup_time != check_param_struct->am3_popup_time) {
		sec_to_str(check_param_struct->am3_popup_time, str);
		if (lang == lang_rus)
		    err += "\nОшибка времени аварийного всплытия по модему, должно быть: " + String(str);
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
	    INFO_BOX("Параметры в файле проверены, ошибок и несоответствий не найдено!");
	else
	    INFO_BOX("Parameters in file are checked, errors not found!");
    }
}

//---------------------------------------------------------------------------
