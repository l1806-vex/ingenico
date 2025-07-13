/*! @addtogroup KSFAM_VFS
	* @{
 */ 

#ifndef VFS_H
#define VFS_H


/*
======================================================================
			Data Structures Definition
======================================================================
*/


// From <machine/ansi.h>

/*! @brief Definitions of the types for msdosfs. Extracted from the unix FreeBSD/NetBSD includes. */
typedef int			ssize_t;

/*! @brief Definitions of the types for msdosfs (__int64_t is a long). Extracted from the unix FreeBSD/NetBSD includes. */
typedef long		off_t;

// From <machine/param.h>

#define DEV_BSHIFT	9		/* log2(DEV_BSIZE) */
#define DEV_BSIZE	(1<<DEV_BSHIFT)

// From <sys/inttypes.h>

/*! @brief Definitions of the types for msdosfs(__intptr_t is an int). Extracted from the unix FreeBSD/NetBSD includes.  */
typedef	int	intptr_t;

/*! @brief Definitions of the types for msdosfs (__uintptr_t is an unsigned int). Extracted from the unix FreeBSD/NetBSD includes.  */
typedef	unsigned int	uintptr_t;

// From <sys/types.h>

/*! @brief Definitions of the types (quads) for msdosfs (u_quad_t is an unsigned long). Extracted from the unix FreeBSD/NetBSD includes.  */
typedef	unsigned long	u_quad_t;	/*!< quads */

/*! @brief Definitions of the types (quads) for msdosfs (quad_t is a long). Extracted from the unix FreeBSD/NetBSD includes.  */
typedef	long		quad_t;

/*! @brief Definitions of the types (quads) for msdosfs (qaddr_t is a long).  Extracted from the unix FreeBSD/NetBSD includes.  */
// \if SIMULATION
//  @GSIM_T:qaddr_t:SUPPLIED(BUF_SER_qaddr_t;BUF_DES_qaddr_t)
// \endif
typedef	quad_t *	qaddr_t;

/*! @brief Definitions of the types (group id) for msdosfs (gid_t is a unsigned int). Extracted from the unix FreeBSD/NetBSD includes.  */
typedef	unsigned int	gid_t;			/*!< group id */


/*! @brief Definitions of the types (user id) for msdosfs (uid_t is a unsigned int). Extracted from the unix FreeBSD/NetBSD includes.  */
typedef	unsigned int	uid_t;			/*!< user id */


/*! @brief Definitions of the types (permission) for msdos file system (mode_t is a unsigned short). Extracted from the unix FreeBSD/NetBSD includes.  */
typedef	unsigned short	mode_t;		/*!< permissions */


/*! @brief Definitions of the types ( link count) for msdosfs (nlink_t is a unsigned short). Extracted from the unix FreeBSD/NetBSD includes.  */
typedef	unsigned short	nlink_t;	/*!< link count */

/*! @brief Definitions of the types (core address) for msdosfs. Extracted from the unix FreeBSD/NetBSD includes.  */
typedef	char *		caddr_t;	/*!< core address */


/*! @brief Definitions of the types (disk address) for msdosfs (daddr_t is an int). Extracted from the unix FreeBSD/NetBSD includes.  */
typedef	int		daddr_t;			/*!< disk address */


struct specinfo;

//#ifndef udev_t
//typedef	unsigned int	udev_t;		/*!< device number */
//typedef struct specinfo	*dev_t;
//#endif
 
/*! @brief Definitions of the types (inode number) for msdosfs (ino_t is an int). Extracted from the unix FreeBSD/NetBSD includes.  */
typedef	unsigned int	ino_t;		/*!< inode number */


// From <sys/types.h>

#define	PATH_MAX		1024	/*!< max bytes in pathname */
#define	NGROUPS			16		/*!< max number groups */


// From <sys/time.h>

#define tz_minuteswest	0		/*!< Minutes west of GMT.  */
#define	wall_cmos_clock	0		/*!< time to be adjusted */
#define adjkerntz		0		/*!< adjust time */


#ifndef _TIMESPEC_DECLARED
#define NG_TIMEVAL
#define _TIMESPEC_DECLARED

/*! @brief Definitions of the types (time value) for msdosfs.  Extracted from the unix FreeBSD/NetBSD includes.  */
struct timeval {
	long	tv_sec;							/*!< seconds */
	long	tv_usec;						/*!< microseconds */
};

/*! @brief Definitions of the types (time) for msdosfs. Extracted from the unix FreeBSD/NetBSD includes.  */
struct timespec {
	unsigned int	tv_sec;					/*!< seconds */
	long			tv_nsec;				/*!< nanoseconds */
};
#endif

// From <sys/dirent.h>

/*! @brief Definitions of the types for msdosfs (int32_t is an int). Extracted from the unix FreeBSD/NetBSD includes.  */
struct dirent{
	unsigned int	d_fileno;				/*!< file number of entry (unsigned int). */
	unsigned short	d_reclen;				/*!< length of this record (unsigned short). */
	unsigned char	d_type;					/*!< file type, see below (unsigned char). */
	unsigned char	d_namlen;				/*!< length of string in d_name (unsigned char). */
#define	MAXNAMLEN	255						/*!< Max name length */
	char		d_name[MAXNAMLEN + 1];		/*!< name of the file (must be no longer than MAXNAMLEN). */
};

