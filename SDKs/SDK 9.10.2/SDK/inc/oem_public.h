#ifdef __cplusplus
extern "C" {
#endif

#ifndef __OEM_PUBLIC_H_INCLUDED__
#define __OEM_PUBLIC_H_INCLUDED__

/*! @addtogroup KSFAM_FIC
	* @{
 */ 
 
/*! @brief Define the structure of a buffer. */
typedef struct {
      unsigned char *addr;							/*!< address of the buffer */
      unsigned char *readptr;						/*!< pointer to address of next character to read */
      unsigned char *writeptr;					/*!< pointer to address of next character to write */
      unsigned short int   size;				/*!< size of the buffer in max different elements */
} Buffer;

/*! @brief Define the structure of a file. */
typedef struct {
      unsigned char    _descr;					/*!<  number of channel, neccessary for _INCHRW */
      Buffer _send;											/*!< buffer for sending */
	  	Buffer _rec;											/*!< buffer for receiving */
      unsigned short int   _task;				/*!< owner of the channel (0xFFFF = unused) */
      unsigned short int   _event;			/*!< event to occur when waiting for in- or output */
      unsigned short int 	 _error;			/*!< indicates the error (if one has occurred) */
      char  _unget_char;								/*!< character which has been 'unget' */
      unsigned char _state;							/*!< state of the channel */
      unsigned char _mode;							/*!< mode of the channel (read,write,reset,..) */
      unsigned char _masque;						/*!< mask of the state wich lead to events */
      unsigned char _raison;						/*!< event goal */
      unsigned char _autsend;						/*!< authorization of sending */
      unsigned char _autreceive;				/*!< authorization of  reception */
      void *PtData;											/*!< pointer to the data. */
}FILE;

/*! @}  */ 

#include "oem_public_def.h"
#ifdef __FRAMEWORK_TELIUM_2__
#include "oem_public_deprecated.h"
#endif
#include "uiram.h"


/*! @addtogroup KSFAM_FIC
	* @{
 */ 
 
/*
==================
	oem_open.c
==================
*/

/*! @brief fopen opens a file with a file_name and associates a buffer to this file.
 * @param *file_name : name of file .
 * @param *type : type of opening.
 * @return
 * - pointer to FILE structure.
 * - null pointer if the function has not been correctly executed.
 * @note 
 *  The peripheral files must be opened in all cases to drive a peripheral.
 *
 *  The standard peripheral files are : KEYBOARD, DISPLAY, PRINTER, SWIPE2, SWIPE3, SWIPE31,
		CAM0, CAM1, COM0, COM1, COM5,  COM6,  COm20, COM_KEYSPAN, COM_SL, COM_SL1, MODEM, SAM1, SAM2, SAM3, SAM4, IAPP, POWER,
                     DGPRS, MOUSE, KEYBUSB, TSCREEN, SWIPE31, SWIPE2, SWIPE3, RETRO_ECLAIRAGE, USB_MASS_STORAGE	.
 *
 *  These files are created by the software on initialisation if the peripherals are present.
		For other peripherals have a look to other documentation.
 *
 *  The following opening types are available :
 * - The '-' option is used to wait for a peripheral to be released (non-ANSI). In this case,
		the function waits for release of the peripheral by another task before turning over control
		to the calling task (indispensable for the printer).
 * - The '*' option is used to obtain a report complying with C ANSI requirements. This opening
		option is used to select the processing when a problem occurs (peripheral already open,
		port non-existent) ; by default, when a problem occurs, it generates a RESET and stores a
		diagnostic information. If the '*' option is positioned, the fopen will comply with the C ANSI
		return as well as the other functions (fclose, etc.).
 * - The 'a' option is used to avoid resetting the context when opening a peripheral. This function
		is implemented for the DISPLAY, for example.
 * - The standard options accepted are 'r' and 'w' for read and write.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
FILE *fopen(const char *file_name, const char *type);


/*! @brief fclose closes a file which has been opened by fopen.
 * @param *stream : pointer to file structure.
 * @return
 * - Return 0 if OK.
 * - EOF if problem is detected.
 *
 * @note
 * - Writing in the file takes place immediately.
 * - A peripheral which is closed during a dialogue will reset the dialogue
		 buffers and wait for a stable peripheral status before turning over control.
 * - Fclose on the modem peripheral is only permitted provided the line is cut
		 off, otherwise the terminal will generate a diagnostic indication and perform a reset.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
int fclose(FILE *stream);

/*! @}  */ 


 /*! @brief putchar sends a character to display.
 * @param c : value of character.
 * @return
 * - the character sent if OK.
 * - EOF if problem is detected.
 *
 * @note stream file is standard output file (display).
		Writing in the display immediately triggers start up of the peripheral without waiting for a start
		character. If the dialogue buffer is full, the routine waits for a free space before turning over control to the application.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
int putchar(int c);

/*! @brief fowner modifies the task in the file descriptor. 
 *
 * This function is used to modify the task number for a given peripheral.
 * @param *device_name : peripheral where stream task number is to be modified.
 * @param notask : number of the task.
 * @return
 * - FILE * : the stream if OK.
 * - NULL if the change is unsuccessful.
 * @note The peripheral must be open.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
FILE *fowner(const char *device_name,unsigned short notask);

/*! @}  */ 


/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

/*! @brief mask_event modifies conditions generating an event. 
 *
 * This function is used to modify the conditions by which an event, for a given peripheral, is obtained.
 * @param stream : peripheral where event mask is to be modified.
 * @param mask : value of mask
 * @return None
 * @note The values of the conditions for obtaining a peripheral event are given in Appendix B.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
int mask_event(FILE *stream,unsigned char mask);


/*! @brief ChngEventFile modifies generating event for a specified peripheral. 
 *
 * This function is used to modify the event raised by the given peripheral to wake-up application task.
 * @param stream : peripheral to modify.
 * @param evt_nbr : event number to use (from 0 to 31)
 * @return :OK ou EOF
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
int ChngEventFile(FILE* stream, unsigned short evt_nbr);



/*! @brief mask_event_read reads conditions generating an event. 
 *
 * This function is used to read the conditions by which an event, for a given peripheral, is obtained.
 * @param fd : peripheral where event mask is to be modified.
 * @param mask : value of mask.
 * @return None
 * @note The values of the conditions for obtaining a peripheral event are given in Appendix B.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
int mask_event_read(FILE *fd,unsigned char *mask);



/*! @brief status tests status of a peripheral. 
 *
 * This function is used to poll the peripheral.
 * @param fd : file address
 * @param ad_status : binary OR (|) of OEMC status bits for the specified peripheral
 * @return None
 * @note Given below are the status information items per peripheral :
 * - KEYBOARD : Keyboard FIFO not empty
 * - PRINTER : End of printing, Printing error, Printing buffer empty paper Out detection in bit 0.
 * - SWIPE2 / SWIPE31 : Track read
 * - CAM0 : 0 - No card inserted.
 *          1 - Card inserted (CAM_PRESENT).
 *          8 - Card removed (CAM_ARRACHEE).
 *          9 - Card inserted after a removal (CAM_PRESENT | CAM_ARRACHEE).
 * - CAM1 : Same as CAM0.
 * - CAM2 : Same as CAM0.
 * - COM0 : Transmission FIFO empty, reception FIFO not empty, end of transmission .
 * - COM1 : Transmission FIFO empty, reception FIFO not empty, end of transmission .
 * - MODEM : Transmission FIFO empty, reception FIFO not empty, end of transmission, Loss of carrier .
 * - MOUSE : tests presence of mouse.
 * - KEYBUSB : tests presence of USB keyboard.
 * - MASS STORAGE : tests the presence of USB mass storage.
 * - COM5 : tests the presence of a USB host.
 *
 * @link OEMC_STATUS_BITS Possible values returned by status @endlink
 *
 * Be careful not to confuse the flows associated to the stream file and the
   peripheral information bits (the modem defined below is the flow
   whereas MODEM is the bit associated to the peripheral for ttestall).
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
void status(FILE* fd, unsigned char* ad_status);

/*! @brief send_receive programs of a port for send/receive. 
 *
 * This function is used to selectively enable the 2 ways directions COMx or MODEM channels for send or receive.
 * @param stream : file address.
 * @param send : boolean for enabling/disabling send.
 * @param receive : boolean for enabling/disabling receive.
 * @return
 * - 0 if function has been correctly executed.
 * - -1 if COMx or MODEM file was not open.
 * @note send and receive can take values ON or OFF.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
int send_receive (FILE *stream, char send, char receive);

/*
==================
	Liaison serie
==================
*/


/*! @brief fbreak generates a break on communication port.
 *
 * Sends a logical 0 on TX signal for a duration of time.
 * @param stream : pointer to FILE.
 * @param time : time of break in miliseconds.
 * @return 0
 * @note send and receive can take values ON or OFF.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
int fbreak(FILE *stream, unsigned short time);

/*! @}  */ 


/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

/*! @brief reset_buf resets a peripheral file. 
 *
 * This function resets a peripheral buffer.
 * @param stream : peripheral where buffer is to be reset.
 * @param id_buffer : buffer identification. id_buffer can take following values :
 * - _send_id : transmission buffer
 * - _receive_id : reception buffer
 *
 * @return None
 * @note It also clears the reception related events (see APPENDIX B)
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
int reset_buf(FILE *stream,int id_buffer);

/*! @}  */ 


/*! @addtogroup KSFAM_FIC
	* @{
 */ 

/*! @brief __STDIN returns the FILE handle of standard input (keyboard, generally).
 * @return
 * - 0 if standard input is not open (keyboard generally).
 * - FILE * otherwise.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
FILE *__STDIN(void);


/*! @brief __STDOUT returns the FILE handle of standard output (screen generally).
 * @return
 * - 0 if the screen is not open.
 * - FILE * otherwise.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
FILE *__STDOUT(void);


/*! @brief stdprt returns the FILE structure of the printer.
 * @return
 * - 0 if the printer is not open.
 * - FILE * otherwise.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
FILE *__stdprt(void);


#define stdin()    __STDIN()			/*!< Gets OEMC FILE standard input */
#define stdout()   __STDOUT()			/*!< Gets OEMC FILE standard output */

/*! @}  */ 


/*! @addtogroup KSFAM_FIC
	* @{
 */ 

#define getchar()  getc(__STDIN())


/*! @brief stdperif gets the address of the Stream and Copy the file in an application area.
 *
 * This function is used to read the FILE of a given peripheral and get the address of the stream.
 * @param *name : name of the peripheral.
 * @param *fd : destination of the structure FILE.
 * @return
 * - the address FILE of the peripheral if OK.
 * - NULL if unsuccessful.
 *
 * @note The peripheral must be open.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
FILE *stdperif(const char *name, FILE *fd);


/*! @brief CopyFile copies the file in an application area.
 *
 * This function is used to read the FILE of a given peripheral.
 * @param *Hdl: source of the stream FILE.
 * @param *fd: destination of the stream FILE.
 * @return
 * - EOF if unsuccessful.
 * - 0 if succesful.
 *
 * @note The peripheral must be open.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
int CopyFile(FILE* Hdl, FILE *fd);


/*! @brief fioctl calls low level OEMC driver control function.
 *
 * @param cmd: Function code to be executed by OEMC device driver.
 * @param *data: command parameter(s).
 * @param *fd: target stream FILE.
 * @return
 * - 0 if succesful.
 * - other if unsuccessful.
 *
 * @note The peripheral must be open.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
int fioctl(int cmd, const void *data, FILE *fd);


/*! @brief fputc writes a character in specified file opened by fopen.
 * @param  c : value of character.
 * @param fd : pointer to FILE structure.
 * @return
 * - Returns the character sent if OK.
 * - EOF if problem detected.
 *
 * @note Writing in a file immediately triggers start up of the peripheral without waiting for
    the start character. If the dialogue buffer is full, the routine waits for a space in
    buffer to be released before returning control to the application.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
int fputc(int   c, FILE *fd);

/*! @}  */ 


/*! @addtogroup KSFAM_FIC
	* @{
 */ 

/*
==================
	reading.c
==================
*/

/*! @brief getc reads a character in a file.
 * @param stream : address of file where information will be read.
 * @return character read.
 * @note
 * This function only returns control provided a character has been read. The
   function blocks the current task while waiting for a character to be read. To
   avoid blocking the calling task, the status of the peripheral reception buffer
   must be tested before calling.
 *
 * In case of serial link, the function returns EOF when an end-of-file or a
   reception error has been detected. The ferror routine must be used to
   determine the type of error.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
int getc(FILE *stream);



/*! @brief fgets reads a string from a file.
 * @param s : address of character string read.
 * @param n : maximum number of characters to be read
 * @param stream : file address where information will be read,
 * @return
 * - s : address of string s if OK,
 * - null pointer otherwise.
 *
 * @note This function only returns control provided an end of string condition is
   detected (i.e /n or /0 or EOF ) .
 *
 * @b Caution : There is no time out supervision ; there is a potential risk of
   blocking the calling task if the end of string condition is not detected.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
char* fgets(char *s,int n,FILE *stream);



/*! @brief fread : copies, starting from address indicated by ptr, a number of data
    items , (nitems) having indicated size in file buffer.
 * @param ptr : pointer used to read into a file
 * @param size : size of item handled.
 * @param nitems : number of items handled.
 * @param stream : address of FILE.
 * @return
 * - number of items read in file buffer if Ok
 * - 0 if nothing has occurred.
 *
 * @note
 * The fread function used for a serial link (MODEM, COM0, COM1) must be used with a size=1 (char)
 * In this case, fread does not return the number of characters requested when a reception error is detected. 
 *
 * The user must therefore request the ferror() function to determine the cause of the reception error.
 *
 * If the reception buffer is empty (see status function), there is no error.
 *
 * If ferror is not called, the next call to fread will automatically clear the error and read the following characters.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
Telium_size_t fread(void *ptr, Telium_size_t size, Telium_size_t nitems,FILE *stream);



/*! @brief ungetc recovers last character from a file.
 * @param c : position of the character in file.
 * @param stream : address of file.
 * @return EOF if character could not be inserted.
 * @note character inserted can be recovered by next getc.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
int ungetc(int c,FILE *stream);


/*! @brief getchar reads a character from standard input.
 * @return character read.
 * @note
 * This function only returns control provided a character has been read. The
   function blocks the current task while waiting for a character to be read. To
   avoid blocking the calling task, the status of the standard input peripheral 
   must be tested before calling.
 *
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
#define getchar() getc(__STDIN())


/*
==================
	writing.c
==================
*/


/*! @brief putc writes a character in a file opened by fopen.
 * @param c : value of character
 * @param stream : pointer to FILE structure
 * @return
 * - 0 if OK.
 * - EOF if problem is detected.
 *
 * @note Writing in a file immediately triggers start up of the peripheral without
	  waiting for a start character. If the dialogue buffer is full, the routine waits
	  for a free space in buffer before returning control to the application.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
int putc(int c, FILE *stream);


/*! @brief puts sends a character string to display.
 * @param s: formated string to be transmitted to output. Formated character string is addressed to standard output (display).
 * @return: Upon successful completion, fputs() returns a non-negative number. Otherwise, it returns EOF
 * @note Writing in a file immediately triggers initiation of the peripheral without waiting for a start character.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
int puts(const char *s);



/*! @brief fputs sends a character string to a file.
 * @param s : formatted string to be transmitted to output.
 * @param stream : pointer to specified FILE.
 * @return: Upon successful completion, fputs() returns a non-negative number. Otherwise, it returns EOF
 * @note Writing in a file immediately triggers initiation of the peripheral without
   waiting for a start character (except for printer).
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
int fputs(const char *s, FILE *stream);



/*! @brief fwrite : recovers, starting from address indicated by ptr, a number of data
    items (nitems) with indicated size in stream file buffer.
 * @param ptr : pointer used to write into a file
 * @param size : size of item handled.
 * @param nitems : number of items handled.
 * @param stream : address of FILE.
 * @return
 * - number of items written in file buffer if Ok.
 * - EOF (-1) if an error has occurred (FILE not oppened in write mode) .
 *
 * @note Writing in a file immediately initiates start up of the peripheral without waiting for a start character.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
Telium_size_t fwrite(const void * ptr, Telium_size_t size, Telium_size_t nitems, FILE *stream);


/*
==================
	print.c
==================
*/


/*! @brief fprintf writes in file opened by fopen.
 * @param stream : pointer to FILE structure.
 * @param format : string to be formatted.
 * @return
 * - number of characters formatted if OK.
 * - (-1) if problem detected.
 *
 * @note <ul><li> Writing in a file immediately triggers initiation of the peripheral without
   waiting for a start character.</li>
 		 <li>If the peripheral is PRINTER, refer to \ref pprintf to get the ESC sequences.</li>
 		 </ul>

 *
 * @b Caution: the maximum size of the string to be formatted must not exceed 256 bytes for a "COM" devices and 128 bytes for "PRINTER"
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
int fprintf(FILE *stream, const char *format,...);


/*! @brief vprintf formats an output (argc argv) (cf doc ansi C)
 * @param argc : Number of arguments
 * @param argv : array of arguments
 * @return cf doc ansi C
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
int _vprintf(const char * argc, va_list argv );


/*
==================
	error.c
==================
*/


/*! @brief ferror returns error status linked to last file read operations.
 * @param stream : address of file.
 * @return
 * - EOF if access to file is unsuccessful (file not opened, file opened in write mode only, ...).
 * - file read status otherwise.
 *
 * @note Status of ferror function :
 *   OVERRUN_BUFFER 0xFF		  : OEMC buffer overrun 
 *   OVERRUN_ERROR  0x2000		: USART overrun error 
 *   FRAMING_ERROR  0x4000		: USART framing error 
 *   PARITY_ERROR   0x8000		: USART parity error
 * - 0 if no error present.
 *
 * bit mask should be used if ferror returns neither 0 nor 0xFF :
 *  if(ferror & FRAMING_ERROR  ) {  ==> framming error }
 *  if(ferror & OVERRUN_ERROR ) {  ==>overrun error }
 *  if(ferror & PARITY_ERROR) {  ==> parity error }
 *  other bits are not error flags
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
int ferror( FILE *stream);



/*! @brief clearerr clears file error indicator.
 * @param stream : file address.
 * @return None
 * @note After clearing the error on the character which should have been read, the
   character can be read by a function such as fgetc or fread.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
void clearerr(FILE *stream);

/*! @}  */ 


/*! @addtogroup KSFAM_IOSF
	* @{
 */ 


/*! @brief mask_event modifies conditions generating an event. 
 *
 * This function is used to modify the conditions by which an event, for a given peripheral, is obtained.
 * @param stream : peripheral where event mask is to be modified.
 * @param mask : value of mask
 * @return None
 * @note The values of the conditions for obtaining a peripheral event are given in Appendix B.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
int mask_event(FILE *stream,unsigned char mask);


/*! @brief ChngEventFile modifies generating event for a specified peripheral. 
 *
 * This function is used to modify the event raised by the given peripheral to wake-up application task.
 * @param stream : peripheral to modify.
 * @param evt_nbr : event number to use (from 0 to 31)
 * @return :OK ou EOF
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
int ChngEventFile(FILE* stream, unsigned short evt_nbr);



/*! @brief mask_event_read reads conditions generating an event. 
 *
 * This function is used to read the conditions by which an event, for a given peripheral, is obtained.
 * @param fd : peripheral where event mask is to be modified.
 * @param mask : value of mask.
 * @return None
 * @note The values of the conditions for obtaining a peripheral event are given in Appendix B.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
int mask_event_read(FILE *fd,unsigned char *mask);



/*! @brief status tests status of a peripheral. 
 *
 * This function is used to poll the peripheral.
 * @param fd : file address
 * @param ad_status : binary OR (|) of OEMC status bits for the specified peripheral
 * @return None
 * @note Given below are the status information items per peripheral :
 * - KEYBOARD : Keyboard FIFO not empty
 * - PRINTER : End of printing, Printing error, Printing buffer empty paper Out detection in bit 0.
 * - SWIPE2 / SWIPE31 : Track read
 * - CAM0 : 0 - No card inserted.
 *          1 - Card inserted (CAM_PRESENT).
 *          8 - Card removed (CAM_ARRACHEE).
 *          9 - Card inserted after a removal (CAM_PRESENT | CAM_ARRACHEE).
 * - CAM1 : Same as CAM0.
 * - CAM2 : Same as CAM0.
 * - COM0 : Transmission FIFO empty, reception FIFO not empty, end of transmission .
 * - COM1 : Transmission FIFO empty, reception FIFO not empty, end of transmission .
 * - MODEM : Transmission FIFO empty, reception FIFO not empty, end of transmission, Loss of carrier .
 * - MOUSE : tests presence of mouse.
 * - KEYBUSB : tests presence of USB keyboard.
 * - MASS STORAGE : tests the presence of USB mass storage.
 * - COM5 : tests the presence of a USB host.
 *
 * @link OEMC_STATUS_BITS Possible values returned by status @endlink
 *
 * Be careful not to confuse the flows associated to the stream file and the
   peripheral information bits (the modem defined below is the flow
   whereas MODEM is the bit associated to the peripheral for ttestall).
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
void status(FILE* fd, unsigned char* ad_status);

/*! @brief format programs a serial port COM0/COM1.This function is used to format a serial link.
 * @param peripheral_name : COM0, COM1, COM2.
 * @param arglist : List of arguments :
 * - arglist[0]        : baud_rate = 300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200 bps.
 * - arglist[1]        : 7 or 8 bits.
 * - arglist[2]        : 1 or 2 stop bits.
 * - arglist[3]       :
 *	- PARITY, parity tested.
 *	- NO_PARITY, parity not tested.
 * - arglist[4] :
 *	- EVEN parity.
 *	- ODD parity.
 * - arglist[5] : flow control ( only on COM0 )
 *	- 00 No flow control
 *	- 01 flow control via RTS/CTS management
 *
 * @return
 * - 0 if function has been correctly executed
 * - -1 if COMx file was not open.
 *
 * @note
 * The parity parameter indicates that the character parity has been tested. The evenodd parameter
 * indicates whether the parity is EVEN or ODD. This function can be accessed even if the peripheral
 * is not open. The format is preserved up to the next time the serial port is programmed.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
int FormatOem(const char *peripheral_name, va_list arglist);

/*! @}  */ 


/*! @addtogroup KSFAM_OS_TASK
	* @{
 */ 



/*! @brief This function is used to create and start a user task
 * @param Startaddress : address of the entry point of the task
 * @param dummy1 : kept for for EFT10/20 compatibility purpose (USP is OS handled)
 * @param prior : This parameter allows to choose the priority level of the created task. 
 *  Priority level goes from -32 to +32. -32 corresponds to the highest priority level.
 * @return the task handle
 * @sa 
 *	- @link t_topstack topstack structure@endlink
 *
 * @b Include: to be defined in your application
 *
 * @b Compatibility: Non-ANSI
 *
 * @note  exit ( EXIT_MAX_TASK_NUMBER ) if no more task available (up to 20 tasks can be defined including task 1 )
 * - It must be called prior to any kernel routines
 * - stacks are located in O/S, user stack by 2Kb incremented up to 64Kb
 * - fork creates and starts the task
 * - Use CurrentTask to get the task number at task level
 *
 * @link KSFAM_OS_TASK Back to top @endlink
 */ 
t_topstack *fork (word(*Startaddress) (),byte* dummy1, int prior );
                          
                          

/*! @brief task stopping and killing, fork must be called prior to kill routine. 
 *
 * It replaces StopTask / Terminate kernel routines.
 *
 * It is recommended to signal the task by sending an event before killing it.
 * @param TaskHdl1 : t_topstack pointer returned by fork routine when creating task
 * @param options  : see below.
 * - ""   reset if the task is using peripheral, a diagnostic is recorded EXIT_LINKED_TO_PERIPH in that case
 * - "-*" wait for peripheral closing by the task
 *
 * @return None
 *
 * @b Include: to be defined in your application
 *
 * @b Compatibility: Non-ANSI
 *
 *  @par Example:

 * @include oem_public_Sample_03.c
 *
 * @link KSFAM_OS_TASK Back to top @endlink
 */ 
int kill ( t_topstack *TaskHdl1, char *options);



/*! @brief GiveNoTask converts one pointer to type t_topstack to an OEMC task number.
 * @param topstack : pointer on t_topstack structure. This pointer is returned by fork routine when creating task.
 * @return OEMC task number.
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
extern word        GiveNoTask (t_topstack *topstack);


//tms
//typedef struct {
//    char bidon;
//} S_PARAM_TLCHGT ;

/*! @}  */ 


/*! @brief SysCmd send command to Booster.
 * @param Cmd : Command identifier.
 * @param spydata : data.
 * @param diagnostic : data.
 * @return None.
 *
 * @link KSFAM_DIAG Back to top @endlink
 */ 
int SysCmd(unsigned char Cmd, spy_data_t * spydata , char * diagnostic);

/*! @addtogroup KSFAM_FIC
	* @{
 */ 
 
/*! @brief pprintf formats an output to printer with flow control
 * @param format : String to be formatted. The character string to be formatted is addressed to the printer.
 * @return
 * - number of characters formatted if OK.
 * - -1 if problem is detected.
 *
 * @note <ul>
 *		<li>Standard printing mode: single-width, black on white background, 4-microline as interlining space,7*5 dots matrice printing.</li>
 *		<li>Printing modes:
 *			<ul>
 *				<li>Single and double-width printing (12 or 24 characters/line).</li>			
 *				<li>Printing in white on black background or black on white background.</li>
 				<li>Condensed mode printing:
 *				<ul>
 *					<li>character width reduced by 2 (24 or 48 characters/line)</li>
 * 					<li>interline modification</li>
 *				</ul>
 *				<li>Printing in bold font. The bold font printing mode is not compatible with the condensed mode</li>
 *			</ul>
 *		</li>
 *		<li>Fast paper feed by line feed increments</li>
 *		<li>Definition/editing of printable characters (\ref defprinterpatternHR).</li>
 *		<li>Formatting the margins via format routine (\ref format)<br>

 * @include oem_public_Sample_01.c
 * </li>
 *		<li>Font size changing via added ESC sequence</li>
 *		<li>Paper out detection via status routine</li>
 * </ul>
 *
 * @b Caution:<ul>
 * <li>Only the lines are printed. A line is terminated by "\n" or "\r".
 * <li>The maximum size of the string to be formatted must not exceed 128 bytes.</li>
 * <li>characters not forming part of the standard ASCII table (code exceeding 7F Hex) cannot be used directly in C language.</li>
 * 
 * </ul>
 * @b Commands
 * <table>
 * <tr><th></th><th>enable</th><th>disable</th></tr>
 * <tr><td>Return to the default mode (useful at the beginning and end of ticket to restore the default mode)</td><td>"\x1B""@"</td><td></td></tr>
 * <tr><td>Printout in white with black background</td><td>"\x1B""B1"</td><td>"\x1B""B0"</td></tr>
 * <tr><td>Printout in black with white background</td><td>"\x1B""B0"</td><td>"\x1B""B1"</td></tr>
 * <tr><td>User character printing (\ref defprinterpatternHR)</td><td>"\x1B""U"</td><td>"\x1B""V"</td></tr>
 * <tr><td>Modification of interlining space</td><td>"\x1B""A"\em n<br>with n(in hex) the number of dots for the line </td><td>"\x1B""@"</td></tr>
 * <tr><td>Bold font print</td><td>"\x1B""E"</td><td>"\x1B""F" or "\x1B""@"</td></tr>
 * <tr><td>Normal print mode</td><td>"\x1B""F"</td><td></td></tr>
 * <tr><td>Double height</td><td>"\x1B""H"</td><td>"\x1B""@" , "\r" or "\n"</td></tr>
 * <tr><td>Double width</td><td>"\xE"</td><td>"\x12" , "\r" or "\n"</td></tr>
 * <tr><td>Condensed mode</td><td>"\xF"</td><td>"\x12"</td></tr>
 * <tr><td>Normal mode</td><td>"\x12"</td><td></td></tr>
 * <tr><td>End of ticket (add some carriage returns to exit the ticket according to the terminal type) </td><td>"\xC"</td><td></td></tr>
 * </table>
 *
 * @b Example

 * @include oem_public_Sample_02.c
 * 
 * @link KSFAM_FIC Back to top @endlink
 */ 
int pprintf(const char * format, ...);

/*! @brief printf formats an output to display on screen.
 * @param format : string to be formatted. The character string to be formatted is addressed to the standard output (display).
 * @return
 * Upon successful completion, the printf() functions return the number of bytes transmitted  
 * If an output error was encountered, these functions return a negative value. 
 *
 * @note 
 * <ul><li>Writing in a file immediately triggers start up of the peripheral without
 *  waiting for a start character.</li>
 *  <li>"\x1b" clears the display</li></ul>
 *
 * @b Caution : the maximum size of the string to be formatted must not exceed 256 bytes.
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
int printf(const char * format, ...);

/*! @}  */ 


/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

/*! @brief On mobile terminal only : shutdown() turn terminal in standby mode
 * Terminal can pe powered down using :
 *   FILE *pwr; 
 *   pwr = fopen("POWER","r");
 *   r=fioctl(PWR_FIOCTL_ENTER_PWRDWN,NULL,pwr); 
 * @return None.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
void shutdown (void);

/*! @}  */ 


/*! @addtogroup KSFAM_CAL
	* @{
 */ 

#define Wrong_Date (unsigned char)1

/*! @brief This function is used to check the date by verifying the coherency of the parameterized date.
 * @param date : pointer to structure DATE.
 * @return
 * - 0 if function has been correctly executed
 * - 1 if date is incoherent.
 *
 * @link KSFAM_CAL Back to top @endlink
 */ 
int  ctrl_date     (DATE *date);

/*! @}  */ 


/*! @addtogroup KSFAM_AUTRES
	* @{
 */ 

/*
==================
		oem.c
==================
*/

/*! @brief OEM_exit performs a startup of the Terminal. 
 *
 *  This routine records a startup diagnostic.
 *
 *  The diagnostic code is given by the parameter code.
 * @param code : diagnostic code. Diagnostic codes are described in file defdiag_TSys.h.
 * @return None
 *
 * @link KSFAM_AUTRES Back to top @endlink
 */ 
void	OEM_exit(int code);


/*! @brief Tests if battery is present
 * @return 0 if no battery is present.
 *
 * @link KSFAM_AUTRES Back to top @endlink
 */ 
extern int  isbattery (void);



/*! @brief powered checks if the terminal need to be powered for communication layout.
 *
 * If the caller is linked to DLL CB2A (French communication layout), the return depends on the network access parameter :
 * - GPRS and GSM, return always TRUE.
 * - Bluetooth terminal, return always TRUE.
 * - WiFi terminal, return TRUE if terminal is powered;
    if not, return TRUE only if network access parameter does not need to be powered
    (IP/Eth for instance), FALSE instead.
 * - Other value, return TRUE if terminal is powered, FALSE instead.
 *
 * If the caller is not linked to DLL CB2A (French communication layout), return TRUE if terminal is powered, FALSE instead
 * @return see above
 *
 * @link KSFAM_AUTRES Back to top @endlink
 */ 
extern int  powered (void);

/*
==================
	oem_cal.c
==================
*/


/*! @brief get_tick_counter returns the tick counter. one tick = 10 ms.
 * @return Number of elapsed ticks since startup.
 *
 * @link KSFAM_AUTRES Back to top @endlink
 */ 
unsigned long int get_tick_counter (void);

/*! @}  */ 


/*! @addtogroup KSFAM_OS
	* @{
 */ 

/*! @brief ttestall is used to place the calling task in a standby status for reactivation on an event.
 *
 *  When an event arrives on a peripheral, the function reads the status of the concerned peripheral
	  and acknowledges the event (reset) if the event was produced by a completed action (transmission
	  buffer empty or end-of-transmission).
 * @param events : expected-peripherals in the form of a 32-bit long word :
	  CAM0, CAM1, SWIPE2, SWIPE31, COM0, COM1, MODEM, IAPP,
		KEYBOARD, PRINTER, PINPAD . Or00 if no peripheral is expected (case of pause).
 * @param TimeOut : operates in units of 10 milliseconds. To set an infinite timeout value TimeOut = 0.
 * @return Expected peripherals positioned in the form of a 32-bit long word mask or 00 for time-out.
 * - BIT 0 : KEYBOARD
 * - BIT 1 : PRINTER
 * - BIT 2 : COM0
 * - BIT 3 : COM1
 * - BIT 4 : MODEM
 * - BIT 5 : CAM0
 * - BIT 6 : CAM1
 * - BIT 7 : SWIPE2
 * - BIT 8 : IAPP
 * - BIT 9 : SWIPE31
 * - BIT 10 : COM5
 * - BIT 11 : COM6
 * - BIT 12 : Manager event. This bit cannot be used by applications
 * - BIT 15 : available for  application
 * - BIT 16 : PPR KEYBOARD 
 * - BIT 17 : IAPP PPR
 * - BIT 18 : CAM2, CAM9, COM11
 * - BIT 19 : COM2
 * - BIT 20 : MOUSE, CLESS
 * - BIT 21 : KEYBOARD USB
 * - BIT 22 : SWIPE3
 * - BIT 23 : DRV_GPRS
 * - BIT 24 : DRV_UMS
 * - BIT 25 : DBLUETOOTH
 * - BIT 26 : COM3 and USB serial drivers (COM20, COM21, COM_KEYSPAN, COM_SL, ...)
 * - BIT 27 : TSCREEN
 * - BIT 31 : available for  application
 *
 * @link OEMC_PER_BITS Events associated to OEMC FILE @endlink
 *
 * @note
 *
 *  Events not linked to peripherals are systematically cleared by ttestall.
 *
 *  Application must handle all of the events positioned as a ttestall return.
 *
 *  Non peripherals events can be used by the user by means of event positioning primitives : see [3].
 *
 *  Caution :
 * - if both parameters are 0, the calling task will be blocked forever,
 * - this function does not clear end-of-reception events ; it is
		 necessary to read the entire buffer or call the reset_buf function,
 * - before calling ttestall, it is necessary to select the events expected by the mask_event function.
 * - The following instruction to get a peripheral event is now forbidden ttestall ( 1<<fd->event , .. )
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
unsigned int ttestall(unsigned int events,unsigned int TimeOut);

/*! @brief This function replaces a standard character with a special character. 
 *
 * Up to 128 characters can be redefined.
 * @param key : ASCII value of key parameter
 * @param *pattern : Definition of character, pattern .
 * @return
 * - 0 if function has been correctly executed.
 * - -1 if more characters are available.
 *
 * @note
 * - same routine as defprinterpattern
 * - allows to have common font between display and printer
 * - the key value will vary between 20 Hex and FF hex.
 * - Character code :
 * - 1 byte specifies the number of blank columns prior to the first column of dots
 * - 1 byte specifies the number of useful columns containing at least one dot
 * - x bytes : dot matrix represented for vertical with 8 dots defined, i.e. 1 byte per column as below :
 * - b0 highest line
 * - b1
 * - b2
 * - b3
 * - b4
 * - b5
 * - b6 lowest line
 * - b7 line under character
 * - 1 byte specifies if the character involves more than 1 'line' ( 8 dots ) is
 *
 * FF : all other value signifies last line.
 * - 1 byte specifies the number of blank columns after the last columns of dots.
 * - This sequence has to be repeated as long as lines have to be defined.
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
int  defdisplaypattern (char key,char *pattern);

/*! @}  */ 


/*! @addtogroup KSFAM_PPS
	* @{
 */ 

/*! @brief Define a bitmap to display
 * @param Fp : pointer on oemc file.
 * @param key : Hexadecimal value of byte to replace
 * @param pattern : Bitmap
 * @return
 * - OK (0)
 * - or -1.
 *
 * @link KSFAM_PPS Back to top @endlink
 */ 
int defdisplaypatterndsp (FILE *Fp, char key,char *pattern);

/*! @}  */


/*! @addtogroup KSFAM_CARD
	* @{
 */ 
 
/*! @brief This function is used to check and format the ISO1 stripe buffer.
 * @param stream : Address of SWIPE31 file. *stream, uses the same peripheral as ISO3 driver
   ( SWIPE31 peripheral event, file handle ).
 * @param length : char decoded count
 * @param swipe_read : data read on the swipe.
 *    ASCII-formatted card buffer ( 79 characters Max ) , swipe_read
 *		%.............^............ ? 'LRC' in ASCII
 *		% and ? characters are defined as ISO1 sentinels
 *		^ character is ISO1 separator
 *		( several ^ characters can be found on track 1 ).
 * @return : ISO 1 status
 * - ISO_OK if card is ISO 1 compatible
 * - DEF_SEP if separator fault detected
 * - DEF_PAR if parity fault detected
 * - DEF_LRC if LRC fault detected
 * - NO_DATA if no readable data detected
 *
 * @note The following checks are performed for the ISO1 stripe :
 * - check of sentinels presence (%, ?)
 * - length : stripe length must be less than or equal to 79 characters
 * - character parity
 * - LRC fault
 *
 *  ISO1 separator (^) is not checked.
 *
 *  The is_iso1 function must always be preceded by the fopen function on the swipe31 peripheral .
	  SWIPE31 event can occur at the same time as SWIPE2 event, this is very
	  important when application waits for both events and returns from ttestall
 *
 * Note:
 * If the read magnetic track contains non ISO character or has a non 
 * ISO format, you can recover raw track stream of bits by 
 * using fread(). To build your own algorithm to re-form data from 
 * magnetic tracks, you have to consider that stream of bits may differ 
 * according to terminal types and to read cards (= number of 
 * synchronisation bits may differ). 
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
int is_iso1(FILE *stream,unsigned char *length,unsigned char *swipe_read);


/*! @brief This function is used to check and format the ISO2 stripe buffer.
 * @param stream : pointer to FILE.
 * @param length : char decoded count
 * @param swipe_read  : data read on the swipe :
 *		ASCII-formatted card buffer ( 40 characters Max ) , BUFFER_PISTE.
 *		B.............D..............F 'LRC' in ASCII
 *
 * @return : ISO 2 status :
 * - ISO_OK if card is ISO
 * - DEF_SEP if separator fault detected
 * - DEF_PAR if parity fault detected
 * - DEF_LRC if LRC fault detected
 * - DEF_LUH if LUHN fault detected
 * - DEF_NUM if numerical fault detected
 * - NO_DATA if no readable data detected
 *
 * @note The following checks are performed for the ISO2 stripe :
 * - Check of separators (B,D,F) and length (stripe length less than or equal to
		 40 characters), character parity, stripe LRC, luhn code, numerical fault.
 * - The is_iso2 function must always be preceded by the fopen function on the swipe2 peripheral.
 *
 * Note:
 * If the read magnetic track contains non ISO character or has a non 
 * ISO format, you can recover raw track stream of bits by 
 * using fread(). To build your own algorithm to re-form data from 
 * magnetic tracks, you have to consider that stream of bits may differ 
 * according to terminal types and to read cards (= number of 
 * synchronisation bits may differ). 
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
int is_iso2(FILE *stream, LG_REF_CLI *length, BUFFER_PISTE swipe_read);


/*! @brief This function is used to check and format the ISO3 stripe buffer.
 * @param stream : pointer to FILE.
 * @param length : char decoded count
 * @param swipe_read  : data read on the swipe.
 * @return : ISO 3 status
 * - ISO_OK if card is ISO
 * - DEF_SEP if separator fault detected
 * - DEF_PAR if parity fault detected
 * - DEF_LRC if LRC fault detected
 * - DEF_NUM if numerical fault detected
 * - NO_DATA if no readable data detected
 *
 * @note The following checks are performed for the ISO3 stripe :
 * - Check of separators (B,F) and length (stripe length less than or equal to 107
		 characters), character parity, stripe LRC, numerical fault.
 * - The is_iso3 function must always be preceded by the fopen function on the swipe31 peripheral.
 * - SWIPE31 event can occur at the same time as SWIPE2 event, this is very
		 important when application waits for both events and returns from ttestall
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
int is_iso3(FILE *stream,unsigned char *length,unsigned char *swipe_read);

/*! @brief This routine executes an APDU command and handles the response according to EMV 3.1.1. 
 *
 * The protocol to be used is the one asked by the card at the reset time.
 * @param Fd_P : card flow address.
 * @param C_apdu : The APDU command.
 * @param R_apdu : The APDU response.
 * @return
 *<table><tr><th>Value</th><th>Description</th></tr>
 *<tr><td>\a 0</td><td>OK, no error.</td></tr>
 *<tr><td>\a 1</td><td>N.A.</td></tr>
 *<tr><td>\a 2</td><td>Invalid card because Answer To Reset is not EMV compliant.</td></tr>
 *<tr><td>\a 3</td><td>Card is mute.</td></tr>
 *<tr><td>\a 4</td><td>VCC or VPP problem.</td></tr>
 *<tr><td>\a 5</td><td>VCC or VPP problem.</td></tr>
 *<tr><td>\a 6</td><td>Communication problem (driver problem).</td></tr>
 *<tr><td>\a 7</td><td>Card removed.</td></tr>
 *<tr><td>\a 8</td><td>Unauthorized command as long as IUC is unsecured.</td></tr>   
 *</table>
 *  
 * @note
 * This routine is equivalent to send_receive_t1 () for T=1 protocol.
 *
 * In case of T=0 protocol, this routine executes automatically input and output commands according to EMV 3.1.1.
 *
 * If the chip card is EMV compliant, application does not need to know any more the card protocol.
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
extern unsigned char EMV_apdu(FILE *Fd_P, T_APDU *C_apdu, T_APDU *R_apdu);



/*! @brief This function is used to shutdown the card per standard ISO 7816-3.
 * @param Fd_P : pointer to Card flow.
 * @return
 * - 0 if function has been correctly executed.
 * - 1 if card has already been removed.
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
extern int power_down ( FILE *Fd_P );



/*! @brief This routine must be used instead of already existing power_down_gpm routine.
 * @param Fd_P : pointer to oemc file structure. CAM0 only.
 * @return Always returned 00.
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
extern int power_down_sync ( FILE *Fd_P );


/*! @brief InitGkDrv init of CAM IFD context to use T=1 after T=0 ATR (Moneo specific)
 * @param Fd_P : Card flow address.
 * @param  arglist :
 * - arglist[0] : Convention (0 : same than ATR - 1 : direct convention - 2 : inverse convention)
 * - arglist[1] : ATR TA3 byte (which defines IFSC)
 * - arglist[2] : ATR TB3 byte (which defines CWI and BWI)
 * - arglist[3] : ruf
 * - arglist[4] : ruf
 * @return None.
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
extern void InitGkDrv(FILE *Fd_P, va_list arglist);


/*! @brief Check the card according to EMV 3.1.1.
 * @param Fd_P : Card flow address.
 * @param pOctetsHisto_P : pointer to structure HISTORIC.
 * @return Read address for card history data generated by the reset pOctetsHisto_P. Return codes are unchanged :
 * - ok 0
 * - invalid card 2 Answer To Reset is not EMV compliant
 * - card is mute 3
 * - VCC or VPP problem 4/5
 * - communication problem 6
 * - card removed 7
 *
 * @note Accept T0 or T1 protocol. The card historical data may be :
 * - Manufacturer's identifier
 * - Mask number
 * - Lock word
 * - Status word 1
 * - Status word 2
 *
 * The history data are only recovered provided the function returns 0.
 *
 * The HISTORIC structure contains the length (up to 15 characters) and the history data.
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
extern unsigned char  EMV_power_on ( FILE *Fd_P , HISTORIC *pOctetsHisto_P );



/*! @brief Check the card according to ISO7816  
 * @param Fd_P : Card flow address.
 * @param pOctetsHisto_P : pointer to structure HISTORIC.
 * @return Read address for card history data generated by the reset pOctetsHisto_P. Return codes are unchanged :
 * - ok 0
 * - invalid card 2 Answer To Reset is not EMV compliant
 * - card is mute 3
 * - VCC or VPP problem 4/5
 * - communication problem 6
 * - card removed 7
 *
 * @note Accept T0 or T1 protocol. The card historical data may be :
 * - Manufacturer's identifier
 * - Mask number
 * - Lock word
 * - Status word 1
 * - Status word 2
 *
 * The history data are only recovered provided the function returns 0.
 *
 * The HISTORIC structure contains the length (up to 15 characters) and the history data.
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
extern int power_on ( FILE *Fd_P , HISTORIC *pOctetsHisto_P );



/*! @brief This function must be called when SLE4432/SLE4442 cards have to be powered- up.
 *
 * This routine must be used instead of already existing power_on_gpm routine.
 * @param Fd_P : CAM0 only.
 * @param PROTOCOL : protocole type.
 * @return
 * - 0 OK
 * - 5 VCC problem ( short circuit for example )
 * - 7 card removed
 *
 * @note This routine doesn't applied any voltage on VPP pin ( C6 contact ).
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
extern int power_on_sync ( FILE * Fd_P,int PROTOCOL  );



/*! @brief This function is used to execute an input command per standard ISO 7816-3. 
 *
 * The function returns control following execution.
 * @param stream : Card flow address.
 * @param cmd : Address of structure of input command.
 * @return
 * - 0 if function has been correctly executed
 * - 3 if card is silent
 * - 4 if VDC voltage fault detected
 * - 5 if VPP problem detected
 * - 6 if card communication fault detected
 * - 7 if card removed
 * - 8 if unauthorized command as long as IUC is unsecured
 * - 29Hex if card communication fault detected
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
extern int input_command(FILE * stream, COMMAND_CAM * cmd );



/*! @brief This function is used to execute an output command per standard ISO 7816-3.
 * @param stream : pointer to oemc file. Card flow address.
 * @param outputcommand : Address of output command structure.
 * @return
 * - 0 if function has been correctly executed
 * - 3 if card is silent
 * - 4 if VDC voltage fault detected
 * - 5 if VPP problem detected
 * - 6 if card communication fault detected
 * - 7 if card removed
 * - 8 if unauthorized command as long as IUC is unsecured
 * - 29Hex if card communication fault detected
 *
 * @note The header includes 5 bytes :
 * - application class
 * - instruction code
 * - P1 card parameter
 * - P2 card parameter
 * - length of data to read from the card from 0 to 248.
 * 
 * The status words are only significant provided the function returns to 0.
 * 
 * These are updated by the operating system in the input structure.
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
extern int output_command(FILE *stream, COMMAND_CAM *outputcommand);


extern int f_sync_fct(FILE *stream,int NbParam,int *arglist);			/*!< Only for compatibility : do not use */

/*! @}  */


/*! @addtogroup KSFAM_M2OS
	* @{
 */ 
 
/*! @brief Start a download instance.
 * @return None
 *
 * @link KSFAM_M2OS Back to top @endlink
 */ 
void download(void );

/*! @}  */


#endif   // __OEM_PUBLIC_H_INCLUDED__

#ifdef __cplusplus
}
#endif
