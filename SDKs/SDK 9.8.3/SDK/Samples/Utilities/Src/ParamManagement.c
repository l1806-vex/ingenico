/** \file
 * Various TELIUM functions used for XML Parsing
 */

// Includes
//-------------------------------------------------------------------
#include <SDK30.H>
#include <xmls.h>

#include "Utilities.h"

static int fileLen;
static char tag[64];
static char fileBuf[2056];
static char txtFile[128];

static char *strupper(char *source)
{
    int i;
    int size;
    char str[255] = {0};

    size = strlen(source);
    memcpy(str, source, size);
    for (i=0;i<size;i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] -= 0x20;
        }
    }
    memcpy(source, str, size);
    return source;
}

/** Obtain the value of the xml start tag
 * Obtain also the atributes of the start tag if there are any
 */
static void getAtrVal(XMLs_PARSER parser, const char* name, XMLs_ATTRIBUTE_HANDLE atr)
{
    int ret;
    int idx;
    int maxAtr;

   const char* id;
   const char* val;

    //save tag name
    memset(tag, 0, sizeof(tag));
    memcpy(tag, name, strlen(name));
    maxAtr = XMLs_Attributes_GetCount(atr);
    trcS("Xml Tag=");
    trcS(name);

    // call vmt for attributes and value
    for(idx=0; idx<(int)maxAtr; idx++)
    {
        ret = XMLs_Attributes_GetByIndex(atr, idx, &id, &val);
        trcS(" ");
        trcS("Xml Attr=");
        trcS(id);
        trcS(" ");
        trcS("Xml Val=");
        trcS(val);
        trcS(" ");
    }

    trcS("\n");
}

/** Obtain the value from the current xml tag/element
 */
static void getTagVal( XMLs_PARSER  parser, const char*  buf, unsigned int len )
{
    char* val;
    char* tagName=NULL;
    
    val = XMLs_ProcessData(buf, len, XML_DATA_ALL);
    tagName=strupper(tag);

    if ((strcmp("Parameters", tagName)!=0) && (val!=NULL))
    {
        trcS(tag);
        trcS("=");
        trcS(val);
        trcS("\n");

        strcat(fileBuf, tag);
        fileLen += strlen(tag);

        strcat(fileBuf, "=");

        strcat(fileBuf, val);
        fileLen += strlen(val);

        strcat(fileBuf, "\n");
        fileLen += 2;
    }
}

static int xmlParse(const unsigned char* filename)
{
    int ret;
    XMLs_PARSER parser;

    trcS("xmlParse Beg\n");
    // Create the parser
    parser =  XMLs_Create();
    CHECK(parser!=NULL, lblKO);

    // Set the parsing callbacks.
    ret = XMLs_SetOption(parser, XMLs_START_ELEMENT_HANDLER, getAtrVal);
    CHECK(ret==XMLS_OK, lblKO);
    ret = XMLs_SetOption(parser, XMLs_DATA_HANDLER, getTagVal);
    CHECK(ret==XMLS_OK, lblKO);

    ret = XMLs_ParseFile(parser, filename);
    CHECK(ret==XMLS_OK, lblKO);

    // Destroy the parser
    ret = XMLs_Destroy(parser);
    CHECK(ret==XMLS_OK, lblKO);
    ret = 1;
    goto lblEnd;
    lblKO:
        ret = -1;
    lblEnd:
        trcFN("xmlParse ret=%d\n", ret);
        return ret;
}

int dpmInit(const char*filename)
{
    int ret;
    char xmlFile[128];
    tStream *stm;

    trcS("dpmInit Beg\n");
    fileLen=0;
    memset(fileBuf, 0, sizeof(fileBuf));

    memset(xmlFile, 0, sizeof(xmlFile));
    strcat(xmlFile, "/HOST/");
    strcat(xmlFile, filename);
    strcat(xmlFile, ".XML");

    memset(txtFile, 0, sizeof(txtFile));
    strcat(txtFile, filename);
    strcat(txtFile, ".TXT");

    trcS("Parsing File ");
    trcS(xmlFile);
    trcS("\n");

    ret = xmlParse(xmlFile);
    if (ret!=1)
    {
        trcS("Parsing Failed or File /HOST/PARAM.XML Not Found\n");
        return ret;
    }

    stm = stmFileInit(txtFile, "w+");
    if(stm == 0)
    {
        trcS("File ");
        trcS(txtFile);
        trcS(" not found\n");
        return -1;
    }
    else
    {
        trcS("File ");
        trcS(txtFile);
        trcS(" Opened\n");
    }

    trcS(fileBuf);
    ret = stmPutBuf(stm, fileBuf, fileLen);
    stmClose(stm);
    trcFN("dpmInit ret=%d\n", ret);
    return ret;
}

