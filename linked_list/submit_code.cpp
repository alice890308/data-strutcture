#include <string>
#include <iostream>
#include <cstdio>
#include <cstring>

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

void Chain::InsertBack(int data)
{
    total += 1;
    Node* temp = new Node();
    temp->data = data;

    if (IsEmpty())
    {
        head = temp;
    }
    else
    {
        Node* test = head;
        while (test->next != NULL)
        {
            test = test->next;
        }
        test->next = temp;
    }
}

void Chain::InsertFront(int data)
{
    total += 1;
    Node *temp = new Node();
    temp->data = data;

    if (IsEmpty())
    {
        head = temp;
    }
    else
    {
        temp->next = head;
        head = temp;
    }
}

void Chain::InsertAfter(int data, int data_ref)
{
    if (IsEmpty())
    {
        return;
    }
    Node* test = head;
    while (test != NULL)
    {
        if (test->data == data_ref)
        {
            Node* temp = new Node();
            total += 1;
            temp->data = data;
            temp->next = test->next;
            test->next = temp;
            break;
        }
        test = test->next;
    }
}

void Chain::InsertBefore(int data, int data_ref)
{
    if (IsEmpty())
    {
        return;
    }
    if (head->data == data_ref)
    {
        Node* temp = new Node();
        total += 1;
        temp->data = data;
        temp->next = head;
        head = temp;
        return;
    }
    
    Node* test = head;
    while (test->next != NULL)
    {
        if (test->next->data == data_ref)
        {
            Node* temp = new Node();
            total += 1;
            temp->data = data;
            temp->next = test->next;
            test->next = temp;
            break;
        }
        test = test->next;
    }
}

void Chain::Delete(int data)
{
    if (IsEmpty())
    {
        return;
    }
    if (head->data == data)
    {
        Node* test = head->next;
        delete head;
        total -= 1;
        head = test;
        return;
    }
    
    Node* test = head;
    
    while (test->next != NULL)
    {
        if (test->next->data == data)
        {
            Node* temp = test->next->next;
            delete test->next;
            total -= 1;
            test->next = temp;
            break;
        }
        test = test->next;
    }
}

void Chain::DeleteFront()
{
    if (IsEmpty())
    {
        return;
    }
    Node* test = head->next;
    delete head;
    total -= 1;
    head = test;
}

void Chain::DeleteBack()
{
    if (IsEmpty())
    {
        return;
    }

    Node* test = head;
    while (test != NULL)
    {
        if (test->next->next == NULL)
        {
            delete test->next;
            total -= 1;
            test->next = NULL;
            break;
        }
        test = test->next;
    }
}

void Chain::Reverse()
{
    if (IsEmpty() || head->next == NULL)
    {
        return;
    }

    Node *pre, *next, *cur;
    pre = NULL;
    cur = head;

    while (cur != NULL)
    {
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    head = pre;
}

void Chain::Rotate(int k)
{
    if (k > total)
    {
        k = k % total;
    }
    if (IsEmpty() || (k == total))
    {
        return;
    }
    
    
    Node *next_tail = head, *next_head, *tail;

    for (int i = 0; i < total-k-1; i++)
    {
        next_tail = next_tail->next;
    }
    next_head = next_tail->next;
    tail = next_head;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }
    next_tail->next = NULL;
    tail->next = head;
    head = next_head;
}

void Chain::Swap(int k, int j)
{
    if (IsEmpty())
    {
        return;
    }
    Node *pk = head, *pj = head;

    while (pk != NULL)
    {
        if (pk->data == k)
            break;
        pk = pk->next;
    }
    while (pj != NULL)
    {
        if (pj->data == j)
            break;
        pj = pj->next;
    }
    if (pk == NULL || pj == NULL)
        return;
    pj->data = k;
    pk->data = j;
}

bool Chain::IsEmpty(){
    return this->head == NULL;
}

string Chain::PrintChain(){
    Node *cur = this->head;
    string result = "";
    if(cur == NULL){
        result = "Empty";
        return result;
    }
    while(cur != NULL){
        int num = cur->data;
        std::string num_str = std::to_string(num);
        result.append(num_str);
        if(cur -> next){
            result.append("->");
        }
        cur = cur->next;
    }
    return result;
}

int main()
{
    Chain inst = *(new Chain());

    string command;
    int data , data_ref;

    while(cin>>command){
        if(command == "InsertBack"){
            cin>>data;
            inst.InsertBack(data);
        }else if(command == "InsertFront"){
            cin>>data;
            inst.InsertFront(data);
        }else if(command == "InsertAfter"){
            cin>>data>>data_ref;
            inst.InsertAfter(data , data_ref);
        }else if(command == "InsertBefore"){
            cin>>data>>data_ref;
            inst.InsertBefore(data , data_ref);
        }else if(command == "Delete"){
            cin>>data;
            inst.Delete(data);
        }else if(command == "DeleteFront"){
            inst.DeleteFront();

        }else if(command == "DeleteBack"){
            inst.DeleteBack();

        }else if(command == "Reverse"){
            inst.Reverse();
        }else if(command == "Rotate"){
            int k;
            cin>>k;
            inst.Rotate(k);
        }else if(command == "Swap"){
            int j,k;
            cin>>j>>k;
            inst.Swap(j,k);
        }
        else if(command == "PrintChain"){

            cout<<inst.PrintChain()<< '\n';
        }
    }
    
    return 0;
}