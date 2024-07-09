#ifndef __OLED_DATA_H
#define __OLED_DATA_H

#include <stdint.h>

#define OLED_CHN_CHAR_WIDTH			3		

typedef struct 
{
	char Index[OLED_CHN_CHAR_WIDTH + 1];	
	uint8_t Data[32];						
} ChineseCell_t;


extern const uint8_t OLED_F8x16[][16];
extern const uint8_t OLED_F6x8[][6];


extern const ChineseCell_t OLED_CF16x16[];


extern const uint8_t Diode[];
extern const unsigned char FaceBlock[];		
extern const unsigned char FaceEvil[];		
extern const unsigned char FaceCry[];		
extern const unsigned char FaceSleep[];	
extern const unsigned char FaceDou[];		
extern const unsigned char FaceRight[];	
extern const unsigned char FaceLeft[];		
extern const unsigned char FaceAss[];	

#endif

