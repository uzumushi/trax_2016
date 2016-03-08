#include <iostream>
#include <iomanip>
using namespace std;

#include "trax_array.h"
#include "tiledef.h"

const int WINWIDTH=8;

const bool HORIZONTAL=false;
const bool VERTICAL=true;

/*****public functions*****/
TRAX_ARRAY::TRAX_ARRAY(){
	initField();
}

void TRAX_ARRAY::initField(){
	for(COORDINATE x=0;x<WIDTH;x++){
		for(COORDINATE y=0;y<WIDTH;y++){
			setElem(x,y,NULLNODE);
		}
	}
	left=0;
	right=0;
	bottom=0;
	top=0;
	tiles=0;
	rloop=false;
	wloop=false;
	rline=false;
	wline=false;
}

void TRAX_ARRAY::copyArray(TRAX_ARRAY& cpyfield){
	initField();
	
	left=cpyfield.left;
	right=cpyfield.right;
	top=cpyfield.top;
	bottom=cpyfield.bottom;
	tiles=cpyfield.tiles;
	
	rloop=cpyfield.rloop;
	wloop=cpyfield.wloop;
	rline=cpyfield.rline;
	wline=cpyfield.wline;
	for(COORDINATE x=left+FIELD_CENTER+1;x<=right+FIELD_CENTER;x++){
		for(COORDINATE y=top+FIELD_CENTER+1;y<=bottom+FIELD_CENTER;y++){
			setElem(x,y,cpyfield.getElem(x,y));
		}
	}
}

bool TRAX_ARRAY::checkMove(MOVE mo){
	return checkMove(mo.x+FIELD_CENTER+left,mo.y+FIELD_CENTER+top,exchangeMoveToTile(mo),false);
}

bool TRAX_ARRAY::placeMove(MOVE mo){
	return checkMove(mo.x+FIELD_CENTER+left,mo.y+FIELD_CENTER+top,exchangeMoveToTile(mo),true);
}

//debug function
void TRAX_ARRAY::printField(bool flag) const{
	ostream* ost;
	if(!flag) ost=&cout;
	else ost=&cerr;
	
	for(COORDINATE y=top+FIELD_CENTER;y<=bottom+FIELD_CENTER+1;y++){
		if(y==top+FIELD_CENTER){
			for(COORDINATE x=left+FIELD_CENTER;x<=right+FIELD_CENTER+1;x++){
				if(x==left+FIELD_CENTER) (*ost)<<"  @";
				else (*ost)<<(char)('A'+x-(left+FIELD_CENTER)-1);
			}
			(*ost)<<endl;
		}
		for(COORDINATE x=left+FIELD_CENTER;x<=right+FIELD_CENTER+1;x++){
			char c;
	
			if(x==left+FIELD_CENTER) (*ost)<<setw(2)<<y-(FIELD_CENTER+top);
			switch(getElem(x,y)){
				case RPLUS:c='a';break;
				case WPLUS:c='b';break;
				case RSLSH:c='c';break;
				case WSLSH:c='d';break;
				case RBSLS:c='e';break;
				case WBSLS:c='f';break;
				case NULLNODE:c='*';break;
			}
			(*ost)<<c;
		}
		(*ost)<<endl;
	}
	(*ost)<<endl;
}

bool TRAX_ARRAY::checkWLine() const{
	return wline;
}
bool TRAX_ARRAY::checkRLine() const{
	return rline;
}
bool TRAX_ARRAY::checkWLoop() const{
	return wloop;
}
bool TRAX_ARRAY::checkRLoop() const{
	return rloop;
}

/*****private functions*****/
//field operators
inline TILE TRAX_ARRAY::getElem(COORDINATE x,COORDINATE y) const{
	return field[x][y];
}

inline void TRAX_ARRAY::setElem(COORDINATE x,COORDINATE y,TILE tile){
	field[x][y]=tile;
}

inline void TRAX_ARRAY::placeElem(COORDINATE x,COORDINATE y,TILE tile){
	setElem(x,y,tile);
	if(x==FIELD_CENTER+left)left--;
	if(y==FIELD_CENTER+top)top--;
	if(x>right+FIELD_CENTER)right++;
	if(y>bottom+FIELD_CENTER)bottom++;
	tiles++;
	traceLoop(x,y);
}

inline bool TRAX_ARRAY::checkMove(COORDINATE x,COORDINATE y,TILE tile,bool place_flag){
	
	if(tile==NULLNODE) return false;
	if(getElem(x,y) || isIsolated(x,y) || isProhibited3(x,y)||!isConnected(x,y,tile)) return false;
	else{
		TRAX_ARRAY array_buf;
		array_buf.copyArray(*this);
		array_buf.placeElem(x,y,tile);
		if(!array_buf.scanForcedArea(x,y)) return false;
		array_buf.traceLine();
		if(place_flag) copyArray(array_buf);
	}
	return true;	
}

