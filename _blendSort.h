#pragma once

#include <cstdlib>
#include <algorithm>
#include <ctime>
#include "_InsertionSort.h"
#include "airplane.h"
//
// Created by HengyiYu on 2019/3/17.
//
namespace mySort{
    template <typename RandomAccessIterator, typename Compare>
    void sort(RandomAccessIterator first, RandomAccessIterator last, Compare cmp);
    template <typename RandomAccessIterator, typename Compare>
    void _quickSort(RandomAccessIterator L, RandomAccessIterator R, Compare cmp);





    template <typename RandomAccessIterator, typename Compare>
    void sort(RandomAccessIterator first, RandomAccessIterator last, Compare cmp){
        srand((unsigned)time(NULL));
        _quickSort(first, last - 1, cmp);
    }

    template <typename RandomAccessIterator, typename Compare>
    void _quickSort(RandomAccessIterator L, RandomAccessIterator R, Compare cmp){
        if(R - L <= 15){
            _InsertionSort(L, R, cmp);
            return;
        }
        // Partition
        std::swap(*L, *(L+rand()%(R-L+1)));
        Airplane temp = *L;
        RandomAccessIterator lt = L, gt = R + 1, i = L + 1;
        while(i < gt){
            if(cmp(*i, temp)){
                std::swap(*(lt + 1),*i); lt++; i++;
            }else if(cmp(temp, *i)){
                std::swap(*(gt - 1), *i); gt--;
            }else i++;
        }
        std::swap(*L, *lt);
        _quickSort(L,lt - 1, cmp);
        _quickSort(gt, R, cmp);
    }
}
