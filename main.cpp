#include<iostream>
#include<ctime>
#include<random>
using namespace std;

const int BASE = 1e8;
const int NN = 100, NNN = 100;
#include <iostream>
#include <ctime>
#include <random>
using namespace std;

const int BASE = 1e8;
const int NN = 100;

typedef long long NrMare[NN];

void setSmall(NrMare x, int n)
{
	for (int i = 0; i < NN; i ++)
	x[i] = 0;

	if (n == 0)
	{
		x[0] = 1;
		x[1] = 0;
	} else {
		while (n)
		{
			x[ ++ x[0]] = n % BASE;
			n /= BASE;
		}
	}
}

void copyBig(NrMare target, NrMare source)
{
	int i;

	for (i = 0; i <= source[0]; i ++)
	target[i] = source[i];

	for (; i < NN; i ++)
	target[i] = source[i] = 0;
}

int compareBig(NrMare x, NrMare y)
{
	int leftSize = x[0];
	int rightSize = y[0];

	while (leftSize > 1 && x[leftSize] == 0)
	leftSize -- ;

	while (rightSize > 1 && y[rightSize] == 0)
	rightSize -- ;

	if (leftSize < rightSize)
	return - 1;

	if (leftSize > rightSize)
	return 1;

	while (leftSize > 0 && x[leftSize] == y[leftSize])
	leftSize -- ;

	if (leftSize == 0)
	return 0;

	if (x[leftSize] < y[leftSize])
	return - 1;

	return 1;
}

void addBig(NrMare x, NrMare y)
{
	int n = max(x[0], y[0]);
	long long carry = 0;

	for (int i = 1; i <= n; i ++)
	{
		long long sum = x[i] + y[i] + carry;
		x[i] = sum % BASE;
		carry = sum / BASE;
	}

	x[0] = n;

	if (carry)
	x[ ++ x[0]] = carry;
}

void subtractBig(NrMare x, NrMare y)
{
	long long borrow = 0;

	for (int i = 1; i <= x[0]; i ++)
	{
		long long value = x[i] - y[i] - borrow;

		if (value < 0)
		{
			value += BASE;
			borrow = 1;
		}
		else
		borrow = 0;

		x[i] = value;
	}

	while (x[0] > 1 && x[x[0]] == 0)
	x[0] -- ;
}

void multiplySmall(NrMare x, int n)
{
	long long carry = 0;

	for (int i = 1; i <= x[0]; i ++)
	{
		long long value = 1LL * x[i] * n + carry;
		x[i] = value % BASE;
		carry = value / BASE;
	}

	while (carry)
	{
		x[ ++ x[0]] = carry % BASE;
		carry /= BASE;
	}
}

int divideSmall(NrMare x, int n)
{
	long long remainder = 0;

	for (int i = x[0]; i > 0; i --)
	{
		remainder = remainder * BASE + x[i];
		x[i] = remainder / n;
		remainder %= n;
	}

	while (x[0] > 1 && x[x[0]] == 0)
	x[0] -- ;

	return remainder;
}

void multiplyBig(NrMare x, NrMare y)
{
	NrMare z;
	setSmall(z, 0);

	z[0] = x[0] + y[0];

	for (int i = 1; i <= z[0]; i ++)
	z[i] = 0;

	for (int i = 1; i <= x[0]; i ++)
	{
		long long carry = 0;

		for (int j = 1; j <= y[0]; j ++)
		{
			long long current = z[i + j - 1] + 1LL * x[i] * y[j] + carry;

			z[i + j - 1] = current % BASE;
			carry = current / BASE;
		}

		z[i + y[0]] += carry;
	}

	while (z[0] > 1 && z[z[0]] == 0)
	z[0] -- ;

	copyBig(x, z);
}

void printBig(NrMare A)
{
	for (int i = A[0] - 1; i > 0; i --)
	printf("%08lld", A[i]);
}

