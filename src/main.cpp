#include "app-window.h"
#include <stdio.h>
#include <cstdio>
#include <stdlib.h>
#include <string>
#include "nodes.hpp"
#include <vector>



int displaySlint (const std::shared_ptr<slint::VectorModel<slint::SharedString>>& display, Node* head,Node* cursor=NULL){
    slint::SharedString text = "";
    int i = 0, cursor_index = 0;
    display->clear();
    Node* node = head;
    while(node != NULL){
        switch (node->cvalue[0])
        {
        case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
        case '+': case '-': case '%': case '!':case '(':case ')':case '.':case '^': case 'e':
            text = std::string(1, node->cvalue[0]);
            break;
    
        case 'x':
            text ="*";
            break;
        case '/':
            if (node->cvalue[1] == '|'){text ="(";}
            else{text =")/(";}
            break;
        case 'l':
            if (node->cvalue[1] == '|'){text ="ln(";}
            else{text ="log(";}
            break;
        case 'c':
            text ="cos(";
            break;
        case 's':
            text ="sin(";
            break;
        case 't':
            text ="tan(";
            break;
        case 'r':
            text ="√(";
            break;
        case '|':
            text =")";
            break;
        default:
            break;
        }
        if (node == cursor){display->push_back("I"); cursor_index =i;}else{i++;}
        
        display->push_back(text);
        
        node = node->n;
    }
    if (cursor == NULL){display->push_back("I");cursor_index =i;}
    return cursor_index;
}

int delnode(Node** cursor,Node** head){
    Node* node = *cursor;
    if (*head == NULL){return 0;}
    if(node==NULL){
        node = *head;
        while(node->n != NULL){node = node->n;}
    }else if(node->p != NULL){node = node->p;}
    if(node->type == 0){
        if(node->p != NULL && node->n != NULL){
            node->n->p = node->p;
            node->p->n = node->n;
            free(node);
        }else if(node->p == NULL && node->n != NULL){
            node = node->n;
            *head = node;
            *cursor = node;
            free(node->p);
            node->p = NULL;
        }else if(node->p != NULL && node->n == NULL){
            node = node->p;
            free(node->n);
            node->n = NULL;
        }else{
            *head = NULL;
            *cursor = NULL;
            free(node);
            return 1;
        }
    }else if(node->type == 1){
        if(*cursor != NULL && (*cursor)->p != NULL){
            *cursor = (*cursor)->p;
        }else if(*cursor != NULL && (*cursor)->n != NULL){
            *cursor = (*cursor)->n;
        }
        while(node->details != NULL) node = node->details;
        while(node->pdetails != NULL) {
            Node* pdetails = node->pdetails;
            if(node->p != NULL && node->n != NULL){
                node->n->p = node->p;
                node->p->n = node->n;
                free(node);
            }else if(node->p == NULL && node->n != NULL){
                node = node->n;
                *head = node;
                free(node->p);
                node->p = NULL;
            }else if(node->p != NULL && node->n == NULL){
                node = node->p;
                free(node->n);
                node->n = NULL;
            }else{
                *head = NULL;
                *cursor = NULL;
                free(node);
                return 1;
            }
            node = pdetails;
            if(node == NULL){return 1;}
        }
        if(node->p != NULL && node->n != NULL){
            node->n->p = node->p;
            node->p->n = node->n;
            free(node);
        }else if(node->p == NULL && node->n != NULL){
            node = node->n;
            *head = node;
            free(node->p);
            node->p = NULL;
            *head = node;
        }else if(node->p != NULL && node->n == NULL){
            node = node->p;
            free(node->n);
            node->n = NULL;
        }else{
            *head = NULL;
            *cursor = NULL;
            free(node);
            return 1;
        }
        
    }
    return 0;
}

int addnode(Node** head,Node* newnode,Node* node = NULL){
    if (head == NULL || newnode == NULL) return -1;

    if (*head == NULL) {
        *head = newnode;
        newnode->n = NULL;
        newnode->p = NULL;
        return 0;
    }

    if (node != NULL) {
        if(node->p != NULL){node->p->n = newnode;}
        else{*head = newnode;}
        newnode->p = node->p;
        newnode->n = node;
        node->p = newnode;
        if(*head == node){*head = newnode;}
        return 0;
    }

    Node* temp = *head;
    while (temp->n != NULL) {
        temp = temp->n;
    }
    temp->n = newnode;
    newnode->n = NULL;
    newnode->p = temp;

    return 0;
}

