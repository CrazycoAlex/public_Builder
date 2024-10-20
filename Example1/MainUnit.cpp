//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ViewUnit.h"
#include "GrafUnit.h"
#include "MainUnit.h"
#include "AboutUnit.h"
#include <iostream.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"

TMainForm *MainForm;
FILE *in;
bool OneFileWork = false,GrSize[8];// количество используемых графиков (от 1 до 8)
int StInF[2][8],// столбцы в файле, используемые для построения графика (абсцисс(гор),ординат(верт))
i,j,k,Nstrok=1,Nchis=0;
char simv;
String errorMessage,TemporaryDirectory,FileName,StrGr[3][8];//названия осей (абсцисс(гор),ординат(верт)),имя файла
TColor ColGr[8];// цвет графика
float chislo = 0,chislo1 = 0,chislo2;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CheckBox1Click(TObject *Sender)
{
 if(CheckBox1->Checked)
  {
   Edit1->Visible = true;
   Edit2->Visible = true;
   CSpinEdit1->Visible = true;
   CSpinEdit2->Visible = true;
   if(!OneFileWork) BitBtn1->Visible = true;
   BitBtn9->Visible = true;
   GrSize[0] = true;
  }
 else
  {
   Edit1->Visible = false;
   Edit2->Visible = false;
   CSpinEdit1->Visible = false;
   CSpinEdit2->Visible = false;
   BitBtn1->Visible = false;
   BitBtn9->Visible = false;
   GrSize[0] = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CheckBox2Click(TObject *Sender)
{
 if(CheckBox2->Checked)
  {
   Edit3->Visible = true;
   Edit4->Visible = true;
   CSpinEdit3->Visible = true;
   CSpinEdit4->Visible = true;
   if(!OneFileWork) BitBtn2->Visible = true;
   BitBtn10->Visible = true;
   GrSize[1] = true;
  }
 else
  {
   Edit3->Visible = false;
   Edit4->Visible = false;
   CSpinEdit3->Visible = false;
   CSpinEdit4->Visible = false;
   BitBtn2->Visible = false;
   BitBtn10->Visible = false;
   GrSize[1] = false;
  }

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CheckBox3Click(TObject *Sender)
{
 if(CheckBox3->Checked)
  {
   Edit5->Visible = true;
   Edit6->Visible = true;
   CSpinEdit5->Visible = true;
   CSpinEdit6->Visible = true;
   if(!OneFileWork) BitBtn3->Visible = true;
   BitBtn11->Visible = true;
   GrSize[2] = true;
  }
 else
  {
   Edit5->Visible = false;
   Edit6->Visible = false;
   CSpinEdit5->Visible = false;
   CSpinEdit6->Visible = false;
   BitBtn3->Visible = false;
   BitBtn11->Visible = false;
   GrSize[2] = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CheckBox4Click(TObject *Sender)
{
 if(CheckBox4->Checked)
  {
   Edit7->Visible = true;
   Edit8->Visible = true;
   CSpinEdit7->Visible = true;
   CSpinEdit8->Visible = true;
   if(!OneFileWork) BitBtn4->Visible = true;
   BitBtn12->Visible = true;
   GrSize[3] = true;
  }
 else
  {
   Edit7->Visible = false;
   Edit8->Visible = false;
   CSpinEdit7->Visible = false;
   CSpinEdit8->Visible = false;
   BitBtn4->Visible = false;
   BitBtn12->Visible = false;
   GrSize[3] = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CheckBox5Click(TObject *Sender)
{
 if(CheckBox5->Checked)
  {
   Edit9->Visible = true;
   Edit10->Visible = true;
   CSpinEdit9->Visible = true;
   CSpinEdit10->Visible = true;
   if(!OneFileWork) BitBtn5->Visible = true;
   BitBtn13->Visible = true;
   GrSize[4] = true;
  }
 else
  {
   Edit9->Visible = false;
   Edit10->Visible = false;
   CSpinEdit9->Visible = false;
   CSpinEdit10->Visible = false;
   BitBtn5->Visible = false;
   BitBtn13->Visible = false;
   GrSize[4] = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CheckBox6Click(TObject *Sender)
{
 if(CheckBox6->Checked)
  {
   Edit11->Visible = true;
   Edit12->Visible = true;
   CSpinEdit11->Visible = true;
   CSpinEdit12->Visible = true;
   if(!OneFileWork) BitBtn6->Visible = true;
   BitBtn14->Visible = true;
   GrSize[5] = true;
  }
 else
  {
   Edit11->Visible = false;
   Edit12->Visible = false;
   CSpinEdit11->Visible = false;
   CSpinEdit12->Visible = false;
   BitBtn6->Visible = false;
   BitBtn14->Visible = false;
   GrSize[5] = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CheckBox7Click(TObject *Sender)
{
 if(CheckBox7->Checked)
  {
   Edit13->Visible = true;
   Edit14->Visible = true;
   CSpinEdit13->Visible = true;
   CSpinEdit14->Visible = true;
   if(!OneFileWork) BitBtn7->Visible = true;
   BitBtn15->Visible = true;
   GrSize[6] = true;
  }
 else
  {
   Edit13->Visible = false;
   Edit14->Visible = false;
   CSpinEdit13->Visible = false;
   CSpinEdit14->Visible = false;
   BitBtn7->Visible = false;
   BitBtn15->Visible = false;
   GrSize[6] = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CheckBox8Click(TObject *Sender)
{
 if(CheckBox8->Checked)
  {
   Edit15->Visible = true;
   Edit16->Visible = true;
   CSpinEdit15->Visible = true;
   CSpinEdit16->Visible = true;
   if(!OneFileWork) BitBtn8->Visible = true;
   BitBtn16->Visible = true;
   GrSize[7] = true;
  }
 else
  {
   Edit15->Visible = false;
   Edit16->Visible = false;
   CSpinEdit15->Visible = false;
   CSpinEdit16->Visible = false;
   BitBtn8->Visible = false;
   BitBtn16->Visible = false;
   GrSize[7] = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BitBtn9Click(TObject *Sender)
{
       if(ColorDialog->Execute())
        ColGr[0] = ColorDialog->Color;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BitBtn10Click(TObject *Sender)
{
       if(ColorDialog->Execute())
        ColGr[1] = ColorDialog->Color;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BitBtn11Click(TObject *Sender)
{
       if(ColorDialog->Execute())
        ColGr[2] = ColorDialog->Color;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BitBtn12Click(TObject *Sender)
{
       if(ColorDialog->Execute())
        ColGr[3] = ColorDialog->Color;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BitBtn13Click(TObject *Sender)
{
       if(ColorDialog->Execute())
        ColGr[4] = ColorDialog->Color;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BitBtn14Click(TObject *Sender)
{
       if(ColorDialog->Execute())
        ColGr[5] = ColorDialog->Color;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BitBtn15Click(TObject *Sender)
{
       if(ColorDialog->Execute())
        ColGr[6] = ColorDialog->Color;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BitBtn16Click(TObject *Sender)
{
       if(ColorDialog->Execute())
        ColGr[7] = ColorDialog->Color;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BitBtn1Click(TObject *Sender)
{
        if(OneFileWork)
         {
            StrGr[2][0] = FileName;
            BitBtn1->Caption = StrGr[2][0];
         }
        else
         {
          if(OpenDialog->Execute())
           {
            StrGr[2][0] = OpenDialog->FileName;
            BitBtn1->Caption = StrGr[2][0];
           }
         }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BitBtn2Click(TObject *Sender)
{
        if(OneFileWork)
         {
            StrGr[2][1] = FileName;
            BitBtn2->Caption = StrGr[2][1];
         }
        else
         {
          if(OpenDialog->Execute())
           {
            StrGr[2][1] = OpenDialog->FileName;
            BitBtn2->Caption = StrGr[2][1];
           }
         }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BitBtn3Click(TObject *Sender)
{
        if(OneFileWork)
         {
            StrGr[2][2] = FileName;
            BitBtn3->Caption = StrGr[2][2];
         }
        else
         {
          if(OpenDialog->Execute())
           {
            StrGr[2][2] = OpenDialog->FileName;
            BitBtn3->Caption = StrGr[2][2];
           }
         }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BitBtn4Click(TObject *Sender)
{
        if(OneFileWork)
         {
            StrGr[2][3] = FileName;
            BitBtn4->Caption = StrGr[2][3];
         }
        else
         {
          if(OpenDialog->Execute())
           {
            StrGr[2][3] = OpenDialog->FileName;
            BitBtn4->Caption = StrGr[2][3];
           }
         }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BitBtn5Click(TObject *Sender)
{
        if(OneFileWork)
         {
            StrGr[2][4] = FileName;
            BitBtn5->Caption = StrGr[2][4];
         }
        else
         {
          if(OpenDialog->Execute())
           {
            StrGr[2][4] = OpenDialog->FileName;
            BitBtn5->Caption = StrGr[2][4];
           }
         }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BitBtn6Click(TObject *Sender)
{
        if(OneFileWork)
         {
            StrGr[2][5] = FileName;
            BitBtn6->Caption = StrGr[2][5];
         }
        else
         {
          if(OpenDialog->Execute())
           {
            StrGr[2][5] = OpenDialog->FileName;
            BitBtn6->Caption = StrGr[2][5];
           }
         }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BitBtn7Click(TObject *Sender)
{
        if(OneFileWork)
         {
            StrGr[2][6] = FileName;
            BitBtn7->Caption = StrGr[2][6];
         }
        else
         {
          if(OpenDialog->Execute())
           {
            StrGr[2][6] = OpenDialog->FileName;
            BitBtn7->Caption = StrGr[2][6];
           }
         }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BitBtn8Click(TObject *Sender)
{
        if(OneFileWork)
         {
            StrGr[2][7] = FileName;
            BitBtn8->Caption = StrGr[2][7];
         }
        else
         {
          if(OpenDialog->Execute())
           {
            StrGr[2][7] = OpenDialog->FileName;
            BitBtn8->Caption = StrGr[2][7];
           }
         }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BitBtn17Click(TObject *Sender)
{
        if(OneFileWork)
         {
          if(OpenDialog->Execute())
           {
            FileName = OpenDialog->FileName;
            BitBtn17->Caption = FileName;
            for(i=0;i<8;i++)
               StrGr[2][i] = FileName;
           }
         }
        else
         {
          if(OpenDialog->Execute())
           {
            StrGr[2][0] = OpenDialog->FileName;
            BitBtn17->Caption = FileName;
           }
         }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N7Click(TObject *Sender)
{
        if(OneFileWork)
         {
                BitBtn17->Visible = false;
                if(CheckBox1->Checked ) BitBtn1->Visible = true;
                if(CheckBox2->Checked ) BitBtn2->Visible = true;
                if(CheckBox3->Checked ) BitBtn3->Visible = true;
                if(CheckBox4->Checked ) BitBtn4->Visible = true;
                if(CheckBox5->Checked ) BitBtn5->Visible = true;
                if(CheckBox6->Checked ) BitBtn6->Visible = true;
                if(CheckBox7->Checked ) BitBtn7->Visible = true;
                if(CheckBox8->Checked ) BitBtn8->Visible = true;
                N7->Checked = false;
                OneFileWork = false;
         }
        else
         {
                BitBtn17->Visible = true;
                BitBtn1->Visible = false;
                BitBtn2->Visible = false;
                BitBtn3->Visible = false;
                BitBtn4->Visible = false;
                BitBtn5->Visible = false;
                BitBtn6->Visible = false;
                BitBtn7->Visible = false;
                BitBtn8->Visible = false;
                N7->Checked = true;
                OneFileWork = true;
         }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::N5Click(TObject *Sender)
{
        PrinterSetupDialog->Execute();        
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N8Click(TObject *Sender)
{
        exit(0);        
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FormCreate(TObject *Sender)
{
        ColGr[0] = clRed;
        GrSize[0] = true;
        for(i=1;i<8;i++)
                ColGr[i] = ColGr[i-1] + 5000;
}
//---------------------------------------------------------------------------







void __fastcall TMainForm::ShowGraphExecute(TObject *Sender)
{
        for(i=0;i<8;i++)// цикл по всем графикам
         {
          if(GrSize[i])// если график выбран ...
           {
           // начальные данные
                switch(i)
                 {
                  case 0 : StrGr[0][i] = Edit1->Text; StrGr[1][i] = Edit2->Text;
                           StInF[0][i] = CSpinEdit1->Value; StInF[1][i] =CSpinEdit2->Value;
                           break;
                  case 1 : StrGr[0][i] = Edit3->Text; StrGr[1][i] = Edit4->Text;
                           StInF[0][i] = CSpinEdit3->Value; StInF[1][i] =CSpinEdit4->Value;
                           break;
                  case 2 : StrGr[0][i] = Edit5->Text; StrGr[1][i] = Edit4->Text;
                           StInF[0][i] = CSpinEdit5->Value; StInF[1][i] =CSpinEdit6->Value;
                           break;
                  case 3 : StrGr[0][i] = Edit7->Text; StrGr[1][i] = Edit8->Text;
                           StInF[0][i] = CSpinEdit7->Value; StInF[1][i] =CSpinEdit8->Value;
                           break;
                  case 4 : StrGr[0][i] = Edit9->Text; StrGr[1][i] = Edit10->Text;
                           StInF[0][i] = CSpinEdit9->Value; StInF[1][i] =CSpinEdit10->Value;
                           break;
                  case 5 : StrGr[0][i] = Edit11->Text; StrGr[1][i] = Edit12->Text;
                           StInF[0][i] = CSpinEdit11->Value; StInF[1][i] =CSpinEdit12->Value;
                           break;
                  case 6 : StrGr[0][i] = Edit13->Text; StrGr[1][i] = Edit14->Text;
                           StInF[0][i] = CSpinEdit13->Value; StInF[1][i] =CSpinEdit14->Value;
                           break;
                  case 7 : StrGr[0][i] = Edit15->Text; StrGr[1][i] = Edit16->Text;
                           StInF[0][i] = CSpinEdit15->Value; StInF[1][i] =CSpinEdit16->Value;
                           break;
                 }
           // проверка соответствия файла заданным требованиям
                j = 0x20;
                if ((in = fopen(StrGr[2][i].c_str(),"rb")) == NULL)
                 {
                  Application->MessageBox("Неверное имя файла,либо испорченный файл!!!","Ошибка открытия файла!", MB_OK);
                 }
                else
                 {
                  while(!feof(in))
                   {
                    if( fscanf(in,"%c",&j) == EOF ) break;
                    if(!(((j<=0x39)&&(j>=0x30))||((j>=0x2B)&&(j<=0x2E))||(j==0x20)||(j==0x0A)||(j==0x0D)))
                     {
                        errorMessage = "Файл не удовлетворяет заданным требованиям. Встречен нецифровой символ!!! Код символа в десятичной системе: ";
                        errorMessage += IntToStr(j);
                        errorMessage += ". Код символа в шестнадцатиричной системе: ";
                        errorMessage += IntToHex(j,2);
                        errorMessage += ".";
                        Application->MessageBox( errorMessage.c_str() ,"Ошибка открытия файла!", MB_OK);
                        goto end;
                     }
                   }
                 }
            // определение параметров файла
                simv ='0';
                if ((in = fopen(StrGr[2][i].c_str(),"rb")) == NULL)
                 {
                  Application->MessageBox("Неверное имя файла,либо испорченный файл!!!","Ошибка открытия файла!", MB_OK);
                 }
                else
                 {
                  //        считывание файла и подсчет всех чисел в нем
                  Nchis=0;
                  while(!feof(in))
                   {
                    if(fscanf(in,"%f",&chislo)!=EOF) Nchis++;
                   }
                  fclose(in);
                  //        считывание файла и подсчет количества строк в нем (j + 1) по окончании
                  in = fopen(StrGr[2][i].c_str(),"rb");
                  Nstrok=0;
                  char *simvs[100];
                  while(!feof(in))
                   {
                    while(simv1!='\n')
                     {
                      fscanf(in,"%c"&simv1);
                      simv
                      if(simvs=="\n") Nstrok++;
                     }
                   }
                  fclose(in);
                 }

                 //защита от дебила
                if((StInF[0][i]>(Nchis/Nstrok))||(StInF[1][i]>(Nchis/Nstrok)))
                 {
                  errorMessage ="У Вас в файле всего ";
                  errorMessage += IntToStr(Nchis/Nstrok);
                  errorMessage += " ст., а Вы указываете ";
                  if (StInF[0][i]>(Nchis/Nstrok)) errorMessage += IntToStr(StInF[0][i]);
                  else errorMessage += IntToStr(StInF[1][i]);
                  errorMessage += " столбец!!!! И как мне это выполнить???!!!";
                  Application->MessageBox(errorMessage.c_str(),"Ошибка указания столбцов!", MB_OK);
                  continue;
                 }

                  // построение графика по данным файла
                GrafForm->Graf->Series[i]->SeriesColor = ColGr[i];
                if((StrGr[0][i]!="")&&(StrGr[1][i]!="")) GrafForm->Graf->Series[i]->Title = StrGr[0][i]+" от "+StrGr[1][i];
                else GrafForm->Graf->Series[i]->Title = "График "+ IntToStr(i+1);
                in = fopen(StrGr[2][i].c_str(),"rb");
                for(j=0;j<Nchis;j+=Nchis/Nstrok)
                 {
                  if(StInF[0][i]<StInF[1][i])
                   {
                    k = 0;
                    for(;(StInF[0][i]-1)>k;k++)
                        fscanf(in,"%f",&chislo2);
                    fscanf(in,"%f",&chislo);
                    k++;
                    for(;(StInF[1][i]-1)>k;k++)
                        fscanf(in,"%f",&chislo2);
                    fscanf(in,"%f",&chislo1);
                    k++;
                    for(;k<(Nchis/Nstrok);k++)
                        fscanf(in,"%f",&chislo2);
                   }
                  else if (StInF[0][i]>StInF[1][i])
                   {
                    k = 0;
                    for(;(StInF[1][i]-1)>k;k++)
                        fscanf(in,"%f",&chislo2);
                    fscanf(in,"%f",&chislo1);
                    k++;
                    for(;(StInF[1][i]-1)>k;k++)
                        fscanf(in,"%f",&chislo2);
                    fscanf(in,"%f",&chislo);
                    k++;
                    for(;k<(Nchis/Nstrok);k++)
                        fscanf(in,"%f",&chislo2);
                   }
                  else
                   {
                    k = 0;
                    if((StInF[1][i]-1)>k) for(;k<StInF[1][i];k++)
                        fscanf(in,"%f",&chislo2);
                    fscanf(in,"%f",&chislo1);
                    chislo = chislo1;
                    k++;
                    for(;k<(Nchis/Nstrok);k++)
                        fscanf(in,"%f",&chislo2);
                   }
                  GrafForm->Graf->Series[i]->AddXY(chislo,chislo1);
                 }
            end:
           }
         }
         GrafForm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SaveGraphExecute(TObject *Sender)
{
        SaveDialog->Execute();
        GrafForm->Graf->SaveToBitmapFile( SaveDialog->FileName );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PrintGraphExecute(TObject *Sender)
{
        GrafForm->Graf->Print();       

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ClearGraphExecute(TObject *Sender)
{
        for(i = 0;i<8;i++)
        {
         GrafForm->Graf->Series[i]->Clear();
         GrafForm->Graf->Series[i]->Title = " ";
        }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N4Click(TObject *Sender)
{
        TemporaryDirectory = MainForm->DirectoryListBox->Directory;
        MainForm->OpenDialog->InitialDir = TemporaryDirectory;
        MainForm->SaveDialog->InitialDir = TemporaryDirectory;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N13Click(TObject *Sender)
{
        AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N14Click(TObject *Sender)
{
        const HELPUSER(1);
        Application->HelpContext(HELPUSER);
}
//---------------------------------------------------------------------------





void __fastcall TMainForm::ViewExecute(TObject *Sender)
{
        MainForm->OpenDialog->Execute();
        ViewForm->Memo1->Lines->LoadFromFile(MainForm->OpenDialog->FileName);
        ViewForm->ShowModal();        
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormShow(TObject *Sender)
{
        for(i=0;i<8;i++)
         {
          StrGr[2][i] = OpenDialog->FileName;
         }
        BitBtn1->Caption = OpenDialog->FileName;
        BitBtn2->Caption = OpenDialog->FileName;
        BitBtn3->Caption = OpenDialog->FileName;
        BitBtn4->Caption = OpenDialog->FileName;
        BitBtn5->Caption = OpenDialog->FileName;
        BitBtn6->Caption = OpenDialog->FileName;
        BitBtn7->Caption = OpenDialog->FileName;
        BitBtn8->Caption = OpenDialog->FileName;
        BitBtn17->Caption = OpenDialog->FileName;
        OpenDialog->InitialDir = DirectoryListBox->Directory;
        SaveDialog->InitialDir = DirectoryListBox->Directory;
}
//---------------------------------------------------------------------------




