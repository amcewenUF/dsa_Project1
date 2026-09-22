#include <iostream>
#include "headers/AVL.hpp"

using namespace std;

int main(){
    AVL tree;   // Create a Tree object

    std::vector<int> inputs  = {2, 4, 1, 5, 3, 6};
    for (int i : inputs) {
        tree.insert(i);
    }

    tree.printInorder();

}
