#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <stack>
#include <algorithm>
#include <cmath>

using namespace std;

struct node
{
    int weight = -1;
    double rate = -1;
    int campus = -1;
};

struct edge
{
    int v1 = -1;
    int v2 = -1;
    int weight = -1;
    double rate = 0;
    int used = 0;
};

vector<vector<node>> each_path;
vector<edge> each_edge;
int boss[2000]; // 每個node的boss是誰
int each_n[2000]; // 如果這個node是boss，那跟他在同一個set的node數
int t;
int v2_max_cre;
int used[1010][1010];
vector<int> max_cre2;

void init(int n);
void init_for_map();
void add(int v1, int v2, int weight,    double rate);
void shortest(int v1, int v2, int n);
void deleting(int v1, int v2);
void map(int n);
int find_boss(int a);
bool comparing_weight(edge e1, edge e2);
bool comparing_rate(edge e1, edge e2);
void importantBus(int n);
void importantBus_temp(int n);
void cre_ex(int v1, int v2, int credit, int n);
void cre_ex2(int v1, int v2, int credit, int limit, int num);

int main()
{
    int n;
    int v1, v2;
    int weight;
    double rate;
    int credit;
    int limit;
    string cmd;
    cin >> n;
    init(n); // init checked!
    
    while (cin >> cmd)
    {
        if (cmd == "Add")
        {
            cin >> v1 >> v2 >> weight >> rate;
            add(v1, v2, weight, rate);
        }
        else if (cmd == "Delete")
        {
            cin >> v1 >> v2;
            deleting(v1, v2);
        }
        else if (cmd == "Shortest")
        {
            cin >> v1 >> v2;
            shortest(v1, v2, n);
        }
        else if (cmd == "Map")
            map(n);
        else if (cmd == "ImportantBus")
            importantBus_temp(n);
        else if (cmd == "CreditExchange")
        {
            cin >> v1 >> v2 >> credit;
            cre_ex(v1, v2, credit, n);
        }
        else if (cmd == "CreditExchange2")
        {
            cin >> v1 >> v2 >> credit >> limit;
            v2_max_cre = 0;
            max_cre2[v1] = credit;
            cre_ex2(v1, v2, credit, limit, n);
            cout << v2_max_cre << '\n';
        }

        /* for debug */
        //for(auto v : each_path)
        //{
        //    for(auto n : v)
        //        cout << n.rate << ' ' << n.weight << " " << n.campus << " -> ";
        //    cout << '\n';
        //}
        //cout << '\n';
    //
        //for(auto e : each_edge)
        //{
        //    cout << e.v1 << ' ' << e.v2 << ' ' << e.weight << "-> ";
        //}
        //cout << '\n';
    }
}

void init(int n)
{
    for(int i = 0; i < n; i++)
    {
        vector<node> temp;
        each_path.push_back(temp);
        max_cre2.push_back(0);
    }
}

void add(int v1, int v2, int weight,    double rate)
{
    /* only update each_path. shortest_path update only when calling shortest function! */
    node temp;
    int flag = 0;

    /* add new path */
    temp.campus = v2;
    temp.rate = rate;
    temp.weight = weight;
    each_path[v1].push_back(temp);

    temp.campus = v1;
    each_path[v2].push_back(temp);

    /* add new edge*/
    ///* check if the edge is already exist, if so, update it */
    //for(auto iter = each_edge.begin(); iter != each_edge.end(); iter++)
    //{
    //    if ((v1 == iter->v1 && v2 == iter->v2) || (v1 == iter->v2 && v2 == iter->v1))
    //    {
    //        iter->weight = weight;
    //        flag = 1;
    //        break;
    //    }
    //}

    /* if not, add a new one */
    edge e_temp;
    e_temp.v1 = v1;
    e_temp.v2 = v2;
    e_temp.weight = weight;
    e_temp.rate = rate;
    each_edge.push_back(e_temp);
}

