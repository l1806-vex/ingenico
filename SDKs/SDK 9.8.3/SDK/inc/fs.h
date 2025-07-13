/*! @addtogroup KSFAM_FFMS
	* @{
		
	* @section ex_FFMS Example
 	*

 * @include fs_Sample_01.c
 	* 
 	* @link KSFAM_FFMS Back to top @endlink
 	
 */ 

#ifndef _FS_H
#define _FS_H

// suppression des majuscules pour analyse GSIM 
#include "rtctime.h"

/*
======================================================================
					List of Defines
======================================================================
*/

/*! @brief Max Number of files in system disks. */
#define MAX_SYSTEM_FILES 200	/*!< Max Number of files in SYSTEM disk. */
#define MAX_HOST_FILES   200	/*!< Max Number of files in HOST disk */

// volume name size 
/*! @brief Max Number of files in SYSTEM disk. */
#define FS_LABELNAMESIZE                16 		/*!< disk name size */
#define FS_NBFILES                   		1000 	/*!< nb of files handled  */
#define FS_NBDISKS                      52 		/*!< nb of disk handled  */
#define FS_DISKNAMESIZE                 16 		/*!< max disk name size (15 bytes + '\0') */
#define FS_FILENAMESIZE                 16 		/*!< max file name size (15 bytes + '\0') */
#define FS_PATHSIZE                     FS_DISKNAMESIZE+FS_FILENAMESIZE+2 	/*!<size of path+disk name + filename + separator */
#define FS_SEPARATOR                    '/' 	/*!< separator */
#define FS_METACARSUB                   '*' 	/*!< wild card  */
#define FS_MAX_DIR_DEPTH                7  		/*!< max directory depth*/
#define FS_MAX_PATH_SIZE                (FS_MAX_DIR_DEPTH*(FS_FILENAMESIZE+1))		/*!< max depth of sub directories */

// open and access mode 
#define FS_NOFLAGS                      0x00		/*!< No access allowed from other applications */
#define FS_RONLYMOD                     0x01		/*!< read only mode allowed from other applications */
#define FS_WRTMOD                       0x04		/*!< write mode allowed from other applications */

#define FS_READMOD                      0x02		/*!< only for compatibility with existing projects. It has not to be used. */
#define FS_APNDMOD                      0x0C    /*!< only for compatibility with existing projects. It has not to be used. */
#define FS_TEXT_MOD                     0x10		/*!< only for compatibility with existing projects. It has not to be used. */
#define FS_BINARY_MOD                   0x20		/*!< only for compatibility with existing projects. It has not to be used. */

/*! @brief Define the disk creation parameters : S_FS_PARAM_CREATE->Mode */
#define FS_WRITEONCE                    0x1000	/*!< create nand flash disk. */
#define FS_WRITEMANY                    0x2000	/*!< create RAM disk. */
#define FS_ONCEMANY_MOD                 0xF000	/*!< mask for previous values. */

/*! @brief Define the disk creation parameters : S_FS_PARAM_CREATE->IdentZone. used only for Nand flash */
#define FS_WO_ZONE_APPLICATION 			0						/*!< Create disk in programme area ; only for compatibility with existing projects. It has not to be used. */
#define FS_WO_ZONE_DATA							1						/*!< Create disk in data area */

// values that take "whence" in FS_seek - file position 
#define FS_SEEKSET                      0				/*!< seek from start of file */
#define FS_SEEKCUR                      1				/*!< seek from current position */
#define FS_SEEKEND                      2				/*!< seek from end of file */


/*
======================================================================
					Return codes
======================================================================
*/

