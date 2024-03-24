#include <iostream>
#include <vector>
#include <random>
#include <string>

using namespace std;

class BigInteger //создаем свой тип данных
{
private:
	bool isNegative;
	std::string value = "0"; //делаем строковый массив для больших чисел

	//умножение
	BigInteger KaratsubaMultiply(const BigInteger &a, const BigInteger &b)
	{
		string val1 = a.GetValue();
		string val2 = b.GetValue();
		
		int len1 = val1.length();
		int len2 = val2.length();
		int len = max(len1, len2); 

		if (len1 = len2 < 9)
		{
			return stol(a.GetValue()) * stol(b.GetValue()); //лонгуем строку
		}

		len += len % 2;
		int n = len / 2;
		//разбиваем числа н а4 части
		BigInteger Xr(len1 > n ? val1.substr(len1 - n, n) : val1);//правая часть 
		BigInteger Xl(a >> n); //левая часть
		BigInteger Yr(len2 > n ? val2.substr(len1 - n, n) : val2); //правая часть
		BigInteger Yl(b >> n); //левая часть

		//перемножаем половинки
		BigInteger P1 = KaratsubaMultiply(Xl, Yl);
		BigInteger P2 = KaratsubaMultiply(Xr, Yr);
		BigInteger P3 = KaratsubaMultiply(Xr + Xl, Yr + Yl);
	}

public:
	string GetValue() const
	{
		return value;
	}

	bool GetNegative()
	{
		return isNegative;
	}


	BigInteger(long x)
	{
		isNegative = x < 0;
		value = to_string(isNegative ? -x:x);
	}

	BigInteger(string x)
	{
		if (x.length() == 0) //пустая ли строка
		{
			isNegative = false;
			value = "0";
			return;
		}

		isNegative = x[0] == '-'; //если минус, то тру
		x = x.substr(isNegative); //удаление

		int count = 0;
		while (x[count] == '0' && x.length() - count > 1) //проряем нули в числе в н ачале
		{
			count++;
		}

		//записываем число без нулей
		value = x.substr(count);
	}
	
	const bool operator == (const BigInteger& x) const //равенство
	{
		return (value == x.GetValue()) && (isNegative == x.isNegative);
	}
	//сравнение ссылок  на не равенство
	const bool operator != (const BigInteger& x)
	{
		return !(*this == x);
	}
	//
	const bool operator < (const BigInteger& x) const
	{
		string v2 = x.GetValue(); 
		size_t l1 = value.length(); //длина первого знчения против второго л1
		size_t l2 = v2.length();

		if (isNegative == x.isNegative)
		{
			if (l1 != l2)
			{
				return(l1 < l2)^ isNegative; //оператор ксора, если длина чисел не равна, то бессмысленно делать дальше проверку
			} //таблица истинности на ксор
			//пример
			//-9981
			//9924
			size_t i = 0;
			while (i < l1 && value[i] == v2[i]) //находим индекс отличноого от других числа
			{
				i++;
			}
			return (i < l1) && ((value[i] < v2[i]) ^ isNegative); //если расхождение будет в пределах
			
		}
		return isNegative;
	}

	//операторы на большее
	const bool operator > (const BigInteger& x) const
	{
		return !(*this < x || *this == x);
	}

	//операторы меньше или ровно
	const bool operator <= (const BigInteger& x) const
	{
		return *this < x || *this == x;
	}

	// >=
	const bool operator >= (const BigInteger& x) const
	{
		return *this > x || *this == x;
	}

	//присваивание
	BigInteger operator=(const BigInteger& x)
	{
		value = x.GetValue();
		isNegative = x.isNegative;

		return *this;
	}

	//унарный минус
	BigInteger operator-() const&&
	{
		return BigInteger(isNegative ? value : "-" + value); //переворачиваем - и +
	}

