rem ==========================================================
rem
rem  sample to generate FON file
rem
rem ===========================================================
rem 1- convert TTF to BDF 
Ttf2bdf  -rh 60 -rv 60 -l '0_127'  AerialMono.ttf> ISO1displayMEDIUM.bdf
Ttf2bdf  -rh 60 -rv 50 -l '0_127'  AerialMono.ttf> ISO1displaySMALL.bdf
Ttf2bdf  -rh 80 -rv 70 -l '0_127'  AerialMonoBd.ttf> ISO1displayLARGE.bdf
Ttf2bdf  -rh 90 -rv 80 -l '0_127'  AerialMonoBd.ttf> ISO1displayXLARGE.bdf
Ttf2bdf  -rh 200 -rv 180 -l '0_127'  AerialBd.ttf> ISO1printerBOLD.bdf
Ttf2bdf  -rh 130 -rv 150 -l '0_127'  Aerial.ttf> ISO1printerNORMAL.bdf
Ttf2bdf  -rh 75 -rv 145 -l '0_127' AerialBd.ttf> ISO1printerCONDENSED.bdf
Ttf2bdf  -rh 270 -rv 155 -l '0_127' VerandaBd.ttf > ISO1printerLARGE.bdf
Ttf2bdf  -rh 200 -rv 360 -l '0_127'  AerialBd.ttf> ISO1printerHEIGHTBOLD.bdf

rem 2- convert BDF to FON
bdf2fon -c -tISO1 -w7 -fISO1displayMEDIUM.bdf -s_dMEDIUM_ DEMO.FON
bdf2fon -w7 -y0 -fISO1displaySMALL.bdf -s_dSMALL_ DEMO.FON
bdf2fon -w8 -x2 -fISO1displayLARGE.bdf -s_dLARGE_ DEMO.FON
bdf2fon -w14 -y0 -fISO1displayXLARGE.bdf -s_dXLARGE_ DEMO.FON
bdf2fon -w15 -fISO1printerNORMAL.bdf -s_pNORMAL_ DEMO.FON
bdf2fon -w16 -x3 -fISO1printerBOLD.bdf -s_pBOLD_ DEMO.FON
bdf2fon -x0 -fISO1printerHEIGHTBOLD.bdf -s_pHEIGHTBOLD_ DEMO.FON
bdf2fon -w6 -fISO1printerCONDENSED.bdf -s_pCONDENSED_ DEMO.FON
bdf2fon -w30 -fISO1printerLARGE.bdf -s_pLARGE_ DEMO.FON

rem 3- delete tmp files
del ISO1displayMEDIUM.bdf
del ISO1displaySMALL.bdf
del ISO1displayLARGE.bdf
del ISO1printerNORMAL.bdf
del ISO1printerBOLD.bdf
del ISO1printerCONDENSED.bdf
del ISO1printerLARGE.bdf
del ISO1printerHEIGHTBOLD.bdf
del ISO1displayXLARGE.bdf

rem 4- update one charactere
FONexport _dMEDIUM_ 65 DEMO.FON .\DEMOdMEDIUM65.txt

PAUSE