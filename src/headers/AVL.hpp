#pragma once

#include "Node.hpp"
#include <vector>
#include <queue>

class AVL {
public:
    Node* root;

    AVL() {
        root = nullptr;
    }

    AVL(Node* root_) {
        root = root_;
    }

    // Tree Helpers

    void rotateTree(Node*& node, bool left) {
        if (left) { // left rotation
            Node* right_node = node->right;
            if (right_node == nullptr) return; // branch is too left heavy to perform a left rotation

            node->right = right_node->left;
            right_node->left = node;

            update_height(node);
            update_height(right_node);
            node = right_node;
            
        }
        else { // right rotation
            Node* left_node = node->left;
            if (left_node == nullptr) return;// branch is too right heavy to perform a right rotation
            node->left = left_node->right;
            left_node->right = node;

            update_height(node);
            update_height(left_node);
            node = left_node;
        }
    }

    int get_balance_factor(Node* node) {
        int left_height = (node->left == nullptr) ? 0 : node->left->height;
        int right_height = (node->right == nullptr) ? 0 : node->right->height;

        return left_height - right_height;
    }

    void update_height(Node* node) {
        int left_height = (node->left == nullptr) ? 0 : node->left->height;
        int right_height = (node->right == nullptr) ? 0 : node->right->height;

        node->height = std::max(left_height, right_height) + 1;
    }

    void balance_node(Node* node) {
        update_height(node);

        int balance_factor = get_balance_factor(node);
        if (balance_factor > 1) { // if tree is left heavy perform right rotation
            if (get_balance_factor(node->left) < 0) { // if left tree is right heavy do a left rotation on it
                rotateTree(node->left, true);
            }
            rotateTree(node, false);
        }
        else if (balance_factor < -1) { // if tree is right heavy perform left rotation
            if (get_balance_factor(node->right) > 0) { // if right tree is left heavy do a right rotation on it
                rotateTree(node->right, false);
            }
            rotateTree(node, true);
        }
    }

    // Tree Editing

    void insert(Node* insert_node) {
        if (root == nullptr) {
            root = insert_node;
        }
        else {
            insertHelper(insert_node, root);
        }
    }

    // wrapper function
    void insert(int ID, std::string name) {
        Node* new_node = new Node(ID, name);
        insert(new_node);
    }

    void insertHelper(Node* insert_node, Node*& tree_node) {
        if (tree_node == nullptr) {
            tree_node = insert_node;
            insert_node->height = 1;
        }
        else {
            if (insert_node->ID < tree_node->ID) {
                insertHelper(insert_node, tree_node->left);
            }
            else if (insert_node->ID > tree_node->ID) {
                insertHelper(insert_node, tree_node->right);
            }

            balance_node(tree_node);
        }
    }


    void removeID(int ID) {
        Node* node = root;
        Node* parent_node;
        bool left;

        while (node->ID != ID) {

            parent_node = node;
            if (node->left != nullptr && ID < node->ID) {
                node = node->left;
                left = true;
            }
            else if (node->right != nullptr && ID > node->ID) {
                node = node->right;
                left = false;
            }
            else {
                std::cout << "unsuccessful" << std::endl;
                return;
            }
        }

        

        if (left) parent_node->left = nullptr;
        else      parent_node->right = nullptr;

        delete node;
        

    }




    // Tree Searching
    void search(int ID) {
        Node* node = root;
        
        while (node->ID != ID) {
            if (node->left != nullptr && ID < node->ID) {
                node = node->left;
            }
            else if (node->right != nullptr && ID > node->ID) {
                node = node->right;
            }
            else {
                std::cout << "unsuccessful" << std::endl;
                return;
            }

        }
        std::cout << "\"" << node->name << "\"" << std::endl;
    }

    void search(std::string name) {
        std::vector<Node*> sorted_nodes = preorder();
        std::vector<int> matches;

        
        for (Node* node : sorted_nodes) {
            if (node->name == name) {
                matches.push_back(node->ID);
            }
        }

        if (matches.empty()) {
            std::cout << "unsuccessful" << std::endl;
        }
        else {
            for (int match : matches) {
                std::cout << match << std::endl;
            }
        }

    }



    // Tree Traversals

    std::vector<Node*> inorder() {
        std::vector<Node*> inorder_vector;
        inorder(root, inorder_vector); // calls the first iteration of the recursion with the root node

        return inorder_vector;
    }

    // recursive helper function
    void inorder(Node* tree_node, std::vector<Node*>& inorder_vector) {
        if (tree_node == nullptr) {
            return;
        }
        
        // LEFT -> NODE -> RIGHT
        inorder(tree_node->left, inorder_vector);
        inorder_vector.push_back(tree_node);
        inorder(tree_node->right, inorder_vector);
    }




    std::vector<Node*> preorder() {
        std::vector<Node*> preorder_vector;
        preorder(root, preorder_vector);  // calls the first iteration of the recursion with the root node

        return preorder_vector;
    }

    // recursive helper function
    void preorder(Node* tree_node, std::vector<Node*>& preorder_vector) {
        if (tree_node == nullptr) {
            return;
        }

        // NODE -> LEFT -> RIGHT 
        preorder_vector.push_back(tree_node);
        preorder(tree_node->left, preorder_vector);
        preorder(tree_node->right, preorder_vector);

    }




    std::vector<Node*> postorder() {
        std::vector<Node*> postorder_vector;
        postorder(root, postorder_vector);  // calls the first iteration of the recursion with the root node

        return postorder_vector;
    }

    // recursive helper function
    void postorder(Node* tree_node, std::vector<Node*>& postorder_vector) {
        if (tree_node == nullptr) {
            return;
        }
        // RIGHT -> LEFT -> NODE
        postorder(tree_node->left, postorder_vector);
        postorder(tree_node->right, postorder_vector);
        postorder_vector.push_back(tree_node);


    }

    std::vector<Node*> levelorder() {
        std::vector<Node*> level_order_vector;
        std::queue<Node*> next_nodes;
        next_nodes.push(root);

        while(!next_nodes.empty()) {
            Node* check = next_nodes.front();
            if (check->left != nullptr) {
                next_nodes.push(check->left);
            }
            if (check->right != nullptr) {
                next_nodes.push(check->right);
            }

            level_order_vector.push_back(check);
            next_nodes.pop();
        }
        return level_order_vector;
    }





    // Printing

    // printing helper function that just prints out the node vector in order
    void print_node_vector(std::vector<Node*> vector) {
        for (std::size_t i = 0; i < vector.size(); ++i) {
            std::cout << vector[i]->name;
            
            if (i + 1 < vector.size()) {
                std::cout << ", ";
            } else {
                std::cout << std::endl;
            }
        }
    }

    // print wrappers
    void printInorder() {
        print_node_vector(inorder());
    }

    void printPreorder() {
        print_node_vector(preorder());

    }

    void printPostorder() {
        print_node_vector(postorder());
    }

    void printLevelorder() {
        print_node_vector(levelorder());
    }

    void printLevelCount() {
        if (root == nullptr) {
            std::cout << 0 << std::endl;
        }
        else {
            std::cout << root->height << std::endl;
        }
    }
};