//---------------------------------------------------------------------------

#ifndef MainThreadH
#define MainThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <vcl.h>
#include "HID.h"
#include "ConstantString.h"
#include "PowerSupplyAccess.h"
#include <cmath>
#include <iostream>

#define STEP_THREAD_WAIT						0
#define STEP_CHECK_HIDBOARD						1
#define STEP_CHECK_HID_PIN_15					2
#define STEP_CHECK_PSU							3
#define STEP_PSU_OPEN							4
#define STEP_GET_PSU_VALUE						5
#define STEP_CHECK_TEST_ITEM					6
#define STEP_READ_VALUE							7
#define STEP_ADVALUE_CHANGE_TO_VOLTAGE_VALUE	8
#define STEP_CHECK_VOLTAGE_VALUE				9
#define STEP_CHECK_NEXT_STEP					10
#define STEP_THREAD_AD_VALUE_PASS				11
#define STEP_THREAD_AD_VALUE_FAIL				12
#define STEP_THREAD_CLOSE_PSU					13
#define STEP_THREAD_PSU_ERROR					14
#define STEP_THREAD_WAIT_SWITCH_SETTING			15
#define STEP_THREAD_SWITCH_CHECK_VALUE			16
#define STEP_PSU_OUTPUT_DELAY					17
#define STEP_HIDERROR			100


#define GET_VALUE_CONTINUE	1
#define GET_VALUE_END		2
#define GET_VALUE_ERROR		3
#define GET_VALUE_FAIL		4
//---------------------------------------------------------------------------
class TMainThread : public TThread
{
private:
	PowerSupplyAccess *mPowerSupplyAccess;
	INI_DESCRIPOR *INI_Desc;
	HID m_hid;
	HWND mHwnd;
	void EnumHID();
	bool IsNumeric(AnsiString input);

	queue<AnsiString> queThreadVoltageValue;
	queue<AnsiString> queThreadCurrentValue;
	void CaptureAndSaveScreenshot();
	DWORD dwCurrentNowPASS[2];
	DWORD dwPSUFailCount[5];
protected:
	void __fastcall Execute();
public:
	__fastcall TMainThread(bool CreateSuspended,INI_DESCRIPOR* info,HWND hWnd);
	DWORD TMainThread::CheckPSUReturnValue(DWORD ItemIndex,DWORD PSUIndex);
	double TMainThread::GetADValue(DWORD ADIndex);
	AnsiString GetAllPSUName();
	bool CheckPUSStatus();
	void SetPSUCOM();
	bool bSwitchFail;
};
//---------------------------------------------------------------------------
#endif
