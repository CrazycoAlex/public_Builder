//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainUnit.h"
#include "OptionsUnit.h"
#include "TestUnit.h"
#include "PasswUnit.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;

const int NUserRegRazr = 3;
const int NUserTryRazr = 1;
// ���������� �����������
String UserName = "",//���
       UserPatronymicname = "",//��������
       UserSurname = "",//�������
       UserEMail = "";//����� ����������� �����
String FileNameRez = ""; // �������� �����, � ������� ������������ ���������� �����
String AdressF,AdressT,SubjectM,TextM; //����������, ������� � ������ ������ �� ��������������
// ����� �����������, ����� ����������, ���� ������ � ����� ������ ��������������
String openfile = "",Subj = "",addrT = "",addrF = "";
int UserNumTry = 0;// ���������� �������������� �������
int NUserReg = 0;
float TimeTest = 15;// ����������� �� ������� (������)
// ������ ����������

int UserMark;// ������ �� �����
extern int Ntrue[];//������� ������� � ������ ������
extern int Nfalse[];//������� ������� � ������ ������
void rezPrint(void);//������� ������ ����������� ����� �� ������
void rezmail(void);//������� ������ ����������� ����� �� ����������� �����
void secfunW(void); //������� ����������� ���������� �����������
void secfunR(void); //������� ����������� ���������� �����������
void ReadOpt(void); //������� ������ ����� ��������� �����������
void SaveOpt(void); //������� ������ ����� ��������� �����������
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//������� � ����� ������� ������ �� �������������� ������
void __fastcall TMainForm::BitBtn1Click(TObject *Sender)
{
   if(PasswForm->ShowModal() == mrOk)
    {
     OptionsForm->ShowModal();
    }
   else
    {
     ShowMessage("��� �������� � ����� ������� � ����������!");
    }
}
//---------------------------------------------------------------------------
void rezPrint(void)
{
 FILE * out;  //���������� ������ ��� ������ �����
 //���������� ����� ����� � �������������� ������� ���������������
 FileNameRez = "";
 FileNameRez += "RezTest";
 FileNameRez += UserSurname;
 FileNameRez += ".txt";

 out = fopen(FileNameRez.c_str() ,"w"); //������������� ������ �� ������

 //������ ���������� � ����
 fprintf(out,"��������������� ����������:\n");
 fprintf(out,"\n�������: \t %s\n",UserSurname);
 fprintf(out,"���: \t %s\n",UserName);
 fprintf(out,"��������: \t %s\n",UserPatronymicname);
 fprintf(out,"����� ����������� �����: \t %s\n",UserEMail);
 fprintf(out,"\n���������� ����� �� ���������� �����: \n");
 fprintf(out,"\n������� �%i \n",NUserReg);
 if((Ntrue[0] == 0)&&(Nfalse[0] == 0))
  {
   fprintf(out,"\n�� ��������������\n");
  }
 else
  {
   fprintf(out,"\n���������� �������: %i\n",Ntrue[0]);
   fprintf(out,"������������ �������: %i\n",Nfalse[0]);
   fprintf(out,"������: %i \n",UserMark);
  }
/* fprintf(out,"\n������� �2 \n");
 if((Ntrue[1] == 0)&&(Nfalse[1] == 0))
  {
   fprintf(out,"\n�� ��������������\n");
  }
 else
  {
   fprintf(out,"\n���������� �������: %i\n",Ntrue[1]);
   fprintf(out,"������������ �������: %i\n",Nfalse[1]);
   fprintf(out,"������: %i \n",UserMark);
  }
 fprintf(out,"\n������� �3 \n");
 if((Ntrue[2] == 0)&&(Nfalse[2] == 0))
  {
   fprintf(out,"\n�� ��������������\n");
  }
 else
  {
   fprintf(out,"\n���������� �������: %i\n",Ntrue[2]);
   fprintf(out,"������������ �������: %i\n",Nfalse[2]);
   fprintf(out,"������: %i \n",UserMark);
  }        */
 fclose(out);  //�������� ������
}
//---------------------------------------------------------------------------
//������� � ����� ������ ����� (�, ����������� �����)
void __fastcall TMainForm::BitBtn2Click(TObject *Sender)
{
 if(( UserName == MainForm->Edit1->Text)&&(UserPatronymicname == MainForm->Edit2->Text)&&(UserSurname == MainForm->Edit3->Text))
  {
   UserNumTry++; //���� ����������� �������� ��� ��������� - ��������� ���������� �������������� ������� �� 1
  }
 else
  {
   UserNumTry = 1; //����� - ���������� �������������� ������� ��������� �������� 1
   NUserReg++;
   secfunW();
   if(NUserReg > NUserRegRazr) MainForm->Close();
  }
 if((MainForm->Edit1->Text == "")||(MainForm->Edit2->Text == "")||(MainForm->Edit3->Text == "")||(MainForm->Edit4->Text == ""))
  {
     ShowMessage("��� ������������ ���������� ��������� ������������������!");
  }
 else
  {
   if (UserNumTry <= NUserTryRazr)// ���� ���������� �������������� ������� ������ ��� ����� 3 - ���������� ����
    {
     //���������� ���������� � �����������
     UserName = MainForm->Edit2->Text;
     UserPatronymicname = MainForm->Edit3->Text;
     UserSurname = MainForm->Edit1->Text;
     UserEMail = MainForm->Edit4->Text;

     // ����� �������, ����������� ������������
     TestForm->ShowModal();
     ShowMessage("���� ������ : " + IntToStr(UserMark));
    }
   else
    {
     //���� ���������� �������������� ������� ������ 3 - �������� ���������
     ShowMessage("�� ��������� ������ ����� �������!");
    }
  }
}
//---------------------------------------------------------------------------
void rezmail(void) //��� � ���� ������� ��������� ���������� �� ��. �����
{
 ReadOpt();
 addrF = UserEMail;
 openfile = FileNameRez;
 if (Subj == "") Subj = "���������� ������������ �� ���������� �����";
 SaveOpt();
 WinExec("Smtest.exe ut",SW_RESTORE);

}
//---------------------------------------------------------------------------
void secfunW(void) //������� ����������� ���������� �����������
{
  FILE * TMPW;

  TMPW = fopen("Quest.tmr","w");

  fprintf(TMPW,"%i",NUserReg);

  fclose(TMPW);
}
//---------------------------------------------------------------------------
void secfunR(void) //������� ����������� ���������� �����������
{
  FILE * TMPR;

  TMPR = fopen("Quest.tmr","r");

  fscanf(TMPR,"%i",&NUserReg);

  fclose(TMPR);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
 TimeTest = StrToFloat(OptionsForm->Edit1->Text);
 secfunR();
 if(NUserReg > NUserRegRazr) MainForm->Close();
}
//---------------------------------------------------------------------------
void ReadOpt(void)
{
 FILE * opt;
 int i;

 char ch;
 opt = fopen("SAND.opt","r");
 for(i = 0; i < 4; i++ )
  {
   while((ch != '\n')&&(!feof(opt)))
    {
     fscanf(opt,"%c",&ch);
     if ((i == 0)&&(ch != '\n')) openfile += ch;
     if ((i == 1)&&(ch != '\n')) Subj += ch;
     if ((i == 2)&&(ch != '\n')) addrT += ch;
     if ((i == 3)&&(ch != '\n')&&(!feof(opt))) addrF += ch;
    }
   ch = '\0';
  }

 fclose(opt);
}
//---------------------------------------------------------------------------
void SaveOpt(void)
{
 FILE * opt;

 opt = fopen("SAND.opt","w");

 fprintf(opt,"%s \n %s \n %s \n %s",openfile,Subj,addrT,addrF);

 fclose(opt);

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
 double KformW;
 int KformH;
 Word y,m,d;
 DecodeDate(Now(), y, m, d);

 if((y >= 2004)&&(m >= 10)&&(d >= 10)) exit(0);

 KformW = (Screen->Width/1024.0);
 MainForm->ScaleBy(int(KformW*10),10);
 MainForm->BitBtn1->ScaleBy(10,int(KformW*10));
 MainForm->BitBtn2->ScaleBy(10,int(KformW*10));
 KformH = int((MainForm->Height - 30)/5);

 MainForm->Edit1->Top = (KformH + 2);
 MainForm->Edit2->Top = (KformH + 2)*2;
 MainForm->Edit3->Top = (KformH + 2)*3;
 MainForm->Edit4->Top = (KformH + 2)*4;

 MainForm->Label1->Top = 2;
 MainForm->Label2->Top = (KformH + 2);
 MainForm->Label3->Top = (KformH + 2)*2;
 MainForm->Label4->Top = (KformH + 2)*3;
 MainForm->Label5->Top = (KformH + 2)*4;

 MainForm->Edit1->Left = 110;
 MainForm->Edit2->Left = 110;
 MainForm->Edit3->Left = 110;
 MainForm->Edit4->Left = MainForm->Width - MainForm->Edit4->Width - 8;

 MainForm->BitBtn1->Left = MainForm->Width - MainForm->BitBtn1->Width - 25 ;
 MainForm->BitBtn2->Left = MainForm->Width - MainForm->BitBtn2->Width - 25 ;

 MainForm->BitBtn1->Top = KformH + 4;
 MainForm->BitBtn2->Top = (KformH + 2)*3;

}
//---------------------------------------------------------------------------


