//---------------------------------------------------------------------------

#ifndef SaveFileThreadH
#define SaveFileThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class SaveFileThread : public TThread
{            
private:
protected:
        void __fastcall Execute();
public:
        __fastcall SaveFileThread(bool CreateSuspended);
        void DisplayMessage(char* s);
};
//---------------------------------------------------------------------------
#endif