#define	DT_DIR		 4		/*!< Folder type */
#define	DT_REG		 8		/*!< Regular file type */

#define	GENERIC_DIRSIZ(dp) \
    ((sizeof (struct dirent) - (MAXNAMLEN+1)) + (((dp)->d_namlen+1 + 3) &~ 3))		/*!< Size of directory entry */

/*! @brief Definitions of the types (directory) for msdosfs. Extracted from the unix FreeBSD/NetBSD includes.  */
#ifdef _GSIM_ 
typedef void DIR;
#else
typedef struct __dirstream DIR;
#endif

// From <sys/errno.h>
#ifndef _SIMULPC_
#define errno * errno_p()
#endif

#define	EPERM		1		/*!< Operation not permitted */
#define	ENOENT		2		/*!< No such file or directory */
#define	EIO			5		/*!< Input/output error */
#define	E2BIG		7		/*!< Argument list too long */
#define	EBADF		9		/*!< Bad file descriptor */
#define	ENOMEM		12		/*!< Cannot allocate memory */
#define	EBUSY		16		/*!< Device busy */
#define	EEXIST		17		/*!< File exists */
#define	EXDEV		18		/*!< Cross-device link */
#define	ENODEV		19		/*!< Operation not supported by device */
#define	ENOTDIR		20		/*!< Not a directory */
#define	EISDIR		21		/*!< Is a directory */
#define	EINVAL		22		/*!< Invalid argument */
#define	EMFILE		24		/*!< Too many open files */
#define	EFBIG		27		/*!< File too large */
#define	ENOSPC		28		/*!< No space left on device */
#define	EROFS		30		/*!< Read-only file system */

#define	EOPNOTSUPP	45		/*!< Operation not supported */

#define	ENOTEMPTY	  66		/*!< Directory not empty */

// From <sys/stat.h>
//#define __dev_t	udev_t

#ifndef _POSIX_SOURCE
/*! @brief Definitions of the types for msdosfs. Extracted from the unix FreeBSD/NetBSD includes.  */
struct ostat {
	unsigned short st_dev;						/*!< inode's device */
	ino_t	  st_ino;							/*!< inode's number */
	mode_t	  st_mode;							/*!< inode protection mode */
	nlink_t	  st_nlink;							/*!< number of hard links */
	unsigned short st_uid;						/*!< user ID of the file's owner */
	unsigned short st_gid;						/*!< group ID of the file's group */
	unsigned short st_rdev;						/*!< device type */
	int	  st_size;								/*!< file size, in bytes */
	struct timespec st_atimespec;				/*!< time of last access */
	struct timespec st_mtimespec;				/*!< time of last data modification */
	struct timespec st_ctimespec;				/*!< time of last file status change */
	int	  st_blksize;							/*!< optimal blocksize for I/O */
	int	  st_blocks;							/*!< blocks allocated for file */
	unsigned int st_flags;						/*!< user defined flags for file */
	unsigned int st_gen;						/*!< file generation number */
};
#endif /* !_POSIX_SOURCE */


/*! @brief Definitions of the types for msdosfs. Extracted from the unix FreeBSD/NetBSD includes.  */
#ifdef _GSIM_
typedef struct {
#else
struct stat {
#endif
	unsigned int		st_dev;				/*!< inode's device  */
	ino_t				st_ino;				/*!< inode's number  */
	mode_t				st_mode;			/*!< inode protection mode  */
	nlink_t				st_nlink;			/*!< number of hard links  */
	uid_t				st_uid;				/*!< user ID of the file's owner  */
	gid_t				st_gid;				/*!< group ID of the file's group  */
	unsigned 			st_rdev;			/*!< device type  */
#ifndef _POSIX_SOURCE
	struct timespec		st_atimespec;		/*!< time of last access  */
	struct timespec 	st_mtimespec;		/*!< time of last data modification  */
	struct timespec 	st_ctimespec;		/*!< time of last file status change  */
#else
	unsigned int		st_atime;			/*!< time of last access  */
	long	  			st_atimensec;		/*!< nsec of last access  */
	unsigned int		st_mtime;			/*!< time of last data modification  */ 
	long	  			st_mtimensec;		/*!< nsec of last data modification  */
	unsigned int		st_ctime;			/*!< time of last file status change */ 
	long	  			st_ctimensec;		/*!< nsec of last file status change */
#endif
	long	 			st_size;			/*!< file size, in bytes  */
	long	 			st_blocks;			/*!< blocks allocated for file  */
	unsigned int 		st_blksize;			/*!< optimal blocksize for I/O  */
	unsigned int 		st_flags;			/*!< user defined flags for file  */ 
	unsigned int 		st_gen;				/*!< file generation number  */
	int	  					 st_lspare;		/*!< st_lspare :  */
	long	           st_qspare[2];		/*!< st_qspare :  */
#ifdef _GSIM_
}t_stat ;
#else
};
#endif



