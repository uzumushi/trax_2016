#include "move.h"
#include "tiledef.h"
#include <iostream>
#include <sstream>
#define ALPNUM 26

MOVE::MOVE(const string& m){//exchenge from notation
	operator=(m);
}

MOVE::MOVE(COORDINATE x_,COORDINATE y_,TILE tile_){
	x=x_;y=y_;tile=tile_;
}

void MOVE::operator=(const string& m){
	int step=0;
	int pos=0;

	x=0;
	y=0;
  
	while(pos < m.length()){
		char mm = m[pos];
		switch(step){
			case 0:
				if(mm=='@'){ x=0; break; }
				if('A'<=mm && mm<='Z'){ x*=26; x+= mm-'A'+1; break; }
				y = mm-'0';
				step = 1;
				break;
	   		case 1:
				if('0'<=mm && mm<='9'){ y*=10; y+= mm-'0'; break; }
				tile = mm;
				step = 2;
				break;
			case 2:break;
		}
		pos++;
	}
}

string MOVE::exchangeToNotation(){
	string str;
	stringstream ss;
	COORDINATE xx=x;
	if(xx>ALPNUM){
		str+= (xx-(ALPNUM+1))/ALPNUM+'A';
		xx = (xx-1)%ALPNUM+1;
	}
	str=xx+'@';        
	ss<<(int)y;
	str+=ss.str();
	str+=tile;
	return str;
}

bool MOVE::operator==(const MOVE& obj){
	return x==obj.x && y==obj.y && tile==obj.tile;
}

ostream& operator<<(ostream& stream, const MOVE& m){
	stream << "X:" << (int)m.x << ", Y:" << (int)m.y << ", Tile:" << m.tile;
	return stream;
}