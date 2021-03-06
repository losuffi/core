#pragma once

#include<ccdk/preprocessor/bool_or.h>
#include<ccdk/preprocessor/bool_and.h>
#include<ccdk/preprocessor/bool_if.h>
#include<ccdk/preprocessor/seq_unpack.h>
#include<ccdk/preprocessor/impl/bit4x4_add.h>

// byte1 + byte2
// do unpack byte1 and byte2
#define CCDK_PP_BYTE_ADD(byte1, byte2)                         \
			CCDK_PP_BYTE_ADD_CONNECT1( CCDK_PP_BYTE_ADD_STEP1,  \
				(CCDK_PP_UNPACK(byte1),                    \
					CCDK_PP_UNPACK(byte2)))
// byte1 + byte2 + byte3
#define CCDK_PP_BYTE_ADD3(byte1, byte2, byte3)        CCDK_PP_BYTE_ADD(byte1, CCDK_PP_BYTE_ADD(byte2, byte3))

// byte1 + byte2 + byte3 + byte4
#define CCDK_PP_BYTE_ADD4(byte1, byte2, byte3, byte4) CCDK_PP_BYTE_ADD(CCDK_PP_BYTE_ADD(byte1, byte2), CCDK_PP_BYTE_ADD(byte3, byte4))

//do high-4bit and low-4bit add
#define CCDK_PP_BYTE_ADD_STEP1(x7,x6,x5,x4,x3,x2,x1,x0,y7,y6,y5,y4,y3,y2,y1,y0) \
			CCDK_PP_BYTE_ADD_CONNECT2(CCDK_PP_BYTE_ADD_STEP2,                    \
				(CCDK_PP_BIT4x4_ADD(x7, x6, x5, x4, y7, y6, y5, y4),            \
				 CCDK_PP_BIT4x4_ADD(x3, x2, x1, x0, y3, y2, y1, y0)))

// if(s1==1 ) 
//    overflow return 255
// else 
//    check carry bit 
#define CCDK_PP_BYTE_ADD_STEP2(s1,r7,r6,r5,r4,s0,r3,r2,r1,r0)                \
			CCDK_PP_IF(s1,                                                   \
				CCDK_PP_BYTE_ADD_GT_255,                                     \
				CCDK_PP_BYTE_ADD_LE_255)(r7,r6,r5,r4,s0,r3,r2,r1,r0)

// overflow return 255
#define CCDK_PP_BYTE_ADD_GT_255(...) (1,1,1,1,1,1,1,1)

// check carry bit 
// if( s0 == 1)
//    return (high-4bit + 1) | low-4bit 
// else
//    return hight-4bit | low-4bit
#define CCDK_PP_BYTE_ADD_LE_255(r7,r6,r5,r4,s0,r3,r2,r1,r0)                  \
			CCDK_PP_IF(s0,                                                   \
				CCDK_PP_BYTE_ADD_ON_LOW_SIGN,                                \
				CCDK_PP_BYTE_ADD_NO_CHANGE)(r7, r6, r5, r4, r3, r2, r1, r0)

// return hight-4bit | low-4bit
#define CCDK_PP_BYTE_ADD_NO_CHANGE(...) (__VA_ARGS__)
// return (high-4bit + 1) | low-4bit 
#define CCDK_PP_BYTE_ADD_ON_LOW_SIGN(r7, r6, r5, r4, r3, r2, r1, r0) (CCDK_PP_BIT4_ADD1_VALUE##r7##r6##r5##r4, r3,r2,r1,r0)

//  (high-4bit + 1) lookup table
#define CCDK_PP_BIT4_ADD1_VALUE0000 0,0,0,1
#define CCDK_PP_BIT4_ADD1_VALUE0001 0,0,1,0
#define CCDK_PP_BIT4_ADD1_VALUE0010 0,0,1,1
#define CCDK_PP_BIT4_ADD1_VALUE0011 0,1,0,0
#define CCDK_PP_BIT4_ADD1_VALUE0100 0,1,0,1
#define CCDK_PP_BIT4_ADD1_VALUE0101 0,1,1,0
#define CCDK_PP_BIT4_ADD1_VALUE0110 0,1,1,1
#define CCDK_PP_BIT4_ADD1_VALUE0111 1,0,0,0
#define CCDK_PP_BIT4_ADD1_VALUE1000 1,0,0,1
#define CCDK_PP_BIT4_ADD1_VALUE1001 1,0,1,0
#define CCDK_PP_BIT4_ADD1_VALUE1010 1,0,1,1
#define CCDK_PP_BIT4_ADD1_VALUE1011 1,1,0,0
#define CCDK_PP_BIT4_ADD1_VALUE1100 1,1,0,1
#define CCDK_PP_BIT4_ADD1_VALUE1101 1,1,1,0
#define CCDK_PP_BIT4_ADD1_VALUE1110 1,1,1,1

//helper function
#define CCDK_PP_BYTE_ADD_CONNECT1(x, y) CCDK_PP_BYTE_ADD_CONNECT1_STEP1(x, y)
#define CCDK_PP_BYTE_ADD_CONNECT1_STEP1(x, y) CCDK_PP_BYTE_ADD_CONNECT1_STEP2(x y)
#define CCDK_PP_BYTE_ADD_CONNECT1_STEP2(result) result
#define CCDK_PP_BYTE_ADD_CONNECT2(x, y) CCDK_PP_BYTE_ADD_CONNECT2_STEP1(x, y)
#define CCDK_PP_BYTE_ADD_CONNECT2_STEP1(x, y) CCDK_PP_BYTE_ADD_CONNECT2_STEP2(x y)
#define CCDK_PP_BYTE_ADD_CONNECT2_STEP2(result) result
