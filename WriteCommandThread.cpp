//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#pragma hdrstop
#include "globdefs.h"
#include "proto.h"
#include "main.h"
#include "WriteCommandThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall WriteCommandThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall WriteCommandThread::WriteCommandThread(void *func, void* p, bool a, bool CreateSuspended)
        : TThread(CreateSuspended)
{
     param = p;
     app = a;
     thread_func = (void (*)(void*)) func;
}
//---------------------------------------------------------------------------
void __fastcall WriteCommandThread::Execute()
{
    // char *str = "$RSAPR,,*162f\r\n";

    /* Вызываем thread_func, если он установлен */
    if (thread_func != NULL) {
	thread_func(param);

        /*
        // Для команд SET
        if(app == true) {
             Sleep(100);
             SendAnyCommand(str);
            }
         */

     }

}
//---------------------------------------------------------------------------