#ifndef _POSIX_SOURCE
/*! @brief Definitions of the types for msdosfs. Extracted from the unix FreeBSD/NetBSD includes. */
struct nstat {
	unsigned int	st_dev;					/*!< inode's device */
	ino_t			st_ino;					/*!< inode's number */
	unsigned int	st_mode;				/*!< inode protection mode */
	unsigned int	st_nlink;				/*!< number of hard links */
	uid_t			st_uid;					/*!< user ID of the file's owner */
	gid_t			st_gid;					/*!< group ID of the file's group */
	unsigned int st_rdev;					/*!< device type  */
#ifndef _POSIX_SOURCE
	struct timespec	st_atimespec;			/*!< time of last access */
	struct timespec st_mtimespec;			/*!< time of last data modification */
	struct timespec st_ctimespec;			/*!< time of last file status change */
#else
	unsigned int	st_atime;				/*!< time of last access */
	long			st_atimensec;			/*!< nsec of last access */
	unsigned int	st_mtime;				/*!< time of last data modification */
	long			st_mtimensec;			/*!< nsec of last data modification */
	unsigned int	st_ctime;				/*!< time of last file status change */
	long			st_ctimensec;			/*!< nsec of last file status change */
#endif
	long			st_size;				/*!< file size, in bytes */
	long			st_blocks;				/*!< blocks allocated for file */
	unsigned int	st_blksize;				/*!< optimal blocksize for I/O */
	unsigned int	st_flags;				/*!< user defined flags for file */
	unsigned int	st_gen;					/*!< file generation number */
	long			st_qspare[2];			/*!< st_qspare :  */
};
#endif

//#undef __dev_t

#ifndef _POSIX_SOURCE
#define st_atime st_atimespec.tv_sec
#define st_mtime st_mtimespec.tv_sec
#define st_ctime st_ctimespec.tv_sec
#endif

#define	S_ISUID	0004000			/*!< set user id on execution */
#define	S_ISGID	0002000			/*!< set group id on execution */
#ifndef _POSIX_SOURCE
#define	S_ISTXT	0001000			/*!< sticky bit */
#endif

#define	S_IRWXU	0000700			/*!< RWX mask for owner */
#define	S_IRUSR	0000400			/*!< R for owner */
#define	S_IWUSR	0000200			/*!< W for owner */
#define	S_IXUSR	0000100			/*!< X for owner */

#ifndef _POSIX_SOURCE
#define	S_IREAD		S_IRUSR
#define	S_IWRITE	S_IWUSR
#define	S_IEXEC		S_IXUSR
#endif

#define	S_IRWXG	0000070			/*!< RWX mask for group */
#define	S_IRGRP	0000040			/*!< R for group */
#define	S_IWGRP	0000020			/*!< W for group */
#define	S_IXGRP	0000010			/*!< X for group */

#define	S_IRWXO	0000007			/*!< RWX mask for other */
#define	S_IROTH	0000004			/*!< R for other */
#define	S_IWOTH	0000002			/*!< W for other */
#define	S_IXOTH	0000001			/*!< X for other */

#ifndef _POSIX_SOURCE
#define	S_IFMT	 0170000		/*!< type of file mask */
#define	S_IFIFO	 0010000		/*!< named pipe (fifo) */
#define	S_IFCHR	 0020000		/*!< character special */
#define	S_IFDIR	 0040000		/*!< directory */
#define	S_IFBLK	 0060000		/*!< block special */
#define	S_IFREG	 0100000		/*!< regular */
#define	S_IFLNK	 0120000		/*!< symbolic link */
#define	S_IFSOCK 0140000		/*!< socket */
#define	S_IFWHT  0160000		/*!< whiteout */
#define	S_ISVTX	 0001000		/*!< save swapped text even after use */
#endif

#define	S_ISDIR(m)	(((m) & 0170000) == 0040000)	/*!< directory */
#define	S_ISCHR(m)	(((m) & 0170000) == 0020000)	/*!< char special */
#define	S_ISBLK(m)	(((m) & 0170000) == 0060000)	/*!< block special */
#define	S_ISREG(m)	(((m) & 0170000) == 0100000)	/*!< regular file */
#define	S_ISFIFO(m)	(((m) & 0170000) == 0010000)	/*!< fifo or socket */
#ifndef _POSIX_SOURCE
#define	S_ISLNK(m)	(((m) & 0170000) == 0120000)	/*!< symbolic link */
#define	S_ISSOCK(m)	(((m) & 0170000) == 0140000)	/*!< socket */
#define	S_ISWHT(m)	(((m) & 0170000) == 0160000)	/*!< whiteout */
#endif

#ifndef _POSIX_SOURCE
#define	ACCESSPERMS	(S_IRWXU|S_IRWXG|S_IRWXO)	/* 0777 */
							/* 7777 */
#define	ALLPERMS	(S_ISUID|S_ISGID|S_ISTXT|S_IRWXU|S_IRWXG|S_IRWXO)
							/* 0666 */
#define	DEFFILEMODE	(S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

#define S_BLKSIZE	512		/*!< block size used in the stat struct */


// Definitions of flags stored in file flags word.
// Super-user and owner changeable flags.
#define	UF_SETTABLE		0x0000ffff			/*!< mask of owner changeable flags */
#define	UF_NODUMP			0x00000001			/*!< do not dump file */
#define	UF_IMMUTABLE	0x00000002			/*!< file may not be changed */
#define	UF_APPEND			0x00000004			/*!< writes to file may only append */
#define UF_OPAQUE			0x00000008			/*!< directory is opaque wrt. union */
#define UF_NOUNLINK		0x00000010			/*!< file may not be removed or renamed */


