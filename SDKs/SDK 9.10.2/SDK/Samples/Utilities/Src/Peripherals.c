/** \file
 * Various TELIUM functions to manage peripherals
 */

// Includes
//-------------------------------------------------------------------
#include <SDK30.H>
#include <GL_GraphicLib.h>

#include "Utilities.h"

// Global variables
//-------------------------------------------------------------------

//Timer
#define tmrN 4
typedef struct {
    unsigned long hi;                    /*!< \brief Most significant 32bits of the timer value. */
    unsigned long lo;                    /*!< \brief Least significant 32bits of the timer value. */
} tTimer;
static tTimer timer[tmrN];

//Printing
static FILE *hPrt = 0;
static unsigned char prtWait = 0;

//Display
static FILE *hDsp = 0;

//Keyboard
static FILE *hKbd = 0;

//Magnetic Card
static FILE *hMag13 = NULL;
static FILE *hMag2 = NULL;
static FILE *hMag3 = NULL;

//Chip Card
static FILE *hSmc[5] = { 0, 0, 0, 0, 0 };
static unsigned char iccType = 0;

//Touch Screen
static FILE *htft;

int prtStart(void) 
{
    trcS("prtStart\n");
    if(IsISC350())
        return 0;

    if(hPrt)
        return 1;

    hPrt = fopen("PRINTER", "w-*");
    CHECK(hPrt, lblKO);
    prtWait = 0;

    return 1;
  lblKO:
    return -1;
}

int prtStop(void) {
    int ret;

    trcS("prtStop\n");
    if(IsISC350())
        return 0;

    if(hPrt) 
    {
        if(prtWait)
            ttestall(PRINTER, 0);
        ret = fclose(hPrt);
        hPrt = 0;
    }
    prtWait = 0;
    return 1;
}

int prtCtrl(void) 
{
    unsigned char sta = 0;

    trcS("prtCtrl\n");
    if(IsISC350())
        return 0;

    VERIFY(hPrt);
    if(prtWait) 
    {
        ttestall(PRINTER, 0);
        prtWait = 0;
    }
    status(hPrt, &sta);
    if(sta & PAPER_OUT)
        return -1;
    return 1;

}

int dspStart(void) {
    trcS("dspStart\n");

    if(!hDsp)
        hDsp = fopen("DISPLAY", "w*");
    CHECK(hDsp, lblKO);

    return 1;
  lblKO:
    return -1;
}

int dspStop(void) {
    trcS("dspStop\n");
    if(hDsp) {
        fclose(hDsp);
    }
    hDsp = 0;
    return 0;
}

int kbdStart(unsigned char fls) {
    trcS("kbdStart\n");

    if(!hKbd) {
        hKbd = fopen("KEYBOARD", "r*");
        CHECK(hKbd, lblKO);
    }

    if(fls)                     // Flush Input Buffer
        reset_buf(hKbd, _receive_id);

    return 1;

  lblKO:
    return -1;
}

int kbdStop(void) {
    trcS("kbdStop\n");
    if(hKbd)
        fclose(hKbd);
    hKbd = 0;
    return 0;
}

char kbdKey(void) {
    int ret;
    byte key = 0;

    ret = ttestall(KEYBOARD, 1);    // wait for the first event

    if(ret & KEYBOARD) {
        key = getchar();
        trcFS("%s: ", "kbdKey");
        trcFN("hex= [%02x] ", key);
        trcFN("chr= [%c]\n", key);
    }
    return key;
}

int tftStart(void) {
    int ret;

    trcS("tftStart Beg\n");

    // Open touch
    if(!htft) {
        htft = fopen("TSCREEN", "r*");
        CHECK(htft, lblKO);
    }

    ret = 1;
    goto lblEnd;
  lblKO:
    ret = -1;
  lblEnd:
    trcFN("tftStart ret=%d\n", ret);
    return ret;
}

int tftStop(void) {
    trcS("tftStop Beg\n");

    if(htft) {
        fclose(htft);
        htft = NULL;;
    }

    trcS("tftStop End\n");
    return 1;
}