void divideBig(NrMare A, NrMare B, NrMare Q, NrMare R)
{
	int i, j;

	NrMare current; setSmall(current, 0);

	Q[0] = A[0];

	for (i = 1; i <= Q[0]; i ++)
	Q[i] = 0;

	for (i = A[0]; i > 0; i --)
	{
		if (current[0] == 1 && current[1] == 0)
		current[0] = 0;

		if (current[0] != 0)
		for (j = current[0]; j >= 1; j --)
		current[j + 1] = current[j];

		current[0] ++ ;
		current[1] = A[i];

		while (current[current[0]] == 0 && current[0] > 1)
		current[0] -- ;

		int digit = 0;

		int left, right, middle;
		NrMare temp;
		left = 0; right = BASE - 1;
		while (left <= right)
		{
			middle = left + (right - left) / 2;
			setSmall(temp, middle);
			multiplyBig(temp, B);
			if (compareBig(temp, current) <= 0)
			{
				digit = middle;
				left = middle + 1;
			} else {
				right = middle - 1;
			}
		}

		Q[i] = digit;

		setSmall(temp, digit);
		multiplyBig(temp, B);
		subtractBig(current, temp);
	}

	while (Q[Q[0]] == 0 && Q[0] > 1)
	Q[0] -- ;

	copyBig(R, current);
}

void modularPower(NrMare a, NrMare n, NrMare MOD)
{
	NrMare base; copyBig(base, a);
	setSmall(a, 1);
	NrMare i, half;

	NrMare one; setSmall(one, 1);
	NrMare two; setSmall(two, 2);
	NrMare Q, R;

	for (copyBig(i, n); compareBig(i, one) != - 1; divideSmall(i, 2))
	{
		copyBig(half, i);

		setSmall(two, 2);
		divideBig(half, two, Q, R);

		if (compareBig(R, one) == 0)
		{
			multiplyBig(a, base);

			divideBig(a, MOD, Q, R);
			copyBig(a, R);
		}
		multiplyBig(base, base);
		divideBig(base, MOD, Q, R);
		copyBig(base, R);
	}
}

std::mt19937 mt_rand(std::random_device
{
}());

long long getRandomNumber()
{
	long long value = mt_rand();

	return value;
}

void getRandomBigNumber(NrMare n, int partLength)
{
	n[0] = partLength;

	for (int i = 1; i <= n[0]; i ++)
	n[i] = getRandomNumber() % BASE;
}

void extendedEuclid(NrMare a, NrMare b, NrMare x, NrMare y, NrMare MOD)
{
	NrMare x0, y0, Q, R, temp;

	NrMare zero; setSmall(zero, 0);

	for (int k = 0; k < NN; k ++)
	{
		x0[k] = y0[k] = Q[k] = R[k] = temp[k] = 0;
	}

	if (compareBig(b, zero) == 0)
	{
		setSmall(x, 1);
		setSmall(y, 0);
	} else {
		divideBig(a, b, Q, R);
		extendedEuclid(b, R, x0, y0, MOD);

		copyBig(x, y0);

		NrMare temp; copyBig(temp, Q); multiplyBig(temp, y0);
		NrMare dummy;
		divideBig(temp, MOD, dummy, R);
		copyBig(temp, R);

		if (compareBig(x0, temp) > - 1)
		{
			copyBig(y, x0);
			subtractBig(y, temp);
		} else {
			copyBig(y, x0);
			addBig(y, MOD);
			subtractBig(y, temp);
		}
	}
}

void modularInverse(NrMare A, NrMare MOD, NrMare result)
{
	NrMare y;

	NrMare zero; setSmall(zero, 0);

	extendedEuclid(A, MOD, result, y, MOD);

	if (compareBig(result, zero) == - 1)
	{
		addBig(result, MOD);
	}
}

int getRandomDigit()
{
	return getRandomNumber() % BASE;
}

void generateCandidate(NrMare p, int bits)
{
	int size = (bits + 26) / 27;

	p[0] = size;
	for (int i = 1; i <= size; i ++)
	{
		p[i] = getRandomDigit();
	}

	p[1] |= 1;
}

void generateRandomNumber(NrMare a, NrMare n)
{
	NrMare q, r;

	NrMare two; setSmall(two, 2);
	NrMare four; setSmall(four, 4);

	NrMare n4; copyBig(n4, n); subtractBig(n4, four);

	getRandomBigNumber(a, 1);
	divideBig(a, n4, q, r);
	copyBig(a, r);
	addBig(a, two);
}

