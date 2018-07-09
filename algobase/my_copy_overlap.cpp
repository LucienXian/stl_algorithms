#include <iostream>
#include <iterator>
#include <algorithm>
#include <deque>

using namespace std;

void print(int v[])
{
    for(int i=0;i<9;i++)
        cout << v[i] << " ";
    cout << endl;
}

int main()
{
    {
        int ia[] = {0,1,2,3,4,5,6,7,8};
        copy(ia+2, ia+7,ia);//输出区间的终点与输入区间重叠，copy正常
        print(ia); //2 3 4 5 6 5 6 7 8
    }
    {
        int ia[] = {0,1,2,3,4,5,6,7,8};
        deque<int> id(ia, ia+9);
        deque<int>::iterator first = id.begin();
        deque<int>::iterator last = id.end();
        ++++first; //advance 2
        cout << *first << endl;
        ----last; //advance -2
        cout << *last << endl;
        deque<int>::iterator res = id.begin();
        copy(first, last, res);
        copy(id.begin(), id.end(), ostream_iterator<int>(cout, " "));//2 3 4 5 6 5 6 7 8
        cout << endl;
    }
    {
        int ia[] = {0,1,2,3,4,5,6,7,8};
        deque<int> id(ia, ia+9);
        deque<int>::iterator first = id.begin();
        deque<int>::iterator last = id.end();
        ++++first; //advance 2
        cout << *first << endl;
        ----last; //advance -2
        cout << *last << endl;
        deque<int>::iterator res = id.begin();
        res = res+4;
        copy(first, last, res);
        copy(id.begin(), id.end(), ostream_iterator<int>(cout, " "));//0 1 2 3 2 3 4 5 6
        cout << endl;
    }
}