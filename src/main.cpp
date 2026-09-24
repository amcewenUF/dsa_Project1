#include <iostream>
#include "headers/AVL.hpp"

using namespace std;

int main(){
    AVL tree;   // Create a Tree object

    std::vector<int> inputs  = {2, 4, 1, 7, 5, 3, 6};
    std::vector<std::string> names  = {"Avery", "Brandon", "Brandon", "Caleb", "Daniel", "Ellie", "Fredrick"};
    for (int i = 0; i < inputs.size(); i++) {
        tree.insert(inputs[i], names[i]);
    }

    tree.printLevelCount();


}
