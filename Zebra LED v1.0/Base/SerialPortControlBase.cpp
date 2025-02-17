//---------------------------------------------------------------------------


#pragma hdrstop

#include "SerialPortControlBase.h"
//---------------------------------------------------------------------------
struct ComNum_Info
{
	HANDLE handle;
	HANDLE Threadhandle;
	AnsiString ComName;
};
struct ComNum_Info comNum_Info[10]; // COM資訊

struct ComTestParm
{
	AnsiString PSUName;
	AnsiString DeviceCOM;
	HANDLE Dev_hCom;
	bool bCOMPortOpen;
};
struct ComTestParm mComTestParm[2];
DWORD dwCOMDevIndex;
AnsiString strAllPSUName;

#pragma package(smart_init)

extern DWORD WINAPI WORKTESTExecute(LPVOID Param);
extern DWORD WINAPI FIND_PSUExecute(LPVOID Param);
DWORD dwCMDPrevTime[2];
SerialPortControl::SerialPortControl(void)
{
	dwCOMDevIndex = 0;
	dwCMDPrevTime[0] = 0;
	mComTestParm[0].bCOMPortOpen = false;
	mComTestParm[0].DeviceCOM = "";
	mComTestParm[0].Dev_hCom = NULL;
	mComTestParm[0].PSUName = "PSS";

	dwCMDPrevTime[1] = 0;
	mComTestParm[1].bCOMPortOpen = false;
	mComTestParm[1].DeviceCOM = "";
	mComTestParm[1].Dev_hCom = NULL;
	mComTestParm[1].PSUName = "PSS";
}
void SerialPortControl::CommPort_SerSerialPort(AnsiString SerialPort)
{
	mComTestParm[dwCOMDevIndex].DeviceCOM = SerialPort;
	if(mComTestParm[dwCOMDevIndex].DeviceCOM.Length()>4)
		mComTestParm[dwCOMDevIndex].DeviceCOM = "\\\\.\\"+mComTestParm[dwCOMDevIndex].DeviceCOM;
}
void SerialPortControl::CommPort_Set_Device_Index(DWORD dwIndex)
{
	dwCOMDevIndex = dwIndex;
}
void SerialPortControl::CommPort_Set_Device_Name(DWORD dwIndex,AnsiString PSU_KeyName)
{
	mComTestParm[dwIndex].PSUName = PSU_KeyName;
}
void SerialPortControl::CommPort_Set_Device_COM(DWORD dwIndex,AnsiString PSU_KeyCOM)
{
	mComTestParm[dwIndex].DeviceCOM = PSU_KeyCOM;
}
bool SerialPortControl::CommPort_OpenCommPort()
{
	if(mComTestParm[dwCOMDevIndex].bCOMPortOpen)
		return true;
	DWORD WaitTime=GetTickCount()+3000;
	if(!strstr(mComTestParm[dwCOMDevIndex].DeviceCOM.c_str(),"COM"))
		CommPort_SearchDevCOM(); //偵測是否有裝置名稱
	while(1)
	{
		if(strstr(mComTestParm[dwCOMDevIndex].DeviceCOM.c_str(),"COM"))
		{
			mComTestParm[dwCOMDevIndex].Dev_hCom = CreateFileA(mComTestParm[dwCOMDevIndex].DeviceCOM.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL,
				OPEN_EXISTING, 0, NULL);
			if (mComTestParm[dwCOMDevIndex].Dev_hCom == INVALID_HANDLE_VALUE) {
				Sleep(100);
				CommPort_Stop();
				mComTestParm[dwCOMDevIndex].Dev_hCom = CreateFileA(mComTestParm[dwCOMDevIndex].DeviceCOM.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL,
					OPEN_EXISTING, 0, NULL);
				if (mComTestParm[dwCOMDevIndex].Dev_hCom == INVALID_HANDLE_VALUE){
					mComTestParm[dwCOMDevIndex].bCOMPortOpen = false;
					CloseHandle(mComTestParm[dwCOMDevIndex].Dev_hCom);
					return 0;
				}
			}
			DCB dcb; // 設定comport相關係數
			GetCommState(mComTestParm[dwCOMDevIndex].Dev_hCom, &dcb);
			BuildCommDCBA("9600,n,8,1", &dcb);
			SetCommState(mComTestParm[dwCOMDevIndex].Dev_hCom, &dcb);
			// 設定TimeOut
			COMMTIMEOUTS TimeOut;
			TimeOut.ReadIntervalTimeout = MAXDWORD;
			TimeOut.ReadTotalTimeoutMultiplier = 0;
			TimeOut.ReadTotalTimeoutConstant = 300;
			TimeOut.WriteTotalTimeoutMultiplier  = 0;
			TimeOut.WriteTotalTimeoutConstant  = 0;
			SetCommTimeouts(mComTestParm[dwCOMDevIndex].Dev_hCom, &TimeOut);
			PurgeComm(mComTestParm[dwCOMDevIndex].Dev_hCom,PURGE_TXCLEAR);
			mComTestParm[dwCOMDevIndex].bCOMPortOpen = true;
			return true;
		}
		else if(GetTickCount()>WaitTime)
		{
			mComTestParm[dwCOMDevIndex].bCOMPortOpen = false;
			return false;
		}
		else
			Sleep(100);
	}
}
//---------------------------------------------------------------------------
bool SerialPortControl::CommPort_SendMsg(AnsiString SendMsg)
{
	if (mComTestParm[dwCOMDevIndex].bCOMPortOpen == false)
	{
		if (CommPort_OpenCommPort() == false)
			return false;
	}
	bool bl = false;
	while(true)
	{
		if((GetTickCount() - dwCMDPrevTime[dwCOMDevIndex]) > 100) //每一個CMD間距需為300ms以上
		{
			unsigned long Written;
			bl = WriteFile(mComTestParm[dwCOMDevIndex].Dev_hCom, SendMsg.c_str(), SendMsg.Length(), &Written, NULL);
			dwCMDPrevTime[dwCOMDevIndex] = GetTickCount();
			break;
		}
		Sleep(10);
	}
	return bl;
}
AnsiString SerialPortControl::CommPort_ReadMsg()
{
	DWORD ByteRead;
	char RXBuff[512];
	char buff[512];
	memset(buff, 0, sizeof(buff));
	memset(RXBuff, 0, sizeof(RXBuff));
	while(true)
	{
		if((GetTickCount() - dwCMDPrevTime[dwCOMDevIndex]) > 100) //read至少	100ms以上
		{
			ULONGLONG cmd_TimeOut = GetTickCount() + 1000;
			int ret;
			while (1)
			{
				ret = ReadFile(mComTestParm[dwCOMDevIndex].Dev_hCom, RXBuff, 1024, &ByteRead, NULL);//接收
				if (ret && ByteRead > 0) // 接收到數據
				{
					strncpy(buff, RXBuff, ByteRead);
					while (1)
					{
						ret = ReadFile(mComTestParm[dwCOMDevIndex].Dev_hCom, RXBuff, 1024, &ByteRead, NULL);
						if (ret && ByteRead == 0)
							break;
						else
						{
							strncat(buff, RXBuff, ByteRead);
						}
						Sleep(30);
					}
					break;
				}
				else if (GetTickCount64() > cmd_TimeOut)
				{
					break;
				}
			}
			dwCMDPrevTime[dwCOMDevIndex] = GetTickCount();
			break;
		}
		Sleep(10);
	}
	return AnsiString(buff);
}
 // 取得 regedt COM
