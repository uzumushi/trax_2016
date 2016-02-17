#include "trax_array.h"
#include <iostream>
#include <string>
using namespace std;

bool placeTest(TRAX_ARRAY&,string&);

int main(){
	TRAX_ARRAY array;
	string str;
	
	while(1){
		cin>>str;
		if(!placeTest(array,str)){
			cout<<"error!"<<endl;
			break;
		}
		if(array.checkRLoop()){
			cout<<"RedLoop is exsiting!"<<endl;
			break;
		}
		if(array.checkWLoop()){
			cout<<"WhiteLoop is exsiting!"<<endl;
			break;
		}
		if(array.checkRLine()){
			cout<<"RedLine is exsiting!"<<endl;
			break;
		}
		if(array.checkWLine()){
			cout<<"WhiteLine is exsiting!"<<endl;
			break;
		}
	}
	return 1;
}

bool placeTest(TRAX_ARRAY& array,string& move){
	MOVE mo(move);
	cout<<move<<endl;
	bool flag=array.placeMove(mo);
	array.printField();
	return flag;
}