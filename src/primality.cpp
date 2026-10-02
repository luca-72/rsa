#include "primality.h"

#include<random>

#include<ctime>

using namespace std;

std::mt19937 mt_rand(std::random_device {}());

long long getRandomIntNumber() {

   long long value = mt_rand();

   return value;

}

void getRandomBigInt(BigInt n, int len) {

   n[0] = len;

   for (int i = 1; i <= n[0]; i++)
      n[i] = getRandomIntNumber() % BASE;

}

int randomBaseDigit() {

   // returns a random digit in base BASE;

   return getRandomIntNumber() % BASE;

}

void randomCandidate(BigInt p, int bits) {

   int limbs = (bits + 26) / 27;

   p[0] = limbs;
   for (int i = 1; i <= limbs; i++) {
      p[i] = randomBaseDigit();
   }

   p[1] |= 1;

}

void randomNumber(BigInt a, BigInt n) {

   // generates a random number between 2 and n-2; answer stored a

   BigInt q, r;

   BigInt doi;
   smallAssign(doi, 2);
   BigInt patru;
   smallAssign(patru, 4);

   BigInt n4;
   bigAssign(n4, n);
   substract(n4, patru);

   getRandomBigInt(a, 3);
   bigDivide(a, n4, q, r);
   bigAssign(a, r);
   add(a, doi);

}

bool MillerTest(BigInt d, BigInt n) {
   BigInt dd;
   bigAssign(dd, d);

   BigInt a;
   randomNumber(a, n);

   BigInt x;
   bigAssign(x, a);
   fastExponentiation(x, dd, n);

   BigInt unu;
   smallAssign(unu, 1);

   BigInt doi;
   smallAssign(doi, 2);

   BigInt n1;
   bigAssign(n1, n);
   substract(n1, unu);

   if (compare(x, unu) == 0 ||
      compare(x, n1) == 0)
      return true;

   while (compare(dd, n1) != 0) {
      fastExponentiation(x, doi, n);

      smallProduct(dd, 2);

      if (compare(x, unu) == 0)
         return false;

      if (compare(x, n1) == 0)
         return true;
   }

   return false;
}

bool isEven(BigInt n) {

   BigInt nn;
   bigAssign(nn, n);

   if (smallDivide(nn, 2) == 0)
      return true;
   return false;

}

bool isPrime(BigInt n, int k) {

   BigInt unu;
   smallAssign(unu, 1);
   BigInt trei;
   smallAssign(trei, 3);
   BigInt patru;
   smallAssign(patru, 4);

   if (compare(n, unu) < 1 || compare(n, patru) == 0)
      return false;
   if (compare(n, trei) < 1)
      return true;

   BigInt d;
   bigAssign(d, n);
   substract(d, unu);

   while (isEven(d))
      smallDivide(d, 2);

   for (int i = 0; i < k; i++) {
      if (!MillerTest(d, n))
         return false;
   }

   return true;

}

bool quickCompositeCheck(BigInt n){
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
            BigInt tmp; bigAssign(tmp, n);
            if(smallDivide(tmp, p) == 0) return true;
        }
        return false;
}

void randomPrime64(BigInt n){

    randomCandidate(n, 512);

    while(quickCompositeCheck(n) || !isPrime(n, 5)){
        randomCandidate(n, 512);
    }
}
