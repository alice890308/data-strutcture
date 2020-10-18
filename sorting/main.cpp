#include <iostream>
#include <vector>

using namespace std;

void init();
void split(int left, int right);
void merge_sort(int left, int middle, int right);
void radix_sort(int max_num, int radix, int num);

int pairs_arr[1000005];
int radix_arr[1000005];
long long int pairs;

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
    int num, radix;
    while (cin >> num >> radix)
    {
        init();
        for(int i = 0; i < num; i++)
        {
            cin >> pairs_arr[i];
            radix_arr[i] = pairs_arr[i];
        }
        split(0, num-1);
        cout << pairs << '\n';
        radix_sort(pairs_arr[num-1], radix, num);
        /* for debug */
    }
    return 0;
}

void init()
{
    for(int i = 0; i < 1000005; i++)
    {
        pairs_arr[i] = 0;
        radix_arr[i] = 0;
    }
    pairs = 0;
}

void split(int left, int right)
{
    if (left < right)
    {
        int middle = (left + right) / 2;
        split(left, middle);
        split(middle + 1, right);
    
        merge_sort(left, middle, right);
    }
}

void merge_sort(int left, int middle, int right)
{
    int temp_left[500005];
    int temp_right[500005];
    int left_num = middle - left + 1;
    int right_num = right - middle;

    for(int i = 0; i < left_num; i++)
        temp_left[i] = pairs_arr[left+i];
    for(int i = 0; i < right_num; i++)
        temp_right[i] = pairs_arr[middle +i +1];
    
    int cur_left = 0;
    int cur_right = 0;
    int arr_pos = left;

    while(cur_left < left_num && cur_right < right_num)
    {
        if (temp_left[cur_left] > temp_right[cur_right])
        {
            pairs += (left_num - cur_left);
            pairs_arr[arr_pos++] = temp_right[cur_right++];
        }
        else
        {
            pairs_arr[arr_pos++] = temp_left[cur_left++];
        }
    }
    while(cur_left < left_num)
    {
        pairs_arr[arr_pos++] = temp_left[cur_left++];
    }
    while (cur_right < right_num)
    {
        pairs_arr[arr_pos++] = temp_right[cur_right++];
    }
}

void radix_sort(int max_num, int radix, int num)
{
    int max_level = 0;
    int temp = max_num;
    while(temp != 0)
    {
        temp /= radix;
        max_level++;
    }

    for(long long int times = 1, i = 0; i < max_level; times *= radix, i++)
    {
        /* create buckets */
        vector<vector<int> > buckets;
        for(int i = 0; i < radix; i++)
        {
            vector<int> temp;
            buckets.push_back(temp);
        }

        /* put element into bucket */
        for(int j = 0; j < num; j++)
        {
            int index = (radix_arr[j] / times) % radix;
            buckets[index].push_back(radix_arr[j]);
        }

        /* change the order of radix_arr */
        int pos = 0;
        for(auto bucket : buckets)
        {
            for(auto el : bucket)
            {
                radix_arr[pos++] = el;
            }
        }
        cout << radix_arr[0] << ' ' << radix_arr[num-1] << '\n';
    }
}