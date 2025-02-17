//---------------------------------------------------------------------------

#ifndef SerialPortControlBaseH
#define SerialPortControlBaseH

#include <vcl.h>
#include <string>
#include <stdio.h>
#include <Registry.hpp>
using namespace std;
//---------------------------------------------------------------------------


class SerialPortControl{
	private:

		void  CommPort_SearchRegeditCommName();
		void  CommPort_SearchDevCOM();

	public:
		SerialPortControl::SerialPortControl(void);
        void CommPort_SerSerialPort(AnsiString SerialPort);
		bool CommPort_SendMsg(AnsiString SendMsg);
		AnsiString CommPort_ReadMsg();
		AnsiString CommPort_SearchAllDevCOM();
		void CommPort_Set_Device_COM(DWORD dwIndex,AnsiString PSU_KeyCOM);

		bool 	CommPort_OpenCommPort();
		void 	CommPort_Stop();
		void	CommPort_Set_Device_Index(DWORD dwIndex);
		void	CommPort_Set_Device_Name(DWORD dwIndex,AnsiString PSU_KeyName);
};
#endif
