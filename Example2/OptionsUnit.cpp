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
//��� ����������� ������ �� ������� ������������� � ��������� ��-����������� ��������
 OptionsForm->TableAns->Filter = "Nzap=" + IntToStr(OptionsForm->TableQuest->FieldByName("Nzap")->AsInteger);
}
//---------------------------------------------------------------------------


void __fastcall TOptionsForm::TableAnsAfterEdit(TDataSet *DataSet)
{
//�������������� ������������ ������ ������ �������� ������� ��� ��������������
 OptionsForm->TableAns->FieldByName("Nzap")->AsInteger = OptionsForm->TableQuest->FieldByName("Nzap")->AsInteger;
}
//---------------------------------------------------------------------------

void __fastcall TOptionsForm::TableAnsAfterInsert(TDataSet *DataSet)
{
//�������������� ������������ ������ ������ �������� ������� ��� �������� ����� ������
 OptionsForm->TableAns->Edit();
 OptionsForm->TableAns->FieldByName("Nzap")->AsInteger = OptionsForm->TableQuest->FieldByName("Nzap")->AsInteger;
 OptionsForm->TableAns->Post();
       
}
//---------------------------------------------------------------------------

void __fastcall TOptionsForm::DBGridQuestMouseMove(TObject *Sender,TShiftState Shift, int X, int Y)
{
//��� ����������� ������ �� ������� ������������� � ��������� ����� ��������
//� ������ �������� ������� � ���������
 OptionsForm->TableAns->Filter = "Nzap=" + IntToStr(OptionsForm->TableQuest->FieldByName("Nzap")->AsInteger);
 OptionsForm->DBGridQuest->Hint = OptionsForm->TableQuest->FieldByName("Questions")->AsString;
}
//---------------------------------------------------------------------------

void __fastcall TOptionsForm::FormShow(TObject *Sender)
{
 //��� ����������� ������ �� ������� ��� �������������� ������ �����, �.�. �� ������� �������
 OptionsForm->TableAns->Filter = "Nzap=" + IntToStr(OptionsForm->TableQuest->FieldByName("Nzap")->AsInteger);
}
//---------------------------------------------------------------------------



void __fastcall TOptionsForm::DBGridQuestKeyUp(TObject *Sender, WORD &Key,TShiftState Shift)
{
//��� ����������� ������ �� ������� ������������� � ��������� �������� � ���������� ��������
//� ������ �������� ������� � ���������
 OptionsForm->TableAns->Filter = "Nzap=" + IntToStr(OptionsForm->TableQuest->FieldByName("Nzap")->AsInteger);
 OptionsForm->DBGridQuest->Hint = OptionsForm->TableQuest->FieldByName("Questions")->AsString;
}
//---------------------------------------------------------------------------

void __fastcall TOptionsForm::DBGridAnsMouseMove(TObject *Sender,TShiftState Shift, int X, int Y)
{
//������ �������� ������ � ��������� ��� ������ �����
 OptionsForm->DBGridAns->Hint = OptionsForm->TableAns->FieldByName("Answers")->AsString;
}
//---------------------------------------------------------------------------

void __fastcall TOptionsForm::DBGridAnsKeyUp(TObject *Sender, WORD &Key,TShiftState Shift)
{
//������ �������� ������ � ��������� ��� ������ �������� � ����������
 OptionsForm->DBGridAns->Hint = OptionsForm->TableAns->FieldByName("Answers")->AsString;
}
//---------------------------------------------------------------------------

void __fastcall TOptionsForm::Edit1Change(TObject *Sender)
{
 TimeTest = StrToFloat(OptionsForm->Edit1->Text);
}
//---------------------------------------------------------------------------

