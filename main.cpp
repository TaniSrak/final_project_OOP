
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <string>

using namespace std;

class IOManager {
public:
	string Read(string path) //прочитать из файла
	{ 
		ifstream readStream(path);
		string readResult;
		getline(readStream, readResult);
		readStream.close();
		return readResult;
	}

	void Write(string data, string path) //записать все в файл
	{
		fstream writeStream(path);
		writeStream << data;
		writeStream.close();
	}

};

class RsaEncryptionService //класс для шифрования и дешифрования 
{
private:
		long int p; //два простых числа
		long int q;
	
		long int n; //модуль открытого числа
		long int t; // функция Эйлера
	
		long int flag; //для проверки простоты числа
		long int e[100]; //целое число, в диапазоне от единицы до t. e и t должны быть взаимно обратными
		long int d[100]; //обратное от е по модулю t
		long int temp[100]; // временная переменная для промежуточных значений
	
		long int j; //переменные итераторы в цикле
		long int i;
	

	int prime(long int pr) //проверка числ на простоту
	{
		int i;
		j = sqrt(pr);
		for (i = 2; i <= j; i++)
		{
			if (pr % i == 0) 
			{
				return 0;
			}
		}
		return 1;
	}
	//вычисления константы д
	long int ComputeD(long int x) 
	{
		long int k = 1; //число которое станет числом д
		while (1) {
			k = k + t;
			if (k % x == 0)
			{
				return (k / x);
			}
		}
	}

	void ComputeE() //вычисления е
	{
		int k = 0; //индекс в числе е
		for (i = 2; i < t; i++)
		{
			if (t % i == 0) 
			{
				continue;
			}
			flag = prime(i);
			if (flag == 1 && i != p && i != q) //простое число или нет
			{
				e[k] = i;
				flag = ComputeD(e[k]); //вычисляем д поразрядно, чтобы не исопльзовать большие числа
				if (flag > 0)
				{
					d[k] = flag;
					k++;
				}
				if (k == 99)
				{
					break;
				}
			}
		}
	}

public:

	char* EncryptData(char* msg) //шифруем
	{
		long int pt; //незашифрованный символ в сообщении
		long int ct; //уже зашифрованный символ
		long int key = e[0]; // ключ для шифрования
		long int k; // временная переменная
		long int len; // длина строки, т.е сообщения

		i = 0;
		len = strlen(msg);
		char* encrypted = new char[len + 1];

		while (i != len)
		{
			pt = msg[i];
			pt -= 96; //константное значение для преобразования из символа в число, взято из пальца
			k = 1;
			for (j = 0; j < key; j++) //шифрование
			{
				k *= pt;
				k %= n;
			}
			temp[i] = k; //формируем зашифрованное сообщение посимвольно
			ct = k + 96;
			encrypted[i] = ct;
			i++;
		}
		encrypted[i] = -1; //закончиалсь строка

		return encrypted;
	}

	char* DecryptData(char* msg) //дешефруем
	{
		long int pt; //незашифрованный символ в сообщении
		long int ct; //уже зашифрованный символ
		long int key = e[0]; // ключ для шифрования
		long int k; // временная переменная

		i = 0;
		char* decrypted = new char[strlen(msg) + 1];

		while (msg[i] != -1)
		{
			ct = temp[i];
			k = 1;
			for (j = 0; j < key; j++)
			{
				k *= ct;
				k %= n;
			}
			pt = k + 96;
			decrypted[i] = pt;
			i++;
		}
		decrypted[i] = -1;

		return decrypted;
	}

	RsaEncryptionService(long int p_, long int q_) //конструктор с параметрамим
	{
		p = p_;
		q = q_;
		n = p * q;
		t = (p - 1) * (q - 1);

		ComputeE();
	}
};

//метод который нам позволит вывести список функций
void DisplayMenu(int stage) {

	switch (stage)
	{
	case 1:
		cout << "1.Read text from file" << endl;
		cout << "2.Read text from command line" << endl;
		break;
	case 2:
		cout << "1.Encrypt" << endl;
		cout << "2.Decrypt" << endl;
		break;
	case 3:
		cout << "Enter file name" << endl;
		break;
	case 4:
		cout << "Enter text" << endl;
		break;
	}
}


void DisplayCharArr(char* arr) {
	for (int i = 0; arr[i] != -1; i++)
	{
		printf("%c", arr[i]);
	}
	cout << endl;
}

//свое преобразование
char* FromStr(string m) {
	char* res = new char[100];
	for (size_t i = 0; i < 100; i++)
	{
		if (i < m.length())
		{
			res[i] = m[i];
		}
		else
		{
			break;
		}
	}
	return res;
}

int main()
{
	RsaEncryptionService rsa = RsaEncryptionService(3, 7);
	IOManager io;

	fflush(stdin);
	char* msg = new char[100];
	string filePath;

	cout << "Rsa tool" << endl;
	cout << "Select action" << endl;
	DisplayMenu(1);

	char inp;
	cin >> inp;

	switch (inp) {
	case '1':
		DisplayMenu(3);
		cin >> filePath;

		msg = FromStr(io.Read(filePath));
		break;
	case '2':
		DisplayMenu(4);
		cin >> msg;
		break;
	}

	DisplayMenu(2);
	cin >> inp;
	switch (inp)
	{
	case '1':
		msg = rsa.EncryptData(msg); //шифруем
		break;
	case '2':
		msg = rsa.DecryptData(msg); //дешефруем
		break;
	}
	DisplayCharArr(msg);
	delete msg;
}
