#include <iostream>
#include <string>
using namespace std;

#pragma once

int hexToDec(char hex);
string binToHex(string bin);
string hexToBin(string hex);
string Sbox(string str, bool enc);
string textToPbox(string str);
string PboxToText(string str);