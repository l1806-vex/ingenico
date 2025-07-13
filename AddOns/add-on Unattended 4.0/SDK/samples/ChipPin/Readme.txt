This sample is based on the sample EmvCustom of the pack "TELIUM EASY PATH EMV to 22.2".

For this sample to work, you must load some modules into the terminal:
3065xxxx 3622xxxx,3421xxxx and 3678xxxx (optional 3678xxxx = EMVTOOL  Warning  use com0 for trace).

Configuration test:
IUP250+IUR250: UCMI065x.pas simuwin2007
CAD30 UPTC: UCR+UPP: UCM3063x.par simuwin2007
CAD30 UPT: UCM+USR+UPP: UCM4004x.par simuwin2007
IUP250+IUR250+IUC150: UCMK462x.pas Vending simuEXE
IUC180B+IUR250: UCMM462x Vending simuEXE

Possibility to use UCMxZxx.par or .pas of each configuration without Host. Amount is 1.00 Euros.
In this case FALL_BACK entry point could be be implemented to managed tracks for exemple.

*************************************
Evolutions Addon unattended 4.0
- Deprecated functions replaced.
- TELIUM EASY PATH EMV 21.1 to 22.2
- Adding vending kinematic.
- 3 types of protocol are supported: Banking, Vending or No Protocol are automatically recognized.
- Adding IUC180B+IUR250
- sleep power management function
- Adding waiting removed card at the end of transaction.
- Backlight managment evolutions
- adding UCMDEVICE_CMD_GETDLLSECU sample
- iGraphicMessage() evolutions
- Rename projet "bankingChipPin" to "ChipPin"

*************************************
Evolutions Addon unattended 3.3

- Update to "TELIUM EASY PATH EMV to 21.1".
- Fix: Cam_Menu(): iLIBUCM_Device_Config(,UCM_DEVICE_ICC0)  instead of  de UCMC_ICC0
- Fix: iUnattendedRead_Iso123(): iLIBUCM_Device_Config( UCM_DEVICE_ICC0, &sDevice ) ;.
- Fix: "FORCED ?" adaptation key press for IUN.
- Adding possibility using UCMxZxx.par or pas.
- Modification message display in iUnattendedLeverLock().
- Adding removed card message after payment.
- Adding: Sample buzzer: adding high and bass buzzer.
- Adding sample Sleep Power Management. iSetSleepPowerManagement()
- Adding ATR sample: iTestAtr()
- CGUI functions deleted.
- Deprecated functions replaced.