//field checkers
inline bool TRAX_ARRAY::isIsolated(COORDINATE x,COORDINATE y) const{
	return tiles&&!(getElem(x-1,y)||getElem(x,y-1)||getElem(x+1,y)||getElem(x,y+1));
}

inline bool TRAX_ARRAY::isProhibited3(COORDINATE x,COORDINATE y) const{
	char white=0,red=0;
	if(LTILE(x,y)) LTILE(x,y)&RPOS ? red++:white++; 
	if(RTILE(x,y)) RTILE(x,y)&LPOS ? red++:white++;
	if(UTILE(x,y)) UTILE(x,y)&DPOS ? red++:white++;
	if(DTILE(x,y)) DTILE(x,y)&UPOS ? red++:white++;
	if(red>=3||white>=3)return true;
	return false;
}

inline bool TRAX_ARRAY::isConnected(COORDINATE x,COORDINATE y,TILE tile) const{
	if(UTILE(x,y) && (UTILE(x,y)&DPOS)>>D_SHIFT != (tile&UPOS)>>U_SHIFT)return false;
	if(DTILE(x,y) && (DTILE(x,y)&UPOS)>>U_SHIFT != (tile&DPOS)>>D_SHIFT)return false;
	if(LTILE(x,y) && (LTILE(x,y)&RPOS)>>R_SHIFT != (tile&LPOS)>>L_SHIFT)return false;
	if(RTILE(x,y) && (RTILE(x,y)&LPOS)>>L_SHIFT != (tile&RPOS)>>R_SHIFT)return false;
	return true;
}

inline bool TRAX_ARRAY::scanForcedArea(COORDINATE x,COORDINATE y){
	if(scanForcedSpot(x-1,y) && scanForcedSpot(x,y-1) && scanForcedSpot(x+1,y) && scanForcedSpot(x,y+1)) return true;
	return false;
}

inline bool TRAX_ARRAY::scanForcedSpot(COORDINATE x,COORDINATE y){
	TILE nodeflag=0;
	char red=0;
	char white=0;
	TILE forced=NULLNODE;
	if(getElem(x,y)) return true;
	
	if(UTILE(x,y))	{	nodeflag+=UPOS; forced+=(UTILE(x,y)&DPOS)>>1; UTILE(x,y)&DPOS ? red++:white++;	}
	if(DTILE(x,y))	{	nodeflag+=DPOS; forced+=(DTILE(x,y)&UPOS)<<1; DTILE(x,y)&UPOS ? red++:white++;	}
	if(LTILE(x,y))	{	nodeflag+=LPOS; forced+=(LTILE(x,y)&RPOS)>>1; LTILE(x,y)&RPOS ? red++:white++;	}
	if(RTILE(x,y))	{	nodeflag+=RPOS; forced+=(RTILE(x,y)&LPOS)<<1; RTILE(x,y)&LPOS ? red++:white++;	}
	
	if(red==3||white==3)return false;
	if(red==2||white==2){
		char remcolor=red>white ? WHITE:RED;
		forced+=remcolor&(~nodeflag)&DPOS;
		forced+=remcolor&(~nodeflag)&UPOS;
		forced+=remcolor&(~nodeflag)&RPOS;
		forced+=remcolor&(~nodeflag)&LPOS;
		placeElem(x,y,forced);
		return scanForcedArea(x,y);
	}
	return true;
}

//field tracer
inline bool TRAX_ARRAY::traceLine(){
	bool found=false;
	if((right-left)>=WINWIDTH){
		for(COORDINATE y=FIELD_CENTER+top+1;y<=FIELD_CENTER+bottom;y++){
			if(getElem(left+FIELD_CENTER+1,y)&&traceLine(y,HORIZONTAL)){
				if(getElem(left+FIELD_CENTER+1,y)&LPOS)
					rline=true;
				else
					wline=true;
				found=true;
			}
		}
	}
	if((bottom-top)>=WINWIDTH){
		for(COORDINATE x=FIELD_CENTER+left+1;x<=FIELD_CENTER+right;x++){
			if(getElem(x,top+FIELD_CENTER+1)&&traceLine(x,VERTICAL)){
				
				if(getElem(x,top+FIELD_CENTER+1)&UPOS)
					rline=true;
				else
					wline=true;
				found=true;
			}
		}
	}
	return found;
}

