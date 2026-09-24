#pragma once

class Node {
public:
    Node* left;
    Node* right;

    std::string name;
    int ID;
    int height = 0;
    
    Node(int ID_ = 0, std::string name_ = "") {
        ID = ID_;
        name = name_;
        left = nullptr;
        right = nullptr;
    }


};