#pragma once
#include <iostream>

enum colour
{
	RED,
	BLACk
};

template<class k ,class v>
struct BRTreeNode
{
	BRTreeNode* _parent;
	BRTreeNode* _left;
	BRTreeNode* _right;
	std::pair<k, v> _kv;
	colour _colo;
	BRTreeNode(std::pair<k, v> kv)
		:_parent(nullptr),
		_left(nullptr),
		_right(nullptr),
		_colo(RED)
	{
		_kv.first = kv.first;
		_kv.second = kv.second;
	}
};

template<class k,class v>
class BRTree
{
public:
	typedef BRTreeNode<k,v> Node;
	BRTree()
		:_root(nullptr)
	{
		;
	}

	void Sawp(Node*& i,Node*& j)
	{
		Node* tmp=i;
		i = j;
		j = tmp;
	}

	void RotateR(Node* pos)
	{
		Node* L = pos->_left;
		Node* LR = L->_right;
		L->_parent = pos->_parent;
		if(pos->_parent!=nullptr)
		{
			L->_parent->_right = L;
		}
		pos->_parent = L;
		L->_right = pos;
		pos->_left = LR;
		if(LR!=nullptr)
		{
			LR->_parent = pos;
		}
	}

	void RotateL(Node* pos)
	{
		Node* R = pos->_right;
		Node* RL = R->_left;
		R->_parent = pos->_parent;
		if(pos->_parent!=nullptr)
		{
			R->_parent->_left = R;
		}
		pos->_parent = R;
		R->_left = pos;
		pos->_right = RL;
		if(RL!=nullptr)
		{
			RL->_parent = pos;
		}
	}

	bool insert(const std::pair<k,v>& kv)
	{
		if(_root==nullptr)
		{
			_root = new Node(kv) ;
			_root->_colo = BLACk;
			return true;
		}
		Node* cur = _root;
		Node* parent = nullptr;
		while(cur)
		{
			if(kv.first<cur->_kv.first)
			{
				parent = cur;
				cur = cur->_left;
				
			}
			else if (kv.first > cur->_kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(kv);
		if (kv.first>parent->_kv.first)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		cur->_colo = RED;
		
		while (parent!=nullptr && parent->_colo==RED)
		{
			Node* grand = parent->_parent;
			Node* uncle;

			if (grand->_left == parent&&grand->_right!=nullptr)
			{
				uncle = grand->_right;
			}
			else if (grand->_right == parent&&grand->_right!=nullptr)
			{
				uncle = grand->_left;
			}
			else
			{
				uncle = nullptr;
			}

			if(grand!=nullptr&&uncle!=nullptr && parent->_colo==RED && uncle->_colo==RED)
			{
				parent->_colo = BLACk;
				uncle->_colo = BLACk;
				grand->_colo = RED;
				cur = grand;
				parent = cur->_parent;
			}

			else if(grand!=nullptr)
			{
				if(grand->_left==parent)
				{
					if(cur==parent->_right)
					{
						RotateL(parent);
						Sawp(parent, cur);

					}
					RotateR(grand);
					grand->_colo = RED;
					parent->_colo = BLACk;
					if(parent->_parent==nullptr)
					{
						_root = parent;
					}
					break;
				}
				else if(grand->_right==parent)
				{
					if(cur==parent->_left)
					{
						RotateR(parent);
						Sawp(parent, cur);
					}
					RotateL(grand);
					grand->_colo = RED;
					parent->_colo = BLACk;
					if (parent->_parent == nullptr)
					{
						_root = parent;
					}
					break;
				}
			}
		}
		_root->_colo = BLACk;
		return true;
	}
	void Inorder()
	{
		if(_root!=nullptr)
		{
			Inorder(_root);
			std::cout << std::endl;
		}
		else
		{
			std::cout << "没有要打印的元素"<< std::endl;
		}
	}

	void Inorder(Node*& _root)
	{
		if(_root!=nullptr)
		{
			Inorder(_root->_left);
			std::cout << _root->_kv.first << ":" << _root->_kv.second;
			if (_root->_colo == RED)
			{
				std::cout << "red" << "  ";
			}
			else if (_root->_colo == BLACk)
			{
				std::cout << "black" << "  ";
			}
			else
			{
				std::cout << "nop" << "  ";
			}
			Inorder(_root->_right);
		}
	}

private:
	Node* _root;
};