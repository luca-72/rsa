#pragma once

#include <string>
#include "bigint.h"

std::string string_to_string10(std::string s);
void string10_to_NrMare(NrMare rez, std::string s);
std::string NrMare_to_string10(NrMare a);
std::string string10_to_string(std::string s);
void read(NrMare message, std::string s);
void write(NrMare a);
void setup();
void encrypt(NrMare ct, std::string s);
void decrypt(NrMare pt, NrMare ct);
void display();