bool millerTest(NrMare d, NrMare n)
{
	NrMare exponent;
	copyBig(exponent, d);

	NrMare a;
	generateRandomNumber(a, n);

	NrMare x;
	copyBig(x, a);
	modularPower(x, exponent, n);

	NrMare one;
	setSmall(one, 1);

	NrMare two;
	setSmall(two, 2);

	NrMare nMinusOne;
	copyBig(nMinusOne, n);
	subtractBig(nMinusOne, one);

	if (compareBig(x, one) == 0 ||
	compareBig(x, nMinusOne) == 0)
	return true;

	while (compareBig(exponent, nMinusOne) != 0)
	{
		modularPower(x, two, n);

		multiplySmall(exponent, 2);

		if (compareBig(x, one) == 0)
		return false;

		if (compareBig(x, nMinusOne) == 0)
		return true;
	}

	return false;
}

bool isEven(NrMare n)
{
	NrMare nn; copyBig(nn, n);

	if (divideSmall(nn, 2) == 0)
	return true;
	return false;
}

bool checkPrime(NrMare n, int k)
{
	NrMare one; setSmall(one, 1);
	NrMare three; setSmall(three, 3);
	NrMare four; setSmall(four, 4);

	if (compareBig(n, one) < 1 || compareBig(n, four) == 0)
	return false;
	if (compareBig(n, three) < 1)
	return true;

	NrMare d; copyBig(d, n); subtractBig(d, one);

	while (isEven(d))
	divideSmall(d, 2);

	for (int i = 0; i < k; i ++)
	{
		if (!millerTest(d, n))
		return false;
	}

	return true;
}

bool hasSmallFactor(NrMare n)
{
	static const int small_primes[] =
	{
		2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
		43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127,
		131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211,
		223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307,
		311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401,
		409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499,
		503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607,
		613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709,
		719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823,
		827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937,
		941, 947, 953, 967, 971, 977, 983, 991, 997
	};
	for (int p : small_primes)
	{
		NrMare tmp; copyBig(tmp, n);
		if (divideSmall(tmp, p) == 0) return true;
	}
	return false;
}

void generatePrime64(NrMare n)
{
	generateCandidate(n, 64);

	while (hasSmallFactor(n) || !checkPrime(n, 10))
	{
		generateCandidate(n, 64);
	}
}

string stringToDecimal(string s)
{
	int i, length, length2 = 0, number, numberLength, j;
	string result, temp;

	length = s.size();

	for (i = 0; i < length; i ++)
	{
		number = int((unsigned char)s[i]);

		numberLength = 0;
		temp.clear();

		while (number)
		{
			numberLength ++ ;
			temp.push_back(char(number % 10 + '0'));
			number /= 10;
		}

		result.push_back(char(numberLength + '0'));
		for (j = temp.size() - 1; j >= 0; j --)
		result.push_back(temp[j]);
	}

	return result;
}

void decimalToBigNumber(NrMare result, string s)
{
	setSmall(result, 0);
	result[0] = 0;

	int i, length = s.size(), j, temp;

	for (i = length - 1; i >= 0; i -= 8)
	{
		temp = 0;

		for (j = i - 7; j <= i; j ++)
		{
			if (j >= 0)
			temp = temp * 10 + (s[j] - '0');
		}

		result[ ++ result[0]] = temp;
	}
}

string bigNumberToDecimal(NrMare a)
{
	int i, j;
	string result, temp;
	NrMare base;

	copyBig(base, a);

	for (i = a[0]; i > 0; i --)
	{
		temp.clear();
		while (a[i])
		{
			temp.push_back(char(a[i] % 10 + '0')); a[i] /= 10;
		}

		if (i != a[0])
		while (temp.size() < 8)
		temp.push_back('0');

		for (j = temp.size() - 1; j >= 0; j --)
		result.push_back(temp[j]);
	}

	copyBig(a, base);

	return result;
}

string decimalToString(string s)
{
	string result;
	int i, length = s.size(), j, temp, partLength;

	for (i = 0; i < length; i ++)
	{
		temp = 0;
		partLength = s[i] - '0';

		for (j = i + 1; j <= i + partLength; j ++)
		{
			temp = temp * 10 + (s[j] - '0');
		}

		i = j - 1;

		result.push_back(char(temp));
	}

	return result;
}

void testConversion()
{
	string s;
	NrMare n;
	cin >> s;

	s = stringToDecimal(s);

	decimalToBigNumber(n, s);

	s = bigNumberToDecimal(n);

	s = decimalToString(s);
}