void SerialPortControl::CommPort_SearchRegeditCommName()
{
	AnsiString temppath;
	TRegistry *reg = new TRegistry();
	TStringList* itemSet = new TStringList();
	reg->RootKey = HKEY_LOCAL_MACHINE;
	temppath = "HARDWARE\\DEVICEMAP\\SERIALCOMM";
	reg->OpenKey(temppath.c_str(), false);
	reg->GetValueNames(itemSet);
	for(int i=0;i<itemSet->Count;i++)
	{
		AnsiString comName =(AnsiString)reg->ReadString(itemSet->Strings[i]);
		if(strlen(comName.c_str())>4) comName="\\\\.\\"+comName;
		comNum_Info[i].ComName=(AnsiString)comName.c_str();
	}
	reg->CloseKey();
	delete itemSet;
	delete reg;
}
// Create多執行緒 找裝置COM
void SerialPortControl::CommPort_SearchDevCOM()
{
	CommPort_SearchRegeditCommName();
	mComTestParm[dwCOMDevIndex].DeviceCOM = "";
	int Count=0;
	while(strstr(comNum_Info[Count].ComName.c_str(),"COM"))
	{
		comNum_Info[Count].Threadhandle = ::CreateThread(0, 0, WORKTESTExecute, (void*)Count, 0, NULL);
		CloseHandle(comNum_Info[Count].Threadhandle);
		Count++;
	}
}
//執行緒
DWORD WINAPI WORKTESTExecute(LPVOID Param) // 執行續
{
	//開COM
	comNum_Info[(int)Param].handle = CreateFileA((comNum_Info[(int)Param].ComName).c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, 0, 0);
	if (comNum_Info[(int)Param].handle != INVALID_HANDLE_VALUE) {
		DCB dcb;
		GetCommState(comNum_Info[(int)Param].handle, &dcb);
		BuildCommDCBA("9600,n,8,1", &dcb);
		SetCommState(comNum_Info[(int)Param].handle, &dcb);

		COMMTIMEOUTS TimeOut;
		GetCommTimeouts(comNum_Info[(int)Param].handle, &TimeOut);
		TimeOut.ReadIntervalTimeout = MAXDWORD;
		TimeOut.ReadTotalTimeoutMultiplier = 0;
		TimeOut.ReadTotalTimeoutConstant = 300;  //(總讀取 time out 時間 = 0.1 秒)
		TimeOut.WriteTotalTimeoutMultiplier = 0;
		TimeOut.WriteTotalTimeoutConstant = 100; //(總寫入 time out 時間 = 0.1 秒)
		SetCommTimeouts(comNum_Info[(int)Param].handle, &TimeOut);
	//寫
		unsigned long Written ;
		char* data="*idn?\n";
		WriteFile(comNum_Info[(int)Param].handle,data,strlen(data),&Written,NULL);
	//讀
		DWORD ByteRead;
		char RXBuff[1024];
		char buff[1024];
		ReadFile(comNum_Info[(int)Param].handle, RXBuff, 1024, &ByteRead,NULL);//接收
		if (ByteRead>0) // 接收到數據
		{
			strncpy(buff,RXBuff,ByteRead);
			if(strstr(buff,mComTestParm[dwCOMDevIndex].PSUName.c_str()))
			{
				mComTestParm[dwCOMDevIndex].DeviceCOM = comNum_Info[(int)Param].ComName;
				dwCMDPrevTime[dwCOMDevIndex] = GetTickCount();
			}
		}
		CloseHandle(comNum_Info[(int)Param].handle);
		memset(RXBuff, 0, sizeof(RXBuff));
	}
	return 0;
}
void SerialPortControl::CommPort_Stop()
{
	mComTestParm[dwCOMDevIndex].bCOMPortOpen = false;
	if(mComTestParm[dwCOMDevIndex].Dev_hCom != NULL)
	{
		CloseHandle(mComTestParm[dwCOMDevIndex].Dev_hCom);
		mComTestParm[dwCOMDevIndex].Dev_hCom = NULL;
	}
}
// Create多執行緒 找裝置COM
AnsiString SerialPortControl::CommPort_SearchAllDevCOM()
{
	strAllPSUName = "";
	CommPort_SearchRegeditCommName();
	mComTestParm[dwCOMDevIndex].DeviceCOM = "";
	int Count=0;
	HANDLE threadHandles[10];
	while(strstr(comNum_Info[Count].ComName.c_str(),"COM"))
	{
		comNum_Info[Count].Threadhandle = ::CreateThread(0, 0, FIND_PSUExecute, (void*)Count, 0, NULL);
		threadHandles[Count] = comNum_Info[Count].Threadhandle;
		Count++;
	}
	WaitForMultipleObjects(Count, threadHandles, TRUE, INFINITE);
    for (int i = 0; i < Count; i++)
    {
        CloseHandle(threadHandles[i]);
	}

	return strAllPSUName;
}
//執行緒
DWORD WINAPI FIND_PSUExecute(LPVOID Param) // 執行續
{
	//開COM
	comNum_Info[(int)Param].handle = CreateFileA((comNum_Info[(int)Param].ComName).c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, 0, 0);
	if (comNum_Info[(int)Param].handle != INVALID_HANDLE_VALUE) {
		DCB dcb;
		GetCommState(comNum_Info[(int)Param].handle, &dcb);
		BuildCommDCBA("9600,n,8,1", &dcb);
		SetCommState(comNum_Info[(int)Param].handle, &dcb);

		COMMTIMEOUTS TimeOut;
		GetCommTimeouts(comNum_Info[(int)Param].handle, &TimeOut);
		TimeOut.ReadIntervalTimeout = MAXDWORD;
		TimeOut.ReadTotalTimeoutMultiplier = 0;
		TimeOut.ReadTotalTimeoutConstant = 300;  //(總讀取 time out 時間 = 0.1 秒)
		TimeOut.WriteTotalTimeoutMultiplier = 0;
		TimeOut.WriteTotalTimeoutConstant = 100; //(總寫入 time out 時間 = 0.1 秒)
		SetCommTimeouts(comNum_Info[(int)Param].handle, &TimeOut);
	//寫
		unsigned long Written ;
		char* data="*idn?\n";
		WriteFile(comNum_Info[(int)Param].handle,data,strlen(data),&Written,NULL);
	//讀
		DWORD ByteRead;
		char RXBuff[512];
		char buff[512]={0};
		ReadFile(comNum_Info[(int)Param].handle, RXBuff, 512, &ByteRead,NULL);//接收
		if (ByteRead>0) // 接收到數據
		{
			strncpy(buff,RXBuff,ByteRead);
			strAllPSUName += AnsiString(comNum_Info[(int)Param].ComName)+"-"+AnsiString(buff);
		}
		CloseHandle(comNum_Info[(int)Param].handle);
		memset(RXBuff, 0, sizeof(RXBuff));
	}
	return 0;
}

