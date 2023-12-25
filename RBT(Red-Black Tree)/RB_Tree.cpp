#include"RB_Tree.h"
template<class T>
// 根节点数据大于所有左节点数据，小于所有右节点数据
RB_Tree<T>::RB_Tree(T Root_Data) :Root_Node(nullptr) {
	if (Root_Node == nullptr) {
		Root_Node = new RB_Tree_Node<T>(Root_Data);
		Root_Node->color_tag = 0;// 根节点为黑色
	}
}

template<class T>
RB_Tree<T>::~RB_Tree() {

}

// 插入节点
template<class T>
void RB_Tree<T>::Insert_Node(T insert_data) {
	RB_Tree_Node<T>* node = new RB_Tree_Node<T>(insert_data);
	if (Root_Node == nullptr) {
		Root_Node = node;
		node->color_tag = 0;
		return;
	}

	RB_Tree_Node<T>* current = Root_Node;
	RB_Tree_Node<T>* parent = nullptr;
	while (current != nullptr) {
		parent = current;
		if (current->data > insert_data)
			current = current->Left_child;
		else 
			current = current->Right_child;
	}

	node->Father_Node = parent;
	if (insert_data < parent->data)
		parent->Left_child = node;
	else
		parent->Right_child = node;
	Fix_Tree(node);

	//RB_Tree_Node<T>* temp_Node = Root_Node;
	//while (temp_Node != nullptr) {
	//	if (insert_data > temp_Node->data) {// 进入右子树
	//		if (temp_Node->Right_child == nullptr) {// 没有右孩子
	//			temp_Node->Right_child = new RB_Tree_Node<T>(insert_data);
	//			temp_Node->Right_child->color_tag = 1;
	//			temp_Node->Right_child->Father_Node = temp_Node;
	//			if (temp_Node->color_tag == 1) {// 相邻节点均为红色
	//				Fix_Tree(temp_Node->Right_child);
	//			}
	//			break;
	//		}
	//		else {
	//			temp_Node = temp_Node->Right_child;
	//		}
	//	}
	//	else {// 进入左子树
	//		if (temp_Node->Left_child == nullptr) {
	//			temp_Node->Left_child = new RB_Tree_Node<T>(insert_data);
	//			temp_Node->Left_child->color_tag = 1;
	//			temp_Node->Left_child->Father_Node = temp_Node;
	//			if (temp_Node->color_tag == 1) {
	//				Fix_Tree(temp_Node->Left_child);
	//			}
	//			break;
	//		}
	//		else {
	//			temp_Node = temp_Node->Left_child;
	//		}
	//	}
	//}
}

