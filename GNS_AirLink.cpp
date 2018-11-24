//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <time.h>
#include <time.h>
#include <stdio.h>
//---------------------------------------------------------------------------
USEFORM("main.cpp", frmMain);
USEFORM("const.cpp", frmConst);
USEFORM("About.cpp", frmAbout);
USEFORM("number.cpp", frmNumber);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  HANDLE hWnd = NULL;
  DecimalSeparator = '.';


  hWnd = FindWindow(NULL, "GNS AirLink");
  if(hWnd){
           ShowWindow(hWnd, SW_SHOWNORMAL);
           return 0;
  } else
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TfrmMain), &frmMain);
                 Application->CreateForm(__classid(TfrmConst), &frmConst);
                 Application->CreateForm(__classid(TfrmAbout), &frmAbout);
                 Application->CreateForm(__classid(TfrmNumber), &frmNumber);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }


     return 0;
}
//---------------------------------------------------------------------------