int tmrStart(unsigned char tmr, int dly) {
    tTimer cnt;

    VERIFY(tmr < tmrN);

    /* Get the current timer value */
    cnt.hi = 0;
    cnt.lo = get_tick_counter();    // In 10ms ticks.

    /* Set the timer a 'period' into the future */
    cnt.lo += dly;

    /* If an overflow occurs, adjust the high tick counter */
    //if ((unsigned int)dly > (0xffffffffL - cnt.lo))
    if(cnt.lo < (unsigned long) dly)
        (cnt.hi)++;

    /* Assign it to the proper timer */
    timer[tmr].hi = cnt.hi;
    timer[tmr].lo = cnt.lo;

    return dly;
}

int tmrGet(unsigned char tmr) {
    unsigned long hi, lo;
    tTimer cnt;

    VERIFY(tmr < 4);

    /* Get the new time */
    cnt.hi = timer[tmr].hi;
    cnt.lo = timer[tmr].lo;

    hi = 0;
    lo = get_tick_counter();    // In 10ms ticks.

    if(lo < cnt.lo)
        return (cnt.lo - lo);
    return 0;
}

void tmrStop(unsigned char tmr) {
    VERIFY(tmr < 4);
    timer[tmr].hi = 0;
    timer[tmr].lo = 0;
}

int magStart(void) 
{
    trcS("magStart\n");

    hMag13 = fopen("SWIPE31", "r*");
    CHECK(hMag13, lblKO);

    hMag2 = fopen("SWIPE2", "r*");
    CHECK(hMag2, lblKO);

    hMag3 = fopen("SWIPE3", "r*");
    CHECK(hMag3, lblKO);
    return 1;
  lblKO:
    return -1;
}

static int magTrack1(char *trk1, char *src, char *dst) 
{
    int ret = 0;                //to be returned: number of tracks read
    unsigned char len = 0;
    char tmp[128];

    if(trk1) 
    {
        memset(tmp, 0, 128);
        ret = is_iso1(hMag13, &len, tmp);
        trcFS("iso1 : %s\n", tmp);
        CHECK(ret >= ISO_OK, lblEnd);

        if(ret < DEF_SEP) 
        {
            VERIFY(strlen(tmp) < 128);
            src = tmp;
            dst = trk1;
            while(*src) 
            {       //find start sentinel
                if(*src++ == '%')
                    break;
            }
            while(*src) 
            {       //copy all data between start and end sentinels
                if(*src == '?')
                    break;
                *dst++ = *src++;
            }
            trcFS("Track 1 : %s\n", trk1);
        }
    }

  lblEnd:
    return ret;
}

static int magTrack2(char *trk2, char *src, char *dst) 
{
    int ret = 0;                //to be returned: number of tracks read
    unsigned char len = 0;
    char tmp[128];

    if(trk2) 
    {
        memset(tmp, 0, 128);
        ret = is_iso2(hMag2, &len, tmp);
        trcFS("iso2 : %s\n", tmp);
        CHECK(ret >= ISO_OK, lblKO);

        switch (ret) 
        {
          case DEF_SEP:
          case DEF_PAR:
          case DEF_LRC:
          case DEF_LUH:
          case DEF_NUM:
          case NO_DATA:
              goto lblKO;
              break;
        };
        CHECK(ret < DEF_SEP, lblEnd);
        VERIFY(strlen(tmp) < 128);
        src = tmp;
        dst = trk2;
        while(*src) 
        {           //find start sentinel
            if(*src++ == 'B')
                break;
        }
        while(*src) 
        {           //copy all data between start and end sentinels
            if(*src == 'F')
                break;
            if(*src == 'D')
                *src = '=';
            *dst++ = *src++;
        }
        trcFS("Track 2 : %s\n", trk2);
        CHECK(ret >= 0, lblKO);
    }

    goto lblEnd;

  lblKO:
    return -1;
  lblEnd:
    return ret;
}

static int magTrack3(char *trk3, char *src, char *dst) 
{
    int ret = 0;                //to be returned: number of tracks read
    unsigned char len = 0;
    char tmp[128];

    if(trk3) 
    {
        memset(tmp, 0, 128);
        ret = is_iso3(hMag3, &len, tmp);
        trcFS("iso3 : %s\n", tmp);
        CHECK(ret >= ISO_OK, lblEnd);

        if(ret < DEF_SEP) 
        {
            VERIFY(strlen(tmp) < 128);
            src = tmp;
            dst = trk3;
            while(*src) 
            {       //find start sentinel
                if(*src++ == 'B')
                    break;
            }
            while(*src) 
            {       //copy all data between start and end sentinels
                if(*src == 'F')
                    break;
                if(*src == 'D')
                    *src = '=';
                if(*src == '?')
                    break;
                *dst++ = *src++;
            }
            trcFS("Track 3 : %s\n", trk3);
        }
    }

  lblEnd:
    return ret;
}

