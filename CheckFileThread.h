//---------------------------------------------------------------------------

#ifndef CheckFileThreadH
#define CheckFileThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "my_cmd.h"
//---------------------------------------------------------------------------
class CheckFileThread : public TThread
{            
private:
protected:
        void __fastcall Execute();
        String dir;
        param_file_struct  *check_param_struct;
        param_file_struct  my_param_struct;
public:
        __fastcall CheckFileThread(String, void*,  bool);
};
//---------------------------------------------------------------------------
#endif
