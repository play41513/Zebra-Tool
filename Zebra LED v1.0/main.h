//---------------------------------------------------------------------------

#ifndef mainH
#define mainH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
#include <dbt.h> //DBT_常數 註冊要取得的裝置消息
#include "HID.h"
#include "IO_Request.h"
#include "DeviceNotify.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "Gauges.hpp"
#include "cspin.h"
#include <Graphics.hpp>
#include <jpeg.hpp>
#include <pngimage.hpp>
#include <queue>
#include <fstream>
#include <Buttons.hpp>
#include <Registry.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <Grids.hpp>
#include <direct.h>

#include "FileControlBase.h"
#include "ConstantString.h"
#include "MainThread.h"

const AnsiString PASSWORD  = "SET";
const AnsiString MTTWORD   = "MTT";

const float H_UNIT = 0.0211; //H_單位元電壓值
const float L_UNIT = 0.0056; //L_單位元電壓值

//
#define GET_VALUE_TIMEOUT_MS 10
#define H_HARDWARE_VOLTAGE_COMPENSATION(voltage0) (((voltage0.ToDouble())*H_UNIT)-0.075)/0.99
#define L_HARDWARE_VOLTAGE_COMPENSATION(voltage0) (((voltage0.ToDouble())*L_UNIT)-0.014)/0.984

#define HID_IS_ONLINE		0
#define HID_TURN_ON			1
#define CHANGE_AD_PORT		2
#define READ_AD_VALUE		3
#define TEST_VOLTAGE_PASS	4
#define TEST_VOLTAGE_FAIL	5
#define HID_NOT_FIND		6



#define DEBUG(String)    FrmMain->moDebug->Lines->Add(String)

//---------------------------------------------------------------------------

