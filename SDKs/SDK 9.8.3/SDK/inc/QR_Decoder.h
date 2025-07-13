#ifndef __QR_DECODER_H__
#define __QR_DECODER_H__
/**

 * Encoding mode.
 */
typedef enum {
	QR_MODE_NUL = -1,  ///< Terminator (NUL character). Internal use only
	QR_MODE_NUM = 0,   ///< Numeric mode
	QR_MODE_AN,        ///< Alphabet-numeric mode
	QR_MODE_8,         ///< 8-bit data mode
	QR_MODE_KANJI,     ///< Kanji (shift-jis) mode
	QR_MODE_STRUCTURE ///< Internal use only
} QRencodeMode;

/**
 * Level of error correction.
 */
typedef enum {
	QR_ECLEVEL_UKNOWN = -1, ///< ECLevel not specified
	QR_ECLEVEL_L = 0, ///< lowest
	QR_ECLEVEL_M,
	QR_ECLEVEL_Q,
	QR_ECLEVEL_H      ///< highest
} QRecLevel;
#endif //__QR_DECODER_H__
