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
            // std::cout << "Error: empty string." << std::endl;
            res.clear();
            return res;
        }
        int j = 0;
        while(argv[i][j] )
        {
            if(!isdigit(argv[i][j]))
            {
                // std::cout << "Error: Format No Valid." << std::endl;
                res.clear();
                return res;
            }
            j++;
        }
        long number = std::atol(argv[i]);
        if(number > INT_MAX)
        {
            // std::cout << "Error: OverFlow problem." << std::endl;
            res.clear();
            return res;
        }
        int NumConverted = static_cast<int> (number);
        res.push_back(NumConverted);
    }

    return res;
}
    //Deque Soultion
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

std::deque<std::pair<int,int> >MakePairsDeque(const std::deque<int> &d,bool &hasOdd, int &OddValue)
{
    std::pair<int,int> p;
    std::deque<std::pair<int,int> > pairs;
    int last = 0;
    size_t limite;
    if(d.size() % 2 == 0)
        limite = d.size();
    else
        limite = d.size() - 1;
    
    for(size_t i = 0; i < limite;i+=2)
    {
        if(d[i+1] > d[i])
        {
            p.first = d[i+1];
            p.second = d[i];
            pairs.push_back(p);
        }
        else
        {
            p.first = d[i];
            p.second =d[i + 1];    
            pairs.push_back(p);
        }
    }

    if(d.size() % 2 != 0)
    {
        hasOdd = true;
        OddValue = d[d.size() - 1];
    }
    else
        hasOdd = false;
    return pairs;
}
std::deque<int>::iterator binarysearchDeque(std::deque<int> &MainChain,int value,std::deque<int>::iterator limit)
{
    std::deque<int>::iterator low = MainChain.begin();
    std::deque<int>::iterator hight = limit;

    while (low < hight)
    {
        std::deque<int>::iterator  mid = low + (hight - low) / 2;
        
        if(*mid < value)
            low = mid + 1;
        else
            hight = mid;
    }
    return low;
}
void RecursionDeque(std::deque<int> &Main,int n)
{
    if(n <= 1)
        return;
    
    RecursionDeque(Main,n-1);

    int last = Main[n-1];
    int j = n - 2;

    while(j >= 0 && Main[j] > last)
    {
        Main[j+1] = Main[j];
        j--;
    }
    Main[j+1] = last;

}
std::deque<int> MainChainPartnersDeque(std::deque<int> &MainChain)
{
    std::deque<int> partners;
    for(int i = 0; i < (int)MainChain.size();i++)
        partners.push_back(MainChain[i]);
    return partners;
}
std::deque<int> JacobSthalAlgoDeque(std::deque<int> &pend,std::deque<int> &MainChain)
{
 
    std::deque<int> JacobSthal;

    JacobSthal.push_back(0);
    JacobSthal.push_back(1);

    for(int i = 1; i < (int)pend.size();i++)
    {
        int n = JacobSthal.size();
        int next = JacobSthal[n - 1] + 2 * JacobSthal[n - 2];
        JacobSthal.push_back(next);
    }
    return JacobSthal;
}

std::deque<int> IndicesJacobSthalDeque(std::deque<int> &JacobSthal,std::deque<int> &pend)
{
    std::deque<int> Groupes;
    for(int i = 1; i < (int)JacobSthal.size();i++)
    {
        int previous = JacobSthal[i - 1];
        int current = JacobSthal[i];

        int start = std::min(current,(int)pend.size() - 1);

        for(int j = start;j > previous;j--)
        Groupes.push_back(j);
    }
    return Groupes;
}
std::deque<int> mergeInsertSortdeque(std::deque<int> &d)
{
    if(d.size() <= 1)
        return d;
    bool hasOdd = false;
    int OddValue = 0;
    std::deque<std::pair<int,int> > pairs = MakePairsDeque(d,hasOdd,OddValue);
   
    clock_t start,end;

    // Speare MainChian and pend
    std::deque<int> MainChain;
    std::deque<int> pend;
    for(size_t i = 0; i < pairs.size();i++)
    {
        MainChain.push_back(pairs[i].first);
        pend.push_back(pairs[i].second);
    }

    // sort MainChain
    int n = MainChain.size();
    RecursionDeque(MainChain,n);


    start = clock();

    // insert first element pend in MainChain
    int firstPend = -1;
    for(size_t i = 0; i < pairs.size();i++)
    {
        if(pairs[i].first == MainChain[0])
        {
            firstPend = pairs[i].second;
            break;
        }
    }
    
    // main chain original
    std::deque<int> partners = MainChainPartnersDeque(MainChain);
    MainChain.insert(MainChain.begin(),firstPend);
    //suite JacobSthal
    std::deque<int> JacobSthal = JacobSthalAlgoDeque(pend,MainChain);
    // Creer des groupes 
    std::deque<int> Groupes = IndicesJacobSthalDeque(JacobSthal,pend);
    
   

    // Inseret element avec binary search
    for(int i = 0; i < (int)Groupes.size();i++)
    {
        int index = Groupes[i];
        int ValueToInsert = -1;
        for(size_t k =  0; k < pairs.size();k++)
        {
            if(pairs[k].first == partners[index])
            {
                ValueToInsert= pairs[k].second;
                break;
            }
        }

        std::deque<int>::iterator limit = std::find(MainChain.begin(),MainChain.end(),partners[index]);

        std::deque<int>::iterator pos = binarysearchDeque(MainChain,ValueToInsert,limit);

        MainChain.insert(pos,ValueToInsert);
    }

    // inserer element impaire if exist
    if(hasOdd)
    {
        std::deque<int>::iterator value = binarysearchDeque(MainChain,OddValue,MainChain.end());
        MainChain.insert(value,OddValue);
    }

    end = clock();

    double time = (double)(end - start) / CLOCKS_PER_SEC * 1000000;


    std::cout << "Time to process a range of " << d.size() << " elements with std::deque :  " << 
    time << " us"  << std::endl;

    return MainChain;
}

    // Vector Soultion
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


