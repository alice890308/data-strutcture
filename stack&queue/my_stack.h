#ifndef MY_STACK_H
#define MY_STACK_H

#include <iostream>

class my_stack
{
public:
    my_stack();
    ~my_stack();
    void insert(char c);
    char pop();
    char top();

private:
    int capacity;
    char *s;
    int top_pos;
};

#endif