//Super-user changeable flags.
#define	SF_SETTABLE		0xffff0000			/*!< mask of superuser changeable flags */
#define	SF_ARCHIVED		0x00010000			/*!< file is archived */
#define	SF_IMMUTABLE	0x00020000			/*!< file may not be changed */
#define	SF_APPEND			0x00040000			/*!< writes to file may only append */
#define	SF_NOUNLINK		0x00100000			/*!< file may not be removed or renamed */

#ifdef _KERNEL

//Shorthand abbreviations of above.
#define	OPAQUE		(UF_OPAQUE)
#define	APPEND		(UF_APPEND | SF_APPEND)
#define	IMMUTABLE	(UF_IMMUTABLE | SF_IMMUTABLE)
#define	NOUNLINK	(UF_NOUNLINK | SF_NOUNLINK)
#endif

#endif /* !_POSIX_SOURCE */

#ifndef _KERNEL
//#include <sys/cdefs.h>


/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @brief This function sets the file permission bits of the file specified by the pathname path to mode.
 * @param path : path of the file.
 * @param mode : file permission bits. Only the flag VWRITE = 0200 is managed.
 * @return
 * - Upon successful completion a value of 0 is returned. 
 * - Otherwise, a value of -1 is returned and errno is set to indicate the error. 
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:chmod:KSFAM_VFS:0x13
// \endif
int	chmod (const char * path, mode_t mode);


/*! @brief This function obtains the same information about an open file known by the file descriptor fd.
 * @param fd : file descriptor.
 * @param sb : pointer to a stat structure as defined by vfs.h (shown below) and into which information is placed concerning the file. 
 * @return
 * - Upon successful completion a value of 0 is returned.
 * - Otherwise, a value of -1 is returned and errno is set to indicate the error. 
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
#ifdef _GSIM_
// \if SIMULATION
//  @GSIM_F:fstat:KSFAM_VFS:0x12
//  @GSIM_A:2:ONE_POINTER 
// \endif
int	fstat (int fd, t_stat * sb);
#else
int	fstat (int fd, struct stat * sb);
#endif



/*! @brief The directory path is created with the access permissions specified by mode. 
 *
 * - Access permissions values are : 6,4,2 ( r, w, r+w are possible, x never used ) for both user, group, world.
 * - The directory's owner ID is set to the process's effective user ID. 
 * - The directory's group ID is set to that of the parent directory in which it is created. 
 *
 * @param path : path of the directory.
 * @param mode : Access permissions.
 * @return 
 * - 0 return value indicates success. 
 * - -1 return value indicates an error, and an error code is stored in errno. 
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:mkdir:KSFAM_VFS:0x09
// \endif
int	mkdir (const char * path, mode_t mode);


//! \brief The stat() function obtains information about the file pointed to by path. 
//! Read, write or execute permission of the named file is not required, but all directories listed
//! in the path name leading to the file must be searchable. 
//! \param path: path of the file.
//! \param info: pointer to a stat structure as defined by vfs.h and into which 
//! information is placed concerning the file.
//! \return
//! - Upon successful completion a value of 0 is returned.
//! - Otherwise, a value of -1 is returned and errno is set to indicate the error.
// \if SIMULATION
//  @GSIM_F:stat:KSFAM_VFS:0x11
//  @GSIM_A:2:ONE_POINTER 
// \endif
#ifdef _GSIM_
int	stat (const char * path, t_stat * info);
#else
int	stat (const char * path, struct stat * info);
#endif


/*
======================================================================
					List of Defines
======================================================================
*/


// From <sys/fcntl.h>

#define	O_RDONLY		0x00000000		/*!< open for reading only */
#define	O_WRONLY		0x00000001		/*!< open for writing only */
#define	O_RDWR			0x00000002		/*!< open for reading and writing */
#define	O_ACCMODE		0x00000003		/*!< mask for above modes */
#define O_APPEND		0x00000008		/*!< set append mode */
#define O_CREAT			0x00000200		/*!< create if nonexistent */
#define O_TRUNC			0x00000400		/*!< truncate to zero length */
#define O_EXCL			0x00000800		/*!< error if already exists */

#define	FREAD			0x00000001		/*!< Validate read access */
#define	FWRITE			0x00000002		/*!< Validate write access */

#define	SEEK_SET	0	/*!< set file offset to offset */
#define	SEEK_CUR	1	/*!< set file offset to current plus offset */
#define	SEEK_END	2	/*!< set file offset to EOF minus offset */

// From <stdio.h>

#ifndef NULL
#define	NULL	0
#endif


// Divers

#define M_MSDOSFSMNT		0		/*!< MSDOSFS mount structure */
#define M_MSDOSFSFAT		1		/*!< MSDOSFS file allocation table */
#define M_MSDOSFSNODE		2		/*!< MSDOSFS node private part */
#define M_MSDOSFSDIR		3		/*!< MSDOSFS directory struct storage */
#define M_MSDOSFSDBUF		4		/*!< MSDOSFS data buffer storage */
#define M_MSDOSFSVNODE		5		/*!< MSDOSFS vnode private part */
#define M_MSDOSFSBLCK		6		/*!< MSDOSFS blocks private part */
#define MTX_DEF				0		/*!< Mutex must be defined */

