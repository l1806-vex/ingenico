/** \file
 * Child classes that performs operations for File Stream processing
 * - stmFileInit()
 * - stmFileGet()
 * - stmFilePut()
 * - stmFileClose()
 *
 */

#include "sdk30.h"
#include <string.h>

#include "Utilities.h"

#ifndef CFG_DIR 
#define CFG_DIR "/HOST" 
#endif

typedef struct sFileStream
{
    tStmVmt *vmt; ///<virtual method functions for get, put and close
    char *mode; ///<'r' read or 'w' write mode
    void* fd; ///<file descriptor
} tFileStream;

/** Get a byte from the file stream
 * \param stm (I) pointer to the stream descriptor
 * \return byte retrieved; negative in case of error
 */
static int stmFileGet(tStream* stm)
{
    int ret;
    unsigned char b;
    tFileStream *fileStm = (tFileStream*)stm;

    VERIFY(fileStm->fd);
    ret = FS_length(fileStm->fd);
    if (ret==0)
        return -1;

    ret = FS_read(&b, 1, 1, fileStm->fd);
    if(ret!=1)
        ret = -1;
    else
       ret = (int)b;

    return ret;
}

/** Put a byte to file stream
 * \param stm (I) pointer to the stream descriptor
 * \param buf (O) pointer to the source buffer 
 * \return number of bytes added to the stream
 */
static int stmFilePut(tStream* stm, unsigned char buf)
{
    int ret;
    tFileStream *fileStm = (tFileStream*)stm;	

    VERIFY(fileStm->fd);
    ret = FS_write(&buf, 1, 1, fileStm->fd);
    if (ret!=1)
        return -1;

    return ret;
}

/** Close the file stream
 * \param stm (I) pointer to the stream descriptor
 * \return 1
 */
void stmFileClose(tStream* stm)
{
    tFileStream *fileStm = (tFileStream*)stm;

    if (fileStm->fd)
    {
        FS_close(fileStm->fd);
        FS_unmount(CFG_DIR);
    }
    if (stm)
        ufree(stm);
}

/** Open the file stream
 * \param stm (I) pointer to the stream descriptor
 * \param file (I) file to be processed
 * \param mod (I) 'r' read or 'w' write mode 
 * \return 1; negative in case of error
 */
static int stmFileOpen(tFileStream* stm, const char *file, char *mod)
{
    int ret;
    char dir[128];
    unsigned int mode = FS_WRITEMANY;

    memset(dir, 0, sizeof(dir));
    sprintf(dir, "%s/%s", CFG_DIR, file);
    if(FS_mount (CFG_DIR, &mode) == FS_OK)
    {
        stm->fd = FS_open(dir, mod);
        if(stm->fd==NULL) 
        {
            if (strcmp(mod, "r")!=0)
            {
                stm->fd = FS_open(dir, "a");
                FS_close(stm->fd);
                stm->fd = FS_open(dir, "r+");
            }
        }
    }
    CHECK(stm->fd, lblKO);
    trcFN("File stream length = %d\n", FS_length(stm->fd));

    ret = 1;
    goto lblEnd;
    lblKO:
        ret = -1;
    lblEnd:
        return ret;
}

//vitual method table for children stream classes Get, Put, and Close
static tStmVmt vmt = {stmFileGet, stmFilePut, stmFileClose};

tStream *stmFileInit(const char *file, char *mod)
{
    int ret;
    tFileStream *stm = (tFileStream*)umalloc(sizeof(tFileStream));
    
    trcS("stmFileInit Beg\n");
    memset(stm, 0, sizeof(tFileStream));
    stm->vmt = &vmt;
    stm->mode = mod;

    ret = stmFileOpen(stm, file, mod);
    CHECK(ret>=0, lblKO);

    trcS("stmFileInit OK\n");
    goto lblEnd;
    lblKO:
        trcS("stmFileInit KO\n");
        (tFileStream*)stm = NULL;
    lblEnd:
        return (tStream*)stm;
}