// as an integer - basic FS routines 
#define FS_GARBAGE_COLLECTION           9			/*!< only for compatibility with existing projects. It has not to be used */
#define FS_DSKUSED                      8			/*!< error : disk is used */
#define FS_NOACCESS                     7			/*!< error : access denied */
#define FS_NAMEUSED                     6			/*!< error : a file with the same name exist  */
#define FS_NOMEM                        5			/*!< error : no enough memory */
#define FS_FILEUSED                     4			/*!< error : file is opened */
#define FS_NOFORMAT                     3			/*!< error : disk is not formated */
#define FS_OK                           2			/*!< success */
#define FS_NOADR                        1   	/*!< bad address */
#define FS_KO                           0			/*!< other errors */
#define FS_ERROR                        (-1)	/*!< other errors */


/*
======================================================================
			Data Structures Definition
======================================================================
*/

/*
======================================================================
			     File Stream 
======================================================================
*/

/*! @brief Define the file stream. */
// GSIM_T:S_FS_FILE:DATA_CODE( 4 * 2 + sizeof(long) + sizeof(int) )
typedef struct {
    void* DiskDescriptor;							//!< Disk Identifier */
    void* FileDescriptor;							//!< File descriptor  */
    unsigned long FileCursor;					//!< Current file position  */
    unsigned int  Flags;							//!< Opening mode */
}S_FS_FILE;

/*
======================================================================
			     File Infos 
======================================================================
*/

/*! @brief Define the file informations. */
typedef struct {
    char FileName[FS_FILENAMESIZE];		/*!< filename  */
    S_TM_LOCAL	DateCreate;				/*!< creation date */
    unsigned long FileSize;						/*!< file size  */
}S_FS_FILEINFO;

/*
======================================================================
			     Disk Stream  
======================================================================
*/

/*! @brief Define the disk stream informations. */
// GSIM_T:S_FS_DIR:DATA_CODE( 4 * 2 + sizeof(int) + sizeof(char) * FS_FILENAMESIZE ) 
typedef struct {
    void* DiskIdent;								/*!< disk identifier */
    unsigned int DescriptNb;				/*!< current descriptor number */
    char Pattern[FS_FILENAMESIZE];	/*!< searching pattern */
    S_FS_FILEINFO InfoFile;					/*!< ptr on file information */
}S_FS_DIR;

/*
======================================================================
			     Disk Creation Parameters  
======================================================================
*/

/*! @brief Define the disk creation parameters. */
typedef struct {
    char Label[FS_DISKNAMESIZE];			/*!< disk label  */
    unsigned int Mode;								/*!< Handling mode (FS_WRITEMANY or FS_WRITEONCE)  */
    unsigned int AccessMode;					/*!< disk access rights . FS_NOFLAGS (no), FS_RONLYMOD (reading only) and FS_WRTMOD (r/w)  */
    unsigned int NbFichierMax;				/*!< maximun files number */
    unsigned int IdentZone;						/*!< disk area FS_WO_ZONE_APPLICATION or FS_WO_ZONE_DATA (when FS_WRITEONCE)  */
}S_FS_PARAM_CREATE;

/*
======================================================================
			     Disks Infos  
======================================================================
*/

/*! @brief Define the disk informations. */
typedef struct {
    char Label[FS_DISKNAMESIZE];				/*!< disk label. */
    unsigned int NumAppli;							/*!< application number that creates disk. */
}S_FS_CONTEXT;

/*! @brief Define the disk informations. */
typedef struct {
    S_FS_CONTEXT DiskIdent[FS_NBDISKS];				/*!< Disk informations */
}S_FS_INFO_CONTEXT;  



/*! @brief Define a structure giving informations about a file system area. */
typedef struct {
	unsigned int Ident;								/*!< ID of the area */
	unsigned long Size;								/*!< size of the area in bytes */
	unsigned long Free;								/*!< free size in bytes */
	unsigned long Erasable;						/*!< erasable size in bytes (will be free by gabgae collection) */
} S_FS_AREA_DIAG;

#define NB_AREA_DEFINE 3 