#define	bcmp(a,b,c)		memcmp(a,b,c)		/*!< Compare byte string */
#define	bcopy(a,b,c)	memcpy(b,a,c)		/*!< Copy byte string */
#define	bzero(a,b)		memset(a,0,b)		/*!< Write zeroes to a byte string */

#define MFSNAMELEN		16	/*!< length of fs type name, including null */
#define	MNAMELEN		80	/*!< length of buffer for returned name */


/*! @brief Definitions of the types for msdosfs. Extracted from the unix FreeBSD/NetBSD includes. fsid_t is the file system id type. */
typedef struct fsid {
	int val[2];				/*!< array of int. */
} fsid_t;					/* file system id type */


/*! @brief Definitions of the types for msdosfs. Extracted from the unix FreeBSD/NetBSD includes.  */
#ifdef _GSIM_
typedef struct {
#else
struct statfs{
#endif
	long	f_spare2;					/*!< placeholder */
	long	f_bsize;					/*!< fundamental file system block size */
	long	f_iosize;					/*!< optimal transfer block size  */
	long	f_blocks;					/*!< total data blocks in file system  */
	long	f_bfree;					/*!< free blocks in fs */
	long	f_bavail;					/*!< free blocks avail to non-superuser */
	long	f_files;					/*!< total file nodes in file system */
	long	f_ffree;					/*!< free file nodes in fs */
	fsid_t	f_fsid;						/*!< file system id */
	uid_t	f_owner;					/*!< user that mounted the filesystem */
	int		f_type;						/*!< type of filesystem */
	int		f_flags;					/*!< copy of mount exported flags */
	long  	f_syncwrites;				/*!< count of sync writes since mount */
	long  	f_asyncwrites;				/*!< count of async writes since mount */
	char	f_fstypename[MFSNAMELEN];	/*!< fs type name */
	char	f_mntonname[MNAMELEN];		/*!< directory on which mounted */
	long 	f_syncreads;				/*!< count of sync reads since mount */
	long 	f_asyncreads;				/*!< count of async reads since mount */
	short	f_spares1;					/*!< unused spare */
	char	f_mntfromname[MNAMELEN];	/*!< mounted filesystem */
	short	f_spares2;					/*!< unused spare */
	long 	f_spare[2];					/*!< unused spare */
#ifdef _GSIM_
} t_statfs;
#else
};
#endif

struct export_args {
	int		ex_flags;			/*!< export related flags */
};

#define	MNT_RDONLY			0x00000001	/*!< read only filesystem */
#define	MNT_SYNCHRONOUS		0x00000002	/*!< file system written synchronously */
#define	MNT_UPDATE			0x00010000	/*!< not a real mount, just an update */
#define	MNT_RELOAD			0x00040000	/*!< reload filesystem data */
#define	MNT_FORCE			0x00080000	/*!< force unmount or readonly change */
#define	MNT_NOATIME			0x10000000	/*!< disable update of file access time */

#define MNTK_WANTRDWR		0x04000000	/*!< upgrade to read/write requested */

#define	MNT_LOCAL			0x00001000	/*!< filesystem is stored locally */

#define MNT_WAIT		1		/*!< synchronously wait for I/O to complete */
#define MNT_NOWAIT		2		/*!< start all I/O, but do not wait for it */
#define MNT_LAZY		3		/*!< push data not written by filesystem syncer */


/*
======================================================================
			Functions Definition
======================================================================
*/

// Fonctions systemes exportees via les SWIs


