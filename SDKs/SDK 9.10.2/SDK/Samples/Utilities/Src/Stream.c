/** \file
 * Implementation of parent classes for the following types of stream processing
 * - RAM stream
 * - FILE stream
 */

#include "sdk30.h"
#include <string.h>

#include "Utilities.h"

int stmGet(tStream *stm)
{
    int ret;

    VERIFY(stm);
    VERIFY(stm->vmt);
    VERIFY(stm->vmt->get);

    ret = stm->vmt->get(stm);
    return ret;
}

int stmGetBuf(tStream *stm, unsigned char *buf, unsigned int len)
{
    int ret;
    int idx;

    //trcS("stmGetBuf Beg\n");
    memset(buf, 0, len);
    for (idx=0; idx<len; idx++)
    {
        ret = stmGet(stm);
        if (ret==-1)
            break;
        buf[idx] = (unsigned char)ret;
    }

    ret = idx;
    return ret;
}

int stmPut(tStream *stm, unsigned char buf)
{
    int ret;
    
    VERIFY(stm);
    VERIFY(stm->vmt);
    VERIFY(stm->vmt->put);

    ret = stm->vmt->put(stm, buf);
    return ret;
}

int stmPutBuf(tStream *stm, const unsigned char *buf, unsigned int len)
{
    int ret;
    int idx;

    for (idx=0; idx<len; idx++)
    {
        ret = stmPut(stm, buf[idx]);
        if (ret<=0)
            break;
    }

    ret = idx;
    return ret;
}

void stmClose(tStream *stm)
{
    VERIFY(stm);
    VERIFY(stm->vmt);
    VERIFY(stm->vmt->close);
    
    stm->vmt->close(stm);
}

