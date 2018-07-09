# SGI STL中的copy算法

在stl中，copy是一个调用非常频繁的函数，而这些操作又涉及到了各种的内存操作——运用assignment operator或者copy constructor。为了提高效率，对于拥有trivial assignment operator的元素类型，可以使用直接的内存复制（例如C库函数——memmove或者memcpy）。

copy算法脉络：

![img](stl_copy_6_2)

在这里有一个需要注意的问题，就是由于copy算啊是将输入区间内的元素复制到输出区间中，因此当输入区间与输出区间重叠的时候很有可能出现问题。

![img](stl_copy_6_3)

这里出现问题的原因是由于deque的迭代器不是原生指针，如果使用的是vector，迭代器是原生指针，调用copy算法后会以memmove执行实际的复制操作，这样整块内存进行复制就不会出错。

> 但是这个在我的机器上运行是正确的
>
> gcc version 5.4.0

[my_copy_overlap.cpp](https://github.com/LucienXian/stl_algorithms/blob/master/algobase/my_copy_overlap.cpp)

```cpp
#include <iostream>
#include <iterator>
#include <algorithm>
#include <deque>

using namespace std;

void print(int v[])
{
    for(int i=0;i<9;i++)
        cout << v[i] << " ";
    cout << endl;
}

int main()
{
    {
        int ia[] = {0,1,2,3,4,5,6,7,8};
        copy(ia+2, ia+7,ia);//输出区间的终点与输入区间重叠，copy正常
        print(ia); //2 3 4 5 6 5 6 7 8
    }
    {
        int ia[] = {0,1,2,3,4,5,6,7,8};
        deque<int> id(ia, ia+9);
        deque<int>::iterator first = id.begin();
        deque<int>::iterator last = id.end();
        ++++first; //advance 2
        cout << *first << endl;
        ----last; //advance -2
        cout << *last << endl;
        deque<int>::iterator res = id.begin();
        copy(first, last, res);
        copy(id.begin(), id.end(), ostream_iterator<int>(cout, " "));//2 3 4 5 6 5 6 7 8
        cout << endl;
    }
    {
        int ia[] = {0,1,2,3,4,5,6,7,8};
        deque<int> id(ia, ia+9);
        deque<int>::iterator first = id.begin();
        deque<int>::iterator last = id.end();
        ++++first; //advance 2
        cout << *first << endl;
        ----last; //advance -2
        cout << *last << endl;
        deque<int>::iterator res = id.begin();
        res = res+4;
        copy(first, last, res);
        copy(id.begin(), id.end(), ostream_iterator<int>(cout, " "));//0 1 2 3 2 3 4 5 6
        cout << endl;
    }
}
```



我们还是回到SGI的STL吧，以下是唯一的对外接口：

```cpp
template <class InputIterator, class OutputIterator>
inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
{
    return __copy_dispatch<InputIterator, OutputIterator>()(first, last, result);
}
```



另外，会有两个重载函数，针对原始指针——const char*和const wchar_t*，进行内存直接拷贝操作：

```c++
inline char* copy(const char* first, const char* last, char* result)
{
    memmove(result, first, last-first);
    return result+(last-first);
}

inline wchar_t* copy(const wchar_t* first, const wchar_t* last, wchar_t* result)
{
    memmove(result, first, sizeof(wchar_t)*(last-first));
    return result+(last-first);
}
```



接下来，我们看一下copy()函数中调用的__copy_dispatch()：

```c++
template <class InputIterator, class OutputIterator>
strcut __copy_dispatch
{
	OutputIterator operator()(InputIterator first, InputIterator last, OutputIterator result){
		return __copy(first, last, result, iterator_category(first));
	}
}

//另外，提供两个偏特化版本，针对的是T*指针类型
//这里的目的是在参数为原生指针的前提下，判断指针所指对象是否拥有trivial assignment operator，如果是，则直接使用memmove进行内存拷贝，否则，需要调用assignment operator进行复制
template <class T>
strcut __copy_dispatch<T*, T*>
{
	T* operator()(T* first, T* last, T* result){
		typedef typename __type_traits<T>::has_trivial_assignment_operator t;
		return __copy_t(first, last, result, t());
	}
}
template <class T>
strcut __copy_dispatch<const T*, T*>
{
	T* operator()(const T* first, const T* last, T* result){
		typedef typename __type_traits<T>::has_trivial_assignment_operator t;
		return __copy_t(first, last, result, t());
	}
}
```



先来看看泛化版本的**__copy_dispatch调用的** 函数**__copy**，该函数针对不同类型的迭代器使用的循环条件不同：

```cpp
template <class InputIterator, class OutputIterator>
inline OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, input_iterator_tag)
{
    for (; first!=last; ++result, ++first)
        *result = *first;
    return result;
}

template <class RandomAccessIterator, class OutputIterator>
inline OutputIterator __copy(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, random_access_iterator_tag)
{
    //抽出这个函数，是因为接下来也有被使用的地方
    return __copy_d(first, last, result, distance_type(first));
}
```



接下来是__copy_d的实现：

```c++
template <class RandomAccessIterator, class OutputIterator, class Distance>
inline OutputIterator __copy_d(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, Distance*)
{
    for (Distance n = last-first; n>0; --n, ++result, ++first)
        *result = *first;
    return result;
}
```



回到__copy_dispatch的偏特化版本中，这个函数里面调用 \_\_copy_t()

```c++
template <class T>
inline T* __copy_t(const T* first, const T* last, T* result, __true_type)
{
    memmove(result, first, sizeof(T)*(last-first));
    return result+(last-first);
}

template <class T>
inline T* __copy_t(const T* first, const T* last, T* result, __false_type)
{
    //原生指针是一种RandomAccessIterator，所以交给了__copy_d
    return __copy_d(first, last, result, (ptrdiff_t*)0);
}
```



> 即便自定义的class C具备trivial operator=，它仍然可能被判断__false_type，这是因为<type_triais.h>中只针对某些类型做了记录。

