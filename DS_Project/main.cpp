
#include <iostream>
using namespace std;

#include "BST.h"

int main(int argc, const char * argv[]) {

	BST<int> intBST;            
	cout << "Constructing empty BST\n";
	cout << "BST " << (intBST.empty() ? "is" : "is not") << " empty\n";

	cout << "\nNow insert a bunch of integers into the BST." "\nTry items not in the BST and some that are in it:\n";
	int number;
	for (;;)
	{
		cout << "Item to insert (-999 to stop): ";
		cin >> number;
		if (number == -999) break;
		intBST.insert(number);
	}

	cout << "\n\nNow testing the search() operation."
		"\nTry both items in the BST and some not in it:\n";
	for (;;)
	{
		cout << "Item to find (-999 to stop): ";
		cin >> number;
		if (number == -999) break;
		cout << (intBST.search(number) ? "Found" : "Not found") << endl;
	}

	intBST.Display();

	/*cout << "Inorder Traversal of BST: \n";
	intBST.inorder(cout);

	cout << "\nNow insert a bunch of integers into the BST."
		"\nTry items not in the BST and some that are in it:\n";
	int number;
	for (;;)
	{
		cout << "Item to insert (-999 to stop): ";
		cin >> number;
		if (number == -999) break;
		intBST.insert(number);
	}
	intBST.graph(cout);

	cout << "BST " << (intBST.empty() ? "is" : "is not") << " empty\n";
	cout << "Inorder Traversal of BST: \n";
	intBST.inorder(cout);

	cout << endl;

	
	cout << "\nNow testing the remove() operation."
		"\nTry both items in the BST and some not in it:\n";
	for (;;)
	{
		cout << "Item to remove (-999 to stop): ";
		cin >> number;
		if (number == -999) break;
		intBST.remove(number);
		intBST.graph(cout);
	}
	cout << "\nInorder Traversal of BST: \n";
	intBST.inorder(cout);
	cout << endl;*/

	return 0;
}
