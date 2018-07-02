#include <numeric>
#include <vector>
#include <functional>
#include <iostream>
#include <iterator>

using namespace std;

namespace xtf{
    template <class InputIterator, class OutputIterator>
    OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result) {
        if (first == last) return result;
        *result = *first;
        typename iterator_traits<InputIterator>::value_type value, prev;
        prev = *first;
        while (++first != last) {
            value = *first;
            *++result = value - prev;
            prev = value;
        }
        return ++result;
    }

    template <class InputIterator, class OutputIterator, class BinaryOperation>
    OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation binary_op) {
        if (first == last) return result;
        *result = *first;
        typename iterator_traits<InputIterator>::value_type value, prev;
        prev = *first;
        while (++first != last) {
            value = *first;
            *++result = binary_op(value ,prev);
            prev = value;
        }
        return ++result;       
    }
}


int main()
{
    vector<int> iv{1,2,3,4,5};

    ostream_iterator<int> oite(cout, ", ");
    adjacent_difference(iv.begin(), iv.end(), oite); cout << endl;
    adjacent_difference(iv.begin(), iv.end(),  oite, minus<int>()); cout << endl;

    xtf::adjacent_difference(iv.begin(), iv.end(), oite); cout << endl;
    xtf::adjacent_difference(iv.begin(), iv.end(),  oite, plus<int>()); cout << endl;

}