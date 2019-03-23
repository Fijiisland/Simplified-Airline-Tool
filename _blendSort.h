#pragma once

#include <cstdlib>
#include <algorithm>
#include <ctime>
#include "_InsertionSort.h"
#include "_airplane.h"
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
        srand((unsigned)time(nullptr));
        _quickSort(first, last - 1, cmp);
    }

    template <typename RandomAccessIterator, typename Compare>
    void _quickSort(RandomAccessIterator L, RandomAccessIterator R, Compare cmp){
        if(R - L <= 15){
            _InsertionSort(L, R, cmp);
            return;
        }
        // Partition
        std::swap(_instance(L), _instance(L+rand()%(R-L+1)));
        Airplane temp = _instance(L);
        RandomAccessIterator lt = L, gt = R + 1, i = L + 1;
        while(i < gt){
            if(cmp(_instance(i), temp)){
                std::swap(_instance(lt + 1),_instance(i)); lt++; i++;
            }else if(cmp(temp, _instance(i))){
                std::swap(_instance(gt - 1), _instance(i)); gt--;
            }else i++;
        }
        std::swap(_instance(L), _instance(lt));
        _quickSort(L,lt - 1, cmp);
        _quickSort(gt, R, cmp);
    }
}
