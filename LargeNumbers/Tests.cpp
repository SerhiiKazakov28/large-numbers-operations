#include <iostream>
#include "LargeNumOperations.h"

using namespace std;

int main()
{
    LargeNumber op1, op2, res;
    string testHex1, testHex2;
    cout << "setHex() getHex() test" << endl;
    testHex1 = "d182aed568b01fee105557a1d173791c798030db267cf94e17102b94dcbbda3c";
    cout << "Initial hex:\t\t" << testHex1 << endl;
    op1.setHex(testHex1);
    cout << "getHex method result:\t" << op1.getHex() << endl;
    cout << (testHex1.compare(op1.getHex()) ? "Hexes are not equal" : "Hexes are equal") << endl;
    testHex1 = "6ae664e45ee80745574e2f5ab80";
    cout << "Initial hex:\t\t" << testHex1 << endl;
    op1.setHex(testHex1);
    cout << "getHex method result:\t" << op1.getHex() << endl;
    cout << (testHex1.compare(op1.getHex()) ? "Hexes are not equal" : "Hexes are equal") << endl;

    cout << "\nBitwise operations test\nInversion:" << endl;
    testHex1 = "de04661e39b16be9fe952f6eaf579a819ae29f63eae7d49f1024b566cb5a253a";
    cout << "Initial hex:\t" << testHex1 << endl;
    op1.setHex(testHex1);
    op1 = INV(op1);
    cout << "Inversed:\t" << op1.getHex() << endl;
    op1 = INV(op1);
    cout << "Inversed again:\t" << op1.getHex() << endl;
    cout << (testHex1.compare(op1.getHex()) ? "Hexes are not equal" : "Hexes are equal") << endl;

    testHex1 = "51bf608414ad5726a3c1bec098f77b1b54ffb2787f8d528a74c1d7fde6470ea4";
    testHex2 = "403db8ad88a3932a0b7e8189aed9eeffb8121dfac05c3512fdb396dd73f6331c";
    cout << "\nXOR\nInitial hex1:\t" << testHex1 << "\nInitial hex2:\t" << testHex2 << endl;
    op1.setHex(testHex1);
    op2.setHex(testHex2);
    res = XOR(op1, op2);
    cout << "XOR result:\t" << res.getHex() << endl;
    op1 = XOR(res, op2);
    cout << "XOR Result with Initial hex2 to get Initial hex1 back:\n" << op1.getHex() << endl;
    cout << (testHex1.compare(op1.getHex()) ? "Hexes are not equal" : "Hexes are equal") << endl;

    testHex1 = "528a74c1d7fde6470ea4";
    testHex2 = "c05c3512fdb396dd73f6331c";
    cout << "\nOR\nInitial hex1:\t" << testHex1 << "\nInitial hex2:\t" << testHex2 << endl;
    op1.setHex(testHex1);
    op2.setHex(testHex2);
    res = OR(op1, op2);
    cout << "OR result:\t" << res.getHex() << endl;

    testHex1 = "93864f939ccaca0380eb645e640da2079e4840aa55de404529a5b22be3c02152";
    testHex2 = "426b6713096880e";
    cout << "\nAND\nInitial hex1:\t" << testHex1 << "\nInitial hex2:\t" << testHex2 << endl;
    op1.setHex(testHex1);
    op2.setHex(testHex2);
    res = AND(op1, op2);
    cout << "AND result:\t" << res.getHex() << endl;

    testHex1 = "859dadece93ae8005872562625943274c37b81377f92501c0b760b2577c68195";
    cout << "\nShift right\nInitial hex:\t" << testHex1 << endl;
    op1.setHex(testHex1);    
    res = RShift(op1, 24);
    cout << "Shift on 24 bits:  " << res.getHex() << endl;
    res = RShift(op1, 252);
    cout << "Shift on 252 bits: " << res.getHex() << endl;
   
    cout << "\nShift left\nInitial hex:\t" << testHex1 << endl;
    res = LShift(op1, 33);
    cout << "Shift on 33 bits:  " << res.getHex() << endl;
    res = LShift(op1, 192);
    cout << "Shift on 192 bits: " << res.getHex() << endl;

    cout << "\nArithmetic operations test\nAddition and substraction:" << endl;
    testHex1 = "36f028580bb02cc8272a9a020f4200e346e276ae664e45ee80745574e2f5ab80";
    testHex2 = "70983d692f648185febe6d6fa607630ae68649f7e6fc45b94680096c06e4fadb";
    cout << "Initial hex1:\t" << testHex1 << "\nInitial hex2:\t" << testHex2 << endl;
    op1.setHex(testHex1);
    op2.setHex(testHex2);
    res = ADD(op1, op2);
    cout << "hex1 + hex2:\t" << res.getHex() << endl;
    cout << "Previous result - hex2 to get hex1" << endl;
    op1 = SUB(res, op2);
    cout << "Result: " << op1.getHex() << endl;
    cout << (testHex1.compare(op1.getHex()) ? "Hexes are not equal" : "Hexes are equal") << endl;

    cout << "\nSubstraction and addition:" << endl;
    testHex1 = "33ced2c76b26cae94e162c4c0d2c0ff7c13094b0185a3c122e732d5ba77efebc";
    testHex2 = "22e962951cb6cd2ce279ab0e2095825c141d48ef3ca9dabf253e38760b57fe03";
    cout << "Initial hex1:\t" << testHex1 << "\nInitial hex2:\t" << testHex2 << endl;
    op1.setHex(testHex1);
    op2.setHex(testHex2);
    res = SUB(op1, op2);
    cout << "hex1 - hex2:\t" << res.getHex() << endl;
    cout << "Previous result + hex2 to get hex1" << endl;
    op1 = ADD(res, op2);
    cout << "Result: " << op1.getHex() << endl;
    cout << (testHex1.compare(op1.getHex()) ? "Hexes are not equal" : "Hexes are equal") << endl;
}