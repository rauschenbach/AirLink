//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop
#include "time.h"
#include "utils.h"
#include "Main.h"
#include "SaveFileThread.h"
#pragma package(smart_init)


//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall SaveFileThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall SaveFileThread::SaveFileThread(bool CreateSuspended)
:TThread(CreateSuspended)
{
}

//---------------------------------------------------------------------------
#define    param_struct frmMain->param_struct
void __fastcall SaveFileThread::Execute()
{
    char str[MAX_FILE_SIZE];	/* Создается в стеке  */
    TIME_DATE td;
    String data;
    c8 buf[128];
    c8 buf1[128];
    c8 buf2[128];
    struct tm dir_time;
    SYSTEMTIME st;
    HANDLE fd0;
    HANDLE fd1;
    BOOL res;
    myLangID lang;
    float f;
    unsigned long bw, i, j;	/* В стиле DOS-UNIX, откроеца в любой ОС  */
    int num, t0;


    do {
	lang = frmMain->GetLangID();

	frmMain->sdParamFile->FileName = "recparam.cfg";

	// начальная директория
	frmMain->sdParamFile->InitialDir = String(frmMain->dcbDisk->Drive) + ":";


	// Чтобы лишних скобок не ставить
	if (frmMain->sdParamFile->Execute() == false)
	    break;


	frmMain->LogOut("--------------------------------------------------");
	data = ExtractFileDrive(frmMain->sdParamFile->FileName);

	if (frmMain->VolumeIsFat(data) == false) {
	    if (lang == lang_rus)
		WARN_BOX("Этот диск не содержит FAT32 или ExFAT!");
	    else
		WARN_BOX("This disk doesn't contain FAT32 or ExFAT!");
	    //   return;
	}
	//----------------- Открываем
	fd0 = CreateFile(frmMain->sdParamFile->FileName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fd0 == INVALID_HANDLE_VALUE) {
	    if (lang == lang_rus)
		DisplayMessage("Не могу создать файл параметров");
	    else
		DisplayMessage("Can't create parameters file");
	    break;
	}
	//----------------- Строка с предупреждением  не более 80-ти символов
	frmMain->edSampleString->GetTextBuf(buf, 80);
	memcpy(param_struct.my_str, buf, strlen(buf));

	/* убрать переносы */
	for (i = 0; i < 80; i++) {
	    if (buf[i] == '\r' || buf[i] == '\n') {
		buf[i] = 0;
		break;
	    }
	}
	data = "//" + String(buf) + "\r\n";

	WriteFile(fd0, data.c_str(), data.Length(), &bw, NULL);
	memset(str, 0, sizeof(str));
	frmMain->LogOut(data.c_str());



	//----------------- Позиция
	frmMain->edPosition->GetTextBuf(buf, 10);
	param_struct.pos = StrToInt(frmMain->edPosition->Text);
	if (lang == lang_rus)
	    data = String(buf) + "   \t\t\t// Позиция установки\r\n";
	else
	    data = String(buf) + "   \t\t\t// SPN survey location number\r\n";


	WriteFile(fd0, data.c_str(), data.Length(), &bw, NULL);
	memset(str, 0, sizeof(str));
	memcpy(str, data.c_str(), strlen(data.c_str()) - 2);
	frmMain->LogOut(str);



	//----------------- начало регистрации
	frmMain->dtStartDate->GetTextBuf(buf1, 10);
	data = String(buf1) + " ";
	frmMain->dtStartTime->GetTextBuf(buf2, 10);
	if (lang == lang_rus)
	    data += String(buf2) + "  \t// Начало регистрации, время UTC\r\n";
	else
	    data += String(buf2) + "  \t// Start recording time, UTC\r\n";


	WriteFile(fd0, data.c_str(), data.Length(), &bw, NULL);
	memset(str, 0, sizeof(str));
	memcpy(str, data.c_str(), strlen(data.c_str()) - 2);
	frmMain->LogOut(str);
	param_struct.start_time = bufs_to_st(buf1, buf2, &st);	// время старта



	//----------------- окончание регистрации
	frmMain->dtFinishDate->GetTextBuf(buf1, 10);
	data = String(buf1) + " ";
	frmMain->dtFinishTime->GetTextBuf(buf2, 10);

	if (lang == lang_rus)
	    data += String(buf2) + "  \t// Окончание регистрации, время UTC\r\n";
	else
	    data += String(buf2) + "  \t// End recording time, UTC\r\n";


	WriteFile(fd0, data.c_str(), data.Length(), &bw, NULL);
	memset(str, 0, sizeof(str));
	memcpy(str, data.c_str(), data.Length() - 2);
	frmMain->LogOut(str);
	param_struct.finish_time = bufs_to_st(buf1, buf2, &st);	// время окончания


	//----------------- начало пережига
	frmMain->dtBurnDate->GetTextBuf(buf1, 10);
	data = String(buf1) + " ";
	frmMain->dtBurnTime->GetTextBuf(buf2, 10);

	if (lang == lang_rus)
	    data += String(buf2) + "  \t// Начало пережига, время UTC\r\n";
	else
	    data += String(buf2) + "  \t// Burn wire start time, UTC\r\n";

	WriteFile(fd0, data.c_str(), data.Length(), &bw, NULL);
	memset(str, 0, sizeof(str));
	memcpy(str, data.c_str(), data.Length() - 2);
	frmMain->LogOut(str);
	param_struct.burn_time = bufs_to_st(buf1, buf2, &st);	// время начала пережига



	//----------------- длительность пережига проволки в секундах
	param_struct.releburn_time = frmMain->udBurnTime->Position;

	if (lang == lang_rus)
	    data = IntToStr(param_struct.releburn_time) + "   \t\t\t// Длительность пережига проволоки в секундах\r\n";
	else
	    data = IntToStr(param_struct.releburn_time) + "   \t\t\t// Burn wire duration in seconds\r\n";


	WriteFile(fd0, data.c_str(), data.Length(), &bw, NULL);
	memcpy(str, data.c_str(), data.Length() - 2);
	frmMain->LogOut(str);



	//----------------- длительность всплытия + убрать нули
	param_struct.popup_len = frmMain->udPopupLen->Position;

	if (lang == lang_rus)
	    data = IntToStr(param_struct.popup_len) + "   \t\t\t// Длительность всплытия в минутах\r\n";
	else
	    data = IntToStr(param_struct.popup_len) + "   \t\t\t// SPN rising time in minutes\r\n";


	WriteFile(fd0, data.c_str(), data.Length(), &bw, NULL);
	memset(str, 0, sizeof(str));
	memcpy(str, data.c_str(), data.Length() - 2);
	frmMain->LogOut(str);

	//----------------- Номер модема смотрим по выпадающему списку
	frmMain->edModemNum->GetTextBuf(buf, 5);
	num = atoi(buf);
	param_struct.modem_num = num;

	if (lang == lang_rus)
	    data = IntToStr(num) + "   \t\t\t// Номер модема: 0..9999, 0 - не опрашивать\r\n";
	else
	    data = IntToStr(num) + "   \t\t\t// Modem number: 0..9999, 0 - don't address\r\n";


	WriteFile(fd0, data.c_str(), data.Length(), &bw, NULL);
	memset(str, 0, sizeof(str));
	memcpy(str, data.c_str(), data.Length() - 2);
	frmMain->LogOut(str);


	//----------------- Время аварийного всплытия
	frmMain->dtAm3PopupDate->GetTextBuf(buf1, 10);
	data = String(buf1) + " ";
	frmMain->dtAm3PopupTime->GetTextBuf(buf2, 10);

	if (lang == lang_rus)
	    data += String(buf2) + "  \t// Время аварийного всплытия от модема, время UTC\r\n";
	else
	    data += String(buf2) + "  \t// Modem alarm time, UTC\r\n";


	WriteFile(fd0, data.c_str(), data.Length(), &bw, NULL);
	memset(str, 0, sizeof(str));
	memcpy(str, data.c_str(), data.Length() - 2);
	frmMain->LogOut(str);
	param_struct.am3_popup_time = bufs_to_st(buf1, buf2, &st);


	//----------------- Светлое время суток
	frmMain->meAm3Cal0->GetTextBuf(buf, 6);
	memcpy(buf1, buf, strlen(buf));
	buf1[2] = 0;
	param_struct.am3_cal_h0 = atoi(buf1);
	memcpy(buf1, buf + 3, strlen(buf) - 3);
	buf1[5] = 0;
	param_struct.am3_cal_m0 = atoi(buf1);


	data = String(buf) + "-";
	frmMain->meAm3Cal1->GetTextBuf(buf, 6);
	memcpy(buf1, buf, strlen(buf));
	buf1[2] = 0;
	param_struct.am3_cal_h1 = atoi(buf1);
	memcpy(buf1, buf + 3, strlen(buf) - 3);
	buf1[5] = 0;
	param_struct.am3_cal_m1 = atoi(buf1);

	if (lang == lang_rus)
	    data += String(buf) + "  \t\t// Светлое время суток\r\n";
	else
	    data += String(buf) + "  \t\t// Daytime\r\n";


	WriteFile(fd0, data.c_str(), data.Length(), &bw, NULL);
	memset(str, 0, sizeof(str));
	memcpy(str, data.c_str(), data.Length() - 2);
	frmMain->LogOut(str);


	//----------------- Частота оцифровки
	if (lang == lang_rus)
	    data = (*frmMain->cbAdcSample->Items)[frmMain->cbAdcSample->ItemIndex] + "  \t\t\t// Частота оцифровки АЦП\r\n";
	else
	    data = (*frmMain->cbAdcSample->Items)[frmMain->cbAdcSample->ItemIndex] + "  \t\t\t// ADC sampling rate\r\n";



	param_struct.sample_freq = StrToInt((*frmMain->cbAdcSample->Items)[frmMain->cbAdcSample->ItemIndex]);
	WriteFile(fd0, data.c_str(), data.Length(), &bw, NULL);
	memset(str, 0, sizeof(str));
	memcpy(str, data.c_str(), data.Length() - 2);
	frmMain->LogOut(str);



	//----------------- Энергопотрбление
	if (lang == lang_rus)
	    data = (frmMain->cbAdcCons->ItemIndex == 0 ? "Lo" : "Hi") + String("  \t\t\t// Энергопотребление АЦП\r\n");
	else
	    data = (frmMain->cbAdcCons->ItemIndex == 0 ? "Lo" : "Hi") + String("  \t\t\t// ADC power consumption\r\n");

	param_struct.power_cons = frmMain->cbAdcCons->ItemIndex;
	WriteFile(fd0, data.c_str(), data.Length(), &bw, NULL);
	memset(str, 0, sizeof(str));
	memcpy(str, data.c_str(), data.Length() - 2);
	frmMain->LogOut(str);


	//------------------ PGA АЦП
	if (lang == lang_rus)
	    data = (*frmMain->cbAdcPGA->Items)[frmMain->cbAdcPGA->ItemIndex] + "  \t\t\t// PGA АЦП\r\n";
	else
	    data = (*frmMain->cbAdcPGA->Items)[frmMain->cbAdcPGA->ItemIndex] + "  \t\t\t// PGA ADC\r\n";



	param_struct.pga_adc = StrToInt((*frmMain->cbAdcPGA->Items)[frmMain->cbAdcPGA->ItemIndex]);
	WriteFile(fd0, data.c_str(), data.Length(), &bw, NULL);
	memset(str, 0, sizeof(str));
	memcpy(str, data.c_str(), data.Length() - 2);
	frmMain->LogOut(str);


	//----------------- Тип модема смотрим по выпадающему списку
	num = frmMain->cbModemNum->ItemIndex;
	param_struct.am3_modem_type = num;
	if (lang == lang_rus)
	    data = IntToStr(num) + "   \t\t\t// Тип модема: 0 - нет, 1 - старый, 2 - AM3, 3 - бентос\r\n";
	else
	    data = IntToStr(num) + "   \t\t\t// Modem type: 0 - none, 1 - old, 2 - AM3, 3 - Bentos\r\n";


	WriteFile(fd0, data.c_str(), data.Length(), &bw, NULL);
	memset(str, 0, sizeof(str));
	memcpy(str, data.c_str(), data.Length() - 2);
	frmMain->LogOut(str);


	// Включенные каналы
	// 4 цифры на число.        Смотрим ПО выключеию
	sprintf(buf, "%01d%01d%01d%01d",
		(frmMain->cbChan4->Checked ? 1 : 0), (frmMain->cbChan3->Checked ? 1 : 0), (frmMain->cbChan2->Checked ? 1 : 0), (frmMain->cbChan1->Checked ? 1 : 0));

	param_struct.on_off_channels = 0;
	param_struct.on_off_channels = 0x0;
	if (buf[0] != '0')
	    param_struct.on_off_channels |= 0x08;
	if (buf[1] != '0')
	    param_struct.on_off_channels |= 0x04;
	if (buf[2] != '0')
	    param_struct.on_off_channels |= 0x02;
	if (buf[3] != '0')
	    param_struct.on_off_channels |= 0x01;

	if (lang == lang_rus)
	    data = String(buf) + "  \t\t\t// Включенные каналы: h-z-y-x\r\n";
	else
	    data = String(buf) + "  \t\t\t// Channels ON: h-z-y-x\r\n";



	WriteFile(fd0, data.c_str(), data.Length(), &bw, NULL);
	memset(str, 0, sizeof(str));
	memcpy(str, data.c_str(), data.Length() - 2);
	frmMain->LogOut(str);


	// Размер файла данных
	i = (frmMain->cbDataFileLen->ItemIndex == 0) ? 1 : frmMain->cbDataFileLen->ItemIndex == 1 ? 4 : 24;
	param_struct.data_file_len = i;
	if (lang == lang_rus)
	    data = IntToStr(i) + "  \t\t\t// Размер файла данных\r\n";
	else
	    data = IntToStr(i) + "  \t\t\t// Size of data file\r\n";

	WriteFile(fd0, data.c_str(), data.Length(), &bw, NULL);
	memset(str, 0, sizeof(str));
	memcpy(str, data.c_str(), data.Length() - 2);
	frmMain->LogOut(str);


	// Частота среза фильтра
	f = frmMain->seFreq->Value;
	param_struct.filter_freq = f;

	if (lang == lang_rus)
	    sprintf(buf, "%1.4f   \t\t// %s \r\n", f, "Частота среза ФВЧ");
	else
	    sprintf(buf, "%1.4f   \t\t// %s \r\n", f, "Filter low cut frequency");

	WriteFile(fd0, buf, strlen(buf), &bw, NULL);
	memset(str, 0, sizeof(str));
	memcpy(str, data.c_str(), data.Length() - 2);
	frmMain->LogOut(str);



	// Постоянная регистрация
	i = (frmMain->cbConstReg->Checked == false ? 0 : 1);

	param_struct.const_reg_flag = i;

	if (lang == lang_rus)
	    data = IntToStr(i) + "   \t\t\t// Постоянная регистрация\r\n";
	else
	    data = IntToStr(i) + "   \t\t\t// Continuous recording\r\n";

	WriteFile(fd0, data.c_str(), data.Length(), &bw, NULL);
	memset(str, 0, sizeof(str));
	memcpy(str, data.c_str(), data.Length() - 2);
	frmMain->LogOut(str);
	frmMain->LogOut("--------------------------------------------------");

	// Закроем файл
	CloseHandle(fd0);

	if (lang == lang_rus)
	    sprintf(buf, "Командный файл \"recparam.cfg\" для станции %d записан на диск %s",
		    frmMain->port_set[frmMain->cbPortName->ItemIndex].gns_name, ExtractFilePath(frmMain->sdParamFile->FileName).c_str());
	else
	    sprintf(buf, "Parameters file \"recparam.cfg\" for SPN %d was written on disk %s",
		    frmMain->port_set[frmMain->cbPortName->ItemIndex].gns_name, ExtractFilePath(frmMain->sdParamFile->FileName).c_str());


	frmMain->LogOut(buf);


	// Должен быть путь!!!
	data = ExtractFileDir(frmMain->sdParamFile->FileName) + "\\lock.fil";

	// Лок-файл
	fd1 = CreateFile(data.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fd1 == INVALID_HANDLE_VALUE) {
	    if (lang == lang_rus)
		DisplayMessage("Не могу создать Lock-file");
	    else
		DisplayMessage("Can't create Lock-file");
	    break;
	}

	if (WriteFile(fd1, "lock-file", 9, &bw, NULL) == false) {
	    if (lang == lang_rus)
		DisplayMessage("Не могу сохранить Lock-file");
	    else
		DisplayMessage("Can't save Lock-file");
	}

	CloseHandle(fd1);

	// Создадим копию файла в папке LOGS
	t0 = time(NULL);
	sec_to_td(t0, &td);
	data = ExtractFilePath(Application->ExeName) + "LOGS";
	res = CreateDirectory(data.c_str(), NULL);


	// Имя файла
	sprintf(buf1, "%s\\%d_%d_%d_%02d%02d%02d_%02d%02d.cfg\0",
		data.c_str(), param_struct.pos, frmMain->gns_num,
                param_struct.am3_modem_type == 0 ? 0 : param_struct.modem_num,
                td.day, td.month, td.year - 2000, td.hour, td.min);
	res = CopyFile(frmMain->sdParamFile->FileName.c_str(), buf1, FALSE);


	if (lang == lang_rus)
	    sprintf(buf, "Lock файл записан на диск %s,копия сохранена как %s. Проверьте подключение модема!!!", ExtractFilePath(frmMain->sdParamFile->FileName).c_str(), buf1);
	else
	    sprintf(buf, "Lock file was written on the disk %s, copy was saved as %s. Check modem connection!!!", ExtractFilePath(frmMain->sdParamFile->FileName).c_str(), buf1);
	frmMain->LogOut(buf);

//    SetFileAttributes(frmMain->sdParamFile->FileName.c_str(), FILE_ATTRIBUTE_READONLY);

	data = ExtractFileDrive(frmMain->sdParamFile->FileName);
	frmMain->dcbDisk->Drive = (data.c_str())[0];
    } while (0);
}

//---------------------------------------------------------------------------
void SaveFileThread::DisplayMessage(char *s)
{
    char str[512];
    u32 bw;
    LPVOID lpMsgBuf;

    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) & lpMsgBuf, 0, NULL);


    sprintf(str, "%s: %s", s, lpMsgBuf);
    frmMain->LogOut(str);

    ERROR_BOX(str);

    LocalFree(lpMsgBuf);	// Free the buffer.
}

//---------------------------------------------------------------------------
