#include "binary_search_tree.hpp"

int main()
{
	BTree<int> awa;
	int a[] = { 5,3,4,1,7,8,2,6,0,9 };
	for(auto ax:a)
	{
		awa.insert(ax);
	}
	for(auto xs: a)
	{
		awa.erase(xs);
		awa.InOrder();
	}
	awa.erase(1);
	awa.InOrder();

	return 0;
}