/*! @brief This function grafts a file system object onto the system file tree at the point dir.
 *
 * - The argument data describes the file system object to be mounted. 
 * - The argument type tells the kernel how to interpret data (See type below). 
 * - The contents of the file system become available through the new mount point dir.
 * - Only one file system can be mounted and only once. 
 * - You should mount it on the first initialisation of the application ( cf after_reset entry point ) 
 *
 * @param type  : how to interpret data.
 * @param dir   : point to grafts a file system object.
 * - MMC for /dev/mmcd0a
 * - USB1 for /dev/umsd0a
 * - USB2 for /dev/umsd1a
 * @param flags : mount flag. This flag takes the value MNT_SYNCHRONOUS. Other values are not managed.
 * @param data  : pointer to structure msdosfs_args
 * @return 
 * - mount() returns the value 0 if the mount was successful.
 * - otherwise -1 is returned and the variable errno is set to indicate the error. 
 *
 * @par Example:

 * @include oem_vfs_Sample_01.c


 * @link KSFAM_VFS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:mount:KSFAM_VFS:0x01
//  @GSIM_S:S_mount:E_mount
// \endif
extern int		mount(const char *type, const char *dir, int flags, void *data);



/*! @brief This function call disassociates the file system from the specified mount point dir. 
 * @param dir : mount point specified at mount function call.
 * @param flags : The flags argument may specify MNT_SYNCHRONOUS. Other values are not managed.
 * @return 
 * - On success, 0 is returned.
 * - On error -1 is returned, and errno is set appropriately.
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:unmount:KSFAM_VFS:0x02
// \endif
extern int		unmount(const char *dir, int flags);



/*! @brief This function opens the directory named by filename, associates a directory stream with it 
 * and returns a pointer to be used to identify the directory stream in subsequent operations.
 * @param filename : directory to be opened.
 * @return 
 * - Pointer to be used to identify the directory stream in subsequent operations. 
 * - The pointer NULL is returned if filename cannot be accessed, or if it cannot allocate enough memory to hold the whole thing. 
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:opendir:KSFAM_VFS:0x03
//  @GSIM_A:0:ONE_ADDRESS
// \endif
extern DIR *	opendir(const char *filename);



/*! @brief This function returns a pointer to the next directory entry.
 * @param dirp : pointer to structure DIR.
 * @return 
 * - pointer to the next directory entry. 
 * - It returns NULL upon reaching the end of the directory or detecting an invalid seekdir() operation. 
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:readdir:KSFAM_VFS:0x04
//  @GSIM_S:readdir:E_readdir
// \endif
extern struct dirent *readdir(DIR *dirp);



/*! @brief This function returns the current location associated with the named directory stream.
 * @param dirp : pointer to structure DIR.
 * @return
 * - The current location associated with the names directory stream if OK
 * - -1 if param dirp is incorrect. And variable errno is set.
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:telldir:KSFAM_VFS:0x05
//  @GSIM_A:1:ONE_ADDRESS
// \endif
extern long	telldir(const DIR *dirp);




/*! @brief This function sets the position of the next readdir() operation on the directory stream. 
 *
 * The new position reverts to the one associated with the directory stream when the telldir() operation was performed. 
 * Values returned by telldir() are good only for the lifetime of the DIR pointer, dirp, from which they are derivated. 
 * If the directory is closed and then reopened, the telldir() value may be invalidated. 
 * It is safe to use a previous telldir() value immediately after a call to opendir() and before any calls to readdir(). 
 *
 * @param dirp : pointer to directory stream.
 * @param loc : value returned by telldir() function.
 * @return None.
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:seekdir:KSFAM_VFS:0x06
//  @GSIM_A:1:ONE_ADDRESS
// \endif
extern void	seekdir(DIR *dirp, long loc);



/*! @brief This function resets the position of the named directory stream to the beginning of the directory. 
 * @param dirp : pointer to directory stream.
 * @return None.
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:rewinddir:KSFAM_VFS:0x07
//  @GSIM_A:1:ONE_ADDRESS
// \endif
extern void	rewinddir(DIR *dirp);


/*! @brief This function closes the named directory stream and frees the structure associated with the dirp pointer, returning 0 on success. 
 * @param dirp : pointer to directory stream.
 * @return 
 * - 0 on success. 
 * - -1 on failure. And the global variable errno is set to indicate the error. 
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:closedir:KSFAM_VFS:0x08
//  @GSIM_A:1:ONE_ADDRESS
// \endif
extern int		closedir(DIR *dirp);



/*! @brief The directory path is created with the access permissions specified by mode. 
 *
 * - Access permissions values are : 6,4,2 ( r, w, r+w are possible, x never used ) for both user, group, world.
 * - The directory's owner ID is set to the process's effective user ID. 
 * - The directory's group ID is set to that of the parent directory in which it is created.
 *
 * @param path : path of the directory.
 * @param mode : Access permissions.
 * @return 
 * -  0 return value indicates success. 
 * - -1 return value indicates an error, and an error code is stored in errno. 
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:mkdir:KSFAM_VFS:0x09
// \endif
extern int		mkdir(const char *path, mode_t mode);



/*! @brief This function removes a directory file whose name is given by path. 
 *
 * The directory must not have any entries other than '.' and '..'
 * @param path : path of the directory.
 * @return 
 * - 0 return value indicates success. 
 * - -1 return value indicates an error, and an error code is stored in errno. 
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:rmdir:KSFAM_VFS:0x0A
// \endif
extern int		rmdir(const char *path);



/*! @brief The file name specified by path is opened for reading and/or writing as specified by the argument flags and the file descriptor returned to the calling process. 
 *
 * The flags are specified by or'ing the following values. 
 *
 * Applications must specify exactly one of the first three values (file access modes): 
 * - O_RDONLY Open for reading only. 
 * - O_WRONLY Open for writing only. 
 * - O_RDWR Open for reading and writing. 
 *
 * Any combination of the following may be used: 
 * - O_APPEND Append to the file on each write. 
 * - O_CREAT Create the file if it does not exist, in which case the file is created with mode as described in chmod(2) and modified by the process' umask value (see umask(2)).
 * - O_TRUNC Truncate size to 0. 
 * - O_EXCL Error if O_CREAT and the file already exists. 
 * - Opening a file with O_APPEND set causes each write on the file to be appended to the end. 
 * - If O_TRUNC is specified and the file exists, the file is truncated to zero length. 
 * - If O_EXCL is set with O_CREAT and the file already exists, open() returns an error. 
 *
 * This may be used to implement a simple exclusive access locking mechanism. 
 *
 * If O_EXCL is set and the last component of the pathname is a symbolic link, open() will fail even if the symbolic link points to a non- existent name. 
 *
 * If open() is successful, the file pointer used to mark the current position within the file is set to the beginning of the file. 
 *
 * When a new file is created it is given the group of the directory which contains it. 
 *
 * The maximum number of file descriptors open simultaneously is 20. 
 * @param path  : path of the directory.
 * @param flags : argument.
 * @param mode  : Mode of the file creation. Only the flag VWRITE = 0200 is managed.
 * @return 
 * - If successful, open() returns a non-negative integer, termed a file descriptor. 
 * - Otherwise, a value of -1 is returned and errno is set to indicate the error. 
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:open:KSFAM_VFS:0x0B
// \endif
extern int		open(const char *path, int flags, mode_t mode);



/*! @brief This function deletes a descriptor from the per-process object reference table. 
 *
 * If this is the last reference to the underlying object, the object will be deactivated. 
 * @param d : reference of the object to delete.
 * @return 
 * - Upon successful completion, a value of 0 is returned. 
 * - Otherwise, a value of -1 is returned and the global integer variable errno is set to indicate the error.
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:close:KSFAM_VFS:0x0C
// \endif
extern int		close(int d);



/*! @brief This function removes the link named by path from its directory and decrements the link count of the file which was referenced by the link. 
 *
 * If that decrement reduces the link count of the file to zero, and no process has the file open, 
 * then all resources associated with the file are reclaimed. If one or more process have the file open 
 * when the last link is removed, the link is removed, but the removal of the file is delayed 
 * until all references to it have been closed. 
 * @param path : path of the directory.
 * @return
 * - Upon successful completion, a value of 0 is returned. 
 * - Otherwise, a value of -1 is returned and errno is set to indicate the error. 
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:unlink:KSFAM_VFS:0x0D
// \endif
extern int		unlink(const char *path);



/*! @brief This function  attempts to read nbytes of data from the object referenced by the descriptor 'd' into the buffer pointed to by buf. 
 *
 * It starts at a position given by the pointer associated with d (see lseek(2)). 
 *
 * Upon return from read(), the pointer is incremented by the number of bytes actually read. 
 *
 * Upon successful completion, read(), returns the number of bytes actually read and placed in the buffer. 
 *
 * The system guarantees to read the number of bytes requested if the descriptor references a normal file that has that many bytes left before the end-of-file, but in no other case.
 * @param d : descriptor.
 * @param buf : pointer to the buffer to read.
 * @param nbytes : number of bytes to read.
 * @return 
 * - Upon successful completion, a value of 0 is returned. 
 * - Otherwise, a value of -1 is returned and errno is set to indicate the error. 
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:read:KSFAM_VFS:0x0E
//  @GSIM_A:2:DATA_SIZE(nbytes)
// \endif
extern ssize_t	read(int d, void *buf, unsigned int nbytes);



/*! @brief This function attempts to write nbytes of data to the object referenced by the descriptor d from the buffer pointed to by buf .
 *
 * It starts at a position given by the pointer associated with d (see lseek(2)). 
 *
 * Upon return from write(), the pointer is incremented by the number of bytes which were written. 
 *
 * If write() succeeds it will update the st_ctime and st_mtime fields of the file's meta-data (see stat(2)). 
 * @param d : descriptor.
 * @param buf : pointer to the buffer to write.
 * @param nbytes : number of bytes to write.
 * @return 
 * - Upon successful completion, a value of 0 is returned.
 * - Otherwise, a value of -1 is returned and errno is set to indicate the error.
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:write:KSFAM_VFS:0x0F
//  @GSIM_A:2:DATA_SIZE(nbytes)
//  @GSIM_A:2:IN_ONLY
// \endif
extern ssize_t	write(int d, const void *buf, unsigned int nbytes);



/*! @brief This function repositions the offset of the file descriptor fildes to the argument offset according to the directive whence. 
 *
 * The argument fildes must be an open file descriptor. 
 *
 * lseek() repositions the file pointer fildes as follows: 
 * - If whence is SEEK_SET, the offset is set to offset bytes. 
 * - If whence is SEEK_CUR, the offset is set to its current location plus offset bytes. 
 * - If whence is SEEK_END, the offset is set to the size of the file plus offset bytes. 
 * - The lseek() function allows the file offset to be set beyond the end of the existing end-of-file of the file. 
 *
 * If data is later written at this point, subsequent reads of the data in the gap return bytes of zeros (until data is actually written into the gap).
 * @param fildes : open file descriptor.
 * @param offset : argument.
 * @param whence : directive.
 * @return
 * - Upon successful completion, lseek() returns the resulting offset location as measured in bytes from the beginning of the file. 
 * - Otherwise, a value of -1 is returned and errno is set to indicate the error. 
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:lseek:KSFAM_VFS:0x10
// \endif
extern off_t	lseek(int fildes, off_t offset, int whence);



/*! @brief This function obtains the same information about an open file known by the file descriptor fd.
 * @param fd : file descriptor.
 * @param sb : pointer to a stat structure as defined by vfs.h (shown below) and into which  information is placed concerning the file. 
 * @return
 * - Upon successful completion a value of 0 is returned.
 * - Otherwise, a value of -1 is returned and errno is set to indicate the error. 
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
#ifdef _GSIM_
// \if SIMULATION
//  @GSIM_F:fstat:KSFAM_VFS:0x12
//  @GSIM_A:2:ONE_POINTER 
// \endif
extern int		fstat(int fd, t_stat *sb);
#else
extern int		fstat(int fd, struct stat *sb);
#endif



/*! @brief The function sets the file permission bits of the file specified by the pathname path to mode.
 * @param path : path of the file.
 * @param mode : file permission bits. Only the flag VWRITE = 0200 is managed.
 * @return
 * - Upon successful completion a value of 0 is returned. 
 * - Otherwise, a value of -1 is returned and errno is set to indicate the error. 
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:chmod:KSFAM_VFS:0x13
// \endif
extern int		chmod(const char *path, mode_t mode);



/*! @brief The function sets the permission bits of the specified file descriptor fd.
 * @param fd : file descriptor.
 * @param mode : file permission bits. Only the flag VWRITE = 0200 is managed.
 * @return
 * - Upon successful completion a value of 0 is returned.
 * - Otherwise, a value of -1 is returned and errno is set to indicate the error. 
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:fchmod:KSFAM_VFS:0x14
// \endif
extern int		fchmod(int fd, mode_t mode);



/*! @brief This function causes the link named 'from' to be renamed as 'to'. If to exists, it is first removed. 
 *
 * Both from and to must be of the same type (that is both directories or both non-directories), and must reside on the same file system. 
 *
 * It guarantees that an instance of 'to' will always exist, even if the system should crash in the middle of the operation. 
 *
 * If both from and to are pathnames of the same existing file in the file system's name space, rename() returns successfully and performs no other action.
 * @param oldname : old name of the file
 * @param newname : new name of the file
 * @return 
 * - 0 value is returned if the operation succeeds, 
 * - otherwise rename returns -1 and the global variable errno indicates the reason for the failure.
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:rename:KSFAM_VFS:0x17
// \endif
extern int		rename(const char *oldname, const char *newname);



/*! @brief This routine truncates a file at the specified length.
 * @param path : path of the file.
 * @param length : remaining length. Final length of the file.
 * @return 0 if OK
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:truncate:KSFAM_VFS:0x18
// \endif
extern int		truncate(const char *path, off_t length);



/*! @brief This routine truncates a file at the specified length.
 * @param fd : File descriptor
 * @param length : remaining length. Final length of the file.
 * @return 0 if OK
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ftruncate:KSFAM_VFS:0x19
// \endif
extern int		ftruncate(int fd, off_t length);



/*! @brief This routine gives information on a file.
 * @param path : path of the file.
 * @param buf : pointer to structure statfs.
 * @return 0 if OK.
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
#ifdef _GSIM_
// \if SIMULATION
//  @GSIM_F:statfs:KSFAM_VFS:0x1A
//  @GSIM_A:2: ONE_POINTER
// \endif
extern int		statfs(const char *path, t_statfs *buf);
#else
extern int		statfs(const char *path, struct statfs *buf);
#endif



/*! @brief This routine gives information on a file.
 * @param fd : file descriptor.
 * @param buf : pointer to structure statfs. 
 * @return  0 if Ok.
 *
 * @link KSFAM_VFS Back to top @endlink
 */ 
