//---------------------------------------------------------------------------

#ifndef MainThreadH
#define MainThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "FileControl.h"
#include "ConstantString.h"

const char GUID_USB_HUB[] = "{F18A0E88-C30C-11D0-8815-00A0C906BED8}";
const char GUID_USB_DEVICE[] = "{A5DCBF10-6530-11D2-901F-00C04FB951ED}";
const char GUID_USBSTOR[] = "{53F5630D-B6BF-11D0-94F2-00A0C91EFB8B}";
//---------------------------------------------------------------------------
class TMainThread : public TThread
{
private:
	AnsiString strCMD;
	bool EnumUSB();
	bool CheckReportContent();
	void RemoveFiles();
	bool CompareContents(AnsiString RepoetContents);

	INI_DESCRIPOR *INI_Desc;
	HWND mHwnd;
protected:
	void __fastcall Execute();
public:
	__fastcall TMainThread(bool CreateSuspended,HWND hWnd,INI_DESCRIPOR *ini);
	void TMainThread::SetCommandLine(AnsiString cmd);
	AnsiString DosCommand();
};
//---------------------------------------------------------------------------
#endif
