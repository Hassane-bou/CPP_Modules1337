#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>
#include <cerrno>
#include <algorithm>
#include <ctime>



class PmergeMe
{
    private:
        std::vector<int> _v;
        std::deque<int> _q;

    public:
        PmergeMe();
        ~PmergeMe();
        PmergeMe(const PmergeMe& obj);
        PmergeMe& operator=(const PmergeMe& obj);

};
    std::vector<int> ParseArgs(int argc,char **argv);
    std::deque<int> StoreValuesToDeque(std::vector<int> &v);
    std::vector<std::pair<int,int> >MakePairs(const std::vector<int> &v,bool &hasOdd, int &OddValue);
    std::vector<int> mergeInsertSortVector(std::vector<int> &v);
    std::deque<int> mergeInsertSortdeque(std::deque<int> &d);