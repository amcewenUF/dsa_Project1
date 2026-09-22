#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "headers/AVL.hpp"


using namespace std;


// you must write 5 unique, meaningful tests for credit on the testing portion of this project!
TEST_CASE("Balance Test") {
	AVL tree;   // Create a Tree object

	std::vector<int> inputs  = {1, 2, 3, 4, 5, 6};
	for (int i : inputs) {
		tree.insert(i);
	}
	
	REQUIRE(std::abs(tree.get_balance_factor(tree.root)) < 2);
}


TEST_CASE("Inorder Test", "[Insert]"){
	
		AVL tree;   // Create a Tree object

		std::vector<int> inputs  = {2, 4, 1, 5, 3};
		for (int i : inputs) {
			tree.insert(i);
		}

		std::vector<Node*> node_pointers_inorder = tree.inorder();

		std::vector<int> ID_outputs;
		for(Node* node : node_pointers_inorder) {
			ID_outputs.push_back(node->ID);
		}

		std::vector<int> expected_output  = {1, 2, 3, 4, 5};


		REQUIRE(ID_outputs == expected_output);
	
}

TEST_CASE("Preorder Test", "[Insert]"){
	
		AVL tree;   // Create a Tree object

		std::vector<int> inputs  = {2, 4, 1, 5, 3};
		for (int i : inputs) {
			tree.insert(i);
		}

		std::vector<Node*> node_pointers_inorder = tree.preorder();

		std::vector<int> ID_outputs;
		for(Node* node : node_pointers_inorder) {
			ID_outputs.push_back(node->ID);
		}

		std::vector<int> expected_output  = {2, 1, 4, 3, 5};


		REQUIRE(ID_outputs == expected_output);	
}

TEST_CASE("Postorder Test", "[Insert]"){
	
		AVL tree;   // Create a Tree object

		std::vector<int> inputs  = {2, 4, 1, 5, 3};
		for (int i : inputs) {
			tree.insert(i);
		}

		std::vector<Node*> node_pointers_inorder = tree.postorder();

		std::vector<int> ID_outputs;
		for(Node* node : node_pointers_inorder) {
			ID_outputs.push_back(node->ID);
		}

		std::vector<int> expected_output  = {1, 3, 5, 4, 2};


		REQUIRE(ID_outputs == expected_output);	
}

TEST_CASE("Zig-Zag Test", "[Insert]"){
	
		AVL tree;   // Create a Tree object

		std::vector<int> inputs  = {6, 2, 4};
		for (int i : inputs) {
			tree.insert(i);
		}

		std::vector<Node*> node_pointers_inorder = tree.inorder();

		std::vector<int> ID_outputs;
		for(Node* node : node_pointers_inorder) {
			ID_outputs.push_back(node->ID);
		}

		std::vector<int> expected_output  = {2, 4, 6};


		REQUIRE(ID_outputs == expected_output);
		REQUIRE(tree.get_balance_factor(tree.root) == 0);
}