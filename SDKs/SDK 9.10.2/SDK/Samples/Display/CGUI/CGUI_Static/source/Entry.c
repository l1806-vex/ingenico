#include <sdk30.h>
#include "CGUI_Static.h"


#define NUMBER_OF_ITEMS(a)   (sizeof(a)/sizeof((a)[0]))


static const char appname[]    = "CGUI_Static";


int Main(unsigned int size, StructPt *data)
{
	NO_SEGMENT No;
	int            ret;
	No = ApplicationGetCurrent();
	switch(data->service)
	{
	case AFTER_RESET :
		ret = after_reset(No,NULL,&data->Param.AfterReset.param_out);
		break;

	case MORE_FUNCTION :
		ret = more_function(No,NULL,NULL);
		break;

	case IS_NAME :
		ret = is_name(No,NULL,&data->Param.IsName.param_out);
		break;

	case IS_STATE :
		ret = is_state(No,NULL,&data->Param.IsState.param_out);
		break;

	case GIVE_YOUR_DOMAIN :
		ret = give_your_domain(No,NULL,&data->Param.GiveYourType.param_out);
		break;

	default:
		break;
	}
	return FCT_OK;
}


int after_reset( NO_SEGMENT no, void *p1, S_TRANSOUT *etatseq )
{
	unsigned char chgt;
	char  type;

	// Test if it is the first execution of the application.
	first_init( no, &chgt,(unsigned char *) &type);

	if ( chgt == 0xFF )
	{
		raz_init(no);
	}
	return FCT_OK;
}


int is_state(NO_SEGMENT no,void *p1,S_ETATOUT *etatseq)
{
	S_ETATOUT etatout;
	int retour;

	memcpy (&etatout, etatseq, sizeof(etatout));
	etatout.returned_state[etatout.response_number].state.response = REP_OK;
	memcpy (etatseq, &etatout, sizeof(etatout));
	retour = is_name (no, PT_NULL, etatseq);
	return (retour);
}


int is_name(NO_SEGMENT no,void *p1,S_ETATOUT *etatseq)
{
	S_ETATOUT etatout;

	memcpy ((char *)&etatout, (char *)etatseq, sizeof(etatout));
	strcpy((char *)etatout.returned_state[etatout.response_number].appname,(char *)appname);
	etatout.returned_state[etatout.response_number].no_appli = no;
	etatout.response_number++;
	memcpy (etatseq, &etatout, sizeof(etatout));
	return (FCT_OK);
}


int give_your_domain(NO_SEGMENT no,void *p1,S_INITPARAMOUT *param_out)
{
	S_INITPARAMOUT etatout;

	memcpy (&etatout, param_out, sizeof(etatout));
	etatout.returned_state[etatout.response_number].mask     = MSK_MDP|MSK_SWIPE|MSK_TYPE_PPAD|MSK_PINPAD|MSK_STANDARD|MSK_LANGUE|MSK_FRMT_DATE|MSK_DATE;
	etatout.returned_state[etatout.response_number].application_type = TYP_EXPORT;
	etatout.response_number++;
	memcpy (param_out, &etatout, sizeof(etatout));
	return (FCT_OK);
}


typedef int (*T_SERVICE_FUNCTION)(unsigned int nSize, void*Data);

int give_interface(unsigned short no,void *p1,void *p2)
{
	service_desc_t MesServices[40];
	int i ;
	i = 0 ;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = IS_NAME;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = GIVE_YOUR_DOMAIN;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = MORE_FUNCTION;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = AFTER_RESET;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;

	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = IS_STATE;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;

	ServiceRegister(i,MesServices);

	return FCT_OK;
}


#ifdef __cplusplus
extern "C"
{
#endif
void entry(void)
{
	object_info_t info;

	ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(),&info);
	give_interface(info.application_type, NULL, NULL);

}
#ifdef __cplusplus
}
#endif



int more_function( NO_SEGMENT no, void *p1, void *p2 )
{
	FILE *keyboard = NULL, *mouse = NULL, *touch = NULL, *display  = NULL;
	int led, footer, header;

	//Hide all diplayed elements
	led = DisplayLeds(_OFF_);
	footer = DisplayFooter(_OFF_);
	header = DisplayHeader(_OFF_);



	// Open display
	display = (FILE*)fopen("DISPLAY","w*");
	// Open keyboard
	keyboard = fopen("KEYBOARD","r*");
	// Open mouse
	mouse = fopen("MOUSE","r*");
	// Open touch
	touch = fopen("TSCREEN","r*");


	// Start CGUI application
	CGUI_Static();

	// close touch
	if(touch) fclose(touch);
	// close mouse
	if(mouse) fclose(mouse);
	// close keyboard
	if(keyboard) fclose(keyboard);
	// close display
	if(display) fclose(display);

	// Restore display context
	DisplayLeds(led);
	DisplayFooter(footer);
	DisplayHeader(header);

	return FCT_OK;
}

