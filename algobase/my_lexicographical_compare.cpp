#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
#include <string>

using namespace std;

namespace xtf{
    template<class InputIterator1, class InputIterator2>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2){
        for ( ; first1!=last1 && first2!=last2 ; ++first1, ++first2){
            if (*first1 < *first2) return true;
            if (*first2 < *first1) return false;

        }
        return first1==last1 && first2!=last2;
    }

    template<class InputIterator1, class InputIterator2, class Compare>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2, Compare comp){
        for ( ; first1!=last1 && first2!=last2 ; ++first1, ++first2){
            if (comp(*first1,*first2)) return true;
            if (comp(*first2,*first1)) return false;
        }
        return first1==last1 && first2!=last2;
    }

    
}

int main()
{
    string stra1[] = {"Jamie", "JJHou", "Jason"};
    string stra2[] = {"Jamie", "JJHou", "Jerry"};
    cout << lexicographical_compare(stra1, stra1+2, stra2, stra2+2) << endl;
    cout << lexicographical_compare(stra1, stra1+2, stra2, stra2+2, greater<string>()) << endl;

    cout << xtf::lexicographical_compare(stra1, stra1+2, stra2, stra2+2) << endl;
    cout << xtf::lexicographical_compare(stra1, stra1+2, stra2, stra2+2, greater<string>()) << endl;
}