void deleting(int v1, int v2)
{
    /* deleting path */
    for (auto iter = each_path[v1].begin(); iter != each_path[v1].end(); iter++)
    {
        if (iter->campus == v2)
        {
            each_path[v1].erase(iter);
            break;
        }  
    }

    for (auto iter = each_path[v2].begin(); iter != each_path[v2].end(); iter++)
    {
        if (iter->campus == v1)
        {
            each_path[v2].erase(iter);
            break;
        }  
    }

    /* deleting edge */
    for (auto iter = each_edge.begin(); iter != each_edge.end(); iter++)
    {
        if ((iter->v1 == v1 && iter->v2 == v2) || (iter->v1 == v2 && iter->v2 == v1))
        {
            each_edge.erase(iter);
            break;
        }
    }
}

void shortest(int v1, int v2, int n)
{
    vector<int> shortest_path; // record the distance of start point to each node.
    set<int> visited;
    int now_searching;

    /* initial */
    for(int i = 0; i < n; i++)
    {
        if (i == v1)
            shortest_path.push_back(0);
        else
            shortest_path.push_back(2147483647);
    }

    for(int time = 0; time < n-1; time++)
    {
        
        /* for debug*/
        //for(auto n : visited)
        //{
        //    cout << n << " ";
        //}
        //cout << '\n';

        //cout << "now_searching = " << now_searching << '\n';
        //for(auto v : shortest_path)
        //{
        //    cout << v << ' ';
        //}
        //cout << '\n';

        /* find next "now_searching" */
        pair<int, int> min = make_pair(-1, 2147483647);
        for(int i = 0; i < n; i++)
        {
            auto iter = visited.find(i);
            if (iter == visited.end())
            {
                if (shortest_path[i] < min.second)
                {
                    min = make_pair(i, shortest_path[i]);
                }
            }
        }
        now_searching = min.first;

        /* update shortest_path */
        visited.insert(now_searching);
        for(auto v : each_path[now_searching])
        {
            if (shortest_path[v.campus] > v.weight + shortest_path[now_searching])
                shortest_path[v.campus] = v.weight + shortest_path[now_searching];
        }
    }

    if (shortest_path[v2] == 2147483647)
        cout << "Error\n";
    else
        cout << shortest_path[v2] << '\n';
}

void init_for_map()
{
    t = 1010;
    for(int i = 0; i < 2000; i++)
    {
        boss[i] = i;
        each_n[i] = 1;
    }
}

int find_boss(int a)
{
    if (boss[a] == a)
        return a;
    return boss[a] = find_boss(boss[a]);
}

void map(int n)
{
    int count = 0;
    int min_dist = 0;

    /* initial */
    sort(each_edge.begin(), each_edge.end(), comparing_weight);
    init_for_map();

    for(auto e : each_edge)
    { 
        int boss_1 = find_boss(e.v1);
        int boss_2 = find_boss(e.v2);
        if (boss_1 != boss_2)
        {
            min_dist += e.weight;
            boss[boss_1] = boss_2;
            each_n[boss_2] += each_n[boss_1];
            each_n[boss_1] = 0;
        }

        /* for debug */
        //cout << "node_num\n";
        //for (int i = 0; i < n; i++)
        //{
        //    cout << "i = " << i << ", node_num = " << each_n[i] << '\n';
        //}
        //cout << '\n';
    }
    
    for(int i = 0; i < n; i++)
    {
        if (each_n[i] != 0)
            count++;
    }

    if (count > 1)
        cout << "Error\n";
    else
        cout << min_dist << '\n';
}

bool comparing_weight(edge e1, edge e2)
{
    return (e1.weight < e2.weight);
}

bool comparing_rate(edge e1, edge e2)
{
    return (e1.rate > e2.rate);
}

