#pragma once
#include <string>
#include <vector>

struct Node
{   
    std::string value;
    Node* next;
    Node* previous;
};

struct DisplayNode {
    int type;
    slint::Image image;
    std::vector<DisplayNode> child;
};