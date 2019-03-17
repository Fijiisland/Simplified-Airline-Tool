#pragma once

#include "airplane.h"
//
// Created by HengyiYu on 2019/3/17.
//
template <typename RandomAccessIterator, typename Compare>
void _InsertionSort(RandomAccessIterator L, RandomAccessIterator R, Compare cmp){
    for(RandomAccessIterator i = L + 1;i <= R;i ++){
        Airplane temp = *i;
        RandomAccessIterator j;
        for(j = i;j > L && cmp(temp, *(j - 1));j--)
            *j = *(j - 1);
        *j = temp;
    }
}

