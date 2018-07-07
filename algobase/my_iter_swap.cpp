#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
#include <string>

using namespace std;

namespace xtf{
    template<class ForwardIterator1, class ForwardIterator2>
    inline void iter_swap(ForwardIterator1 a, ForwardIterator2 b)
    {
        typename iterator_traits<ForwardIterator1>::value_type tmp = *a;
        *a = *b;
        *b = tmp;
    }

}

void print_vec(vector<int>& v)
{
    for (auto& a : v)
        cout << a << " ";
    cout << endl;
}

int main()
{
    int ia[9] = {0,1,2,3,4,5,6,7,8};
    vector<int> iv1(ia, ia+5);
    vector<int> iv2(ia, ia+9);

    vector<int>::iterator iter1 = iv1.begin();
    vector<int>::iterator iter2 = iter1+3;
    iter_swap(iter1, iter2);
    cout << *iter1 << "  " << *iter2 << endl;
    print_vec(iv1);

    xtf::iter_swap(iter1, iter2);
    cout << *iter1 << "  " << *iter2 << endl;
    print_vec(iv1);

}