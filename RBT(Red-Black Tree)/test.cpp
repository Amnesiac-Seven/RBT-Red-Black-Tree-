
#include <iostream>

// Structure for a node in Red-Black Tree
struct Node {
    int data;
    enum class Color { RED, BLACK };
    Node* parent;
    Node* left;
    Node* right;
    Color color;

    // Constructor
    explicit Node(int data)
        : data(data), parent(nullptr), left(nullptr), right(nullptr), color(Color::RED) {}
};

class RedBlackTree {
private:
    Node* root;

    // Function to perform left rotation at a given node
    void leftRotate(Node* node) {
        Node* rightChild = node->right;
        node->right = rightChild->left;

        if (node->right != nullptr)
            node->right->parent = node;

        rightChild->parent = node->parent;

        if (node->parent == nullptr)
            root = rightChild;
        else if (node == node->parent->left)
            node->parent->left = rightChild;
        else
            node->parent->right = rightChild;

        rightChild->left = node;
        node->parent = rightChild;
    }

    // Function to perform right rotation at a given node
    void rightRotate(Node* current_Node) {
        Node* leftChild = current_Node->left;//1
        current_Node->left = leftChild->right;

        if (current_Node->left != nullptr)
            current_Node->left->parent = current_Node;

        leftChild->parent = current_Node->parent;

        if (current_Node->parent == nullptr)
            root = leftChild;
        else if (current_Node == current_Node->parent->left)
            current_Node->parent->left = leftChild;
        else
            current_Node->parent->right = leftChild;

        leftChild->right = current_Node;
        current_Node->parent = leftChild;
    }

    // Function to fix the Red-Black Tree properties after insertion
    void fixInsertion(Node* node) {
        while (node != root && node->parent->color == Node::Color::RED) {
            if (node->parent == node->parent->parent->left) {
                Node* uncle = node->parent->parent->right;

                // Case 1: Uncle is RED
                if (uncle != nullptr && uncle->color == Node::Color::RED) {
                    uncle->color = Node::Color::BLACK;
                    node->parent->color = Node::Color::BLACK;
                    node->parent->parent->color = Node::Color::RED;
                    node = node->parent->parent;
                }
                else {
                    // Case 2: Uncle is BLACK and node is a right child
                    if (node == node->parent->right) {
                        node = node->parent;
                        leftRotate(node);
                    }

                    // Case 3: Uncle is BLACK and node is a left child
                    node->parent->color = Node::Color::BLACK;
                    node->parent->parent->color = Node::Color::RED;
                    rightRotate(node->parent->parent);
                }
            }
            else {
                Node* uncle = node->parent->parent->left;

                // Case 1: Uncle is RED
                if (uncle != nullptr && uncle->color == Node::Color::RED) {
                    uncle->color = Node::Color::BLACK;
                    node->parent->color = Node::Color::BLACK;
                    node->parent->parent->color = Node::Color::RED;
                    node = node->parent->parent;
                }
                else {
                    // Case 2: Uncle is BLACK and node is a left child
                    if (node == node->parent->left) {
                        node = node->parent;
                        rightRotate(node);
                    }

                    // Case 3: Uncle is BLACK and node is a right child
                    node->parent->color = Node::Color::BLACK;
                    node->parent->parent->color = Node::Color::RED;
                    leftRotate(node->parent->parent);
                }
            }
        }

        root->color = Node::Color::BLACK;  // Ensuring property 2
    }

    // Function to insert a node into the Red-Black Tree
    void insertNode(int data) {
        Node* newNode = new Node(data);

        if (root == nullptr) {
            root = newNode;
            newNode->color = Node::Color::BLACK;  // Ensuring property 2
            return;
        }

        Node* current = root;
        Node* parent = nullptr;

        while (current != nullptr) {
            parent = current;

            if (data < current->data)
                current = current->left;
            else
                current = current->right;
        }

        newNode->parent = parent;

        if (data < parent->data)
            parent->left = newNode;
        else
            parent->right = newNode;

        fixInsertion(newNode);  // Fixing any violations of Red-Black Tree properties
    }

    // Function to print the Red-Black Tree using Inorder traversal
    void printInOrder(Node* node) {
        if (node == nullptr)
            return;

        printInOrder(node->left);
        std::cout << node->data << " ";
        printInOrder(node->right);
    }

public:
    // Constructor
    RedBlackTree() : root(nullptr) {}

    // Function to insert a node into the Red-Black Tree
    void insert(int data) {
        insertNode(data);
    }

    // Function to print the Red-Black Tree
    void print() {
        printInOrder(root);
        std::cout << std::endl;
    }
};

void test(){
    RedBlackTree rbTree;

    // Inserting nodes into the Red-Black Tree
    rbTree.insert(7);
    rbTree.insert(3);
    rbTree.insert(18);
    rbTree.insert(10);
    rbTree.insert(22);
    rbTree.insert(8);
    rbTree.insert(11);
    rbTree.insert(26);
    rbTree.insert(2);
    rbTree.insert(6);
    rbTree.insert(13);

    // Printing the Red-Black Tree
    std::cout << "Red-Black Tree: ";
    rbTree.print();

}