int magGet(char *trk1, char *trk2, char *trk3) 
{
    int ret;                    //to be returned: number of tracks read
    int ctr;
    int sta;
    int num = 0;
    char *src = 0;
    char *dst = 0;

    VERIFY(hMag13);
    VERIFY(hMag2);
    VERIFY(hMag3);
    reset_buf(hMag13, _receive_id);
    reset_buf(hMag2, _receive_id);
    reset_buf(hMag3, _receive_id);

    ctr = 0;
    while(ctr < 1) 
    {

        sta = ttestall(SWIPE2 | SWIPE31 | SWIPE3, 100); // wait for the first event
        if(sta) 
        {
            trcFN("sta1=%x\n", sta);
        }

        if(sta & SWIPE31) 
        {
            sta |= ttestall(SWIPE2, 100);   //wait for the second event
            trcFN("sta2=%x\n", sta);
        } else if(sta & SWIPE2) 
        {
            sta |= ttestall(SWIPE31, 100);  //wait for the second event
            trcFN("sta31=%x\n", sta);
        } else if(sta & SWIPE3) 
        {
            sta |= ttestall(SWIPE3, 100);   //wait for the third event
            trcFN("sta31=%x\n", sta);
        }
        ctr++;                  //retry if first event retruns timeout / unable to read track data
    }

    //zero pointer means that the info is not needed
    if(trk1)
        *trk1 = 0;
    if(trk2)
        *trk2 = 0;
    if(trk3)
        *trk3 = 0;

    if(sta & SWIPE31) 
    {
        ret = magTrack1(trk1, src, dst);
        trcS("trk1:");
        trcS(trk1);
        trcS("\n");
        if((ret >= ISO_OK) && (ret < DEF_SEP)) 
        {
            num++;
        }
    }

    if(sta & SWIPE2) 
    {
        ret = magTrack2(trk2, src, dst);
        trcS("trk2:");
        trcS(trk2);
        trcS("\n");

        CHECK(ret >= ISO_OK, lblKO);
        num++;
    }

    if(sta & SWIPE3) 
    {
        ret = magTrack3(trk3, src, dst);
        trcS("trk3:");
        trcS(trk3);
        trcS("\n");
        if((ret < DEF_SEP) && (ret >= ISO_OK)) 
        {
            num++;
        }
    }

    goto lblEnd;
  lblKO:
    return -1;
  lblEnd:
    return num;
}

int magStop(void) 
{
    int ret;                    //to be returned: normally zero

    trcS("magStop\n");
    VERIFY(hMag13);
    VERIFY(hMag2);
    VERIFY(hMag3);

    ret = fclose(hMag13);
    hMag13 = 0;
    CHECK(ret == 0, lblKO);

    ret = fclose(hMag2);
    hMag2 = 0;
    CHECK(ret == 0, lblKO);

    ret = fclose(hMag3);
    hMag3 = 0;
    CHECK(ret == 0, lblKO);
    return 0;
  lblKO:
    return -1;
}

static int getMag(char *trk1, char *trk2, char *trk3, int sta) 
{
    int ret;                    //to be returned: number of tracks read
    int num = 0;
    char *src = 0;
    char *dst = 0;

    VERIFY(hMag13);
    VERIFY(hMag2);
    VERIFY(hMag3);

    //zero pointer means that the info is not needed
    if(trk1)
        *trk1 = 0;
    if(trk2)
        *trk2 = 0;
    if(trk3)
        *trk3 = 0;

    if(sta & SWIPE31) 
    {
        ret = magTrack1(trk1, src, dst);
        if((ret >= ISO_OK) && (ret < DEF_SEP)) 
        {
            num++;
        }
    }

    if(sta & SWIPE2) 
    {
        ret = magTrack2(trk2, src, dst);
        CHECK(ret >= ISO_OK, lblKO);
        num++;
    }

    if(sta & SWIPE3) 
    {
        ret = magTrack3(trk3, src, dst);
        if((ret < DEF_SEP) && (ret >= ISO_OK)) 
        {
            num++;
        }
    }

    goto lblEnd;
  lblKO:
    return -1;
  lblEnd:
    return num;
}

