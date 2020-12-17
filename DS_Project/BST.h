#include <iostream>
#pragma once

template <typename DataType>
class BST
{
public:
	BST();
	bool empty() const;
	void insert(const DataType & item);
	bool search(const DataType & item) const;
	//void remove(const DataType & item);
	//void inorder(ostream & out) const;
	//void graph(ostream & out) const;*/

private:
	class Node
	{
	public:
		DataType data;
		Node * left;
		Node * right;

		Node()
			: left(0), right(0)
		{}

		Node(DataType item)
			: data(item), left(0), right(0)
		{}

	};
	typedef Node* NodePointer;
	NodePointer root;

	bool search(const DataType & item, NodePointer & ptr, NodePointer & parent, bool & leftchild) const; //used by insert
	/*void search2(const DataType & item, bool & found, NodePointer & locptr, NodePointer & parent) const;
	void inorderAux(ostream & out, NodePointer subtreePtr) const;
	void graphAux(ostream & out, int indent, NodePointer subtreeRoot) const;*/

};



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

		bool found = search(item, ptr , parent,leftchild);
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
		else if (item < ptr-> data)
		{
			ptr = ptr -> left;
		}
		else if (item > ptr->data)
		{
			ptr = ptr->right;
		}
		else
			return true;
	}
}

template <typename DataType>
bool  BST<DataType>::search(const DataType & item, NodePointer  & ptr, NodePointer  & parent , bool & leftchild) const
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



//template <typename DataType>
//void BST<DataType>::remove(const DataType & item)
//{
//	bool found;                      
//	BST<DataType>::NodePointer
//		x,                           
//		parent;                      
//	search2(item, found, x, parent);
//
//	if (!found)
//	{
//		cout << "Item not in the BST\n";
//		return;
//	}
//	
//	if (x->left != 0 && x->right != 0)
//	{                                
//									
//		BST<DataType>::NodePointer xSucc = x->right;
//		parent = x;
//		while (xSucc->left != 0)      
//		{
//			parent = xSucc;
//			xSucc = xSucc->left;
//		}
//
//		
//		x->data = xSucc->data;
//		x = xSucc;
//	} 
//
//	BST<DataType>::NodePointer
//		subtree = x->left;           
//	if (subtree == 0)
//		subtree = x->right;
//	if (parent == 0)                 
//		root = subtree;
//	else if (parent->left == x)      
//		parent->left = subtree;
//	else                             
//		parent->right = subtree;
//	delete x;
//}
//
//template <typename DataType>
//inline void BST<DataType>::inorder(ostream & out) const
//{
//	inorderAux(out, root);
//}
//
//template <typename DataType>
//inline void BST<DataType>::graph(ostream & out) const
//{
//	graphAux(out, 0, root);
//}
//
//template <typename DataType>
//void BST<DataType>::search2(const DataType & item, bool & found, NodePointer & locptr, NodePointer & parent) const
//{
//	locptr = root;
//	parent = 0;
//	found = false;
//	while (!found && locptr != 0)
//	{
//		if (item < locptr->data)       
//		{
//			parent = locptr;
//			locptr = locptr->left;
//		}
//		else if (locptr->data < item)  
//		{
//			parent = locptr;
//			locptr = locptr->right;
//		}
//		else                           
//			found = true;
//	}
//}
//
//template <typename DataType>
//void BST<DataType>::inorderAux(ostream & out, NodePointer subtreeRoot) const
//{
//	if (subtreeRoot != 0)
//	{
//		inorderAux(out, subtreeRoot->left);    // L operation
//		out << subtreeRoot->data << "  ";      // V operation
//		inorderAux(out, subtreeRoot->right);   // R operation
//	}
//}
//
//#include <iomanip>
//
//template <typename DataType>
//void BST<DataType>::graphAux(ostream & out, int indent,
//	NodePointer subtreeRoot) const
//{
//	if (subtreeRoot != 0)
//	{
//		graphAux(out, indent + 8, subtreeRoot->right);
//		out << setw(indent) << " " << subtreeRoot->data << endl;
//		graphAux(out, indent + 8, subtreeRoot->left);
//	}
//}
//
//
//
