#pragma once
#include <iostream>

template <class k>
struct BSTreeNode
{
	BSTreeNode(k key)
		:_right(nullptr)
		, _left(nullptr)
		,_key(key)
	{
		;
	}
	BSTreeNode<k>* _right;
	BSTreeNode<k>* _left;
	k _key;
	~BSTreeNode()
	{
		_right = nullptr;
		_left = nullptr;
	}
};

template <class k>
class BTree
{
public:
	typedef BSTreeNode<k> Node;
	BTree()
		:_root(nullptr)
	{
		;
	}
	bool insert(k key)
	{
		Node* parent = _root;
		Node* cur = _root;
		if(cur==nullptr)
		{
			_root = new Node(key);
			return true;
		}
		else
		{
			while (cur)
			{
				parent = cur;
				if (cur->_key > key)
				{
					cur = cur->_left;
					
				}
				else if (cur->_key < key)
				{
					cur = cur->_right;
				}
				else if(cur->_key==key)
				{
					return false;
				}
			}
			cur = new Node(key);
			if(parent->_key>key)
			{
				parent->_left = cur;
				cur->_key = key;
			}
			else if (parent->_key < key)
			{
				parent->_right = cur;
				cur->_key = key;
			}
			return true;
		}
	}
	bool InOrder(Node* _root)
	{
		Node* cur = _root;
		if (cur == nullptr)
		{
			return false;
		}
		
		
		InOrder(cur->_left);
		std::cout << cur->_key << ' ';
		InOrder(cur->_right);
		return true;
	}
	bool InOrder()
	{
		if(_root==nullptr)
		{
			std::cout << "没有元素打印"<<std::endl;
		}
		InOrder(_root);
		std::cout << std::endl;
		return true;
	}
	bool erase(k key)
	{
		Node* parent = _root;
		Node* cur = _root;
		int Isleft = -1;
		if (cur==nullptr)
		{
			std::cout << "没有要删除的元素"<<std::endl;
			return false;
		}
		while (cur)
		{
			
			if(key>cur->_key)
			{
				parent = cur;
				cur = cur->_right;
				Isleft = 0;
			}
			else if(key<cur->_key)
			{
				parent = cur;
				cur = cur->_left;
				Isleft = 1;
			}
			else if(key==cur->_key)
			{
				break;
			}
			else
			{
				std::cout << "找不到要删除的元素"<<std :: endl;
				return false;
			}
		}
		if(cur->_right==nullptr&&cur->_left==nullptr)
		{
			if(cur==_root)
			{
				_root = nullptr;
			}
			delete cur;
			if(Isleft==1)
			{
				parent->_left = nullptr;
			}
			else
			{
				parent->_right = nullptr;
			}
			return true;
		}
		else if(cur->_right!=nullptr&&cur->_left==nullptr)
		{
			if(cur==_root)
			{
				_root=cur->_right;
				delete cur;
				return true;
			}
			if (cur==parent->_left)
			{
				parent->_left = cur->_right;
			}
			else
			{
				parent->_right = cur->_right;
			}

			delete cur;
			return true;
		}
		else if (cur->_right==nullptr&&cur->_left!=nullptr)
		{
			if (cur == _root)
			{
				_root = cur->_left;
				delete cur;
				return true;
			}
			if (cur == parent->_left)
			{
				parent->_left = cur->_left;
			}
			else
			{
				parent->_right = cur->_left;
			}
			delete cur;
			return true;
		}
		else if (cur->_left!=nullptr&&cur->_right!=nullptr)
		{
			Node* RightMinparent = cur;
			Node* RightMin = cur->_right;
			while(RightMin->_left)
			{
				RightMinparent = RightMin;
				RightMin = RightMin->_left;
			}
			cur->_key = RightMin->_key;
			if(cur->_right==RightMin)
			{
				
				RightMinparent->_right = RightMin->_right;
				
			}
			else
			{
				RightMinparent->_left = RightMin->_right;
			}
			delete RightMin;
			return true;

			/*while(1) //依托构思
			{
				Node* tmp = parent;
				parent = cur;
				cur = cur->_left;
				while (cur->_right)
				{
					parent = cur;
					cur = cur->_right;
				}
				if (Isleft == 1)
				{
					tmp->_left->_key = cur->_key;
				}
				else if (Isleft == 0)
				{
					tmp->_right->_key = cur->_key;
				}
				else if(Isleft==-1)
				{
					tmp->_key = cur->_key;
				}
				if (cur->_left == nullptr && cur->_right == nullptr)
				{
					delete cur;
					parent->_right = nullptr;
					return true;
				}
				else
				{
					Isleft = 1;
					parent = cur; 
					cur = cur->_left;
					parent->_key = cur->_key;
				}
			}*/
			
		}
	}
private:
	Node* _root;
};
