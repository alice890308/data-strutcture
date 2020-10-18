/*
infix expression to pre and postfix expression,
using stack and queue.
*/

#include <iostream>
#include <string>

using namespace std;

void infix_postfix(string str);
char* infix_pre(string str);
long long int calculate();

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
    int is_empty;
    char *s;
    int top_pos;
};

my_stack::my_stack()
{
    s = new char[2];
    fill(s, s+2, '\0');
    capacity = 2;
    top_pos = 0;
    is_empty = 1;
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
    is_empty = 0;
}

char my_stack::pop()
{
    char ans;

    if (is_empty == 1)
        return '\0';
    else
    {
        ans = s[top_pos];
        if (top_pos != 0)
            top_pos -= 1;
        else
            is_empty = 1;
    }

    return ans;
}

char my_stack::top()
{
    if (is_empty == 1)
        return '\0';
    else
        return s[top_pos];
}

char* pre;
int cal_pos;

int main()
{
    string str;
    long long int ans;

    while (cin >> str)
    {
        infix_postfix(str);
        pre = infix_pre(str);
        for(int i = 0; pre[i] != '\0'; i++)
            cout << pre[i];
        cout << '\n';
        cal_pos = 0;
        ans = calculate();
        cout << ans << '\n';
    }
}

void infix_postfix(string str)
{
    my_stack stk;
    char c;

    for(int i = 0; i < str.length(); i++)
    {
        /*數字直接印出來*/
        if (str[i] >= '0' && str[i] <= '9')
        {
            cout << str[i];
        }
        /*其他運算符*/
        else
        {
            if (str[i] == ')')
            {
                c = stk.top();
                while (c != '(')
                {
                    c = stk.pop();
                    cout << c;
                    c = stk.top();
                }
                stk.pop();
            }
            /*要insert時發現stack裡面有東西，要把level >= + | -
            的東西先pop掉*/
            else if (str[i] == '+' || str[i] == '-')
            {
                c = stk.top();
                while (c != '(' && c != '\0')
                {
                    c = stk.pop();
                    cout << c;
                    c = stk.top();
                }
                stk.insert(str[i]);
            }
            else if (str[i] == '*' || str[i] == '/')
            {
                c = stk.top();
                while (c == '*' || c == '/')
                {
                    c = stk.pop();
                    cout << c;
                    c = stk.top();
                }
                stk.insert(str[i]);
            }
            /*str[i]是上引號*/
            else
            {
                stk.insert(str[i]);
            }
        }
    }
    c = stk.top();
    while(c != '\0')
    {
        c = stk.pop();
        if (c != '\0')
            cout << c;
    }
    cout << '\n';
}

char* infix_pre(string str)
{
    int len = str.length();
    int pos = 0;
    char* ans = new char[len + 1];
    char* r_ans = new char[len+1];
    my_stack stk;
    char c;

    for(len = len - 1; len >= 0; len--)
    {
        /*number*/
        if (str[len] >= '0' && str[len] <= '9')
        {
            ans[pos++] = str[len];
        }
        /*operand*/
        else
        {
            if (str[len] == '(')
            {
                c = stk.top();
                while (c != ')')
                {
                    c = stk.pop();
                    ans[pos++] = c;
                    c = stk.top();
                }
                stk.pop();
            }
    /*要insert時發現stack裡面有東西，要把level > + | -的東西先pop掉*/
            else if (str[len] == '+' || str[len] == '-')
            {
                c = stk.top();
                while (c == '*' || c == '/')
                {
                    c = stk.pop();
                    ans[pos++] = c;
                    c = stk.top();
                }
                stk.insert(str[len]);
            }
            else 
            {
                stk.insert(str[len]);
            }
        }    
    }
    c = stk.pop();
    while (c != '\0')
    {
        ans[pos++] = c;
        c = stk.pop();
    }

    pos = pos - 1;
    int i;
    for(i = 0; pos >= 0; i++, pos--)
    {
        r_ans[i] = ans[pos];
    }
    r_ans[i] = '\0';
    return r_ans;
}

long long int calculate()
{
    if (pre[cal_pos] >= '0' && pre[cal_pos] <= '9')
    {
        char c = pre[cal_pos];
        cal_pos++;
        return (c - '0');
    }
    
    if (pre[cal_pos] == '+')
    {
        cal_pos++;
        return (calculate() + calculate());
    }
        
    else if (pre[cal_pos] == '-')
    {
        cal_pos++;
        return (calculate() - calculate());
    }
    else if (pre[cal_pos] == '*')
    {
        cal_pos++;
        return (calculate() * calculate());
    }
    else if (pre[cal_pos] == '/')
    {
        cal_pos++;
        return (calculate() / calculate());
    }
    return 0;
}