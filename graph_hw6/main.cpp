#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int dist[105][105];
int all_edge[105][105];
int all_rank[105][105];
int n;

void init();
bool Floyed_warshall();
void Ranking();
pair<pair<int, int>, pair<double, pair<double, double>>> Find_ecc();
double SOSPD(int v1, int v2, double from_v1, double from_v2);

int main()
{
    string cmd;
    init();
    cin >> n;
    while(cin >> cmd)
    {
        if (cmd == "Add")
        {
            int v1, v2, weight;
            cin >> v1 >> v2 >> weight;
            all_edge[v1][v2] = weight;
            all_edge[v2][v1] = weight;
        }
        else if(cmd == "Delete")
        {
            int v1, v2;
            cin >> v1 >> v2;
            all_edge[v1][v2] = -1;
            all_edge[v2][v1] = -1;
        }
        else if(cmd == "AC")
        {
            if (n == 1)
            {
                cout << "0\n";
                continue;
            }
            bool connected = Floyed_warshall();
            if (connected == false)
            {
                cout << "Not connected graph\n";
                continue;
            }
            Ranking();
            // ((v1, v2), (ecc, (from_v1, from_v2)))
            pair<pair<int, int>, pair<double, pair<double, double>>> ecc = Find_ecc();
            if (ecc.first.second == -1)
                cout << ecc.first.first << '\n';
            else
                cout << ecc.first.first << ' ' << ecc.first.second << '\n';
        }
        else if (cmd == "Diameter")
        {
            if (n == 1)
            {
                cout << "0\n";
                continue;
            }
            bool connected = Floyed_warshall();
            if (connected == false)
            {
                cout << "Not connected graph\n";
                continue;
            }
            Ranking();
            // ((v1, v2), (ecc, (from_v1, from_v2)))
            pair<pair<int, int>, pair<double, pair<double, double>>> ecc = Find_ecc();
            cout << 2 * ecc.second.first << '\n';
        }
        else if (cmd == "SOSPD")
        {
            if (n == 1)
            {
                cout << "0\n";
                continue;
            }
            bool connected = Floyed_warshall();
            if (connected == false)
            {
                cout << "Not connected graph\n";
                continue;
            }
            Ranking();
            // ((v1, v2), (ecc, (from_v1, from_v2)))
            pair<pair<int, int>, pair<double, pair<double, double>>> ecc = Find_ecc();
            double sum = SOSPD(ecc.first.first, ecc.first.second, ecc.second.second.first, ecc.second.second.second);
            cout << sum << '\n';
        }
    }
    return 0;
}

void init()
{
    for(int i = 0; i < 105; i++)
    {
        for(int j = 0; j < 105; j++)
        {
            all_edge[i][j] = -1;
        }
    }
}

bool Floyed_warshall()
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = all_edge[i][j];
        }
    }

    for(int k = 0; k < n; k++)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if (dist[i][k] < 0 || dist[k][j] < 0)
                    continue;
                if (dist[i][j] == -1 || dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if (dist[i][j] == -1)
                return false;
        }
    }
    return true;
}

void Ranking()
{
    /*rank init*/
    for(int i = 0; i < 105; i++)
    {
        for(int j = 0; j < 105; j++)
        {
            all_rank[i][j] = j;
        }
    }

    /*sorting*/
    for(int i = 0; i < n; i++) // i_th vertex
    {
        for(int j = 1; j < n; j++) // 排第幾個vertex
        {
            int k = j;
            all_rank[i][j] = j;
            while(k-1 >= 0 && dist[i][all_rank[i][k-1]] < dist[i][all_rank[i][k]])
            {
                int temp = all_rank[i][k];
                all_rank[i][k] = all_rank[i][k-1];
                all_rank[i][k-1] = temp;
                k--;
            }
        }
    }
}

pair<pair<int, int>, pair<double, pair<double, double>>> Find_ecc()
{
    int r_v1 = -1;//return v1
    int r_v2 = -1;//return v2
    double ecc = -1;
    double from_v1 = -1;
    double from_v2 = -1;
    for(int i = 0; i < n-1; i++) // v1
    {
        for(int j = i+1; j < n; j++) // v2
        {
            /*判斷i, j兩個端點是不是ecc*/
            if (ecc == -1 || dist[i][all_rank[i][0]] < ecc)
            {
                ecc = double(dist[i][all_rank[i][0]]);
                r_v1 = i;
                r_v2 = -1;
                from_v1 = -1;
                from_v2 = -1;
            }
            if (ecc == -1 || dist[j][all_rank[j][0]] < ecc)
            {
                ecc = double(dist[j][all_rank[j][0]]);
                r_v1 = j;
                r_v2 = -1;
                from_v1 = -1;
                from_v2 = -1;
            }
            /*判斷i, j邊上的位子*/
            if (all_edge[i][j] != -1) //判斷v1, v2之間有沒有edge
            {
                for(int a = 0, b = 1; b < n; b++)
                {
                    if(dist[j][all_rank[i][b]] > dist[j][all_rank[i][a]])
                    {
                        double temp = double((dist[i][all_rank[i][b]] + dist[j][all_rank[i][a]] + all_edge[i][j])) / 2;
                        if (ecc == -1 || temp < ecc)
                        {
                            ecc = temp;
                            r_v1 = i;
                            r_v2 = j;
                            from_v1 = ecc-dist[i][all_rank[i][b]];
                            from_v2 = all_edge[i][j] - from_v1;
                        }
                        a = b;
                    }
                }
            }
        }
    }
    return make_pair(make_pair(r_v1, r_v2), make_pair(ecc, make_pair(from_v1, from_v2)));
}

double SOSPD(int v1, int v2, double from_v1, double from_v2)
{
    int node_num;
    int cur;
    double shortest[105];
    bool valid[105];
    for(int i = 0; i < 105; i++)
        valid[i] = true;
    for(int i = 0; i < 105; i++)
        shortest[i] = -1;
    if (v2 == -1) // absolute center on vertex
    {
        double ans = 0;
        for(int i = 0; i < n; i++)
        {
            ans += dist[v1][i];
        }
        return ans;
    }
    else{ //absolute center on edge
        node_num = n+1;
        cur = n;
        shortest[cur] = 0;
        shortest[v1] = from_v1;
        shortest[v2] = from_v2;
        valid[n] = false;
    }
    while(1){
        double cur_weight = -1;
        /*找出現在要繼續搜的點*/
        for(int i = 0; i < node_num; i++)
        {
            if (shortest[i] == -1) //要當下一個cur的點，不可以是無限大(-1)
                continue;
            if (valid[i] == true && (cur_weight == -1 || shortest[i] < cur_weight))
            {
                cur = i;
                cur_weight = shortest[cur];
            }
        }
        valid[cur] = false;
        /*check all false*/
        int flag = 0;
        for(int i = 0; i < node_num; i++)
        {
            if(valid[i] == true)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            break;

        /*compare and update*/
        for(int i = 0; i < n; i++)
        {
            //cout << all_edge[cur][i] << ' ';
            if(all_edge[cur][i] != -1 && (shortest[i] == -1 || shortest[cur] + all_edge[cur][i] < shortest[i]))
            {
                //cout << "in compare and update, cur = " << cur << " i = " << i << '\n';
                shortest[i] = shortest[cur] + all_edge[cur][i];
            }
        }
    }

    /*calculate sum*/
    double sum = 0;
    for(int i = 0; i < node_num; i++)
    {
        sum += shortest[i];
    }
    return sum;
}