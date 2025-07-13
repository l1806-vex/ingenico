#include "GL_GraphicLib.h"

extern void GL_TutorialStepGraphicLib(void);
extern void GL_TutorialStepWindow(void);
extern void GL_TutorialStepLayout(void);
extern void GL_TutorialStepFooter(void);
extern void GL_TutorialStepInput(void);
extern void GL_TutorialStepId(void);
extern void GL_TutorialStepEvent(void);
extern void GL_TutorialStepData(void);
extern void GL_TutorialStepWindowGml(void);
extern void GL_TutorialStepEventGml(void);
extern void GL_TutorialStepDataGml(void);
extern void GL_TutorialStepScrollView(void);
extern void GL_TutorialStepScrollViewGml(void);

/** Tutorial steps */
T_GL_WCHAR GL_TutorialSteps_Menu(T_GL_HGRAPHIC_LIB  graphicLib)
{
	const char * menu [] =
	{
		"Graphic lib creation",
		"Window creation",
		"Layout creation",
		"Footer creation",
		"Inputs fields creation",
		"Assignement id",
		"Event handling",
		"Sets and gets datas",
		"Add scroll view",
		"GML Window creation",
		"GML Event handling",
		"GML Sets and gets datas",
		"GML scroll view",
	0};
	T_GL_WCHAR choice  = 0;

	do
	{
		choice = GL_Dialog_Menu   (graphicLib, 0, menu, choice, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_INFINITE);
		switch(choice)
		{
		case 0  : GL_TutorialStepGraphicLib (); break;
		case 1  : GL_TutorialStepWindow ();       break;
		case 2  : GL_TutorialStepLayout ();       break;
		case 3  : GL_TutorialStepFooter ();       break;
		case 4  : GL_TutorialStepInput ();        break;
		case 5  : GL_TutorialStepId   ();         break;
		case 6  : GL_TutorialStepEvent ();        break;
		case 7  : GL_TutorialStepData ();         break;
		case 8  : GL_TutorialStepScrollView();    break;
		case 9  : GL_TutorialStepWindowGml();     break;
		case 10 : GL_TutorialStepEventGml();      break;
		case 11 : GL_TutorialStepDataGml();       break;
		case 12 : GL_TutorialStepScrollViewGml(); break;
		}
	}
	while(choice != GL_KEY_CANCEL && choice != GL_KEY_CORRECTION);
	return choice;
}
