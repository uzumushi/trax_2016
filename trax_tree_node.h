#ifndef TRAX_TREE_NODE_INCLUDE
#define TRAX_TREE_NODE_INCLUDE

#include <list>
using namespace std;

#include "move.h"
#include "typedef.h"

extern const bool ALPHA_FLAG;
extern const bool BETA_FLAG;

class TRAX_ARRAY_KAI;

class TRAX_TREE_NODE{
public:
	TRAX_TREE_NODE();
	TRAX_TREE_NODE(const MOVE&);
	TRAX_TREE_NODE(TRAX_TREE_NODE*,MOVE);
	bool makeChildren(bool);
	void makeDescendent(TILE,int);
	MOVE getMove() const;
	list<TRAX_TREE_NODE>::const_iterator getFirstChild() const;
	list<TRAX_TREE_NODE>::const_iterator getFinalChild() const;
	bool operator ==(const TRAX_TREE_NODE&) const;
protected:
	bool makeDescendent(TILE,int,int);
	void makeMyArray() const;
	bool isMyTurn(TILE,int) const;
	TRAX_TREE_NODE* parent;
	MOVE mymove;
	list<TRAX_TREE_NODE> children;
};

#endif