#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "RU");
	system("chcp 1251 >> null");
	const int N_Max = 100;
	const int dict_max = 25;
	char str[N_Max] = "На завтрак кошка съела миску каши.";
	char dictVowel[dict_max] = "аиоуыэёеюяъь";
	bool flag = false;
	int k = 0;
	
	cout << "\tКОДИРОВКА РУССКИЙ БУКАВ" << endl;
	cout << endl << endl;
	for (int i = -64; i < -32; i++)
	{
		cout << (char)i << " (" << i << ")" << "      ";
		cout << (char)(i + 32) << "(" << i + 32 << ")" << endl;
	}
	
	cout << (char)-72 << " (" << -72 << ")" << "   ";
	cout << (char)-88 << " (" << -88 << ")" << endl;
	cout << '.' << " (" << (int)'.' << ")" << "   ";
	cout << ',' << " (" << (int)',' << ")" << endl;
	cout << '!' << " (" << (int)'!' << ")" << "   ";
	cout << '?' << " (" << (int)'?' << ")" << endl;
	cout << '(' << " (" << (int)'(' << ")" << "   ";
	cout << ')' << " (" << (int)')' << ")" << endl;
	cout << '"' << " (" << (int)'"' << ")" << "   ";
	cout << '-' << " (" << (int)'-' << ")" << endl;
	cout << ':' << " (" << (int)':' << ")" << "   ";
	cout << ';' << " (" << (int)';' << ")" << endl << endl;
	
	cout << str << endl;
	cout << endl;
	cout << "\t\tПолучившаяся строка первого задания (без гласных): " << endl;
	cout << endl;
	for (int i = 0; i < N_Max; i++)
	{
		flag = false;
		for (int j = 0; j < dict_max; j++)
		{
			if (str[i] == dictVowel[j] || (str[i] == (char)((int)dictVowel[j] -32)))
			{
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			str[k] = str[i];
			k++;

		}
	}
	for (int i = k; i < N_Max; i++) {
		 str[i] = '\0';
	}
	cout << str << endl;
	cout << endl;

	ifstream quant("assets\\input.txt");
	if (!quant.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
		return -1;
	}
	string word;
	int N;
	quant >> N;
	quant.close();
	ifstream in("assets\\text.txt");
	if (!in.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
		return -2;
	}
	bool flag_2 = true;
	string result[11];
	string point1;
	bool diff = true;
	int count = 0;


	while (!in.eof())
	{
		in >> word;
		flag_2 = true;
		for (int i = 0; i < word.length(); i++)
		{
			if (!((word[i] >= -64) && (word[i] <= -1) || (word[i] == -72) || (word[i] == -88) || (word[i] == 45))) {
				if (((word[i] >= 65) && (word[i] <= 90)) || ((word[i] >= 97) && (word[i] <= 122))) {
					flag_2 = false;
					break;
				}
				word.erase(i, word.length());
			}
			else
				word[i] = tolower(word[i]);
		}
		for (int i = 0; i < word.length(); i++)
		{
			if ((word[i] != 45) && (word[i] > word[i + 1]))
			{
				flag_2 = false;
				break;
			}
			if (word[word.length()-1] == 45)
			{
				word.erase(word.length()-1, word.length());
			}
		}
		if (flag_2)
		{
			if (word.length() > result[N-1].length()) {
				
				diff = true;

				for (int i = N; i > 0; i--)
				{
					if (result[i] == "")
						break;
					if (result[i] == word)
					{
						diff = false;
						break;
					}
				}
				
				if (diff)
				{
					result[N - 1] = word;
					for (int i = 0; i < N; i++)
						for (int j = 0; j < N-1; j++)
						{
							if (result[j].length() < result[j + 1].length())
								swap(result[j], result[j + 1]);
						}
				}
			}

		}
	}
	ofstream fout("assets\\result.txt");
	if (!fout.is_open())
	{
		cout << "Файл не открыт, ошибка" << endl;
		return -3;
	}
	else
	{
		cout << "\t\tПолучившиеся слова второго задания для N = " << N << endl;
		cout << endl;
		for (int i = 0; i < N; i++)
		{
			cout << result[i] << endl;
			fout << result[i] << endl;
		}
		cout << endl;
	}
	

	in.close();
}