// 删除节点，成功返回1，否则返回-1
template<class T>
int RB_Tree<T>::Delete_Node(T delete_node) {
	RB_Tree_Node<T>* temp_Node = Root_Node;
	while (temp_Node != nullptr && temp_Node->data != delete_node) {// 寻找该值所在节点
		if (temp_Node->data > delete_node) {
			temp_Node = temp_Node->Left_child;
		}
		else temp_Node = temp_Node->Right_child;
	}
	if (temp_Node) {
		int color_tag = temp_Node->color_tag;
		if (temp_Node->Left_child == nullptr && temp_Node->Right_child == nullptr)
			delete temp_Node;
		else 
		// 仅存在右子树
		if (temp_Node->Left_child == nullptr && temp_Node->Right_child != nullptr) {
			if (temp_Node != Root_Node) {// 不是根节点
				if (temp_Node->Father_Node->Left_child == temp_Node) {
					temp_Node->Father_Node->Left_child = temp_Node->Right_child;
					temp_Node->Right_child->Father_Node = temp_Node->Father_Node;
				}
				else {
					temp_Node->Father_Node->Right_child = temp_Node->Right_child;
					temp_Node->Right_child->Father_Node = temp_Node->Father_Node;
				}
			}
			else {
				Root_Node = temp_Node->Right_child;
				temp_Node->Right_child->Father_Node = Root_Node;
			}
		}
		// 仅存在左子树
		else if (temp_Node->Left_child != nullptr && temp_Node->Right_child == nullptr) {
			if (temp_Node != Root_Node) {
				if (temp_Node->Father_Node->Left_child == temp_Node) {
					temp_Node->Father_Node->Left_child = temp_Node->Left_child;
					temp_Node->Left_child->Father_Node = temp_Node->Father_Node;
				}
				else {
					temp_Node->Father_Node->Right_child = temp_Node->Left_child;
					temp_Node->Left_child->Father_Node = temp_Node->Father_Node;
				}
			}
			else {
				Root_Node = temp_Node->Left_child;
				temp_Node->Left_child->Father_Node = Root_Node;
			}
		}
		else if (temp_Node->Left_child != nullptr && temp_Node->Right_child != nullptr) {
			RB_Tree_Node<T>* Successor_Node = Find_Successor_Node(temp_Node);
			if (temp_Node == temp_Node->Father_Node->Left_child) {
				temp_Node->Father_Node->Left_child = Successor_Node;
				Successor_Node->Right_child = temp_Node->Right_child;
				Successor_Node->Left_child = temp_Node->Left_child;
				Successor_Node->Father_Node = temp_Node->Father_Node;
				Successor_Node->color_tag = temp_Node->color_tag;
				if (Successor_Node->Right_child) {// 由于上面Successor_Node的关系已被修改，该处可能出错
					Successor_Node->Father_Node->Left_child = Successor_Node->Right_child;
					Successor_Node->Right_child->Father_Node = Successor_Node->Father_Node;
				}
			}
			else {
				temp_Node->Father_Node->Right_child = Successor_Node;
				Successor_Node->Right_child = temp_Node->Right_child;
				Successor_Node->Left_child = temp_Node->Left_child;
				Successor_Node->Father_Node = temp_Node->Father_Node;
				Successor_Node->color_tag = temp_Node->color_tag;
				if (Successor_Node->Right_child) {
					Successor_Node->Father_Node->Left_child = Successor_Node->Right_child;
					Successor_Node->Right_child->Father_Node = Successor_Node->Father_Node;
				}
			}
		}
		if (color_tag == 0) {// 删除黑节点，则调整红黑树
			Fix_Tree(temp_Node);
		}
	}
	else return -1;
	return 1;
}

// 修整红黑树
template<class T>
void RB_Tree<T>::Fix_Tree(RB_Tree_Node<T>* current_Node) {
	RB_Tree_Node<T>* temp_current_Node = current_Node;
	RB_Tree_Node<T>* uncle_Node;
	while (1) {
		if (temp_current_Node->Father_Node == nullptr)break;
		if (temp_current_Node->Father_Node->color_tag != 1)break;
		RB_Tree_Node<T>* father_Node = temp_current_Node->Father_Node;
		RB_Tree_Node<T>* grandfa_Node = father_Node->Father_Node;
		if (grandfa_Node) {
			if (father_Node == grandfa_Node->Left_child) {
				uncle_Node = grandfa_Node->Right_child;
				if (uncle_Node) {
					// 叔节点为红，则父叔节点均为黑，祖父节点为红
					if (uncle_Node->color_tag) {
						uncle_Node->color_tag = 0;
						father_Node->color_tag = 0;
						grandfa_Node->color_tag = 1;
						temp_current_Node = grandfa_Node;
					}
					// 叔节点为黑，且当前节点为右孩子，则以父节点进行左旋
					else if (temp_current_Node == father_Node->Right_child) {
						temp_current_Node = temp_current_Node->Father_Node;
						Left_Rotate(temp_current_Node);
					}
					// 叔节点为黑，且当前节点和父节点均为左孩子，则将父节点设为黑色
					else {
						father_Node->color_tag = 0;
						grandfa_Node->color_tag = 1;
						Right_Rotate(grandfa_Node);
					}
				}
				else {// 没有叔节点
					if (temp_current_Node == father_Node->Right_child) {
						temp_current_Node = temp_current_Node->Father_Node;
						Left_Rotate(temp_current_Node);
					}
					else {
						father_Node->color_tag = 0;
						grandfa_Node->color_tag = 1;
						Right_Rotate(grandfa_Node);
					}
				}
			}
			else {
				uncle_Node = grandfa_Node->Left_child;
				if (uncle_Node) {
					// 叔节点为红，父叔节点为黑，祖父节点为红
					if (uncle_Node->color_tag) {
						uncle_Node->color_tag = 0;
						father_Node->color_tag = 0;
						grandfa_Node->color_tag = 1;
						temp_current_Node = grandfa_Node;
					}
					// 叔节点为黑，且为父节点的左孩子
					else if (temp_current_Node == father_Node->Left_child) {
						temp_current_Node = temp_current_Node->Father_Node;
						Right_Rotate(temp_current_Node);
					}
					// 叔节点为黑，且为父节点的右孩子
					else {
						father_Node->color_tag = 0;
						grandfa_Node->color_tag = 1;
						Left_Rotate(grandfa_Node);
					}
				}
				else {
					if (temp_current_Node == father_Node->Left_child) {
						temp_current_Node = temp_current_Node->Father_Node;
						Right_Rotate(temp_current_Node);
					}
					else {
						father_Node->color_tag = 0;
						grandfa_Node->color_tag = 1;
						Left_Rotate(grandfa_Node);
					}
				}
			}
			
		}
	}
	Root_Node->color_tag = 0;
}

