#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstring>

using namespace std;

typedef struct Node
{
    Node *next;
    int value;
}node;

int main()
{
    string cmd;

    node *head;
    int num;
    int ref;
    int total = 0;

    while (cin >> cmd)
    {
        if (cmd == "InsertBack")
        {
            cin >> num;
            if (head == NULL)
            {
                head = new node();
                head->value = num;
                head->next = nullptr;
            }
            else
            {
                node *cur = head;
                for (; cur->next!=nullptr; cur = cur->next);

                node *tmp = new node();
                tmp->value = num;
                tmp->next = nullptr;
                cur->next = tmp;
            }
            total++;
        }
        else if (cmd == "InsertFront")
        {
            cin >> num;
            if (head == NULL)
            {
                head = new node();
                head->value = num;
                head->next = nullptr;
            }
            else
            {
                node *tmp = new node();
                tmp->value = num;
                tmp->next = head;
                head = tmp;
            }
            total++;
        }
        else if (cmd == "InsertAfter")
        {
            cin >> num >> ref;

            if (head == nullptr) continue;

            node *cur = head;
            for (; cur != NULL && cur->value != ref; cur = cur->next);
            
            if (cur != NULL)
            {
                node *tmp;
                tmp = new node();
                tmp->value = num;
                tmp->next = cur->next;
                cur->next = tmp;
            }
            total++;
        }
        else if (cmd == "InsertBefore")
        {
            cin >> num >> ref;

            if (head == nullptr) continue;

            node *cur = head;
            if (cur->value == ref)
            {
                node *tmp = new node();
                tmp->value = num;
                tmp->next = head;
                head = tmp;
            }
            else
            {
                for (; cur->next != nullptr && cur->next->value != ref; cur = cur->next);

                if (cur->next != nullptr)
                {
                    node *tmp = new node();
                    tmp->value = num;
                    tmp->next = cur->next;
                    cur->next = tmp;
                }
            }
            total++;
        }
        else if (cmd == "Delete")
        {
            cin >> num;
            node *cur = head;
            node *tmp;
            
            if (head == nullptr) continue;

            if (cur->value == num)
            {
                head = head->next;
                delete cur;
            }
            else
            {
                while (cur != nullptr && cur->value != num)
                {
                    tmp = cur;
                    cur = cur->next;
                }
                if (cur != nullptr)
                {
                    tmp->next = cur->next;
                    delete cur;
                }
            }
            total--;
        }
        else if (cmd == "DeleteFront")
        {
            if (head == nullptr) continue;

            node *cur = head;
            head = head->next;
            delete cur;
            total--;
        }
        else if (cmd == "DeleteBack")
        {
            if (head == nullptr) continue;

            node *cur = head;
            node *tmp;

            if (head->next == nullptr)
            {
                head = nullptr;
                delete cur;
                continue;
            }

            while (cur != nullptr && cur->value != num)
            {
                tmp = cur;
                cur = cur->next;
            }
            if (cur != nullptr)
            {
                tmp->next = nullptr;
                delete cur;
            }
            total--;
        }
        else if (cmd == "Reverse")
        {
            node *cur = head;
            node *prev = nullptr;
            node *next = head->next;

            if (head == nullptr) continue;

            while (next != nullptr)
            {
                cur->next = prev;
                prev = cur;
                cur = next;
                next = next->next;
            }
            cur->next = prev;
            head = cur;
        }
        else if (cmd == "Rotate") //have some problem
        {

            cin >> num;

            if (head == nullptr) continue;


            if (total == num) continue;
            else if (total > num)
            {
                node *cur = head;
                node *tmp;
                node *last;
                for (int i = 0; i < total - num; i++)
                {
                    tmp = cur;
                    cur = cur->next;
                    last = cur;
                }

                for (;last->next != nullptr; last = last->next);

                last->next = head;
                head = cur;
                tmp->next = nullptr;
            }
            else 
            {
                num = num % total;
                node *cur = head;
                node *tmp;
                node *last;

                for (int i = 0; i < total - num; i++)
                {
                    tmp = cur;
                    cur = cur->next;
                }
                for (;last->next != nullptr; last = last->next);

                last->next = head;
                head = cur;
                tmp->next = nullptr;
            }
        }
        else if (cmd == "Swap")
        {
            cin >> num >> ref;

            if (num == ref || head == nullptr) continue;

            node *left = nullptr;
            node *right = nullptr;
            node *cur = head;
            for (; cur!=nullptr; cur = cur->next)
            {
                if (cur->value == num) left = cur;
                else if (cur->value == ref) right = cur;
            }
            int tmp = left->value;
            left->value = right->value;
            right->value = tmp;
        }
        else if (cmd == "PrintChain")
        {
            node *cur = head;

            if (head == nullptr)
            {
                cout << "Empty" << "\n";
                continue;
            }

            if (cur != NULL)
            {
                cout << cur->value;
                cur = cur->next;
                for (; cur != nullptr; cur = cur->next)
                {
                    cout << "->" << cur->value;
                }
                cout << "\n";
            }
        }
    }
}