//---------------------------------------------------------------------------

#ifndef MainUnitH
#define MainUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include "CSPIN.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <FileCtrl.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <ActnList.hpp>
#include <ActnMan.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *N3;
        TMenuItem *N4;
        TMenuItem *N5;
        TMenuItem *N6;
        TMenuItem *N7;
        TMenuItem *N8;
        TMenuItem *N9;
        TMenuItem *N10;
        TMenuItem *N11;
        TMenuItem *N12;
        TMenuItem *N13;
        TMenuItem *N14;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TCheckBox *CheckBox1;
        TEdit *Edit1;
        TEdit *Edit2;
        TCSpinEdit *CSpinEdit1;
        TCSpinEdit *CSpinEdit2;
        TCheckBox *CheckBox2;
        TEdit *Edit3;
        TEdit *Edit4;
        TCSpinEdit *CSpinEdit3;
        TCSpinEdit *CSpinEdit4;
        TCheckBox *CheckBox3;
        TEdit *Edit5;
        TEdit *Edit6;
        TCSpinEdit *CSpinEdit5;
        TCSpinEdit *CSpinEdit6;
        TCheckBox *CheckBox4;
        TEdit *Edit7;
        TEdit *Edit8;
        TCSpinEdit *CSpinEdit7;
        TCSpinEdit *CSpinEdit8;
        TCheckBox *CheckBox5;
        TEdit *Edit9;
        TEdit *Edit10;
        TCSpinEdit *CSpinEdit9;
        TCSpinEdit *CSpinEdit10;
        TCheckBox *CheckBox6;
        TEdit *Edit11;
        TEdit *Edit12;
        TCSpinEdit *CSpinEdit11;
        TCSpinEdit *CSpinEdit12;
        TCheckBox *CheckBox7;
        TEdit *Edit13;
        TEdit *Edit14;
        TCSpinEdit *CSpinEdit13;
        TCSpinEdit *CSpinEdit14;
        TCheckBox *CheckBox8;
        TEdit *Edit15;
        TEdit *Edit16;
        TCSpinEdit *CSpinEdit15;
        TCSpinEdit *CSpinEdit16;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TBitBtn *BitBtn4;
        TBitBtn *BitBtn5;
        TBitBtn *BitBtn6;
        TBitBtn *BitBtn7;
        TBitBtn *BitBtn8;
        TBitBtn *BitBtn9;
        TBitBtn *BitBtn10;
        TBitBtn *BitBtn11;
        TBitBtn *BitBtn12;
        TBitBtn *BitBtn13;
        TBitBtn *BitBtn14;
        TBitBtn *BitBtn15;
        TBitBtn *BitBtn16;
        TBitBtn *BitBtn17;
        TPanel *Panel1;
        TBitBtn *BitBtn18;
        TBitBtn *BitBtn19;
        TBitBtn *BitBtn20;
        TBitBtn *BitBtn21;
        TDirectoryListBox *DirectoryListBox;
        TOpenDialog *OpenDialog;
        TSaveDialog *SaveDialog;
        TColorDialog *ColorDialog;
        TPrinterSetupDialog *PrinterSetupDialog;
        TDriveComboBox *DriveComboBox;
        TActionManager *ActionManager;
        TImageList *ImageList;
        TAction *ShowGraph;
        TAction *SaveGraph;
        TAction *PrintGraph;
        TAction *ClearGraph;
        TAction *View;
        TMenuItem *N15;
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall CheckBox2Click(TObject *Sender);
        void __fastcall CheckBox3Click(TObject *Sender);
        void __fastcall CheckBox4Click(TObject *Sender);
        void __fastcall CheckBox5Click(TObject *Sender);
        void __fastcall CheckBox6Click(TObject *Sender);
        void __fastcall CheckBox7Click(TObject *Sender);
        void __fastcall CheckBox8Click(TObject *Sender);
        void __fastcall BitBtn9Click(TObject *Sender);
        void __fastcall BitBtn10Click(TObject *Sender);
        void __fastcall BitBtn11Click(TObject *Sender);
        void __fastcall BitBtn12Click(TObject *Sender);
        void __fastcall BitBtn13Click(TObject *Sender);
        void __fastcall BitBtn14Click(TObject *Sender);
        void __fastcall BitBtn15Click(TObject *Sender);
        void __fastcall BitBtn16Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn4Click(TObject *Sender);
        void __fastcall BitBtn5Click(TObject *Sender);
        void __fastcall BitBtn6Click(TObject *Sender);
        void __fastcall BitBtn7Click(TObject *Sender);
        void __fastcall BitBtn8Click(TObject *Sender);
        void __fastcall BitBtn17Click(TObject *Sender);
        void __fastcall N7Click(TObject *Sender);
        void __fastcall N5Click(TObject *Sender);
        void __fastcall N8Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall ShowGraphExecute(TObject *Sender);
        void __fastcall SaveGraphExecute(TObject *Sender);
        void __fastcall PrintGraphExecute(TObject *Sender);
        void __fastcall ClearGraphExecute(TObject *Sender);
        void __fastcall N4Click(TObject *Sender);
        void __fastcall N13Click(TObject *Sender);
        void __fastcall N14Click(TObject *Sender);
        void __fastcall ViewExecute(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
