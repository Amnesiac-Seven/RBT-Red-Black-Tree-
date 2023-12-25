#include"RB_Tree_Node.h"

template<class T>
RB_Tree_Node<T>::RB_Tree_Node(T data_in) :data(data_in), color_tag(0), Left_child(nullptr), Right_child(nullptr), Father_Node(nullptr) {
	color_tag = 1;
	data = data_in;
}
template<class T>
RB_Tree_Node<T>::~RB_Tree_Node() {

}