//-------------------------------------------------------------------
//
// Copyright (c) 2001 Sagem Monetel SA, rue claude Chappe,
// 07503 Guilherand-Granges, France, All Rights Reserved.
//
// Sagem Monetel SA has intellectual property rights relating
// to the technology embodied in this software.  In particular, 
// and without limitation, these intellectual property rights 
// may include one or more patents.
//
// This software is distributed under licenses restricting 
// its use, copying, distribution, and decompilation.  
// No part of this software may be reproduced in any form 
// by any means without prior written authorization of 
// Sagem Monetel.
//
// Description: User Interface function set. Miscellaneous.
//      
// Author:      V.GOMES
// Version:     1.0
// Date:        2005/07/22 
//
//-------------------------------------------------------------------

// Includes.
//-------------------------------------------------------------------

#include <SDK30.H>
#include <GL_GraphicLib.h>

#include "string.h"

#include "Utilities.h"

// Defines
//-------------------------------------------------------------------
#define MAXLEN 255

extern int sscanf(const char *buf, const char *format, ...);

// Global variables
//-------------------------------------------------------------------
static T_GL_HGRAPHIC_LIB hGoal = NULL;

T_GL_HGRAPHIC_LIB guiStart(void) {
    if(hGoal==NULL)
    {
        hGoal = GL_GraphicLib_Create();
    }
    return hGoal;
}

void guiStop(void) {
    if(hGoal!=NULL)
    {
        GL_GraphicLib_Destroy(hGoal);
    }
}

int guiScreen(char *title, char *text, int icon, int delay) {
    int ret=0;
    int button;
    unsigned long result;

    guiStart();

    button = GL_BUTTON_NONE;
    switch (icon)
    {
        case GL_ICON_INFORMATION:
        case GL_ICON_WARNING:
        case GL_ICON_ERROR:
            button = GL_BUTTON_VALID;
            break;
        case GL_ICON_QUESTION:
            button = GL_BUTTON_VALID_CANCEL;
            break;
        default:
            break;
    }

    result = GL_Dialog_Message(hGoal, title, text, icon, button, delay);
    ret = result;
    return ret;
}

int guiMenu(int type, int sta, const char *hdr, const char **mnu) {
    int ret;
    static unsigned long sel;
    const char **ptr = NULL;

    CHECK(type > mnuTypeBeg, lblKO);
    CHECK(type < mnuTypeEnd, lblKO);
    guiStart();
    tftStart();
    kbdStart(1);
	
    ptr = mnu;
    switch (type) {
        case mnuTypeIcon:
            sel = GL_Dialog_IconMenu(hGoal, hdr, (const char **) ptr, sta,
                GL_BUTTON_DEFAULT, GL_KEY_1, 60*1000);
            break;
        case mnuTypeButton:
            sel = GL_Dialog_IconButtonMenu(hGoal, hdr, (const char **) ptr, sta,
                GL_BUTTON_DEFAULT, GL_KEY_1, 60*1000);
            break;
        default:
            sel = GL_Dialog_Menu(hGoal, hdr, (const char **) ptr, sta,
                GL_BUTTON_DEFAULT, GL_KEY_1, 60*1000);
            break;
    }

    ret = sel;
    goto lblEnd;
  lblKO:
    ret = -1;
  lblEnd:
    kbdStop();
    tftStop();  	
    return ret;
}

//fill the buf with mask 
static int setMask(char *mask, int len, char *buf, int size) {
    int i;

    memset(buf, 0, size);
    for (i = 1; i < len; i++) {
        strcat(buf, mask);
    }
    return i;
}

static int formatTcp(char *dst, char *src, int len) {
    int dim;

    VERIFY(src);

    for (dim = 0; dim < len; dim++) // Verify the size of the address
    {
        if(dim != 0 && (dim + 1) % 4 == 0 && *src != '.') {
            *dst = '.';         // Add a dot every 4 inputs - the index starts at 0
            len++;
        } else {
            *dst = *src;
            src++;
        }

        dst++;
    }
    *dst = 0;
    dim--;
    return dim;
}

//convert up address to goal format (unsigned long)
static unsigned long convertTcp(char *ip) {
    char i, *tmp;
    unsigned long val = 0, cvt;

    tmp = strtok(ip, ".");
    for (i = 0; i < 4; i++) {
        sscanf(tmp, "%lu", &cvt);
        val <<= 8;
        val |= (unsigned char) cvt;
        tmp = strtok(NULL, ".");
    }
    return (val);
}

static int dialogTcp(char *title, char *text, char *buf, int len) {
    int ret;
    unsigned long ip = 0;
    unsigned long res;
    char tmp[15 + 1];

    VERIFY(buf);
    guiStart();

    memset(tmp, 0, sizeof(tmp));
    strncpy(tmp, buf, strlen(buf));
    ip = convertTcp(tmp);

    res = GL_Dialog_Ip(hGoal, title, text, &ip, 30*1000);
    ret = res;

    if((ret != GL_KEY_CANCEL) && (ret != 0)) 
    {
        memset(tmp, 0, sizeof(tmp));
        sprintf(tmp, "%03d%03d%03d%03d", HBYTE(HWORD(ip)), LBYTE(HWORD(ip)), HBYTE(LWORD(ip)), LBYTE(LWORD(ip)));
        memcpy(buf, tmp, strlen(tmp));
    }

    return ret;
}

