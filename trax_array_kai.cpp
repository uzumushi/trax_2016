#include "trax_array_kai.h"
#include "tiledef.h"

/*****public function*****/
TRAX_ARRAY_KAI::TRAX_ARRAY_KAI(){
	mycolor=WHITE;
	value=0;
	initSearch();
}
void TRAX_ARRAY_KAI::initSearch(){
	xbuf=FIELD_CENTER+left;
	ybuf=FIELD_CENTER+top;
	tilebuf=RPLUS;
}

MOVE TRAX_ARRAY_KAI::getMove(){
	if(tiles==0){
		MOVE m(0,0,getTileChar());
		switch(tilebuf){
			case RPLUS:tilebuf=RSLSH;break;
			case RSLSH:tilebuf=NULLNODE;break;
			case NULLNODE:tilebuf=RPLUS;break;
		}
		return m;
	}
	
	for(;ybuf<=FIELD_CENTER+bottom+1;ybuf++){
		for(;xbuf<=FIELD_CENTER+right+1;xbuf++){
			while(tilebuf)
			{
				if(field[xbuf][ybuf]!=NULLNODE)break;
			  	if(checkMove(xbuf,ybuf,tilebuf,false)){
					MOVE m(xbuf-left-FIELD_CENTER,ybuf-top-FIELD_CENTER,getTileChar());
					getNextTileBuf();
					return m;
				}
				getNextTileBuf();
			}
			tilebuf=RPLUS;
		}
		xbuf=FIELD_CENTER+left;
	}
	MOVE m(0,0,NULLNODE);
	initSearch();
	return m;
}

void TRAX_ARRAY_KAI::evaluateValue(){
	value=0;
	if(mycolor==RED){
		if(rloop||rline)value=1;
		if(wloop||wline)value=-1;
	}
	if(mycolor==WHITE)
	{
		if(wloop||wline)value=1;
		if(rloop||rline)value=-1;
	}
}

void TRAX_ARRAY_KAI::setMyColor(TILE color){
	mycolor=color;
}

bool TRAX_ARRAY_KAI::placeMove(MOVE m){
	
	if(TRAX_ARRAY::placeMove(m)){
		initSearch();
		evaluateValue();
		return true;
	}
	return false;
}

void TRAX_ARRAY_KAI::copyArrayKai(TRAX_ARRAY_KAI& copyfield){
	copyArray(copyfield);
	mycolor=copyfield.mycolor;
	value=copyfield.value;
	xbuf=copyfield.value;
	ybuf=copyfield.value;
	tilebuf=copyfield.tilebuf;
}

char TRAX_ARRAY_KAI::getValue(){
	return value;	
}

/*****protected function*****/
inline void TRAX_ARRAY_KAI::getNextTileBuf(){
	switch(tilebuf){
		case RPLUS:tilebuf=WPLUS;break;
		case WPLUS:tilebuf=RSLSH;break;
		case RSLSH:tilebuf=WSLSH;break;
		case WSLSH:tilebuf=RBSLS;break;
		case RBSLS:tilebuf=WBSLS;break;
		case WBSLS:tilebuf=NULLNODE;break;
		case NULLNODE:tilebuf=RPLUS;break;
	}		
}

inline char TRAX_ARRAY_KAI::getTileChar(){
	switch(tilebuf){
		case RPLUS:return C_PLUS;
		case WPLUS:return C_PLUS;
		case RSLSH:return C_SLSH;
		case WSLSH:return C_SLSH;
		case RBSLS:return C_BSLS;
		case WBSLS:return C_BSLS;
		default:return NULLNODE;
	}
}