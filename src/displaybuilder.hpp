#pragma once

#include "app-window.h"
#include "nodes.hpp"

#include <stdio.h>
#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <string>


inline void displaySlint (
    slint::ComponentHandle<AppWindow>ui,
    const std::shared_ptr<slint::VectorModel<slint::SharedString>>& display,
    Node* head,
    Node* cursor,
    int dsplylength)
    {
    std::string eq = "";
    bool leftof= false,rightof=false;
    display->clear();
    if(cursor == head){
        eq.append("I");
    }
    //creating the whole eqution string
    Node* node = head->next;
    while(node != nullptr){
        for (int i = 0; i < (node->value.length()); i++){
            eq.append(std::string(1, node->value[i]));
            //display->push_back();
        }
        if(cursor == node){eq.append("I");}//display->push_back("I");}
        node = node->next;
    }
    std::cout <<"\n"+eq;
    //creating the display string
    std::string dsplyStr = "";
    int i = eq.find("I");
    while (dsplyStr.length() < (dsplylength-2)){
        dsplyStr = eq.at(i) + dsplyStr;
        i--;
        leftof=true;
        if(i< 0){leftof=false;break;}
    }
    i = eq.find("I");
    i++;
    while (dsplyStr.length() < dsplylength && i<eq.length()){
        dsplyStr = dsplyStr + eq.at(i);
        i++;
        rightof= true;
        if(i== eq.length()){rightof=false;break;}
    }
    std::cout <<"\n"<<"dislpay: "<< dsplyStr;

    //sending string to display
    for ( i = 0; i < dsplyStr.length(); i++){
        if(dsplyStr.at(i) == '\''){display->push_back(slint::SharedString("root"));}
        else{display->push_back(slint::SharedString(std::string(1, dsplyStr.at(i))));}
    }
    ui->set_leftOverflow(leftof);
    ui->set_rightOverflow(rightof);
    
}

inline void add(Node** cursor,std::string value){
    Node* node = new Node();
    node->value = value;
    node->next = (*cursor)->next;
    (*cursor)->next = node;
    node->previous = (*cursor);
    *cursor = node;
}

inline void del(Node** cursor){
    if((*cursor)->value == "Start"){return;}
    Node* del = *cursor;
    (*cursor) = (*cursor)->previous;
    del->previous->next = del->next;
    if (del->next){del->next->previous = *cursor;}
    delete del;
}

inline void moveCursor(Node** cursor,std::string diraction){
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

inline void displayCMD(Node* head,Node* cursor){
    Node* node = head;
    while (node != nullptr)
    {  
        std::cout << node->value;
        if (node==cursor){std::cout << "I";}
        node = node->next;
    }
    std::cout <<"\n";
}

inline void ac(Node* head,Node** cursor){
    Node* node = head;
    *cursor = head;
    while (node->next != NULL){node = node->next;}
    while (node->previous != NULL){
        node = node->previous;
        delete node->next;
        node->next = NULL;
    }
}