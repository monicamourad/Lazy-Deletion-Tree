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

	//void remove(const DataType & item);
	void erase(const DataType & item);
	void delete_erased();


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
		//remove(ptr -> data);
	}
	delete_erased(ptr->left);
	delete_erased(ptr->right);
}

//template <typename datatype>
//void BST<datatype>::remove(const datatype & item)
//{
//	bool found;                      
//	BST<datatype>::Node x, parent;                      
//	search2(item, found, x, parent);
//
//	if (!found)
//	{
//		cout << "item not in the bst\n";
//		return;
//	}
//	
//	if (x->left != 0 && x->right != 0)
//	{                                
//									
//		bst<datatype>::nodepointer xsucc = x->right;
//		parent = x;
//		while (xsucc->left != 0)      
//		{
//			parent = xsucc;
//			xsucc = xsucc->left;
//		}
//
//		
//		x->data = xsucc->data;
//		x = xsucc;
//	} 
//
//	bst<datatype>::nodepointer
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
