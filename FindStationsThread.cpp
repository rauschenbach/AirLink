//---------------------------------------------------------------------------
// ��� ������ ������� �� ��������� COM ������
#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include "main.h"
#include "about.h"
#include "globdefs.h"
#include "utils.h"
#include "FindStationsThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall FindStationsThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
static int stations = 0;
static bool enter = false;

__fastcall FindStationsThread::FindStationsThread(bool CreateSuspended):
TThread(CreateSuspended)
{
}

//---------------------------------------------------------------------------
void __fastcall FindStationsThread::Execute()
{
    //---- Place thread code here ----
    int i, j = 0, k;
    u32 num;
    u8 buf[128];
    bool res;
    int baud;
    static t1 = 0;
    char str[128];

    enter = true;


    frmMain->sbRunModule->Down = false;
    frmMain->cbPortName->Items->Clear();	// �������� ������ ������

    if (t1 % 2 == 0) {
	if (frmMain->GetLangID() == lang_rus)
	    frmMain->sbInfo->Panels->Items[0]->Text = "����� �������";
	else
	    frmMain->sbInfo->Panels->Items[0]->Text = "Searching SPN...";
    } else {
	frmMain->sbInfo->Panels->Items[0]->Text = "";
    }
    t1++;

    // 255 ������
    for (i = 0; i < 255; i++) {
	frmMain->PortName = "\\\\.\\COM" + IntToStr(i + 1);

	buf[0] = 0xff;
	buf[1] = 0x00;
	buf[2] = 0x01;		/* ������� ���� ����� */
	buf[3] = 0x01;		/* ������� "��� �� ����?"   */
	add_crc16(buf);

	// 6 ����� ��������, 10 �������!!!
//        frmMain->port_set[j].baud = UART_BAUD_RATE;


	// ������ ���� ���������� �� 2-� ���������
	num =
	    frmMain->Querry(frmMain->PortName, buf, 6,
			    (u8 *) & frmMain->dev_addr,
			    sizeof(DEV_ADDR_STRUCT), &baud);
	memcpy(buf, (u8 *) & frmMain->dev_addr, sizeof(DEV_ADDR_STRUCT));	// ���� �� ����������-������!!!


	if (num == sizeof(DEV_ADDR_STRUCT) && test_crc16(buf) == 0) {	// len �.� == 5 + (1 len + 2 ����� crc16)
	    frmMain->port_set[j].port_num = i + 1;
	    frmMain->port_set[j].gns_name = frmMain->dev_addr.addr;
	    frmMain->port_set[j].baud = baud;	// ��������� ��������

	    if (frmMain->dev_addr.addr > 0 && frmMain->dev_addr.addr < 7)
		frmMain->port_set[j].board = 'A';
	    else if (frmMain->dev_addr.addr >= 7
		     && frmMain->dev_addr.addr < 10)
		frmMain->port_set[j].board = 'B';
	    else if (frmMain->dev_addr.addr >= 10
		     && frmMain->dev_addr.addr < 10000)
		frmMain->port_set[j].board = 'C';
	    else
		frmMain->port_set[j].board = 'Z';

	    ver_to_str(&frmMain->dev_addr, str);
	    frmMain->port_set[j].v = frmMain->dev_addr.ver;
	    frmMain->port_set[j].r = frmMain->dev_addr.rev;
	    frmMain->port_set[j].ver = String(str);

	    if (frmMain->GetLangID() == lang_rus) {
		sprintf(buf,
			"���������� ������� GNS%04d �� ����� COM%d (%d ���/�). ������ �� ������������: %s",
			frmMain->port_set[j].gns_name, i + 1, baud,
			frmMain->port_set[j].ver.c_str());
	    } else {
		sprintf(buf,
			"Found SPN: GNS%04d on COM%d (%d bit per sec). Recorder ver: %s",
			frmMain->port_set[j].gns_name, i + 1, baud,
			frmMain->port_set[j].ver.c_str());
	    }

	    frmMain->LogOut((char *) buf);
	    sprintf(buf, "GNS%04d", frmMain->port_set[j].gns_name);
	    frmMain->cbPortName->Items->Add((char *) buf);	// ��������� �������
	    frmMain->cbPortName->ItemIndex = j;	// ������ ������ combobox
	    j++;
	    if (frmMain->GetLangID() == lang_rus)
		frmMain->sbInfo->Panels->Items[0]->Text = "������� �������";
	    else
		frmMain->sbInfo->Panels->Items[0]->Text = "SPN found";
	}
    }
    if (j <= 0) {		// ���� ���������
//       frmMain->LogOut("������� �� �������!");
    }
    stations = j;
    enter = false;
}

//---------------------------------------------------------------------------
int get_num_station()
{
    return stations;
}

//---------------------------------------------------------------------------
void reset_num_station()
{
    stations = 0;
}

//---------------------------------------------------------------------------
bool no_enter(void)
{
    return enter;
}

//---------------------------------------------------------------------------
