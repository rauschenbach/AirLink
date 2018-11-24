//---------------------------------------------------------------------------																																																																																
#include <vcl.h>                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
#pragma hdrstop
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include "const.h"
#include "proto.h"
#include "main.h"
#include "globdefs.h"
#include "utils.h"
#include "WriteCommandThread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BMSpinEdit"
#pragma resource "*.dfm"
TfrmConst *frmConst;

//---------------------------------------------------------------------------
__fastcall TfrmConst::TfrmConst(TComponent * Owner)
:TForm(Owner)
{
}

//----------------------------------------------------------------------------
// Выведем один раз старые значения
//static int b = 0;
void __fastcall TfrmConst::FormActivate(TObject * Sender)
{
    char str[128];

    if (GetConst(&regs) == 0) {
	seOffsetX->Value = (int)regs.chan[0].offset;
	seGainX->Value = regs.chan[0].gain;

	seOffsetY->Value = (int)regs.chan[1].offset;
	seGainY->Value = (int)regs.chan[1].gain;

	seOffsetZ->Value = (int)regs.chan[2].offset;
	seGainZ->Value = (int)regs.chan[2].gain;

	seOffsetH->Value = (int)regs.chan[3].offset;
	seGainH->Value = (int)regs.chan[3].gain;

/*
        frmMain->PrintLog("offset: ",(u8*) &off, 4);
        frmMain->PrintLog("gain: ", (u8*)&gain, 4);
        frmMain->PrintLog("offset: ", (u8*)&regs.chan[1].offset, 4);
        frmMain->PrintLog("gain: ", (u8*)&regs.chan[1].gain, 4);
        frmMain->PrintLog("offset: ", (u8*)&regs.chan[2].offset, 4);
        frmMain->PrintLog("gain: ", (u8*)&regs.chan[2].gain, 4);
        frmMain->PrintLog("offset: ", (u8*)&regs.chan[3].offset, 4);
        frmMain->PrintLog("gain: ", (u8*)&regs.chan[3].gain, 4);
  */
    }
}

//---------------------------------------------------------------------------
void __fastcall TfrmConst::btnDefaultClickClick(TObject * Sender)
{
    // Восстановить дефолтные значения
    seOffsetX->Value = 64000;
    seOffsetY->Value = 64000;
    seOffsetZ->Value = 64000;
    seOffsetH->Value = 64000;

    seGainX->Value = 0x400000;
    seGainY->Value = 0x400000;
    seGainZ->Value = 0x400000;
    seGainH->Value = 0x400000;
}
//---------------------------------------------------------------------------
 // Переписываем для передачи
void __fastcall TfrmConst::btnOkClick(TObject * Sender)
{
    WriteCommandThread *thread;
    char str[128];
    int num;

    regs.chan[0].offset = seOffsetX->Value;
    regs.chan[0].gain = seGainX->Value;


    regs.chan[1].offset = seOffsetY->Value;
    regs.chan[1].gain = seGainY->Value;

    regs.chan[2].offset = seOffsetZ->Value;
    regs.chan[2].gain = seGainZ->Value;

    regs.chan[3].offset = seOffsetH->Value;
    regs.chan[3].gain = seGainH->Value;
    regs.magic = MAGIC;

    thread = new WriteCommandThread(SetConst, &regs, false, false);
    thread->WaitFor();
    delete thread;
}

//---------------------------------------------------------------------------
