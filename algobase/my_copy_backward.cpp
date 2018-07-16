#include <iostream>
#include <algorithm>
#include <deque>

using namespace std;

template <class T>
struct display {
    void operator()(const T& x){
        cout << x << ' ';
    }
};

int main()
{
    {
        int ia[] = {0,1,2,3,4,5,6,7,8};
        copy_backward(ia+2, ia+7, ia+9);
        for_each(ia, ia+9, display<int>());//0 1 2 3 2 3 4 5 6
        cout << endl;
    }
    {
        int ia[] = {0,1,2,3,4,5,6,7,8};
        copy_backward(ia+2, ia+7, ia+5);
        for_each(ia, ia+9, display<int>());//2 3 4 5 6 5 6 7 8
        cout << endl;
    }
    {
        int ia[] = {0,1,2,3,4,5,6,7,8};
        deque<int> id(ia,ia+9);
        deque<int>::iterator first = id.begin();
        deque<int>::iterator last = id.end();
        ++++first;
        cout << *first << endl;//2
        ----last;
        cout << *last << endl;//7
        deque<int>::iterator result = id.end();
        copy_backward(first, last, result);
        for_each(id.begin(), id.end(), display<int>());//0 1 2 3 2 3 4 5 6
        cout << endl;
    }
    {
        int ia[] = {0,1,2,3,4,5,6,7,8};
        deque<int> id(ia,ia+9);
        deque<int>::iterator first = id.begin();
        deque<int>::iterator last = id.end();
        ++++first;
        cout << *first << endl;//2
        ----last;
        cout << *last << endl;//7
        deque<int>::iterator result = id.begin();
        advance(result, 5);
        copy_backward(first, last, result);
        for_each(id.begin(), id.end(), display<int>());//2 3 4 5 6 5 6 7 8
        cout << endl;
    }
}