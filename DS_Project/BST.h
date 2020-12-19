#ifndef BST_hpp
#define BST_hpp

#include <stdio.h>
#include <iostream>

template <typename DataType>
class BST
{
public:
	BST();
	bool empty() const;
	void insert(const DataType & item);
	bool search(const DataType & item) const;
	void Display(ostream & out) const;
	void RemoveNode(const DataType & key);
	void erase(const DataType & item);
	void delete_erased();
	int  FindSmallest();



private:
	class Node
	{
	public:
		bool erased;
		DataType data;
		Node * left;
		Node * right;

		Node()
			: left(0), right(0), erased(false)
		{}

		Node(DataType item)
			: data(item), left(0), right(0), erased(false)
		{}

	};

	typedef Node* NodePointer;
	NodePointer root;

	bool search_extra(const DataType & item, NodePointer & ptr, NodePointer & parent, bool & leftchild) const;
	void DisplayPreOrder(NodePointer & ptr) const;
	void DisplayInOrder(NodePointer & ptr) const;
	void DisplayPostOrder(NodePointer & ptr) const;
	void delete_erased(NodePointer & ptr);
	void RemoveNodePrivate(const DataType & key, NodePointer & parent);
	void RemoveRootMatch();
	void RemoveMatch(NodePointer & parent, NodePointer & match, bool left);
	int  FindSmallestPrivate(NodePointer & ptr);
};
template <typename DataType>
ostream & operator<< (ostream & out, const BST<DataType> & bst);
#endif

template <typename DataType>
inline BST<DataType>::BST()
	: root(0)
{}

template <typename DataType>
inline bool BST<DataType>::empty() const
{
	return root == 0;
}

template <typename datatype>
inline void  BST<datatype>::insert(const datatype & item)
{
	NodePointer ptr = root, parent;
	bool leftchild = false;

	if (this->empty())
		// Tree has no items
	{
		root = new BST<datatype>::Node(item);
	}
	else
		// Tree contains items
	{

		bool found = search_extra(item, ptr, parent, leftchild);
		if (!found)
			//Item doesn't exist
		{
			ptr = new BST<datatype>::Node(item);
			if (leftchild)
			{
				parent->left = ptr;
			}
			else
			{
				parent->right = ptr;

			}
		}
		else
			//Item exists
			cout << "Item already exists; Tree can't have duplicates\n";
	}


}

template <typename DataType>
bool  BST<DataType>::search(const DataType & item) const
{
	NodePointer ptr = root;
	while (1)
	{
		if (ptr == 0)
		{
			return false;
		}
		else if (item < ptr->data)
		{
			ptr = ptr->left;
		}
		else if (item > ptr->data)
		{
			ptr = ptr->right;
		}
		else
			return true;
	}
}

template <typename DataType>  //used by insert and erase
bool  BST<DataType>::search_extra(const DataType & item, NodePointer  & ptr, NodePointer  & parent, bool & leftchild) const
{
	while (1)
	{
		if (ptr == 0)
		{
			return false;
		}
		else if (item < ptr->data)
		{
			parent = ptr;
			ptr = ptr->left;
			leftchild = true;
		}
		else if (item > ptr->data)
		{
			parent = ptr;
			ptr = ptr->right;
			leftchild = false;

		}
		else
			return true;
	}
}

template <typename DataType>
void BST<DataType>::Display(ostream & out) const
{
	NodePointer ptr = root;

	cout << endl;
	cout << "Preorder Traversal of BST:" << endl;
	DisplayPreOrder(ptr);

	cout << endl;
	cout << "Inorder Traversal of BST:" << endl;
	DisplayInOrder(ptr);

	cout << endl;
	cout << "Postorder Traversal of BST:" << endl;
	DisplayPostOrder(ptr);
}

template <typename DataType>
ostream & operator<< (ostream & out, const BST<DataType> & bst) {
	bst.Display(out);
	return out;
}

template <typename DataType>
void BST<DataType>::DisplayPreOrder(NodePointer & ptr) const
{
	if (ptr == 0)
		return;
	else
	{
		cout << ptr->data << " ";
		DisplayPreOrder(ptr->left);
		DisplayPreOrder(ptr->right);
	}
}

template <typename DataType>
void BST<DataType>::DisplayInOrder(NodePointer & ptr) const
{
	if (ptr == 0)
		return;
	else
	{
		DisplayInOrder(ptr->left);
		cout << ptr->data << " ";
		DisplayInOrder(ptr->right);
	}
}

