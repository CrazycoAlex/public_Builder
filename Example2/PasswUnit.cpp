//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PasswUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPasswForm *PasswForm;
//---------------------------------------------------------------------------
__fastcall TPasswForm::TPasswForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPasswForm::BitBtn1Click(TObject *Sender)
{
 //запрос имени пользовател€ и парол€ и их обработка
 if ((PasswForm->Edit1->Text == "Administrator")&&(PasswForm->Edit2->Text == "89163060713"))
  {
   //разрешено редактирование Ѕƒ
   ShowMessage("ƒобро пожаловать,Administrator");
   PasswForm->Close();
   PasswForm->ModalResult = mrOk;
  }
 else
  {
   //не разрешено редактирование Ѕƒ
   PasswForm->ModalResult = mrCancel;
   PasswForm->Close();
  }
}
//---------------------------------------------------------------------------
void __fastcall TPasswForm::FormShow(TObject *Sender)
{
 //обнуление строк "пользователь" и "пароль" при показе формы
 PasswForm->Edit1->Text = "";
 PasswForm->Edit2->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TPasswForm::FormCreate(TObject *Sender)
{
 double KformW;
 int KformH;

 KformW = (Screen->Width/1024.0);
 PasswForm->ScaleBy(int(KformW*10),10);
 PasswForm->BitBtn1->ScaleBy(10,int(KformW*10));
 PasswForm->BitBtn2->ScaleBy(10,int(KformW*10));
 KformH = (PasswForm->Height - 30 - PasswForm->BitBtn1->Height - 8);

 PasswForm->Edit1->Top = int(KformH/3 + 4);
 PasswForm->Edit2->Top = int(KformH/3 + 4)*2;

 PasswForm->Label1->Top = 4;
 PasswForm->Label2->Top = int(KformH/3 + 4);
 PasswForm->Label3->Top = int(KformH/3 + 4)*2;

 PasswForm->Edit1->Left = PasswForm->Width - PasswForm->Edit1->Width - 12;
 PasswForm->Edit2->Left = PasswForm->Width - PasswForm->Edit2->Width - 12;

 PasswForm->BitBtn1->Left = 8 ;
 PasswForm->BitBtn2->Left = PasswForm->Width - PasswForm->BitBtn2->Width - 8 ;

 PasswForm->BitBtn1->Top = KformH + 4;
 PasswForm->BitBtn2->Top = KformH + 4;

}
//---------------------------------------------------------------------------

