# Educational RSA Implementation (from scratch)

A pure C++ educational implementation of the RSA public-key cryptosystem.  
No external big-integer or cryptographic libraries are used.

## Mathematical foundation

RSA security rests on the difficulty of factoring the product of two large primes.

1. Choose two distinct primes \(p, q\).
2. Compute the modulus \(N = p \cdot q\).
3. Compute Euler’s totient \(\varphi(N) = (p-1)(q-1)\).
4. Choose a public exponent \(e\) coprime to \(\varphi(N)\) (here fixed to \(65537\)).
5. Compute the private exponent \(d\) as the modular inverse of \(e\) modulo \(\varphi(N)\):
   \[
   d \equiv e^{-1} \pmod{\varphi(N)}.
   \]
6. Encryption of a message \(m\) (\(0 \le m < N\)):
   \[
   c \equiv m^{e} \pmod{N}.
   \]
7. Decryption:
   \[
   m \equiv c^{d} \pmod{N}.
   \]

## Implementation overview

| `bigint`    | Arbitrary-precision arithmetic in base \(10^{8}\) (addition, subtraction, multiplication, division, modular exponentiation, extended Euclidean algorithm). |
| `primality` | Random prime generation (64-bit) via Miller–Rabin probabilistic primality test + small-prime sieve. |
| `rsa`       | Key generation, message encoding/decoding (ASCII → decimal digits → big-integer), encryption and decryption. |

Messages longer than a few characters are split into 4-byte blocks, each encrypted independently.

## Build & run

```bash
g++ -std=c++17 -O2 main.cpp src/*.cpp -Iinclude -o rsa
./rsa
