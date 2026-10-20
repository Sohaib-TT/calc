#include "app-window.h"
#include "nodes.hpp"

#include <stdio.h>
#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <string>


int displaySlint (const std::shared_ptr<slint::VectorModel<slint::SharedString>>& display, Node* head,Node* cursor=NULL){
    slint::SharedString text = "";
    int i = 0, cursor_index = 0;
    display->clear();
    Node* node = head;
    while(node != NULL){
        text = node-> value;
        display->push_back(text);
        node = node->next;
    }
    return cursor_index;
}

Node* createNode(std::string value){
    Node* node = new Node();
    node->value = value;
    node->next = nullptr;
    node->previous = nullptr;
    return node;
}

void add(Node* cursor,std::string value){
    Node* node = createNode(value);
    node->next = cursor->next;
    cursor->next = node;
    node->previous = cursor;
}

void del(Node* cursor){
    if(cursor->value == "Start"){return;}
    cursor->previous->next = cursor->next;
    free(cursor);
}

void moveCursor(Node** cursor,std::string diraction){
    Node* node = *cursor;
    if(diraction == ">"){
        if(node->next != nullptr){
            *cursor = node->next;
        }
    }else if(diraction == "<"){
        if(node->value != "Start"){
            *cursor = node->previous;
        }
    }
}

void displayCMD(Node* head,Node* cursor){
    Node* node = head;
    while (node != nullptr)
    {  
        std::cout << node->value;
        if (node==cursor){std::cout << "I";}
        node = node->next;
    }
    std::cout <<"\n";
}

int displayBuilder(Node* node , Node* end = NULL){
    return 0;
} 