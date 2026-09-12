#include "PmergeMe.hpp"

PmergeMe::PmergeMe() { }

PmergeMe::~PmergeMe() { }

PmergeMe::PmergeMe(const PmergeMe& obj): _v(obj._v), _q(obj._q){}


PmergeMe& PmergeMe::operator=(const PmergeMe& obj)
{
    if(this != &obj)
    {
        _v = obj._v;
        _q =obj._q;
    }
    return *this;
}


std::vector<int> ParseArgs(int argc,char **argv)
{
    std::vector<int> res;

    int i;
    for(i = 1; i < argc ;i++)
    {
        if(argv[i][0] == '\0')
        {
            std::cout << "Error: empty string." << std::endl;
            res.clear();
            return res;
        }
        int j = 0;
        while(argv[i][j] )
        {
            if(!isdigit(argv[i][j]))
            {
                std::cout << "Error: Format No Valid." << std::endl;
                res.clear();
                return res;
            }
            j++;
        }
        long number = std::atol(argv[i]);
        if(number > INT_MAX)
        {
            std::cout << "Error: OverFlow problem." << std::endl;
            res.clear();
            return res;
        }
        int NumConverted = static_cast<int> (number);
        res.push_back(NumConverted);
    }

    return res;
}

std::deque<int> StoreValuesToDeque(std::vector<int> &v)
{
    std::deque<int> d;
    std::vector<int>::iterator it;

    for(it = v.begin(); it != v.end(); ++it)
    {
        d.push_back(*it);
    }

    return d;
}
std::vector<std::pair<int,int> >MakePairs(const std::vector<int> &v,bool &hasOdd, int &OddValue)
{
    std::pair<int,int> p;
    std::vector<std::pair<int,int> > pairs;
    int last = 0;
    size_t limite;
    if(v.size() % 2 == 0)
        limite = v.size();
    else
        limite = v.size() - 1;
    
    for(size_t i = 0; i < limite;i+=2)
    {
        if(v[i+1] > v[i])
        {
            p.first = v[i+1];
            p.second = v[i];
            pairs.push_back(p);
        }
        else
        {
            p.first = v[i];
            p.second =v[i + 1];    
            pairs.push_back(p);
        }
    }

    if(v.size() % 2 != 0)
    {
        hasOdd = true;
        OddValue = v[v.size() - 1];
    }
    else
        hasOdd = false;
    return pairs;
}
std::vector <int> BuilDMainChain(std::vector <int> &G,std::vector <int> &P)
{
    std::vector<int> MainChain;

    MainChain.push_back(P[0]);
    for(size_t i = 0; i  < G.size() ; i++)
        MainChain.push_back(G[i]);

    return MainChain;
}

std::vector<int>::iterator binarysearch(std::vector<int> &MainChain,int value,std::vector<int>::iterator limit)
{
    std::vector<int>::iterator low = MainChain.begin();
    std::vector<int>::iterator hight = limit;

    while (low < hight)
    {
        std::vector<int>::iterator  mid = low + (hight - low) / 2;
        
        if(*mid < value)
            low = mid + 1;
        else
            hight = mid;
    }
    return low;
}


void insertionSortRecursion(std::vector<int> &Main,int n)
{
    if(n <= 1)
        return;
    
    insertionSortRecursion(Main,n-1);

    int last = Main[n-1];
    int j = n - 2;

    while(j >= 0 && Main[j] > last)
    {
        Main[j+1] = Main[j];
        j--;
    }
    Main[j+1] = last;

}


std::vector<int> mergeInsertSort(std::vector<int> &v)
{
    if(v.size() <= 1)
        return v;
    bool hasOdd = false;
    int OddValue = 0;
    std::vector<std::pair<int,int> > pairs = MakePairs(v,hasOdd,OddValue);
   

    // Speare MainChian and pend

    std::vector<int> MainChain;
    std::vector<int> pend;


    for(size_t i = 0; i < pairs.size();i++)
    {
        MainChain.push_back(pairs[i].first);
        pend.push_back(pairs[i].second);
    }
      std::cout << "Main: ";
    for(size_t i = 0; i < MainChain.size();i++)
        std::cout << " " << MainChain[i] <<  " ";
    std::cout <<"\n";

    std::vector<int> partners;
    for(int i = 0; i < (int)MainChain.size();i++)
        partners.push_back(MainChain[i]);

    // sort MainChain
        int n = MainChain.size();
        insertionSortRecursion(MainChain,n);

       std::cout << "MainChainAvecRecusion: ";
        for(size_t i = 0; i < MainChain.size();i++)
            std::cout << " " << MainChain[i] <<  " ";
        std::cout <<"\n";

     // main chain original

 
    // insert first element pend in MainChain
    MainChain.insert(MainChain.begin(),pend[0]);

    //suite JacobSthal
    std::vector<int> JacobSthal;

    JacobSthal.push_back(0);
    JacobSthal.push_back(1);

    for(int i = 1; i < (int)pend.size();i++)
    {
        int n = JacobSthal.size();
        int next = JacobSthal[n - 1] + 2 * JacobSthal[n - 2];
        JacobSthal.push_back(next);
    }
    // Creer des groupes 

    std::vector<int> Groupes;

    for(int i = 1; i < (int)JacobSthal.size();i++)
    {
        int previous = JacobSthal[i - 1];
        int current = JacobSthal[i];

        int start = std::min(current,(int)pend.size() - 1);

        for(int j = start;j > previous;j--)
        Groupes.push_back(j);
    }

    std::cout << "La suite de JacobSthal: " << "\n";
    for(size_t i = 0; i < JacobSthal.size();i++)
        std::cout << "J(" << JacobSthal[i] <<  ")";
    std::cout <<"\n";

    std::cout << "Groupes: " << "\n";
    for(size_t i = 0; i < Groupes.size();i++)
        std::cout << "J(" << Groupes[i] <<  ")";
    std::cout <<"\n";

    //  std::cout << "Main: ";
    // for(size_t i = 0; i < MainChain.size();i++)
    //     std::cout << " " << MainChain[i] <<  " ";
    // std::cout <<"\n";

    std::cout << "pend: ";
    for(size_t i = 0; i < pend.size();i++)
        std::cout << " " << pend[i] <<  " ";
    std::cout <<"\n";

   

    

    // Inseret element avec binary search

    for(int i = 0; i < (int)Groupes.size();i++)
    {
        int index = Groupes[i];

        std::vector<int>::iterator limit = std::find(MainChain.begin(),MainChain.end(),partners[index]);


        std::vector<int>::iterator pos = binarysearch(MainChain,pairs[index].second,limit);


        MainChain.insert(pos,pairs[index].second);
    }

    //apres merge sort
    std::cout << "Main Apres: ";
    for(size_t i = 0; i < MainChain.size();i++)
        std::cout << " " << MainChain[i] <<  " ";
    std::cout <<"\n";
    

    return MainChain;
}

