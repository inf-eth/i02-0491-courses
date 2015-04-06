#include "Tree.h"
#include <iostream>
using namespace std;

int main()
{
	Tree TestTree;
	char* Prefix="(*(-(a)(*(d)(e)))(+(b)(c)))";
	TestTree.MakeTree(Prefix);

	TestTree.Preorder();
	cout << endl;

	TestTree.Inorder();
	cout << endl;

	TestTree.Postorder();
	cout << endl;

	return 0;
}
