//
//  linked_list.cpp
//  my_crypto
//
//  Created by qTp on 12/22/20.
//  Copyright © 2020 qTp. All rights reserved.
//

#include "linked_list.hpp"

LinkedList *CreateList(bool x){
    LinkedList *l = new LinkedList;
    l->head = new Node;
    l->head->data = x;
    l->head->prev = NULL;
    l->head->next = NULL;
    l->tail = l->head;
    l->size=1;
    return l;
}
LinkedList *CreateList(string s){
    LinkedList *l = CreateList(0);
    for (int i=0; i<s.length(); i++){
        if (s[i]==48){
            if (l->size>1)
                AddTail(l, 0);
        }
        else
            AddTail(l, 1);
    }
    if (l->size>1){
        DeleteAtHead(l);
    }
    return l;
}

LinkedList *CloneList(LinkedList *l){
    Node *p=l->head;
    LinkedList *rs = CreateList(p->data);
    p=p->next;
    while (p!=NULL){
        AddTail(rs, p->data);
        p=p->next;
    }
    return rs;
}

LinkedList *AddHead(LinkedList *l, bool x){
    Node *temp = new Node;
    temp->data = x;
    temp->prev = NULL;
    temp->next = l->head;
    l->head->prev = temp;
    l->head = temp;
    l->size=l->size+1;
    return l;
}
LinkedList *AddTail(LinkedList *l, bool x){
    Node *temp = new Node;
    temp->data = x;
    temp->next = NULL;
    temp->prev = l->tail;
    l->tail->next = temp;
    l->tail = temp;
    l->size=l->size+1;
    return l;
}
LinkedList *AddAt(LinkedList *l, int k, bool x){
    Node *p = l->head;
    for (int i = 0; i < k-1; i++){
        p = p->next;
    }
    Node *temp = new Node;
    temp->data = x;
    temp->prev = p;
    temp->next = p->next;
    p->next->prev = temp;
    p->next = temp;
    l->size=l->size+1;
    return l;
}
 
void DeleteAtHead(LinkedList *l) {
    if(l->head == NULL) {
        return;
    }
    l->head = l->head->next;
    l->head->prev = NULL;
    l->size=l->size-1;
}

void DeleteAtTail(LinkedList *l) {
    if(l->head == NULL) {
        return;
    }
    l->tail = l->tail->prev;
    l->tail->next = NULL;
    l->size=l->size-1;
}

//Prints all the elements in linked list in forward traversal order
void PrintList(LinkedList *l) {
    Node* temp = l->head;
    printf("Size: %d\n", l->size);
    while(temp != NULL) {
        printf("%d",temp->data);
        temp = temp->next;
    }
    printf("\n");
}
 
//Prints all elements in linked list in reverse traversal order.
void PrintListReverse(LinkedList *l) {
    Node* temp = l->tail;
    if(temp == NULL) return; // empty list, exit
    printf("\nReverse: ");
    while(temp != NULL) {
        printf("%d",temp->data);
        temp = temp->prev;
    }
    printf("\n");
}
