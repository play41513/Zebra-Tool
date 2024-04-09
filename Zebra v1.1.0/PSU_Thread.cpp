//---------------------------------------------------------------------------


#pragma hdrstop

#include "test_thread.h"
#include "main.h"
extern HANDLE hCom;
//---------------------------------------------------------------------------

#pragma package(smart_init)
int get_current_count;
float total_current;
//---------------------------------------------------------------------------
int cmd_status(char *s)
{  //不使用
	char *p,*p1;
	int x;
	p =s;
	p1 =strstr(p,"\n");
	if(p1 ==NULL) return -1;
	*p1 =0;
	x =atoi(p);
	if(x ==1) frmMain->moDebug->Lines->Add(x);
	else
	{
		frmMain->moDebug->Lines->Add(x);
		frmMain->test_stop();
		frmMain->pl_result->Color=clRed;
		frmMain->pl_result->Caption="FAIL";

	}
}
int cmd_get_system_consumptoin(char *s)
{
	string buff(s);
	char zbuf[200];
	string Sys_Voltage=buff.substr(0,5);
	string Sys_Current=buff.substr(6,5);
	sprintf(zbuf,"System Power : %.4fV  %.4fA",atof(Sys_Voltage.c_str()),atof(Sys_Current.c_str()));
	frmMain->pl_sys_power->Caption=zbuf;
	frmMain->moDebug->Lines->Add(zbuf);
	frmMain->Refresh();
	get_current_count++;
	if(atof(Sys_Voltage.c_str())==0||atof(Sys_Current.c_str())==0)
	{
		frmMain->bError_Happened=true;
		frmMain->Error_Msg="The Device is Open Circuit";
		frmMain->moDebug->Lines->Add(atof(Sys_Current.c_str()));
		frmMain->pl_result->Color=clRed;
		frmMain->pl_result->Caption="FAIL";
		frmMain->test_stop();
	}
	else if(get_current_count>2)
	{
		total_current+=atof(Sys_Current.c_str());
		if(get_current_count==5)
		{
			int max_current=frmMain->SET_AVG_CURRENT+frmMain->SET_AVG_CURRENT/10;
			int min_current=frmMain->SET_AVG_CURRENT-frmMain->SET_AVG_CURRENT/10;
			int get_avg_current=total_current*1000/3;
			if(get_avg_current<=max_current&&get_avg_current>=min_current)
			{
				frmMain->pl_result->Color=clLime;
				frmMain->pl_result->Caption="PASS";
			}
			else
			{
				frmMain->bError_Happened=true;
				frmMain->Error_Msg="The Device Circuit is not right";
				frmMain->moDebug->Lines->Add(atof(Sys_Current.c_str()));
				frmMain->pl_result->Color=clRed;
				frmMain->pl_result->Caption="FAIL";
			}
			frmMain->test_stop();
		}
	}
}
const 	CMD_DESC zCMD_MAP[]=
{
	{":OUTPut:STATe?",cmd_status},
	{"CHAN1:MEASure:VOLTage?;CURRent?",cmd_get_system_consumptoin},
};

__fastcall CL_CMD_TASK::CL_CMD_TASK(bool CreateSuspended) : TThread
(CreateSuspended) {
}
void __fastcall CL_CMD_TASK::Execute(void)
{
	//---- Place thread code here ----
	get_current_count=0;
	total_current=0;
	while(!Terminated)
	{
		Synchronize(Polling_Task);
	}
}
//---------------------------------------------------------------------------
void __fastcall CL_CMD_TASK::Polling_Task(void)
{
	unsigned long Written ;

	switch(frmMain->now_step)
	{
		case 1:
			if(frmMain->que_cmd.empty())
			{
				frmMain->que_cmd.push("CHAN1:MEASure:VOLTage?;CURRent?\n");
				//frmMain->que_cmd.push(":OUTPut:STATe?\n");
			}
		//寫
			frmMain->moDebug->Lines->Add(frmMain->que_cmd.front());
			WriteFile(hCom,frmMain->que_cmd.front().c_str(),frmMain->que_cmd.front().Length(),&Written,NULL);
			frmMain->now_step=2;
			cmd_TimeOut=GetTickCount()+1000;
			frmMain->moDebug->Lines->Add("time(ms): "+(AnsiString)(GetTickCount()-frmMain->init_time));
			break;
		case 2:
			//讀
			if(!strcmp(frmMain->que_cmd.front().c_str(),"CHAN1:MEASure:VOLTage?;CURRent?\n")||!strcmp(frmMain->que_cmd.front().c_str(),":OUTPut:STATe?\n"))
			{
				DWORD ByteRead;
				char RXBuff[20];
				char buff[20];
				while(1)
				{
					ReadFile(hCom, RXBuff, 20, &ByteRead,NULL);//接收
					if (ByteRead>0) // 接收到數據
					{
						strncpy(buff,RXBuff,ByteRead);
						for(int x=0;x<100;x++){
							if(zCMD_MAP[x].pfn ==NULL) break;
							if(strstr(frmMain->que_cmd.front().c_str(),zCMD_MAP[x].cmd)){
								(*(zCMD_MAP[x].pfn))(buff);
								break;
							}
						}
						frmMain->que_cmd.pop();
						frmMain->now_step=1;
						memset(buff, 0, sizeof(buff));
						memset(RXBuff, 0, sizeof(RXBuff));
						break;
					}
					else if(GetTickCount()>cmd_TimeOut)
					{
						frmMain->bError_Happened=true;
						frmMain->Error_Msg="The Power Supply is no respond!";
						frmMain->test_stop();
						frmMain->pl_result->Color=clRed;
						frmMain->pl_result->Caption="FAIL";
						break;
					}
				}
			}
			else
			{
				frmMain->Delay(100);
				frmMain->que_cmd.pop();
				frmMain->now_step=1;
			}
			break;
	}


}

