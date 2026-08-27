#pragma once

const int BASE = 1e8;
const int NN = 100;

typedef long long NrMare[NN];

void smallAssign(NrMare x, int n);
void bigAssign(NrMare dest, NrMare src);
int compare(NrMare x, NrMare y);
void add(NrMare x, NrMare y);
void substract(NrMare x, NrMare y);
void smallProduct(NrMare x, int n);
int smallDivide(NrMare x, int n);
void bigProduct(NrMare x, NrMare y);
void print(NrMare A);
void bigDivide(NrMare A, NrMare B, NrMare Q, NrMare R);
void fastExponentiation(NrMare a, NrMare n, NrMare MOD);
void euclid(NrMare a, NrMare b, NrMare x, NrMare y, NrMare MOD);
void modularInverse(NrMare A, NrMare MOD, NrMare rez);
