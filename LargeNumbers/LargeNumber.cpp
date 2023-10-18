#include "LargeNumber.h"

std::string appendZeros(size_t quantity) {
    std::string res;
    for (size_t i = 0; i < 16 - quantity; i++)
    {
        res += "0";
    }
    return res;
}

void LargeNumber::setHex(std::string hexStr)
{
    short mod = hexStr.size() % 16;
    unsigned long long part;
    std::stringstream ss;
    numberVector.clear();
    if (mod) {
        ss << hexStr.substr(0, mod);
        ss >> std::hex >> part;
        if (part) numberVector.push_back(part);
        hexStr = hexStr.substr(mod);
        ss.str("");
        ss.clear();
    }
    for (size_t i = 0; i < hexStr.size() / 16; ++i)
    {
        ss << hexStr.substr(i * 16, 16);
        ss >> std::hex >> part;
        if (numberVector.size() || part) numberVector.push_back(part);
        ss.str("");
        ss.clear();
    }
    if (!numberVector.size()) numberVector.push_back(0);
}

std::string LargeNumber::getHex()
{
    std::string hexStr;
    std::stringstream ss;
    for (size_t i = 0; i < numberVector.size(); i++) {
        ss << std::hex << numberVector[i];
        if (i) hexStr += appendZeros(ss.str().size()) + ss.str();
        else hexStr = ss.str();
        ss.str("");
        ss.clear();
    }
    return hexStr;
}

std::vector<unsigned long long> LargeNumber::getNumVector()
{
    return numberVector;
}
