#include<iostream>
#include<ctime>
#include<random>
using namespace std;

const int BASE = 1e8;
const int NN = 100, NNN = 100;

typedef long long NrMare[NNN];



void AtribMic(NrMare x, int n)
{
  for(int i=0;i<NN;i++)
    x[i] = 0;
  if(n==0)
    x[(x[0]=1)]=0;
  else
    for(;n;n/=BASE)
      x[++x[0]]=n%BASE;
}

void AtribMare(NrMare Dest, NrMare Sursa)
{
  int i;
  for(i=0;i<=Sursa[0];i++)
    Dest[i]=Sursa[i];
  for(;i<NNN;i++)
   Dest[i] = Sursa[i] = 0;
}

int Compara(NrMare x, NrMare y)
{
  int ox = x[0], oy = y[0];  // Save originals
  
  // Work with local copies
  int tx = x[0], ty = y[0];
  while(tx>1 && x[tx]==0) tx--;
  while(ty>1 && y[ty]==0) ty--;
  
  if(tx!=ty)
    return (tx<ty?-1:1);
  int i=tx;
  while(x[i]==y[i] && i>0) i--;
  if(i==0) return 0;
  if(x[i]<y[i]) return -1;
  return 1;
}
void Adunare(NrMare x,NrMare y)
// x = x + y
{
  int i;
  long long t=0;
  if(x[0]<y[0]) 
    x[0]=y[0];
  for(i=1;i<=x[0];i++,t/=BASE)
  {
    t=(i<=x[0] ? x[i] : 0)+(i<=y[0] ? y[i] : 0)+t;
    x[i]=t%BASE;
    // echivalent x[i]=(t+=x[i]+y[i])%10
  }
  if(t)
    x[++x[0]]=t;
}

void Scadere(NrMare x, NrMare y)
// x <-- x-y
{
  int i,j;
  for (i = 1; i <= x[0]; i++){
    int yi = (i <= y[0]) ? y[i] : 0;
    if(x[i]>=yi) 
      x[i]-=yi;
    else
    {
      j=i+1;
      while(x[j]==0)
        x[j++]=BASE-1;
      x[j]--;
      x[i]=BASE+x[i]-yi;
    }

  }
  for (; x[0] > 1 && !x[x[0]]; x[0]--); // sa n-am zerouri nesemnificative
}

void ProdusMic(NrMare x, int n)
//x <- x*n
{
  int i;
  long long t=0;
  for(i=1;i<=x[0];i++,t/=BASE)
  {
    t+=1ll*x[i]*n;
    x[i]=t%BASE;
  }
  for(;t;t/=BASE)
    x[++x[0]]=t%BASE;
}

/*

void ProdusMare(NrMare x, NrMare y)
//x = x * y
{
  int i,j;
  long long t=0;
  NrMare z, zz[NN+1], aux;
  //stabilim lungimea rezultatului. S-ar putea modifica
  z[0]=x[0]+y[0]-1;
  //initializez vectorul z
  for(i=1;i<=x[0]+y[0];i++) 
    z[i]=0;
  //calculez produsele intermediare, impreuna cu suma intermediara
  for(i=1;i<=x[0];i++){
    for(j=1;j<=y[0];j++)
      z[i+j-1]+=1ll*x[i]*y[j];

   
    for(int ii=2;ii<=z[0];ii++){
      z[ii] += z[ii-1];
      z[ii-1] %= BASE;
    }
    z[z[0]] %= BASE;
  }
  //corectez sumele intermediare
  for(i=1;i<=z[0];i++)
  {
    t+=z[i];
    z[i]=t%BASE;
    t/=BASE;
  }
  if(t)
    z[++z[0]]=t;
  // pun rezultatul in x
  for(i=0;i<=z[0];i++)
    x[i]=z[i];
}

*/

int Divide(NrMare x, int n)
//x = x /n, returneaza x%n
{
  int i;
  long long r=0;
  for(i=x[0];i>0;i--)
  {
    r=1ll*BASE*r+x[i];
    x[i]=r/n;
    r%=n;
  }
  for(;x[x[0]]==0 && x[0]>1;) 
    x[0]--;
  return r;
}

