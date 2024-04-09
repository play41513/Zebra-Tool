# Zebra Tool
 Controlling the power supply to provide power and using the "Zebra board" to measure voltage values.

## Program

### Zebra LED v1.0
- Notices :Copyright(c) 2023 Leno
- Compiler :Embarcadero RAD Studio 2010 Version 14.0.3615.26342
- OS :Windows 8 ver6.3 Build 9600
- Desc :
	- Release :Zebra Test Tool v2.0(MD-LNA0-A) 、 Zebra Test Tool v2.0(MD-LNA0-B)
	- Program structure improved.

### Zebra Test Tool 1.5.0
- Notices :Copyright(c) 2023 Leno
- Compiler :Embarcadero RAD Studio 2010 Version 14.0.3615.26342
- OS :Windows 8 ver6.3 Build 9600
- Desc :
	- Change "GPIO Pin" to "Voltage Measurement Pin" to increase the number of measurements.
	- LOG file format converted to CSV format.

### Zebra Test Tool 1.4.4
- Notices :Copyright(c) 2023 Leno
- Compiler :Embarcadero RAD Studio 2010 Version 14.0.3615.26342
- OS :Windows 8 ver6.3 Build 9600
- Desc :
	- Corrected the setting in the configuration file to "[OCP]" to disable the OCP feature.

### Zebra Test Tool 1.4.3
- Notices :Copyright(c) 2020 Leno
- Compiler :Embarcadero RAD Studio 2010 Version 14.0.3615.26342
- OS :Windows 8 ver6.3 Build 9600
- Desc :
	- Implemented rounding down to the third decimal place for the voltage values obtained.

### Zebra Test Tool 1.4.2
- Notices :Copyright(c) 2019 Leno
- Compiler :Embarcadero RAD Studio 2010 Version 14.0.3615.26342
- OS :Windows 8 ver6.3 Build 9600
- Desc :
	- Added logging functionality.
	- PSU voltage and current settings screen are hidden, can be displayed by double-clicking "Powered By Power Supplier" with the mouse.
	
### Zebra Test Tool 1.4.1
- Notices :Copyright(c) 2019 Leno
- Compiler :Embarcadero RAD Studio 2010 Version 14.0.3615.26342
- OS :Windows 8 ver6.3 Build 9600
- Desc :
	- Voltage judgment logic modified: Added detection for voltage equal to 0. Previous versions considered 0 voltage as a fail condition.
	- Voltage will not display negative values.

### Zebra Test Tool 1.4.0
- Notices :Copyright(c) 2018 Leno
- Compiler :Embarcadero RAD Studio 2010 Version 14.0.3615.26342
- OS :Windows 8 ver6.3 Build 9600
- Desc :
	- Program structure improved.
	- Added detection for open circuit and short circuit.
	- Added OVP test for DS-SSB5 & DS-SSB6.
	- Added judgment for OVP current range.

### Zebra Test Tool 1.3.0
- Notices :Copyright(c) 2018 Leno
- Compiler :Embarcadero RAD Studio 2010 Version 14.0.3615.26342
- OS :Windows 8 ver6.3 Build 9600
- Desc :
	- Bug fix: When the voltage range is set to 0, the test will now correctly fail.
	- Added OVP test for DS-UCC6(To check LED light prompting window).

### Zebra Test Tool 1.2.4
- Notices :Copyright(c) 2017 Leno
- Compiler :Embarcadero RAD Studio 2010 Version 14.0.3615.26342
- OS :Windows 8 ver6.3 Build 9600
- Desc :
	- Added display of the test product's name in the UI.
	- Added a delay parameter for PSU output power in the INI file under the [PSU-OUT-DELAY-TIME] field.
	- For some products that experience a momentary surge in current when powered on, added a second OCP parameter for the PSU, allowing for a lower current setting after the initial surge to provide additional protection.

### Zebra Test Tool 1.2.3
- Notices :Copyright(c) 2017 Leno
- Compiler :Embarcadero RAD Studio 2010 Version 14.0.3615.26342
- OS :Windows 8 ver6.3 Build 9600
- Desc :
	- Added functionality to input and edit K value by typing "MTT" in the password field.
	- Added the ability to read parameters from different INI files based on the naming convention (INI file named as config_product_number_ini).

### Zebra Test Tool 1.2.2
- Notices :Copyright(c) 2017 Leno
- Compiler :Embarcadero RAD Studio 2010 Version 14.0.3615.26342
- OS :Windows 8 ver6.3 Build 9600
- Desc :
	- Obtain the voltage value with precision up to the second decimal place instead of the third decimal place.

### Zebra Test Tool 1.2.1
- Notices :Copyright(c) 2017 Leno
- Compiler :Embarcadero RAD Studio 2010 Version 14.0.3615.26342
- OS :Windows 8 ver6.3 Build 9600
- Desc :
	- Compatible with GWINSTEK power supplies manufactured in Mainland China.

### Zebra Test Tool 1.2.0
- Notices :Copyright(c) 2017 Leno
- Compiler :Embarcadero RAD Studio 2010 Version 14.0.3615.26342
- OS :Windows 8 ver6.3 Build 9600
- Desc :
	- Continue voltage measurement after abnormal current.

### Zebra Test Tool 1.1.0
- Notices :Copyright(c) 2017 Leno
- Compiler :Embarcadero RAD Studio 2010 Version 14.0.3615.26342
- OS :Windows 8 ver6.3 Build 9600
- Desc :
	- Changed voltage setting range from 5% to custom.
	- Resolved DUG where the program failed to open when enumerating HID devices.

### Zebra Test Tool 1.0.0
- Notices :Copyright(c) 2017 Leno
- Compiler :Embarcadero RAD Studio 2010 Version 14.0.3615.26342
- OS :Windows 8 ver6.3 Build 9600
- Desc :
	- Controlling the power supply to provide power and using the "Zebra board" to measure voltage values.
