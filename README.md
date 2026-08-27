# Educational RSA Implementation

A pure C++ implementation of the RSA public-key cryptosystem, written from scratch.

No external big-integer or cryptographic libraries are used.

## Mathematical Foundation

RSA is a public-key cryptosystem based on modular arithmetic and the difficulty of factoring large composite numbers.

### Key Generation

1. Choose two distinct prime numbers `p` and `q`.

2. Calculate the modulus:

```text
N = p * q
```

3. Calculate Euler's totient:

```text
phi(N) = (p - 1) * (q - 1)
```

4. Choose a public exponent `e` such that:

```text
gcd(e, phi(N)) = 1
```

This implementation uses:

```text
e = 65537
```

5. Calculate the private exponent `d`, the modular inverse of `e`:

```text
d = e^(-1) mod phi(N)
```

The resulting keys are:

```text
Public key:  (N, e)
Private key: (N, d)
```

### Encryption

A message is represented as an integer `m` satisfying:

```text
0 <= m < N
```

Encryption is performed using:

```text
c = m^e mod N
```

### Decryption

The original message is recovered using:

```text
m = c^d mod N
```

## Implementation

The project is divided into three main components:

| Component   | Description                                                                                                                                                                               |
| ----------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `bigint`    | Arbitrary-precision integer arithmetic using base `10^8`. Includes addition, subtraction, multiplication, division, modulo, modular exponentiation, and the extended Euclidean algorithm. |
| `primality` | Prime generation using a small-prime sieve and the Miller-Rabin probabilistic primality test.                                                                                             |
| `rsa`       | RSA key generation, message encoding and decoding, encryption, and decryption.                                                                                                            |

Messages are converted from ASCII to decimal digits and processed in 4-byte blocks. Each block is encrypted independently.

## Build and Run

### Linux / macOS

```bash
git clone https://github.com/luca-72/rsa.git
cd rsa
g++ -std=c++17 -O2 main.cpp src/*.cpp -Iinclude -o rsa
./rsa
```

### Windows

Using MinGW:

```bash
git clone https://github.com/luca-72/rsa.git
cd rsa
g++ -std=c++17 -O2 main.cpp src/*.cpp -Iinclude -o rsa.exe
rsa.exe
```

## Limitations

This implementation is intended for educational purposes and should not be used for real-world cryptography.

It does not implement modern RSA padding schemes such as OAEP. The message encoding, key generation, and random number generation are simplified for the purposes of the project.

## Project Goals

The goal of this project is to understand the mathematics and algorithms behind RSA by implementing the underlying components directly.

The project covers:

* Arbitrary-precision integer arithmetic
* Modular arithmetic
* Prime generation
* Miller-Rabin primality testing
* Modular inverses
* Modular exponentiation
* RSA key generation
* RSA encryption and decryption
