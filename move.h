#ifndef MOVE_INCLUDE
#define MOVE_INCLUDE

#include "typedef.h"
#include <string>
using namespace std;

class MOVE{
public:
	/***function***/
	MOVE(const string&);
	MOVE(COORDINATE=0,COORDINATE=0,TILE='*');
	void operator=(const string&);
	std::string exchangeToNotation();

	/***variable***/
	COORDINATE x;
	COORDINATE y;
	TILE tile;
};

std::ostream& operator<<(ostream&, const MOVE&);
#endif