	//бинарный плюс
	BigInteger operator+(const BigInteger& x) const
	{
		bool addOp = !(x.isNegative ^ isNegative);

		if (addOp)
		{
			string num2 = x.GetValue();

			int len1 = value.length();
			int len2 = num2.length();
			int length = 1 + max(len1, len2);

			string res = string(' ', length + 1);
			res[length - 1] = res[length] = '\0';

			for ( int i = 0; i < length -1; i++)
			{
				int j = length - 1 - i;
				res[j] += ((i < len2) ? (num2[len2 - 1 - i] - '0') : 0) + ((i < len1) ? (value[len1 - 1 - i] - '0') : 0); //складываем разряды
				res[j - 1] = res[j] / 10; //чтобы прибывить разряд
				res[j] = res[j] % 10 + '0'; //прообразование символа в цифру
			}

			res[0] += '0';

			return BigInteger(isNegative ? string("-") + res : res); //возвращаем результат с учетом знака
		}
		else
		{
			return isNegative ? (x - (-BigInteger(*this))) : (*this - (-BigInteger(x))); //разные знаки определем большее и меньшее и возвращаем вычитание
		}
	}


	//битовый бинарный сдвиг
	BigInteger operator<<(int n) const
	{
		return BigInteger(string(isNegative ? "-" : "") + value + string(n, '0'));
	}

	//сдвиг в обратную сторону
	BigInteger operator>>(int n) const
	{
		if (n >= value.length())
		{
			return 0;
		}
		return BigInteger(string(isNegative ? "-" : "") + value.substr(0, value.length() - n));  //срез числа на н элементов
	}


};


class SieveOfEratoshenes //решето добываем простое число
{
private:
	std::vector<bool> _bitArray;
public:
	int* GetRandomSieve(int sieveCount)
	{
		int* result = new int[sieveCount];
		int i = 0;
		while (sieveCount != 0)
		{
			int ind = (rand() % (_bitArray.size() - 0 + 1) + 0) - 1;

			if (!_bitArray[ind])
			{
				result[i] = ind;
				sieveCount--;
				i++;
			}
		}
		//for (int i = 0; i < sieveCount; i++)
		//{

		//	result[i] = _bitArray[rand() % (_bitArray.size() - 0 + 1) + 0]; //не оч, но пока так

		//}
		return result;
	}

	SieveOfEratoshenes(int length) 
	{
		_bitArray = std::vector<bool>(length);
		
		for (int p = 2; p * p < length; p++)
		{
			if (!_bitArray[p]) //для оптимизации
			{
				for (int i = p*p; i < length; i+=p) 
				{
					_bitArray[i] = true; //true - это false и наоборот
				}
			}
		}
	}
};

class  Rsa //шифруем
{
private:
	long p;
	long q;
	long n;
	long phiN;
	long e;
	long d;

	long Gdc(long a, long b)
	{
		while (b > 0)
		{
			a %= b;
			std::swap(a, b);
		}
		return a;
	}

	long ComputeEncryption(long m)
	{
		return long(pow(m, e)) / n;
	}
	long ComputeDecryption(long c)
	{
		return long(pow(c, d)) / n;
	}

public:

	std::string Encrypt(std::string srcData)
	{
		std::string result = " ";
		for (int i = 0; i < srcData.size(); i++)
		{
			result += char (ComputeDecryption(int(srcData[i])));
		}
		return result;
	}
	std::string Decrypt(std::string encryptedData)
	{
		std::string result = " ";
		for (int i = 0; i < encryptedData.size(); i++)
		{
			result += char (ComputeDecryption(int(encryptedData[i])));
		}
		return result;
	}
	Rsa()
	{
		SieveOfEratoshenes eratosthenes = SieveOfEratoshenes(5);
		int* sieves = eratosthenes.GetRandomSieve(2);
		p = sieves[0];
		q = sieves[1];

		n = p * q;
		phiN = (p - 1) * (q - 1);

		do{
			e = (rand() % (phiN - 1 + 1) + 1) - 1;
		} while (Gdc(e, phiN) != 1);

		d = 1;
		long res = (d * e) % phiN;
		while (res != d)
		{
			d++;
			res = (d * e) % phiN;
		}
	}
};

int main() {
	setlocale(LC_ALL, "Russian");
	int n;

	srand((unsigned long)time(NULL));
	Rsa r = Rsa();
	std::string data = "test";
	data = r.Encrypt("Test");

	std::cout << data;

	data = r.Decrypt(data);
	std::cout << data;

	return 0;
}