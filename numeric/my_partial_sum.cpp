#include <numeric>
#include <vector>
#include <functional>
#include <iostream>
#include <iterator>

using namespace std;

namespace xtf{
    template<class InputIterator, class OutputIterator>
    OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result)
    {
        if (first==last) return result;
        *result = *first;
        auto value = *first;
        while (++first != last) {
            value += *first;
            *++result = value;
        }
        return ++result;
    }

    template<class InputIterator, class OutputIterator, class BinaryOperation>
    OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result, 
                    BinaryOperation bin_op)
    {
        if (first==last) return result;
        *result = *first;
        auto value = *first;
        while (++first != last) {
            value = bin_op(value, *first);
            *++result = value;
        }
        return ++result;
    }
}


int main()
{
    vector<int> iv{1,2,3,4,5};

    ostream_iterator<int> oite(cout, ", ");
    
    partial_sum(iv.begin(), iv.end(), oite); cout << endl;
    partial_sum(iv.begin(), iv.end(), oite, minus<int>()); cout << endl;
    xtf::partial_sum(iv.begin(), iv.end(), oite); cout << endl;
    xtf::partial_sum(iv.begin(), iv.end(), oite, minus<int>()); cout << endl;

}