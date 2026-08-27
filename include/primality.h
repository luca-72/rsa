#pragma once

#include "bigint.h"

long long getRandomIntNumber();
void getRandomNrMare(NrMare n, int len);
int randomBaseDigit();
void randomCandidate(NrMare p, int bits);
void randomNumber(NrMare a, NrMare n);
bool MillerTest(NrMare d, NrMare n);
bool Par(NrMare n);
bool isPrime(NrMare n, int k);
bool quickCompositeCheck(NrMare n);
void randomPrime64(NrMare n);

