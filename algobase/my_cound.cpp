#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
#include <string>

using namespace std;

namespace xtf{
    template <class InputIterator, class T>
    typename iterator_traits<InputIterator>::difference_type
    count(InputIterator first, InputIterator last, const T& value) {
        typename iterator_traits<InputIterator>::difference_type n = 0;
        for ( ;first != last; ++first)
            if (*first == value) ++n;
        return n;
    }
    
    template <class InputIterator, class Predicate>
    typename iterator_traits<InputIterator>::difference_type
    count_if(InputIterator first, InputIterator last, Predicate pred) {
        typename iterator_traits<InputIterator>::difference_type n = 0;
        for ( ;first != last; ++first)
            if (pred(*first)) ++n;
        return n;
    }
}

int main()
{
    int ia[9] = {0,1,2,3,4,5,6,7,8};
    vector<int> iv(ia, ia+sizeof(ia)/sizeof(int));
    //vector<int> iv2(ia, ia+9);
    cout << count(iv.begin(), iv.end(), 6) << endl;
    cout << count_if(iv.begin(), iv.end(), bind2nd(less<int>(), 7)) << endl;

    cout << xtf::count(iv.begin(), iv.end(), 6) << endl;
    cout << xtf::count_if(iv.begin(), iv.end(), bind2nd(less<int>(), 7)) << endl;
    
}