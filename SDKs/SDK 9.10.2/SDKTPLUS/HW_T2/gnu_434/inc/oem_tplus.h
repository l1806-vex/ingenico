#ifndef _OEM_TPLUS_H
#define _OEM_TPLUS_H

#ifdef __cplusplus
extern "C" {
#endif


/*+++******* EXPORTED #DEFINE CONSTANTS ****************************---*/

/*! @addtogroup KSFAM_TPLUS_FIC
	* @{
 */ 

//exported error
#define SVC_NO_MORE_RESOURCES    1

/*+++******* EXPORTED TYPES ****************************************---*/

typedef int (*svc_callback) (unsigned int data_size, 		 			    /*!< Mandatory : Data size to be exchanged between application ( this is because there is no way to read from the caller due to firewalls )  */
                             void *data);                     	         /*!< Mandatory : Data address to be exchanged */

typedef struct {
   unsigned short appli_id;					/*!< application type */
   unsigned short serv_id;						/*!< service number */
   svc_callback  sap;	         /*!< service entry point */
   unsigned char priority;						/*!< service priority  */
} svc_service_desc_t;

/*+++******* EXPORTED FUNCTION PROTOTYPES **************************---*/


/*! @brief Telium_Fopen opens a file with a file_name and associates a buffer to this file.
 * @param file_name : name of file .
 * @param type : type of opening.
 * @return
 * - pointer to Telium_File_t structure.
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
		diagnostic information. If the '*' option is positioned, the Telium_Fopen will comply with the C ANSI
		return as well as the other functions (Telium_Fclose, etc.).
 * - The 'a' option is used to avoid resetting the context when opening a peripheral. This function
		is implemented for the DISPLAY, for example.
 * - The standard options accepted are 'r' and 'w' for read and write.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern Telium_File_t *Telium_Fopen(const char *file_name, const char *type);

/*! @brief Telium_Fclose closes a file which has been opened by Telium_Fopen.
 * @param stream : pointer to file structure.
 * @return
 * - Return 0 if OK.
 * - EOF if problem is detected.
 *
 * @note
 * - Writing in the file takes place immediately.
 * - A peripheral which is closed during a dialogue will reset the dialogue
		 buffers and wait for a stable peripheral status before turning over control.
 * - Telium_Fclose on the modem peripheral is only permitted provided the line is cut
		 off, otherwise the terminal will generate a diagnostic indication and perform a reset.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_Fclose(Telium_File_t *stream);

/*! @brief Telium_Reset_buf resets a peripheral file. 
 *
 * This function resets a peripheral buffer.
 * @param stream : peripheral where buffer is to be reset.
 * @param id_buffer : buffer identification. id_buffer can take following values :
 * - _send_id : transmission buffer
 * - _receive_id : reception buffer
 *
 * @return None
 * @note It also clears the reception related events
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_Reset_buf(Telium_File_t *stream,int id_buffer);

/*! @brief Telium_Stdin returns the Telium_File_t handle of standard input (keyboard, generally).
 * @return
 * - 0 if standard input is not open (keyboard generally).
 * - Telium_File_t * otherwise.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern Telium_File_t *Telium_Stdin(void);

/*! @brief Telium_Stdout returns the Telium_File_t handle of standard output (screen generally).
 * @return
 * - 0 if the screen is not open.
 * - Telium_File_t * otherwise.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern Telium_File_t *Telium_Stdout(void);

/*! @brief Telium_Stdprt returns the Telium_File_t handle of standard printer.
 * @return
 * - 0 if the printer is not open.
 * - Telium_File_t * otherwise.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern Telium_File_t *Telium_Stdprt(void);

/*! @brief Telium_Ttestall is used to place the calling task in a standby status for reactivation on an event.
 *
 *  When an event arrives on a peripheral, the function reads the status of the concerned peripheral
	  and acknowledges the event (reset) if the event was produced by a completed action (transmission
	  buffer empty or end-of-transmission).
 * @param events : expected-peripherals in the form of a 32-bit long word :
	  CAM0, CAM1, SWIPE2, SWIPE31, COM0, COM1, MODEM, IAPP,
		KEYBOARD, PRINTER, PINPAD . Or 00 if no peripheral is expected (case of pause).
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
 *  Events not linked to peripherals are systematically cleared by Telium_Ttestall.
 *
 *  Application must handle all of the events positioned as a Telium_Ttestall return.
 *
 *  Non peripherals events can be used by the user by means of event positioning primitives : see [3].
 *
 *  Caution :
 * - if both parameters are 0, the calling task will be blocked forever,
 * - this function does not clear end-of-reception events ; it is
		 necessary to read the entire buffer or call the Telium_Reset_buf function,
 * - before calling Telium_Ttestall, it is necessary to select the events expected by the Telium_Mask_event function.
 * - The following instruction to get a peripheral event is now forbidden Telium_Ttestall ( 1<<fd->event , .. )
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern unsigned int Telium_Ttestall(unsigned int events,unsigned int TimeOut);

/*! @brief Telium_Mask_event modifies conditions generating an event. 
 *
 * This function is used to modify the conditions by which an event, for a given peripheral, is obtained.
 * @param stream : peripheral where event mask is to be modified.
 * @param mask : value of mask
 * @return None
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_Mask_event(Telium_File_t *stream,unsigned char mask);

/*! @brief Telium_ChngEventFile modifies generating event for a specified peripheral. 
 *
 * This function is used to modify the event raised by the given peripheral to wake-up application task.
 * @param stream : peripheral to modify.
 * @param evt_nbr : event number to use (from 0 to 31)
 * @return :OK ou EOF
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_ChngEventFile(Telium_File_t* stream, unsigned short evt_nbr);

/*! @brief Telium_Mask_event_read reads conditions generating an event. 
 *
 * This function is used to read the conditions by which an event, for a given peripheral, is obtained.
 * @param stream : peripheral where event mask is to be modified.
 * @param mask : value of mask.
 * @return None
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_Mask_event_read(Telium_File_t *stream,unsigned char *mask);

/*! @brief Telium_Status tests status of a peripheral. 
 *
 * This function is used to poll the peripheral.
 * @param stream : file address
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
   whereas MODEM is the bit associated to the peripheral for Telium_Ttestall).
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern void Telium_Status(Telium_File_t* stream, unsigned char* ad_status);

/*! @brief send_receive programs of a port for send/receive. 
 *
 * This function is used to selectively enable the 2 ways directions COMx or MODEM channels for send or receive.
 * @param stream : a Telium_File_t pointer.
 * @param send : boolean for enabling/disabling send.
 * @param receive : boolean for enabling/disabling receive.
 * @return
 * - 0 if function has been correctly executed.
 * - -1 if COMx or MODEM file was not open.
 * @note send and receive can take values ON or OFF.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
int Telium_Send_receive (Telium_File_t *stream, char send, char receive);

/*! @brief Telium_FormatOem programs a serial port COM0/COM1.This function is used to format a serial link.
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
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_FormatOem(const char *peripheral_name, va_list arglist);

/*! @brief Telium_Getc reads a character in a file.
 * @param stream : address of file where information will be read.
 * @return character read.
 * @note
 * This function only returns control provided a character has been read. The
   function blocks the current task while waiting for a character to be read. To
   avoid blocking the calling task, the status of the peripheral reception buffer
   must be tested before calling.
 *
 * In case of serial link, the function returns EOF when an end-of-file or a
   reception error has been detected. The Telium_Ferror routine must be used to
   determine the type of error.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_Getc(Telium_File_t *stream);

/*! @brief Telium_Fgets reads a string from a file.
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
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern char* Telium_Fgets(char *s,int n, Telium_File_t *stream);

/*! @brief Telium_Fread : copies, starting from address indicated by ptr, a number of data
    items , (nitems) having indicated size in file buffer.
 * @param ptr : pointer used to read into a file
 * @param size : size of item handled.
 * @param nitems : number of items handled.
 * @param stream : address of Telium_File_t.
 * @return
 * - number of items read in file buffer if Ok
 * - 0 if nothing has occurred.
 *
 * @note
 * The Telium_Fread function used for a serial link (MODEM, COM0, COM1) must be used with a size=1 (char)
 * In this case, Telium_Fread does not return the number of characters requested when a reception error is detected. 
 *
 * The user must therefore request the Telium_Ferror() function to determine the cause of the reception error.
 *
 * If the reception buffer is empty (see Telium_Status function), there is no error.
 *
 * If Telium_Ferror is not called, the next call to Telium_Fread will automatically clear the error and read the following characters.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern Telium_size_t Telium_Fread(void *ptr, Telium_size_t size, Telium_size_t nitems,Telium_File_t *stream);

/*! @brief Telium_Ungetc restore last character from a file.
 * @param c : character to restore.
 * @param stream : address of file.
 * @return EOF if character could not be inserted.
 * @note character inserted can be recovered by next Telium_Getc.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_Ungetc(int c, Telium_File_t *stream);

/*! @brief Telium_Getchar reads a character from standard input.
 * @return character read.
 * @note
 * This function only returns control provided a character has been read. The
   function blocks the current task while waiting for a character to be read. To
   avoid blocking the calling task, the status of the standard input peripheral 
   must be tested before calling with Telium_Status function.
 *
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
#define Telium_Getchar() Telium_Getc(Telium_Stdin())

/*! @brief Telium_Putc writes a character in a file opened by Telium_Fopen.
 * @param c : value of character
 * @param stream : pointer to Telium_File_t structure
 * @return
 * - 0 if OK.
 * - EOF if problem is detected.
 *
 * @note Writing in a file immediately triggers start up of the peripheral without
	  waiting for a start character. If the dialogue buffer is full, the routine waits
	  for a free space in buffer before returning control to the application.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_Putc(int c, Telium_File_t *stream);

/*! @brief Telium_Puts sends a character string to display.
 * @param s: formated string to be transmitted to output. Formated character string is addressed to standard output (display).
 * @return: Upon successful completion, Telium_Puts() returns a non-negative number. Otherwise, it returns EOF
 * @note Writing in a file immediately triggers initiation of the peripheral without waiting for a start character.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */
extern int Telium_Puts(const char *s);

/*! @brief This function reads the cursor line number, or returns -1 if display is not open.
 * @return
 * - cursor line number if OK
 * - -1 otherwise.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_Wherex(void);

/*! @brief This function reads the cursor column number, or returns -1 if display is not open.
 * @return
 * - cursor line number if OK.
 * - -1 otherwise.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_Wherey(void);

/*! @brief This function is used to position the cursor.
 * @param line : This parameter is used to give the line number.
 * @param column : This parameter is used to give the line column.
 * @return
 * - 0 if function has been executed,
 * - if not, returns -1.
 *
 * @note
 * - x and y may vary according to the display and font size.
 * - Using the small font ( 6* 8 pixels for a character ) on the 128*64 pixels
   display, x is between 0 and 7, y is between 0 and 20 .
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_Gotoxy(int line, int column);

/*! @brief Telium_Vfprintf writes in file opened by Telium_Fopen.
 * @param stream : pointer to Telium_File_t structure.
 * @param format : string to be formatted.
 * @param arglist : List of arguments :
 * @return
 * - number of characters formatted if OK.
 * - (-1) if problem detected.
 *
 * @note <ul><li> Writing in a file immediately triggers initiation of the peripheral without
   waiting for a start character.</li>
 		 <li>If the peripheral is PRINTER, refer to \ref Telium_Pprintf to get the ESC sequences.</li>
 		 </ul>

 *
 * @b Caution: the maximum size of the string to be formatted must not exceed 256 bytes for a "COM" devices and 128 bytes for "PRINTER"
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_Vfprintf(Telium_File_t *stream,const char *format, va_list arglist);

/*! @brief Telium_Fputs sends a character string to a file.
 * @param s : formatted string to be transmitted to output.
 * @param stream : pointer to specified Telium_File_t.
 * @return: Upon successful completion, Telium_Fputs() returns a non-negative number. Otherwise, it returns EOF
 * @note Writing in a file immediately triggers initiation of the peripheral without
   waiting for a start character (except for printer).
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_Fputs(const char *s, Telium_File_t *stream);

/*! @brief Telium_Fwrite : recovers, starting from address indicated by ptr, a number of data
    items (nitems) with indicated size in stream file buffer.
 * @param ptr : pointer used to write into a file
 * @param size : size of item handled.
 * @param nitems : number of items handled.
 * @param stream : address of Telium_File_t.
 * @return
 * - number of items written in file buffer if Ok.
 * - EOF (-1) if an error has occurred (file not oppened in write mode) .
 *
 * @note Writing in a file immediately initiates start up of the peripheral without waiting for a start character.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern Telium_size_t Telium_Fwrite(const void * ptr, Telium_size_t size, Telium_size_t nitems, Telium_File_t *stream);

/*! @brief Telium_Fprintf writes in file opened by Telium_Fopen.
 * @param stream : pointer to Telium_File_t structure.
 * @param format : string to be formatted.
 * @return
 * - number of characters formatted if OK.
 * - (-1) if problem detected.
 *
 * @note <ul><li> Writing in a file immediately triggers initiation of the peripheral without
   waiting for a start character.</li>
 		 <li>If the peripheral is PRINTER, refer to \ref Telium_Pprintf to get the ESC sequences.</li>
 		 </ul>

 *
 * @b Caution: the maximum size of the string to be formatted must not exceed 256 bytes for a "COM" devices and 128 bytes for "PRINTER"
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_Fprintf(Telium_File_t *stream, const char *format,...);

/*! @brief Telium_Ferror returns error status linked to last file read operations.
 * @param stream : address of file.
 * @return
 * - EOF if access to file is unsuccessful (file not opened, file opened in write mode only, ...).
 * - file read status otherwise.
 *
 * @note Status of Telium_Ferror function :
 *   OVERRUN_BUFFER 0xFF		: OEMC buffer overrun 
 *   OVERRUN_ERROR  0x2000		: USART overrun error 
 *   FRAMING_ERROR  0x4000		: USART framing error 
 *   PARITY_ERROR   0x8000		: USART parity error
 * - 0 if no error present.
 *
 * bit mask should be used if Telium_Ferror returns neither 0 nor 0xFF :
 *  _error_ = Telium_Ferror();
 *  if(_error_ & FRAMING_ERROR  ) {  ==> framming error }
 *  if(_error_ & OVERRUN_ERROR ) {  ==>overrun error }
 *  if(_error_ & PARITY_ERROR) {  ==> parity error }
 *  other bits are not error flags
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_Ferror( Telium_File_t *stream);

/*! @brief Telium_Clearerr clears file error indicator.
 * @param stream : file address.
 * @return None
 * @note After clearing the error on the character which should have been read, the
   character can be read by a function such as Telium_Fgetc or Telium_Fread.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern void Telium_Clearerr(Telium_File_t *stream);

/*! @brief Telium_Fowner modifies the task in the file descriptor. 
 *
 * This function is used to modify the task number for a given peripheral.
 * @param device_name : peripheral where stream task number is to be modified.
 * @param notask : number of the task.
 * @return
 * - Telium_File_t * : the stream if OK.
 * - NULL if the change is unsuccessful.
 * @note <ul><li>The peripheral must be open.</li>
 		 <li>non ZKA terminal only</li>
 		 </ul>
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern Telium_File_t *Telium_Fowner(const char *device_name,unsigned short notask);

/*! @brief Telium_Stdperif gets the address of the Stream and Copy the file in an application area.
 *
 * This function is used to read the Telium_File_t of a given peripheral and get the address of the stream.
 * @param name : name of the peripheral.
 * @param stream : destination of the structure Telium_File_t (only on NUCLEUS plateform).
 * @return
 * - the address Telium_File_t of the peripheral if OK.
 * - NULL if unsuccessful.
 *
 * @note The peripheral must be open.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern Telium_File_t *Telium_Stdperif(const char *name, Telium_File_t *stream);

/*! @brief Telium_CopyFile copies the file in an application area.
 *
 * This function is used to read the Telium_File_t of a given peripheral.
 * @param Hdl: source of the stream Telium_File_t.
 * @param fd: destination of the stream Telium_File_t.
 * @return
 * - EOF if unsuccessful.
 * - 0 if succesful.
 *
 * @note <ul><li>The peripheral must be open.</li>
 		 <li>Only on NUCLEUS plateform</li>
 		 </ul>
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_CopyFile(Telium_File_t* Hdl, Telium_File_t *fd);

/*! @brief Telium_Fioctl calls low level OEMC driver control function.
 *
 * @param cmd: Function code to be executed by OEMC device driver.
 * @param data: command parameter(s).
 * @param stream: target stream Telium_File_t.
 * @return
 * - 0 if succesful.
 * - other if unsuccessful.
 *
 * @note The peripheral must be open.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_Fioctl(int cmd, const void *data, Telium_File_t *stream);

/*! @brief Telium_Fputc writes a character in specified file opened by Telium_Fopen.
 * @param  c : value of character.
 * @param stream : pointer to Telium_File_t structure.
 * @return
 * - Returns the character sent if OK.
 * - EOF if problem detected.
 *
 * @note Writing in a file immediately triggers start up of the peripheral without waiting for
    the start character. If the dialogue buffer is full, the routine waits for a space in
    buffer to be released before returning control to the application.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_Fputc(int c, Telium_File_t *stream);

/*! @brief Telium_Fbreak generates a break on communication port.
 *
 * Sends a logical 0 on TX signal for a duration of time.
 * @param stream : pointer to Telium_File_t.
 * @param time : time of break in miliseconds.
 * @return 0
 * @note send and receive can take values ON or OFF.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_Fbreak(Telium_File_t *stream, unsigned short time);

/*! @brief Telium_Exit performs a startup of the Terminal. 
 *
 *  This routine records a startup diagnostic.
 *
 *  The diagnostic code is given by the parameter code.
 * @param code : diagnostic code. 
 * @return None
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern void Telium_Exit(int code);

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
 * @note  Telium_Exit ( EXIT_MAX_TASK_NUMBER ) if no more task available (up to 20 tasks can be defined including task 1 )
 * - It must be called prior to any kernel routines
 * - stacks are located in O/S, user stack by 2Kb incremented up to 64Kb
 * - Telium_Fork creates and starts the task
 * - Use Telium_CurrentTask to get the task number at task level
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern t_topstack *Telium_Fork (word(*Startaddress) (),byte* dummy1, int prior );

/*! @brief task stopping and killing, Telium_Fork must be called prior to kill routine. 
 *
 * It replaces Telium_StopTask / Telium_Terminate kernel routines.
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
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_Kill ( t_topstack *TaskHdl1, char *options);

/*! @brief Telium_GiveNoTask converts one pointer to type t_topstack to an OEMC task number.
 * @param topstack : pointer on t_topstack structure. This pointer is returned by Telium_Fork routine when creating task.
 * @return OEMC task number.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern word Telium_GiveNoTask (t_topstack *topstack);

/*! @brief This function allows application to get or set system parameters.
 * @param cmd : command identifier .
 * @param data : command parameters.
 * @return
 *   \li  0 if succesful.
 *   \li -1 if function not available.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */
extern int Telium_Systemfioctl(int cmd, void *data);

/*! @brief This routine configures the character font.
* @param pdoth : number of horizontal dots.
* @param pdotv : number of vertical dots.
* @return None.
*
* @link KSFAM_TPLUS_FIC Back to top @endlink
*/
extern void Telium_Startupcv20 (char pdoth,char pdotv);

/*! @brief This function replaces a standard character with a special character. 
 *
 * Up to 128 characters can be redefined.
 * @param key : ASCII value of key parameter
 * @param pattern : Definition of character, pattern .
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
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_Defdisplaypattern(char key,char *pattern);

/*! @brief Start a local download instance
 * @return None
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern void Telium_Download(void );

/*! @brief Tests if battery is present
 * @return 0 if no battery is present.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int  Telium_Isbattery (void);

/*! @brief Telium_Powered checks if the terminal need to be powered for communication layout.
 *
 * If the caller is linked to DLL CB2A (French communication layout), the return depends on the network access parameter :
 * - GPRS and GSM, return always TRUE.
 * - Bluetooth terminal, return always TRUE.
 * - WiFi terminal, return always TRUE.
    if not, return TRUE only if network access parameter does not need to be powered
    (IP/Eth for instance), FALSE instead.
 * - Other value, return TRUE if terminal is powered, FALSE instead.
 *
 * If the caller is not linked to DLL CB2A (French communication layout), return TRUE if terminal is powered, FALSE instead
 * @return see above
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int  Telium_Powered(void);
/*
=======================================
			Task management
=======================================
*/

/*! @brief Telium_CurrentTask returns the OEMC task number of the current task. 
 * @return Current OEMC task number. The TaskNumber for a user defined task 
 * - or -1     for the BackGround Task
 * - or -2     for the Clock Task 
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern short Telium_CurrentTask(void);

/*! @brief Telium_TaskState gets the state of a task.
 * @param TaskNumber : task number affected to this task (see CurrentTask ).
 * @param pTaskState : state of the task.
 * - 0 : cCurrent = specified task is the running one
 * - 1 : cReady   = specified task is ready
 * - 2 : cWaiting = specified task is waiting
 * - 3 : cNonOperational = specified task is stopped
 * @return error code :
 * - cOK 
 * - cBadTaskNumber (fatal error : The task number specified is not in the range configured by the OS).
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern tStatus Telium_TaskState( Word TaskNumber, Word *pTaskState);

/*! @brief Telium_Terminate Stop Current task.
 *   WARNING : Telium_Terminate doesn't free task's stack. Telium_Kill must be used instead of Telium_Terminate
 * @return error code : 
 * - cOK 
 * - cBadTaskNumber (called by unknown rtc task).
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern tStatus Telium_Terminate(void);

/*! @brief Telium_SignalEvent signals a real time event, to a given task.
 *
 * The event @c EventNumber of the task identified by @c TaskNumber is set. 
   Should this task be waiting for the occurrence of this event, it is
   reactivated and its state is changed back to the ready or current state.
 * @param TaskNumber  : task number to which an event is to be signalled. 
 * @param EventNumber : event number to signal. from 0 to 31.
 * @return error code :
 * - cOK 
 * - cBadTaskNumber : fatal errors, The task number specified is not in the range configured by the OS
 *
 * @note  Some event numbers are reserved for OEMC peripherals, and for manager. 
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern tStatus Telium_SignalEvent( Word   TaskNumber,tEvent EventNumber);

/*! @brief The calling task is put in the waiting (cWaiting) state until one of the events of @c EventList is signalled (i.e. put in the 'set' state). 
 *
 * If one of the events specified in @c EventList is already set upon calling
   Telium_WaitEvents, the calling task does not wait nor it is pre-empted.
 *
 * In order to limit the waiting time, a maximum value @c TimeOut can be specified. 
   @c TimeOut is given in terms of number of 10 milliseconds.
   if the time-out occurs before any of the events, the task is reactivated
   and will resume with a status cTimeOut. A value of zero means that
   no limit is requested.
 *
 * If @c Eventlist is empty, then the invoking task only waits for the
   occurrence of a time-out. Note that passing an empty @c EventList
   and a value of zero for @c Timeout will provoke an infinite wait.
 * @param EventsAwaited : 32 bits bitfield List of awaited events : 1 bit per event, 
   where the bit number corresponds to the event number. (The least significant bit corresponds
   to @c EventNumber = 0). If @c EventList = 0 (i.e. the event list is empty)
   then only the @c TimeOut is awaited.
 * @param TimeOut 			 : Maximum waiting time in terms of 10 milliseconds period. A time-out
   value of 0 indicates no waiting limit.
 * @param pEventsOccurred : 32 bit bitfield List of all occurred events : 1 bit per event (included those which are not waited)
 * @return error code :
 * - cOK 
 * - cTimeOut : The time out specified in the call occurred before any of the specified events occurred.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern tStatus Telium_WaitEvents( tEventList EventsAwaited,DoubleWord TimeOut,tEventList *pEventsOccurred);                           

/*! @brief Telium_EventsOccurred tests whether ALL the events of @c EventList of the calling task have occurred.
 * @param EventList : List of events to be tested : 1 bit per event, where the bit number corresponds to the event number. (The least significant bit corresponds to EventNumber>0) 
 * @return 
 * - 1 (TRUE) if all the events in EventList occurred or if EventList is empty.
 * - 0 (FALSE) if at least one of the events in EventList has not occurred. The primitive tests whether ALL the events of EventList of the calling task have occurred.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern Boolean Telium_EventsOccurred(tEventList EventList);

/*! @brief Telium_ClearEvents clears one or several real time events in the current task. 
 * @param EventList : 32 bits bitfield. To each bit corresponds an event. 
 * Each bit set to 1 will erase the corresponding event. 
 * @return error code :
 * - 0 if OK.
 * - Other returned values are defined in file xecarm_def.h.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern tStatus Telium_ClearEvents( tEventList EventList);

/*! @brief Telium_InitSemaphore initialises the count limit of the semaphore identified by SemaphoreNumber. 
 *
 * All the semaphores have the following default initialisation : 
 *
 * - UnitCount   = 0 
 * - Task queue  = empty 
 * - Count limit = 32767 
 *
 * The unit count can be initialised by calling repeatedly the Telium_V primitive .
 * @param SemaphoreNumber : Use GetSemaphoreUser() to get the SemaphoreNumber.
 * @param CountMaxValue   : Maximum value (limit) that the count may take in the range 0..32767. 
 * @return error code :
 * - cOK 
 * - cBadSemaphoreNumber : fatal errors, the semaphore number specified is not in the range configured by the OS.
 * - cNegMaxValue : The CountMaxValue parameter has a negative value. 
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern tStatus Telium_InitSemaphore( Word  SemaphoreNumber,Word  CountMaxValue);

/*! @brief The calling task is releasing a unit of the semaphore identified by SemaphoreNumber. 
 *
 * The unit count associated with the semaphore is incremented and if any tasks are waiting, 
   the first is dequeued from the task queue associated with the semaphore, put back in the 
   READY or CURRENT state and the unit is granted to it. 
 *
 * Should the maximum value of the semaphore count be exceeded, the unit count remains unchanged and a cSemOverflow status returned.
 * @param SemaphoreNumber : Use GetSemaphoreUser() to get the SemaphoreNumber.
 * @return error code :
 * - cOK 
 * - cSemOverFlow : More Telium_V primitives have been performed on this semaphore than allowed by the count limit. 
 * - cBadSemaphoreNumber : Fatal error. The semaphore number specified is not in the range configured by the OS. 
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern tStatus Telium_V( Word SemaphoreNumber);

/*! @brief The calling task is requesting allocation of a unit in the semaphore identified by SemaphoreNumber. 
 *
 * If no unit is available, the calling task is inserted at 
   the end of the task queue associated with semaphore SemaphoreNumber and waits until one unit 
   is available. The unit count associated with the semaphore is decremented. 
 *
 * In order to limit the waiting time, a maximum value TimeOut can be specified. Timeout is 
   specified in terms of number of 10 milliseconds. If the time-out occurs before the granting 
   of the unit, the task is reactivated and will resume with a status cTime-out. A value of 
   zero means that no limit is requested. 
 * @param TimeOut : Maximum waiting time in terms of number of 10 milliseconds. A time-out value of 0 indicates no waiting limit.
 * @param SemaphoreNumber : Use GetSemaphoreUser() to get the SemaphoreNumber.
 * @return error code :
 * - cOK 
 * - cTimeOut : The time out specified in the call occurred before a unit was granted in the specified semaphore. 
 * - cBadSemaphoreNumber : Fatal error. The semaphore number specified is not in the range configured by the OS. 
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern tStatus Telium_P( Word SemaphoreNumber,tTimeOut TimeOut);

/*! @brief The calling task is requesting allocation of a unit in the semaphore identified by SemaphoreNumber with no waiting if no unit is available.
 *
 * If a semaphore unit is available, it is granted and the unit count is decremented. Otherwise a status indicating
 * that no unit is available is returned (cSemNonAvailable). 
 * @param SemaphoreNumber : Use GetSemaphoreUser() to get the SemaphoreNumber.
 * @return  error code :
 * - cOK 
 * - cSemNonavailable : no unit was available in the specified semaphore. 
 * - cBadSemaphoreNumber : Fatal error. The semaphore number specified is not in the range configured by the OS.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern tStatus Telium_TestP( Word SemaphoreNumber);

/*! @brief Initialises the local message capacity of the mailbox. 
 *
 * All the mailboxes have a default initialisation :
 * - Number of pending messages = 0 
 * - Number of waiting tasks = 0 
 * - Limit on the number of pending messages = 32767 
 *
 * This is done at OS run time. So, all the mailboxes can be immediately used with no 
     further initialisation. The default value of the limit on the number of pending messages 
     will never be reached as the limit on the overall number of pending messages would be 
     reached much before. 
 * 
 * Telium_InitMailBox can be called at any moment, even for a mailbox already in use. 
   If the number of pending messages at that point is greater than the newly 
   specified value, all the messages remain pending, but further calls to send will not be 
   accepted until the number of messages in the queue actually becomes lower than the limit. 
 * @param MailBoxNumber : Use GetMailboxUser .
 * @param Capacity : mailbox capacity (max. number of messages waiting in the mailbox) 
 * @return error code :
 * - cOK 
 * - cBadMailBoxNumber : The mailbox number specified is not in the range configured by the OS. 
 * - cNegCapacity : The mailbox capacity specified has a negative value. 
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern tStatus Telium_InitMailBox( Word MailBoxNumber,Word Capacity);

/*! @brief The Telium_Send primitive requests the sending of the message 'Message' to the mailbox identified by @c MailboxNumber. 
 *
 * If no task is waiting for a message from the mailbox the @c Message is stored in an 'envelope' and enqueued at the end of the message queue associated with the mailbox.
 *
 * if no envelope is available, a (cMessOverflow) is generated. Should the number of messages in
   the message queue exceed the local capacity specified by the
   primitive Telium_InitMailBox, the request is refused and an error status word
   (cFull) is returned to the calling task.
 *
 * In the case where the queue of waiting tasks is not empty, the
   message is directly granted to the first task of the queue, which is
   thus dequeued and activated. 
 * @param MailBoxNumber : Use GetMailboxUser() to get the MailBoxNumber.
 * @param Message : Message to be sent (4 bytes) 
 * @return error code :
 * - cOK 
 * - cFull : The local capacity of the mailbox (specified by Telium_InitMailBox) has been exceeded. 
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern tStatus Telium_Send( Word MailBoxNumber,DoubleWord Message);

/*! @brief The Telium_Receive primitive requests a message from the mailbox identified by @c MailboxNumber. 
 *
 * If no message is pending in the mailbox, the calling task 
   is put in the waiting state and is inserted at the end of the task queue associated
   with the mailbox and waits until a message is available. 
 *
 * If there is already a message in the mailbox the task does not wait nor it is 
   pre-empted, gets the message and returns its envelope. 
 *
 * In order to limit the waiting time, a maximum value 'TimeOut' can be specified. 
   'TimeOut' is specified in terms of number of 10 milliseconds. If the time-out occurs 
   before the occurrence of a message, the task is reactivated and will resume with a status cTimeOut. 
   A value of zero means that no limit is requested. 
 * @param MailBoxNumber : Use GetMailboxUser() to get the MailBoxNumber.
 * @param pMessage : pointer to the received message (4 bytes).
 * @param TimeOut : Maximum waiting time in terms of number of 10 milliseconds. 
 * A time-out value of 0 indicates no waiting limit. 
 * @return error code :
 * - cOK 
 * - cTimeOut : The time out specified in the call occurred before a message was available in the specified mailbox. 
 * - cBadMailBoxNumber : The mailbox number specified is not in the range configured by the OS. 
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern tStatus Telium_Receive( Word MailBoxNumber,DoubleWord *pMessage,tTimeOut   TimeOut);

/*! @brief The Telium_TestReceive Primitive requests a message from the mailbox identified by @c MailboxNumber, with no waiting if no message is pending. 
 *
 * In this case a status (cNoMessPending) indicating that no message is available is returned. 
 * @param MailBoxNumber : Use GetMailboxUser() to get the MailBoxNumber.
 * @param pMessage : pointer to the received message (4 bytes). Output parameter.
 * @return error code :
 * - cOK 
 * - cNoMessPending : No message was pending in the specified mailbox. 
 * - cBadMailBoxNumber : The mailbox number specified is not in the range configured by the OS.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern tStatus Telium_TestReceive( Word MailBoxNumber,DoubleWord *pMessage);

/*! @brief This primitive requests the execution of @c UserDelayProcedure upon detecting 
 * the expiration of @c FirstDelay, and to repeat cyclically this primitive with a periodic delay 'period'. 
 *
 * The invoking task is not pre-empted through the Telium_StartLDelay primitive. 
 * 
 * 'Period' and @c FirstDelay are expressed in number of 10 milliseconds. 
 * 
 * Some examples of what this procedure could do : 
 * - Signal an event to a task waiting for this event to synchronise cyclic execution. 
 * - Release a unit to a semaphore to wake up a task waiting for one unit of this semaphore.
 * - Send a predefined message to a mailbox 
 * - Increment a counter or set a flag for statistical purposes 
 * - Sample values of counters incremented by other tasks in order to make statistics on task activity 
 * 
 * There are some precautions to take concerning the procedure : 
 * - It is technically possible to call all the routines of the kernel but it is highly 
     recommended not to call primitives which could put the clock task in the waiting or 
     in the non-operational state, as this may block the services provided by the clock task. 
 * - No call of OEMC / M2-OS routines 
 * - @c UserDelayProcedure is a procedure called by the JSR instruction, with no parameters. 
 * - @c UserDelayProcedure cannot rely on any register values initialised by a host task. 
     Rather, it should initialize all data and address registers it will use, as is usually 
     done in interrupt routines. But none of them have to be restored, except the system stack 
 * 
 * Besides note that the Telium_StartLDelay may be called at any time between two clock interrupts : 
   the accuracy of the first delay is 1 clock tick. 
 *
 * @param DelayNumber : Delay identifier (Use GetDelayUser() to get the DelayNumber). range 0..NbDelays-1 
 * @param FirstDelay : First delay. (in unit of 10ms).
 *     Value in the range 00..65535 (a value of 0 will be considered as 1) .
 * @param Period : Period between successive delays. (in unit of 10ms)
 *     A value of zero indicates that no cyclic delay is requested. 
 * @param FunctionPtr : pointer to the function to be activated at the expiration of the delay
 * @return error code :
 * - cOK 
 * - cBadDelayNumber : The delay number specified is not in the range configured by the OS. 
 * - cDelaySlotAlreadyUsed : The specified delay has already been activated by a call to Telium_StartLDelay. 
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern tStatus Telium_StartLDelay(Word DelayNumber,DoubleWord FirstDelay, DoubleWord Period, word (*FunctionPtr)());
                                          
/*! @brief This primitive will cancel the handling of the delay identified by DelayNumber and started by Telium_StartLDelay. 
 * @param DelayNumber  : Delay identifier: Use GetDelayUser() to get the DelayNumber
 * @param pRestOfDelay : Output param. Remaining time before the next expiration of delay. 
 *
 * It is expressed in number of 10 milliseconds.
 * - if > 0 : remaining delay until the next activation of the user procedure.
 * - if = 0 : (non periodical) delay already occurred or stopped.
 *
 * @param pPeriod : Period value or zero in case of non periodical delay. Not used.
 * @return error code :
 * - cOK 
 * - cBadDelayNumber : The delay number specified is not in the range configured by the OS. 
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern tStatus Telium_StopDelay( Word DelayNumber,DoubleWord *pRestOfDelay,DoubleWord *pPeriod);

/*! @brief TMT_Retrieve_Clock returns the tick counter. one tick = 10 ms.
 * @return Number of elapsed ticks since startup.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern unsigned long int TMT_Retrieve_Clock (void);

/*! @brief This function can call a service.
 * @param num_appli : application type
 * @param service : service number
 * @param data_size : Data size to be exchanged between application ( this is because there is no way to read from the caller due to firewalls ) .
 * @param data : Data address to be exchanged 
 * @param ret_code : Returned value from the called service 
 * @return
 * -1 --> Service does not exist
 * -2 --> Application does not exist
 * -3 --> Application is not loaded
 *  0 --> successful 
 *  1 --> no more resources to allocate a stack 
 *  4 --> MMU error
 *  5 --> task context error (not called by a task)
 * @note
 * - Data area to be exchanged between applications must be contiguous and does not contain any  pointer. 
 * - This area is used as an input or output from the service : the service provider may read or write into this data area. 
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_ServiceCall(unsigned short num_appli, unsigned short service, unsigned int data_size, void* data, int *ret_code);

/*! @brief This function records new services via a service descriptor in which is specified the number of services to be recorded and for each service : 
 *
 * - the routine address with a data transfert area as parameter.
 * - the priority of the service .
 * - the application number that provides the service .
 *
 * There is 2 prototypes allowed for servicies with 2 or 4 parameters. 
 *
 * @param num_of_serv : number of services in the service descriptor .
 * @param services : service descriptor .
 *
 * @return 
 * - 0 sucessfull .
 * - Non zero value otherwise.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_ServiceRegister(unsigned int num_of_serv, svc_service_desc_t services[]);

/*! @brief This function checks the availability of a service and allow to read the service priority if it exists.
 * @param appli_id : application number 
 * @param serv_id : service number 
 * @param priority : Service priority 
 * @return
 * - 0 sucessfull .
 * - Non zero value otherwise ( service does not exist ) .
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_ServiceGet(unsigned short appli_id, unsigned short serv_id,unsigned char *priority);

/*! @brief This function is used to remove a service.
 * @param appli_id : Application number.
 * @param serv_id : Service number to remove.
 * @param sap : Service entry point.
 * @param priority : Service priority.
 * @return
 * - 0 sucessfull .
 * - Non zero value otherwise ( service does not exist or bad parameters passing).
 *
 * @note The service is removed only if parameters num_appli, service, sap, priority correspond to the recorded service. 
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int Telium_ServiceRemove(unsigned short appli_id, unsigned short serv_id, svc_callback sap,unsigned char priority);

// DATE and TIME
/*! @brief This function is used to read the date in the terminal's calendar.
 * @param pt_date : pointer to structure Telium_Date_t. 
 * @return 
 * - 0 if function has been correctly executed.
 * - -1 if date is incoherent.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */
extern int    Telium_Read_date  (Telium_Date_t *pt_date );

/*! @brief This function is used to check the date by verifying the coherency of the param eterized date.
 * @param date : pointer to structure Telium_Date_t.
 * @return
 * - 0 if function has been correctly executed
 * - 1 if date is incoherent.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int    Telium_Ctrl_date  (Telium_Date_t *date);

/*! @brief This function is used to write the date in the terminal's calendar.
 * @param pt_date : pointer to structure Telium_Date_t. 
 * @return 
 * - 0 if function has been correctly executed.
 * - -1 if date is incoherent.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */
extern int    Telium_Write_date (Telium_Date_t *pt_date);

/*! @brief Telium_Printf formats an output to display on screen.
 * @param format : string to be formatted. The character string to be formatted is addressed to the standard output (display).
 * @return
 * Upon successful completion, the Telium_Printf() functions return the number of bytes transmitted  
 * If an output error was encountered, these functions return a negative value. 
 *
 * @note 
 * <ul><li>Writing in a file immediately triggers start up of the peripheral without
 *  waiting for a start character.</li>
 *  <li>"\x1b" clears the display</li></ul>
 *
 * @b Caution : the maximum size of the string to be formatted must not exceed 256 bytes.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int    Telium_Printf(const char * format, ...);

// \brief Telium_Vsprintf formats an output (argc argv) (cf doc ansi C)
// \param argc
// \param argv
// \return
// cf doc ansi C
// \note
int Telium_Vsprintf(char *, const char *, va_list );

/*! @brief Telium_Pprintf formats an output to printer with flow control
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
 * 
 * @link KSFAM_FIC Back to top @endlink
 */ 
extern int    Telium_Pprintf(const char * format, ...);

/*! @brief Telium_Fprintf writes in file opened by Telium_Fopen.
 * @param stream : pointer to Telium_File_t structure.
 * @param format : string to be formatted.
 * @return
 * - number of characters formatted if OK.
 * - (-1) if problem detected.
 *
 * @note <ul><li> Writing in a file immediately triggers initiation of the peripheral without
   waiting for a start character.</li>
 		 <li>If the peripheral is PRINTER, refer to \ref Telium_Pprintf to get the ESC sequences.</li>
 		 </ul>

 *
 * @b Caution: the maximum size of the string to be formatted must not exceed 256 bytes for a "COM" devices and 128 bytes for "PRINTER"
 *
 * @link KSFAM_FIC Back to top @endlink
 */ 
extern int    Telium_Fprintf(Telium_File_t *stream, const char *format,...);

/*! @brief Telium_Vprintf formats an output to display on screen.
 * @param format : string to be formatted. The character string to be formatted is addressed to the standard output (display).
 * @param arglist : List of arguments :
 * @return
 * Upon successful completion, the Telium_Vprintf() functions return the number of bytes transmitted  
 * If an output error was encountered, these functions return a negative value. 
 *
 * @note 
 * <ul><li>Writing in a file immediately triggers start up of the peripheral without
 *  waiting for a start character.</li>
 *  <li>"\x1b" clears the display</li></ul>
 *
 * @b Caution : the maximum size of the string to be formatted must not exceed 256 bytes.
 *
 * @link KSFAM_TPLUS_FIC Back to top @endlink
 */ 
extern int    Telium_Vprintf(const char * format, va_list arglist );

 /*! @brief Telium_Putchar sends a character to display.
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
extern int    Telium_Putchar(int c);

/*! @brief On mobile terminal only : Telium_Shutdown() turn terminal in standby mode
 * @return 
 * - 1 if function has been executed,
 * - if not, returns 0.
 *
 * @note
 * - this function doen't test if POS is Mobile or not
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
extern int Telium_Shutdown (void);

/*! @}  */ 
 
/*! @addtogroup KSFAM_PPS
	* @{
 */ 

/*! @brief Define a bitmap to display
 * @param Fp : pointer to Telium_File_t.
 * @param key : Hexadecimal value of byte to replace
 * @param pattern : Bitmap
 * @return
 * - OK (0)
 * - or -1.
 *
 * @link KSFAM_PPS Back to top @endlink
 */ 
int Telium_Defdisplaypatterndsp (Telium_File_t *Fp, char key,char *pattern);

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
 *  The Telium_Is_iso1 function must always be preceded by the fopen function on the swipe31 peripheral .
	  SWIPE31 event can occur at the same time as SWIPE2 event, this is very
	  important when application waits for both events and returns from ttestall
 *
 * Note:
 * If the read magnetic track contains non ISO character or has a non 
 * ISO format, you can recover raw track stream of bits by 
 * using Telium_Fread(). To build your own algorithm to re-form data from 
 * magnetic tracks, you have to consider that stream of bits may differ 
 * according to terminal types and to read cards (= number of 
 * synchronisation bits may differ). 
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
int Telium_Is_iso1(Telium_File_t *stream,unsigned char *length,unsigned char *swipe_read);


/*! @brief This function is used to check and format the ISO2 stripe buffer.
 * @param stream : pointer to Telium_File_t.
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
 * - The Telium_Is_iso2 function must always be preceded by the fopen function on the swipe2 peripheral.
 *
 * Note:
 * If the read magnetic track contains non ISO character or has a non 
 * ISO format, you can recover raw track stream of bits by 
 * using Telium_Fread(). To build your own algorithm to re-form data from 
 * magnetic tracks, you have to consider that stream of bits may differ 
 * according to terminal types and to read cards (= number of 
 * synchronisation bits may differ). 
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
int Telium_Is_iso2(Telium_File_t *stream, LG_REF_CLI *length, BUFFER_PISTE swipe_read);


/*! @brief This function is used to check and format the ISO3 stripe buffer.
 * @param stream : pointer to Telium_File_t.
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
 * - The Telium_Is_iso3 function must always be preceded by the fopen function on the swipe31 peripheral.
 * - SWIPE31 event can occur at the same time as SWIPE2 event, this is very
		 important when application waits for both events and returns from ttestall
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
int Telium_Is_iso3(Telium_File_t *stream,unsigned char *length,unsigned char *swipe_read);

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
extern unsigned char Telium_EMV_apdu(Telium_File_t *Fd_P, T_APDU *C_apdu, T_APDU *R_apdu);



/*! @brief This function is used to shutdown the card per standard ISO 7816-3.
 * @param Fd_P : pointer to Card flow.
 * @return
 * - 0 if function has been correctly executed.
 * - 1 if card has already been removed.
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
extern int Telium_Power_down ( Telium_File_t *Fd_P );



/*! @brief This routine must be used instead of already existing power_down_gpm routine.
 * @param Fd_P : pointer to oemc file structure. CAM0 only.
 * @return Always returned 00.
 *
 * @link KSFAM_CARD Back to top @endlink
 */ 
extern int Telium_Power_down_sync ( Telium_File_t *Fd_P );


/*! @brief Telium_InitGkDrv init of CAM IFD context to use T=1 after T=0 ATR (Moneo specific)
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
extern void Telium_InitGkDrv(Telium_File_t *Fd_P, va_list arglist);


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
extern unsigned char Telium_EMV_power_on ( Telium_File_t *Fd_P , HISTORIC *pOctetsHisto_P );



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
extern int Telium_Power_on ( Telium_File_t *Fd_P , HISTORIC *pOctetsHisto_P );



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
extern int Telium_Power_on_sync ( Telium_File_t * Fd_P,int PROTOCOL  );



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
extern int Telium_Input_command(Telium_File_t * stream, COMMAND_CAM * cmd );



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
extern int Telium_Output_command(Telium_File_t *stream, COMMAND_CAM *outputcommand);


/*! @}  */
 
#ifdef __cplusplus
}
#endif

#endif /* _T2_TRAP_INT_H */

