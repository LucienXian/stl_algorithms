#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
#include <string>

using namespace std;

namespace xtf{
    template<class InputIterator1, class InputIterator2>
    inline bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
    {
        for ( ; first1 != last1; first1++, first2++)
            if (*first1 != *first2) return false;
        return true;
    }

    template<class InputIterator1, class InputIterator2, class BinaryPredicate>
    inline bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate binary_pred)
    {
        for ( ; first1 != last1; first1++, first2++)
            if (!binary_pred(*first1, *first2)) return false;
        return true;
    }
}

int main()
{
    int ia[9] = {0,1,2,3,4,5,6,7,8};
    vector<int> iv1(ia, ia+5);
    vector<int> iv2(ia, ia+9);

    cout << equal(iv1.begin(), iv1.end(), iv2.begin()) << endl;
    cout << equal(iv1.begin(), iv1.end(), &ia[3]) << endl;
    cout << equal(iv1.begin(), iv1.end(), &ia[3], less<int>()) << endl;

    cout << xtf::equal(iv1.begin(), iv1.end(), iv2.begin()) << endl;
    cout << xtf::equal(iv1.begin(), iv1.end(), &ia[3]) << endl;
    cout << xtf::equal(iv1.begin(), iv1.end(), &ia[3], less<int>()) << endl;
}