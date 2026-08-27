#include "bigint.h"

#include<ctime>

#include<cstdio>

#include<algorithm>

#include<iostream>

using namespace std;

void smallAssign(NrMare x, int n) {
   for (int i = 0; i < NN; i++)
      x[i] = 0;

   if (n == 0) {
      x[0] = 1;
      x[1] = 0;
   } else {
      while (n) {
         x[++x[0]] = n % BASE;
         n /= BASE;
      }
   }
}

void bigAssign(NrMare dest, NrMare src) {
   int i;

   for (i = 0; i <= src[0]; i++)
      dest[i] = src[i];

   for (; i < NN; i++)
      dest[i] = src[i] = 0;
}

int compare(NrMare x, NrMare y) {
   int nx = x[0];
   int ny = y[0];

   while (nx > 1 && x[nx] == 0)
      nx--;

   while (ny > 1 && y[ny] == 0)
      ny--;

   if (nx < ny)
      return -1;

   if (nx > ny)
      return 1;

   while (nx > 0 && x[nx] == y[nx])
      nx--;

   if (nx == 0)
      return 0;

   if (x[nx] < y[nx])
      return -1;

   return 1;
}

void add(NrMare x, NrMare y){
   int n = max(x[0], y[0]);
   long long carry = 0;

   for (int i = 1; i <= n; i++) {
      long long sum = x[i] + y[i] + carry;
      x[i] = sum % BASE;
      carry = sum / BASE;
   }

   x[0] = n;

   if (carry)
      x[++x[0]] = carry;
}

void substract(NrMare x, NrMare y){
   long long borrow = 0;

   for (int i = 1; i <= x[0]; i++) {
      long long value = x[i] - y[i] - borrow;

      if (value < 0) {
         value += BASE;
         borrow = 1;
      } else
         borrow = 0;

      x[i] = value;
   }

   while (x[0] > 1 && x[x[0]] == 0)
      x[0]--;
}

void smallProduct(NrMare x, int n){
   long long carry = 0;

   for (int i = 1; i <= x[0]; i++) {
      long long value = 1LL * x[i] * n + carry;
      x[i] = value % BASE;
      carry = value / BASE;
   }

   while (carry) {
      x[++x[0]] = carry % BASE;
      carry /= BASE;
   }
}

int smallDivide(NrMare x, int n){
   long long rest = 0;

   for (int i = x[0]; i > 0; i--) {
      rest = rest * BASE + x[i];
      x[i] = rest / n;
      rest %= n;
   }

   while (x[0] > 1 && x[x[0]] == 0)
      x[0]--;

   return rest;
}

void bigProduct(NrMare x, NrMare y) {
   NrMare z;
   smallAssign(z, 0);

   z[0] = x[0] + y[0];

   for (int i = 1; i <= z[0]; i++)
      z[i] = 0;

   for (int i = 1; i <= x[0]; i++) {
      long long carry = 0;

      for (int j = 1; j <= y[0]; j++) {
         long long cur =
            z[i + j - 1] +
            1LL * x[i] * y[j] +
            carry;

         z[i + j - 1] = cur % BASE;
         carry = cur / BASE;
      }

      z[i + y[0]] += carry;
   }

   while (z[0] > 1 && z[z[0]] == 0)
      z[0]--;

   bigAssign(x, z);
}

void print(NrMare A) {

   cout << A[A[0]];

   for (int i = A[0] - 1; i > 0; i--)
      printf("%08lld", A[i]);

}

void bigDivide(NrMare A, NrMare B, NrMare Q, NrMare R) {

   int i, j;

   NrMare cur;
   smallAssign(cur, 0);

   Q[0] = A[0];

   for (i = 1; i <= Q[0]; i++)
      Q[i] = 0;

   for (i = A[0]; i > 0; i--) {

      if (cur[0] == 1 && cur[1] == 0)
         cur[0] = 0;

      if (cur[0] != 0)
         for (j = cur[0]; j >= 1; j--)
            cur[j + 1] = cur[j];

      cur[0]++;
      cur[1] = A[i];

      while (cur[cur[0]] == 0 && cur[0] > 1)
         cur[0]--;

      int digit = 0;

      // find the biggest digit for which digit*B <= cur is true

      int st, dr, mij;
      NrMare aux;
      st = 0;
      dr = BASE - 1;
      while (st <= dr) {
         mij = st + (dr - st) / 2;
         smallAssign(aux, mij);
         bigProduct(aux, B);
         if (compare(aux, cur) <= 0) {
            digit = mij;
            st = mij + 1;
         } else {
            dr = mij - 1;
         }
      }

      Q[i] = digit;

      smallAssign(aux, digit);
      bigProduct(aux, B);
      substract(cur, aux);

   }

   while (Q[Q[0]] == 0 && Q[0] > 1)
      Q[0]--;

   bigAssign(R, cur);

}

void fastExponentiation(NrMare a, NrMare n, NrMare MOD) {

   NrMare aa;
   bigAssign(aa, a);
   smallAssign(a, 1);
   NrMare i, ii;

   NrMare unu;
   smallAssign(unu, 1);
   NrMare doi;
   smallAssign(doi, 2);
   NrMare Q, R;

   for (bigAssign(i, n); compare(i, unu) != -1; smallDivide(i, 2)) {

      bigAssign(ii, i);

      smallAssign(doi, 2);
      bigDivide(ii, doi, Q, R);

      if (compare(R, unu) == 0) {
         bigProduct(a, aa);
         // a = a % MOD
         bigDivide(a, MOD, Q, R);
         bigAssign(a, R);
      }
      bigProduct(aa, aa);
      bigDivide(aa, MOD, Q, R);
      bigAssign(aa, R);
   }

}

void euclid(NrMare a, NrMare b, NrMare x, NrMare y, NrMare MOD) {

   NrMare x0, y0, Q, R, aux;

   NrMare zero;
   smallAssign(zero, 0);

   for (int k = 0; k < NN; k++) {
      x0[k] = y0[k] = Q[k] = R[k] = aux[k] = 0;
   }

   if (compare(b, zero) == 0) {
      smallAssign(x, 1);
      smallAssign(y, 0);
   } else {

      bigDivide(a, b, Q, R);
      euclid(b, R, x0, y0, MOD);

      bigAssign(x, y0);

      NrMare temp;
      bigAssign(temp, Q);
      bigProduct(temp, y0);
      NrMare dummy;
      bigDivide(temp, MOD, dummy, R);
      bigAssign(temp, R);

      if (compare(x0, temp) > -1) {
         bigAssign(y, x0);
         substract(y, temp);
      } else {
         bigAssign(y, x0);
         add(y, MOD);
         substract(y, temp);
      }

   }

}

void modularInverse(NrMare A, NrMare MOD, NrMare rez) {

   // A and MOD are coprime

   NrMare y;

   NrMare zero;
   smallAssign(zero, 0);

   euclid(A, MOD, rez, y, MOD);

   if (compare(rez, zero) == -1) {
      add(rez, MOD);
   }

}