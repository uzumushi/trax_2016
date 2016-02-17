#ifndef TRAX_ARRAY_KAI_INCLUDE
#define TRAX_ARRAY_KAI_INCLUDE

#include "trax_array.h"

class TRAX_ARRAY_KAI:public TRAX_ARRAY{
public:
	TRAX_ARRAY_KAI();
	void initSearch();
	MOVE getPlace();
	void evaluateValue();
	void setMyColor(TILE);
	virtual bool placeMove(MOVE);
	void copyArrayKai(TRAX_ARRAY_KAI&);
	char getValue();
	
protected:
	void getNextTileBuf();
	char getTileChar();
	TILE mycolor;
	char value;
	COORDINATE xbuf,ybuf;
	TILE tilebuf;
};

#endif