#ifdef _GSIM_
// \if SIMULATION
//  @GSIM_F:fstatfs:KSFAM_VFS:0x1B
//  @GSIM_A:2:ONE_POINTER
// \endif
extern int		fstatfs(int fd, t_statfs *buf);
#else
extern int		fstatfs(int fd, struct statfs *buf);
#endif



// Arguments to mount MSDOS filesystems.

struct msdosfs_args {
 char *fspec;  									/*!<blocks special holding the fs to mount */
#ifdef __cplusplus                                                                               
 struct export_args export_arg; /*!< network export information */
#else
 struct export_args export; 	/*!< network export information */
#endif                                                                                            
 uid_t uid;  									/*!< uid that owns msdosfs files */
 gid_t gid;  									/*!< gid that owns msdosfs files */
 mode_t mask;  								/*!< mask to be applied for msdosfs perms */
 int flags;  									/*!< see below */
 int magic;  									/*!< version number */
 unsigned short u2w[128];     /*!< Local->Unicode table */
 unsigned char  ul[128];      /*!< Local upper->lower table */
 unsigned char  lu[128];      /*!< Local lower->upper table */
 unsigned char  d2u[128];     /*!< DOS->local table */
 unsigned char  u2d[128];     /*!< Local->DOS table */
};

#define MOUNT_MSDOS     "msdos"         /* MSDOS Filesystem */

