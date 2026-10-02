#pragma once

#include <string>
#include "bigint.h"

std::string stringToString10(std::string s);
void string10ToBigInt(BigInt rez, std::string s);
std::string BigIntToString10(BigInt a);
std::string string10ToString(std::string s);
void read(BigInt message, std::string s);
void write(BigInt a);
void setup();
void encrypt(BigInt ct, std::string s);
void decrypt(BigInt pt, BigInt ct);
void display();