/** \file
 * TELIUM functions to manage traces
 */

// Includes
//-------------------------------------------------------------------
#include <SDK30.H>

#include "Utilities.h"

// Macros & preprocessor definitions.
//-------------------------------------------------------------------
#define TRCID (trace_sap_id_t)0xF000

void _trcS(const char *str) 
{
    static unsigned char i = 0;          //indicates whether this function is called for the first time

    trace(TRCID, strlen(str), str);
    #ifdef SYS_FIOCTL_DEBUG_TRACE
    {
        #define DIM 512    
        long len, dim;
        char tmp[DIM+1];

        dim = strlen(str);
        while(dim)
        {
            if (dim < DIM)
            {
                len = dim;
            }
            else
            {
                len = DIM;
            }
            memset(tmp, 0, sizeof(tmp));
            memcpy(tmp, str, len);
            SystemFioctl(SYS_FIOCTL_DEBUG_TRACE, (unsigned char *)tmp);
            dim-=len;
            str+=len;
        }
    }
    #endif
    i = 1;                      //next time it will not be zero
}

void _trcFS(const char *fmt, const char *str) 
{
    char buf[2048];

    sprintf(buf, fmt, str);
    _trcS(buf);
}

void _trcFN(const char *fmt, long num) 
{
    char buf[1024];

    sprintf(buf, fmt, num);
    _trcS(buf);
}

void _trcBuf(const unsigned char * buf, int len) 
{
    char tmp[2048];
    int idx;

    if(len > 512)
        len = 512;
    *tmp = 0;
    for (idx = 0; idx < len; idx++) 
    {
        sprintf(tmp + strlen(tmp), "%02X ", (word) buf[idx]);
    }
    _trcS(tmp);
}

void _trcBN(const unsigned char * buf, int len) 
{
    int idx;
    char tmp[4];

    for (idx = 0; idx < len; idx++) 
    {
        sprintf(tmp, "%02X ", (word) buf[idx]);
        _trcS(tmp);
    }
}

void _trcAN(const byte * buf, int len) 
{
    int idx;
    char val[3];
    char tmp[2048];

    CHECK(tmp != NULL, lblKO);
    memset(tmp, 0, 2048);
    for (idx = 0; idx < len; idx++) {
        memset(val, 0, sizeof val);
        if(buf[idx] == '%')
            val[1] = '%';
        if(buf[idx] < 0x20)
            val[0] = '?';
        else if(buf[idx] > 0x7F)
            val[0] = '?';
        else
            val[0] = buf[idx];
        strcat(tmp, val);
    }
    _trcS(tmp);
lblKO:
    return;
}

void _trcBAN(const unsigned char * buf, int len) 
{
    _trcBN((unsigned char *) buf, len);
    _trcS(" [");
    _trcAN(buf, len);
    _trcS("]");
}

void _trcErr(long err) 
{
    _trcFN("!error code: %ld\n", err);
}

void _trcFL(const char *file, int line) 
{
    _trcFS("FILE: %s ", file);
    _trcFN("LINE: %u\n", line);
}

void errVrf(const char *cond, const char *file, word line) {
    trcFS( "Fatal error, COND: %s, ", cond);
    trcFL( file, line);
}

void errChk(const char *cond, const char *file, word line) {
    trcFS("Error: %s, ", cond);
    trcFL(file, line);
}

