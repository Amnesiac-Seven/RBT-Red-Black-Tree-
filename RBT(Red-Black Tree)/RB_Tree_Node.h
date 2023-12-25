#ifndef RB_TREE_NODE_H
#define RB_TREE_NODE_H
#pragma once
//#include "stdafx.h"
template <class T>
class RB_Tree_Node {
public:
	RB_Tree_Node(T data_in);// 构造函数
	~RB_Tree_Node();		// 析构函数
	RB_Tree_Node* Left_child;
	RB_Tree_Node* Right_child;
	RB_Tree_Node* Father_Node;
	T data;			// 该节点存储的数据
	int color_tag;	// 颜色:红或黑
};

#endif