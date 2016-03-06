#include "trax_tree_node.h"
#include "trax_array_kai.h"
#include "tiledef.h"

#include <iostream>
using namespace std;

const bool ALPHA_FLAG=false;
const bool BETA_FLAG=true;

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
	TRAX_ARRAY_KAI* field=makeMyArray();
	MOVE mo;
	
	for(mo=field->getMove();mo.tile!=NULLNODE;mo=field->getMove()){
		TRAX_ARRAY_KAI fieldbuf;
		fieldbuf.copyArrayKai(*field);
		fieldbuf.placeMove(mo);
		switch(fieldbuf.getValue()){
		case -1:
			if(modeflag==BETA_FLAG){
				delete field;
				return false;
			}
			break;
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
		cout<<mo<<endl;
	}
	delete field;
	return true;
}

bool TRAX_TREE_NODE::makeDescendent(TILE color,int height,int maxheight){
	int depth=maxheight-height;
	if(isMyTurn(color,depth)){
		makeChildren(ALPHA_FLAG);
	}
	else{
		if(!makeChildren(BETA_FLAG)){
			parent->children.remove(*this);
			return true;
		}
	}
	if(height!=2){
		for(list<TRAX_TREE_NODE>::iterator iter=children.begin();iter!=children.end();iter++){
			if(!iter->makeDescendent(color,height-1,maxheight)) return true;
		}
	}
	if(children.empty()){
		if(isMyTurn(color,depth)){
			parent->parent->children.remove(*parent);
			return false;
		}
		else{
			parent->children.remove(*this);
			return true;
		}
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

inline TRAX_ARRAY_KAI* TRAX_TREE_NODE::makeMyArray(TRAX_ARRAY_KAI* array){
	if(array==NULL) array=new TRAX_ARRAY_KAI;
	if(parent!=NULL) makeMyArray(array);
	array->placeMove(mymove);
	return array;
}

inline bool TRAX_TREE_NODE::isMyTurn(TILE color,int depth){
	return (color==RED && depth%2==1)||(color==WHITE && depth%2==0);
}