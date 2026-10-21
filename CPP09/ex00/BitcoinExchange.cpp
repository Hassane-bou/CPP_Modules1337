#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    std::ifstream Filedata("data.csv");
    std::string line;

    if(!Filedata.is_open())
    {
        std::cout << "Error: cannot open file data.csv" << std::endl;
        std::exit(1); 
    }
    std::getline(Filedata,line);
    if(line.empty())
    {
        std::cout << "Error: file Data.cvs is empty" << std::endl;
        std::exit(1);
    }
    while(std::getline(Filedata,line))
    {
        if(line.empty())
            continue;
        size_t separ = line.find(',');

        std::string data = line.substr(0,separ);
        std::string rate = line.substr(separ +1);

        float value = std::stof(rate);

        _data[data] = value;

    }
    Filedata.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &obj)
{
    *this = obj;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &obj)
{
    if(this != &obj)
        this->_data = obj._data;
    return *this;
}

BitcoinExchange::~BitcoinExchange() { }


int CheckDateValide(std::string date)
{

    if(date.size() != 10)
    {
        std::cout << "Error: bad size input => " << date << std::endl;
        return 0;
    }

    if(date[4] != '-' || date[7] != '-')
    {
        std::cout << "Error: bad input => " << date << std::endl;
        return 0;
    }
    for(int i = 0; i < 4;i++)
    {
        if(!std::isdigit(date[i]))
        { 
            std::cout << "Error: bad input => " << date << std::endl;
            return 0;
        }

    }
    for(int i = 5; i < 7;i++)
    {
        if(!std::isdigit(date[i]))
        {
            std::cout << "Error: bad input => " << date << std::endl;
            return 0;
        }

    }
    for(int i = 8; i < 10 ; i++)
    {
        if(!std::isdigit(date[i]))
        {
            std::cout << "Error: bad input => " << date << std::endl;
            return 0;
        }

    }

    int M = std::atoi(date.substr(5,2).c_str());
    int D = std::atoi(date.substr(8,2).c_str());

    if(M <= 0 || M > 12 || D <= 0 || D > 31)
    {
        std::cout << "Error: bad input => " << date << std::endl;
        return 0;
    }
    return 1;
}
int CheckValueValide(std::string value)
{
    int i = 0;
    int flage = 0;

    if(value.empty())
        return 0;
    if(value[0] == '-')
        i = 1;
    while(value[i])
    {
        if(value[i] == '.')
        {
            flage++;
        }
        else if(!(std::isdigit(value[i])))
        {
            std::cout << "Error: Value is not digit ";
            return 0;
        }
        if(flage > 1)
        {
            std::cout << "Error: is not float value ";
            return 0;
        }
        i++;
    }
    return 1;
}

void BitcoinExchange::RunFile(const std::string file)
{
    std::ifstream Inputfile(file);
    std::string line;

    if(!Inputfile.is_open())
    {
        std::cout << "Error: cannot open the file input.txt" << std::endl;
        return;
    }

    std::getline(Inputfile,line);
    if(line != "date | value")
    {
        std::cout << "Error: invalid file format\n";
        return;
    }
    while(std::getline(Inputfile,line))
    {
        size_t sep = line.find('|');
        if(sep == std::string::npos)
        {
            std::cout << "Error: bad input " << " => " << line << std::endl;
            continue;
        }
        std::string date = line.substr(0,sep);
        while(!date.empty() && date[date.size() - 1] == ' ')
            date.erase(date.size() - 1);
        if(CheckDateValide(date) == 0)
        {
            continue ;
        }
        std::string value = line.substr(sep + 1);
        while(!value.empty() && value[0] == ' ')
            value.erase(0,1);
        if((CheckValueValide(value)) == 0)
        {
            std::cout << " => " << value << std::endl;
            continue;
        }
        float realvalue;
        std::string str = value;
        std::stringstream ss(str);
        ss >> realvalue;

        if(realvalue < 0)
        {
            std::cout << "Error: not a positive number." << std::endl;
            continue;
        }
        if(realvalue > 1000)
        {
            std::cout << "Error: too large a number.\n";
            continue; 
        }

        std::map<std::string ,float>::iterator it = _data.lower_bound(date);
        
        if(it == _data.end() || it->first != date)
            it--;
        else if(it == _data.begin() && it->first != date)
        {
            std::cout << "Error: bad input => " << date << std::endl;
            continue;
        }

        std::cout << date << " => "  << realvalue << " = " << realvalue * it->second << std::endl;

    }
    Inputfile.close();
}