// 左旋转
template<class T>
void RB_Tree<T>::Left_Rotate(RB_Tree_Node<T>* current_Node) {
	RB_Tree_Node<T>* Right_child = current_Node->Right_child;
	current_Node->Right_child = Right_child->Left_child;

	if (current_Node->Right_child)
		current_Node->Right_child->Father_Node = current_Node;
	Right_child->Father_Node = current_Node->Father_Node;
	
	if (current_Node->Father_Node == nullptr)
		Root_Node = Right_child;
	else if (current_Node == current_Node->Father_Node->Left_child)
		current_Node->Father_Node->Left_child = Right_child;
	else
		current_Node->Father_Node->Right_child = Right_child;
	Right_child->Left_child = current_Node;
	current_Node->Father_Node = Right_child;
}

// 右旋转
template<class T>
void RB_Tree<T>::Right_Rotate(RB_Tree_Node<T>* current_Node) {
	RB_Tree_Node<T>* leftChild = current_Node->Left_child;
	current_Node->Left_child = leftChild->Right_child;
	if (current_Node->Left_child != nullptr)
		current_Node->Left_child->Father_Node = current_Node;
	leftChild->Father_Node = current_Node->Father_Node;

	if (current_Node->Father_Node == nullptr)
		Root_Node = leftChild;
	else if (current_Node == current_Node->Father_Node->Left_child)
		current_Node->Father_Node->Left_child = leftChild;
	else 
		current_Node->Father_Node->Right_child = leftChild;

	leftChild->Right_child = current_Node;
	current_Node->Father_Node = leftChild;
}

// 寻找继承节点，为右子树中的最左侧节点
template<class T>
RB_Tree_Node<T>* RB_Tree<T>::Find_Successor_Node(RB_Tree_Node<T>* currNode) {
	RB_Tree_Node<T>* Rchild = currNode->Right_child;
	while (Rchild->Left_child != nullptr) {
		Rchild = Rchild->Left_child;
	}
	return Rchild;
}

// 清除节点所有信息
template<class T>
void RB_Tree<T>::Erase_Tree(RB_Tree_Node<T>* Node_del) {
	Node_del->Left_child = nullptr;
	Node_del->Right_child = nullptr;
	Node_del->color_tag = nullptr;
	Node_del->data = nullptr;
	Node_del->Father_Node = nullptr;
	delete Node_del;
}

template<class T>
void RB_Tree<T>::Fix_Tree_Delete(RB_Tree_Node<T>* current_Node) {

}