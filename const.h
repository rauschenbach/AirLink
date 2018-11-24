//---------------------------------------------------------------------------

#ifndef constH
#define constH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <ComCtrls.hpp>
#include "BMSpinEdit.h"
#include "globdefs.h"
#include "my_cmd.h"

//---------------------------------------------------------------------------
class TfrmConst : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TBMSpinEdit *seOffsetX;
        TBMSpinEdit *seOffsetY;
        TBMSpinEdit *seOffsetZ;
        TBMSpinEdit *seGainX;
        TBMSpinEdit *seGainY;
        TBMSpinEdit *seGainZ;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TBMSpinEdit *seOffsetH;
        TBMSpinEdit *seGainH;
        TLabel *Label6;
        TCheckBox *cbConstWrite;
        TBitBtn *btnOk;
        TBitBtn *BitBtn1;
        TBitBtn *btnDefaultClick;
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall btnOkClick(TObject *Sender);
        void __fastcall btnDefaultClickClick(TObject *Sender);
private:	// User declarations
         ADS1282_Regs regs;
public:		// User declarations
        __fastcall TfrmConst(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmConst *frmConst;
//---------------------------------------------------------------------------
#endif
