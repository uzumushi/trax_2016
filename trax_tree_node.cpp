#include "trax_tree_node.h"
#include "trax_array_kai.h"
#include "tiledef.h"

#include <iostream>
using namespace std;

const bool ALPHA_FLAG=false;
const bool BETA_FLAG=true;

TRAX_ARRAY_KAI TRAX_TREE_NODE::myfield;

TRAX_TREE_NODE::TRAX_TREE_NODE(){
	parent=NULL;
}

TRAX_TREE_NODE::TRAX_TREE_NODE(const MOVE& mo){
	mymove=mo;
	parent=NULL;
}

TRAX_TREE_NODE::TRAX_TREE_NODE(TRAX_TREE_NODE* ptrparent,MOVE mo){
	parent=ptrparent;
	mymove=mo;
}

bool TRAX_TREE_NODE::makeChildren(bool modeflag){
	makeMyArray();
	MOVE mo;
	
	if(myfield.getValue()) return true;
	
	for(mo=myfield.getMove();mo.tile!=NULLNODE;mo=myfield.getMove()){
		static TRAX_ARRAY_KAI fieldbuf;
		fieldbuf.initField();
		fieldbuf.copyArrayKai(myfield);
		fieldbuf.placeMove(mo);
		switch(fieldbuf.getValue()){
		case -1:
			if(modeflag==BETA_FLAG) return false;
		case 1:
			if(modeflag==ALPHA_FLAG){
				TRAX_TREE_NODE nodebuf(this,mo);
				children.push_back(nodebuf);
			}
			break;
		case 0:
			TRAX_TREE_NODE nodebuf(this,mo);
			children.push_back(nodebuf);
			break;
		}
	}
	return true;
}

void TRAX_TREE_NODE::makeDescendent(TILE color,int height){
	if(height<2)return;
	makeDescendent(color,height,height-1);
}

inline bool TRAX_TREE_NODE::makeDescendent(TILE color,int maxheight,int height){
	int depth=maxheight-height;
	
	if(isMyTurn(color,depth)) makeChildren(ALPHA_FLAG);
	else if(!makeChildren(BETA_FLAG)) return false;
	
	if(!(depth<=maxheight-1)) return true;
	for(list<TRAX_TREE_NODE>::iterator iter=children.begin();iter!=children.end();){
		if(!iter->makeDescendent(color,maxheight,height-1)){
			if(isMyTurn(color,depth)){
				iter=children.erase(iter);
				continue;
			}
			return false;
		}
		iter++;
	}
	
	if(children.empty()){
		makeMyArray();
		if(myfield.getValue()==1) return true;
		return false;
	}
	return true;
}

MOVE TRAX_TREE_NODE::getMove() const{
	return mymove;
}

list<TRAX_TREE_NODE>::const_iterator TRAX_TREE_NODE::getFirstChild() const{
	return children.begin();
}

list<TRAX_TREE_NODE>::const_iterator TRAX_TREE_NODE::getFinalChild() const{
	return children.end();
}

bool TRAX_TREE_NODE::operator==(const TRAX_TREE_NODE& obj) const{
	return parent==obj.parent && mymove==obj.mymove;
}

inline void TRAX_TREE_NODE::makeMyArray() const{
	if(parent!=NULL) parent->makeMyArray();
	else myfield.initField();
	myfield.placeMove(mymove);
}

inline bool TRAX_TREE_NODE::isMyTurn(TILE color,int depth) const{
	return (color==RED && depth%2==1)||(color==WHITE && depth%2==0);
}