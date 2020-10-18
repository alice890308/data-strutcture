#include <iostream>
#include <string>

using namespace std;

class node
{
public:
    node(){data = 0; level = 0; index = 0; left = NULL; right = NULL;}
    ~node(){left = NULL; right = NULL;}

    int data;
    int level;
    int index;
    node* left;
    node* right;
};

class my_stack
{
public:
    my_stack();
    ~my_stack();
    void push(node *c);
    bool empty();
    void pop();
    node* top();

private:
    int capacity;
    node **s;
    int top_pos;
};

my_stack::my_stack()
{
    s = new node*[2];
    s[0] = NULL;
    s[1] = NULL;
    capacity = 2;
    top_pos = 0;
}

my_stack::~my_stack()
{
    delete [] s;
}

bool my_stack::empty()
{
    if (top_pos == 0 && s[0] == NULL)
        return true;
    else
        return false;
}

void my_stack::push(node *c)
{
    if (top_pos == capacity - 1)
    {
        node **temp;
        temp = new node*[2 * capacity];
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

void my_stack::pop()
{
    node *ans = s[top_pos];

    if (top_pos != 0)
        top_pos -= 1;
    else
        s[top_pos] = NULL;
}

node* my_stack::top()
{
    return s[top_pos];
}

node* create_tree(string in);
void pre_order(node *root);
void in_order(node *root);
void post_order(node *root);
void fodable(node *root);
pair<long long int, long long int> QQ(node *root);
void delete_all_leaves(node *root);
void delete_tree(node *root);

int height;
int total;
int m;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    string in;
    node *root;
    pair<long long int, long long int> qwq;
    while (cin >> in)
    {
        height = 0;
        total = 0;
        m = 0;
        root = create_tree(in);
        pre_order(root);
        in_order(root);
        post_order(root);
        cout << "\n";

        cout << height << "\n";

        if (m == total)
            cout << "Complete\n";
        else
            cout << "Not complete\n";

        if (root == NULL || total == 1)
            cout << "Foldable\n";
        else
            fodable(root);
        
        qwq = QQ(root);
        cout << max(qwq.first, qwq.second) << '\n';

        if (root != NULL && root->right == NULL && root->left == NULL)
        {
            delete root;
            root = NULL;
        }
        else
            delete_all_leaves(root);

        pre_order(root);
        in_order(root);
        post_order(root);
        cout << "\n";
        delete_tree(root);
    }
}

node* create_tree(string in)
{
    my_stack no;
    int temp_data;
    int i = 1;
    int n_flag = 0;
    node *head, *cur;

    if (in[0] == '(' && in[1] == ')')
        return NULL;

    /* create root node*/
    temp_data = 0;
    if (in[i] == '-')// handle negative number
    {
        n_flag = 1;
        i++;
    }
    while(in[i] <= '9' && in[i] >= '0')
    {
        temp_data *= 10;
        temp_data += in[i] - '0';
        i++;
    }
    if (n_flag == 1)
    {
        temp_data = -temp_data;
        n_flag = 0;
    }
    head = new node();
    total++;
    head->data = temp_data;
    head->index = 1;
    head->level = 1;
    no.push(head);
    cur = head;

    /* construct tree */
    while(!no.empty())
    {
        while (1)
        {
            /* find node numbers */
            while(in[i] != '(')
                i++;
            i++;
            /*create a NULL node*/
            if (in[i] == ')')
                break;

            /*construct left tree,
                push every encounter node into the no*/
            else
            {
                /*parse the node_data*/
                temp_data = 0;
                if (in[i] == '-')// handle negative number
                {
                    n_flag = 1;
                    i++;
                }
                while(in[i] <= '9' && in[i] >= '0')
                {
                    temp_data *= 10;
                    temp_data += in[i] - '0';
                    i++;
                }
                if (n_flag == 1)
                {
                    temp_data = -temp_data;
                    n_flag = 0;
                }
                cur->left = new node();
                total++;
                cur->left->index = cur->index * 2;
                cur->left->data = temp_data;
                cur->left->level = cur->level + 1;
                cur = cur->left;
                no.push(cur);
            }
        }
        /* create the right node */
        cur = no.top();
        no.pop();
        if (cur->level > height)
            height = cur->level;
        if (cur->index > m)
            m = cur->index;
        while (1)
        {
            while (in[i] != '(')
                i++;
            i++;
            if (in[i] == ')')
            {
                if (no.empty())
                    break;
                cur = no.top();
                no.pop();
            }
            else
            {
                /*parse the node_data*/
                if (in[i] == '-')// handle negative number
                {
                    n_flag = 1;
                    i++;
                }
                temp_data = 0;
                while(in[i] <= '9' && in[i] >= '0')
                {
                    temp_data *= 10;
                    temp_data += in[i] - '0';
                    i++;
                }
                if (n_flag == 1)
                {
                    temp_data = -temp_data;
                    n_flag = 0;
                }
                cur->right = new node();
                total++;
                cur->right->index = cur->index * 2 + 1;
                cur->right->data = temp_data;
                cur->right->level = cur->level + 1;
                cur = cur->right;
                no.push(cur);
                break;
            }
        }
    }
    return head;
}

void pre_order(node *root)
{
    my_stack t;
    node *temp = root;

    if (root == NULL)
    {
        cout << "\n";
        return;
    }

    t.push(root);

    while(!t.empty())
    {
        while (temp != NULL)
        {
            cout << temp->data << " ";
            if (temp->left != NULL)
                t.push(temp->left);
            temp = temp->left;
        }
        temp = t.top();
        t.pop();
        if (temp->right != NULL)
        {
            temp = temp->right;
            t.push(temp);
        }
            
        else
            temp = NULL;
    }
    cout << '\n';
}

void in_order(node *root)
{
    my_stack t;
    node *temp = root;

    if (root == NULL)
    {
        cout << "\n";
        return;
    }

    t.push(root);

    while(!t.empty())
    {
        while (temp != NULL)
        {
            if (temp->left != NULL)
                t.push(temp->left);
            temp = temp->left;
        }
        temp = t.top();
        t.pop();
        cout << temp->data << ' ';
        if (temp->right != NULL)
        {
            temp = temp->right;
            t.push(temp);
        }
            
        else
            temp = NULL;
    }
    cout << '\n';
}

void post_order(node *root)
{
    if (root == NULL)
    {
        return;
    }

    post_order(root->left);
    post_order(root->right);
    cout << root->data << " ";
}

void fodable(node *root)
{
    my_stack r, l;
    node *r_temp = root->right;
    node *l_temp = root->left;
    int flag = 0;

    if (root->left == NULL || root->right == NULL)
    {
        cout << "Not foldable\n";
        return;
    }
    
    r.push(root->right);
    l.push(root->left);

    while (!r.empty() && !l.empty())
    {
        while (r_temp != NULL && l_temp != NULL)
        {
            if (l_temp->left != NULL && r_temp->right != NULL)
            {
                l.push(l_temp->left);
                r.push(r_temp->right);
            }
            else if(l_temp->left == NULL && r_temp->right == NULL);
            else
            {
                flag = 1;
                cout << "Not foldable\n";
                return;
            }
            l_temp = l_temp->left;
            r_temp = r_temp->right;
        }
        r_temp = r.top();
        r.pop();
        l_temp = l.top();
        l.pop();
        if (r_temp->left != NULL && l_temp->right != NULL)
        {
            l_temp = l_temp->right;
            r_temp = r_temp->left;
            l.push(l_temp);
            r.push(r_temp);
        }
        else if(r_temp->left == NULL && l_temp->right == NULL)
        {
            r_temp = NULL;
            l_temp = NULL;
        }
        else
        {
            cout << "Not foldable\n";
            return;
        }
    }
    cout << "Foldable\n";
}

pair<long long int, long long int> QQ(node *root)
{
    if (root == NULL)
        return make_pair(0, 0);
    
    /* first -> me_in, second -> me_out*/
    pair<long long int, long long int> me, l_child, r_child;

    l_child = QQ(root->left);
    r_child = QQ(root->right);
    me.first = l_child.second + r_child.second + root->data;
    me.second = max(l_child.first, l_child.second) + max(r_child.first, r_child.second);
    
    return me;
}

void delete_all_leaves(node *root)
{
    if (root == NULL)
        return;
    if (root->left != NULL && root->left->left == NULL && root->left->right == NULL)
    {
        delete (root->left);
        root->left = NULL;
    }
    if (root->right != NULL && root->right->left == NULL && root->right->right == NULL)
    {
        delete (root->right);
        root->right = NULL;
    }
    if(root->left != NULL)
        delete_all_leaves(root->left);
    if (root->right != NULL)
        delete_all_leaves(root->right);
}

void delete_tree(node *root)
{
    if (root == NULL)
        return;
    
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}