int getCard(unsigned char * buf, const char *ctl) 
{
    int ret = 0, mag, icc, kbd;
    int sta;

    VERIFY(buf);
    VERIFY(ctl);

    memset(buf, 0, 128 * 3);
    mag = -1;
    icc = -1;
    kbd = -1;

    while(*ctl) 
    {
        switch (*ctl++) 
        {
          case 'm':
              mag = magStart();
              break;
          case 'c':
              icc = iccStart(0);
              break;
          case 'k':
              kbd = kbdStart(1);
              break;
          default:
              break;
        }
    }

    while(1) 
    {
        if(hMag13 != NULL)
            reset_buf(hMag13, _receive_id);
        if(hMag2 != NULL)
            reset_buf(hMag2, _receive_id);
        if(hMag3 != NULL)
            reset_buf(hMag3, _receive_id);

        sta = ttestall(KEYBOARD | CAM0 | SWIPE31 | SWIPE2 | SWIPE3 | CLESS, 30 * 100);  // Wait for an event  
        sta |= ttestall(sta ^ (SWIPE31 | SWIPE2 | CAM0 | SWIPE3), 10);  // Wait for the second event
        sta |= ttestall(sta ^ (SWIPE31 | SWIPE2 | CAM0 | SWIPE3), 10);  // Wait for the third event
        sta |= ttestall(sta ^ (SWIPE31 | SWIPE2 | CAM0 | SWIPE3), 10);  // Wait for the third event

        CHECK(sta != 0, lblEnd);    // Exit if no event occured after 30s        

        if(icc >= 0) 
        {          //we process chip?
            ret = iccCommand(0, (byte *) 0, (byte *) 0, buf);   //try reset

            if(ret == -iccCardRemoved) 
            {

                ret = 0;        //removed=inserted
            }
            if(ret == -iccDriverPb) 
            {   //driver works fine?

                ret = 0;
                icc = -1;       //don't ask for icc any more
            } else if(ret < 0) 
            {

                ret = -iccReadFailure;
                goto lblEnd;
            }
            if(ret > 0) 
            {
                ret = 'c';      //chip car inserted
                trcFN("chip OK : %d\n", ret);
                goto lblEnd;
            }
        }

        if(mag >= 0) 
        {          //we process magstripe?                            
            ret =
                getMag((char *) buf, (char *) buf + 128, (char *) buf + 256,
                       sta);
            if(ret) 
            {
                ret = 'm';      //yes, finished
                trcFN("mag OK : %d\n", ret);
                goto lblEnd;
            }
        }

        if(kbd >= 0) 
        {          //we process keyboard?
            ret = kbdKey();
            CHECK(ret != '\xFF', lblKO);    //errors are not acceptable        
            if(ret) 
            {           //key pressed
                switch (ret) 
                {
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
                        if(kbd < 0) 
                        {
                            buzzer(10);
                            ret = kbdStart(1);
                            CHECK(ret, lblKO);
                            continue;
                        }
                        *buf = ret;   //put it into buffer
                        ret = 'k';
                        break;
                    case GL_KEY_CANCEL:
                        *buf = ret;   //put it into buffer
                        ret = 'k';
                        goto lblEnd;
                    default:
                        buzzer(10);
                        kbdStop();
                        ret = kbdStart(1);
                        CHECK(ret, lblKO);
                        continue;
                }
                goto lblEnd;
            }
        }
    }

    lblKO:
        trcErr(ret);
        ret = -1;
    lblEnd:
        if(mag >= 0)
            magStop();
        if(icc >= 0)
            iccStop(0);
        kbdStop();
        return ret;
}

