#pragma once

const int BASE = 1e8;
const int NN = 100;

typedef long long BigInt[NN];

void smallAssign(BigInt x, int n);
void bigAssign(BigInt dest, BigInt src);
int compare(BigInt x, BigInt y);
void add(BigInt x, BigInt y);
void substract(BigInt x, BigInt y);
void smallProduct(BigInt x, int n);
int smallDivide(BigInt x, int n);
void bigProduct(BigInt x, BigInt y);
void print(BigInt A);
void bigDivide(BigInt A, BigInt B, BigInt Q, BigInt R);
void fastExponentiation(BigInt a, BigInt n, BigInt MOD);
void euclid(BigInt a, BigInt b, BigInt x, BigInt y, BigInt MOD);
void modularInverse(BigInt A, BigInt MOD, BigInt rez);