/*
void ProdusMare(NrMare x, NrMare y)
//x = x * y
{
  int i,j;
  long long t=0;
  NrMare z, zz[2*NN+1], aux, tt;
  NrMare zero; AtribMic(zero, 0);

  for(i=0;i<=x[0]+y[0];i++)
   AtribMic(zz[i], 0);

  //stabilim lungimea rezultatului. S-ar putea modifica
  z[0]=x[0]+y[0];
  //initializez vectorul z
  for(i=1;i<=x[0]+y[0];i++) 
    z[i]=0;
  //calculez produsele intermediare, impreuna cu suma intermediara
  for(i=1;i<=x[0];i++){
    for(j=1;j<=y[0];j++){
      AtribMic(aux, x[i]);
      ProdusMic(aux, y[j]);
      Adunare(zz[i+j-1], aux);
      //z[i+j-1]+=1ll*x[i]*y[j];

    }

  }
  //corectez sumele intermediare
  AtribMic(tt, 0);
  NrMare Q, R;
  for(i=1;i<=z[0];i++)
  {
    Adunare(tt,zz[i]);
    z[i] = Divide(tt, BASE);
  }
  if(Compara(tt, zero) == 1)
    z[++z[0]]=Divide(tt, BASE);

  while(z[0] > 1 && z[z[0]] == 0)
   z[0]--;

  // pun rezultatul in x
  for(i=0;i<=z[0];i++)
    x[i]=z[i];
}
*/

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

  cout << A[A[0]];

    for(int i = A[0]-1;i>0;i--)
        printf("%08lld", A[i]);

    cout << '\n';

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

    /*
    while(Compara(cur,B) > -1){
      Scadere(cur, B);
      digit++;
    }
    */

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

 long long getRandomIntNumber(){

   std::mt19937 mt_rand(std::random_device{}());

  long long value = mt_rand();  // Call the generator

  return value;

}

