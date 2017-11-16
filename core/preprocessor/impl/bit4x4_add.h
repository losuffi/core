#pragma once

#define CCDK_PP_BIT2x2_ADD(x1,x0,y1,y0) CCDK_PP_BIT2x2_ADD_VALUE##x1##x0##y1##y0
#define CCDK_PP_BIT4x4_ADD(x3,x2,x1,x0,y3,y2,y1,y0)   CCDK_PP_BIT4x4_ADD_CONNECT( CCDK_PP_BIT4x4_ADD_HELPER, (CCDK_PP_BIT2x2_ADD(x3,x2,y3,y2), CCDK_PP_BIT2x2_ADD(x1,x0,y1,y0)))
#define CCDK_PP_BIT4x4_ADD_HELPER(s1,r3,r2,s0,r1,r0)  CCDK_PP_BIT4x4_ADD_VALUE##s1##r3##r2##s0##r1##r0

#define CCDK_PP_BIT4x4_ADD_CONNECT(x, y) x y

//   result (sign,high,low)
//   sign = 1 means carry one for high bit2x2
//   sign = 0 means no carry
#define CCDK_PP_BIT2x2_ADD_VALUE0000 0,0,0
#define CCDK_PP_BIT2x2_ADD_VALUE0001 0,0,1
#define CCDK_PP_BIT2x2_ADD_VALUE0010 0,1,0
#define CCDK_PP_BIT2x2_ADD_VALUE0011 0,1,1
#define CCDK_PP_BIT2x2_ADD_VALUE0100 0,0,1
#define CCDK_PP_BIT2x2_ADD_VALUE0101 0,1,0
#define CCDK_PP_BIT2x2_ADD_VALUE0110 0,1,1
#define CCDK_PP_BIT2x2_ADD_VALUE0111 1,0,0
#define CCDK_PP_BIT2x2_ADD_VALUE1000 0,1,0
#define CCDK_PP_BIT2x2_ADD_VALUE1001 0,1,1
#define CCDK_PP_BIT2x2_ADD_VALUE1010 1,0,0
#define CCDK_PP_BIT2x2_ADD_VALUE1011 1,0,1
#define CCDK_PP_BIT2x2_ADD_VALUE1100 0,1,1
#define CCDK_PP_BIT2x2_ADD_VALUE1101 1,0,0
#define CCDK_PP_BIT2x2_ADD_VALUE1110 1,0,1
#define CCDK_PP_BIT2x2_ADD_VALUE1111 1,1,0

// no (*,*,*,1,1,1) or (1,1,1,*,*,*) compose
// format  (s0, b3,b2,b1,b0)
// s0 = 1 carry bit for high 2 bits
// s0 = 0 no carry
#define CCDK_PP_BIT4x4_ADD_VALUE000000   0,0,0,0,0
#define CCDK_PP_BIT4x4_ADD_VALUE000001   0,0,0,0,1
#define CCDK_PP_BIT4x4_ADD_VALUE000010   0,0,0,1,0
#define CCDK_PP_BIT4x4_ADD_VALUE000011   0,0,0,1,1
#define CCDK_PP_BIT4x4_ADD_VALUE000100   0,0,1,0,0
#define CCDK_PP_BIT4x4_ADD_VALUE000101   0,0,1,0,1
#define CCDK_PP_BIT4x4_ADD_VALUE000110   0,0,1,1,0
#define CCDK_PP_BIT4x4_ADD_VALUE001000   0,0,1,0,0
#define CCDK_PP_BIT4x4_ADD_VALUE001001   0,0,1,0,1
#define CCDK_PP_BIT4x4_ADD_VALUE001010   0,0,1,1,0
#define CCDK_PP_BIT4x4_ADD_VALUE001011   0,0,1,1,1
#define CCDK_PP_BIT4x4_ADD_VALUE001100   0,1,0,0,0
#define CCDK_PP_BIT4x4_ADD_VALUE001101   0,1,0,0,1
#define CCDK_PP_BIT4x4_ADD_VALUE001110   0,1,0,1,0
#define CCDK_PP_BIT4x4_ADD_VALUE010000   0,1,0,0,0
#define CCDK_PP_BIT4x4_ADD_VALUE010001   0,1,0,0,1
#define CCDK_PP_BIT4x4_ADD_VALUE010010   0,1,0,1,0
#define CCDK_PP_BIT4x4_ADD_VALUE010011   0,1,0,1,1
#define CCDK_PP_BIT4x4_ADD_VALUE010100   0,1,1,0,0
#define CCDK_PP_BIT4x4_ADD_VALUE010101   0,1,1,0,1
#define CCDK_PP_BIT4x4_ADD_VALUE010110   0,1,1,1,0
#define CCDK_PP_BIT4x4_ADD_VALUE011000   0,1,1,0,0
#define CCDK_PP_BIT4x4_ADD_VALUE011001   0,1,1,0,1
#define CCDK_PP_BIT4x4_ADD_VALUE011010   0,1,1,1,0
#define CCDK_PP_BIT4x4_ADD_VALUE011011   0,1,1,1,1
#define CCDK_PP_BIT4x4_ADD_VALUE011100   1,0,0,0,0
#define CCDK_PP_BIT4x4_ADD_VALUE011101   1,0,0,0,1
#define CCDK_PP_BIT4x4_ADD_VALUE011110   1,0,0,1,0
#define CCDK_PP_BIT4x4_ADD_VALUE100000   1,0,0,0,0
#define CCDK_PP_BIT4x4_ADD_VALUE100001   1,0,0,0,1
#define CCDK_PP_BIT4x4_ADD_VALUE100010   1,0,0,1,0
#define CCDK_PP_BIT4x4_ADD_VALUE100011   1,0,0,1,1
#define CCDK_PP_BIT4x4_ADD_VALUE100100   1,0,1,0,0
#define CCDK_PP_BIT4x4_ADD_VALUE100101   1,0,1,0,1
#define CCDK_PP_BIT4x4_ADD_VALUE100110   1,0,1,1,0
#define CCDK_PP_BIT4x4_ADD_VALUE101000   1,0,1,0,0
#define CCDK_PP_BIT4x4_ADD_VALUE101001   1,0,1,0,1
#define CCDK_PP_BIT4x4_ADD_VALUE101010   1,0,1,1,0
#define CCDK_PP_BIT4x4_ADD_VALUE101011   1,0,1,1,1
#define CCDK_PP_BIT4x4_ADD_VALUE101100   1,1,0,0,0
#define CCDK_PP_BIT4x4_ADD_VALUE101101   1,1,0,0,1
#define CCDK_PP_BIT4x4_ADD_VALUE101110   1,1,0,1,0
#define CCDK_PP_BIT4x4_ADD_VALUE110000   1,1,0,0,0
#define CCDK_PP_BIT4x4_ADD_VALUE110001   1,1,0,0,1
#define CCDK_PP_BIT4x4_ADD_VALUE110010   1,1,0,1,0
#define CCDK_PP_BIT4x4_ADD_VALUE110011   1,1,0,1,1
#define CCDK_PP_BIT4x4_ADD_VALUE110100   1,1,1,0,0
#define CCDK_PP_BIT4x4_ADD_VALUE110101   1,1,1,0,1
#define CCDK_PP_BIT4x4_ADD_VALUE110110   1,1,1,1,0
