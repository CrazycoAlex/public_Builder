//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TestUnit.h"
#include "OptionsUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTestForm *TestForm;

const int Nvopr = 20; //количество вопросов в попытке
const int Npop =3;    //количество попыток

int i,j,RandomVar; //промежуточные переменные

int NumQuestTest[Nvopr*Npop];  //номера вопросов, случайно выбранных для трех попыток в порядке следования в БД
bool RightUserAns[Nvopr*Npop];
int NumberAllQuestions; //количество всех вопросов в базе данных
int Nzap; //параметр связи вопроса и ответов на него
int NumA; // количество вариантов ответов на текущий вопрос
int k,kk;//промежуточные переменные
String Question; // текст текущего вопроса
String Answers[10];// текст ответов на текущий вопрос
bool RightA[10];//правильные ответы на текущий вопрос(из БД)
bool UserA[10]; //ответы пользователя на текущий вопрос(из теста)
int Ntrue[Npop]; //количество правильных ответов для трех попыток
int Nfalse[Npop]; //количество неправильных ответов для трех попыток

extern int UserNumTry;//переменная описана в другом модуле
extern int UserMark; //переменная описана в другом модуле
extern float TimeTest;//переменная описана в другом модуле

void firsttesty(void);//Функция формирования списка вопросов при первом запуске
int testy(void); //Функция тестирования
int QuestAllNumber(void);//Функция подсчета всех вопросов в базе данных
void QuestForming(int QuestNo); //Функция формирования вопроса на форму
extern rezPrint();//функция описана в другом модуле
extern rezmail();//функция выдачи результатов теста на электронный адрес
//---------------------------------------------------------------------------
__fastcall TTestForm::TTestForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
int testy(void) //функция выставления отметки за тест
 {
  int mark = 2;
  Ntrue[(UserNumTry - 1)] = 0;
  Nfalse[(UserNumTry - 1)] = 0;
  for(kk =0 + (20*(UserNumTry - 1));kk< (20*UserNumTry);kk++)
   {
    if(RightUserAns[kk]) Ntrue[(UserNumTry - 1)] = Ntrue[(UserNumTry - 1)] + 1;
    else Nfalse[(UserNumTry - 1)] = Nfalse[(UserNumTry - 1)] + 1;
   }
  if(Ntrue[(UserNumTry - 1)] < 12) mark = 2;
  else if((Ntrue[(UserNumTry - 1)]>=12)&&(Ntrue[(UserNumTry - 1)]<15)) mark = 3;
  else if((Ntrue[(UserNumTry - 1)]>=15)&&(Ntrue[(UserNumTry - 1)]<18)) mark = 4;
  else if((Ntrue[(UserNumTry - 1)]>=18)&&(Ntrue[(UserNumTry - 1)]<=20)) mark = 5;

  return mark;
 }
//---------------------------------------------------------------------------
int QuestAllNumber(void)//Функция подсчета всех вопросов в базе данных
{
 int NumberQuest =0;
 OptionsForm->TableQuest->First();
 while(!OptionsForm->TableQuest->Eof)
  {
   OptionsForm->TableQuest->Next();
   NumberQuest++;
  }
 return NumberQuest;
}
//---------------------------------------------------------------------------
void QuestForming(int QuestNo) //Функция формирования текущего вопроса по его номеру в БД
{
 //Формирование текста вопроса по его номеру в БД
 OptionsForm->TableQuest->First();
 for(i=1;i<QuestNo; i++)
  OptionsForm->TableQuest->Next();

 Nzap = OptionsForm->TableQuest->FieldByName("Nzap")->AsInteger;
 Question = OptionsForm->TableQuest->FieldByName("Questions")->AsString;

 //Формирование текста ответов, соответствующих вопросу и переменных, соответствующих правильным\неправильным ответам
 OptionsForm->TableAns->First();
 NumA=0;
 while(!OptionsForm->TableAns->Eof)
  {
   if(OptionsForm->TableAns->FieldByName("Nzap")->AsInteger == Nzap)
    {
     Answers[NumA] =  OptionsForm->TableAns->FieldByName("Answers")->AsString;
     RightA[NumA] = OptionsForm->TableAns->FieldByName("RightAnswers")->AsBoolean;
     NumA++;
    }
   OptionsForm->TableAns->Next();
  }
}
//---------------------------------------------------------------------------
void firsttesty(void)//Функция формирования списка вопросов при первом запуске
{
  for(j=0;j<Npop;j++)
   {
    Ntrue[j] = 0;
    Nfalse[j] = 0;
    RightUserAns[j]=false;
   }

  randomize();
  NumberAllQuestions = QuestAllNumber();
  //заполнение массива номерами вопросов из БД(случайно, но вопросы не повторяются)
  for(i = 0; i<(Npop*Nvopr); i++)
   {
    RandomVar = (((rand()*(NumberAllQuestions-1))/RAND_MAX)+1);
    NumQuestTest[i] = RandomVar;
    for(j = 0;j<i;j++)
     {
      if(RandomVar == NumQuestTest[j])
       {
        i--;
        break;
       }
     }
   }
}
//---------------------------------------------------------------------------


