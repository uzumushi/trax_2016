#include <iostream>
using namespace std;
#include "trax_tree_node.h"

int main(){
	MOVE mo("@0+");
	TRAX_TREE_NODE test(mo);
	test.makeChildren(ALPHA_FLAG);
	for(list<TRAX_TREE_NODE>::const_iterator itr=test.getFirstChild();itr!=test.getFinalChild();itr++){
		cout<<(*itr).getMove()<<endl;
	}
}