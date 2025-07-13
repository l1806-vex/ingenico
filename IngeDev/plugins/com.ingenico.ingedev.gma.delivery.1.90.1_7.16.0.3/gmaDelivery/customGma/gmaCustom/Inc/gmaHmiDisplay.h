#ifndef __GMA_HMI_DISPLAY_H_INCLUDED
#define __GMA_HMI_DISPLAY_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @file gmaHmiDisplay.h
 */

/**
 * Macro for nibble selection
 */ 
#define NIBBLE(byte, nibble) ((nibble == 0) ? ((byte & 0xF0) >> 4) : (byte & 0x0F))

/**
 * Macro for color selection
 */ 
#define SETCOLOR(colorIn) ((uint8)((gmaUtilTermColor()) ? colorIn : (colorIn == 15 ? 0 : 1)))

#ifdef __cplusplus
}
#endif


#endif
