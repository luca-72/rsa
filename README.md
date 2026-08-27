# Educational RSA Implementation (from scratch)

A pure C++ educational implementation of the RSA public-key cryptosystem.  
No external big-integer or cryptographic libraries are used.

## Mathematical foundation

RSA is based on modular arithmetic and the difficulty of factoring a large composite number.

The key generation process is:

Choose two distinct primes p and q.

Calculate the modulus:

N = p × q

Calculate Euler's totient:

φ(N) = (p - 1)(q - 1)

Choose a public exponent e such that:

gcd(e, φ(N)) = 1

This implementation uses e = 65537.

Calculate the private exponent d as the modular inverse of e:

d ≡ e⁻¹ (mod φ(N))

The resulting keys are:

Public key:  (N, e)
Private key: (N, d)
Encryption

A message is represented as an integer m, where:

0 ≤ m < N

The ciphertext is calculated using:

c = mᵉ mod N
Decryption

The original message is recovered using:

m = cᵈ mod N
Implementation

The project is divided into three main components:

Component	Description
bigint	Arbitrary-precision integer implementation using base 10⁸. Provides arithmetic, division, modulo, modular exponentiation and the extended Euclidean algorithm.
primality	Prime generation using a small-prime sieve and the Miller-Rabin probabilistic primality test.
rsa	RSA key generation, message encoding/decoding, encryption and decryption.

Messages are converted from ASCII to decimal digits and processed in 4-byte blocks. Each block is encrypted independently.

Build and Run
Linux / macOS
git clone https://github.com/luca-72/rsa.git
cd rsa
g++ -std=c++17 -O2 main.cpp src/*.cpp -Iinclude -o rsa
./rsa
Windows

Using MinGW:

git clone https://github.com/luca-72/rsa.git
cd rsa
g++ -std=c++17 -O2 main.cpp src/*.cpp -Iinclude -o rsa.exe
rsa.exe
Limitations

This implementation is intentionally simplified and is designed for learning.

It does not implement modern RSA padding schemes such as OAEP. The message encoding, key generation and random number generation should also not be considered secure.

Do not use this implementation to protect real data.

Project Goals

The main goal of this project is to understand the algorithms behind RSA by implementing them directly rather than relying on existing cryptographic libraries.

The project covers:

Arbitrary-precision integer arithmetic
Modular arithmetic
Prime generation
Miller-Rabin primality testing
Modular inverses
Modular exponentiation
RSA key generation
RSA encryption and decryption
