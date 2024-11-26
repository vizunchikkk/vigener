#include <iostream>
#include <string>
#include <algorithm>
#include <Windows.h>
#include <vector>
#include <math.h>

using namespace std;
string alp = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

string RemoveSpacesAndSpecialChars(const string& input)
{
	string result;
	for (char ch : input)
	{
		// Проверяем, является ли символ буквой или цифрой
		if (isalnum(static_cast<unsigned char>(ch)))
		{
			result += ch; // Добавляем символ в результат, если он буква или цифра
		}
	}
	return result;
}

//строим нужный нам ключ
string BuildingKey(string text, string key)
{
	string temp = key;
	if (key.size() >= text.size())
		return key;
	else
	{
		int size = text.size() - key.size();
		int ksize = key.size();
		while (size >= ksize)
		{
			key += temp;
			size -= ksize;
		}
		key += key.substr(0, size);//дополняем оставшиеся символы
		return key;
	}
}


//их можно переделать и под русский алфавит заменив 26 на 32, букву а на а(рус) и установить кодировку 1251
//но и даже тогда при кодировании есть ошибки, из-за самих числовых кодов букв (ё)
string CodeEnglishLanguage(string text, string key)
{
	string temp = "";
	//просто считем по формуле
	for (int i = 0; i < text.size(); i++)
	{
		temp += ((text[i] - 'a' + key[i] - 'a') % 26) + 'a';
	}
	return temp;
}

string DecodeEnglishLanguage(string text, string key)
{
	string temp = "";
	for (int i = 0; i < text.size(); i++)
	{
		temp += (((text[i] - key[i] + 26) + 26) % 26) + 'a';
	}
	return temp;
}

string CodeRussianLanguage(string text, string key)
{
	vector <int> vectorText;//текст
	vectorText.resize(text.size());
	vector <int> vectorKey;//ключ
	vectorKey.resize(text.size());
	//простым перебором ищем нужные буквы, как для текста так и для ключа
	for (int i = 0; i < text.size(); i++)
	{
		for (int j = 0; j < 33; j++)
		{
			if (text[i] == alp[j])
			{
				vectorText[i] = j;
			}
			if (key[i] == alp[j])
			{
				vectorKey[i] = j;
			}
		}
	}
	int pos = 0;//позиция в алфавите
	//считаем по формуле
	for (int i = 0; i < text.size(); i++)
	{
		pos = ((vectorText[i] + vectorKey[i]) % 33);
		text[i] = alp[pos];
	}
	return text;
}

string DecodeRussianLanguage(string text, string key)
{
	vector <int> vectorText;
	vectorText.resize(text.size());
	vector <int> vectorKey;
	vectorKey.resize(text.size());
	for (int i = 0; i < text.size(); i++)
	{
		for (int j = 0; j < 33; j++)
		{
			if (text[i] == alp[j])
			{
				vectorText[i] = j;
			}
			if (key[i] == alp[j])
			{
				vectorKey[i] = j;
			}
		}
	}
	int pos = 0;
	for (int i = 0; i < text.size(); i++)
	{
		pos = ((vectorText[i] - vectorKey[i] + 33) % 33);
		text[i] = alp[pos];
	}
	return text;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int numberSelectedAction;
	string language;
	cout << "Выберите язык:" << endl;
	cout << "	1 - русский," << endl; 
	cout << "	остальное - английский" << endl;
	getline(cin, language);//сделала string, а не int, тк иначе не будет вводиться строка text (getline не хочет работать)
	string text, key;
	if (language == "1")
	{
		SetConsoleCP(1251);//устанавливаем кодировку с которой будет работать алгоритм
		SetConsoleOutputCP(1251);
		cout << "Введите текст (программа работает только с буквами): " << endl;
		getline(cin, text);
		text = RemoveSpacesAndSpecialChars(text);
		transform(text.begin(), text.end(), text.begin(), tolower);
		cout << "Текст, с которым будем работать: " << text << endl;
		cout << "Выберите что хотите сделать с текстом:" << endl;
		cout << "	1 - закодировать," << endl;
		cout << "	2 - раскодировать" << endl;
		cin >> numberSelectedAction;
		if (numberSelectedAction == 1)
		{
			cout << "Введите ключ: " << endl;
			cin >> key;
			key = BuildingKey(text, key);
			text = CodeRussianLanguage(text, key);
			cout << "Зашифрованное: " << text << endl;
			cout << "Расшифровать обратно?" << endl; 
			cout << "	0 - нет," << endl;
			cout << "	1 - да" << endl;
			cin >> numberSelectedAction;
			if (numberSelectedAction == 1)
			{
				text = DecodeRussianLanguage(text, key);
				cout << "Дешифрованное: " << text << endl;
			}
		}
		else if (numberSelectedAction == 2)
		{
			cout << "Введите ключ: " << endl;
			cin >> key;
			key = BuildingKey(text, key);
			text = DecodeRussianLanguage(text, key);
			cout << "Дешифрованное: " << text << endl;
		}
	}
	else
	{
		cout << "Enter the text (the program only works with letters): " << endl;
		getline(cin, text);
		text = RemoveSpacesAndSpecialChars(text);
		transform(text.begin(), text.end(), text.begin(), tolower);
		cout << "The text that we will work with: " << text << endl;
		cout << "Choose what you want to do with the text:" << endl;
		cout << "	1 - encode," << endl;
		cout << "	2 - decode" << endl;
		cin >> numberSelectedAction;
		if (numberSelectedAction == 1)
		{
			cout << "Enter the key: " << endl;
			cin >> key;
			key = BuildingKey(text, key);
			text = CodeEnglishLanguage(text, key);
			cout << "Encrypted: " << text << endl;
			cout << "Decrypt it back?" << endl;
			cout << "	0 - no,"<< endl;
			cout << "	1 - yes" << endl;
			cin >> numberSelectedAction;
			if (numberSelectedAction == 1)
			{
				text = DecodeEnglishLanguage(text, key);
				cout << "Decrypted: " << text << endl;
			}
		}
		else if (numberSelectedAction == 2)
		{
			cout << "Enter the key: " << endl;
			cin >> key;
			key = BuildingKey(text, key);
			text = DecodeEnglishLanguage(text, key);
			cout << "Decrypted: " << text << endl;
		}
	}

	system("pause");
	return 0;
}