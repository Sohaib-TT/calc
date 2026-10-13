#pragma once
#include <string>
#include <vector>

struct Node
{   
    char cvalue[3];
    int type; // 0 = number, 1= operator
    Node* details;
    Node* pdetails;
    Node* n;
    Node* p;
};

struct DisplayNode {
    int type;
    slint::Image image;
    std::vector<DisplayNode> child;
};