
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
	cout << intBST << endl;

	cout << "\n\nNow testing the search() operation."
		"\nTry both items in the BST and some not in it:\n";
	for (;;)
	{
		cout << "Item to find (-999 to stop): ";
		cin >> number;
		if (number == -999) break;
		cout << (intBST.search(number) ? "Found" : "Not found") << endl;
	}
	cout << intBST << endl;

	cout << "\nNow testing the remove() operation." "\nTry both items in the BST and some not in it:\n";
	for (;;)
	{
	cout << "Item to remove (-999 to stop): ";
	cin >> number;
	if (number == -999) break;
	intBST.remove(number);
	}
	cout << intBST << endl;


	cout <<"\n\nNow testing the erase() operation." "\nNow insert a bunch of integers into the BST." "\nTry items not in the BST and some that are in it:\n";
	for (;;)
	{
		cout << "Item to mark as erased (-999 to stop): ";
		cin >> number;
		if (number == -999) break;
		intBST.erase(number);
	}
	cout << intBST << endl;

	cout << "\n\nNow testing the delete_erased() operation." << endl;
	intBST.delete_erased();
	cout << intBST << endl;


	return 0;
}
