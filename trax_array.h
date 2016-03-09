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
	virtual void initField();
	void copyArray(TRAX_ARRAY&);
	virtual bool placeMove(MOVE);
	bool checkMove(MOVE);
	void printField(bool=false) const;
	bool checkWLine() const;
	bool checkRLine() const;
	bool checkWLoop() const;
	bool checkRLoop() const;
	
protected:
	/***function***/
	//field operators
	TILE getElem(COORDINATE,COORDINATE) const;
	TILE *getElemPtr(COORDINATE,COORDINATE);
	void setElem(COORDINATE,COORDINATE,TILE);
	void placeElem(COORDINATE,COORDINATE,TILE);
	void initElem();
	bool checkMove(COORDINATE,COORDINATE,TILE,bool);
	
	//field checkers
	bool isIsolated(COORDINATE,COORDINATE) const;
	bool isProhibited3(COORDINATE,COORDINATE) const;
	bool isConnected(COORDINATE,COORDINATE,TILE) const;
	bool scanForcedArea(COORDINATE,COORDINATE);
	bool scanForcedSpot(COORDINATE,COORDINATE);
	
	//field tracer
	bool traceLine();
	bool traceLine(COORDINATE,bool) const;
	bool traceLoop(COORDINATE,COORDINATE);
	bool traceLoop(COORDINATE,COORDINATE,TILE);
	void traceField(COORDINATE*,COORDINATE*,TILE*) const;
	
	//field accesser
	TILE LTILE(COORDINATE,COORDINATE) const;
	TILE RTILE(COORDINATE,COORDINATE) const;
	TILE UTILE(COORDINATE,COORDINATE) const;
	TILE DTILE(COORDINATE,COORDINATE) const;
	
	//utilities
	TILE exchangeMoveToTile(MOVE) const;
	TILE getSameColorDir(COORDINATE,COORDINATE,TILE) const;
	
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
