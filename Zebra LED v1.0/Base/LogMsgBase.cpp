//---------------------------------------------------------------------------


#pragma hdrstop

#include <vcl.h>
#include "LogMsgBase.h"
#include <ComObj.hpp>

//---------------------------------------------------------------------------

#pragma package(smart_init)

AnsiString strLogPath,strLogName;
cLogMsg::cLogMsg(void) {
	LOG_DESC.strList = new TStringList();
}

void cLogMsg::AddLocalFilePath(AnsiString ToolName)
{
	AnsiString Path = "C:\\ASMP\\log\\"+ToolName+"\\";
	if(!DirectoryExists(Path))
	{
		AnsiString SS,Temp = "";
		while(true)
		{
			SS = Path.SubString(1,Path.Pos("\\"));
			Path.Delete(1,Path.Pos("\\"));
			Temp+=SS;
			_mkdir( Temp.c_str());
			if(Path == "")
				break;
		}
	}
	strLogPath = Path;
}
void cLogMsg::WriteErrorMsg(AnsiString Line)
{
	LOG_DESC.errorcode = Line;
}
void cLogMsg::WriteItemMsg(DWORD ItemIndex,AnsiString ItemName,AnsiString Result)
{
	AnsiString strTemp = "Item"+AnsiString(ItemIndex)+","+ItemName+","+Result+",";
	LOG_DESC.strList->Add(strTemp);
}
void cLogMsg::WriteLocalLOG(AnsiString Time,bool bPass)
{
	AnsiString Temp;
	Temp = "datetime,"+AnsiString(FormatDateTime("yyyy-mm-dd,hh-nn-ss", Now()))+",";
	for(int i = 0 ; i < LOG_DESC.strList->Count ; i++)
	{
		Temp += LOG_DESC.strList->Strings[i];
    }
	Temp +="TotalTime,"+Time;
	Temp += bPass ? ",Result,PASS" : ",Result,FAIL";
	if(!bPass)
		Temp += ",errorcode,"+LOG_DESC.errorcode;
	Temp += "\r\n";


	FILE * fp;
	strLogName = strLogPath+AnsiString(FormatDateTime("yyyy-mm-dd", Now()))+".log";
	fp = fopen(strLogName.c_str(),"a+");
	fseek( fp, 0, SEEK_END);
	fwrite(Temp.c_str(),Temp.Length(),1,fp); //寫入一筆資料
	fclose(fp);
}
