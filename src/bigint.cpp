#include "bigint.h"

#include<ctime>
#include<cstdio>
#include<algorithm>

using namespace std;


void AtribMic(NrMare x, int n)
{
  for(int i=0;i<NN;i++)
    x[i]=0;

  if(n==0)
  {
    x[0]=1;
    x[1]=0;
  }
  else
  {
    while(n)
    {
      x[++x[0]]=n%BASE;
      n/=BASE;
    }
  }
}

void AtribMare(NrMare dest, NrMare src)
{
  int i;

  for(i=0;i<=src[0];i++)
    dest[i]=src[i];

  for(;i<NN;i++)
    dest[i]=src[i]=0;
}

int Compara(NrMare x, NrMare y)
{
  int nx=x[0];
  int ny=y[0];

  while(nx>1 && x[nx]==0)
    nx--;

  while(ny>1 && y[ny]==0)
    ny--;

  if(nx<ny)
    return -1;

  if(nx>ny)
    return 1;

  while(nx>0 && x[nx]==y[nx])
    nx--;

  if(nx==0)
    return 0;

  if(x[nx]<y[nx])
    return -1;

  return 1;
}

void Adunare(NrMare x, NrMare y)
// x = x + y
{
  int n=max(x[0],y[0]);
  long long carry=0;

  for(int i=1;i<=n;i++)
  {
    long long sum=x[i]+y[i]+carry;
    x[i]=sum%BASE;
    carry=sum/BASE;
  }

  x[0]=n;

  if(carry)
    x[++x[0]]=carry;
}

void Scadere(NrMare x, NrMare y)
// x = x - y
{
  long long borrow=0;

  for(int i=1;i<=x[0];i++)
  {
    long long value=x[i]-y[i]-borrow;

    if(value<0)
    {
      value+=BASE;
      borrow=1;
    }
    else
      borrow=0;

    x[i]=value;
  }

  while(x[0]>1 && x[x[0]]==0)
    x[0]--;
}

void ProdusMic(NrMare x, int n)
// x = x * n
{
  long long carry=0;

  for(int i=1;i<=x[0];i++)
  {
    long long value=1LL*x[i]*n+carry;
    x[i]=value%BASE;
    carry=value/BASE;
  }

  while(carry)
  {
    x[++x[0]]=carry%BASE;
    carry/=BASE;
  }
}

int Divide(NrMare x, int n)
// x = x / n, returns x % n
{
  long long rest=0;

  for(int i=x[0];i>0;i--)
  {
    rest=rest*BASE+x[i];
    x[i]=rest/n;
    rest%=n;
  }

  while(x[0]>1 && x[x[0]]==0)
    x[0]--;

  return rest;
}

void ProdusMare(NrMare x, NrMare y)
{
    NrMare z;
    AtribMic(z, 0);

    z[0] = x[0] + y[0];

    for(int i = 1; i <= z[0]; i++)
        z[i] = 0;

    for(int i = 1; i <= x[0]; i++)
    {
        long long carry = 0;

        for(int j = 1; j <= y[0]; j++)
        {
            long long cur =
                z[i + j - 1]
                + 1LL * x[i] * y[j]
                + carry;

            z[i + j - 1] = cur % BASE;
            carry = cur / BASE;
        }

        z[i + y[0]] += carry;
    }

    while(z[0] > 1 && z[z[0]] == 0)
        z[0]--;

    AtribMare(x, z);
}


void Afis(NrMare A){

  //cout << A[A[0]];

    for(int i = A[0]-1;i>0;i--)
        printf("%08lld", A[i]);

    //cout << '\n';

}

void divideMare(NrMare A, NrMare B, NrMare Q, NrMare R){

  int i, j;

  NrMare cur; AtribMic(cur, 0);

  Q[0] = A[0];

  for(i=1;i<=Q[0];i++)
    Q[i] = 0;

  for(i=A[0];i>0;i--){

    if(cur[0] == 1 && cur[1] == 0)
      cur[0] = 0;

    if(cur[0] != 0)
      for(j=cur[0];j>=1;j--)
       cur[j+1] = cur[j];

    cur[0]++;
    cur[1] = A[i];

    while(cur[cur[0]] == 0 && cur[0] > 1)
     cur[0]--;

    int digit =0;

    // gasim cel mai mare digit pentru care digit*B <= cur

    int st, dr, mij;
    NrMare aux;
    st = 0; dr=BASE-1;
    while(st<=dr){
      mij = st + (dr-st)/2;//mij = (st+dr)/2;
      AtribMic(aux, mij);
      ProdusMare(aux, B);
      if(Compara(aux, cur) <= 0){
        digit = mij;
        st = mij+1;
      }
      else {
        dr = mij-1;
      }
    }

    Q[i] = digit;

    AtribMic(aux, digit);
    ProdusMare(aux, B);
    Scadere(cur,aux);


  }

  while(Q[Q[0]] == 0 && Q[0] > 1)
    Q[0]--;

  AtribMare(R,cur);

}

 void Expo(NrMare a, NrMare n, NrMare MOD){

     //cout << "*";

     NrMare aa; AtribMare(aa, a);
     AtribMic(a, 1);
     NrMare i, ii;

     NrMare unu; AtribMic(unu, 1);
     NrMare doi; AtribMic(doi, 2);
     NrMare Q, R;

     for(AtribMare(i, n); Compara(i, unu) != -1; Divide(i, 2)){

         //Afis(i);
         AtribMare(ii, i);

         AtribMic(doi, 2);
         divideMare(ii,doi,Q,R);

         if(Compara(R,unu) == 0){
             ProdusMare(a, aa);
             // a = a % MOD
             divideMare(a, MOD, Q, R);
             AtribMare(a, R);
         }
         ProdusMare(aa, aa);
         divideMare(aa, MOD, Q, R);
         AtribMare(aa, R);
     }

     //cout << "*";

 }

 void euclid(NrMare a, NrMare b, NrMare x, NrMare y, NrMare MOD){

  //cout << "a = "; Afis(a);
  //cout << "b = "; Afis(b);

  NrMare x0, y0,Q, R, aux;

  NrMare zero; AtribMic(zero, 0);

  for(int k = 0; k < NN; k++) { x0[k] = y0[k] = Q[k] = R[k] = aux[k] = 0; }

  //printf("%lld\n", b[0]); // whatever represents the number of digits

  if(Compara(b,zero) == 0){
    AtribMic(x,1);
    AtribMic(y, 0);
  }
  else{

    
    divideMare(a, b, Q,R);
    euclid(b, R, x0, y0,MOD);

    AtribMare(x,y0);

    //AtribMare(aux, Q); ProdusMare(aux, y0);
    //AtribMare(y, x0); Scadere(y, aux);

    NrMare temp; AtribMare(temp, Q); ProdusMare(temp, y0);
    NrMare dummy;
    divideMare(temp, MOD, dummy, R);
    AtribMare(temp, R);

    if(Compara(x0, temp) > -1){
      AtribMare(y, x0);
      Scadere(y, temp);
    }

    else{
      AtribMare(y, x0);
      Adunare(y, MOD);
      Scadere(y, temp);
    }

  }

}

void invers_modular(NrMare A, NrMare MOD, NrMare rez){

  // A si MOD prime intre ele!!

  NrMare y;

  NrMare zero; AtribMic(zero, 0);

  euclid(A,MOD,rez,y,MOD);

  if(Compara(rez, zero)  == -1){
    Adunare(rez, MOD);
  }

}