int cmdDisplay(Node* head, Node* cursor) {
    if (head == NULL){
        return 0;
    }
    Node* node = head;
    while (node != NULL){
        if(node == cursor){printf("I");}
        if(node->type == 0){
            printf("%c",node->cvalue[0]);
        }else{
            for (int i = 0; i < 3; i++) if (node->cvalue[i]!= 'n') {printf("%c",node->cvalue[i]);}
        }    
        node = node->n;
    }
    if(cursor == NULL){printf("I");}
    printf("\n");
    return 0;
}

Node* addNum(char value){
    Node* node = (Node *)malloc(sizeof(Node));
    node->type = 0;
    node->cvalue[0] = value;
    node->n = NULL;
    node->p = NULL;
    return node;
}

void addOp(Node** head,char op,Node** cursor = NULL){
    Node * node = NULL;
    if(cursor != NULL){node = *cursor;}
    switch (op)
    {
    case '+': case '-': case 'x': case '%': case '!':case '(':case ')':case '.':case '^':case 'e':
        {Node* opnode = (Node *)malloc(sizeof(Node));
        opnode->cvalue[0] = 'n';
        opnode->cvalue[1] = 'n';
        opnode->cvalue[2] = 'n';
        opnode->details = NULL;
        opnode->pdetails = NULL;
        opnode->p = NULL;
        opnode->n = NULL;
        opnode->type = 1;
        opnode->cvalue[0] = op;
        addnode(head,opnode,node);}
        break;
    case '/':
    {
        Node* opnode1 = (Node *)malloc(sizeof(Node));
        opnode1->type = 1;
        opnode1->cvalue[0] = '/';
        opnode1->cvalue[1] = '|';
        opnode1->cvalue[2] = 'n';
        opnode1->p = NULL;
        opnode1->n = NULL;
        opnode1->details = NULL;
        addnode(head,opnode1,node);
        Node* opnode2 = (Node *)malloc(sizeof(Node));
        opnode2->type = 1;
        opnode2->cvalue[0] = '/';
        opnode2->cvalue[1] = 'n';
        opnode2->cvalue[2] = 'n';
        opnode2->p = NULL;
        opnode2->n = NULL;
        opnode2->details = opnode1;
        opnode1->pdetails = opnode2;
        addnode(head,opnode2,node);       
        Node* opnode3 = (Node *)malloc(sizeof(Node));
        opnode3->type = 1;
        opnode3->cvalue[0] = '|';
        opnode3->cvalue[1] = '/';
        opnode3->cvalue[2] = 'n';
        opnode3->p = NULL;
        opnode3->n = NULL;
        opnode3->details = opnode2;
        opnode3->pdetails = NULL;
        opnode2->pdetails = opnode3;
        addnode(head,opnode3,node);
        }       
        break;
    case '1'://ln
        {
        Node* opnode1 = (Node *)malloc(sizeof(Node));
        opnode1->type = 1;
        opnode1->cvalue[0] = 'l';
        opnode1->cvalue[1] = '|';
        opnode1->cvalue[2] = 'n';
        opnode1->p = NULL;
        opnode1->n = NULL;
        addnode(head,opnode1,node);

        Node* opnode2 = (Node *)malloc(sizeof(Node));
        opnode2->type = 1;
        opnode2->cvalue[0] = '|';
        opnode2->cvalue[1] = 'l';
        opnode2->cvalue[2] = 'n';
        opnode2->p = NULL;
        opnode2->n = NULL;
        addnode(head,opnode2,node);
        
        opnode1->details = NULL;
        opnode2->details = opnode1;
        opnode2->pdetails = NULL;
        opnode1->pdetails = opnode2;
        }
        break;

    case '2'://log
        {
        Node* opnode1 = (Node *)malloc(sizeof(Node));
        opnode1->type = 1;
        opnode1->cvalue[0] = 'l';
        opnode1->cvalue[1] = 'o';
        opnode1->cvalue[2] = '|';
        opnode1->p = NULL;
        opnode1->n = NULL;
        addnode(head,opnode1,node);
        Node* opnode2 = (Node *)malloc(sizeof(Node));
        opnode2->type = 1;
        opnode2->cvalue[0] = '|';
        opnode2->cvalue[1] = 'l';
        opnode2->cvalue[2] = 'o';
        opnode2->p = NULL;
        opnode2->n = NULL;
        addnode(head,opnode2,node);

        opnode1->details = NULL;
        opnode2->details = opnode1;
        opnode2->pdetails = NULL;
        opnode1->pdetails = opnode2;}
        break;
    
    
    
    case 'c'://cos
        {
        Node* opnode1 = (Node *)malloc(sizeof(Node));
        opnode1->type = 1;
        opnode1->cvalue[0] = 'c';
        opnode1->cvalue[1] = 'o';
        opnode1->cvalue[2] = '|';
        opnode1->p = NULL;
        opnode1->n = NULL;
        addnode(head,opnode1,node);

        Node* opnode2 = (Node *)malloc(sizeof(Node));
        opnode2->type = 1;
        opnode2->cvalue[0] = '|';
        opnode2->cvalue[1] = 'c';
        opnode2->cvalue[2] = 'o';
        opnode2->p = NULL;
        opnode2->n = NULL;
        addnode(head,opnode2,node);
        
        opnode1->details = NULL;
        opnode2->details = opnode1;
        opnode2->pdetails = NULL;
        opnode1->pdetails = opnode2;
        }
        break;
    
    case 's'://sin
        {
        Node* opnode1 = (Node *)malloc(sizeof(Node));
        opnode1->type = 1;
        opnode1->cvalue[0] = 's';
        opnode1->cvalue[1] = 'i';
        opnode1->cvalue[2] = '|';
        opnode1->p = NULL;
        opnode1->n = NULL;
        addnode(head,opnode1,node);

        Node* opnode2 = (Node *)malloc(sizeof(Node));
        opnode2->type = 1;
        opnode2->cvalue[0] = '|';
        opnode2->cvalue[1] = 's';
        opnode2->cvalue[2] = 'i';
        opnode2->p = NULL;
        opnode2->n = NULL;
        addnode(head,opnode2,node);
        
        opnode1->details = NULL;
        opnode2->details = opnode1;
        opnode2->pdetails = NULL;
        opnode1->pdetails = opnode2;
        }
        break;
    
    case 't': //tan
        {
        Node* opnode1 = (Node *)malloc(sizeof(Node));
        opnode1->type = 1;
        opnode1->cvalue[0] = 't';
        opnode1->cvalue[1] = 'a';
        opnode1->cvalue[2] = '|';
        opnode1->p = NULL;
        opnode1->n = NULL;
        addnode(head,opnode1,node);

        Node* opnode2 = (Node *)malloc(sizeof(Node));
        opnode2->type = 1;
        opnode2->cvalue[0] = '|';
        opnode2->cvalue[1] = 't';
        opnode2->cvalue[2] = 'a';
        opnode2->p = NULL;
        opnode2->n = NULL;
        addnode(head,opnode2,node);
        
        opnode1->details = NULL;
        opnode2->details = opnode1;
        opnode2->pdetails = NULL;
        opnode1->pdetails = opnode2;
        }
        break;
    
    
    case 'r':
    {
        Node* opnode1 = (Node *)malloc(sizeof(Node));
        opnode1->type = 1;
        opnode1->cvalue[0] = 'r';
        opnode1->cvalue[1] = 't';
        opnode1->cvalue[2] = '|';
        opnode1->p = NULL;
        opnode1->n = NULL;
        opnode1->details = NULL;
        addnode(head,opnode1,node);
        Node* opnode2 = (Node *)malloc(sizeof(Node));
        opnode2->type = 1;
        opnode2->cvalue[0] = '|';
        opnode2->cvalue[1] = 'r';
        opnode2->cvalue[2] = 't';
        opnode2->p = NULL;
        opnode2->n = NULL;
        opnode2->details = opnode1;
        opnode1->pdetails = opnode2;
        addnode(head,opnode2,node);
        }       
        break;
    default:{
        break;
    }
    }
}