void __fastcall TTestForm::CheckListBoxAnsClick(TObject *Sender)
{
 //выдача в подсказку текущего ответа
 TestForm->CheckListBoxAns->Hint = TestForm->CheckListBoxAns->Items->operator [](TestForm->CheckListBoxAns->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TTestForm::FormShow(TObject *Sender)
{
 //при первом показе формы
 TestForm->Timer1->Interval = int( (1000*60)*TimeTest);
 TestForm->Timer1->Enabled = true;

 if(UserNumTry == 1) firsttesty();
 k=0 + (20*(UserNumTry - 1));
 //
 QuestForming(NumQuestTest[k]);
 TestForm->Label1->Caption = IntToStr(k+1);
 TestForm->LabelQuestion->Caption = Question;
 TestForm->CheckListBoxAns->Clear();
 for(kk=0;kk<NumA;kk++)
  {
   TestForm->CheckListBoxAns->Items->Add(Answers[kk]);
  }
}
//---------------------------------------------------------------------------

void __fastcall TTestForm::BitBtn1Click(TObject *Sender)
{
 // обработка ответа пользователя на текущий вопрос
 RightUserAns[k]=true;
 for(kk=0;kk<NumA;kk++)
  {
   UserA[kk] = TestForm->CheckListBoxAns->Checked[kk];
   if((UserA[kk]!=RightA[kk])||(RightUserAns[k] == false))
    {
     RightUserAns[k] = false;
    }
  }
 k++;
 // выдача результатов и оценки теста в файл на последнем вопросе
 if(k == (20*UserNumTry))
  {
   TestForm->Close();
   UserMark = testy();
   rezPrint();
   rezmail();
  }

 // формирование текущиего вопроса и ответов, выдача их на форму
 QuestForming(NumQuestTest[k]);
 TestForm->Label1->Caption = IntToStr(k+1);
 TestForm->LabelQuestion->Caption = Question;
 TestForm->CheckListBoxAns->Clear();
 for(kk=0;kk<NumA;kk++)
  {
   TestForm->CheckListBoxAns->Items->Add(Answers[kk]);
  }

}
//---------------------------------------------------------------------------

void __fastcall TTestForm::Timer1Timer(TObject *Sender)
{
 ShowMessage("Ваше время истекло. Тестирование прекращено!");
 UserMark = testy();
 rezPrint();
 rezmail();
 TestForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TTestForm::FormCreate(TObject *Sender)
{
 double KformW;
 int KformH;

 KformW = (Screen->Width/1024.0);
 TestForm->ScaleBy(int(KformW*10),10);
 TestForm->BitBtn1->ScaleBy(10,int(KformW*10));
 KformH = (TestForm->Height - 30 - TestForm->BitBtn1->Height - 12);

 TestForm->Label1->Left = 4;
 TestForm->Label1->Top = 4;

 TestForm->LabelQuestion->Left = 30;
 TestForm->LabelQuestion->Top = 4;
 TestForm->LabelQuestion->Width = TestForm->Width - 40;

 TestForm->CheckListBoxAns->Left = 16;
 TestForm->CheckListBoxAns->Top = 60;
 TestForm->CheckListBoxAns->Width = TestForm->Width - 32;
 TestForm->CheckListBoxAns->Height = TestForm->Height - TestForm->LabelQuestion->Height - TestForm->BitBtn1->Height - 60;

 TestForm->BitBtn1->Left = int((TestForm->Width - TestForm->BitBtn1->Width)/2);
 TestForm->BitBtn1->Top = KformH + 8;
}
//---------------------------------------------------------------------------

void __fastcall TTestForm::FormClose(TObject *Sender, TCloseAction &Action)
{
 TestForm->Timer1->Enabled = false;
}
//---------------------------------------------------------------------------