void readMessage(NrMare message, string s)
{
	s = stringToDecimal(s);
	decimalToBigNumber(message, s);
}

void writeMessage(NrMare a)
{
	string s;

	s = bigNumberToDecimal(a);
	s = decimalToString(s);

	cout << s;
}

NrMare p, N, p1, q1, p2, phi, phi2, d, e;

void setupKeys()
{
	setSmall(e, 65537);

	NrMare phi22, e2, q, r, temp;

	NrMare two; setSmall(two, 2);
	NrMare one; setSmall(one, 1);
	NrMare zero; setSmall(zero, 0);

	while (true)
	{
		generatePrime64(p);
		generatePrime64(q);
		copyBig(N, p); multiplyBig(N, q);

		copyBig(p1, p); subtractBig(p1, one);
		copyBig(q1, q); subtractBig(q1, one);
		copyBig(p2, p); subtractBig(p2, two);

		copyBig(phi, p1); multiplyBig(phi, q1);

		copyBig(phi22, phi);
		copyBig(e2, e);

		divideBig(phi22, e2, q, r);

		if (compareBig(r, zero) != 0)
		break;
	}

	copyBig(phi2, phi); subtractBig(phi2, two);

	copyBig(d, e);

	modularInverse(d, phi, temp); copyBig(d, temp);
}

void encryptMessage(NrMare cipherText, string s)
{
	NrMare message;

	readMessage(message, s);

	copyBig(cipherText, message);
	modularPower(cipherText, e, N);
}

void decryptMessage(NrMare plainText, NrMare cipherText)
{
	copyBig(plainText, cipherText);
	modularPower(plainText, d, N);
}

int main()
{
	NrMare plainText, cipherText;
	setupKeys();
	string s;
	while (true)
	{
		cout << "enter the message : "; getline(cin, s);

		if (s.size() < 4000)
		break;

		cout << "the message can't be longer than 4000 characters. try again\n";
	}

	cout << "\n\n";

	vector < string > messages;
	string temp;
	int i, j, length;

	length = s.size();

	for (i = 0; i < length; i ++)
	{
		temp.clear();

		for (j = i; j < i + 4&&j < length; j ++)
		{
			temp.push_back(s[j]);
		}

		i = j - 1;

		messages.push_back(temp);
	}

	NrMare cipherTexts[NN+1], plainTexts[NN+1];
	NrMare tempCipher, tempPlain;
	int cipherCount = 0, plainCount = 0;

	for (auto part : messages)
	{
		encryptMessage(tempCipher, part);

		copyBig(cipherTexts[ ++ cipherCount], tempCipher);
	}

	cout << "criptat : ";
	for (i = 1; i <= cipherCount; i ++)
	{
		printBig(cipherTexts[i]);
	}
	cout << endl;

	for (i = 1; i <= cipherCount; i ++)
	{
		decryptMessage(tempPlain, cipherTexts[i]);
		copyBig(plainTexts[ ++ plainCount], tempPlain);
	}

	cout << "decriptat : ";
	for (i = 1; i <= plainCount; i ++)
	writeMessage(plainTexts[i]);
	cout << endl;
}
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

 std::mt19937 mt_rand(std::random_device{}());

 long long getRandomIntNumber(){

  long long value = mt_rand();  // Call the generator

  return value;

}

void getRandomNrMare(NrMare n, int len){

  n[0] = len;

  for(int i=1;i<=n[0];i++)
    n[i] = getRandomIntNumber() % BASE;

}

 
void euclid(NrMare a, NrMare b, NrMare x, NrMare y, NrMare MOD){

  //cout << "a = "; Afis(a);
  //cout << "b = "; Afis(b);

  NrMare x0, y0,Q, R, aux;

  NrMare zero; AtribMic(zero, 0);

  for(int k = 0; k < NNN; k++) { x0[k] = y0[k] = Q[k] = R[k] = aux[k] = 0; }

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

  while(quickCompositeCheck(n) || !isPrime(n, 10)){
    randomCandidate(n, 64);
  }
}



