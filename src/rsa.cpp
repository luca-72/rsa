#include "rsa.h"

#include "bigint.h"

#include "primality.h"

#include<random>

#include<ctime>

#include<string>

#include<iostream>

using namespace std;

string stringToString10(string s) {

   int i, lg1, lg2 = 0, nr, lgnr, j;
   string rez, aux;

   lg1 = s.size();

   for (i = 0; i < lg1; i++) {

      nr = int((unsigned char) s[i]); 

      lgnr = 0;
      aux.clear();

      while (nr) {
         lgnr++;
         aux.push_back(char(nr % 10 + '0')); 
         nr /= 10;
      }

      rez.push_back(char(lgnr + '0'));
      for (j = aux.size() - 1; j >= 0; j--)
         rez.push_back(aux[j]);

   }

   return rez;

}

void string10ToBigInt(NrMare rez, string s) {

   smallAssign(rez, 0);
   rez[0] = 0;

   int i, lg = s.size(), j, aux;

   for (i = lg - 1; i >= 0; i -= 8) {

      aux = 0;

      for (j = i - 7; j <= i; j++) {

         if (j >= 0)
            aux = aux * 10 + (s[j] - '0');

      }

      rez[++rez[0]] = aux;

   }

}

string BigIntToString10(NrMare a) {

   int i, j;
   string rez, aux;
   NrMare aa;

   bigAssign(aa, a);

   for (i = a[0]; i > 0; i--) {
      aux.clear();
      while (a[i]) {
         aux.push_back(char(a[i] % 10 + '0'));
         a[i] /= 10;
      }

      if (i != a[0]) // every limb except the top one
         while (aux.size() < 8)
            aux.push_back('0'); // must be exactly 8 digits

      for (j = aux.size() - 1; j >= 0; j--)
         rez.push_back(aux[j]);
   }

   bigAssign(a, aa);

   return rez;

}

string string10ToString(string s) {

   string rez;
   int i, lg = s.size(), j, aux, len;

   for (i = 0; i < lg; i++) {

      aux = 0;
      len = s[i] - '0';

      for (j = i + 1; j <= i + len; j++) {
         aux = aux * 10 + (s[j] - '0');
      }

      i = j - 1;

      rez.push_back(char(aux));

   }

   return rez;

}

void read(NrMare message, string s) {

   s = stringToString10(s);
   string10ToBigInt(message, s);

}

void write(NrMare a) {

   string s;

   s = BigIntToString10(a);
   s = string10ToString(s);

   cout << s;

}

NrMare p, N, p1, q1, p2, phi, phi2, d, e;

void setup() {

   smallAssign(e, 65537);

   NrMare phi22, e2, q, r, aux;

   NrMare doi;
   smallAssign(doi, 2);
   NrMare unu;
   smallAssign(unu, 1);
   NrMare zero;
   smallAssign(zero, 0);

   while (true) {

      randomPrime64(p); 
      randomPrime64(q); 
      bigAssign(N, p);
      bigProduct(N, q);

      bigAssign(p1, p);
      substract(p1, unu);
      bigAssign(q1, q);
      substract(q1, unu);
      bigAssign(p2, p);
      substract(p2, doi);

      bigAssign(phi, p1);
      bigProduct(phi, q1);

      bigAssign(phi22, phi);
      bigAssign(e2, e);

      bigDivide(phi22, e2, q, r);

      if (compare(r, zero) != 0)
         break;

   }

   bigAssign(phi2, phi);
   substract(phi2, doi);

   bigAssign(d, e);

   modularInverse(d, phi, aux);
   bigAssign(d, aux); 

}

void encrypt(NrMare ct, string s) {

   NrMare message;

   read(message, s);

   bigAssign(ct, message);
   fastExponentiation(ct, e, N);

}

void decrypt(NrMare pt, NrMare ct) {

   bigAssign(pt, ct);
   fastExponentiation(pt, d, N);

}

void display(){

    cout << "public modulus N : "; print(N); cout << "\n";
    cout << "Euler's totient of N : "; print(phi); cout << "\n";
    cout << "public exponent : "; print(e); cout << "\n";

}