#include "trax_tree.h"

TRAX_TREE::TRAX_TREE(){
	root=NULL;
}

TRAX_TREE::~TRAX_TREE(){
	delete root;
}

void TRAX_TREE::makeTree(MOVE mo,TILE color,int height){
	root=new TRAX_TREE_NODE(NULL,mo);
	
	
}