#include <iostream>
#include <string.h>
#include <math.h>
//#include "function.h"
using namespace std;

class BST{
public:
    BST():Height(0){}
    virtual ~BST() {}
    virtual void insert(const int &) = 0;
    virtual bool search(const int &) const = 0;
    virtual void print() const = 0;
    int height() const { return Height; }// An empty tree has height of 0. A tree with only root node has height of 1.

protected:
    int Height;
};

class Array_BST : public BST{
public:
    Array_BST();
    virtual ~Array_BST() {}
    virtual void insert(const int &num) override; //root node is stored at index 1.
    virtual bool search(const int &num) const override;
    virtual void print() const override{
        int k = pow(2, height());
        for (int i = 1; i <= k-1; i++) {
            if (array[i] != 0)
                cout << array[i] << " ";
        }
    }

private:
    int array[1025];
};

class ListNode{
    friend class List_BST; //make List_BST a friend

public:
    ListNode(const int &info):key( info ),left( NULL ),right( NULL ) //constructor
    {
    }//end ListNode constructor

private:
    int key;
    ListNode *left;
    ListNode *right;
};//end class ListNode

class List_BST : public BST{
public:
    List_BST();
    virtual ~List_BST()
    {
        deleteTree(root);
    }
    virtual void insert(const int &num) override;
    virtual bool search(const int &num) const override;
    virtual void print() const override{
        int i;
        for(i = 1; i <= Height; i++){
            printGivenLevel(root, i);
        }
    }

private:
    ListNode *root;
    // private member functions
    ListNode* createLeaf(int key) const; //new a ListNode and return its address
    /* clean a tree.*/
    void deleteTree(ListNode *root);

    void printGivenLevel(ListNode* Ptr, int level) const {
        if (Ptr == NULL)
            return;
        if (level == 1)
            cout << Ptr->key << " ";
        else if (level > 1)
        {
            printGivenLevel(Ptr->left, level-1);
            printGivenLevel(Ptr->right, level-1);
        }
    }
};

Array_BST::Array_BST()
{
    fill(array, array + 1025, 0);
    Height = 0;
}

void Array_BST::insert(const int &num)
{
    int i = 1;
    while(array[i] != 0){
        if(num == array[i]){
            return;
        }
        else if(num < array[i]){//go to the left child
            i *= 2;
        }
        else{//go to the right child
            i = i * 2 + 1;
        }
    }
    array[i] = num;
    if((floor(log2(i)) + 1) > Height){
        Height = floor(log2(i)) + 1;
    }
}

bool Array_BST::search(const int &num) const
{
    int i = 1;
    while(array[i] != 0){
        if(num == array[i]){
            return true;
        }
        else if(num < array[i]){//go to the left child
            i *= 2;
        }
        else{//go to the right child
            i = i * 2 + 1;
        }
    }
    return false;
}

List_BST::List_BST()
{
    root = NULL;
}

ListNode* List_BST::createLeaf(int key) const
{
    ListNode *temp;
    temp = new ListNode(key);
    return temp;
}

void List_BST::insert(const int &num)
{
    ListNode *temp = createLeaf(num);
    int cnt = 1;
    if(root == NULL){
        root = temp;
        Height = 1;
    }
    else{
        ListNode *p = root;
        while(p != NULL){
            cnt++;
            if(num == p->key){//if num = p->key
                return;
            }
            else if(num > p->key){//>
                if(p->right != NULL){
                    p = p->right;
                }
                else{
                    p->right = temp;
                    break;
                }
            }
            else{// <
                if(p->left != NULL){
                    p = p->left;
                }
                else{
                    p->left = temp;
                    break;
                }
            }
        }
        if(cnt > Height){
            Height = cnt;
        }
    }
}

bool List_BST::search(const int &num) const
{
    ListNode *p = root;
    while(p != NULL){
        if(num == p->key){
            return true;
        }
        else if(num < p->key){
            p = p->left;
        }
        else{
            p = p->right;
        }
    }
    return false;
}

void List_BST::deleteTree(ListNode *root)
{
    ListNode *p = root;
    if(p->left != NULL){
        deleteTree(p->left);
    }
    if(p->right != NULL){
        deleteTree(p->right);
    }
    delete p;
}

void BSTManipulator(BST& bstobj1,BST& bstobj2, char cmd ){
    int n;
    if (cmd == 'I') {
        cin >> n;
        bstobj1.insert(n);
        bstobj2.insert(n);
    }else if (cmd == 'S'){
        cin >> n;
        if (bstobj1.search(n)) {
            cout << "yes" << endl;
        }else{
            cout << "no" << endl;
        }

        if (bstobj2.search(n)) {
            cout << "yes" << endl;
        }else{
            cout << "no" << endl;
        }

    }else if (cmd == 'H'){
        cout << bstobj1.height() << endl;;
        cout << bstobj2.height() << endl;;

    }else if (cmd == 'P'){
        bstobj1.print();
        cout << endl;
        bstobj2.print();
        cout << endl;
    }
}
int main(){
    Array_BST A_bst;
    List_BST B_bst;
    char cmd;

    while (cin >> cmd)
        BSTManipulator(A_bst, B_bst, cmd);

    return 0;
}
