#include <numeric>
#include <vector>
#include <functional>
#include <iostream>
#include <iterator>

using namespace std;

namespace xtf{
    template<class InputIterator, class T>
    T accumulate(InputIterator first, InputIterator last, T init){
        for ( ;first!=last; first++)
            init += *first;
        return init;
    }

    template<class InputIterator, class T, class BinaryOperation>
    T accumulate(InputIterator first, InputIterator last, T init, BinaryOperation binary_op){
        for ( ;first!=last; first++)
            init = binary_op(init, *first);
        return init;
    }
}

int main()
{
    vector<int> iv{1,2,3,4,5};
    cout << accumulate(iv.begin(), iv.end(), 0) << endl;
    cout << accumulate(iv.begin(), iv.end(),  0, minus<int>()) << endl;

    cout << xtf::accumulate(iv.begin(), iv.end(), 0) << endl;
    cout << xtf::accumulate(iv.begin(), iv.end(), 0,  minus<int>()) << endl;
}