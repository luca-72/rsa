#pragma once

const int BASE = 1e8;
const int NN = 100;

typedef long long NrMare[NN];

void AtribMic(NrMare x, int n);
void AtribMare(NrMare dest, NrMare src);
int Compara(NrMare x, NrMare y);
void Adunare(NrMare x, NrMare y);
void Scadere(NrMare x, NrMare y);
void ProdusMic(NrMare x, int n);
int Divide(NrMare x, int n);
void ProdusMare(NrMare x, NrMare y);
void Afis(NrMare A);
void divideMare(NrMare A, NrMare B, NrMare Q, NrMare R);
void Expo(NrMare a, NrMare n, NrMare MOD);
void euclid(NrMare a, NrMare b, NrMare x, NrMare y, NrMare MOD);
void invers_modular(NrMare A, NrMare MOD, NrMare rez);
