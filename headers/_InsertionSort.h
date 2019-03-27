#pragma once
#define _instance(x) (*(x))
#include "_airplane.h"
//
// Created by HengyiYu on 2019/3/17.
//

template <typename RandomAccessIterator, typename Compare>
extern void _InsertionSort(RandomAccessIterator L, RandomAccessIterator R, Compare cmp);

