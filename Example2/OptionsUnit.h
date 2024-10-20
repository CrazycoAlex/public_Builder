//---------------------------------------------------------------------------

#ifndef OptionsUnitH
#define OptionsUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <DBTables.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TOptionsForm : public TForm
{
__published:	// IDE-managed Components
        TDBGrid *DBGridQuest;
        TDBGrid *DBGridAns;
        TDBNavigator *DBNavigatorQuest;
        TDBNavigator *DBNavigatorAns;
        TDataSource *DataSourceTQuest;
        TTable *TableQuest;
        TTable *TableAns;
        TDataSource *DataSourceAns;
        TAutoIncField *TableAnsNum;
        TIntegerField *TableAnsNzap;
        TStringField *TableAnsAnswers;
        TBooleanField *TableAnsRightAnswers;
        TAutoIncField *TableQuestNzap;
        TStringField *TableQuestQuestions;
        TLabel *Label1;
        TEdit *Edit1;
        void __fastcall DBNavigatorQuestClick(TObject *Sender,
          TNavigateBtn Button);
        void __fastcall TableAnsAfterEdit(TDataSet *DataSet);
        void __fastcall TableAnsAfterInsert(TDataSet *DataSet);
        void __fastcall DBGridQuestMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall DBGridQuestKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall DBGridAnsMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall DBGridAnsKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Edit1Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TOptionsForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TOptionsForm *OptionsForm;
//---------------------------------------------------------------------------
#endif
