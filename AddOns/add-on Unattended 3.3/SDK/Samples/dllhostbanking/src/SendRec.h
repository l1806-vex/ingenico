#define SEND_MSG_ACK 		0xF100
#define SEND_MSG_NACK 		0xF200
#define SEND_MSG_STATUS 	0xF300

extern int iSENDREC_Send_buf(FILE *fd_p, unsigned long lEvent_p,
		unsigned char *pucBuf_p, unsigned int iNb_p);

extern int iSENDREC_Rec_buf(FILE *fd_p, unsigned long lEvent_p,
		unsigned char *pucBuf_p, unsigned int *piNb_p, unsigned int time_out_global);

extern int iSENDREC_Init( T_UCM_DEVICE *psDevice_p );

extern int iSENDREC_UCMC_Give_Status( T_UCMHOST_STATUS_UCM *pNewStatus_p ) ;

extern int iSENDREC_Msg_Creation( unsigned short usType_p , void *pvData_p, int iLgData_p );
extern int iSENDREC_Msg_Display_Creation( unsigned short usType_p , unsigned char *pvData_p, int iLgData_p );
extern int iSENDREC_Msg_Modem_Creation( unsigned short usType_p , unsigned char *pvData_p, int iLgData_p );
extern int iSENDREC_Msg_Printer_Creation( unsigned short usType_p , unsigned char *pvData_p, int iLgData_p );

extern int iSENDREC_UCMC_Send_Msg( T_UCMHOST *p );

extern int iSENDREC_UCMC_Read_Msg( T_UCMHOST *p );

extern int iSENDREC_InitCom( void );

extern int iSENDREC_CloseCom( void );

extern int iSENDREC_Is_Open( unsigned char );

extern int iSENDREC_FIFO_HOST_Is_Msg_To_Send_Waiting( void );

extern int iSENDREC_FIFO_HOST_Set_Msg_Sent( void );

extern int iSENDREC_FIFO_HOST_Task_Send_Msg( void );

extern int iSENDREC_FIFO_HOST_Msg_Is_Creation( void );

extern unsigned short usSENDREC_Task_Is_Msg_From_HOST( unsigned char *pucData_p  );

extern int iSENDREC_Msg_Creation_Key_Txt( char cKey, void *pvData_p );

extern int iSENDREC_UCMC_Get_DLL_Status( T_UCMHOST_MPA_STATUS *psPar1_p ) ;


