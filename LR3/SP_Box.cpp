#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <cmath>

using namespace std;

// функція hexToDec - цифри з 16-річну у 10-річну
int hexToDec(char hex) {
	int res;
	switch (hex)
	{
	case 'a':
		res = 10;
		break;
	case 'b':
		res = 11;
		break;
	case 'c':
		res = 12;
		break;
	case 'd':
		res = 13;
		break;
	case 'e':
		res = 14;
		break;
	case 'f':
		res = 15;
		break;
	default:
		res = hex - '0';
		break;
	}
	return res;
}

// функція binToHex - перетворює строку бітів у шістнадцятирічну систему
string binToHex(string bin) {
	string res = "";
	int hex = 0;
	int j = 0;
	for (int i = 3; i >= 0; i--) {
		hex += (bin[j] - '0') * pow(2, i);
		j++;
	}
	switch (hex)
	{
	case 10:
		res += "a";
		break;

	case 11:
		res += "b";
		break;

	case 12:
		res += "c";
		break;

	case 13:
		res += "d";
		break;

	case 14:
		res += "e";
		break;

	case 15:
		res += "f";
		break;

	default:
		res += to_string(hex);
		break;
	}

	return res;
}

// функція hexToBin - зоротня функція яка перетворює строку у шістнадцятирічній системі у тсроку бітів
string hexToBin(string hex)
{
	string res = "";
	int mas[2];
	for (int i = 0; i < 2; i++) {
		mas[i] = hexToDec(hex[i]);
	}

	for (int i = 0; i < 2; i++)
	{
		string r = "";
		while (mas[i] > 0)
		{
			r = to_string(mas[i] % 2) + r;
			mas[i] /= 2;
		}
		if (r.size() < 4)
		{
			while (r.size() < 4)
			{
				r = "0" + r;
			}
		}
		res += r;
	}
	return res;
}

// Після перероблення завдання функція Sbox приймае 2 параметри - тест, та булеве значення, якщо true, то треба шифрувати,
// якщо false, то дешифрувати
string Sbox(string str, bool enc) {
	string result = "";
	vector<string> res;

	string table;
	// вибір таблиці. Перша для шифрування, друга для дешифрування.
	if (enc)
		table = "637c777bf26b6fc53001672bfed7ab76ca82c97dfa5947f0add4a2af9ca472c0b7fd9326363ff7cc34a5e5f171d8311504c723c31896059a071280e2eb27b27509832c1a1b6e5aa0523bd6b329e32f8453d100ed20fcb15b6acbbe394a4c58cfd0efaafb434d338545f9027f503c9fa851a3408f929d38f5bcb6da2110fff3d2cd0c13ec5f974417c4a77e3d645d197360814fdc222a908846eeb814de5e0bdbe0323a0a4906245cc2d3ac629195e479e7c8376d8dd54ea96c56f4ea657aae08ba78252e1ca6b4c6e8dd741f4bbd8b8a703eb5664803f60e613557b986c11d9ee1f8981169d98e949b1e87e9ce5528df8ca1890dbfe6426841992d0fb054bb16";
	else
		table = "52096ad53036a538bf40a39e81f3d7fb7ce339829b2fff87348e4344c4dee9cb547b9432a6c2233dee4c950b42fac34e082ea16628d924b2765ba2496d8bd12572f8f66486689816d4a45ccc5d65b6926c704850fdedb9da5e154657a78d9d8490d8ab008cbcd30af7e45805b8b34506d02c1e8fca3f0f02c1afbd0301138a6b3a9111414f67dcea97f2cfcef0b4e67396ac7422e7ad3585e2f937e81c75df6e47f11a711d29c5896fb7620eaa18be1bfc563e4bc6d279209adbc0fe78cd5af41fdda8338807c731b11210592780ec5f60517fa919b54a0d2de57a9f93c99cefa0e03b4dae2af5b0c8ebbb3c83539961172b047eba77d626e169146355210c7d";

	// запис таблиці у зручному вигляді
	vector<vector<string>> mas(16, vector<string>(16));
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++) {
			string a = "";
			mas[i][j] = a + table[0] + table[1];
			table.erase(0, 2);
		}

	// Наступний цикл розбивае вхідні данні на 2 тетради та записує першу до firstTetra, а другу до secondTetra
	vector<string> firstTetra;
	vector<string> secondTetra;

	// наступні 2 цикли отримують значення по яким буде знайдено значення у таблиці
	for (int i = 0; i < str.size(); i++) {
		firstTetra.push_back(bitset<8>(str[i]).to_string().substr(0, 4));
		secondTetra.push_back(bitset<8>(str[i]).to_string().substr(4, 4));
	}

	for (int i = 0; i < firstTetra.size(); i++) {
		firstTetra[i] = binToHex(firstTetra[i]);
		secondTetra[i] = binToHex(secondTetra[i]);
	}

	// Наступні 2 цикли записують у змінну result шифротекст
	for (int i = 0; i < firstTetra.size(); i++) {
		res.push_back(mas[hexToDec(firstTetra[i][0])][hexToDec(secondTetra[i][0])]);
	}

	for (int i = 0; i < res.size(); i++) {
		bitset<8> bits(hexToBin(res[i]));
		result += static_cast<char>(bits.to_ulong());
	}

	return result;
}

// функція textToPbox - функція шифрування алгоритмом P-бокс, який на вхід отримує текст, який необхідно зашифрувати
string textToPbox(string str) {
	string result;
	vector<bitset<8>> Bit_str;
	vector<bitset<8>> Bit_res;

	// mas - масив координат за яким буде зроблено перестановку
	int mas[8] = { 3, 6, 1, 5, 2, 4, 0, 7 };

	for (int i = 0; i < str.size(); i++) {
		Bit_str.push_back(bitset<8>(str[i]));
	}

	// наступний цикл записує до результату біти у порядку, який прописано у mas
	for (int i = 0; i < Bit_str.size(); i++) {
		string res = "";
		for (int j = 0; j < 8; j++)
			res += Bit_str[i].to_string()[mas[j]];
		Bit_res.push_back(bitset<8>(res));
	}

	for (int i = 0; i < Bit_res.size(); i++) {
		result += static_cast<char>(Bit_res[i].to_ulong());
	}

	return result;
}

// функція PboxToText - функція дешифрування алгоритмом P-бокс, який на вхід отримує зашифрований текст
string PboxToText(string str) {
	string result;
	vector<bitset<8>> Bit_str;
	vector<bitset<8>> Bit_res;
	char res[8];
	int mas[8] = { 3, 6, 1, 5, 2, 4, 0, 7 };

	for (int i = 0; i < str.size(); i++) {
		Bit_str.push_back(bitset<8>(str[i]));
	}

	// наступний цикл записує до результату біти у порядку, який прописано у mas
	for (int i = 0; i < Bit_str.size(); i++) {
		for (int j = 0; j < 8; j++)
			res[mas[j]] = Bit_str[i].to_string()[j];
		string s = "";

		for (int j = 0; j < 8; j++)
			s += res[j];
		Bit_res.push_back(bitset<8>(s));
	}

	for (int i = 0; i < Bit_res.size(); i++) {
		result += static_cast<char>(Bit_res[i].to_ulong());
	}

	return result;
}