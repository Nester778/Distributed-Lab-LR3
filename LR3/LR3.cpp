#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

// функція binToHex - перетворює строку бітів у шістнадцятирічну систему
string binToHex(string bin) {
	string res = "";
	int mas[2] = { 0,0 };
	int j = 0;
	for (int x = 0; x < 2; x++) {
		for (int i = 3; i >= 0; i--)
		{
			mas[x] += (bin[j] - '0') * pow(2, i);
			j++;
		}
	}
	for (int i = 0; i < 2; i++)
	{
		switch (mas[i])
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
			res += to_string(mas[i]);
			break;
		}
	}
	return res;
}
// функція hexToBin - зоротня функція яка перетворює строку у шістнадцятирічній системі у тсроку бітів
string hexToBin(string hex)
{
	string res = "";
	int mas[2];
	for (int i = 0; i < 2; i++) {

		switch (hex[i])
		{
		case 'a':
			mas[i] = 10;
			break;
		case 'b':
			mas[i] = 11;
			break;
		case 'c':
			mas[i] = 12;
			break;
		case 'd':
			mas[i] = 13;
			break;
		case 'e':
			mas[i] = 14;
			break;
		case 'f':
			mas[i] = 15;
			break;
		default:
			mas[i] = hex[i] - '0';
			break;
		}
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

// функція textToSbox - функція шифрування алгоритмом S-бокс, який на вхід отримує текст, який необхідно зашифрувати
string textToSbox(string str) {
	string result = "";

	vector<bitset<8>> Bit_str;
	vector<string> hex;
	vector<string> res;

	// масив mas - це таблиця за якою буде відбуватися заміна. Було вирішено використовувати массив строк, 
	// так як у початковій таблиці значання розташовані по порядку, та до них зручно звертатися за індексом
	string mas[16];
	mas[0] = "637c777bf26b6fc53001672bfed7ab76";
	mas[1] = "ca82c97dfa5947f0add4a2af9ca472c0";
	mas[2] = "b7fd9326363ff7cc34a5e5f171d83115";
	mas[3] = "04c723c31896059a071280e2eb27b275";
	mas[4] = "09832c1a1b6e5aa0523bd6b329e32f84";
	mas[5] = "53d100ed20fcb15b6acbbe394a4c58cf";
	mas[6] = "d0efaafb434d338545f9027f503c9fa8";
	mas[7] = "51a3408fe19d38f5bcb6da2110fff3d2";
	mas[8] = "cd0c13ec5f974417c4a77e3d645d1973";
	mas[9] = "60814fdc222a908846eeb814de5e0bdb";
	mas[10] = "e0323a0a4906245cc2d3ac629195e479";
	mas[11] = "e7c8376d8dd54ea96c56f4ea657aae08";
	mas[12] = "ba78252e1ca6b4c6e8dd741f4bbd8b8a";
	mas[13] = "703eb5664803f60e613557b986c11d9e";
	mas[14] = "92f8981169d98e949b1e87e9ce5528df";
	mas[15] = "8ca1890dbfe6426841992d0fb054bb16";

	// Наступний цикл перетворюе кожну литеру тексту у 8 біт
	for (int i = 0; i < str.size(); i++) {
		Bit_str.push_back(bitset<8>(str[i]));
	}

	// Наступний цикл переводе двійкову строку у шістнадцятирічну
	for (int i = 0; i < Bit_str.size(); i++)
		hex.push_back(binToHex(Bit_str[i].to_string()));

	// Наступний цикл знаходить у таблиці необхідне значення та записуе його у результат
	for (int i = 0; i < hex.size(); i++) {
		string s = "";
		int a, b;

		// наступні свічі потрібні для переведення 16 у 10, щоб за отриманими індексами знайти значення у таблиці
		switch (hex[i][0])
		{
		case 'a':
			a = 10;
			break;
		case 'b':
			a = 11;
			break;
		case 'c':
			a = 12;
			break;
		case 'd':
			a = 13;
			break;
		case 'e':
			a = 14;
			break;
		case 'f':
			a = 15;
			break;
		default:
			a = hex[i][0] - '0';
			break;
		}
		switch (hex[i][1])
		{
		case 'a':
			b = 10;
			break;
		case 'b':
			b = 11;
			break;
		case 'c':
			b = 12;
			break;
		case 'd':
			b = 13;
			break;
		case 'e':
			b = 14;
			break;
		case 'f':
			b = 15;
			break;
		default:
			b = hex[i][1] - '0';
			break;
		}

		s += mas[a][b * 2];
		s += mas[a][(b * 2) + 1];
		res.push_back(s);
	}

	// переведення результату у текст
	for (int i = 0; i < res.size(); i++) {
		bitset<8> bits(hexToBin(res[i]));
		result += static_cast<char>(bits.to_ulong());
	}

	return result;
}
// функція SboxToText - функція дешифрування алгоритмом S-бокс, який на вхід отримує зашифрований текст
string SboxToText(string str)
{
	string result = "";
	vector<bitset<8>> Bit_str;
	vector<string> hex;
	vector<string> res;

	// для зворотньої таблиці було використано map, так як у цій таблиці значення розташовані не по порядку, а map 
	// працює як ключ-значення.
	map<string, string> table;
	table["63"] = "00"; table["7c"] = "01"; table["77"] = "02"; table["7b"] = "03"; table["f2"] = "04"; table["6b"] = "05"; table["6f"] = "06"; table["c5"] = "07"; table["30"] = "08"; table["01"] = "09"; table["67"] = "0a"; table["2b"] = "0b"; table["fe"] = "0c"; table["d7"] = "0d"; table["ab"] = "0e"; table["76"] = "0f";
	table["ca"] = "10"; table["82"] = "11"; table["c9"] = "12"; table["7d"] = "13"; table["fa"] = "14"; table["59"] = "15"; table["47"] = "16"; table["f0"] = "17"; table["ad"] = "18"; table["d4"] = "19"; table["a2"] = "1a"; table["af"] = "1b"; table["9c"] = "1c"; table["a4"] = "1d"; table["72"] = "1e"; table["c0"] = "1f";
	table["b7"] = "20"; table["fd"] = "21"; table["93"] = "22"; table["26"] = "23"; table["36"] = "24"; table["3f"] = "25"; table["f7"] = "26"; table["cc"] = "27"; table["34"] = "28"; table["a5"] = "29"; table["e5"] = "2a"; table["f1"] = "2b"; table["71"] = "2c"; table["d8"] = "2d"; table["31"] = "2e"; table["15"] = "2f";
	table["04"] = "30"; table["c7"] = "31"; table["23"] = "32"; table["c3"] = "33"; table["18"] = "34"; table["96"] = "35"; table["05"] = "36"; table["9a"] = "37"; table["07"] = "38"; table["12"] = "39"; table["80"] = "3a"; table["e2"] = "3b"; table["eb"] = "3c"; table["27"] = "3d"; table["b2"] = "3e"; table["75"] = "3f";
	table["09"] = "40"; table["83"] = "41"; table["2c"] = "42"; table["1a"] = "43"; table["1b"] = "44"; table["6e"] = "45"; table["5a"] = "46"; table["a0"] = "47"; table["52"] = "48"; table["3b"] = "49"; table["d6"] = "4a"; table["b3"] = "4b"; table["29"] = "4c"; table["e3"] = "4d"; table["2f"] = "4e"; table["84"] = "4f";
	table["53"] = "50"; table["d1"] = "51"; table["00"] = "52"; table["ed"] = "53"; table["20"] = "54"; table["fc"] = "55"; table["b1"] = "56"; table["5b"] = "57"; table["6a"] = "58"; table["cb"] = "59"; table["be"] = "5a"; table["39"] = "5b"; table["4a"] = "5c"; table["4c"] = "5d"; table["58"] = "5e"; table["cf"] = "5f";
	table["d0"] = "60"; table["ef"] = "61"; table["aa"] = "62"; table["fb"] = "63"; table["43"] = "64"; table["4d"] = "65"; table["33"] = "66"; table["85"] = "67"; table["45"] = "68"; table["f9"] = "69"; table["02"] = "6a"; table["7f"] = "6b"; table["50"] = "6c"; table["3c"] = "6d"; table["9f"] = "6e"; table["a8"] = "6f";
	table["51"] = "70"; table["a3"] = "71"; table["40"] = "72"; table["8f"] = "73"; table["e1"] = "74"; table["9d"] = "75"; table["38"] = "76"; table["f5"] = "77"; table["bc"] = "78"; table["b6"] = "79"; table["da"] = "7a"; table["21"] = "7b"; table["10"] = "7c"; table["ff"] = "7d"; table["f3"] = "7e"; table["d2"] = "7f";
	table["cd"] = "80"; table["0c"] = "81"; table["13"] = "82"; table["ec"] = "83"; table["5f"] = "84"; table["97"] = "85"; table["44"] = "86"; table["17"] = "87"; table["c4"] = "88"; table["a7"] = "89"; table["7e"] = "8a"; table["3d"] = "8b"; table["64"] = "8c"; table["5d"] = "8d"; table["19"] = "8e"; table["73"] = "8f";
	table["60"] = "90"; table["81"] = "91"; table["4f"] = "92"; table["dc"] = "93"; table["22"] = "94"; table["2a"] = "95"; table["90"] = "96"; table["88"] = "97"; table["46"] = "98"; table["ee"] = "99"; table["b8"] = "9a"; table["14"] = "9b"; table["de"] = "9c"; table["5e"] = "9d"; table["0b"] = "9e"; table["db"] = "9f";
	table["e0"] = "a0"; table["32"] = "a1"; table["3a"] = "a2"; table["0a"] = "a3"; table["49"] = "a4"; table["06"] = "a5"; table["24"] = "a6"; table["5c"] = "a7"; table["c2"] = "a8"; table["d3"] = "a9"; table["ac"] = "aa"; table["62"] = "ab"; table["91"] = "ac"; table["95"] = "ad"; table["e4"] = "ae"; table["79"] = "af";
	table["e7"] = "b0"; table["c8"] = "b1"; table["37"] = "b2"; table["6d"] = "b3"; table["8d"] = "b4"; table["d5"] = "b5"; table["4e"] = "b6"; table["a9"] = "b7"; table["6c"] = "b8"; table["56"] = "b9"; table["f4"] = "ba"; table["ea"] = "bb"; table["65"] = "bc"; table["7a"] = "bd"; table["ae"] = "be"; table["08"] = "bf";
	table["ba"] = "c0"; table["78"] = "c1"; table["25"] = "c2"; table["2e"] = "c3"; table["1c"] = "c4"; table["a6"] = "c5"; table["b4"] = "c6"; table["c6"] = "c7"; table["e8"] = "c8"; table["dd"] = "c9"; table["74"] = "ca"; table["1f"] = "cb"; table["4b"] = "cc"; table["bd"] = "cd"; table["8b"] = "ce"; table["8a"] = "cf";
	table["70"] = "d0"; table["3e"] = "d1"; table["b5"] = "d2"; table["66"] = "d3"; table["48"] = "d4"; table["03"] = "d5"; table["f6"] = "d6"; table["0e"] = "d7"; table["61"] = "d8"; table["35"] = "d9"; table["57"] = "da"; table["b9"] = "db"; table["86"] = "dc"; table["c1"] = "dd"; table["1d"] = "de"; table["9e"] = "df";
	table["92"] = "e0"; table["f8"] = "e1"; table["98"] = "e2"; table["11"] = "e3"; table["69"] = "e4"; table["d9"] = "e5"; table["8e"] = "e6"; table["94"] = "e7"; table["9b"] = "e8"; table["1e"] = "e9"; table["87"] = "ea"; table["e9"] = "eb"; table["ce"] = "ec"; table["55"] = "ed"; table["28"] = "ee"; table["df"] = "ef";
	table["8c"] = "f0"; table["a1"] = "f1"; table["89"] = "f2"; table["0d"] = "f3"; table["bf"] = "f4"; table["e6"] = "f5"; table["42"] = "f6"; table["68"] = "f7"; table["41"] = "f8"; table["99"] = "f9"; table["2d"] = "fa"; table["0f"] = "fb"; table["b0"] = "fc"; table["54"] = "fd"; table["bb"] = "fe"; table["16"] = "ff";


	// наступні 2 цикли перетворюють літери у 16-річну систему
	for (int i = 0; i < str.size(); i++) {
		Bit_str.push_back(bitset<8>(str[i]));
	}

	for (int i = 0; i < Bit_str.size(); i++)
		hex.push_back(binToHex(Bit_str[i].to_string()));

	// наступні 2 цикли знаходять значення у твблиці та записують його до результату
	for (int i = 0; i < hex.size(); i++) {
		res.push_back(table[hex[i]]);
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


int main()
{
	setlocale(LC_ALL, "");

	string str = "qwertyuiopasdfghjklzxcvbnmйцукенгшщзхъфывапролджэячсмитьбюіїєё"; // всі літери
	string str2 = "QWERTYUIOPASDFGHJKLZXCVBNMЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮІЇЄё"; // всі великі літери
	string str3 = "12345679~!@#$%^&*()_+-=|{}<>,.?/"; // цифри та спецсимволи

	cout << "Тест на всі маленькі літери" << endl;
	cout << "Вхідна строка - " << str << endl;
	cout << "Результат шифрування S-блоком - " << endl;
	cout << textToSbox(str) << endl;
	cout << "Результат дешифрування S-блоком - " << SboxToText(textToSbox(str)) << endl;
	cout << endl;
	cout << "Результат шифрування P-блоком - " << textToPbox(str) << endl;
	cout << "Результат дешифрування P-блоком - " << PboxToText(textToPbox(str)) << endl << endl;

	cout << "Тест на всі Великі літери" << endl;
	cout << "Вхідна строка - " << str2 << endl;
	cout << "Результат шифрування S-блоком - " << textToSbox(str2) << endl;
	cout << "Результат дешифрування S-блоком - " << SboxToText(textToSbox(str2)) << endl;
	cout << endl;
	cout << "Результат шифрування P-блоком - " << textToPbox(str2) << endl;
	cout << "Результат дешифрування P-блоком - " << PboxToText(textToPbox(str2)) << endl << endl;

	cout << "Тест на цифри та спецсимволи" << endl;
	cout << "Вхідна строка - " << str3 << endl;
	cout << "Результат шифрування S-блоком - " << textToSbox(str3) << endl;
	cout << "Результат дешифрування S-блоком - " << SboxToText(textToSbox(str3)) << endl;
	cout << endl;
	cout << "Результат шифрування P-блоком - " << textToPbox(str3) << endl;
	cout << "Результат дешифрування P-блоком - " << PboxToText(textToPbox(str3)) << endl;


	return 0;
}
