#ifndef TRAX_ARRAY_INCLUDE
#define TRAX_ARRAY_INCLUDE

#include "typedef.h"
#include "move.h"

const COORDINATE WIDTH=512;
const COORDINATE FIELD_CENTER=WIDTH/2;

class TRAX_ARRAY{
public:
	/***function***/
	TRAX_ARRAY();
	void initField();
	void copyArray(TRAX_ARRAY&);
	virtual bool placeMove(MOVE);
	bool checkMove(MOVE);
	void printField(bool=false);
	bool checkWLine();
	bool checkRLine();
	bool checkWLoop();
	bool checkRLoop();
	
protected:
	/***function***/
	//field operators
	TILE getElem(COORDINATE,COORDINATE);
	void setElem(COORDINATE,COORDINATE,TILE);
	void placeElem(COORDINATE,COORDINATE,TILE);
	bool checkMove(COORDINATE,COORDINATE,TILE,bool);
	
	//field checkers
	bool isIsolated(COORDINATE,COORDINATE);
	bool isProhibited3(COORDINATE,COORDINATE);
	bool isConnected(COORDINATE,COORDINATE,TILE);
	bool scanForcedArea(COORDINATE,COORDINATE);
	bool scanForcedSpot(COORDINATE,COORDINATE);
	
	//field tracer
	bool traceLine();
	bool traceLine(COORDINATE,bool);
	bool traceLoop(COORDINATE,COORDINATE);
	bool traceLoop(COORDINATE,COORDINATE,TILE);
	void traceField(COORDINATE*,COORDINATE*,TILE*);
	
	//field accesser
	TILE LTILE(COORDINATE,COORDINATE);
	TILE RTILE(COORDINATE,COORDINATE);
	TILE UTILE(COORDINATE,COORDINATE);
	TILE DTILE(COORDINATE,COORDINATE);
	
	//utilities
	TILE exchangeMoveToTile(MOVE);
	TILE getSameColorDir(COORDINATE,COORDINATE,TILE);
	
	/***variable***/
	TILE field[WIDTH][WIDTH];//filed variable
	COORDINATE left;	//position of left terminal-1
	COORDINATE right;	//position ofright terminal-1
	COORDINATE top;		//position of top terminal
	COORDINATE bottom;	//position of bottom terminal
	int tiles;//number of tiles
	
	bool rloop;
	bool wloop;
	bool rline;
	bool wline;
};

#endif