/*
 * Msdosfs mount options:
 */   																
#define	MSDOSFSMNT_SHORTNAME		1				/*!< Force old DOS short names only   */
#define	MSDOSFSMNT_LONGNAME			2				/*!< Force Win'95 long names          */
#define	MSDOSFSMNT_NOWIN95			4				/*!< Completely ignore Win95 entries  */
#define MSDOSFSMNT_U2WTABLE     	0x10    		/*!< Local->Unicode and local<->DOS   */
													/*!< tables loaded                    */
#define MSDOSFSMNT_ULTABLE      	0x20    		/*!< Local upper<->lower table loaded */

/* All flags above: */
#define	MSDOSFSMNT_MNTOPT \
	(MSDOSFSMNT_SHORTNAME|MSDOSFSMNT_LONGNAME|MSDOSFSMNT_NOWIN95 \
	 |MSDOSFSMNT_U2WTABLE|MSDOSFSMNT_ULTABLE)
#define	MSDOSFSMNT_RONLY			0x80000000			/*!< mounted read-only	*/
#define	MSDOSFSMNT_WAITONFAT		0x40000000			/*!< mounted synchronous	*/
#define	MSDOSFS_FATMIRROR			0x20000000			/*!< FAT is mirrored */

#define MSDOSFS_ARGSMAGIC			0xe4eff300			/*!< Magic number for signature */

#endif  //kernel
#endif  //VFS_H

/*! @}  */ 

