#pragma once

#include <string>
#include "bigint.h"

std::string stringToString10(std::string s);
void string10ToBigInt(NrMare rez, std::string s);
std::string BigIntToString10(NrMare a);
std::string string10ToString(std::string s);
void read(NrMare message, std::string s);
void write(NrMare a);
void setup();
void encrypt(NrMare ct, std::string s);
void decrypt(NrMare pt, NrMare ct);
void display();