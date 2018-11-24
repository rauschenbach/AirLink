//---------------------------------------------------------------------------

#ifndef ModemCommandThreadH
#define ModemCommandThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class ModemCommandThread : public TThread
{            
private:
      void* parameter;

protected:
        void __fastcall Execute();
public:
        __fastcall ModemCommandThread(void* p, bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
