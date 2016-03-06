#ifndef TRAX_TREE_INCLUDE
#define TRAX_TREE_INCLUDE

#include "trax_tree_node.h"
#include "typedef.h"

class TRAX_TREE{
public:
	TRAX_TREE();
	~TRAX_TREE();
	void makeTree(MOVE,TILE,int);
private:
	TRAX_TREE_NODE* root;
};

#endif

