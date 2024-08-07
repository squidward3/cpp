#include "BRTree.hpp"

int main()
{
	BRTree<int,int > awa;
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	for (auto e:a)
	{
		awa.insert(std::make_pair(e,e));
	}

	awa.Inorder();
	return 0;
}