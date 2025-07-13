#ifndef __DISK_H__INCLUDED__
#define __DISK_H__INCLUDED__

/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define EMVCOMM_DISK_LABEL						"EMVCOMM"

#define EMVCOMM_DISK_MODE						FS_WRITEONCE
#define EMVCOMM_DISK_ACCESS_MODE				FS_WRTMOD
#define EMVCOMM_DISK_MAX_NUM_OF_FILES			1
#define EMVCOMM_DISK_ZONE						FS_WO_ZONE_DATA
#define EMVCOMM_DISK_SIZE						1024

#define Disk_OpenEmvCommDisk()					Disk_Open(EMVCOMM_DISK_LABEL, EMVCOMM_DISK_MODE, EMVCOMM_DISK_ACCESS_MODE, EMVCOMM_DISK_MAX_NUM_OF_FILES, EMVCOMM_DISK_ZONE, EMVCOMM_DISK_SIZE)
#define Disk_CloseEmvCommDisk()					Disk_Unmount(EMVCOMM_DISK_LABEL)

/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

int Disk_Mount(const char* szDisk);
int Disk_Unmount(const char* szDisk);

int Disk_Create(const char* szDisk, int nMode, int nAccessMode, int nMaxNumOfFiles, int nZone, unsigned long ulDiskSize);
int Disk_Kill(const char* szDisk);

int Disk_Open(const char* szDisk, int nMode, int nAccessMode, int nMaxNumOfFiles, int nZone, unsigned long ulDiskSize);

#endif // __DISK_H__INCLUDED__
