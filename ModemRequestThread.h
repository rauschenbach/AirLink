//---------------------------------------------------------------------------

#ifndef ModemRequestThreadH
#define ModemRequestThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class ModemRequestThread : public TThread
{            
private:
protected:
        void __fastcall Execute();
public:
        __fastcall ModemRequestThread(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
