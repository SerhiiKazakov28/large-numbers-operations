#pragma once
#include "LargeNumber.h"

LargeNumber INV(LargeNumber num);
LargeNumber XOR(LargeNumber numA, LargeNumber numB);
LargeNumber OR(LargeNumber numA, LargeNumber numB);
LargeNumber AND(LargeNumber numA, LargeNumber numB);

unsigned long long makeMask(size_t size);
unsigned long long carryMask(unsigned long long carry, size_t size, char mode);

LargeNumber RShift(LargeNumber num, size_t shift);
LargeNumber LShift(LargeNumber num, size_t shift);

LargeNumber ADD(LargeNumber numA, LargeNumber numB);
LargeNumber SUB(LargeNumber numA, LargeNumber numB);