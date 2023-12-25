#pragma once
#ifndef RB_TREE_H
#define RB_TREE_H
#include"RB_Tree_Node.h"
#include"RB_Tree_Node.cpp"
template<class T>
class RB_Tree {
public:
	RB_Tree(T Root_Data);
	~RB_Tree();
	void Left_Rotate(RB_Tree_Node<T>* current_Node);// 以当前节点为中心左旋转
	void Right_Rotate(RB_Tree_Node<T>* current_Node);// 以当前节点为中心右旋转
	void Insert_Node(T insert_node);// 插入数据
	int Delete_Node(T delete_node);// 删除数据
	void Fix_Tree(RB_Tree_Node<T>* current_Node);// 修整红黑树
	void Erase_Tree(RB_Tree_Node<T>* Node_del);// 删除节点
	void Fix_Tree_Delete(RB_Tree_Node<T>* current_Node); // 
	RB_Tree_Node<T>* Find_Successor_Node(RB_Tree_Node<T>* current_Node);// 寻找当前节点的继承，通常是左子树的最后一个或右子树的第一个
	RB_Tree_Node<T>* Root_Node;// 根节点
};

#endif