/*! @brief Define a structure describing the file system informations. */
typedef struct {
	S_FS_AREA_DIAG Area[NB_AREA_DEFINE];	/*!< array of file system areas. */
	unsigned long NumberOfStart;					/*!< number of starts. */
    unsigned long DeviceMaker;					/*!< maker of the device : \li 0xEC : Samsung, \li 0x98 : Toshiba, \li 0x01 : AMD, \li 0x04 : Fujitsu. */
    unsigned long DeviceType;						/*!< type of the device : \li 1 : 1M, \li 2 : 2M, \li 4 : 4M, \li 8 : 8M, \li 16 : 16M, \li 32:32M \n ...bytes  */
    unsigned long SizeFlash;						/*!< Size of the Flash. */
    unsigned long PagesBlock;						/*!< Count of pages in a block. */
    unsigned long SizeBlock;						/*!< Size of a block. */
    unsigned long BadBlockNb;						/*!< Bad block count. */
} S_FS_DIAG;

/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @brief This function creates a volume or a disk. 
 *
 * It creates, initialises and formats a volume.
 * @param ParamCreat : pointer on volume parameter structure.
 * @param Size : Input/output parameter. 
 *
 * Size returns volume size in bytes ( 1Kb multiple ). 
 *
 * For flash FS_WRITEONCE mode, this size is only used to compute FS_dskfree return value. 
 * The disk in flash is only limited by the size of the flash but not by this parameter. 
 * Size_P must comply with the following values : 
 *
 * - FS_WRITEONCE |  Min value: Flash block size |  Max value : Flash area size 
 * - FS_WRITEMANY |  Min value: 4 Kb             |  Max value : Free RAM size 
 *
 * @return 
 * - FS_OK if successfull, volume ready to be used 
 * - FS_NAMEUSED : volume name already used 
 * - FS_NOMEM no more space available in Flash, return the size still available in Size 
 * - FS_KO other errors 
 *
 * @note Call this function prior using files.
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_dskcreate:KSFAM_FFMS:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:2:ONE_POINTER 
// \endif
int             FS_dskcreate(S_FS_PARAM_CREATE *ParamCreat, unsigned long *Size);