static const char *parseStr(char *dst, const char *src, int len, char separator) {
    VERIFY(dst);
    VERIFY(src);

    while(*src) {
        if(*src == separator) {
            src++;              // skip separator
            break;
        }
        VERIFY(len > 1);        // dim includes ending zero
        *dst++ = *src++;
        len--;
    }

    *dst = 0;
    return src;
}

static int getData(char *dst, const char *src, int len)
{
    int ret;
    char id[128];
    char buf[128];

    ret = 0;
    src = parseStr(id, src, sizeof(id), '=');
    if (*src)
    {
        src = parseStr(buf, src, len, '=');
    }
    else
    {
        return 0;
    }

    if (len>=strlen(buf))
    {
        ret = strlen(buf);
        memcpy(dst, buf, ret);
        trcS("data=");
        trcS(dst);
        trcS("\n");
    }
    return ret;
}

int dpmGet(int id, char *buf, int len)
{
    int ret;
    int res;
    int idx;
    int fsLine;
    char line[128];
    char ch;
    tStream *stm;

    stm = stmFileInit(txtFile, "r");
    if(stm == 0)
    {
        trcS("File not found\n");
        return -1;
    }
    else
    {
        trcS("File Opened\n");
    }

    ret = 0;
    idx = 0;
    fsLine = 0;
    memset(line, 0, sizeof(line));
    res = stmGetBuf(stm, &ch, 1);
    trcS("char=");
    trcBAN(&ch, 1);
    trcS("\n");
    while (res > 0)
    {
        if (ch != '\n'){
            line[idx++] = ch;
        }
        else 
        {
            fsLine++;
            trcFN("Line Number %d\n", fsLine);
            trcS(line);
            trcS("\n");
            line[idx] = '\0';
            if (id==fsLine)
            {
                if (idx==0)
                {
                    ret = 0;
                }
                else
                {
                    trcS("Data Obtained\n");
                    ret = getData(buf, line, len);
                }
                break;
            }
            else
            {
                trcS("Search on next Line\n");
                memset(line, 0, sizeof(line));
            }
            idx = 0;
        }
        res = stmGetBuf(stm, &ch, 1);
        trcS("char=");
        trcBAN(&ch, 1);
        trcS("\n");
    }

    stmClose(stm);
    return ret;
}

int dpmPut(int id, char *buf, int len)
{
    int ret;
    int res;
    int idx;
    int fsLine;
    char ch;
    char str[1024];
    char tmp[128];
    tStream *stm;

    stm = stmFileInit(txtFile, "r+");
    if(stm == 0)
    {
        trcS("File not found\n");
        return -1;
    }
    else
    {
        trcS("File Opened\n");
    }

    ret = len;
    idx=0;
    fsLine = 1;
    memset(str, 0, sizeof(str));
    res = stmGetBuf(stm, &ch, 1);
    trcS("char=");
    trcBAN(&ch, 1);
    trcS("\n");
    while (res > 0)
    {
        str[idx++] = ch;
        if (id==fsLine)
        {
            if (ch == '=')
            {
                memcpy(&str[idx], buf, len);
                idx+=len;
                while (ch != '\n')
                {
                    res = stmGetBuf(stm, &ch, 1);
                    if (res<=0)
                    {
                        break;
                    }
                }
                str[idx++] = ch;
            }
        }
        if (ch == '\n')
        {
            fsLine++;
            trcFN("Line Number %d\n", fsLine);
        }
        res = stmGetBuf(stm, &ch, 1);
        if (res!=0)
        {
            trcS("char=");
            trcBAN(&ch, 1);
            trcS("\n");
        }
    }

    if ((idx==0) ||(fsLine<id+1))
    {
        while (fsLine<id)
        {
            memset(tmp, 0, sizeof(tmp));
            sprintf(tmp, "%d=", fsLine);
            strcat(str, tmp);
            strcat(str, "\n");
            fsLine++;
        }
        memset(tmp, 0, sizeof(tmp));
        sprintf(tmp, "%d=", id);
        strcat(str, tmp);
        strcat(str, buf);
        strcat(str, "\n");
    }

    stmClose(stm);

    stm = stmFileInit(txtFile, "w+");
    if(stm == 0)
    {
        trcS("File not found\n");
        return -1;
    }
    else
    {
        trcS("File Opened\n");
    }

    stmPutBuf(stm, str, strlen(str));
    trcS("Data Saved=");
    trcS(str);

    stmClose(stm);
    return ret;
}