void Recursion(std::vector<int> &Main,int n)
{
    if(n <= 1)
        return;
    
    Recursion(Main,n-1);

    int last = Main[n-1];
    int j = n - 2;

    while(j >= 0 && Main[j] > last)
    {
        Main[j+1] = Main[j];
        j--;
    }
    Main[j+1] = last;

}


std::vector<int> MainChainPartners(std::vector<int> &MainChain)
{
    std::vector<int> partners;
    for(int i = 0; i < (int)MainChain.size();i++)
        partners.push_back(MainChain[i]);
    return partners;
}
std::vector<int> JacobSthalAlgo(std::vector<int> &pend,std::vector<int> &MainChain)
{
 
    std::vector<int> JacobSthal;

    JacobSthal.push_back(0);
    JacobSthal.push_back(1);

    for(int i = 1; i < (int)pend.size();i++)
    {
        int n = JacobSthal.size();
        int next = JacobSthal[n - 1] + 2 * JacobSthal[n - 2];
        JacobSthal.push_back(next);
    }
    return JacobSthal;
}

std::vector<int> IndicesJacobSthal(std::vector<int> &JacobSthal,std::vector<int> &pend)
{
    std::vector<int> Groupes;

    for(int i = 0; i < (int)JacobSthal.size();i++)
    {
        int previous = JacobSthal[i - 1];
        int current = JacobSthal[i];

        int start = std::min(current,(int)pend.size() - 1);

        for(int j = start;j > previous;j--)
        Groupes.push_back(j);
    }
    return Groupes;
}


std::vector<int> mergeInsertSortVector(std::vector<int> &v)
{
    if(v.size() <= 1)
        return v;
    bool hasOdd = false;
    int OddValue = 0;
    std::vector<std::pair<int,int> > pairs = MakePairs(v,hasOdd,OddValue);
   
    clock_t start,end;

    // Speare MainChian and pend
    std::vector<int> MainChain;
    std::vector<int> pend;
    for(size_t i = 0; i < pairs.size();i++)
    {
        MainChain.push_back(pairs[i].first);
        pend.push_back(pairs[i].second);
    }

    // sort MainChain
    int n = MainChain.size();
    Recursion(MainChain,n);


    start = clock();

    // insert first element pend in MainChain
    int firstPend = -1;
    for(size_t i = 0; i < pairs.size();i++)
    {
        if(pairs[i].first == MainChain[0])
        {
            firstPend = pairs[i].second;
            break;
        }
    }
    
    // main chain original
    std::vector<int> partners = MainChainPartners(MainChain);
    MainChain.insert(MainChain.begin(),firstPend);
    //suite JacobSthal
    std::vector<int> JacobSthal = JacobSthalAlgo(pend,MainChain);
    // Creer des groupes 
    std::vector<int> Groupes = IndicesJacobSthal(JacobSthal,pend);
   

    // Inseret element avec binary search
    for(int i = 0; i < (int)Groupes.size();i++)
    {
        int index = Groupes[i];
        int ValueToInsert = -1;
        for(size_t k =  0; k < pairs.size();k++)
        {
            if(pairs[k].first == partners[index])
            {
                ValueToInsert= pairs[k].second;
                break;
            }
        }

        std::vector<int>::iterator limit = std::find(MainChain.begin(),MainChain.end(),partners[index]);

        std::vector<int>::iterator pos = binarysearch(MainChain,ValueToInsert,limit);

        MainChain.insert(pos,ValueToInsert);
    }

    // inserer element impaire if exist
    if(hasOdd)
    {
        std::vector<int>::iterator value = binarysearch(MainChain,OddValue,MainChain.end());
        MainChain.insert(value,OddValue);
    }

    //apres merge sort
    std::cout << "After: ";
    for(size_t i = 0; i < MainChain.size();i++)
        std::cout << " " << MainChain[i] <<  " ";
    std::cout <<"\n";
    
    end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC * 1000000;
    std::cout << "Time to process a range of " << v.size() << " elements with std::vector :  " << 
    time << " us"  << std::endl;

    return MainChain;
}

