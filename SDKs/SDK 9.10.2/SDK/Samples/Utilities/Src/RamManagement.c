/** \file
 * Child classes that performs operations for RAM Stream processing
 * - stmRamInit()
 * - stmRamGet()
 * - stmRamPut()
 * - stmRamClose()
 *
 */

#include "sdk30.h"
#include <string.h>

#include "Utilities.h"

typedef struct sRamStream
{
    tStmVmt *vmt; ///<virtual method functions for get, put and close
    char mode; ///<'r' read or 'w' write mode
    int len; ///<total length of the stream data
    int pos; ///<curent position in the stream
    int dim; ///<max dimension of the stream
    unsigned char *ptr; ///<pointer to the stream buffer    
} tRamStream;

static int stmLen;

/** Get a byte from the Ram stream
 * \param stm (I) pointer to the stream descriptor
 * \return byte retrieved; negative in case of error
 */
static int stmRamGet(tStream* stm)
{
    int ret=-1;
    unsigned char b;
    tRamStream *ramStm=(tRamStream*)stm;

    VERIFY(ramStm->ptr);
    if (ramStm->pos < ramStm->len)
    {
        b = ramStm->ptr[ramStm->pos];
        ramStm->pos++;
        ret = (int)b;
    }

    return ret;
}

/** Put a byte to Ram stream
 * \param stm (I) pointer to the stream descriptor
 * \param buf (O) pointer to the source buffer 
 * \return number of bytes added to the stream
 */
static int stmRamPut(tStream* stm, unsigned char buf)
{
    int ret=0;
    tRamStream *ramStm=(tRamStream*)stm;

    VERIFY(ramStm->ptr);	
    if (ramStm->len < ramStm->dim)
    {
        memcpy(ramStm->ptr + stmLen, &buf, 1);
        stmLen++;
        ret = 1;
    }

    return ret;
}

/** Close the Ram stream
 * \param stm (I) pointer to the stream descriptor
 * \return 1
 */
static void stmRamClose(tStream* stm)
{
    if (stm)
    {
        ufree(stm);
    }
}

//vitual method table for children stream classes Get, Put, and Close
static tStmVmt vmt = {stmRamGet, stmRamPut, stmRamClose};

tStream *stmRamInit(unsigned char *buf, unsigned int len, char mod)
{
    tRamStream *stm = (tRamStream*)umalloc(sizeof(tRamStream));

    memset(stm, 0, sizeof(tRamStream));
    if (mod=='w')
    {
        memset(buf, 0, len);
        stmLen = 0;
    }
    else
    {
        stmLen = len;
        stm->len = stmLen;
    }

    stm->vmt = &vmt;
    stm->mode = mod;
    stm->dim = len;
    stm->ptr = buf; 

    return (tStream*)stm;
}