static unsigned char chr2nib(char chr) { //convert hexadecimal character to nibble
    switch (chr) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
          return (byte) (chr - '0');
      case 'A':
      case 'B':
      case 'C':
      case 'D':
      case 'E':
      case 'F':
          return (byte) (chr - 'A' + 10);
      case 'a':
      case 'b':
      case 'c':
      case 'd':
      case 'e':
      case 'f':
          return (byte) (chr - 'a' + 10);
      default:
          break;
    }
    return 0x10;                //KO
}

static unsigned char dec2num(unsigned long *num, const char *dec, unsigned char len) {
    unsigned char ret;                   //to be returned: number of characters processed
    unsigned char tmp;

    VERIFY(num);
    VERIFY(dec);

    //normally len is the number of characters to get from source string
    if(!len)
        len = (unsigned char) strlen(dec);   //calcualte length if missing

    ret = 0;
    *num = 0;
    while((*dec == ' ') || (*dec == '\t')) {    //skip blank characters
        dec++;
        ret++;
        CHECK(len, lblKO);      //the input is empty
        len--;
    }

    while(*dec) {               //main loop: perform the conversion
        if(*dec < '0')
            break;
        if(*dec > '9')
            break;
        tmp = chr2nib(*dec++);  //convert one more character
        VERIFY(tmp <= 10);
        CHECK(tmp < 10, lblKO); //validity check
        CHECK(*num <= 0xFFFFFFFFL / 10, lblKO); //dec exceeds 0xFFFFFFFFL
        CHECK(!((*num == 0xFFFFFFFFL / 10) && (tmp > 5)), lblKO);   //dec exceeds 0xFFFFFFFFL
        *num *= 10;             //OK, we can shift it left
        *num += tmp;            //OK, let us do it
        ret++;                  //one more digit processed
        len--;
        if(!len)
            break;
    }

    return ret;
  lblKO:
    return 0;
}

static int dialogDate(char *title, char *text, char *buf, const char *mask, int dly) {
    int ret;
    int delay=0;
    unsigned long datetime;
    unsigned long result;
    char tmp[12 + 1];
    unsigned short year;
    T_GL_DATE date;

    DATE curDate;	
    unsigned long ldate;

    guiStart();

    ret = read_date(&curDate);
    ldate = d_tolong(&curDate);

    date.day = (curDate.day[0] - '0') * 10 + curDate.day[1] - '0';
    date.month = (curDate.month[0] - '0') * 10 + curDate.month[1] - '0';
    date.year = (curDate.year[0] - '0') * 10 + curDate.year[1] - '0';

    date.hour = (curDate.hour[0] - '0') * 10 + curDate.hour[1] - '0';
    date.minute = (curDate.minute[0] - '0') * 10 + curDate.minute[1] - '0';
    date.second = (curDate.second[0] - '0') * 10 + curDate.second[1] - '0';

    if(strcmp(mask, "y/m/d") == 0) {
        if (strlen(buf))
        {
            dec2num(&datetime, &buf[0], 2);
            if (datetime>=date.year)
            {
                if (datetime<=(date.year+30))
                {
                    date.year = datetime + 2000;
                }
                else
                {
                    date.year = datetime + 1900;
                }
            }
            else
            {
                if (date.year<=(datetime+30))
                {
                    date.year = datetime + 2000;
                }
                else
                {
                    date.year = datetime + 1900;
                }            
            }
            dec2num(&datetime, &buf[2], 2);
            date.month = datetime;
            dec2num(&datetime, &buf[4], 2);
            date.day = datetime;
        }
	 else
	 {
	     date.year += 2000;
	 }
    } else {
        ret = strcmp(mask, "H:M:S");
        CHECK(ret==0, lblKO);

        if (strlen(buf))
        {
            dec2num(&datetime, &buf[0], 2);
            date.hour = datetime;
            dec2num(&datetime, &buf[2], 2);
            date.minute = datetime;
            dec2num(&datetime, &buf[4], 2);
            date.second = datetime;	 
        }
    }

    delay = dly*1000;
    result = GL_Dialog_Date(hGoal, title, text, &date, mask, delay);
    ret = result;

    if((ret != GL_KEY_CANCEL) && (ret != 0)) {
        if(strcmp(mask, "y/m/d") == 0) {
            year = date.year % 100;
            sprintf(tmp, "%02d%02d%02d", year, date.month, date.day);
        } else {
            sprintf(tmp, "%02d%02d%02d", date.hour, date.minute, date.second);
        }
        memcpy(buf, tmp, strlen(tmp));
    }

    return ret;
    lblKO:
        return GL_KEY_CANCEL;
}


