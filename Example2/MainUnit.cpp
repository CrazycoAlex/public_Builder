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
// переменные регистрации
String UserName = "",//Имя
       UserPatronymicname = "",//Отчество
       UserSurname = "",//Фамилия
       UserEMail = "";//Адрес электронной почты
String FileNameRez = ""; // Название файла, в который записываются результаты теста
String AdressF,AdressT,SubjectM,TextM; //переменные, которые в данной версии не использовались
// адрес отправителя, адрес назначения, тема письма и текст письма соответственно
String openfile = "",Subj = "",addrT = "",addrF = "";
int UserNumTry = 0;// Количество использованных попыток
int NUserReg = 0;
float TimeTest = 15;// Ограничение по времени (минуты)
// Другие переменные

int UserMark;// оценка по тесту
extern int Ntrue[];//функция описана в другом модуле
extern int Nfalse[];//функция описана в другом модуле
void rezPrint(void);//функция выдачи результатов теста на печать
void rezmail(void);//функция выдачи результатов теста на электронный адрес
void secfunW(void); //функция ограничения количества регистраций
void secfunR(void); //функция ограничения количества регистраций
void ReadOpt(void); //функция чтения опций пересылки результатов
void SaveOpt(void); //функция записи опций пересылки результатов
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//переход к форме запроса пороля на редактирование таблиц
void __fastcall TMainForm::BitBtn1Click(TObject *Sender)
{
   if(PasswForm->ShowModal() == mrOk)
    {
     OptionsForm->ShowModal();
    }
   else
    {
     ShowMessage("Вам отказано в праве доступа к настройкам!");
    }
}
//---------------------------------------------------------------------------
void rezPrint(void)
{
 FILE * out;  //объявление потока для записи файла
 //присвоение имени файлу с использованием фамилии регистрируемого
 FileNameRez = "";
 FileNameRez += "RezTest";
 FileNameRez += UserSurname;
 FileNameRez += ".txt";

 out = fopen(FileNameRez.c_str() ,"w"); //инициализация потока на запись

 //выдача информации в файл
 fprintf(out,"Регистрационная информация:\n");
 fprintf(out,"\nФамилия: \t %s\n",UserSurname);
 fprintf(out,"Имя: \t %s\n",UserName);
 fprintf(out,"Отчество: \t %s\n",UserPatronymicname);
 fprintf(out,"Адрес электронной почты: \t %s\n",UserEMail);
 fprintf(out,"\nРезультаты теста по авторскому праву: \n");
 fprintf(out,"\nПопытка №%i \n",NUserReg);
 if((Ntrue[0] == 0)&&(Nfalse[0] == 0))
  {
   fprintf(out,"\nНе использовалась\n");
  }
 else
  {
   fprintf(out,"\nПравильных ответов: %i\n",Ntrue[0]);
   fprintf(out,"Неправильных ответов: %i\n",Nfalse[0]);
   fprintf(out,"Оценка: %i \n",UserMark);
  }
/* fprintf(out,"\nПопытка №2 \n");
 if((Ntrue[1] == 0)&&(Nfalse[1] == 0))
  {
   fprintf(out,"\nНе использовалась\n");
  }
 else
  {
   fprintf(out,"\nПравильных ответов: %i\n",Ntrue[1]);
   fprintf(out,"Неправильных ответов: %i\n",Nfalse[1]);
   fprintf(out,"Оценка: %i \n",UserMark);
  }
 fprintf(out,"\nПопытка №3 \n");
 if((Ntrue[2] == 0)&&(Nfalse[2] == 0))
  {
   fprintf(out,"\nНе использовалась\n");
  }
 else
  {
   fprintf(out,"\nПравильных ответов: %i\n",Ntrue[2]);
   fprintf(out,"Неправильных ответов: %i\n",Nfalse[2]);
   fprintf(out,"Оценка: %i \n",UserMark);
  }        */
 fclose(out);  //закрытие потока
}
//---------------------------------------------------------------------------
//переход к форме самого теста (и, естественно тесту)
void __fastcall TMainForm::BitBtn2Click(TObject *Sender)
{
 if(( UserName == MainForm->Edit1->Text)&&(UserPatronymicname == MainForm->Edit2->Text)&&(UserSurname == MainForm->Edit3->Text))
  {
   UserNumTry++; //Если регистрация осталась без изменений - увеличить количество использованных попыток на 1
  }
 else
  {
   UserNumTry = 1; //Иначе - количеству использованных попыток присвоить значение 1
   NUserReg++;
   secfunW();
   if(NUserReg > NUserRegRazr) MainForm->Close();
  }
 if((MainForm->Edit1->Text == "")||(MainForm->Edit2->Text == "")||(MainForm->Edit3->Text == "")||(MainForm->Edit4->Text == ""))
  {
     ShowMessage("Для тестирования необходимо ПОЛНОСТЬЮ зарегистрироваться!");
  }
 else
  {
   if (UserNumTry <= NUserTryRazr)// Если количество использованных попыток меньше или равно 3 - продолжить тест
    {
     //Сохранение информации о регистрации
     UserName = MainForm->Edit2->Text;
     UserPatronymicname = MainForm->Edit3->Text;
     UserSurname = MainForm->Edit1->Text;
     UserEMail = MainForm->Edit4->Text;

     // Вызов функции, реализующей тестирование
     TestForm->ShowModal();
     ShowMessage("Ваша оценка : " + IntToStr(UserMark));
    }
   else
    {
     //Если количество использованных попыток больше 3 - выдается сообщение
     ShowMessage("Вы исчерпали ресурс своих попыток!");
    }
  }
}
//---------------------------------------------------------------------------
void rezmail(void) //это и есть функция пересылки информации на эл. почту
{
 ReadOpt();
 addrF = UserEMail;
 openfile = FileNameRez;
 if (Subj == "") Subj = "Результаты тестирования по авторскому праву";
 SaveOpt();
 WinExec("Smtest.exe ut",SW_RESTORE);

}
//---------------------------------------------------------------------------
void secfunW(void) //функция ограничения количества регистраций
{
  FILE * TMPW;

  TMPW = fopen("Quest.tmr","w");

  fprintf(TMPW,"%i",NUserReg);

  fclose(TMPW);
}
//---------------------------------------------------------------------------
void secfunR(void) //функция ограничения количества регистраций
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


