//---------------------------------------------------------------------------

#ifndef FileControlBaseH
#define FileControlBaseH
#include <fstream.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <IniFiles.hpp>
#include "ConstantString.h"
//---------------------------------------------------------------------------

class cFileControl
{
	private:
		AnsiString strSettingINI;

		INI_DESCRIPOR *INI_Desc;

	public:
		cFileControl::cFileControl(INI_DESCRIPOR *ini);
		void WritePSUNameToFile(DWORD Index,AnsiString Value);
		void WritePSUCOMToFile(DWORD Index,AnsiString Value);
		bool FindINIFile();
		void ReadINIFile();
		void 		  WriteINIFile(INI_DESCRIPOR info);

};
#endif
