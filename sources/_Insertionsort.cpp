#include "headers/_InsertionSort.h"

template <typename RandomAccessIterator, typename Compare>
void _InsertionSort(RandomAccessIterator L, RandomAccessIterator R, Compare cmp){
    for(RandomAccessIterator i = L + 1;i <= R;i ++){
        Airplane temp = _instance(i);
        RandomAccessIterator j;
        for(j = i;j > L && cmp(temp, _instance(j - 1));j--)
            _instance(j) = _instance(j - 1);
        _instance(j) = temp;
    }
}
