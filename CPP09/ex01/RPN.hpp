#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>

class RPN
{
    private:
        std::stack <int> tokens;
        RPN();
    public:
        RPN(std::string value);
        ~RPN();
        RPN(const RPN &obj);
        RPN& operator=(const RPN &obj);

};
    int NumberAndOpeartorValide(std::string input);
    int checkNumber(std::string input);
    

