#include "primality.h"

#include<random>

#include<ctime>

using namespace std;

std::mt19937 mt_rand(std::random_device {}());

long long getRandomIntNumber() {

   long long value = mt_rand();

   return value;

}

void getRandomNrMare(NrMare n, int len) {

   n[0] = len;

   for (int i = 1; i <= n[0]; i++)
      n[i] = getRandomIntNumber() % BASE;

}

int randomBaseDigit() {

   // returns a random digit in base BASE;

   return getRandomIntNumber() % BASE;

}

void randomCandidate(NrMare p, int bits) {

   int limbs = (bits + 26) / 27;

   p[0] = limbs;
   for (int i = 1; i <= limbs; i++) {
      p[i] = randomBaseDigit();
   }

   p[1] |= 1;

}

void randomNumber(NrMare a, NrMare n) {

   // generates a random number between 2 and n-2; answer stored a

   NrMare q, r;

   NrMare doi;
   AtribMic(doi, 2);
   NrMare patru;
   AtribMic(patru, 4);

   NrMare n4;
   AtribMare(n4, n);
   Scadere(n4, patru);

   getRandomNrMare(a, 3);
   divideMare(a, n4, q, r);
   AtribMare(a, r);
   Adunare(a, doi);

}

bool MillerTest(NrMare d, NrMare n) {
   NrMare dd;
   AtribMare(dd, d);

   NrMare a;
   randomNumber(a, n);

   NrMare x;
   AtribMare(x, a);
   Expo(x, dd, n);

   NrMare unu;
   AtribMic(unu, 1);

   NrMare doi;
   AtribMic(doi, 2);

   NrMare n1;
   AtribMare(n1, n);
   Scadere(n1, unu);

   if (Compara(x, unu) == 0 ||
      Compara(x, n1) == 0)
      return true;

   while (Compara(dd, n1) != 0) {
      Expo(x, doi, n);

      ProdusMic(dd, 2);

      if (Compara(x, unu) == 0)
         return false;

      if (Compara(x, n1) == 0)
         return true;
   }

   return false;
}

bool Par(NrMare n) {

   NrMare nn;
   AtribMare(nn, n);

   if (Divide(nn, 2) == 0)
      return true;
   return false;

}

bool isPrime(NrMare n, int k) {

   NrMare unu;
   AtribMic(unu, 1);
   NrMare trei;
   AtribMic(trei, 3);
   NrMare patru;
   AtribMic(patru, 4);

   if (Compara(n, unu) < 1 || Compara(n, patru) == 0)
      return false;
   if (Compara(n, trei) < 1)
      return true;

   NrMare d;
   AtribMare(d, n);
   Scadere(d, unu);

   while (Par(d))
      Divide(d, 2);

   for (int i = 0; i < k; i++) {
      if (!MillerTest(d, n))
         return false;
   }

   return true;

}

bool quickCompositeCheck(NrMare n){
    static const int small_primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
        43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127,
        131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211,
        223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307,
        311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401,
        409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499,
        503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607,
        613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709,
        719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823,
        827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937,
        941, 947, 953, 967, 971, 977, 983, 991, 997 };
        for(int p : small_primes){
            NrMare tmp; AtribMare(tmp, n);
            if(Divide(tmp, p) == 0) return true;
        }
        return false;
}

void randomPrime64(NrMare n){

    randomCandidate(n, 64);

    while(quickCompositeCheck(n) || !isPrime(n, 5)){
        randomCandidate(n, 64);
    }
}
