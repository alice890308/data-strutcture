#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <string>
#include <iostream>
#include <cstdio>
using namespace std;

class Node
{
public:
    Node(){
        this->next = NULL;
    }
    Node(const int element , Node *next){
        this->data = element;
        this->next = next;
    }
    ~Node(){
        this->next = NULL;
    }

    friend class Chain;
    Node *next;
    int data;
};


class Chain
{
public:

    Chain(){
        head = NULL;
        total = 0;
    }
    Chain(Node *head){
        this->head = head;
        total = 0;
    }
    void InsertBack(int data);
    void InsertFront(int data);
    void InsertAfter(int data,int data_ref);
    void InsertBefore(int data,int data_ref);
    void Delete(int data);
    void DeleteFront();
    void DeleteBack();
    void Reverse();
    void Rotate(int k);
    void Swap(int k, int j);
    bool IsEmpty();//
    string PrintChain();//

    Node *head;
    int total;
};

#endif