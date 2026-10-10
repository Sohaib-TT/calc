#include <stdio.h>
#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <string>

typedef struct Node
{   
    char cvalue[3];
    int type; // 0 = number, 1= operator
    Node* details;
    Node* pdetails;
    Node* n;
    Node* p;
}Node;


int delnode(Node* node,Node** head){
    if(node->type == 0){
        if(node->p != NULL && node->n != NULL){
            node->n->p = node->p;
            node->p->n = node->n;
            free(node);
        }else if(node->p == NULL && node->n != NULL){
            node = node->n;
            free(node->p);
            node->p = NULL;
            *head = node;
        }else if(node->p != NULL && node->n == NULL){
            node = node->p;
            free(node->n);
            node->n = NULL;
        }else{
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
                free(node->p);
                node->p = NULL;
                *head = node;
            }else if(node->p != NULL && node->n == NULL){
                node = node->p;
                free(node->n);
                node->n = NULL;
            }else{
                free(node);
                return 1;
            }
            node = pdetails;
        }
        if(node->p != NULL && node->n != NULL){
            node->n->p = node->p;
            node->p->n = node->n;
            free(node);
        }else if(node->p == NULL && node->n != NULL){
            node = node->n;
            free(node->p);
            node->p = NULL;
            *head = node;
        }else if(node->p != NULL && node->n == NULL){
            node = node->p;
            free(node->n);
            node->n = NULL;
        }else{
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
    return node;
}

void addOp(Node** head,char op,Node* node = NULL){
    
    switch (op)
    {
    case '+': case '-': case 'x': case '%': case '!':
        {Node* opnode = (Node *)malloc(sizeof(Node));
        opnode->cvalue[0] = 'n';
        opnode->cvalue[1] = 'n';
        opnode->cvalue[2] = 'n';
        opnode->type = 1;
        opnode->cvalue[0] = op;
        addnode(head,opnode,node);}
        break;
    case '/':
        {Node* opnode1 = (Node *)malloc(sizeof(Node));
        opnode1->type = 1;
        opnode1->cvalue[0] = '|';
        opnode1->cvalue[1] = '/';
        opnode1->cvalue[2] = 'n';
        addnode(head,opnode1,node);}
        {Node* opnode1 = (Node *)malloc(sizeof(Node));
        opnode1->type = 1;
        opnode1->cvalue[0] = '/';
        opnode1->cvalue[1] = 'n';
        opnode1->cvalue[2] = 'n';
        addnode(head,opnode1,node);}       
        {Node* opnode1 = (Node *)malloc(sizeof(Node));
        opnode1->type = 1;
        opnode1->cvalue[0] = '/';
        opnode1->cvalue[1] = '|';
        opnode1->cvalue[2] = 'n';
        addnode(head,opnode1,node);}        
        break;
    case '1'://ln
        {   Node* opnode1 = (Node *)malloc(sizeof(Node));
            opnode1->type = 1;
            opnode1->cvalue[0] = 'l';
            opnode1->cvalue[1] = '|';
            opnode1->cvalue[2] = 'n';
            addnode(head,opnode1,node);
        }
        {Node* opnode1 = (Node *)malloc(sizeof(Node));
        opnode1->type = 1;
        opnode1->cvalue[0] = '|';
        opnode1->cvalue[1] = 'l';
        opnode1->cvalue[2] = 'n';
        addnode(head,opnode1,node);}
        break;

    case '2'://log
        {Node* opnode1 = (Node *)malloc(sizeof(Node));
        opnode1->type = 1;
        opnode1->cvalue[0] = 'l';
        opnode1->cvalue[1] = 'o';
        opnode1->cvalue[2] = '|';
        addnode(head,opnode1,node);}
        {Node* opnode1 = (Node *)malloc(sizeof(Node));
        opnode1->type = 1;
        opnode1->cvalue[0] = '|';
        opnode1->cvalue[1] = 'l';
        opnode1->cvalue[2] = 'o';
        addnode(head,opnode1,node);}
        break;
    
    case 'e':
        {Node* opnode1 = (Node *)malloc(sizeof(Node));
        opnode1->type = 1;
        opnode1->cvalue[0] = 'e';
        opnode1->cvalue[1] = '|';
        opnode1->cvalue[2] = 'n';
        addnode(head,opnode1,node);}
        {Node* opnode1 = (Node *)malloc(sizeof(Node));
        opnode1->type = 1;
        opnode1->cvalue[0] = '|';
        opnode1->cvalue[1] = 'e';
        opnode1->cvalue[2] = 'n';
        addnode(head,opnode1,node);}
        break;

    default:
        break;
    }
}


int main(){

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
}