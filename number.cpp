//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop
#include "WriteCommandThread.h"
#include "number.h"
#include "main.h"
#include "proto.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmNumber *frmNumber;
//---------------------------------------------------------------------------
__fastcall TfrmNumber::TfrmNumber(TComponent * Owner)
:TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TfrmNumber::btnSetClick(TObject * Sender)
{
    WriteCommandThread *thread;
    char buf[64];
    int i;

    i = frmMain->cbPortName->ItemIndex;
    meDevNum->GetTextBuf(buf, 5);
    num = atoi(buf);		// номер модуля (станции)

    if (num > 9999 || num < 1) {
	if (frmMain->GetLangID() == lang_rus)
		INFO_BOX("Номер станции должен быть в пределах от 1 до 9999!");
	else
		INFO_BOX("SPN number must be in range from 1 to 9999!");
	return;
    }
    thread = new WriteCommandThread(SetId, &num, false, false);
    thread->WaitFor();
    delete thread;

    /* num = StrToInt(cbPortName->Items->Strings[cbPortName->ItemIndex]); */

    sprintf(buf, "GNS%04d", num);
    frmMain->cbPortName->Items[frmMain->cbPortName->ItemIndex].SetText(buf);
    frmMain->cbPortName->ItemIndex = i;
//    frmMain->lbBoard->Caption = frmMain->port_set[frmMain->cbPortName->ItemIndex].board;
//    frmMain->lbBoard->Font->Color = clBlack;
}

//---------------------------------------------------------------------------