int ac(Node** head,Node** cursor){
    if(*head == NULL){return 0;}
    Node* current = *head;
    while (current != NULL) {
        Node* nextNode = current->n;
        free(current);
        current = nextNode; 
    }
    *head = NULL;
    *cursor = NULL;
    return 1;
}

int cursorMov(Node** cursor,Node** head,char diraction){
    if (*head == NULL){ return 0;}
    
    Node* node = *cursor;
    switch (diraction)
    {
    case '<':
        if(*cursor == NULL){
            node = *head;
            while (node->n != NULL){*cursor = node->n;node = *cursor;} 
            return 0; 
        }
        if(node->p != NULL){
            *cursor = node->p;
        }
        break;
    case '>':
        if(*cursor == NULL){return 0;}
        *cursor = node->n;
        break;
    
    default:
        break;
    }
    return 0;
}

#ifdef __ANDROID__
extern "C" void slint_main()
#else
int main(int argc, char **argv)
#endif
{   
    auto ui = AppWindow::create();

    std::vector<slint::SharedString> display = {""};
    auto model = std::make_shared<slint::VectorModel<slint::SharedString>>();
    ui->set_display_list(model);


    Node* eqHead = NULL;
    Node* cursor = NULL;
    int cursor_index;

    displaySlint(model, eqHead);
 

    std::string equation = "987+/3>2";

    ui->on_button_pressed([&](slint::SharedString val) {
        std::string value = std::string(val);
        if (value == "0") {addnode(&eqHead,addNum('0'),cursor);}
        else if(value == "1"){addnode(&eqHead,addNum('1'),cursor);}
        else if(value == "2"){addnode(&eqHead,addNum('2'),cursor);}
        else if(value == "3"){addnode(&eqHead,addNum('3'),cursor);}
        else if(value == "4"){addnode(&eqHead,addNum('4'),cursor);}
        else if(value == "5"){addnode(&eqHead,addNum('5'),cursor);}
        else if(value == "6"){addnode(&eqHead,addNum('6'),cursor);}
        else if(value == "7"){addnode(&eqHead,addNum('7'),cursor);}
        else if(value == "8"){addnode(&eqHead,addNum('8'),cursor);}
        else if(value == "9"){addnode(&eqHead,addNum('9'),cursor);}
        else if(value == "dot"){addOp(&eqHead,'.',&cursor);}
        else if(value == "del"){delnode(&cursor,&eqHead);}
        else if(value == "div"){addOp(&eqHead,'/',&cursor);}
        else if(value == "+"){addOp(&eqHead,'+',&cursor);}
        else if(value == "-"){addOp(&eqHead,'-',&cursor);}
        else if(value == "x"){addOp(&eqHead,'x',&cursor);}
        else if(value == "%"){addOp(&eqHead,'%',&cursor);}
        else if(value == "ac"){ac(&eqHead,&cursor);}
        else if(value == "ln"){addOp(&eqHead,'1',&cursor);}
        else if(value == "log"){addOp(&eqHead,'2',&cursor);}
        else if(value == "cos"){addOp(&eqHead,'c',&cursor);}
        else if(value == "sin"){addOp(&eqHead,'s',&cursor);}
        else if(value == "tan"){addOp(&eqHead,'t',&cursor);}
        else if(value == "e"){addOp(&eqHead,'e',&cursor);}
        else if(value == "^"){addOp(&eqHead,'^',&cursor);}
        else if(value == "("){addOp(&eqHead,'(',&cursor);}
        else if(value == ")"){addOp(&eqHead,')',&cursor);}
        else if(value == "root"){addOp(&eqHead,'r',&cursor);}
        else if(value == "<"){cursorMov(&cursor,&eqHead,'<');}
        else if(value == ">"){cursorMov(&cursor,&eqHead,'>');}
        cursor_index = displaySlint(model, eqHead, cursor);
        ui->set_cursor_index(cursor_index);
        cmdDisplay(eqHead,cursor);
    });
    ui->on_open_docs([]() {
        #if defined(_WIN32)
            system("start readme.html");
        #elif defined(__APPLE__)
            system("open readme.html");
        #else
            system("xdg-open readme.html");
        #endif
    });
    ui->on_open_info([]() {
        #if defined(_WIN32)
            system("start https://github.com/Sohaib-TT/calc");
        #elif defined(__APPLE__)
            system("open https://github.com/Sohaib-TT/calc");
        #else
            system("xdg-open https://github.com/Sohaib-TT/calc");
        #endif
    });
    ui->set_cursor_index(cursor_index);
    ui->run();
}