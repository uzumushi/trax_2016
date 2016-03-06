#ifndef TILEDEF_INCLUDE
#define TILEDEF_INCLUDE

#include "typedef.h"

//color flag definitions
const TILE RED=0x0f;	//00001111
const TILE BLACK=RED;	//00001111
const TILE WHITE=0x00;	//00000000

//tile data definitions
const TILE NULLNODE=0;	//00000000
const TILE RPLUS=0x0c;	//00001100
const TILE WPLUS=0x03;	//00000011
const TILE RSLSH=0x0a;	//00001010
const TILE WSLSH=0x05;	//00000101
const TILE RBSLS=0x09;	//00001001
const TILE WBSLS=0x06;	//00000110

//position bit definitions
const TILE UPOS=0x01;	//00000001
const TILE DPOS=0x02;	//00000010
const TILE LPOS=0x04;	//00000100
const TILE RPOS=0x08;	//00001000

//character definitions
const char C_PLUS='+';
const char C_SLSH='/';
const char C_BSLS='\\';

//shift number definitions
const int U_SHIFT=0;
const int D_SHIFT=1;
const int L_SHIFT=2;
const int R_SHIFT=3;

#endif