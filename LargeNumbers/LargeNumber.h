#pragma once
#include <string>
#include <vector>
#include <sstream>

class LargeNumber
{
private:
    std::vector <unsigned long long> numberVector;
public:
    void setHex(std::string hexStr);
    std::string getHex();
    std::vector<unsigned long long> getNumVector();
};

std::string appendZeros(size_t quantity);