inline bool TRAX_ARRAY::traceLine(COORDINATE pos,bool dirflag) const{
	COORDINATE x=left+FIELD_CENTER+1;
	COORDINATE y=top+FIELD_CENTER+1;
	TILE dir;
	
	if(dirflag==HORIZONTAL){
		y=pos;
		dir=LPOS;
	}
	else{
		x=pos;
		dir=UPOS;
	}
	do{
		traceField(&x,&y,&dir);	
		if(dirflag==HORIZONTAL && x==(FIELD_CENTER+right+1))return true;
		if(dirflag==VERTICAL && y==(FIELD_CENTER+bottom+1))return true;
	}while(getElem(x,y));
	return false;
}

inline bool TRAX_ARRAY::traceLoop(COORDINATE x,COORDINATE y){
	bool found=false;
	if(getElem(x,y)==RPLUS||getElem(x,y)==WPLUS){
		if(traceLoop(x,y,UPOS))found=true;
		if(traceLoop(x,y,LPOS))found=true;
	}
	else{
		if(traceLoop(x,y,RPOS))found=true;
		if(traceLoop(x,y,LPOS))found=true;
	}
	return found;
}

inline bool TRAX_ARRAY::traceLoop(COORDINATE x,COORDINATE y,TILE dir){
	COORDINATE xx=x;
	COORDINATE yy=y;
	bool found=false;
	do{
		traceField(&xx,&yy,&dir);
		if(x==xx&&y==yy){
			if(getElem(xx,yy)&dir) rloop=true;
			else wloop=true;
			found=true;
			break;
		}
	}while(getElem(xx,yy));
	return found;	
}
inline void TRAX_ARRAY::traceField(COORDINATE* x,COORDINATE* y,TILE* dir) const{
	switch(getSameColorDir(*x,*y,*dir)){
		case LPOS:(*x)--;*dir=RPOS;break;
		case RPOS:(*x)++;*dir=LPOS;break;
		case UPOS:(*y)--;*dir=DPOS;break;
		case DPOS:(*y)++;*dir=UPOS;break;
	}	
}

//field accesser
inline TILE TRAX_ARRAY::LTILE(COORDINATE x,COORDINATE y) const{
	return getElem(x-1,y);	
}
inline TILE TRAX_ARRAY::RTILE(COORDINATE x,COORDINATE y) const{
	return getElem(x+1,y);
}
inline TILE TRAX_ARRAY::UTILE(COORDINATE x,COORDINATE y) const{
	return getElem(x,y-1);
}
inline TILE TRAX_ARRAY::DTILE(COORDINATE x,COORDINATE y) const{
	return getElem(x,y+1);
}

//utilities
inline TILE TRAX_ARRAY::exchangeMoveToTile(MOVE mo) const{
	COORDINATE x=mo.x+left+FIELD_CENTER;
	COORDINATE y=mo.y+top+FIELD_CENTER;
	
	if(x<FIELD_CENTER+left || x>FIELD_CENTER+right+1 || y<FIELD_CENTER+top || y>FIELD_CENTER+bottom+1) return NULLNODE;
	if(x<0 || WIDTH<x || y<0 || WIDTH<y)return NULLNODE;
	
	if(tiles==0){
		if(x!=FIELD_CENTER || y!=FIELD_CENTER)return NULLNODE;
		switch(mo.tile){
			case C_PLUS:return RPLUS;
			case C_SLSH:return RSLSH;
			default: return NULLNODE;
		}
	}
	
	if(mo.tile==C_PLUS){
		if(isConnected(x,y,RPLUS))return RPLUS;
		if(isConnected(x,y,WPLUS))return WPLUS;
		return NULLNODE;
	}
	if(mo.tile==C_SLSH){
		if(isConnected(x,y,RSLSH))return RSLSH;
		if(isConnected(x,y,WSLSH))return WSLSH;
		return NULLNODE;
	}
	if(mo.tile==C_BSLS){
		if(isConnected(x,y,RBSLS))return RBSLS;
		if(isConnected(x,y,WBSLS))return WBSLS;
		return NULLNODE;
	}
	return NULLNODE;

}

inline TILE TRAX_ARRAY::getSameColorDir(COORDINATE x,COORDINATE y,TILE dir) const{
	TILE color=getElem(x,y)&dir ? RED:WHITE;
	if(dir!=LPOS&&(getElem(x,y)&LPOS)==(color&LPOS)){ return LPOS;	}
	if(dir!=RPOS&&(getElem(x,y)&RPOS)==(color&RPOS)){ return RPOS;	}
	if(dir!=UPOS&&(getElem(x,y)&UPOS)==(color&UPOS)){ return UPOS;	}
	if(dir!=DPOS&&(getElem(x,y)&DPOS)==(color&DPOS)){ return DPOS;	}
}
