#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>

using namespace std;

class  RsaEncrypyionService //класс для шифрования и дешифрования 
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

	int prime(long int pr) //проверка числа на простоту
	{
		int i;
		j = sqrt(pr);
		for  ( i = 2; i <= j; i++)
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
		while (1)
		{
			k = k + t;
			if (k % x == 0)
			{
				return (k / x);
			}
		}
	}
	//вычисления е
	void ComputeE()
	{
		int k = 0; //индекс в числе е
		for (i = 2; i < t; i++)
		{
			if (t % i == 0) 
			{
				continue;
			}
			flag = prime(i); //простое число или нет
			if (flag == 1 && i != p && i != q) 
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
	RsaEncrypyionService(long int p_, long int q_) //конструктор с параметрами
	{
		p = p_;
		q = q_;
		n = p * q;
		t = (p - 1) * (q - 1);

		ComputeE();
	}

};

int main() {

	RsaEncrypyionService rsa = RsaEncrypyionService(3, 7);

	fflush(stdin);

	char* msg = new char[100];
	cin >> msg;

	msg = rsa.EncryptData(msg);
	for (int i = 0; msg[i] != -1; i++)
	{
		printf("%c", msg[i]);
	}
	cout << endl;
	//расшифровываем
	msg = rsa.DecryptData(msg);
	for (int i = 0; msg[i] != -1; i++)
	{
		printf("%c", msg[i]);
	}
	

	return 0;
}