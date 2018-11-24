//---------------------------------------------------------------------------

#ifndef OpenFileThreadH
#define OpenFileThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class OpenFileThread : public TThread
{            
private:
        String FName;
protected:
        void __fastcall Execute();
public:
        __fastcall OpenFileThread(String name, bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
