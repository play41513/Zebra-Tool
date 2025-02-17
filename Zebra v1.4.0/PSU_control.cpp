//---------------------------------------------------------------------------


#pragma hdrstop
#include "main.h"
#include "PSU_control.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
HANDLE PSU_hCom;
extern DWORD WINAPI WORKTESTExecute(LPVOID Param);
AnsiString DeviceCOM;
bool g_OVP = false,g_OPEN = false;
int get_current_count = 0;

struct ComNum_Info {
HANDLE handle;
HANDLE Threadhandle;
AnsiString ComName;
};
struct ComNum_Info comNum_Info[10]; // COM資訊
DWORD cmd_TimeOut;

int cmd_status(char *s)
{
	char *p,*p1;
	int x;
	p =s;
	p1 =strstr(p,"\n");
	if(p1 ==NULL) return -1;
	*p1 =0;
	x =atoi(p);
	if(x ==1) return TEST_OPEN_CIRCUIT;
	else
		return TEST_SHORT_CIRCUIT;
}
int cmd_get_system_consumptoin(char *s)
{
	string buff(s);
	char zbuf[200];
	string Sys_Voltage=buff.substr(0,5);
	string Sys_Current=buff.substr(6,5);
	sprintf(zbuf,"System Power : %.4fV  %.4fA",atof(Sys_Voltage.c_str()),atof(Sys_Current.c_str()));
	FrmMain->pl_sys_power->Caption = zbuf;
	DEBUG(zbuf);
	FrmMain->Refresh();
	get_current_count++;
	if(atof(Sys_Voltage.c_str())==0||atof(Sys_Current.c_str())==0)
	{
		 DEBUG(atof(Sys_Current.c_str()));
		 FrmMain->que_cmd.push(":OUTPut:STATe?\n");
		 return RS232_WRITE;
	}
	if(get_current_count>2||g_OVP)
	{
		if(get_current_count==3||g_OVP)
		{
			float max_current;
			float min_current;
			if(g_OVP)
			{
				max_current=FrmMain->g_OVP_VOL_MAX/1000;
				min_current=FrmMain->g_OVP_VOL_MIN/1000;;
			}
			else
			{
				max_current=(FrmMain->edt_max->Text.ToDouble())/1000;
				min_current=(FrmMain->edt_min->Text.ToDouble())/1000;
			}
			if(atof(Sys_Current.c_str())<=max_current&&atof(Sys_Current.c_str())>=min_current)
				return TEST_PASS;
			else
				return TEST_FAIL;
		}
	}
	return RS232_WRITE;
}
const 	CMD_DESC zCMD_MAP[]=
{
	{":OUTPut:STATe?",cmd_status},
	{"CHAN1:MEASure:VOLTage?;CURRent?",cmd_get_system_consumptoin},
};
bool cPSU::open_psu_com()
{
	DWORD WaitTime=GetTickCount()+5000;
	if(!strstr(DeviceCOM.c_str(),"COM")) SearchPSUCOM(); //偵測是否有裝置名稱
	while(1)
	{
		if(strstr(DeviceCOM.c_str(),"COM"))
		{
			PSU_hCom = CreateFile(WideString(DeviceCOM).c_bstr(), GENERIC_READ | GENERIC_WRITE, 0, NULL,
				OPEN_EXISTING, 0, NULL);
			if (PSU_hCom == INVALID_HANDLE_VALUE) {
				FrmMain->Delay(100);
				PSU_Stop();
				PSU_hCom = CreateFile(WideString(DeviceCOM).c_bstr(), GENERIC_READ | GENERIC_WRITE, 0, NULL,
					OPEN_EXISTING, 0, NULL);
				if (PSU_hCom == INVALID_HANDLE_VALUE){
					CloseHandle(PSU_hCom);
					return 0;
				}
			}
			DCB dcb; // 設定comport相關係數
			GetCommState(PSU_hCom, &dcb);
			BuildCommDCB(L"9600,n,8,1", &dcb);
			SetCommState(PSU_hCom, &dcb);
			// 設定TimeOut
			COMMTIMEOUTS TimeOut;
			TimeOut.ReadIntervalTimeout = MAXDWORD;
			TimeOut.ReadTotalTimeoutMultiplier = 0;
			TimeOut.ReadTotalTimeoutConstant = 300;
			TimeOut.WriteTotalTimeoutMultiplier  = 0;
			TimeOut.WriteTotalTimeoutConstant  = 0;
			SetCommTimeouts(PSU_hCom, &TimeOut);

			return 1;
		}
		else if(GetTickCount()>WaitTime)
			return 0;
		else FrmMain->Delay(100);
	}
}
int  cPSU::PSU_CMD_Test(bool bOVP)
{
	int nResult = 0;
	unsigned long Written ;
	int step = RS232_WRITE ;
	FrmMain->bCurFail = false;
	g_OVP = bOVP;
	get_current_count = 0;
	while(step)
	{
		switch(step)
		{
			case RS232_WRITE:
				if(!strcmp(FrmMain->que_cmd.front().c_str(),"Delay"))
				{
					step=RS232_READ;
					break;
				}
				if(FrmMain->que_cmd.empty())
				{
					if(bOVP&&FrmMain->bLED)
					{
						step=TEST_END;
						break;
                    }
					FrmMain->que_cmd.push("CHAN1:MEASure:VOLTage?;CURRent?\n");
				}
			//寫
				DEBUG(FrmMain->que_cmd.front());
				WriteFile(PSU_hCom,FrmMain->que_cmd.front().c_str(),FrmMain->que_cmd.front().Length(),&Written,NULL);
				cmd_TimeOut=GetTickCount()+1000;
				step=RS232_READ;
				break;
			case RS232_READ:
				//讀
				if(!strcmp(FrmMain->que_cmd.front().c_str(),"CHAN1:MEASure:VOLTage?;CURRent?\n")
					||!strcmp(FrmMain->que_cmd.front().c_str(),":OUTPut:STATe?\n"))
				{
					DWORD ByteRead;
					char RXBuff[20];
					char buff[20];
					while(1)
					{
						ReadFile(PSU_hCom, RXBuff, 20, &ByteRead,NULL);//接收
						if (ByteRead>0) // 接收到數據
						{
							strncpy(buff,RXBuff,ByteRead);
							for(int x=0;x<2;x++){
								if(zCMD_MAP[x].pfn ==NULL) break;
								if(strstr(FrmMain->que_cmd.front().c_str(),zCMD_MAP[x].cmd)){
									step = (*(zCMD_MAP[x].pfn))(buff);
									if(step){}
									else step = RS232_WRITE;
									break;
								}
							}
							FrmMain->que_cmd.pop();

							memset(buff, 0, sizeof(buff));
							memset(RXBuff, 0, sizeof(RXBuff));
							break;
						}
						else if(GetTickCount()>cmd_TimeOut)
						{
							step = PSU_NO_RESPOND;
							break;
						}
					}
				}
				else
				{
					if(!strcmp(FrmMain->que_cmd.front().c_str(),"Delay"))
                      FrmMain->Delay(FrmMain->psu_out_delay_time);
					else FrmMain->Delay(300); // PSU回應間隔
					FrmMain->que_cmd.pop();
					step = RS232_WRITE;
				}
				break;
			case TEST_PASS:
				nResult = TEST_PASS;
				step = TEST_END;
				break;
			case TEST_FAIL:
				FrmMain->ERROR_MSG = MSG_CURRENT_FAIL;
				nResult = TEST_FAIL;
				step = TEST_END;
				break;
			case TEST_SHORT_CIRCUIT:
				nResult = TEST_SHORT_CIRCUIT;
				DEBUG(MSG_DUT_OCP);
				FrmMain->ERROR_MSG = MSG_DUT_OCP;
				FrmMain->bCurFail = true;
				step = TEST_END;
				break;
			case TEST_OPEN_CIRCUIT:
				nResult = TEST_OPEN_CIRCUIT;
				FrmMain->ERROR_MSG = MSG_DUT_OPEN_CIRCUIT;
				FrmMain->bCurFail = true;
				return TEST_OPEN_CIRCUIT;
			case PSU_NO_RESPOND:
				nResult = PSU_NO_RESPOND;
				FrmMain->ERROR_MSG = MSG_PSU_NO_RESPOND;
				step = TEST_END;
				break;
			case TEST_END:
				break;

		}
	}
	return nResult;
}
//---------------------------------------------------------------------------
void cPSU::search_Reg_ComNum() // 取得 regedt COM
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
void cPSU::SearchPSUCOM()// Create多執行緒 找裝置
{
	search_Reg_ComNum();
	int Count=0;
	while(strstr(comNum_Info[Count].ComName.c_str(),"COM"))
	{
		comNum_Info[Count].Threadhandle = ::CreateThread(0, 0, WORKTESTExecute, (void*)Count, 0, NULL);
		CloseHandle(comNum_Info[Count].Threadhandle);
		Count++;
	}
}
DWORD WINAPI WORKTESTExecute(LPVOID Param) // 執行續
{

//開COM
	comNum_Info[(int)Param].handle = CreateFile(WideString(comNum_Info[(int)Param].ComName).c_bstr(), GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, 0, 0);
	if (comNum_Info[(int)Param].handle != INVALID_HANDLE_VALUE) {
		DCB dcb; // 設定comport相關係數
		GetCommState(comNum_Info[(int)Param].handle, &dcb);
		BuildCommDCB(L"9600,n,8,1", &dcb);
		SetCommState(comNum_Info[(int)Param].handle, &dcb);
		// 設定TimeOut
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
			if(strstr(buff,"GW.Inc,PSS-2005"))
			{
				DEBUG(AnsiString(buff)+"["+comNum_Info[(int)Param].ComName+"]");
				DeviceCOM = comNum_Info[(int)Param].ComName;
			}
		}
		CloseHandle(comNum_Info[(int)Param].handle);
		memset(RXBuff, 0, sizeof(RXBuff));
	}
	return 0;
}
void cPSU::PSU_Stop() {
	unsigned long Written ;
	WriteFile(PSU_hCom,":OUTPut:STATe 0\n",strlen(":OUTPut:STATe 0\n"),&Written,NULL);
	WriteFile(PSU_hCom,"OUTPut:PROTection:CLEar\n",strlen("OUTPut:PROTection:CLEar\n"),&Written,NULL);
	WriteFile(PSU_hCom,"CHAN1:PROTection:CURRent 0\n",strlen("CHAN1:PROTection:CURRent 0\n"),&Written,NULL);
	CloseHandle(PSU_hCom);
	FrmMain->Refresh();
}
void cPSU::QueueClear()//Queue Clear
{
	while(!FrmMain->que_cmd.empty())
	{
		FrmMain->que_cmd.pop();
	}
}