void importantBus(int n)
{
    int edge_num = each_edge.size();
    int flag = 0;

    for(int i = 0; i < edge_num; i++)
    {
        set<int> connected;
        stack<int> searching;
        int no_v1 = each_edge[i].v1;
        int no_v2 = each_edge[i].v2;
        
        /* insert first node */
        if (i == 0)
        {
            connected.insert(each_edge[1].v1);
            searching.push(each_edge[1].v1);
        } 
        else
        {
            connected.insert(each_edge[0].v1);
            searching.push(each_edge[0].v1);
        }
        
        /* brutal searching */
        while (!searching.empty())
        {
            int top = searching.top();
            searching.pop();
            for (auto v : each_path[top])
            {
                /* make sure the edge can use */
                if ((top == no_v1 && v.campus == no_v2) || (top == no_v2 && v.campus == no_v1))
                    continue;
                
                /* if the connected edge hasn't been found, add to connected and searching.*/
                auto temp = connected.find(v.campus);
                if (temp == connected.end())
                {
                    connected.insert(v.campus);
                    searching.push(v.campus);
                }
            }
        }
        if (connected.size() != n)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 1)
        cout << "Yes\n";
    else
        cout << "No\n";
}

void cre_ex(int v1, int v2, int credit , int n)
{
    vector<int> max_credit; // record the max credit of start point to each node.
    set<int> visited;
    int now_searching;

    /* initial */
    sort(each_edge.begin(), each_edge.end(), comparing_rate);
    for(int i = 0; i < n; i++)
    {
        if (i == v1)
            max_credit.push_back(credit);
        else
            max_credit.push_back(0);
    }

    now_searching = v1;
    for(int time = 0; time < n-1; time++)
    {
        /* for debug */
        //cout << "visited: \n";
        //for(auto n : visited)
        //{
        //    cout << n << " ";
        //}
        //cout << '\n';
        //cout << "now_searching = " << now_searching << '\n';
        //for(auto v : max_credit)
        //{
        //    cout << v << ' ';
        //}
        //cout << '\n';
        
        /* find next "now_searching" */
        pair<int, int> max = make_pair(-1, 0);
        for(int i = 0; i < n; i++)
        {
            auto iter = visited.find(i);
            if (iter == visited.end())
            {
                if (max_credit[i] > max.second)
                {
                    max = make_pair(i, max_credit[i]);
                }
            }
        }
        now_searching = max.first;

        /* update max_credit*/
        visited.insert(now_searching);
        for(auto v : each_path[now_searching])
        {
            int temp = int(floor(max_credit[now_searching] * v.rate));
            if (max_credit[v.campus] < temp)
                max_credit[v.campus] = temp;
        }
    }

    cout << max_credit[v2] << '\n';
}

void importantBus_temp(int n)
{
    int flag = 0;
    for (auto v : each_path)
    {
        if (v.size() == 1)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 1)
        cout << "Yes\n";
    else
        cout << "No\n";
}

void cre_ex2(int v1, int v2, int credit, int limit, int num)
{
    if (limit == 0)
    {
        if (v1 != v2)
        {
            max_cre2[v1] = 0;
            return;
        }
            
        else
        {
            if (credit > v2_max_cre)
                v2_max_cre = credit;
            max_cre2[v1] = 0;
            return;
        }
    }

    for(auto n : each_path[v1])
    {
        if (used[v1][n.campus] == 0)
        {
            int cur_credit = credit * n.rate;
            if (cur_credit > max_cre2[n.campus])
            {
                used[v1][n.campus] = 1;
                used[n.campus][v1] = 1;
                if (n.campus == v2 && cur_credit > v2_max_cre)
                    v2_max_cre = cur_credit;
                max_cre2[n.campus] = cur_credit;
                cre_ex2(n.campus, v2, cur_credit, limit-1, num-1);
                used[v1][n.campus] = 0;
                used[n.campus][v1] = 0;
            }
        }
    }
    max_cre2[v1] = 0;
}