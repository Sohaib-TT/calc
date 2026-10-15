#include "app-window.h"
#include <stdio.h>
#include <cstdio>
#include <stdlib.h>
#include <string>
#include "nodes.hpp"



int delnode(Node* node,Node** head){
    if(node==NULL){
        return 0;
    }
    if(node->type == 0){
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
            free(node);
            return 1;
        }
    }else if(node->type == 1){
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
        return 0;
    }

    if (node != NULL) {
        newnode->n = node->n;
        node->n = newnode;
        return 0;
    }

    Node* temp = *head;
    while (temp->n != NULL) {
        temp = temp->n;
    }
    temp->n = newnode;
    newnode->n = NULL;

    return 0;
}
int display(Node* head){
    if (head == NULL){
        return 0;
    }
    Node* node = head;
    while (node != NULL){
        if(node->type == 0){
            printf("%c",node->cvalue[0]);
        }else{
            for (int i = 0; i < 3; i++) if (node->cvalue[i]!= 'n') {printf("%c",node->cvalue[i]);}
        }    
        node = node->n;
    }
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

void addOp(Node** head,char op,Node* node = NULL){
    switch (op)
    {
    case '+': case '-': case 'x': case '%': case '!':case '(':case ')':case '.':
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
        opnode1->cvalue[0] = '|';
        opnode1->cvalue[1] = '/';
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
        opnode3->cvalue[0] = '/';
        opnode3->cvalue[1] = '|';
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
    
    case 'e':
        {
        Node* opnode1 = (Node *)malloc(sizeof(Node));
        opnode1->type = 1;
        opnode1->cvalue[0] = 'e';
        opnode1->cvalue[1] = '|';
        opnode1->cvalue[2] = 'n';
        opnode1->p = NULL;
        opnode1->n = NULL;
        addnode(head,opnode1,node);
        Node* opnode2 = (Node *)malloc(sizeof(Node));
        opnode2->type = 1;
        opnode2->cvalue[0] = '|';
        opnode2->cvalue[1] = 'e';
        opnode2->cvalue[2] = 'n';
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
    
    case '^':
    {
        Node* opnode1 = (Node *)malloc(sizeof(Node));
        opnode1->type = 1;
        opnode1->cvalue[0] = 'p';
        opnode1->cvalue[1] = 'w';
        opnode1->cvalue[2] = '|';
        opnode1->p = NULL;
        opnode1->n = NULL;
        opnode1->details = NULL;
        addnode(head,opnode1,node);
        Node* opnode2 = (Node *)malloc(sizeof(Node));
        opnode2->type = 1;
        opnode2->cvalue[0] = 'p';
        opnode2->cvalue[1] = 'w';
        opnode2->cvalue[2] = 'r';
        opnode2->p = NULL;
        opnode2->n = NULL;
        opnode2->details = opnode1;
        opnode1->pdetails = opnode2;
        addnode(head,opnode2,node);       
        Node* opnode3 = (Node *)malloc(sizeof(Node));
        opnode3->type = 1;
        opnode3->cvalue[0] = '|';
        opnode3->cvalue[1] = 'p';
        opnode3->cvalue[2] = 'w';
        opnode3->p = NULL;
        opnode3->n = NULL;
        opnode3->details = opnode2;
        opnode3->pdetails = NULL;
        opnode2->pdetails = opnode3;
        addnode(head,opnode3,node);
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
        opnode2->cvalue[0] = 'r';
        opnode2->cvalue[1] = '|';
        opnode2->cvalue[2] = 'n';
        opnode2->p = NULL;
        opnode2->n = NULL;
        opnode2->details = opnode1;
        opnode1->pdetails = opnode2;
        addnode(head,opnode2,node);       
        Node* opnode3 = (Node *)malloc(sizeof(Node));
        opnode3->type = 1;
        opnode3->cvalue[0] = '|';
        opnode3->cvalue[1] = 'r';
        opnode3->cvalue[2] = 't';
        opnode3->p = NULL;
        opnode3->n = NULL;
        opnode3->details = opnode2;
        opnode3->pdetails = NULL;
        opnode2->pdetails = opnode3;
        addnode(head,opnode3,node);
        }       
        break;
    default:{
        break;
    }
    }
}
int ac(Node** head){
    if(*head == NULL){return 0;}
    Node* current = *head;
    while (current != NULL) {
        Node* nextNode = current->n;
        free(current);
        current = nextNode; 
    }
    *head = NULL;
    return 1;
}


#ifdef __ANDROID__
extern "C" void slint_main()
#else
int main(int argc, char **argv)
#endif
{
    auto ui = AppWindow::create();

    
    Node* eqHead = NULL;
    


    addnode(&eqHead,addNum('9'));
    addnode(&eqHead,addNum('8'));
    addnode(&eqHead,addNum('7'));
    addnode(&eqHead,addNum('6'));
    addnode(&eqHead,addNum('5'));
    addnode(&eqHead,addNum('4'));
    addOp(&eqHead,'e');
    addOp(&eqHead,'/');
    display(eqHead);

    std::string equation = "987+/3>2";

    ui->on_button_pressed([&](slint::SharedString val) {
        std::string value = std::string(val);
        if (value == "0") {addnode(&eqHead,addNum('0'));}
        else if(value == "1"){addnode(&eqHead,addNum('1'));}
        else if(value == "2"){addnode(&eqHead,addNum('2'));}
        else if(value == "3"){addnode(&eqHead,addNum('3'));}
        else if(value == "4"){addnode(&eqHead,addNum('4'));}
        else if(value == "5"){addnode(&eqHead,addNum('5'));}
        else if(value == "6"){addnode(&eqHead,addNum('6'));}
        else if(value == "7"){addnode(&eqHead,addNum('7'));}
        else if(value == "8"){addnode(&eqHead,addNum('8'));}
        else if(value == "9"){addnode(&eqHead,addNum('9'));}
        else if(value == "dot"){addOp(&eqHead,'.');}
        else if(value == "del"){delnode(eqHead,&eqHead);}
        else if(value == "div"){addOp(&eqHead,'/');}
        else if(value == "+"){addOp(&eqHead,'+');}
        else if(value == "-"){addOp(&eqHead,'-');}
        else if(value == "x"){addOp(&eqHead,'x');}
        else if(value == "%"){addOp(&eqHead,'%');}
        else if(value == "ac"){ac(&eqHead);}
        else if(value == "ln"){addOp(&eqHead,'1');}
        else if(value == "log"){addOp(&eqHead,'2');}
        else if(value == "cos"){addOp(&eqHead,'c');}
        else if(value == "sin"){addOp(&eqHead,'s');}
        else if(value == "tan"){addOp(&eqHead,'t');}
        else if(value == "e"){addOp(&eqHead,'e');}
        else if(value == "^"){addOp(&eqHead,'^');}
        else if(value == "("){addOp(&eqHead,'(');}
        else if(value == ")"){addOp(&eqHead,')');}
        else if(value == "root"){addOp(&eqHead,'r');}
        display(eqHead); 
    });

    ui->run();
}