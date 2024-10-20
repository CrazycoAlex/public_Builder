//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("TestUnit.cpp", TestForm);
USEFORM("OptionsUnit.cpp", OptionsForm);
USEFORM("PasswUnit.cpp", PasswForm);
USEFORM("MainUnit.cpp", MainForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Тест по авторскому праву";
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TTestForm), &TestForm);
                 Application->CreateForm(__classid(TOptionsForm), &OptionsForm);
                 Application->CreateForm(__classid(TPasswForm), &PasswForm);
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
