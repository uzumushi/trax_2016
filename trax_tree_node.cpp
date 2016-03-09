#include "trax_tree_node.h"
#include "trax_array_kai.h"
#include "tiledef.h"

#include <vector>
#include <iostream>
using namespace std;

const bool ALPHA_FLAG=false;
const bool BETA_FLAG=true;
static const char MAKE_CHILDREN_LOSE=0;
static const char MAKE_CHILDREN_WIN=1;
static const char MAKE_CHILDREN_NORMAL=2;

static TRAX_ARRAY_KAI myfield;

TRAX_TREE_NODE::TRAX_TREE_NODE(){
	parent=NULL;
	winflag=false;
}

TRAX_TREE_NODE::TRAX_TREE_NODE(const MOVE& mo){
	mymove=mo;
	parent=NULL;
	winflag=false;
}

TRAX_TREE_NODE::TRAX_TREE_NODE(TRAX_TREE_NODE* ptrparent,MOVE mo){
	parent=ptrparent;
	mymove=mo;
	winflag=false;
}

char TRAX_TREE_NODE::makeChildren(bool modeflag){
	makeMyArray();
	MOVE mo;
	
	for(mo=myfield.getMove();mo.tile!=NULLNODE;mo=myfield.getMove()){
		static TRAX_ARRAY_KAI fieldbuf;
		fieldbuf.copyArrayKai(myfield);
		fieldbuf.placeMove(mo);
		switch(fieldbuf.getValue()){
		case -1:
			if(modeflag==BETA_FLAG) return MAKE_CHILDREN_LOSE;
			break;
		case 1:
			if(modeflag==ALPHA_FLAG) return MAKE_CHILDREN_WIN;
			break;
		case 0:
			TRAX_TREE_NODE nodebuf(this,mo);
			children.push_back(nodebuf);
			break;
		}
	}
	return MAKE_CHILDREN_NORMAL;
}

void TRAX_TREE_NODE::makeDescendent(TILE color,int height){
	if(height<2)return;
	makeDescendent(color,height,height-1);
}

inline bool TRAX_TREE_NODE::makeDescendent(TILE color,int maxheight,int height){
	int depth=maxheight-height;
	
	if(isMyTurn(color,depth)){
		if(makeChildren(ALPHA_FLAG)==MAKE_CHILDREN_WIN){
			winflag=true;
			children.clear();
		}
	}
	else if(makeChildren(BETA_FLAG)==MAKE_CHILDREN_LOSE) return false;
	
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
	
	if(children.empty()&&!winflag) return false;
	
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
	vector<MOVE> movelist;
	for(const TRAX_TREE_NODE* nodeptr=this;nodeptr!=NULL;nodeptr=nodeptr->parent){
		movelist.push_back(nodeptr->mymove);
	}
	
	myfield.initField();
	for(vector<MOVE>::reverse_iterator itr=movelist.rbegin();itr!=movelist.rend();itr++){
		myfield.placeMove(*itr);
	}
	//myfield.printField();
	//if(parent!=NULL) parent->makeMyArray();
	//else myfield.initField();
	//myfield.placeMove(mymove);
}

inline bool TRAX_TREE_NODE::isMyTurn(TILE color,int depth) const{
	return (color==RED && depth%2==1)||(color==WHITE && depth%2==0);
}