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
	void Left_Rotate(RB_Tree_Node<T>* current_Node);// �Ե�ǰ�ڵ�Ϊ��������ת
	void Right_Rotate(RB_Tree_Node<T>* current_Node);// �Ե�ǰ�ڵ�Ϊ��������ת
	void Insert_Node(T insert_node);// ��������
	int Delete_Node(T delete_node);// ɾ������
	void Fix_Tree(RB_Tree_Node<T>* current_Node);// ���������
	void Erase_Tree(RB_Tree_Node<T>* Node_del);// ɾ���ڵ�
	void Fix_Tree_Delete(RB_Tree_Node<T>* current_Node); // 
	RB_Tree_Node<T>* Find_Successor_Node(RB_Tree_Node<T>* current_Node);// Ѱ�ҵ�ǰ�ڵ�ļ̳У�ͨ���������������һ�����������ĵ�һ��
	RB_Tree_Node<T>* Root_Node;// ���ڵ�
};

#endif