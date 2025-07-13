This sample is based on the sample Cless of the SDK and adapted to iUN.

Both VENDING and BANKING kinematics are supported depending on the define UCMCINEMATIC in file UTIL.H:
	- 1=BANKING
	- 2=VENDING

All types of CLESS card is accepted.

VENDING configuration runs with SIMUEXE simulator.
BANKING configuration runs with SimuWin2007 simulator.

SIMUEXE simulator supports preselection mode (first selection then card) and normal mode (first card then selection ).
This sample supports this 2 modes.

This sample has been tested:
	- UCM + Vending Pass, VendingPass.m34, parameter Vending ucmc6401*.par 
	- CAD30 UCR + CAD30 UPP + Vending Pass, VendingPass.m38 ucm9003d.par
	- IUC180, cless.m50,  parameter Vending ucmJ401*.pas 
	- IUP250 + IUR250 + IUC150, cless.m49, parameter Banking ucmk061*.pas 


*************************************
Evolutions Addon unattended 3.3
	- Adding: Sample buzzer: adding high and bass buzzer.
	- Adding Different price value depend of choice.
	- SDK 9.8.0 deprecated function replaced.
	
