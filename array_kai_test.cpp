#include <string>
#include <iostream>
using namespace std;

#include <stdlib.h>
#include <time.h>

#include "trax_array_kai.h"

bool placeTest(TRAX_ARRAY_KAI& array,string move);

int main(){
	TRAX_ARRAY_KAI array;
	MOVE mo;
	srand(time(0));

	for(int i=1;array.getValue()==0;i++){
		int N=rand()%(i*4);
		for(int j=0;j<N;j++){
			mo=array.getMove();
			if(!mo.tile)mo=array.getMove();
		}
		placeTest(array,mo.exchangeToNotation());
	}
	return 0;
}

bool placeTest(TRAX_ARRAY_KAI& array,string move){
	MOVE mo(move);
	bool flag=array.placeMove(mo);
	cout<<move<<endl;
	array.printField();
	return flag;
}