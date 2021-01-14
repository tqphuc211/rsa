//
//  linked_list.hpp
//  my_crypto
//
//  Created by qTp on 12/22/20.
//  Copyright © 2020 qTp. All rights reserved.
//

#ifndef linked_list_hpp
#define linked_list_hpp

#include <stdio.h>
#include <iostream>
using namespace std;

#endif /* linked_list_hpp */

struct Node  {
    bool data;
    Node* next;
    Node* prev;
};

struct LinkedList{
    Node *head;
    Node *tail;
    int size;
};

LinkedList *CreateList(bool x);
LinkedList *CreateList(string s);
LinkedList *CloneList(LinkedList *l);
LinkedList *AddHead(LinkedList *l, bool x);
LinkedList *AddTail(LinkedList *l, bool x);
LinkedList *AddAt(LinkedList *l, int k, bool x);
void DeleteAtHead(LinkedList *l);
void DeleteAtTail(LinkedList *l);
void PrintList(LinkedList *l);


