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
