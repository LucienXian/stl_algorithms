#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>

using namespace std;

namespace xtf{
    template<class ForwardIterator>
    ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last) {
        if (first==last) return last;
        ForwardIterator next = first;
        while(++next!=last){
            if (*first==*next) return first;
            first = next;
        }
        return last;
    }

    template<class ForwardIterator, class BinaryPredicate>
    ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate binary_pred){
        if (first==last) return last;
        ForwardIterator next = first;
        while(++next!=last){
            if (binary_pred(*first, *next)) return first;
            first = next;
        }
        return last;
    }
};

int main()
{
    int ia[] = {0,1,2,3,4,5,6,6,6,7,8};
    vector<int> iv(ia, ia+sizeof(ia)/sizeof(int));

    cout << *adjacent_find(iv.begin(), iv.end()) << endl;
    cout << *adjacent_find(iv.begin(), iv.end(), equal_to<int>()) << endl;

    cout << *xtf::adjacent_find(iv.begin(), iv.end()) << endl;
    cout << *xtf::adjacent_find(iv.begin(), iv.end(), equal_to<int>()) << endl;
}