class TFrmMain : public TForm
{
__published:	// IDE-managed Components
	TPanel *pl_Auto0;
	TCheckBox *ckbAuto;
	TPanel *Panel7;
	TTimer *TimerDetail;
	TPanel *pl_Main;
	TPanel *pl_Set_Switch;
	TPanel *plSet;
	TPanel *Panel14;
	TPanel *plAD14;
	TEdit *edtADSetMax14;
	TPanel *pl_pin14;
	TPanel *Panel10;
	TPanel *plAD13;
	TEdit *edtADSetMax13;
	TPanel *pl_pin13;
	TPanel *Panel15;
	TPanel *plAD12;
	TEdit *edtADSetMax12;
	TPanel *pl_pin12;
	TPanel *Panel19;
	TPanel *plAD11;
	TEdit *edtADSetMax11;
	TPanel *pl_pin11;
	TPanel *Panel23;
	TPanel *plAD10;
	TEdit *edtADSetMax10;
	TPanel *pl_pin10;
	TPanel *Panel27;
	TPanel *plAD9;
	TEdit *edtADSetMax9;
	TPanel *pl_pin9;
	TPanel *Panel31;
	TPanel *plAD8;
	TEdit *edtADSetMax8;
	TPanel *pl_pin8;
	TPanel *Panel35;
	TPanel *plAD7;
	TEdit *edtADSetMax7;
	TPanel *pl_pin7;
	TPanel *Panel39;
	TPanel *plAD6;
	TEdit *edtADSetMax6;
	TPanel *pl_pin6;
	TPanel *Panel43;
	TPanel *plAD5;
	TEdit *edtADSetMax5;
	TPanel *pl_pin5;
	TPanel *Panel47;
	TPanel *plAD4;
	TEdit *edtADSetMax4;
	TPanel *pl_pin4;
	TPanel *Panel51;
	TPanel *plAD3;
	TEdit *edtADSetMax3;
	TPanel *pl_pin3;
	TPanel *Panel54;
	TPanel *plAD2;
	TEdit *edtADSetMax2;
	TPanel *pl_pin2;
	TPanel *Panel57;
	TPanel *plAD1;
	TEdit *edtADSetMax1;
	TPanel *pl_pin1;
	TPanel *Panel60;
	TPanel *plAD0;
	TEdit *edtADSetMin0;
	TPanel *pl_pin0;
	TPanel *Panel63;
	TPanel *Panel64;
	TPanel *Panel65;
	TPanel *Panel66;
	TPanel *Panel67;
	TPanel *plPSU;
	TPanel *pl_Right;
	TLabel *Label1;
	TPanel *pl_Auto1;
	TPanel *pl_Auto2;
	TPanel *pl_Auto3;
	TPanel *pl_Auto4;
	TPanel *pl_Auto5;
	TPanel *pl_Auto6;
	TPanel *pl_Auto7;
	TPanel *pl_Auto8;
	TPanel *pl_Auto9;
	TPanel *pl_Auto10;
	TPanel *pl_Auto11;
	TPanel *pl_Auto12;
	TPanel *pl_Auto14;
	TPanel *pl_Auto13;
	TPanel *Panel8;
	TPanel *plADValue0;
	TPanel *plADValue1;
	TPanel *plADValue2;
	TPanel *plADValue3;
	TPanel *plADValue4;
	TPanel *plADValue5;
	TPanel *plADValue6;
	TPanel *plADValue7;
	TPanel *plADValue8;
	TPanel *plADValue9;
	TPanel *plADValue10;
	TPanel *plADValue11;
	TPanel *plADValue12;
	TPanel *plADValue13;
	TPanel *plADValue14;
	TPanel *Panel11;
	TPanel *plResult;
	TPanel *plErrorMsg;
	TPanel *plStaus;
	TEdit *edtADSetMax0;
	TPanel *Panel1;
	TPanel *Panel2;
	TEdit *edtADSetMin1;
	TEdit *edtADSetMin2;
	TEdit *edtADSetMin3;
	TEdit *edtADSetMin4;
	TEdit *edtADSetMin5;
	TEdit *edtADSetMin6;
	TEdit *edtADSetMin7;
	TEdit *edtADSetMin8;
	TEdit *edtADSetMin9;
	TEdit *edtADSetMin10;
	TEdit *edtADSetMin11;
	TEdit *edtADSetMin12;
	TEdit *edtADSetMin14;
	TEdit *edtADSetMin13;
	TPanel *Panel3;
	TPanel *Panel4;
	TPanel *Panel5;
	TPanel *Panel6;
	TPanel *Panel9;
	TPanel *Panel12;
	TPanel *Panel13;
	TPanel *Panel17;
	TPanel *Panel18;
	TPanel *Panel20;
	TPanel *Panel21;
	TPanel *Panel22;
	TPanel *Panel24;
	TPanel *pl_KValue;
	TPanel *Panel25;
	TPanel *Panel26;
	TEdit *edt_KValue_14;
	TPanel *plPN_14;
	TPanel *Panel28;
	TEdit *edt_KValue_13;
	TPanel *plPN_13;
	TPanel *Panel30;
	TEdit *edt_KValue_12;
	TPanel *plPN_12;
	TPanel *Panel33;
	TEdit *edt_KValue_11;
	TPanel *plPN_11;
	TPanel *Panel36;
	TEdit *edt_KValue_10;
	TPanel *plPN_10;
	TPanel *Panel38;
	TEdit *edt_KValue_9;
	TPanel *plPN_9;
	TPanel *Panel41;
	TEdit *edt_KValue_8;
	TPanel *plPN_8;
	TPanel *Panel44;
	TEdit *edt_KValue_7;
	TPanel *plPN_7;
	TPanel *Panel46;
	TEdit *edt_KValue_6;
	TPanel *plPN_6;
	TPanel *Panel49;
	TEdit *edt_KValue_5;
	TPanel *plPN_5;
	TPanel *Panel52;
	TEdit *edt_KValue_4;
	TPanel *plPN_4;
	TPanel *Panel55;
	TEdit *edt_KValue_3;
	TPanel *plPN_3;
	TPanel *Panel58;
	TEdit *edt_KValue_2;
	TPanel *plPN_2;
	TPanel *Panel61;
	TEdit *edt_KValue_1;
	TPanel *plPN_1;
	TPanel *Panel76;
	TEdit *edt_KValue_0;
	TPanel *plPN_0;
	TPanel *Panel78;
	TPanel *Panel32;
	TLabel *labIni;
	TPanel *Panel34;
	TPanel *Panel37;
	TLabel *labProduct;
	TPanel *Panel40;
	TPanel *Panel45;
	TPanel *Panel48;
	TPanel *Panel70;
	TEdit *edtPSUVol1;
	TPanel *Panel50;
	TPanel *Panel69;
	TEdit *edtPSUSurgeCur1;
	TPanel *Panel53;
	TPanel *Panel42;
	TEdit *edtPSUCur1;
	TPanel *Panel74;
	TPanel *Panel75;
	TPanel *Panel56;
	TEdit *edtPSUCurMin1;
	TPanel *Panel16;
	TEdit *edtPSUCurMax1;
	TPanel *Panel59;
	TPanel *Panel62;
	TPanel *Panel72;
	TEdit *edtPSUVol2;
	TPanel *Panel73;
	TPanel *Panel77;
	TEdit *edtPSUSurgeCur2;
	TPanel *Panel79;
	TPanel *Panel80;
	TEdit *edtPSUCur2;
	TPanel *Panel81;
	TPanel *Panel82;
	TPanel *Panel83;
	TEdit *edtPSUCurMin2;
	TPanel *Panel84;
	TEdit *edtPSUCurMax2;
	TPanel *Panel85;
	TListBox *lboxDetail;
	TPanel *plSwitchSetting;
	TPanel *plSwitchLable;
	TPanel *Panel86;
	TPanel *plSwitchImage;
	TImage *imgSwitch;
	TBitBtn *btnSwitchFail;
	TPanel *plImage;
	TImage *Image2;
	TPanel *plPSUPage;
	TPanel *Panel29;
	TComboBox *cbboxPSU1;
	TImage *Image1;
	TBitBtn *btnPSUNameOk;
	TLabel *lbPSUName;
	TButton *btnGetPSUName;
	TLabel *Label2;
	TImage *Image3;
	TComboBox *cbboxPSU2;
	TPanel *plPSUName1;
	TPanel *plPSUName2;
	void __fastcall plAD0Click(TObject *Sender);
	void __fastcall TimerDetailTimer(TObject *Sender);
	void __fastcall pl_Set_SwitchClick(TObject *Sender);
	void __fastcall btnSwitchFailClick(TObject *Sender);
	void __fastcall btnGetPSUNameClick(TObject *Sender);
	void __fastcall btnPSUNameOkClick(TObject *Sender);
	void __fastcall cbboxPSU1Change(TObject *Sender);



private:	// User declarations
	INI_DESCRIPOR INI_Desc;
	cFileControl *mFileControlBase;
	TMainThread *mainThread;

	//
	bool  TFrmMain::SaveLogLine(AnsiString FileName,AnsiString FileLine);
	bool TFrmMain::CheckDiskName();
	void TFrmMain::FindLogFile();
	void TFrmMain::NewFilePath(AnsiString Path);
	void ReadItemParm(int Index);
	void UpdatePSUDevice();
	//USB拔插消息
	DeviceNotification g_DeviceNogification;
	TWndMethod OldWindowProc;
	void __fastcall MyWindowProc(TMessage&);
	//
	TStringList* strListCOM;
	TStringList* strListName;
public:		// User declarations
	//
	AnsiString Error_Msg;
	queue<AnsiString> que_cmd;

	void QueueClear();

	AnsiString ERROR_MSG;
	AnsiString FILE_DUT_SET_INI;
	__fastcall TFrmMain(TComponent* Owner);
	TWndMethod OldFormWndProc;
	void __fastcall FormWndProc(TMessage& Message);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmMain *FrmMain;
//---------------------------------------------------------------------------
#endif