/*! @brief This function kills a volume. It suppresses a volume.
 * @param DiskPath : '/' followed by volume name
 * @return 
 * - FS_OK if successful 
 * - FS_NOACCESS if the application does not have the access rights 
 * - FS_DSKUSED if the volume is still mounted (unmount it before) 
 * - FS_KO other errors .
 *
 * @note 
 * - FS_unmount must be called prior killing disk. 
 * - This routine can only be used by the application that created the volume .
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_dskkill:KSFAM_FFMS:
// \endif
int             FS_dskkill(const char *DiskPath);


/*! @brief This function initializes the context of the volume with disk name.
 * @param DiskPath : '/' followed by volume name
 * @param AccessMode : access mode. Tells authorized access for the application that performs mount operation.
 * @return If successful, returns : 
 * - FS_OK if volume is ready to be used 
 * - FS_NOFORMAT if volume is not formatted yet 
 *
 * On error, returns : 
 * - FS_KO if the setting has failed for any other reason
 * - FS_NOACCESS if application does not have the access rights 
 * - mode : FS_WRITEONCE or FS_WRITEMANY is returned
 *
 * @note 
 * - Volume must be created prior calling this function. Files related to this volume can not be manipulated prior calling this function. 
 * - This routine must be called prior formatting the disk. 
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_mount:KSFAM_FFMS:
//  @GSIM_A:2:ONE_POINTER
// \endif
int             FS_mount(const char *DiskPath, unsigned int *AccessMode);


/*! @brief This function deactivates a volume. 
 *
 * It releases resources linked to the volume by its disk name.
 * @param DiskPath : '/' followed by volume name
 * @return 
 * - FS_OK If successful 
 * - FS_KO other errors 
 * - FS_NOACCESS if application does not have the access rights
 * - FS_FILEUSED if files are still open
 *
 * @note After calling FS_unmount, files linked to the volume are no more accessible.
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_unmount:KSFAM_FFMS:
// \endif
int             FS_unmount(const char *DiskPath);


/*! @brief This function formats a volume. 
 *
 * It erases all files on disk and creates the tree structure.
 * @param DiskPath : ‘/' followed by volume name.
 * @param AccessMode : access mode from other applications for the volume 
 * - FS_NOFLAGS (no access) 
 * - FS_RONLYMOD (read only ) 
 * - FS_WRTMOD (read/write) 
 *
 * @param NbFichierMax_P : maximum files number into the volume (Future use reserved).
 * @return 
 * - FS_OK if successful
 * - FS_NOFORMAT volume is not formatted 
 * - FS_NOACCESS if application does not have the access rights
 * - FS_KO other errors 
 *
 * @note 
 * - The disk cannot be formatted if some flows are opened on files. 
 * - This routine can only be called from the application that creates the volume.
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_format:KSFAM_FFMS:
// \endif
int             FS_format(const char *DiskPath, unsigned int AccessMode, unsigned int NbFichierMax_P);



/*! @brief This function reads the volume access mode. 
 *
 * It reads the access rights for this volume.
 * @param DiskPath : '/' followed by volume name
 * @return access rights 
 * - FS_NOFLAGS (no access)
 * - FS_RONLYMOD (read only) 
 * - FS_WRTMOD (read/write) 
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_readmode:KSFAM_FFMS:
// \endif
unsigned int    FS_readmode(const char *DiskPath);


/*! @brief This function changes file access mode. 
 *
 * It changes the access permission for a specified file, only if new mode is more restricted than current mode.
 * @param path : full file path 
 * @param AccessMode : access rights 
 * - FS_NOFLAGS (no access) 
 * - FS_RONLYMOD (read only)
 * - FS_WRTMOD (read/write) 
 *
 * @return 
 * - FS_OK if successfull 
 * - FS_KO other errors 
 * - FS_NOACCESS if application does not have the access rights 
 *
 * @note This routine can only be called from the application that has created the volume.
 *
 * @note For Telium I old file system (without directories) this function was used for changing disk access mode
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_chgmode:KSFAM_FFMS:
// \endif
int             FS_chgmode (const char *path, unsigned int AccessMode);



/*! @brief This function provides the size of the volume. 
 *
 * It returns the volume size in bytes.
 * @param DiskPath : '/' followed by volume name
 * @return 
 * - size in bytes if successful 
 * - FS_ERROR on error 
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_dsksize:KSFAM_FFMS:
// \endif
long            FS_dsksize (const char *DiskPath);


/*! @brief This function provides the quantity of free memory on the volume. 
 *
 * It returns the number of available bytes on the volume.
 *
 * free size = disk size ' used space. 
 * In flash, FS_dsksize returns zero if used space exceeds disk size. 
 * @param DiskPath : '/' followed by volume name
 * @return 
 * - number of free bytes if successful .
 * - FS_ERROR on error .
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_dskfree:KSFAM_FFMS:
// \endif
long            FS_dskfree (const char *DiskPath);


/*! @brief This function lists the number of disks.
 * @param NbDisk : disk number.
 * @param InfoContext : array.
 * @return None.
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_dsklist:KSFAM_FFMS:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:2:ONE_POINTER
// \endif
void            FS_dsklist (unsigned int *NbDisk, S_FS_INFO_CONTEXT *InfoContext);



/*! @brief This function opens a flow on a directory, or files to read files information.
 * @param FilePattern : contains '/volume name/' followed by a file(s) pattern to obtain files information . 
 *
 * - The standard wildcard '*' can be used to replace some characters ,
 * - "/mydisk/f*.txt" or "/mydisk/file?.txt" to replace any character in the file pattern , 
 * - "/mydisk/myfile.txt" specifies entirely the filename ,
 * - "/mydisk/" list all files on the disk 'mydisk' 
 *
 * @return 
 * - If successful, returns a pointer on a directory or files flow that can be used by the function FS_readdir .
 * - In case of error, returns a NULL pointer. 
 *
 * @note 
 * - The structure S_FS_DIR does not contain accessible fields from the user. 
 * - Several flows can be opened at the same time. 
 * - Files of the directory can be manipulated (deletion) while a flow is opened. 
 * - This routine can only be called from application that has rights on the volume. 
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_opendir:KSFAM_FFMS:
//  @GSIM_A:0:ONE_ADDRESS
// \endif
S_FS_DIR*       FS_opendir (const char *FilePattern);


/*! @brief This function reads information on a file. 
 *
 * It read files information (name, creation date, size) matching with the file pattern passed to FS_opendir from the directory.
 *
 * Each time FS_readdir is called next file information from the directory is provided as far as it matches file pattern criteria. 
 * @param Directory : pointer on the directory flow.
 * @param InfoFile  : pointer to each file entry.
 * @return 
 * - If successful, returns FS_OK. 
 * - In case of error, returns FS_KO .
 *
 * @note The information provided will be overwritten by the next call. This is not the case with 2 consecutives calls of the function on a different flow. 
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_readdir:KSFAM_FFMS:
//  @GSIM_A:1:ONE_ADDRESS
//  @GSIM_A:2:ONE_POINTER
// \endif
int             FS_readdir (S_FS_DIR *Directory, S_FS_FILEINFO *InfoFile);


/*! @brief FS_closedir closes a flow of an opened directory by FS_opendir.
 * @param Directory : pointer on the flow.
 * @return None.
 * @note see also FS_readdir.
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_closedir:KSFAM_FFMS:
//  @GSIM_A:1:ONE_ADDRESS
// \endif
void            FS_closedir(S_FS_DIR *Directory);



/*! @brief This function renames a file. 
 *
 * It renames a file with filename 'OldName' to 'NewName'.
 * @param OldName including path : /volumename/old filename.
 * @param NewName including path : /volumename/new filename.
 * @return 
 * - FS_OK If successful ;
 * - FS_KO error .
 * - FS_NOACCESS if the application does not have the access rights .
 *
 * @note 
 * - Volume name cannot be changed while filename is renamed. 
 * - This routine can only be called from the application that creates the volume 
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_rename:KSFAM_FFMS:
// \endif
int             FS_rename(const char *OldName, const char *NewName);


/*! @brief This function erases a file. 
 *
 * It erases a file, it cannot be used any more.
 * @param FileName : concatenation '/' 'volume name' '/' and filename . Example : ' /mydisk/myfile ' 
 * @return 
 * - FS_OK If successful .
 * - FS_KO error .
 * - FS_NOACCESS if the application does not have the access rights .
 * - FS_FILEUSED if the file is being used. 
 *
 * @note This routine can only be called from the application that creates the volume.
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_unlink:KSFAM_FFMS:
// \endif
int             FS_unlink (const char *FileName);


/*! @brief This function tests the existence of the file. 
 *
 * It checks if the file exists
 * @param FileName : concatenation '/' 'volume name' '/' and filename . Example : ' /mydisk/myfile ' 
 * @return 
 * - FS_OK If the file exists .
 * - FS_KO error .
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_exist:KSFAM_FFMS:
// \endif
int             FS_exist (const char *FileName);



/*! @brief This function opens a file and associates it to a flow and return a pointer to that flow : the file handle .
 * @param FileName : concatenation of '/''volume name''/' and filename .
 * 
 * @b Example : '/mydisk/myfile' 
 * @param OpenMode : file open mode.
 *
 * - r open an existing file in reading. 
 *   r mode is allowed for FLASH disk and RAM disk.
 *
 * - r+ open an existing file in updating mode (read and write). File cursor is set to 0.
 *   With r+ mode writing is allowed everywhere, even at the end of the file (append mode)
 *   r+ mode is allowed for FLASH disk and RAM disk.
 *
 * - w open an existing file in writing. 
 *   w mode is forbidden for FLASH disk and allowed for RAM disk . 
 *
 * - w+ create a file or delete its content if the file exist. In both cases, the file is open in writing.
 *   w+ mode is forbidden for FLASH disk and allowed for RAM disk . 
 *
 * - a create or open an existing file in writing but only from the end of file. 
 *   a mode is allowed for FLASH disk and RAM disk.
 *
 * @return 
 * - If successful, returns a pointer to the file handle .
 * - In case of error, returns a NULL pointer .
 *
 * @note For FLASH disk, the following code sample does not work because rewriting is used in not flushed data : 
 * - FS_unlink(TEST_FILE); ensure we are creating a new file 
 * - file = FS_open(TEST_FILE, 'r+'); open for read and write 
 * - FS_write(MESSAGE_1, 1, sizeof(MESSAGE_1), file); 
 * - FS_seek(file, 0, FS_SEEKSET); 
 * - FS_write(MESSAGE_2, 1, sizeof(MESSAGE_2), file); file contains MESSAGE_1+MESSAGE_2 
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_open:KSFAM_FFMS:
//  @GSIM_A:0:ONE_ADDRESS
// \endif
S_FS_FILE*      FS_open(const char *FileName, const char *OpenMode);


/*! @brief This function closes a flow on a file.
 * @param File : pointer to the file handle.
 * @return 
 * - If successful, returns FS_OK 
 * - In case of error, returns FS_KO 
 *
 * @note When closing file, automatic flushing operation is done (writing 512 bytes bloc of data from the data buffer to the file) .
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_close:KSFAM_FFMS:
//  @GSIM_A:1:ONE_ADDRESS
// \endif
int             FS_close (S_FS_FILE *File);


/*! @brief This function reads the data in a flow. 
 * 
 * It reads a number NbOfElement of objects of size 'Size' ( in bytes ) into the file handle File.
 * @param Buffer : pointer to a buffer (declared by the caller).
 * @param Size : object size.
 * @param NbOfElement : number of objects.
 * @param File : pointer to the file handle.
 * @return 
 * - If successful, returns the number of expected objects NbOfElement to be read. 
 * - In case of error, returns a number of objects really read (=< NbOfElement).
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_read:KSFAM_FFMS:
//  @GSIM_S:FS_read:E_FS_read
//  1:DATA_CODE(Size * NbOfElement)
//  4:ONE_ADDRESS
// \endif
int				      FS_read (void *Buffer, int Size, int NbOfElement, S_FS_FILE *File);


/*! @brief This function writes in a flow to a file. 
 *
 * It writes a number NbOfElement of objects of size 'Size'( in bytes ) into the file handle File
 * @param Buffer : pointer to a buffer (declared by the caller).
 * @param Size : object size.
 * @param NbOfElement : number of objects.
 * @param File : pointer to the file handle.
 * @return 
 * - If successful, returns the number of expected objects written (NbOfElement) . 
 * - In case of error, returns a number of objects written (=< NbOfElement) 
 *
 * @note 
 * - Data are buffered, FFMS waits to have at least 512 bytes ready to be  written onto the Flash. 
 * - This buffer belongs to the structure of the file handle. This particular mechanism can be avoided by using the function FS_flush. 
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_write:KSFAM_FFMS:
//  @GSIM_S:FS_write:E_FS_write
//  1:DATA_CODE(Size * NbOfElement)
//  1:IN_ONLY
//  4:ONE_ADDRESS
// \endif
int             FS_write (const void *Buffer, int Size, int NbOfElement, S_FS_FILE *File);


/*! @brief This function flushes buffered data to a file. 
 *
 * It forces writing data of a buffer associated to a flow. A maximum of 2048 bytes can be waiting in a buffer .
 * @param File : pointer on the flow.
 * @return Number of bytes written (0 to 2048).
 * @note Useful only if FS_WRITEONCE.
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_flush:KSFAM_FFMS:
//  @GSIM_A:1:ONE_ADDRESS
// \endif
int    			    FS_flush (S_FS_FILE *File);


/*! @brief This routine allows to truncate a file at the current position.
 *
 * FS_trunc only works in RAM memory. Flash is not supported, function returns always FS_KO
 * @param File : pointer to structure S_FS_FILE.
 * @return
 * - FS_OK
 * - error otherwise.
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_trunc:KSFAM_FFMS:
//  @GSIM_A:1:ONE_ADDRESS 
// \endif
int             FS_trunc (S_FS_FILE *File);


/*! @brief This function gives the length of a file. 
 *
 * It returns the length in bytes of the opened file.
 * @param File : pointer on the flow.
 * @return 
 * - If successful, returns the length in bytes .
 * - In case of error, returns FS_ERROR .
 *
 * @note The function does not change the position of the cursor associated to the flow 
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_length:KSFAM_FFMS:
//  @GSIM_A:1:ONE_ADDRESS
// \endif
long   FS_length (S_FS_FILE *File);


/*! @brief This function provides the size actually used by a file. 
 *
 * It gives the RAM or FLASH memory actually used by a file.
 * @param File : pointer on the flow.
 * @return Memory used in bytes.
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_StorageSize:KSFAM_FFMS:
//  @GSIM_A:1:ONE_ADDRESS
// \endif
unsigned long   FS_StorageSize (S_FS_FILE *File) ;


/*! @brief This function positions the cursor associates with a flow. 
 *
 * It places the cursor associated to a flow to the position Offset from the reference Whence. 
 * @param File : pointer on the flow.
 * @param Offset : difference in bytes between whence and the new position.
 * @param Whence  : can take 3 values : 
 * - FS_SEEKSET ( file beginning) 
 * - FS_SEEKCUR (current position) 
 * - FS_SEEKEND (end of file) 
 *
 * @return 
 * - FS_OK If successful.
 * - FS_KO error.
 * @note 
 * - It is impossible to put the cursor after the end of file (Offset > 0 from FS_K_SEEKEND) or before the beginning of file (Offset < 0 from FS_K_SEEKSET). 
 * - In both cases, the position is forced respectively to the 'end of file' and 0. 
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_seek:KSFAM_FFMS:
//  @GSIM_A:1:ONE_ADDRESS
// \endif
int             FS_seek (S_FS_FILE *File, long Offset, int Whence);


/*! @brief This function provides the current position of the cursor associated to a flow. 
 * 
 * It returns the current position of the cursor associated to.
 * @param File : pointer on the flow.
 * @return position of the cursor
 * @note The position is relative to the beginning the file.
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_tell:KSFAM_FFMS:
//  @GSIM_A:1:ONE_ADDRESS
// \endif
unsigned long   FS_tell (S_FS_FILE *File);


/*! @brief This function tests the end of a file. 
 *
 * It checks the end of a file by using the flow.
 * @param File : pointer on the flow.
 * @return 
 * - If successful, returns a value different from 0 
 * - In case of error, returns FS_KO ( end of file not reached ) 
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_eof:KSFAM_FFMS:
//  @GSIM_A:1:ONE_ADDRESS
// \endif
int             FS_eof (S_FS_FILE *File);



/*! @brief This function compacts an area of flash. 
 *
 * The garbage collector groups used, flashes pages together and physically erases logically erased pages. Calling this function avoids automatic garbage collection.
 * @param Area : flash area to compact (use FS_WO_ZONE_DATA). See parameter IdentZone of FS_dskcreate function.
 * @return 
 * - FS_OK If successful 
 * - FS_KO if error 
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_GarbageCollection:KSFAM_FFMS:
// \endif
int             FS_GarbageCollection  (unsigned int Area);


/*! @brief FThis function flashes Information.
 *
 * It retrieves flash memory informations.
 * @param Diag : flash informations.
 * @return None
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_Diag:KSFAM_FFMS:
//  @GSIM_A:1:ONE_POINTER
// \endif
void		 	      FS_Diag(S_FS_DIAG* Diag);


/*! @brief This routine returns the size of flash area.
 * @param area : identifies the area. cf defines in fs.h.
 * @return The size of the area in bytes.
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_AreaGetSize:KSFAM_FFMS:
// \endif
int             FS_AreaGetSize(unsigned int area );


/*! @brief This function returns the free size of a flash area. 
 * @param area : identifies the area. cf defines in fs.h.
 * @return The size of the available area in bytes.
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_AreaGetFreeSize:KSFAM_FFMS:
// \endif
int             FS_AreaGetFreeSize(unsigned int area );


/*! @brief This routine returns the size of the clearable data in the area of a flash. 
 *
 * The data will be freed at automatic garbage collector or launched by FS_GarbageCollection.
 * @param area : identifies the area. cf defines in fs.h.
 * @return The size of the clearable data in bytes.
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_AreaGetGarbageSize:KSFAM_FFMS:
// \endif
int             FS_AreaGetGarbageSize(unsigned int area );



/*! @brief This routine creates a directory in a flash disk.
 * @param path : path of the directory to make.
 * @return FS_OK if ok.
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_mkdir:KSFAM_FFMS:
// \endif
int             FS_mkdir(const char *path);


/*! @brief This routine suppresses a directory in a flash disk. 
 * @param path : path of the directory to remove.
 * @return FS_OK if OK.
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_rmdir:KSFAM_FFMS:
// \endif
int             FS_rmdir(const char *path);



/*! @brief This function resizes application area. 

 * @warning <b>This function is to use with extreme caution.\n Be aware that, when two, or more, applications call this function, only the last parametrization of disk size is kept.</b>

 * @param old_size : 	current size of the APPLICATION area in bytes (value returned by FS_AreaGetSize(FS_WO_ZONE_APPLICATION))
 * @param new_size : new size of the APPLICATION area in bytes.
 * @return FS_OK if OK.
 * @warning Mapping Memory : 
 *  
 *	<table border=1>
		<tr>
    <th></th><th></th><th></th><th></th><th><th></th>
    <th></th><th></th><th></th></th><th></th><th></th>
    <th></th><th>Application Area Size</th><th></th><th></th><th></th><th></th><th></th><th>Data Area Size</th><th></th><th></th><th></th><th></th><th></th><th></th><th></th></tr> 
		</table>
	<table border=1>
		<tr><td>Flash Size</td><td>Default</td><td>Min</td><td>Max</td><td>default</td><td>Min</td><td>Max</td></tr>
		<tr><td>8 MB</td><td>4 MB</td><td>3.5 MB</td><td>6 MB</td><td>4 MB</td><td>2 MB</td><td>4.5 MB</td></tr>
		<tr><td>16 MB</td><td>6 MB</td><td>5.5 MB</td><td>13 MB</td><td>10 MB</td><td>3 MB</td><td>10.5 MB</td></tr>
		<tr><td>32 MB</td><td>6 MB</td><td>5.5 MB</td><td>24 MB</td><td>24 MB</td><td>8 MB</td><td>26.5 MB</td></tr>
		<tr><td>64 MB</td><td>8 MB</td><td>7.5 MB</td><td>48 MB</td><td>56 MB</td><td>16 MB</td><td>56.5 MB</td></tr>
		<tr><td>128 MB</td><td>8 MB</td><td>8 MB</td><td>96 MB</td><td>120 MB</td><td>32 MB</td><td>120 MB</td></tr>
		<tr><td>256 MB</td><td>8 MB</td><td>8 MB</td><td>192 MB</td><td>248 MB</td><td>64 MB</td><td>248 MB</td></tr>
		<tr><td>512 MB</td><td>8 MB</td><td>8 MB</td><td>384 MB</td><td>504 MB</td><td>128 MB</td><td>504 MB</td></tr>
	</table>
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FS_NandRemap:KSFAM_FFMS:
// \endif
int FS_NandRemap(unsigned long old_size, unsigned long new_size);



#endif

/*! @}  */ 

