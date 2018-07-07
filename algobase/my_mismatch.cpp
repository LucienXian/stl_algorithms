#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
#include <string>

using namespace std;

namespace xtf{
    template<class InputIterator1, class InputIterator2>
    pair<InputIterator1, InputIterator2> iter_swap(InputIterator1 first1, InputIterator1 last1,
                                                    InputIterator2 first2)
    {
        while (first1!=last1&&*first1==*first2){
            first1++;
            first2++;
        }
        return pair<InputIterator1,InputIterator2>(first1, first2);
    }

    template<class InputIterator1, class InputIterator2, class BinaryPredicate>
    pair<InputIterator1, InputIterator2> iter_swap(InputIterator1 first1, InputIterator1 last1,
                                                    InputIterator2 first2, BinaryPredicate binary_pred)
    {
        while (first1!=last1&&*first1==*first2&&BinaryPredicate(*first1, *first2)){
            first1++;
            first2++;
        }
        return pair<InputIterator1,InputIterator2>(first1, first2);
    }


}

int main()
{
    int ia[9] = {0,1,2,3,4,5,6,7,8};
    vector<int> iv1(ia, ia+5);
    vector<int> iv2(ia, ia+9);

    cout << *(mismatch(iv1.begin(), iv1.end(), iv2.begin()).first) << endl;
    cout << *(mismatch(iv1.begin(), iv1.end(), iv2.begin()).second) << endl;

}