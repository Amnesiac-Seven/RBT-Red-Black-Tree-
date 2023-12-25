
#include<queue>
#include"RB_Tree.h"
#include"RB_Tree.cpp"
#include"RB_Tree_Node.h"
using namespace std;
void dfs(RB_Tree_Node<double>* node) {// ÖÐÐò±éÀú
	if (node == nullptr)return;
	dfs(node->Left_child);
	printf("%.2f\t%d\n", node->data, node->color_tag);
	dfs(node->Right_child);
}

int main() {
	RB_Tree<double>* node = new RB_Tree<double>(1.0);
	for (int i = 2; i < 10; i++) 
		node->Insert_Node((double)(rand()%100));
	queue<RB_Tree_Node<double>*> q;
	q.push(node->Root_Node);
	while (!q.empty()) {
		auto u = q.front();
		q.pop();
		printf("%.2f\t%d\n", u->data, u->color_tag);
		// std::cout << u->data << "   " << u->color_tag << endl;
		if (u->Left_child)q.push(u->Left_child);
		if (u->Right_child)q.push(u->Right_child);
	}
	printf("-----------------------------------------\n");
	dfs(node->Root_Node);
	printf("-----------------------------------------\n");
	node->Delete_Node(8.0);
	node->Insert_Node(15.0);
	node->Insert_Node(100.5);
	node->Insert_Node(-0.5);
	node->Insert_Node(-11.2);
	q = queue<RB_Tree_Node<double>*>();
	q.push(node->Root_Node);
	// q.push(node->Root_Node);
	while (!q.empty()) {
		auto u = q.front();
		q.pop();
		printf("%.2f\t%d\n", u->data, u->color_tag);
		if (u->Left_child)q.push(u->Left_child);
		if (u->Right_child)q.push(u->Right_child);
	}
	printf("-----------------------------------------\n");
	dfs(node->Root_Node);
	printf("-----------------------------------------\n");
	return 0;
}