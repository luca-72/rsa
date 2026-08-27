# Educational RSA Implementation (from scratch)

A pure C++ educational implementation of the RSA public-key cryptosystem.  
No external big-integer or cryptographic libraries are used.

## Mathematical foundation

RSA is based on modular arithmetic and the difficulty of factoring a large composite number.

Given two distinct primes (p) and (q):

[
N = pq
]

The Euler totient is:

[
\varphi(N) = (p-1)(q-1)
]

A public exponent (e) is chosen such that:

[
\gcd(e,\varphi(N)) = 1
]

This implementation uses:

[
e = 65537
]

The private exponent (d) is the modular inverse of (e):

[
d \equiv e^{-1} \pmod{\varphi(N)}
]

The resulting keys are:

[
\text{Public key} = (N,e)
]

[
\text{Private key} = (N,d)
]

For a message represented as an integer (m), where (0 \leq m < N):

Encryption

[
c \equiv m^e \pmod N
]

Decryption

[
m \equiv c^d \pmod N
]

Implementation

The project is split into three main parts:

Component	Description
bigint	Arbitrary-precision integers using base (10^8). Includes arithmetic, division, modulo, modular exponentiation and the extended Euclidean algorithm.
primality	Prime generation using a small-prime sieve and the Miller-Rabin probabilistic primality test.
rsa	RSA key generation, message encoding/decoding, encryption and decryption.

Messages are converted from ASCII to decimal digits and processed in 4-byte blocks. Each block is encrypted independently using the generated RSA key pair.

## Build and run
Linux / macOS

Copy and run:

git clone https://github.com/luca-72/rsa.git
cd rsa
g++ -std=c++17 -O2 main.cpp src/*.cpp -Iinclude -o rsa
./rsa
Windows

With MinGW:

git clone https://github.com/luca-72/rsa.git
cd rsa
g++ -std=c++17 -O2 main.cpp src/*.cpp -Iinclude -o rsa.exe
rsa.exe

Limitations

This implementation is intentionally simplified.

It does not implement modern RSA padding schemes such as OAEP, and the message encoding and key generation are designed for experimentation rather than security.

The implementation should therefore not be used to protect real data.

Purpose

The main goal of this project is to understand how RSA works at a lower level, including:

arbitrary-precision arithmetic
modular arithmetic
prime generation
primality testing
modular inverses
modular exponentiation
public-key encryption
