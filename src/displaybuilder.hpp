#include "app-window.h"
#include "nodes.hpp"

#include <stdio.h>
#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <string>


void displaySlint (const std::shared_ptr<slint::VectorModel<slint::SharedString>>& display, Node* head,Node* cursor){
    slint::SharedString text = "";
    display->clear();
    if(cursor == head){
        display->push_back("I");
    }
    Node* node = head->next;
    while(node != nullptr){
        for (int i = 0; i < (node->value.length()); i++)
        {
            text = std::string(1, node->value[i]);
            std::cout << text;
            display->push_back(text);
        }
        
        if(cursor == node){
            display->push_back("I");
        }
        node = node->next;
    }
}

void add(Node** cursor,std::string value){
    Node* node = new Node();
    node->value = value;
    node->next = (*cursor)->next;
    (*cursor)->next = node;
    node->previous = (*cursor);
    *cursor = node;
}

void del(Node** cursor){
    if((*cursor)->value == "Start"){return;}
    Node* del = *cursor;
    (*cursor) = (*cursor)->previous;
    del->previous->next = del->next;
    if (del->next){del->next->previous = *cursor;}
    delete del;
}

void moveCursor(Node** cursor,std::string diraction){
    if(diraction == ">"){
        if((*cursor)->next != nullptr){
            *cursor = (*cursor)->next;
        }
    }else if(diraction == "<"){
        if((*cursor)->value != "Start"){
            *cursor = (*cursor)->previous;
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