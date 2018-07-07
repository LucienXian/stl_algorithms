#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
#include <string>

using namespace std;

namespace xtf{
    template<class ForwardIterator, class T>
    void fill(ForwardIterator first, ForwardIterator last, const T& value)
    {
        for ( ; first != last; first++)
            *first = value;
    }

    template<class ForwardIterator, class Size, class T>
    ForwardIterator fill_n(ForwardIterator first, Size n, const T& value)
    {
        for ( ; n > 0; n--, first++)
            *first = value;
        return first;
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

    fill(iv1.begin(), iv1.end(), 9);
    print_vec(iv1);
    fill_n(iv1.begin(), 3, 3);
    print_vec(iv1);

    xtf::fill(iv1.begin(), iv1.end(), 9);
    print_vec(iv1);
    xtf::fill_n(iv1.begin(), 3, 3);
    print_vec(iv1);

}