#include "LargeNumOperations.h"

LargeNumber INV(LargeNumber num)
{
    LargeNumber res;
    std::string hexStr;
    std::stringstream ss;
    std::vector<unsigned long long> vec = num.getNumVector();
    for (unsigned long long part : vec) {
        ss << std::hex << ~part;
        hexStr += appendZeros(ss.str().size()) + ss.str();
        ss.str("");
        ss.clear();
    }
    res.setHex(hexStr);
    return res;
}

LargeNumber XOR(LargeNumber numA, LargeNumber numB)
{
    LargeNumber res;
    std::string hexStr;
    std::stringstream ss;
    std::vector<unsigned long long> vecA = numA.getNumVector(), vecB = numB.getNumVector();
    size_t partsToOp, i;
    bool isALarger = vecA.size() > vecB.size();
    if (isALarger) partsToOp = vecB.size();
    else partsToOp = vecA.size();
    for (i = 1; i <= partsToOp; i++) {
        ss << std::hex << (vecA[vecA.size() - i] ^ vecB[vecB.size() - i]);
        hexStr = appendZeros(ss.str().size()) + ss.str() + hexStr;
        ss.str("");
        ss.clear();
    }
    if (isALarger)
    {
        for (i = vecA.size() - vecB.size(); i > 0; i--)
        {
            ss << std::hex << (vecA[i - 1]);
            hexStr = appendZeros(ss.str().size()) + ss.str() + hexStr;
            ss.str("");
            ss.clear();
        }
    }
    else if (vecA.size() != vecB.size()) {
        for (i = vecB.size() - vecA.size(); i > 0; i--)
        {
            ss << std::hex << (vecB[i - 1]);
            hexStr = appendZeros(ss.str().size()) + ss.str() + hexStr;
            ss.str("");
            ss.clear();
        }
    }
    res.setHex(hexStr);
    return res;
}

LargeNumber OR(LargeNumber numA, LargeNumber numB)
{
    LargeNumber res;
    std::string hexStr;
    std::stringstream ss;
    std::vector<unsigned long long> vecA = numA.getNumVector(), vecB = numB.getNumVector();
    size_t partsToOp, i;
    bool isALarger = vecA.size() > vecB.size();
    if (isALarger) partsToOp = vecB.size();
    else partsToOp = vecA.size();
    for (i = 1; i <= partsToOp; i++) {
        ss << std::hex << (vecA[vecA.size() - i] | vecB[vecB.size() - i]);
        hexStr = appendZeros(ss.str().size()) + ss.str() + hexStr;
        ss.str("");
        ss.clear();
    }
    if (isALarger)
    {
        for (i = vecA.size() - vecB.size(); i > 0; i--)
        {
            ss << std::hex << (vecA[i - 1]);
            hexStr = appendZeros(ss.str().size()) + ss.str() + hexStr;
            ss.str("");
            ss.clear();
        }
    }
    else if (vecA.size() != vecB.size()) {
        for (i = vecB.size() - vecA.size(); i > 0; i--)
        {
            ss << std::hex << (vecB[i - 1]);
            hexStr = appendZeros(ss.str().size()) + ss.str() + hexStr;
            ss.str("");
            ss.clear();
        }
    }
    res.setHex(hexStr);
    return res;
}

LargeNumber AND(LargeNumber numA, LargeNumber numB)
{
    LargeNumber res;
    std::string hexStr;
    std::stringstream ss;
    std::vector<unsigned long long> vecA = numA.getNumVector(), vecB = numB.getNumVector();
    size_t partsToOp, i;
    partsToOp = (vecA.size() > vecB.size()) ? vecB.size() : vecA.size();
    for (i = 1; i <= partsToOp; i++) {
        ss << std::hex << (vecA[vecA.size() - i] & vecB[vecB.size() - i]);
        hexStr = appendZeros(ss.str().size()) + ss.str() + hexStr;
        ss.str("");
        ss.clear();
    }
    res.setHex(hexStr);
    return res;
}

unsigned long long makeMask(size_t size) {
    if (!size) return 0;
    std::stringstream ss;
    std::string maskStr;
    unsigned long long mask;
    switch (size % 4) {
    case 1:
        maskStr = "1";
        break;
    case 2:
        maskStr = "3";
        break;
    case 3:
        maskStr = "7";
        break;
    default:
        break;
    }
    for (size_t i = 0; i < size / 4; i++) maskStr += "F";
    ss << maskStr;
    ss >> std::hex >> mask;
    return mask;
}

unsigned long long carryMask(unsigned long long carry, size_t size, char mode) {
    if (!carry) return 0;
    std::stringstream ss;
    std::string maskStr;
    unsigned long long mask;
    if (mode == 'l')
        return carry;
    else if (mode == 'r') {
        ss << std::hex << carry;
        maskStr = ss.str();
        for (size_t i = 0; i < 16 - size / 4; i++) maskStr += "0";
        ss.str("");
        ss.clear();
        ss << maskStr;
        ss >> std::hex >> mask;
        return mask;
    }
}