//enterFmtStr: enter formatted string
// str: string entered. At the beginning it contains initial value. The resulting string is saved here
// fmt: format control character, can take the following values:
//  '*': entering passwords; the characters entered are echoed as '*'
//  '.': entering host IP address; every 4th character would be "."
//  0xFF: echo without formatting
//  '/': entering date, accepts only valid date
//  ':': entering time, accepts only valid time
//  0, 2 or 3: echo formatted amount with related exponent 
//len: buffer str size including ending zero
static unsigned long enterFmtStr(char *title, char *text, char *str, unsigned char fmt, unsigned char len) {
    unsigned long key = 0;               //key pressed
    char buf[MAXLEN + 1];       //contains the current result
    char tmp[MAXLEN + 1];       //contains the formatted string to display
    char mask[MAXLEN + 1];

    VERIFY(str);
    VERIFY(strlen(str) <= (word) (len + 1));    //too long initial strings are not acepted
    VERIFY(len);

    kbdStart(1);
    tftStart();
    memset(tmp, 0, sizeof(tmp));
    memset(buf, 0, sizeof(buf));
    memset(mask, 0, sizeof(mask));
    strcpy(buf, str);           //the initial string will be modified only in case of ENTER is pressed
    switch (fmt) {
      case 0xFF:               //get the last dspWdt(0) characters
          setMask("/d", len, mask, sizeof(mask));
          key = GL_Dialog_Text(hGoal, title, text, mask, buf, len, 30*1000);
          break;
      case 'c':                //any character
          setMask("/c", len, mask, sizeof(mask));
          key = GL_Dialog_Text(hGoal, title, text, mask, buf, len, 30*1000);		  
          break;
      case '.':                //TCP-IP Address entering
          strcpy(tmp, buf);
          key = dialogTcp(title, text, tmp, len);
          formatTcp(buf, tmp, strlen(tmp));
          break;
      case '*':                //password entering
          setMask("/d", len, mask, sizeof(mask));
          key = GL_Dialog_Password(hGoal, title, text, mask, buf, len, 30*1000);
          break;
      case '%':                //password entering
          setMask("/c", len, mask, sizeof(mask));
          key = GL_Dialog_Password(hGoal, title, text, mask, buf, len, 30*1000);
          break;
      case '/':
          strcat(mask, "y/m/d");
          key = dialogDate(title, text, buf, mask, 60);
          break;
      case ':':
          strcat(mask, "H:M:S");
          key = dialogDate(title, text, buf, mask, 60);
          break;
      case 0:
      case 2:
      case 3:                  //amount entering
          switch (fmt) {
            case 0:
                setMask("/d", len - 1, mask, sizeof(mask));
                strcat(mask, "/D");
                break;
            case 2:
                setMask("/d", len - 3, mask, sizeof(mask));
                strcat(mask, "/D./D/D");
                break;
            case 3:
                setMask("/d", len - 4, mask, sizeof(mask));
                strcat(mask, "/D./D/D/D");
                break;
            default:
                break;
          }
          key = GL_Dialog_Amount(hGoal, title, text, mask, buf, len, 0, GL_ALIGN_RIGHT, 30*1000);          
          break;
      default:
          VERIFY(fmt < 4);
          break;
    }

    switch (key) {
      case 0:
          break;                //timeout; the initial string is not modified
      case GL_KEY_CANCEL:
          break;                //aborted; the initial string is not modified
      case GL_KEY_VALID:             //the entering is finished
          VERIFY(strlen(buf) <= len);
          strcpy(str, buf);     //now we can change the initial string
          break;
      default:
          buzzer(10);
          break;                //invalid key pressed
    }

    tftStop();
    kbdStop();
    return key;
}

unsigned long enterStr(char *title, char *text, char *buf, int len) {
    VERIFY(buf);
    return enterFmtStr(title, text, buf, 0xFF, len);
}

unsigned long enterPwd(char *title, char *text, char *buf, int len) {
    VERIFY(buf);
    return enterFmtStr(title, text, buf, (unsigned char) '*', len);
}

unsigned long enterPwdTxt(char *title, char *text, char *buf, int len) {
    VERIFY(buf);
    return enterFmtStr(title, text, buf, (unsigned char) '%', len);
}

unsigned long enterAmt(char *title, char *text, char *buf, int len, int exp) {
    VERIFY(buf);
    VERIFY(len);
    exp %= 10;
    VERIFY(exp == 0 || exp == 2 || exp == 3);
    return enterFmtStr(title, text, buf, exp, (unsigned char) (len + 1));    //maximum amount length = len digits
}

unsigned long enterTcp(char *title, char *text, char *buf, int len) {
    VERIFY(buf);
    return enterFmtStr(title, text, buf, '.', (unsigned char) (len + 1));    //maximum amount length = len digits
}

unsigned long enterTxt(char *title, char *text, char *buf, int len) {
    VERIFY(buf);
    return enterFmtStr(title, text, buf, 'c', len);
}

unsigned long enterDate(char *title, char *text, char *buf, int len) {
    VERIFY(buf);
    return enterFmtStr(title, text, buf, '/', (unsigned char) (len + 1));
}

unsigned long enterTime(char *title, char *text, char *buf, int len) {
    VERIFY(buf);
    return enterFmtStr(title, text, buf, ':', (unsigned char) (len + 1));
}

