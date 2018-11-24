//---------------------------------------------------------------------------

#ifndef numberH
#define numberH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
#include "globdefs.h"
//---------------------------------------------------------------------------
class TfrmNumber : public TForm
{
__published:	// IDE-managed Components
        TMaskEdit *meDevNum;
        TBitBtn *btnSet;
        TLabel *Label1;
        TBitBtn *BitBtn1;
        void __fastcall btnSetClick(TObject *Sender);
private:	// User declarations
        u16 num;
public:		// User declarations
        __fastcall TfrmNumber(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmNumber *frmNumber;
//---------------------------------------------------------------------------
#endif
