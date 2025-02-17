//---------------------------------------------------------------------------
#include <windows.h>    // 安全移除USB裝置用 *要比 vcl.h 早編譯
#include <cfgmgr32.h>	// 安全移除USB裝置用 *要比 vcl.h 早編譯
#include <SetupAPI.h>	// 安全移除USB裝置用 *要比 vcl.h 早編譯
#include <vcl.h>
#pragma hdrstop

#include "CMDThreadAccess.h"
#pragma package(smart_init)

DWORD dwStart,dwFailCount;
DWORD dwCMDCountNow;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
DWORD dwStep = 99;
__fastcall TCMDThreadAccess::TCMDThreadAccess(bool CreateSuspended,HWND hWnd,INI_DESCRIPOR *ini)
	: TThread(CreateSuspended)
{
	INI_Desc = ini;
	mHwnd = hWnd;
}
void TCMDThreadAccess::SetThreadStep(DWORD Step)
{
	dwStep = Step;
}
//---------------------------------------------------------------------------
void __fastcall TCMDThreadAccess::Execute()
{
	//---- Place thread code here ----
	while( !Terminated )
	{
		switch(dwStep)
		{
			case STEP_CMD_GET_USB_DEVICE:
				if(EnumUSB() && INI_Desc->dwItemIndex == HOME_PAGE_INDEX)
				{
					PostMessage(mHwnd,WM_CMD_UI,WP_CMD_UI_RESULT_WAIT,NULL);
					PostMessage(mHwnd,WM_CMD_REPOET,WP_CMD_REPOET_CLEAR,NULL);
					dwStart = GetTickCount()+INI_Desc->PHID_DETAIL.dwDelayTimeStart;
					dwStep = STEP_CMD_START_DELAY;
				}
				break;
			case STEP_CMD_START_DELAY:
				if(GetTickCount() > dwStart)
				{
					dwCMDCountNow = 0;
					dwFailCount = 0;
					INI_Desc->queHomePageListBox.push("[Get Fireware Version]");
					dwStep = STEP_CMD;
				}
				break;
			case STEP_CMD:
				PostMessage(mHwnd,WM_CMD_UI,WP_CMD_UI_RESULT_TEST,NULL);
				RemoveFiles();
				SetCommandLine(INI_Desc->PHID_DETAIL.PCMD_DESCRIPOR[dwCMDCountNow].Cmdline);
				DosCommand();
				dwStep = STEP_CMD_CHECK_REPORT_METHOD;
				break;
			case STEP_REPEAT_CMD:
				PostMessage(mHwnd,WM_CMD_UI,WP_CMD_UI_RESULT_TEST,NULL);
				RemoveFiles();
				SetCommandLine(INI_Desc->PHID_DETAIL.PCMD_DESCRIPOR[dwCMDCountNow].RepeatCmdline);
				DosCommand();
				dwStep = STEP_CMD_CHECK_REPORT_METHOD;
				break;
			case STEP_CMD_CHECK_REPORT_METHOD:
				if(INI_Desc->PHID_DETAIL.PCMD_DESCRIPOR[dwCMDCountNow].bReportingMethodIsFile)
					dwStep = STEP_CMD_CHECK_REPORT_FILE;
				else
					dwStep = STEP_CMD_CHECK_REPORT_LINE;
				break;
			case STEP_CMD_CHECK_REPORT_FILE:
				if(CheckReportContent())
					dwStep = STEP_CMD_PASS;
				else
					dwStep = STEP_CMD_FAIL;
				break;
			case STEP_CMD_CHECK_REPORT_LINE:
				if(CompareContents(INI_Desc->PHID_DETAIL.ReportMsg))
					dwStep = STEP_CMD_PASS;
				else
					dwStep = STEP_CMD_FAIL;
				break;
			case STEP_CMD_PASS:
				dwCMDCountNow++;
				if(dwCMDCountNow < INI_Desc->PHID_DETAIL.dwCMDCount)
					dwStep = STEP_CMD;
				else
				{
					PostMessage(mHwnd,WM_CMD_REPOET,WP_CMD_REPOET_LINE,NULL);
					PostMessage(mHwnd,WM_CMD_UI,WP_CMD_UI_RESULT_PASS,NULL);
					INI_Desc->queHomePageListBox.push("Version PASSED");
					dwStep = STEP_CMD_WAIT_DEV_OUTPUT;
				}
				break;
			case STEP_CMD_FAIL:
				dwFailCount++;
				if(dwFailCount > INI_Desc->PHID_DETAIL.dwFailRepeatCount)
				{
					PostMessage(mHwnd,WM_CMD_REPOET,WP_CMD_REPOET_LINE,NULL);
					PostMessage(mHwnd,WM_CMD_UI,WP_CMD_UI_RESULT_FAIL,NULL);
					dwStep = STEP_CMD_WAIT_DEV_OUTPUT;
				}
				else
				{
					dwStep = STEP_REPEAT_CMD;
				}
				break;
			case STEP_CMD_WAIT_DEV_OUTPUT:
				if(!EnumUSB())
					if(INI_Desc->dwItemIndex == HOME_PAGE_INDEX)
					{
						PostMessage(mHwnd,WM_CMD_UI,WP_CMD_UI_RESULT_WAIT,NULL);
						dwStep = STEP_CMD_GET_USB_DEVICE;
					}
				break;

        }
		Sleep(100);
	}
}
//---------------------------------------------------------------------------
void TCMDThreadAccess::RemoveFiles()
{
	if(!INI_Desc->PHID_DETAIL.PCMD_DESCRIPOR[dwCMDCountNow].bReportingMethodIsFile)
		return;
	AnsiString filePath = GetCurrentDir() + "\\"+INI_Desc->PHID_DETAIL.PCMD_DESCRIPOR[dwCMDCountNow].FileName;
	if(FileExists(filePath))
	{
		remove(filePath.c_str());
    }
}
bool TCMDThreadAccess::CheckReportContent()
{
	AnsiString filePath = GetCurrentDir() + "\\"+INI_Desc->PHID_DETAIL.PCMD_DESCRIPOR[dwCMDCountNow].FileName;

	if (FileExists(filePath))  // 確認檔案是否存在
	{
        TStringList *fileContent = new TStringList();  // 使用 TStringList 讀取檔案內容
		fileContent->LoadFromFile(filePath);
		INI_Desc->PHID_DETAIL.ReportMsg = fileContent->Text;
		if(CompareContents(fileContent->Text))// 比對字串
		{
			return true;
		}
		else
		{
			INI_Desc->PHID_DETAIL.ErrorMsg="(!)Inconsistent string content comparison";
		}
	}
	else
		INI_Desc->PHID_DETAIL.ErrorMsg="(!)Cannot find the result file";

	return false;
}
bool TCMDThreadAccess::CompareContents(AnsiString RepoetContents)
{
	if(INI_Desc->PHID_DETAIL.PCMD_DESCRIPOR[dwCMDCountNow].bContentLineKey)
	{
		AnsiString Temp = RepoetContents.SubString(INI_Desc->PHID_DETAIL.PCMD_DESCRIPOR[dwCMDCountNow].dwContentLineKeyPoint,INI_Desc->PHID_DETAIL.PCMD_DESCRIPOR[dwCMDCountNow].dwContentLineKeyCount);
		if(Temp != INI_Desc->PHID_DETAIL.PCMD_DESCRIPOR[dwCMDCountNow].strContentLineKeyValue)
		{
			if(dwFailCount >= INI_Desc->PHID_DETAIL.dwFailRepeatCount)
			{
				INI_Desc->PHID_DETAIL.CMDMsg += Temp+"[X]\r\n";
				if(dwCMDCountNow == 0)
					INI_Desc->queHomePageListBox.push(INI_Desc->strListErrorCode->Strings[ERROR_FW_VERSION_1_ERROR-1]+": "+Temp);
				else
					INI_Desc->queHomePageListBox.push(INI_Desc->strListErrorCode->Strings[ERROR_FW_VERSION_2_ERROR-1]+": "+Temp);
			}
			return false;
		}
		else
		{
			INI_Desc->PHID_DETAIL.CMDMsg += Temp+"[O]\r\n";
		}
	}
	for(DWORD i = 0 ; i < (DWORD)INI_Desc->PHID_DETAIL.PCMD_DESCRIPOR[dwCMDCountNow].dwContentLineCount ; i++)
	{
		if(!RepoetContents.Pos(INI_Desc->PHID_DETAIL.PCMD_DESCRIPOR[dwCMDCountNow].Content[i]))
			return false;
	}
	return true;
}
void TCMDThreadAccess::SetCommandLine(AnsiString cmd)
{
	strCMD = cmd;
	INI_Desc->PHID_DETAIL.CMDMsg += strCMD+"\r\n";
}
AnsiString TCMDThreadAccess::DosCommand() {
	INI_Desc->PHID_DETAIL.ReportMsg = "";
	PROCESS_INFORMATION proc = {
		0
	}; // 關於進程資訊的一個結構
	long ret;
	bool sPipe;
	STARTUPINFO start = {
		0
	};
	SECURITY_ATTRIBUTES sa = {
		0
	};
	HANDLE hReadPipe;
	HANDLE hWritePipe;
	AnsiString sOutput;
	AnsiString sBuffer;
	unsigned long lngBytesRead;
	char cBuffer[256];
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = 0;
	sa.bInheritHandle = TRUE;
	sPipe = ::CreatePipe(&hReadPipe, &hWritePipe, &sa, 0); // 創建管道

	if (!sPipe) {
		sOutput = "CreatePipe failed. Error: " + AnsiString(GetLastError());
		INI_Desc->PHID_DETAIL.ReportMsg = sOutput;
		return sOutput;
	}
	start.cb = sizeof(STARTUPINFOA);
	start.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	start.hStdOutput = hWritePipe;
	start.hStdError = hWritePipe;
	start.wShowWindow = SW_HIDE;
	sBuffer = strCMD;
	ret = ::CreateProcess(0, sBuffer.c_str(), &sa, &sa, TRUE,
		NORMAL_PRIORITY_CLASS, 0, 0, &start, &proc);
	if (ret == 0) {
		sOutput = "Bad command or filename";
		INI_Desc->PHID_DETAIL.ReportMsg = sOutput;
		return sOutput;
	}
	::CloseHandle(hWritePipe);
	do {
		memset(cBuffer, '\0', sizeof(cBuffer));
		ret = ::ReadFile(hReadPipe, &cBuffer, 255, &lngBytesRead, 0);
		sBuffer = StrPas(cBuffer);
		sOutput = sOutput + sBuffer;
		INI_Desc->PHID_DETAIL.ReportMsg += sBuffer;
		Application->ProcessMessages();

	}
	while (ret != 0);
	::CloseHandle(proc.hProcess);
	::CloseHandle(proc.hThread);
	::CloseHandle(hReadPipe);
	return sOutput;
}
bool TCMDThreadAccess::EnumUSB()
{
	HDEVINFO hDevInfo;
	SP_DEVINFO_DATA DeviceInfoData;
	DWORD i,j;
	AnsiString SS,USBPath;
	PSP_DEVICE_INTERFACE_DETAIL_DATA   pDetail   =NULL;
	GUID GUID_USB =StringToGUID(GUID_USB_DEVICE);
	//--------------------------------------------------------------------------
	//   獲取設備資訊
	hDevInfo = SetupDiGetClassDevs((LPGUID)&GUID_USB,
	0,   //   Enumerator
	0,
	DIGCF_PRESENT | DIGCF_DEVICEINTERFACE );
	if   (hDevInfo   ==   INVALID_HANDLE_VALUE){
		//DEBUG("ERROR - SetupDiGetClassDevs()"); //   查詢資訊失敗
	}
	else{
	//--------------------------------------------------------------------------
		SP_DEVICE_INTERFACE_DATA   ifdata;
		DeviceInfoData.cbSize   =   sizeof(SP_DEVINFO_DATA);
		for (i=0;SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData);i++)	//   枚舉每個USB設備
		{
			ifdata.cbSize   =   sizeof(ifdata);
			if (SetupDiEnumDeviceInterfaces(								//   枚舉符合該GUID的設備介面
			hDevInfo,           //   設備資訊集控制碼
			NULL,                         //   不需額外的設備描述
			(LPGUID)&GUID_USB,//GUID_CLASS_USB_DEVICE,                     //   GUID
			(ULONG)i,       //   設備資訊集�堛熙]備序號
			&ifdata))                 //   設備介面資訊
			{
				ULONG predictedLength   =   0;
				ULONG requiredLength   =   0;
				//   取得該設備介面的細節(設備路徑)
				SetupDiGetInterfaceDeviceDetail(hDevInfo,         //   設備資訊集控制碼
					&ifdata,          //   設備介面資訊
					NULL,             //   設備介面細節(設備路徑)
					0,         	      //   輸出緩衝區大小
					&requiredLength,  //   不需計算輸出緩衝區大小(直接用設定值)
					NULL);            //   不需額外的設備描述
				//   取得該設備介面的細節(設備路徑)
				predictedLength=requiredLength;
				pDetail = (PSP_INTERFACE_DEVICE_DETAIL_DATA)::GlobalAlloc(LMEM_ZEROINIT,   predictedLength);
				pDetail->cbSize   =   sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

				if(SetupDiGetInterfaceDeviceDetail(hDevInfo,         //   設備資訊集控制碼
					&ifdata,             //   設備介面資訊
					pDetail,             //   設備介面細節(設備路徑)
					predictedLength,     //   輸出緩衝區大小
					&requiredLength,     //   不需計算輸出緩衝區大小(直接用設定值)
					NULL))               //   不需額外的設備描述
				{
					try
					{
						char   ch[512];
						for(j=0;j<predictedLength;j++)
						{
						ch[j]=*(pDetail->DevicePath+8+j);
						}
						SS=ch;
						SS = SS.SubString(1,SS.Pos("{")-2);
						if(SS.Pos(INI_Desc->PHID_DETAIL.AutoVPIDContent))
						{
							GlobalFree(pDetail);
							SetupDiDestroyDeviceInfoList(hDevInfo);
							return true;
						}
						//Memo1->Lines->Add(SS);
						//DEBUG(SS);
					}
					catch(...)
					{
						//DEBUG("列舉失敗");
                    }
				}
				GlobalFree(pDetail);
			}
		}
	}
	SetupDiDestroyDeviceInfoList(hDevInfo);
	return false;
}
bool TCMDThreadAccess::InitLED()
{
	if(EnumUSB())
	{
		AnsiString SS;
		SetCommandLine("usbhidtool \"vid_0835&PID_2a13\" 03 25 06 A0");
		DosCommand();
		if(INI_Desc->PHID_DETAIL.ReportMsg.Pos("03 25 06 A0"))
			return true;
		SetCommandLine("usbhidtool \"vid_0835&PID_2a13\" 03 35 06 A0");
		DosCommand();
		if(INI_Desc->PHID_DETAIL.ReportMsg.Pos("03 35 06 A0"))
			return true;
	}
	return false;
}

