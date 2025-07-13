/*! @addtogroup KSFAM_OK
	* @{
 */ 

// cpp_e.h
// enable cpp definition
//

#ifdef __cplusplus
extern "C" {
#endif

// Prohibit the inclusion of file ctype.h from SDK
#define _CTYPE_H								

/*
======================================================================
			Some Telium system calls and data types
			must be redefined for posix compatibility
======================================================================
*/
#define	fclose	eft_fclose			/*!< redefine the function fclose in order not to interfere with the same function of the POSIX library */
#define	fopen	eft_fopen			/*!< redefine the function fopen in order not to interfere with the same function of the POSIX library */
#define	fread	eft_fread			/*!< redefine the function fread in order not to interfere with the same function of the POSIX library */
#define	fwrite	eft_fwrite			/*!< redefine the function fwrite in order not to interfere with the same function of the POSIX library */
#define	clearerr	eft_clearerr	/*!< redefine the function clearerr in order not to interfere with the same function of the POSIX library */
#define	ferror	eft_ferror			/*!< redefine the function ferror in order not to interfere with the same function of the POSIX library */
#define	getc	eft_getc			/*!< redefine the function getc in order not to interfere with the same function of the POSIX library */
#define	vsprintf	eft_vsprintf	/*!< redefine the function vsprintf in order not to interfere with the same function of the POSIX library */
#define	fgets	eft_fgets			/*!< redefine the function fgets in order not to interfere with the same function of the POSIX library */
#define	fputc	eft_fputc			/*!< redefine the function fputc in order not to interfere with the same function of the POSIX library */
#define	fputs	eft_fputs			/*!< redefine the function fputs in order not to interfere with the same function of the POSIX library */
#define	putc	eft_putc			/*!< redefine the function putc in order not to interfere with the same function of the POSIX library */

#define	fork	eft_fork			/*!< redefine the function fork in order not to interfere with the same function of the POSIX library */
#define	kill	eft_kill			/*!< redefine the function kill in order not to interfere with the same function of the POSIX library */
#define	shutdown	eft_shutdown	/*!< redefine the function shutdown in order not to interfere with the same function of the POSIX library */
#define	fbreak	eft_fbreak			/*!< redefine the function fbreak in order not to interfere with the same function of the POSIX library */
#define	mount	eft_mount			/*!< redefine the function mount in order not to interfere with the same function of the POSIX library */
#define	unmount	eft_unmount			/*!< redefine the function unmount in order not to interfere with the same function of the POSIX library */
#define	opendir	eft_opendir			/*!< redefine the function opendir in order not to interfere with the same function of the POSIX library */
#define	readdir	eft_readdir			/*!< redefine the function readdir in order not to interfere with the same function of the POSIX library */
#define	telldir	eft_telldir			/*!< redefine the function telldir in order not to interfere with the same function of the POSIX library */
#define	seekdir	eft_seekdir			/*!< redefine the function seekdir in order not to interfere with the same function of the POSIX library */
#define	rewinddir	eft_rewinddir	/*!< redefine the function rewinddir in order not to interfere with the same function of the POSIX library */
#define	closedir	eft_closedir	/*!< redefine the function closedir in order not to interfere with the same function of the POSIX library */
#define	mkdir	eft_mkdir			/*!< redefine the function mkdir in order not to interfere with the same function of the POSIX library */
#define	rmdir	eft_rmdir			/*!< redefine the function rmdir in order not to interfere with the same function of the POSIX library */
#define	open	eft_open			/*!< redefine the function open in order not to interfere with the same function of the POSIX library */
#define	close	eft_close			/*!< redefine the function close in order not to interfere with the same function of the POSIX library */
#define	unlink	eft_unlink			/*!< redefine the function unlink in order not to interfere with the same function of the POSIX library */
#define	read	eft_read			/*!< redefine the function read in order not to interfere with the same function of the POSIX library */
#define	write	eft_write			/*!< redefine the function write in order not to interfere with the same function of the POSIX library */
#define	lseek	eft_lseek			/*!< redefine the function lseek in order not to interfere with the same function of the POSIX library */
#define	stat	eft_stat			/*!< redefine the function stat in order not to interfere with the same function of the POSIX library */
#define	fstat	eft_fstat			/*!< redefine the function fstat in order not to interfere with the same function of the POSIX library */
#define	chmod	eft_chmod			/*!< redefine the function fstat in order not to interfere with the same function of the POSIX library */
#define	fchmod	eft_fchmod			/*!< redefine the function fchmod in order not to interfere with the same function of the POSIX library */

// Missing functions or types. To be removed from oem_vfs.h
#define mkfifo  eft_mkfifo			/*!< redefine the function mkfifo in order not to interfere with the same function of the POSIX library */
#define umask   eft_umask			/*!< redefine the function umask in order not to interfere with the same function of the POSIX library */
#define	intptr	eft_intptr_t		/*!< redefine the function intptr in order not to interfere with the same function of the POSIX library */
#define	uintptr	eft_uintptr_t		/*!< redefine the function uintptr in order not to interfere with the same function of the POSIX library */


#define	rename	eft_rename			/*!< redefine the function rename in order not to interfere with the same function of the POSIX library */
#define	fioctl	eft_fioctl			/*!< redefine the function fioctl in order not to interfere with the same function of the POSIX library */
#define	ungetc	eft_ungetc			/*!< redefine the function ungetc in order not to interfere with the same function of the POSIX library */
#define	vfs_truncate	eft_vfs_truncate		/*!< redefine the function vfs_truncate in order not to interfere with the same function of the POSIX library */
#define	vfs_ftruncate	eft_vfs_ftruncate		/*!< redefine the function vfs_ftruncate in order not to interfere with the same function of the POSIX library */
#define	vfs_statfs	eft_vfs_statfs				/*!< redefine the function vfs_statfs in order not to interfere with the same function of the POSIX library */
#define	vfs_fstatfs	eft_vfs_fstatfs				/*!< redefine the function vfs_fstatfs in order not to interfere with the same function of the POSIX library */

#define	FILE	eft_FILE			/*!< redefine the type FILE in order not to interfere with the same type of the POSIX library */
#define	DIR		eft_DIR				/*!< redefine the type DIR in order not to interfere with the same type of the POSIX library */
#define	stat	eft_stat			/*!< redefine the type stat in order not to interfere with the same type of the POSIX library */
#define	timespec	eft_timespec	/*!< redefine the type timespec in order not to interfere with the same type of the POSIX library */
#define	daddr_t	eft_daddr_t			/*!< redefine the type daddr_t in order not to interfere with the same type of the POSIX library */
#define	ino_t	eft_ino_t			/*!< redefine the type ino_t in order not to interfere with the same type of the POSIX library */
#define	uid_t	eft_uid_t			/*!< redefine the type uid_t in order not to interfere with the same type of the POSIX library */
#define	gid_t	eft_gid_t			/*!< redefine the type gid_t in order not to interfere with the same type of the POSIX library */
#define	mode_t	eft_mode_t			/*!< redefine the type mode_t in order not to interfere with the same type of the POSIX library */
#define	_ctype_	eft__ctype_			/*!< redefine the type _ctype_ in order not to interfere with the same type of the POSIX library */

/* eft30cpp fuctions */
#define fprintf  eft_fprintf		/*!< redefine the function fprintf in order not to interfere with the same function of the POSIX library */
#define vprintf  eft_vprintf		/*!< redefine the function vprintf in order not to interfere with the same function of the POSIX library */
#define sprintf  eft_sprintf		/*!< redefine the function sprintf in order not to interfere with the same function of the POSIX library */
#define printf   eft_printf			/*!< redefine the function printf in order not to interfere with the same function of the POSIX library */
#define pprintf  eft_pprintf		/*!< redefine the function pprintf in order not to interfere with the same function of the POSIX library */
#define putchar  eft_putchar		/*!< redefine the function putchar in order not to interfere with the same function of the POSIX library */
#define puts     eft_puts			/*!< redefine the function puts in order not to interfere with the same function of the POSIX library */

#define getdate eft_getdate			/*!< redefine the function getdate in order not to interfere with the same function of the POSIX library */

#define ftruncate eft_ftruncate /*!< redefine the function ftruncate in order not to interfere with the same function of the POSIX library */

/*! @}  */ 

