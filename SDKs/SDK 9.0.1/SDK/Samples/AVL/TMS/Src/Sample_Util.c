#include "SDK30.H"

#define max_buf_printer 127

/* ========================================================================	*/
/* Alias                                                                    */
/* ========================================================================	*/

#define NIBBLE2HEXCHAR(d,ch) \
if (d >= 0 && d <= 9) ch = (char)(d + '0'); \
else if (d >= 0x0a && d <= 0x0f) ch = (char)((d - 10)+ 'A'); \
else ch = '?';


/**
 * @function     : CUTERMprintLine                                                       
 * @description  : This service prints the text and wait for the end of the job
 * ======================================================================= 
 * @param        : *xs_text : Text to be printed.                                                                             
 * ======================================================================= 
 */
void CUTERMprintLine(char *xs_text)
{
	FILE *lp_printer;

	lp_printer = fopen("PRINTER", "w-");
		
	fprintf(lp_printer,"%s\n", xs_text);
	
	/* wait for print end */
	ttestall(PRINTER, 0);
	
	fclose(stdprt());
}


void CUTERMPrintLogFile(char *xs_text)
{
	FILE *lp_printer;
	int ln,n=0;
	char tmp[max_buf_printer+1];

	lp_printer = fopen("PRINTER", "w-");
		
	ln=strlen(xs_text);
	do
	{
		strncpy(tmp,xs_text+(n*max_buf_printer),max_buf_printer);
		tmp[max_buf_printer]=0x00;
		ln-=max_buf_printer;
		fprintf(lp_printer,"%s\n", tmp);
		n++;
	
	}
	while(ln>0);
	
	/* wait for print end */
	ttestall(PRINTER, 0);
		
	fclose(stdprt());
}

/**
 * @function:    hex2str
 */
void hex2str( char *b,char *des,int len)
{
        unsigned char c,j;
		int shift ;
		int i;
		j=0;
        for (i=0; i < 2*len; i++) 
		{
            shift = ((i & 1) == 1 ? 0 : 4);
            NIBBLE2HEXCHAR(((b[i>>1] >> shift) & 0x0F),c);
			des[j++] = c;
        }
		des[j] =0;
        
}