int iccStart(byte rdr) 
{
    char tmp[4 + 1];            //used to generate channel name

    trcFN("iccStart rdr=%d\n", (int) rdr);

    iccType = rdr >> 4;
    rdr &= 0x0F;
    VERIFY(rdr < 5);

    if(rdr == 0) {
        strcpy(tmp, "CAM0");
        tmp[3] = '0' + rdr;
    } else {
        strcpy(tmp, "SAM0");
        tmp[3] = '0' + rdr;
    }

    hSmc[rdr] = 0;
    switch (iccType) {
      case 0:
      case 1:
          hSmc[rdr] = fopen(tmp, "rw*");
          break;
      default:
          VERIFY(iccType <= 1);
          break;
    }
    CHECK(hSmc[rdr], lblKO);

    trcS("iccStart OK\n");
    return 1;
  lblKO:
    return -1;
}

int iccStop(byte rdr) 
{
    VERIFY(rdr < 5);
    trcFN("iccStop rdr=%d\n", (int) rdr);

    if(hSmc[rdr])
        fclose(hSmc[rdr]);
    hSmc[rdr] = 0;
    return 0;
}

int iccDetect(byte rdr) 
{
    byte stat;
    static FILE *smc;           //temporary file handler

    VERIFY(rdr < 5);
    trcFN("iccDetect rdr=%d\n", (int) rdr);

    if(hSmc[rdr] == NULL) 
    {
        char tmp[4 + 1];        //used to generate channel name        

        strcpy(tmp, "CAM0");
        tmp[3] = '0' + rdr;
        smc = stdperif(tmp, NULL);  //icc is started/handled by the manager          
    } else 
    {
        smc = hSmc[rdr];        //icc is started/handled by the application
    }
    CHECK(smc, lblEnd);

    status(smc, &stat);
    if(stat & CAM_PRESENT) 
    {
        trcS("ICC PRESENT\n");
        return 1;
    }

  lblEnd:
    trcS("ICC NOT PRESENT\n");
    return 0;
}

void detectCard(void) {
    int ret;

    ret = iccStart(0);
    if(ret < 0)
        return;

    do {
        ret = iccDetect(0);
    } while(ret > 0);
    iccStop(0);
}

static int iccCmdEmv(byte rdr, const byte * cmd, const byte * dat, byte * rsp) {
    int ret;
    T_APDU apduC;               // Command APDU
    T_APDU apduR;               // Response APDU
    byte snd[262];
    byte rcv[262];
    HISTORIC atr;

    trcS("iccCmdEmv\n");
    VERIFY(rdr < 5);

    memset(&apduC, 0, sizeof(apduC));
    memset(&apduR, 0, sizeof(apduR));
    if(rsp)
        memset(rsp, 0, 260);
    if(cmd) 
    {                   //there is a command to send
        memset(snd, 0x00, sizeof(snd));
        memcpy(snd, cmd + 1, 5);
        memcpy(snd + 4, dat, *dat + 1);
        memset(rcv, 0, sizeof(rcv));
        apduC.data = snd;
        apduC.length = 5 + dat[0];
        apduR.data = rcv;

        if(*cmd == 4) 
        {
            apduC.length++;
        }
        trcS("snd:");
        trcBuf(apduC.data, apduC.length);
        trcS("\n");
        ret = EMV_apdu(hSmc[rdr], &apduC, &apduR);
        if(ret == 0) 
        {
            trcS("rcv: ");
            trcBuf(rcv, apduR.length);
            trcS("\n");

            if(*rcv == 0x61) 
            {  //retrieve response data
                memcpy(snd, "\x00\xC0\x00\x00", 4);
                snd[4] = rcv[1];
                apduC.length = 5;
                ret = EMV_apdu(hSmc[rdr], &apduC, &apduR);
                if(ret == 0) 
	         {
                    ret = apduR.length;
                    if(rsp)
                        memcpy(rsp, rcv, ret);
                } else
                    ret = -ret;
            } else 
            {
                if(rsp)
                    memcpy(rsp, rcv, apduR.length);
            }
        } else
            ret = -ret;
    } else 
    { //no command, POWERON assumed
        trcS("Power On\n");
        ret = EMV_power_on(hSmc[rdr], &atr);
        if(ret == 5)            //try once more: the first time usually it does not work
            ret = EMV_power_on(hSmc[rdr], &atr);
        if(ret == 0) 
        {
            trcS("atr: ");
            trcBuf(atr.historic, atr.length);
            trcS("\n");
            ret = 4 + atr.length;   //compatibility issue with ingenico: the first 4 bytes are Answer-To-Reset - TBD
            if(rsp)
                memcpy(rsp + 4, atr.historic, ret);
        } else
            ret = -ret;
    }
    if(ret < 0) 
    {
        switch (-ret) 
        {
            case 1:
            case 7:
                ret = -iccCardRemoved;
                break;
            case 2:
            case 4:
            case 5:
                ret = -iccCardPb;
                break;
            case 3:
                ret = -iccCardMute;
                break;
            case 6:
                ret = -iccReadFailure;
                break;
            default:
                ret = -iccDriverPb;
                break;
        }
    }
    return ret;
}