LargeNumber RShift(LargeNumber num, size_t shift)
{
    LargeNumber res;
    std::string hexStr;
    std::stringstream ss;
    std::vector<unsigned long long> numVector = num.getNumVector();
    while (shift / 64)
    {
        if (!numVector.empty()) numVector.pop_back();
        shift -= 64;
    }
    unsigned long long mask = makeMask(shift), carryNew, carryOld = 0;
    for (unsigned long long part : numVector) {
        carryNew = part & mask;
        part = part >> shift;
        part |= carryMask(carryOld, shift, 'r');
        carryOld = carryNew;
        ss << std::hex << part;
        hexStr += appendZeros(ss.str().size()) + ss.str();
        ss.str("");
        ss.clear();
    }
    res.setHex(hexStr);
    return res;
}

LargeNumber LShift(LargeNumber num, size_t shift)
{
    LargeNumber res;
    std::string hexStr;
    std::stringstream ss;
    std::vector<unsigned long long> numVector = num.getNumVector(), resizedVector;
    size_t partsToDel = shift / 64;
    if (partsToDel < numVector.size())
    {
        if (partsToDel) {
            resizedVector = { numVector.begin() + partsToDel, numVector.end() };
            shift %= 64;
            numVector = resizedVector;
            while (partsToDel)
            {
                hexStr += appendZeros(0);
                partsToDel--;
            }
        }
        unsigned long long mask = makeMask(shift), carryNew, carryOld = 0;
        for (size_t i = numVector.size(); i > 0; i--) {
            carryNew = numVector[i - 1] >> (64 - shift) & mask;
            numVector[i - 1] = numVector[i - 1] << shift;
            numVector[i - 1] |= carryMask(carryOld, shift, 'l');
            carryOld = carryNew;
            ss << std::hex << numVector[i - 1];
            hexStr = appendZeros(ss.str().size()) + ss.str() + hexStr;
            ss.str("");
            ss.clear();
        }
    }
    res.setHex(hexStr);
    return res;
}

LargeNumber ADD(LargeNumber numA, LargeNumber numB)
{
    LargeNumber res;
    std::string hexStr;
    std::stringstream ss;
    unsigned long long partRes;
    bool carry = 0;
    std::vector<unsigned long long> vecA = numA.getNumVector(), vecB = numB.getNumVector();
    size_t partsToOp, i;
    partsToOp = (vecA.size() > vecB.size()) ? vecB.size() : vecA.size();
    for (i = 1; i <= partsToOp; i++) {
        partRes = vecA[vecA.size() - i] + vecB[vecB.size() - i] + carry;
        carry = (partRes < std::max(vecA[vecA.size() - i], vecB[vecB.size() - i])) ? 1 : 0;
        ss << std::hex << partRes;
        hexStr = appendZeros(ss.str().size()) + ss.str() + hexStr;
        ss.str("");
        ss.clear();
    }
    if (vecA.size() > vecB.size())
    {
        for (i = vecA.size() - vecB.size(); i > 0; i--)
        {
            ss << std::hex << (vecA[i - 1] + carry);
            hexStr = appendZeros(ss.str().size()) + ss.str() + hexStr;
            ss.str("");
            ss.clear();
            carry = false;
        }
    }
    else if (vecA.size() != vecB.size()) {
        for (i = vecB.size() - vecA.size(); i > 0; i--)
        {
            ss << std::hex << (vecB[i - 1] + carry);
            hexStr = appendZeros(ss.str().size()) + ss.str() + hexStr;
            ss.str("");
            ss.clear();
            carry = false;
        }
    }
    if (carry) hexStr = "1" + hexStr;
    res.setHex(hexStr);
    return res;
}

LargeNumber SUB(LargeNumber numA, LargeNumber numB)
{
    LargeNumber res;
    std::string hexStr;
    std::stringstream ss;
    unsigned long long partRes;
    bool carry = 0;
    std::vector<unsigned long long> vecA = numA.getNumVector(), vecB = numB.getNumVector();
    size_t partsToOp, i;
    partsToOp = (vecA.size() > vecB.size()) ? vecB.size() : vecA.size();
    for (i = 1; i <= partsToOp; i++) {
        partRes = vecA[vecA.size() - i] - vecB[vecB.size() - i] - carry;
        carry = (partRes > vecA[vecA.size() - i]) ? 1 : 0;
        ss << std::hex << partRes;
        hexStr = appendZeros(ss.str().size()) + ss.str() + hexStr;
        ss.str("");
        ss.clear();
    }
    if (vecA.size() > vecB.size())
    {
        for (i = vecA.size() - vecB.size(); i > 0; i--)
        {
            ss << std::hex << (vecA[i - 1] - carry);
            hexStr = appendZeros(ss.str().size()) + ss.str() + hexStr;
            ss.str("");
            ss.clear();
            carry = false;
        }
    }
    else if (vecA.size() != vecB.size()) {
        for (i = vecB.size() - vecA.size(); i > 0; i--)
        {
            ss << std::hex << (vecB[i - 1] - carry);
            hexStr = appendZeros(ss.str().size()) + ss.str() + hexStr;
            ss.str("");
            ss.clear();
            carry = false;
        }
    }
    res.setHex(hexStr);
    return res;
}