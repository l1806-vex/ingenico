This sample is based on the sample Cless of the SDK and adapted to iUN.

No PROTOCOL, VENDING and BANKING kinematics are supported depending on the parameters (automatically reconized)
	- 1=BANKING (CLESS FIELD is always opened)
	- 2=VENDING (CLESS FIELD is always opened)
	- 3=NO PROTOCOL (CLESS FIELD is always opened or by key in this sample)
The CLESS Field is always opened (compilation with define UCMCFIELD=1) or just for transaction depending on up function key if possible.

All types of CLESS card is accepted.

VENDING configuration runs with SIMUEXE simulator.
BANKING configuration runs with SimuWin2007 simulator.

SIMUEXE simulator supports preselection mode (first selection then card) and normal mode (first card then selection ).
This sample supports this 2 modes.

This sample has been tested:
	- UCM + Vending Pass, VendingPass.m34, parameter Vending ucmc6401*.par  (compilation with UCMCFIELD=1)
	- CAD30 UCR + CAD30 UPP + Vending Pass, VendingPass.m38 ucm9003*.par (compilation with UCMCFIELD=0)
	- IUC180, cless.m50,  parameter Vending ucmJ401*.pas and no protocol ucmJZ01*.pas (compilation with UCMCFIELD=1)
	- IUC180B, cless.m55,  parameter Vending ucmJ401*.pas and no protocol ucmJZ01*.pas (compilation with UCMCFIELD=1 or 0)
	- IUP250 + IUR250 + IUC150, cless.m49, parameter Banking ucmk061*.pas (compilation with UCMCFIELD=0) 


*************************************
Evolutions Addon unattended 4.0
	- Parameters (automatically reconized) for transaction cinematic and protocol.
	- New UCMCFIELD define for compilation. give_your_specific_context() need this information to launch or not cless field.
	- Compilation gnu 434, ingedev 7.18.0.3.
	- SDK 9.9.2 or superior for IUC180B.
	- sample with option telium no signed

Evolutions Addon unattended 3.3
	- Adding: Sample buzzer: adding high and bass buzzer.
	- Adding Different price value depend of choice.
	- SDK 9.8.0 deprecated function replaced.
	