static int iccCmd7816(byte rdr, const byte * cmd, const byte * dat, byte * rsp) 
{
    int ret = 0;
    COMMAND_CAM cam;
    HISTORIC atr;

    trcS("iccCmd7816\n");
    VERIFY(rdr < 5);

    memset(&cam, 0, sizeof(cam));
    memset(&atr, 0, sizeof(atr));
    if(rsp)
        memset(rsp, 0, 260);
    if(cmd) 
    { //there is a command to send
        cam.header = (unsigned char *) cmd + 1;
        switch (*cmd) 
        {         //command type
            case 0:              //without any protocol
            case 1:              //no input, no output
            case 3:              //some input, no output
                trcS("SV_input_command\n");
                if(dat)
                cam.data = (byte *) dat + 1;
                ret = SV_input_command(hSmc[rdr], &cam);
                if(ret)
                ret = -ret;
                break;
            case 2:              //no input, some output
            case 4:              //some input, some output
                trcS("SV_output_command\n");
                VERIFY(rsp);
                cam.data = rsp;
                ret = SV_output_command(hSmc[rdr], &cam);
                if(ret==0)          //OK
                    ret = cmd[5]; //length of data to read
                else
                    ret = -ret;
                break;
            default:
                VERIFY(*cmd < 4);
                break;
        }

        if(ret >= 0) 
        {
            if(rsp) 
            {
                rsp[ret++] = cam.statusword1;
                rsp[ret++] = cam.statusword2;
            }
        }
    } 
    else 
    {                    //no command, POWERON assumed
        trcS("Power On\n");
        ret = SV_power_on(hSmc[rdr], &atr);
        if(ret == 0) 
        {
            trcS("atr: ");
            trcBuf(atr.historic, atr.length);
            trcS("\n");
            ret = 4 + atr.length;   //compatibility issue with ingenico: the first 4 bytes are Answer-To-Reset - TBD
            if(rsp)
                memcpy(rsp + 4, atr.historic, ret);
        } 
        else
            ret = -ret;
    }
    if(ret < 0) 
    {
        switch (-ret) 
        {
            case 1:
            case 7:
                ret = -iccCardRemoved;
                break;
            case 2:
            case 4:
            case 5:
                ret = -iccCardPb;
                break;
            case 3:
                ret = -iccCardMute;
                break;
            case 6:
                ret = -iccReadFailure;
                break;
            default:
                ret = -iccDriverPb;
                break;
        }
    }
    return ret;
}

int iccCommand(unsigned char rdr, const unsigned char * cmd, const unsigned char * dat, unsigned char * rsp) 
{
    int ret;

    VERIFY(rdr < 5);
    if(!hSmc[rdr]) 
    {
        ret = 0;
        goto lblEnd;
    }
    trcS("iccCommand ");
    if(cmd) 
    {
        trcS("cmd: ");
        trcBuf(cmd, 6);
        trcS("\n");
    }
    if(dat) 
    {
        trcS("dat: ");
        trcBuf(dat, *dat + 1);
        trcS("\n");
    }
    switch (iccType) 
    {
         case 0:
             ret = iccCmdEmv(rdr, cmd, dat, rsp);
             break;
         default:
             VERIFY(iccType == 1);
             ret = iccCmd7816(rdr, cmd, dat, rsp);
             break;
    }
    if(rsp && (ret > 0)) 
    {
        trcS("rsp: ");
        trcBuf(rsp, ret);
        trcS("\n");
    }
  lblEnd:
    trcFN("iccCommand ret=%d\n", ret);
    return ret;
}