string string_to_string10(string s){

  int i, lg1, lg2=0, nr, lgnr, j;
  string rez, aux;

  lg1 = s.size();

  for(i=0;i<lg1;i++){

    nr = int((unsigned char)s[i]); // 97

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
    while(a[i]){
      aux.push_back(char(a[i] % 10 + '0')); a[i] /= 10; 
    }

    if(i != a[0])                   // every limb except the top one...
      while(aux.size() < 8) 
        aux.push_back('0');         // must be exactly 8 digits

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

  //cout << "initial string : " << s << "\n";

  s = string_to_string10(s);
  //cout << "string10 : " << s << "\n";

  string10_to_NrMare(n, s);
  //cout << "NrMare : ";
  //Afis(n);

  s = NrMare_to_string10(n);
  //cout << "string10 : " << s << "\n";

  s = string10_to_string(s);
  //cout <<  "string : " << s << "\n";

}



void read(NrMare message, string s){

  s = string_to_string10(s);
  string10_to_NrMare(message, s);

}

void write(NrMare a){

  string s;

  s = NrMare_to_string10(a);
  s = string10_to_string(s);

  cout << s;

}

NrMare p, N, p1, q1, p2, phi, phi2, d, e;

void setup(){

    AtribMic(e, 65537); 
    
    //AtribMic(message, 12345678);

    NrMare phi22, e2, q, r, aux;

    NrMare doi; AtribMic(doi, 2);
    NrMare unu; AtribMic(unu, 1);
    NrMare zero; AtribMic(zero, 0);

   

    while(true){

      randomPrime64(p); // AtribMic(p, 53);
      randomPrime64(q);// AtribMic(q, 73);
      AtribMare(N, p); ProdusMare(N,q);

      //cout << "N = "; Afis(N);

      //cout << "unu = ";Afis(unu);

      //cout << "p = "; Afis(p);

      //cout << "q = "; Afis(q);



      AtribMare(p1, p); Scadere(p1, unu);
      AtribMare(q1, q); Scadere(q1, unu);
      AtribMare(p2, p); Scadere(p2, doi);

      //cout << "p1 = "; Afis(p1);

      AtribMare(phi, p1);  ProdusMare(phi, q1);

      AtribMare(phi22, phi);
      AtribMare(e2, e);

      divideMare(phi22, e2, q, r);

      if(Compara(r,zero) != 0)
        break;

    }
    //cout << "phi = "; Afis(phi);

    AtribMare(phi2, phi); Scadere(phi2, doi);

    AtribMare(d, e);
    //cout << "phi = "; Afis(phi);

    
    invers_modular(d, phi, aux); AtribMare(d, aux); //Expo(d, phi2,phi);

    //cout << "d = "; Afis(d);

}

void encrypt(NrMare ct, string s){

  NrMare message;

  read(message, s);

  AtribMare(ct, message);
  Expo(ct, e, N);

  //cout << "criptat : "; Afis(ct);

}

void decrypt(NrMare pt, NrMare ct){

  AtribMare(pt, ct);
  Expo(pt, d, N);

  //cout << "decriptat : "; write(pt); //Afis(pt);

}

int main(){

  NrMare pt, ct;
  setup();
  string s;
  while(true){
    cout << "enter the message : "; getline(cin, s);

    if(s.size() < 4000)
      break;

    cout << "the message can't be longer than 4000 characters. try again\n";

  }

  cout << "\n\n";

  vector<string> vmes;
  string aux;
  int i, j, lg;

  lg = s.size();

  for(i=0;i<lg;i++){

    aux.clear();

    for(j=i;j<i+4&&j<lg;j++){

      aux.push_back(s[j]);

    }

    i = j-1;

    vmes.push_back(aux);

  }

  
  NrMare vct[1002], vpt[1002];
  NrMare auxct, auxpt;
  int lgvct=0, lgvpt=0;

  for(auto ee : vmes){

    encrypt(auxct, ee);

    AtribMare(vct[++lgvct], auxct);
    //vct.push_back(auxct);

  }

  

  cout << "criptat : ";
  for(i=1;i<=lgvct;i++){
    Afis(vct[i]);
  }
  cout << endl;

  for(i=1;i<=lgvct;i++){

    decrypt(auxpt, vct[i]);
    AtribMare(vpt[++lgvpt], auxpt);//vpt.push_back(auxpt);

  }

  cout << "decriptat : ";
  for(i=1;i<=lgvpt;i++)
    write(vpt[i]);
  cout << endl;
  
}
