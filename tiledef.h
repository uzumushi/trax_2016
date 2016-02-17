#ifndef TILEDEF_INCLUDE
#define TILEDEF_INCLUDE

//color flag definitions
#define RED 0x0f	//00001111
#define BLACK RED	//00001111
#define WHITE 0x00	//00000000

//tile data definitions
#define NULLNODE 0	//00000000
#define RPLUS 0x0c	//00001100
#define WPLUS 0x03	//00000011
#define RSLSH 0x0a	//00001010
#define WSLSH 0x05	//00000101
#define RBSLS 0x09	//00001001
#define WBSLS 0x06	//00000110

//position bit definitions
#define UPOS 0x01	//00000001
#define DPOS 0x02	//00000010
#define LPOS 0x04	//00000100
#define RPOS 0x08	//00001000

//character definitions
#define C_PLUS '+'
#define C_SLSH '/'
#define C_BSLS '\\'

//shift number definitions
#define U_SHIFT 0
#define D_SHIFT 1
#define L_SHIFT 2
#define R_SHIFT 3

#endif