void getRandomNrMare(NrMare n, int len){

  n[0] = len;

  for(int i=1;i<=n[0];i++)
    n[i] = getRandomIntNumber() % BASE;

}

 
void euclid(NrMare a, NrMare b, NrMare x, NrMare y, NrMare MOD){

  cout << "a = "; Afis(a);
  cout << "b = "; Afis(b);

  NrMare x0, y0,Q, R, aux;

  NrMare zero; AtribMic(zero, 0);

  for(int k = 0; k < NNN; k++) { x0[k] = y0[k] = Q[k] = R[k] = aux[k] = 0; }

  printf("%lld\n", b[0]); // whatever represents the number of digits

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

int randomBaseDigit(){

  // returns a random digit in base BASE;

  return getRandomIntNumber() % BASE;

}

void randomCandidate(NrMare p, int bits){

  int limbs = (bits+26) / 27;

  p[0] = limbs;
  for(int i=1;i<=limbs;i++){
    p[i] = randomBaseDigit();
  }

  p[1] |= 1;

}


void randomNumber(NrMare a, NrMare n){

  // generates a random number between 2 and n-2; answer in a

  NrMare q, r;

  NrMare doi; AtribMic(doi, 2);
  NrMare patru; AtribMic(patru, 4);

  NrMare n4; AtribMare(n4, n); Scadere(n4, patru);

  getRandomNrMare(a, 1); // 1 digit
  divideMare(a, n4, q, r);
  AtribMare(a, r);
  Adunare(a, doi);

}

bool MiillerTest(NrMare d, NrMare n)
{
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

    if(Compara(x, unu) == 0 ||
       Compara(x, n1) == 0)
        return true;

    while(Compara(dd, n1) != 0)
    {
        Expo(x, doi, n);

        ProdusMic(dd, 2);

        if(Compara(x, unu) == 0)
            return false;

        if(Compara(x, n1) == 0)
            return true;
    }

    return false;
}

bool Par(NrMare n){

  
  NrMare nn; AtribMare(nn, n);

  if(Divide(nn,2) == 0)
    return true;
  return false;

}

bool isPrime(NrMare n, int k){

  NrMare unu; AtribMic(unu, 1);
  NrMare trei; AtribMic(trei, 3);
  NrMare patru; AtribMic(patru, 4);

  if(Compara(n,unu) < 1 || Compara(n, patru) == 0)
    return false;
  if(Compara(n, trei) < 1)
    return true;

  NrMare d; AtribMare(d, n); Scadere(d, unu);

  while(Par(d))
    Divide(d, 2);

  for(int i=0; i<k;i++){
    if(!MiillerTest(d, n))
      return false;
  }

  return true;

}

void randomPrime1024(NrMare n){

  randomCandidate(n, 32);

  while(!isPrime(n, 10)){
    randomCandidate(n, 32);
  }
}



string string_to_string10(string s){

  int i, lg1, lg2=0, nr, lgnr, j;
  string rez, aux;

  lg1 = s.size();

  for(i=0;i<lg1;i++){

    nr = int(s[i]); // 97

    lgnr = 0;
    aux.clear();

    while(nr){
      lgnr++;
      aux.push_back(char(nr%10+'0')); // 79
      nr/=10;
    }

    rez.push_back(char(lgnr+'0'));
    for(j=aux.size()-1;j>=0;j--)
      rez.push_back(aux[j]);

  }

  return rez;

}

void string10_to_NrMare(NrMare rez, string s){

  AtribMic(rez, 0);
  rez[0] = 0;

  int i, lg = s.size(), j, aux;

  for(i=lg-1;i>=0;i-=8){

    aux = 0;

   for(j=i-7;j<=i;j++){

    if(j >= 0)
      aux = aux * 10 + (s[j] - '0');

   }

   rez[++rez[0]] = aux;

  }

}

string NrMare_to_string10(NrMare a){

  int i, j;
  string rez, aux;
  NrMare aa;

  AtribMare(aa, a);

  for(i=a[0];i>0;i--){

    aux.clear();

    //cout << "*" << a[i] << endl;

    while(a[i]){
      //cout << "c:" << a[i] << " " << char(a[i] + '0') << endl;
      aux.push_back(char(a[i] % 10 + '0'));
      a[i] /= 10;
    }

    for(j=aux.size()-1;j>=0;j--)
      rez.push_back(aux[j]);

  }

  AtribMare(a, aa);

  return rez;

}

string string10_to_string(string s){

  string rez;
  int i, lg=s.size(), j, aux, len;

  for(i=0;i<lg;i++){

    aux=0;
    len = s[i] - '0';

    for(j=i+1;j<=i+len;j++){
      aux = aux*10 + (s[j] - '0');
    }

    //cout << aux << "\n";

    i = j-1;

    rez.push_back(char(aux));

  }

  return rez;

}

void test(){

  string s;
  NrMare n;
  cin >> s;

  cout << "initial string : " << s << "\n";

  s = string_to_string10(s);
  cout << "string10 : " << s << "\n";

  string10_to_NrMare(n, s);
  cout << "NrMare : ";
  Afis(n);

  s = NrMare_to_string10(n);
  cout << "string10 : " << s << "\n";

  s = string10_to_string(s);
  cout <<  "string : " << s << "\n";

}



void read(NrMare message){

  string s;

  cin >> s;

  s = string_to_string10(s);
  string10_to_NrMare(message, s);

}

void write(NrMare a){

  string s;

  s = NrMare_to_string10(a);
  s = string10_to_string(s);

  cout << s << "\n";

}

int main(){

  //test();

  //return 0;


    NrMare e; AtribMic(e, 65537); 

    NrMare message;

    read(message);

    //AtribMic(message, 12345678);

    NrMare phi22, e2, q, r, aux;

    NrMare doi; AtribMic(doi, 2);
    NrMare unu; AtribMic(unu, 1);
    NrMare zero; AtribMic(zero, 0);

    NrMare p, N, p1, q1, p2, phi;

    while(true){

      randomPrime1024(p); // AtribMic(p, 53);
      randomPrime1024(q);// AtribMic(q, 73);
      AtribMare(N, p); ProdusMare(N,q);

      cout << "N = "; Afis(N);

      cout << "unu = ";Afis(unu);

      cout << "p = "; Afis(p);

      cout << "q = "; Afis(q);



      AtribMare(p1, p);cout << "p1 = "; Afis(p1); Scadere(p1, unu);
      AtribMare(q1, q); Scadere(q1, unu);
      AtribMare(p2, p); Scadere(p2, doi);

      cout << "p1 = "; Afis(p1);

      AtribMare(phi, p1); cout << "phi = "; Afis(phi); ProdusMare(phi, q1);

      AtribMare(phi22, phi);
      AtribMare(e2, e);

      divideMare(phi22, e2, q, r);

      if(Compara(r,zero) != 0)
        break;

    }
    cout << "phi = "; Afis(phi);

    NrMare phi2; AtribMare(phi2, phi); Scadere(phi2, doi);

    NrMare d; AtribMare(d, e);
    cout << "phi = "; Afis(phi);

    
    invers_modular(d, phi, aux); AtribMare(d, aux); //Expo(d, phi2,phi);

    cout << "d = "; Afis(d);

    NrMare ct; AtribMare(ct, message);
    Expo(ct, e, N);

    cout << "criptat : "; Afis(ct);

    //return 0;

    NrMare pt; AtribMare(pt, ct);
    Expo(pt, d, N);

    cout << "decriptat : "; write(pt); //Afis(pt);

}
