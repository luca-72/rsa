#pragma once

#include "bigint.h"

long long getRandomIntNumber();
void getRandomBigInt(BigInt n, int len);
int randomBaseDigit();
void randomCandidate(BigInt p, int bits);
void randomNumber(BigInt a, BigInt n);
bool MillerTest(BigInt d, BigInt n);
bool isEven(BigInt n);
bool isPrime(BigInt n, int k);
bool quickCompositeCheck(BigInt n);
void randomPrime64(BigInt n);

