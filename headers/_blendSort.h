#pragma once

#include <cstdlib>
#include <algorithm>
#include <ctime>
#include "_InsertionSort.h"
#include "_airplane.h"
//
// Created by HengyiYu on 2019/3/17.
//
namespace mySort {
    template <typename RandomAccessIterator, typename Compare>
    extern void _quickSort(RandomAccessIterator L, RandomAccessIterator R, Compare cmp);
}

namespace mySort{
    template <typename RandomAccessIterator, typename Compare>
    extern void sort(RandomAccessIterator first, RandomAccessIterator last, Compare cmp);
}
