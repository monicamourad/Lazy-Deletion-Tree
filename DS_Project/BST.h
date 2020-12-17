#include <iostream>
#pragma once

/* BST.h contains the declaration of class template BST.
Basic operations:
Constructor: Constructs an empty BST
empty:       Checks if a BST is empty
search:      Search a BST for an item
insert:      Inserts a value into a BST
remove:      Removes a value from a BST
inorder:     Inorder traversal of a BST -- output the data values
graph:       Output a grapical representation of a BST
Private utility helper operations:
search2:     Used by delete
inorderAux:  Used by inorder
graphAux:    Used by graph
Other operations described in the exercises:
destructor
copy constructor
assignment operator
preorder, postorder, and level-by-level traversals
level finder
Note: Execution terminates if memory isn't available for a new BST node.
---------------------------------------------------------------------------*/

template <typename DataType>
class BST
{
public:
	BST();
	bool empty() const;
	bool search(const DataType & item) const;
	void insert(const DataType & item);
	void remove(const DataType & item);
	void inorder(ostream & out) const;
	void graph(ostream & out) const;

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

	typedef Node * NodePointer;

	void search2(const DataType & item, bool & found, NodePointer & locptr, NodePointer & parent) const;
	
	void inorderAux(ostream & out, NodePointer subtreePtr) const;

	void graphAux(ostream & out, int indent, NodePointer subtreeRoot) const;
	
	NodePointer root;

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

template <typename DataType>
bool BST<DataType>::search(const DataType & item) const
{
	BST<DataType>::NodePointer locptr = root;
	bool found = false;
	while (!found && locptr != 0)
	{
		if (item < locptr->data)       // descend left
			locptr = locptr->left;
		else if (locptr->data < item)  // descend right
			locptr = locptr->right;
		else                           // item found
			found = true;
	}
	return found;
}

template <typename DataType>
inline void BST<DataType>::insert(const DataType & item)
{
	BST<DataType>::NodePointer
		locptr = root,   
		parent = 0;      
	bool found = false;  
	while (!found && locptr != 0)
	{
		parent = locptr;
		if (item < locptr->data)      
			locptr = locptr->left;
		else if (locptr->data < item) 
			locptr = locptr->right;
		else                          
			found = true;
	}
	if (!found)
	{                                 
		locptr = new BST<DataType>::Node(item);
		if (parent == 0)               
			root = locptr;
		else if (item < parent->data)  
			parent->left = locptr;
		else                           
			parent->right = locptr;
	}
	else
		cout << "Item already in the tree\n";
}

template <typename DataType>
void BST<DataType>::remove(const DataType & item)
{
	bool found;                      
	BST<DataType>::NodePointer
		x,                           
		parent;                      
	search2(item, found, x, parent);

	if (!found)
	{
		cout << "Item not in the BST\n";
		return;
	}
	
	if (x->left != 0 && x->right != 0)
	{                                
									
		BST<DataType>::NodePointer xSucc = x->right;
		parent = x;
		while (xSucc->left != 0)      
		{
			parent = xSucc;
			xSucc = xSucc->left;
		}

		
		x->data = xSucc->data;
		x = xSucc;
	} 

	BST<DataType>::NodePointer
		subtree = x->left;           
	if (subtree == 0)
		subtree = x->right;
	if (parent == 0)                 
		root = subtree;
	else if (parent->left == x)      
		parent->left = subtree;
	else                             
		parent->right = subtree;
	delete x;
}

template <typename DataType>
inline void BST<DataType>::inorder(ostream & out) const
{
	inorderAux(out, root);
}

template <typename DataType>
inline void BST<DataType>::graph(ostream & out) const
{
	graphAux(out, 0, root);
}

template <typename DataType>
void BST<DataType>::search2(const DataType & item, bool & found, NodePointer & locptr, NodePointer & parent) const
{
	locptr = root;
	parent = 0;
	found = false;
	while (!found && locptr != 0)
	{
		if (item < locptr->data)       
		{
			parent = locptr;
			locptr = locptr->left;
		}
		else if (locptr->data < item)  
		{
			parent = locptr;
			locptr = locptr->right;
		}
		else                           
			found = true;
	}
}

template <typename DataType>
void BST<DataType>::inorderAux(ostream & out, NodePointer subtreeRoot) const
{
	if (subtreeRoot != 0)
	{
		inorderAux(out, subtreeRoot->left);    // L operation
		out << subtreeRoot->data << "  ";      // V operation
		inorderAux(out, subtreeRoot->right);   // R operation
	}
}

#include <iomanip>

template <typename DataType>
void BST<DataType>::graphAux(ostream & out, int indent,
	NodePointer subtreeRoot) const
{
	if (subtreeRoot != 0)
	{
		graphAux(out, indent + 8, subtreeRoot->right);
		out << setw(indent) << " " << subtreeRoot->data << endl;
		graphAux(out, indent + 8, subtreeRoot->left);
	}
}



