#include <iostream>
#include <sys/time.h>
using namespace std;
#include "trax_tree_node.h"
#include "tiledef.h"

double get_dtime(void){
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return ((double)(tv.tv_sec) + (double)(tv.tv_usec) * 0.001 * 0.001);
}

int main(){
	MOVE mo("@0+");
	TRAX_TREE_NODE test(mo);
	double starttime=get_dtime();
	test.makeDescendent(WHITE,4);
	double endtime=get_dtime();
	/*for(list<TRAX_TREE_NODE>::const_iterator itr=test.getFirstChild();itr!=test.getFinalChild();itr++){
		cout<<(*itr).getMove()<<endl;
	}*/
	for(list<TRAX_TREE_NODE>::const_iterator itr=(*test.getFirstChild()).getFirstChild();itr!=(*test.getFirstChild()).getFinalChild();itr++){
		cout<<(*itr).getMove()<<endl;
	}
	cout<<"elapsed time "<<endtime-starttime<<"s"<<endl;
}