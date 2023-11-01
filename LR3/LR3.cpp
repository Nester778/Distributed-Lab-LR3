#include <iostream>
#include "SP_Box.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "");

	string str = "qwertyuiopasdfghjklzxcvbnmйцукенгшщзхъфывапролджэячсмитьбюіїєё"; // всі літери
	string str2 = "QWERTYUIOPASDFGHJKLZXCVBNMЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮІЇЄё"; // всі великі літери
	string str3 = "12345679~!@#$%^&*()_+-=|{}<>,.?/"; // цифри та спецсимволи

	cout << "Тест на всі маленькі літери" << endl;
	cout << "Вхідна строка - " << str << endl;
	cout << "Результат шифрування S-блоком - " << endl;
	cout << Sbox(str, true) << endl;
	cout << "Результат дешифрування S-блоком - " << Sbox(Sbox(str, true), false) << endl;
	cout << endl;
	cout << "Результат шифрування P-блоком - " << textToPbox(str) << endl;
	cout << "Результат дешифрування P-блоком - " << PboxToText(textToPbox(str)) << endl << endl;

	cout << "Тест на всі Великі літери" << endl;
	cout << "Вхідна строка - " << str2 << endl;
	cout << "Результат шифрування S-блоком - " << Sbox(str2, true) << endl;
	cout << "Результат дешифрування S-блоком - " << Sbox(Sbox(str2, true), false) << endl;
	cout << endl;
	cout << "Результат шифрування P-блоком - " << textToPbox(str2) << endl;
	cout << "Результат дешифрування P-блоком - " << PboxToText(textToPbox(str2)) << endl << endl;

	cout << "Тест на цифри та спецсимволи" << endl;
	cout << "Вхідна строка - " << str3 << endl;
	cout << "Результат шифрування S-блоком - " << Sbox(str3, true) << endl;
	cout << "Результат дешифрування S-блоком - " << Sbox(Sbox(str3, true), false) << endl;
	cout << endl;
	cout << "Результат шифрування P-блоком - " << textToPbox(str3) << endl;
	cout << "Результат дешифрування P-блоком - " << PboxToText(textToPbox(str3)) << endl;

	return 0;
}
