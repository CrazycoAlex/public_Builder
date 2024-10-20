//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "OptionsUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOptionsForm *OptionsForm;
extern float TimeTest;
//---------------------------------------------------------------------------
__fastcall TOptionsForm::TOptionsForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------




void __fastcall TOptionsForm::DBNavigatorQuestClick(TObject *Sender,TNavigateBtn Button)
{
//это фильтруютс€ записи Ѕƒ ответов всоответствии с выбранным ƒЅ-навигатором вопросом
 OptionsForm->TableAns->Filter = "Nzap=" + IntToStr(OptionsForm->TableQuest->FieldByName("Nzap")->AsInteger);
}
//---------------------------------------------------------------------------


void __fastcall TOptionsForm::TableAnsAfterEdit(TDataSet *DataSet)
{
//обеспечиваетс€ соответствие записи ответа текущему вопросу при редактировании
 OptionsForm->TableAns->FieldByName("Nzap")->AsInteger = OptionsForm->TableQuest->FieldByName("Nzap")->AsInteger;
}
//---------------------------------------------------------------------------

void __fastcall TOptionsForm::TableAnsAfterInsert(TDataSet *DataSet)
{
//обеспечиваетс€ соответствие записи ответа текущему вопросу при создании новой записи
 OptionsForm->TableAns->Edit();
 OptionsForm->TableAns->FieldByName("Nzap")->AsInteger = OptionsForm->TableQuest->FieldByName("Nzap")->AsInteger;
 OptionsForm->TableAns->Post();
       
}
//---------------------------------------------------------------------------

void __fastcall TOptionsForm::DBGridQuestMouseMove(TObject *Sender,TShiftState Shift, int X, int Y)
{
//это фильтруютс€ записи Ѕƒ ответов всоответствии с выбранным мышью вопросом
//и выдача текущего вопроса в подсказку
 OptionsForm->TableAns->Filter = "Nzap=" + IntToStr(OptionsForm->TableQuest->FieldByName("Nzap")->AsInteger);
 OptionsForm->DBGridQuest->Hint = OptionsForm->TableQuest->FieldByName("Questions")->AsString;
}
//---------------------------------------------------------------------------

void __fastcall TOptionsForm::FormShow(TObject *Sender)
{
 //это фильтруютс€ записи Ѕƒ ответов при первоначальном показе формы, т.е. по первому вопросу
 OptionsForm->TableAns->Filter = "Nzap=" + IntToStr(OptionsForm->TableQuest->FieldByName("Nzap")->AsInteger);
}
//---------------------------------------------------------------------------



void __fastcall TOptionsForm::DBGridQuestKeyUp(TObject *Sender, WORD &Key,TShiftState Shift)
{
//это фильтруютс€ записи Ѕƒ ответов всоответствии с выбранным курсором с клавиатуры вопросом
//и выдача текущего вопроса в подсказку
 OptionsForm->TableAns->Filter = "Nzap=" + IntToStr(OptionsForm->TableQuest->FieldByName("Nzap")->AsInteger);
 OptionsForm->DBGridQuest->Hint = OptionsForm->TableQuest->FieldByName("Questions")->AsString;
}
//---------------------------------------------------------------------------

void __fastcall TOptionsForm::DBGridAnsMouseMove(TObject *Sender,TShiftState Shift, int X, int Y)
{
//выдача текущего ответа в подсказку при выборе мышью
 OptionsForm->DBGridAns->Hint = OptionsForm->TableAns->FieldByName("Answers")->AsString;
}
//---------------------------------------------------------------------------

void __fastcall TOptionsForm::DBGridAnsKeyUp(TObject *Sender, WORD &Key,TShiftState Shift)
{
//выдача текущего ответа в подсказку при выборе курсором с клавиатуры
 OptionsForm->DBGridAns->Hint = OptionsForm->TableAns->FieldByName("Answers")->AsString;
}
//---------------------------------------------------------------------------

void __fastcall TOptionsForm::Edit1Change(TObject *Sender)
{
 TimeTest = StrToFloat(OptionsForm->Edit1->Text);
}
//---------------------------------------------------------------------------