template <typename DataType>
void BST<DataType>::DisplayPostOrder(NodePointer & ptr) const
{
	if (ptr == 0)
		return;
	else
	{
		DisplayPostOrder(ptr->left);
		DisplayPostOrder(ptr->right);
		cout << ptr->data << " ";
	}
}

template <typename DataType>
void  BST<DataType>::erase(const DataType & item)
{
	NodePointer ptr = root, parent;
	bool leftchild = false;
	bool found = search_extra(item, ptr, parent, leftchild);
	if (!found)
	{
		cout << "\nItem doesn't exist" << endl;
	}
	else
	{
		ptr->erased = true;
	}

}


template <typename DataType>
void  BST<DataType>::delete_erased()
{
	NodePointer ptr = root;
	delete_erased(ptr);
}

template <typename DataType>
void  BST<DataType>::delete_erased(NodePointer & ptr)
{
	if (ptr == 0)
	{
		return;
	}
	else if (ptr->erased == true)
	{
		RemoveNode(ptr -> data);
	}
	delete_erased(ptr->left);
	delete_erased(ptr->right);
}

template <typename DataType>
void BST<DataType>::RemoveNode(const DataType & key) {
	RemoveNodePrivate(key, root);
}

template <typename DataType>
void BST<DataType>::RemoveNodePrivate(const DataType & key, NodePointer & parent) {
	if (root != NULL) {
		if (root->data == key) {
			RemoveRootMatch();
		}
		else {
			if (key < parent->data && parent->left != NULL) {
				parent->left->data == key ? RemoveMatch(parent, parent->left, true) : RemoveNodePrivate(key, parent->left);
			}
			else if (key > parent->data && parent->right != NULL) {
				parent->right->data == key ? RemoveMatch(parent, parent->right, false) : RemoveNodePrivate(key, parent->right);
			}
			else {
				cout << "The key is not in the tree" << endl;
			}
		}
	}
	else {
		cout << "The tree is empty" << endl;
	}
}

template <typename DataType>
void BST<DataType>::RemoveRootMatch() {
	if (root != NULL) {
		NodePointer delPtr = root;
		DataType rootKey = root->data;
		DataType smallestInRightSubTree;

		// Case 0 - 0 childs
		if (root->left == NULL && root->right == NULL) {
			root = NULL;
			delete delPtr;
		}
		// Case 1 - 1 child
		else if (root->left == NULL && root->right != NULL) {
			root = root->right;
			delPtr->right = NULL;
			delete delPtr;
		}
		else if (root->left != NULL && root->right == NULL) {
			root = root->left;
			delPtr->left = NULL;
			delete delPtr;
		}
		// Case 2 - 2 childs
		else {
			smallestInRightSubTree = FindSmallestPrivate(root->right);
			RemoveNodePrivate(smallestInRightSubTree, root);
			root->data = smallestInRightSubTree;
		}
	}
	else {
		cout << "Tree is empty" << endl;
	}
}

template <typename DataType>
void BST<DataType>::RemoveMatch(NodePointer & parent, NodePointer & match, bool left) {
	if (root != NULL) {
		NodePointer delPtr;
		DataType matchKey = match->data;
		DataType smallestInRightSubTree;

		//Case 0
		if (match->left == NULL && match->right != NULL) {
			delPtr = match;
			left == true ? parent->left = NULL : parent->right = NULL;
			delete delPtr;
		}
		//Case 1
		else if (match->left == NULL && match->right != NULL) {
			left == true ? parent->left = match->right : parent->right = match->right;
			match->right = NULL;
			delPtr = match;
			delete delPtr;
		}
		else if (match->left != NULL && match->right == NULL) {
			left == true ? parent->left = match->left : parent->right = match->left;
			match->left = NULL;
			delPtr = match;
			delete delPtr;
		}
		//Case 2
		else {
			smallestInRightSubTree = FindSmallestPrivate(match->right);
			RemoveNodePrivate(smallestInRightSubTree, match);
			match->data = smallestInRightSubTree;
		}
	}
	else {
		cout << "Tree is empty" << endl;
	}
}

template <typename DataType>
int BST<DataType>::FindSmallest() {
	return FindSmallestPrivate(root);
}

template <typename DataType>
int BST<DataType>::FindSmallestPrivate(NodePointer & ptr) {
	if (root == NULL) {
		cout << "Tree is empty" << endl;
		return -1;
	}
	else {
		if (ptr->left != NULL) {
			return FindSmallestPrivate(ptr->left);
		}
		else {
			return ptr->data;
		}
	}
}