//---------------------------------------------------------------------------

#ifndef PowerSupplyAccessH
#define PowerSupplyAccessH

#include "SerialPortControlBase.h"
#include "ConstantString.h"
//---------------------------------------------------------------------------
class PowerSupplyAccess
{
	private:
		SerialPortControl *mSerialPortControl;
		INI_DESCRIPOR *INI_Desc;
		DWORD dwItemIndex,dwPSUIndex;
	public:
		PowerSupplyAccess::PowerSupplyAccess(INI_DESCRIPOR *ini);
		bool CheckPSUIsOnline();
		bool ClosePower();
		void ClosePowerSupply();
		bool OpenPower();
		bool SetParameter();
		bool ReturnPowerSupplyStatus();
		AnsiString GetValue();
		void SetDeviceIndex(DWORD ItemIndex,DWORD PSUIndex);
		AnsiString FindAllPowerSupplyName();
		void SetDeviceCOM();
};
#endif
