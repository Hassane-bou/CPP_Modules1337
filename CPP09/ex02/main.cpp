#include "PmergeMe.hpp"


int main(int ac,char **av)
{
    if(ac == 1)
    {
        std::cout << "Error." << std::endl;
        return 1;
    }
    std::vector<int> resulat = ParseArgs(ac,av);
    if(resulat.empty())
    {
        std::cout << "Error: Container empty." << std::endl;
        return 1;
    }
    std::deque<int> values =StoreValuesToDeque(resulat);

    std::cout << "Before: ";
    for(size_t i = 0; i < values.size();i++)
    {
        std::cout << values[i] << " ";
    }
    std::cout << std::endl;


    std::vector<int> sortedVector = mergeInsertSort(resulat);

    return 0;

}