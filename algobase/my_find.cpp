#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
#include <string>

using namespace std;

namespace xtf{
    template <class InputIterator, class T>
    InputIterator find(InputIterator first, InputIterator last, const T& value) {
        while (first != last && *first!=value) ++first;
        return first; 
    }

    template <class InputIterator, class Predicate>
    InputIterator find_if(InputIterator first, InputIterator last, const Predicate& pred) {
        while (first != last && pred(*first)) ++first;
        return first; 
    }

    template<class ForwardIterator1, class ForwardIterator2>
    ForwardIterator1 __find_end(ForwardIterator1 first1, ForwardIterator1 last1, 
                                ForwardIterator2 first2, ForwardIterator2 last2,
                                forward_iterator_tag, forward_iterator_tag)
    {
        if (first1 == last2) return last1;
        else {
            ForwardIterator1 result = last1;
            while (1) {
                ForwardIterator1 new_result = search(first1, last1, first2, last2);
                if (new_result == last1) return result;
                else {
                    result = new_result;
                    first1 = new_result;
                    first1++;
                    //cout << "111" << endl;
                }
            }
        }
    }

    template<class BidirecttionalIterator1, class BidirecttionalIterator2>
    BidirecttionalIterator1 __find_end(BidirecttionalIterator1 first1, BidirecttionalIterator1 last1, 
                                BidirecttionalIterator2 first2, BidirecttionalIterator2 last2,
                                bidirectional_iterator_tag, bidirectional_iterator_tag)
    {
        typedef reverse_iterator<BidirecttionalIterator1> reviter1;
        typedef reverse_iterator<BidirecttionalIterator2> reviter2;
        reviter1 rlast1(first1);
        reviter2 rlast2(first2);
        reviter1 rresult = search(reviter1(last1), rlast1, reviter2(last2), rlast2);
        if (rresult == rlast1) return last1;
        else {
            BidirecttionalIterator1 result = rresult.base();
            advance(result, -distance(first2, last2));
            //cout << "11122" << endl;
            return result;
        }
    }

    template<class ForwardIterator1, class ForwardIterator2>
    inline ForwardIterator1
    find_end(ForwardIterator1 first1, ForwardIterator1 last1,
            ForwardIterator2 first2, ForwardIterator2 last2)
    {
        typedef typename iterator_traits<ForwardIterator1>::iterator_category category1;
        typedef typename iterator_traits<ForwardIterator2>::iterator_category category2;

        return __find_end(first1, last1, first2, last2, category1(), category2());
    }

    
}

int main()
{
    int ia[9] = {0,1,2,3,4,5,6,7,8};
    vector<int> iv(ia, ia+sizeof(ia)/sizeof(int));
    vector<int> iv2(ia+6, ia+8);
    cout << *(find_end(iv.begin(), iv.end(), iv2.begin(), iv2.end())) << endl;;
    cout << *(xtf::find_end(iv.begin(), iv.end(), iv2.begin(), iv2.end())) << endl;;
}