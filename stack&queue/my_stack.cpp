#include "my_stack.h"
using namespace std;

my_stack::my_stack()
{
    s = new char[2];
    fill(s, s+2, '\0');
    capacity = 2;
    top_pos = 0;
}

my_stack::~my_stack()
{
    delete [] s;
}

void my_stack::insert(char c)
{
    if (top_pos == capacity - 1)
    {
        char *temp;
        temp = new char[2 * capacity];
        for(int i = 0; i < capacity; i++)
        {
            temp[i] = s[i];
        }
        delete [] s;
        s = temp;
        capacity = 2 * capacity;
    }
    s[top_pos + 1] = c;
    top_pos += 1;
}

char my_stack::pop()
{
    char ans = s[top_pos];

    if (top_pos != 0)
        top_pos -= 1;
    else
        s[top_pos] = '\0';
    
    return ans;
}

char my_stack::top()
{
    return s[top_pos];
}