#include <set>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

template <class T>
struct display {
    void operator()(const T& x)
    { cout << x << " ";} 
};

namespace xtf{
    template<class InputIterator1, class InputIterator2, class OutputIterator>
    OutputIterator set_union(InputIterator1 first1, InputIterator1 last1, 
                            InputIterator2 first2, InputIterator2 last2,
                            OutputIterator result) {
        while (first1!=last1 && first2!=last2) {
            if (*first1 < *first2) {
                *result = *first1;
                first1++;
            }
            else if (*first2 < *first1) {
                *result = *first2;
                first2++;
            }
            else{
                *result = *first1;
                first1++;
                first2++;
            }
            result++;
        }
        return copy(first1, last1, copy(first2, last2, result));
    }

    template<class InputIterator1, class InputIterator2, class OutputIterator>
    OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1, 
                            InputIterator2 first2, InputIterator2 last2,
                            OutputIterator result)
    {
        while (first1!=last1 && first2!=last2) {
            if (*first1 < *first2) {
                //*result = *first1;
                first1++;
            }
            else if (*first2 < *first1) {
                //*result = *first2;
                first2++;
            }
            else{
                *result = *first1;
                first1++;
                first2++;
                result++;
            }
        }
        return result;
    }

    template<class InputIterator1, class InputIterator2, class OutputIterator>
    OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1, 
                            InputIterator2 first2, InputIterator2 last2,
                            OutputIterator result)
    {
        while (first1!=last1 && first2!=last2) {
            if (*first1 < *first2) {
                *result = *first1;
                result++;
                first1++;
            }
            else if (*first2 < *first1) {
                //*result = *first2;
                first2++;
            }
            else{
                //*result = *first1;
                first1++;
                first2++;
                //result++;
            }
        }
        return copy(first1, last1, result);
    }

    template<class InputIterator1, class InputIterator2, class OutputIterator>
    OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1, 
                            InputIterator2 first2, InputIterator2 last2,
                            OutputIterator result)
    {
        while (first1!=last1 && first2!=last2) {
            if (*first1 < *first2) {
                *result = *first1;
                result++;
                first1++;
            }
            else if (*first2 < *first1) {
                *result = *first2;
                result++;
                first2++;
            }
            else{
                //*result = *first1;
                first1++;
                first2++;
                //result++;
            }
        }
        return copy(first1, last1, copy(first2, last2, result));

    }
};

int main()
{
    int ia1[6] = {1,3,5,7,9,11};
    int ia2[7] = {1,1,2,3,5,8,13};

    multiset<int> S1(ia1, ia1+6);
    multiset<int> S2(ia2, ia2+7);


    multiset<int>::iterator first1 = S1.begin();
    multiset<int>::iterator last1 = S1.end();
    multiset<int>::iterator first2 = S2.begin();
    multiset<int>::iterator last2 = S2.end();
    cout << endl;
    cout << "xtf set_union" << endl;
    set_union(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));
    cout << endl;
    xtf::set_union(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));

    cout << endl;
    cout << "xtf set_intersection" << endl;
    set_intersection(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));
    cout << endl;
    xtf::set_intersection(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));

    cout << endl;
    cout << "xtf set_intersection" << endl;
    set_difference(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));
    cout << endl;
    xtf::set_difference(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));

    cout << endl;
    cout << "xtf set_symmetric_difference" << endl;
    set_symmetric_difference(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));
    cout << endl;
    xtf::set_symmetric_difference(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));
}