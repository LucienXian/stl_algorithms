#include <numeric>
#include <vector>
#include <functional>
#include <iostream>
#include <iterator>

using namespace std;

namespace xtf{
    template<class InputIterator1, class InputIterator2, class T>
    T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init)
    {
        for (; first1 != last1; first1++, first2++)
            init += (*first1 * *first2);
        return init;
    }

    template<class InputIterator1, class InputIterator2, class T, 
            class BinaryOperation1, class BinaryOperation2>
    T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init, 
                    BinaryOperation1 bin_op1, BinaryOperation2 bin_op2)
    {
        for (; first1 != last1; first1++, first2++)
            init = bin_op1(init, bin_op2(*first1, *first2));
        return init;
    }
}


int main()
{
    vector<int> iv{1,2,3,4,5};

    cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10) << endl;
    cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10, minus<int>(), plus<int>()) << endl;;

    cout << xtf::inner_product(iv.begin(), iv.end(), iv.begin(), 10) << endl;;
    cout << xtf::inner_product(iv.begin(), iv.end(), iv.begin(), 10, minus<int>(), plus<int>()) << endl;

}