#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <boost/multiprecision/cpp_int.hpp>


using namespace std;
using namespace boost::multiprecision;


//это я оставлю на память

//class BigInteger //создаем свой тип данных
//{
//private:
//	bool isNegative;
//	std::string value = "0"; //делаем строковый массив для больших чисел
//
//	//умножение
//	BigInteger KaratsubaMultiply(const BigInteger &a, const BigInteger &b) const
//	{
//		string val1 = a.GetValue();
//		string val2 = b.GetValue();
//		
//		int len1 = val1.length();
//		int len2 = val2.length();
//		int len = max(len1, len2); 
//
//		if (len1 = len2 < 9)
//		{
//			return stol(a.GetValue()) * stol(b.GetValue()); //лонгуем строку
//		}
//
//		len += len % 2;
//		int n = len / 2;
//		//разбиваем числа н а4 части
//		BigInteger Xr(len1 > n ? val1.substr(len1 - n, n) : val1);//правая часть 
//		BigInteger Xl(a >> n); //левая часть
//		BigInteger Yr(len2 > n ? val2.substr(len1 - n, n) : val2); //правая часть
//		BigInteger Yl(b >> n); //левая часть
//
//		//перемножаем половинки
//		BigInteger P1 = KaratsubaMultiply(Xl, Yl);
//		BigInteger P2 = KaratsubaMultiply(Xr, Yr);
//		BigInteger P3 = KaratsubaMultiply(Xr + Xl, Yr + Yl);
//
//		//вернуть результирующее число со сдвигами
//		return (P1 << len) + ((P3 - P2 - P1) << n) + P2;
//	}
//
//public:
//	string GetValue() const
//	{
//		return value;
//	}
//
//	bool GetNegative() const
//	{
//		return isNegative;
//	}
//	//возводим число в степени n
//	BigInteger Pow(long n) const
//	{
//		if (!n)
//		{
//			return 1;
//		}
//		//0101
//		//0001
//		//0000
//		//оч хитрая системая возведения в степень, необходимо изучить
//		if (n & 1) //оператор адреса переменной, проерка на четнотсь
//		{
//			return Pow(n - 1) * *this; //возводим в степень нечетные, зачем-то минусуем 1, потом умножаем
//		}
//		else
//		{
//			BigInteger tmp = Pow(n / 2); //четные зачем-то делим, потом умножаем
//			return tmp * tmp;
//		}
//	}
//
//	BigInteger(long x)
//	{
//		isNegative = x < 0;
//		value = to_string(isNegative ? -x:x);
//	}
//
//	BigInteger(string x)
//	{
//		if (x.length() == 0) //пустая ли строка
//		{
//			isNegative = false;
//			value = "0";
//			return;
//		}
//
//		isNegative = x[0] == '-'; //если минус, то тру
//		x = x.substr(isNegative); //удаление
//
//		int count = 0;
//		while (x[count] == '0' && x.length() - count > 1) //проряем нули в числе в н ачале
//		{
//			count++;
//		}
//
//		//записываем число без нулей
//		value = x.substr(count);
//	}
//	
//	const bool operator == (const BigInteger& x) const //равенство
//	{
//		return (value == x.GetValue()) && (isNegative == x.isNegative);
//	}
//	//сравнение ссылок  на не равенство
//	const bool operator != (const BigInteger& x)
//	{
//		return !(*this == x);
//	}
//	//
//	const bool operator < (const BigInteger& x) const
//	{
//		string v2 = x.GetValue(); 
//		size_t l1 = value.length(); //длина первого знчения против второго л1
//		size_t l2 = v2.length();
//
//		if (isNegative == x.isNegative)
//		{
//			if (l1 != l2)
//			{
//				return(l1 < l2)^ isNegative; //оператор ксора, если длина чисел не равна, то бессмысленно делать дальше проверку
//			} //таблица истинности на ксор
//			//пример
//			//-9981
//			//9924
//			size_t i = 0;
//			while (i < l1 && value[i] == v2[i]) //находим индекс отличноого от других числа
//			{
//				i++;
//			}
//			return (i < l1) && ((value[i] < v2[i]) ^ isNegative); //если расхождение будет в пределах
//			
//		}
//		return isNegative;
//	}
//
//	//операторы на большее
//	const bool operator > (const BigInteger& x) const
//	{
//		return !(*this < x || *this == x);
//	}
//
//	//операторы меньше или ровно
//	const bool operator <= (const BigInteger& x) const
//	{
//		return *this < x || *this == x;
//	}
//
//	// >=
//	const bool operator >= (const BigInteger& x) const
//	{
//		return *this > x || *this == x;
//	}
//
//	//присваивание
//	BigInteger operator=(const BigInteger& x)
//	{
//		value = x.GetValue();
//		isNegative = x.isNegative;
//
//		return *this;
//	}
//
//	//унарный минус
//	BigInteger operator-() const&&
//	{
//		return BigInteger(isNegative ? value : "-" + value); //переворачиваем - и +
//	}
//
//	//бинарный плюс
//	BigInteger operator+(const BigInteger& x) const
//	{
//		bool addOp = !(x.isNegative ^ isNegative);
//
//		if (addOp)
//		{
//			string num2 = x.GetValue();
//
//			int len1 = value.length();
//			int len2 = num2.length();
//			int length = 1 + max(len1, len2);
//
//			string res = string(' ', length + 1);
//			res[length - 1] = res[length] = '\0';
//
//			for ( int i = 0; i < length -1; i++)
//			{
//				int j = length - 1 - i;
//				res[j] += ((i < len2) ? (num2[len2 - 1 - i] - '0') : 0) + ((i < len1) ? (value[len1 - 1 - i] - '0') : 0); //складываем разряды
//				res[j - 1] = res[j] / 10; //чтобы прибывить разряд
//				res[j] = res[j] % 10 + '0'; //прообразование символа в цифру
//			}
//
//			res[0] += '0';
//
//			return BigInteger(isNegative ? string("-") + res : res); //возвращаем результат с учетом знака
//		}
//		else
//		{
//			return isNegative ? (x - (-BigInteger(*this))) : (*this - (-BigInteger(x))); //разные знаки определем большее и меньшее и возвращаем вычитание
//		}
//	}
//
//
//	//битовый бинарный сдвиг
//	BigInteger operator<<(int n) const
//	{
//		return BigInteger(string(isNegative ? "-" : "") + value + string(n, '0'));
//	}
//
//	//сдвиг в обратную сторону
//	BigInteger operator>>(int n) const
//	{
//		if (n >= value.length())
//		{
//			return 0;
//		}
//		return BigInteger(string(isNegative ? "-" : "") + value.substr(0, value.length() - n));  //срез числа на н элементов
//	}
//
//	//бинарный минус
//	BigInteger operator - (const BigInteger& x) const
//	{
//		if (*this == x) //если числа одинаковые
//		{
//			return 0;
//		}
//		if (!isNegative && !x.isNegative) //если оба числа положительные, то мы вычитаем
//		{
//			string value2 = x.GetValue();
//
//			int len1 = value.length();
//			int len2 = value2.length();
//
//			int len = max(len1, len2);
//
//			bool isNegativeResult = x > *this;
//			int *a= new int [len], *b= new int[len]; //делаем массив 
//
//			a[0] = b[0] = 0;
//
//			char* result = new char[len + 1];
//			result[len - 1] = result[len] = '\0';
//
//			int sing = (1 * isNegative - 1); //из була в числовое значение
//
//			for (int i = 0; i < len - 1; i++) //проходимся по индексам
//			{
//				a[i] += (i < len1) ? (value[len1 - 1 - i] - '0') : 0;
//				b[i] += (i < len2) ? (value2[len2 - 1 - i] - '0') : 0;
//
//				b[i + 1] = -isNegativeResult;
//				a[i + 1] = isNegativeResult - 1;
//
//				result[len - 1 - i] += 10 + sing * (b[i] - a[i]); //вычитаем само число
//				result[len - 1 - i - 1] = result[len - 1 - i] / 10; //занимаем десятку
//				result[len - 1 - i] = result[len - 1 - i] % 10 + '0'; //преобразование в число
//
//			}
//			a[len - 1] += (len - 1 < len1) * (value[0] - '0');
//			b[len - 1] += (len - 1 < len2) * (value[0] - '0');
//				//полученное значение записываем в результат
//			result[0] += sing * (b[len - 1] - a[len - 1]) + '0';
//			//преобразуем все в наш тип данных, при условии что все знаки одинаоквые
//			BigInteger res = BigInteger(isNegativeResult ? string("-") + string(result) : string(result));
//
//			delete[] a;
//			delete[] b;
//			delete[] result;
//
//			return res;
//		}
//		else
//		{
//			//возвращаем все с разными (просто сложив) и минусовыми знаками(предварительно поменяв местами и перевернув знаки)
//			return isNegative && x.isNegative ? (-BigInteger(x) - (-BigInteger(*this))) : (*this + -BigInteger(x));
//		}
//	}
//
//	//бинарное умножение
//	BigInteger operator*(const BigInteger& x) const
//	{
//		if (value == "0" || x.GetValue() == "0")//если хотя бы 1 число равно 0
//		{
//			return 0;
//		}
//
//		string value2 = x.GetValue();
//
//		int len1 = value.length();
//		int len2 = value2.length();
//		int len = len1 + len2 + 1;
//
//		bool isNegativeResult = isNegative ^ x.isNegative; //ксор для кмножений между собой плюсов и минусов
//
//		if (len < 10) //если результирующая длина двух чисел меньше 10
//		{
//			long res = stol(value) * stol(value2);
//			return BigInteger(isNegativeResult ? -res : res);
//		}
//		else
//		{
//			BigInteger result = KaratsubaMultiply(*this, x);
//			return isNegativeResult ? -BigInteger(result) : result; //результирующее число
//		}
//	}
//
//	//бинарное деление
//	BigInteger operator/(const BigInteger& x) const
//	{
//		string value1 = value;
//		string value2 = x.GetValue();
//
//		if (value2[0] != '0') // не даем делить на 0
//		{
//			if (value[0] == '0') //но непосредственно сам 0 даем делить
//			{
//				return 0;
//			}
//			//равняет ли второе значение 1
//			if (value2 == "1")
//			{
//				return BigInteger(x.isNegative ? -BigInteger(*this) : *this);
//			}
//			//проверка ноликов в числе
//			int zeroCount = 0;
//			while (value[value2.length() - 1 - zeroCount] == '0')
//			{
//				zeroCount++;
//			}
//			if (zeroCount >= value.length())
//			{
//				return 0;
//			}
//
//			//прощай круглые числа с нулями в конце
//			if (zeroCount)
//			{
//				value1 = value1.substr(0, value.length() - zeroCount);
//				value2 = value2.substr(0, value.length() - zeroCount);
//			}
//			//определяем знак числа
//			bool isNegativeResult = isNegative ^ x.isNegative;
//
//			BigInteger tmp(value2);
//
//			int divLength = value1.length(); //длина делителя
//			long divV = divLength > 8 ? 0 : atol(value2.c_str()); //преобразовывем делитель
//
//			int length = value.length();//длина делимого
//			int index = 0;
//
//			string divResult;
//			string divTmp;
//
//
//			while (BigInteger(divTmp) < tmp && index < length)
//			{
//				divTmp += value1[index++];
//			}
//			do
//			{
//				int count = 0;
//				if (BigInteger(divTmp) >= tmp) //проверка второго числа что оно меньше или ровно делителя
//				{
//					if (divLength > 8) //помещается ли наше чисо в 8
//					{
//						BigInteger mod = divTmp;
//						while (mod >= tmp)
//						{
//							mod -= tmp;
//							count++;
//						}
//						divTmp = mod.GetValue();
//					}
//					else
//					{
//						long mod = stol(divTmp); //записываем результат
//						count = mod / divV;
//						divTmp = to_string(mod % divV);
//					}
//				}
//				divResult += count + '0'; //проверка индекса, меньше ли он длины числа
//				if (index <= length)
//				{
//					divTmp += value[index++];
//				}
//			} while (index <= length);
//			return BigInteger(isNegativeResult && divResult != "0" ? string("-") + divResult : divResult);
//		}
//		//по хорошему кинуть ошибку
//	}
//
//	//бинарный процент
//	BigInteger operator%(const BigInteger x) const
//	{
//		string value2 = x.GetValue();
//
//		if (value[0] == '0')
//		{
//			//ошибка деленя на 0
//		}
//
//		if (value[0] == '0' || value2 == "1")
//		{
//			return 0;
//		}
//
//		if (value.length() < 9 || value2.length() < 9)
//		{
//			long res = stol(value) % stol(value2);
//			return isNegative ? -res : res;
//		}
//
//		BigInteger tmp(value2);
//		int divLen = value2.length();
//		long divV = divLen >= 9 ? 0 : atol(value2.c_str());
//		int len = value.length();
//		int index = 0;
//
//		BigInteger mod = value;
//		string v;
//
//		while (BigInteger(v) < tmp && index < len)
//		{
//			v += value[index++];
//		}
//		do
//		{
//			if (BigInteger(v) >= tmp)
//			{
//				if (divV)
//				{
//					v = to_string(stol(v) % divV);
//				}
//				else
//				{
//					BigInteger mod2 = v;
//					while (mod2 >= tmp)
//					{
//						mod2 -= tmp;
//					}
//					v = mod2.GetValue();
//				}
//			}
//			if (index <= len)
//			{
//				mod = v;
//				v += value[index++];
//			}
//		}
//		while (index <= len);
//
//		if (mod.GetValue() == "0")
//		{
//			return 0;
//		}
//		return isNegative ? -BigInteger(mod) : mod;
//	}
//
//	//бинарный +=
//	BigInteger operator += (const BigInteger& x)
//	{
//		return *this = *this + x;
//	}
//
//	//бинарный -=
//	BigInteger operator -= (const BigInteger& x)
//	{
//		return *this = *this - x;
//	}
//
//	//бинарное *=
//	BigInteger operator -= (const BigInteger& x)
//	{
//		return *this = *this * x;
//	}
//
//	//бинарное /=
//	BigInteger operator /= (const BigInteger& x)
//	{
//		return *this = *this / x;
//	}
//
//	//бинарный %=
//	BigInteger operator %= (const BigInteger& x)
//	{
//		return *this = *this % x;
//	}
//
//};
//
////вывод числа в выходной поток
//ostream &operator <<(ostream& stream, const BigInteger &x)
//{
//	if (x.GetNegative())
//	{
//		stream << "-";
//	}
//	return stream << x.GetValue();
//}
//
////ввод числа из входного потока
//istream& operator >> (istream& stream,  BigInteger& x)
//{
//	string value;
//	stream >> value;
//	x = BigInteger(value);
//
//	return stream;
//}


class SieveOfEratoshenes //решето эратосфена добываем простое число
{
private:
	std::vector<bool> _bitArray;
public:
	int1024_t* GetRandomSieve(int sieveCount)
	{
		int1024_t* result = new int1024_t[sieveCount];
		int i = 0;
		while (sieveCount != 0)
		{
			int ind = (rand() % (_bitArray.size() - 1 + 1) + 1) - 1;

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
		
		for (size_t p = 2; p * p < length; p++)
		{
			if (!_bitArray[p]) //для оптимизации
			{
				for (size_t i = p*p; i < length; i+=p)
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
	int1024_t p;
	int1024_t q;
	int1024_t n;
	int1024_t phiN;
	int1024_t e;
	int1024_t d;

	int1024_t Gdc(int1024_t a, int1024_t b)
	{
		while (b > 0)
		{
			a %= b;
			std::swap(a, b);
		}
		return a;
	}

	//создаем свой pow
	int1024_t BigPow(int1024_t x, int1024_t power)
	{
		int1024_t result = x;
		for (size_t i = 1; i < power; i++)
		{
			result *= x;
		}
		return result;
	}

	int1024_t ComputeEncryption(int1024_t m)
	{
		return int1024_t(BigPow(m, e)) / n;
	}
	int1024_t ComputeDecryption(int1024_t c)
	{
		return int1024_t(BigPow(c, d)) / n;
	}
	//преоразователь из строки в 1024
	int1024_t FromString(string s)
	{
		int1024_t result = 0;
		int i = s.size() - 1;
		while (i != -1)
		{
			int distance = (s.size() - 1) - i;
			int1024_t powRes = (BigPow(10, distance));
			string c = s.substr(i, 1);
			int1024_t temp = atoi(&s[i]) * powRes;
			result += temp;
			i--;
		}
		return result;
	}

public:
	Rsa()
	{
		SieveOfEratoshenes eratosthenes = SieveOfEratoshenes(25);
		int1024_t* sieves = eratosthenes.GetRandomSieve(2);
		p = sieves[0];
		q = sieves[1];

		n = p * q;
		phiN = (p - 1) * (q - 1);

		do{
			e = (rand() % (phiN - 1 + 1) + 1) - 1;
		} while (Gdc(e, phiN) != 1);

		d = 1;
		int1024_t res = (d * e) % phiN;
		while (res != d)
		{
			d++;
			res = (d * e) % phiN;
		}
	}

	//стрингу принимает и стрингу возвращает // шифруем
	string Encrypt(string data)
	{
		string result = "";
		for (int i = 0; i < data.size(); i++)
		{
			result += to_string(ComputeEncryption((int)data[i])) + ".";
		}
		return result;
	}

	//расшифровка
	string Decrypt(string data)
	{
		string delemiter = ".";
		string result = "";
		int dInd = data.find(delemiter);

		while (dInd != -1 && dInd != data.size() - 1)
		{
			string token = data.substr(0, data.find(delemiter));
			result += (char)((int)ComputeDecryption(FromString(token)));
			data = data.substr(dInd + 1, data.size());
			dInd = data.find(delemiter);
		}
		return result;
	}
};

int main() {
	setlocale(LC_ALL, "Russian");
	int n;

	srand((unsigned long)time(NULL));

	Rsa r = Rsa();
	string test = "Hello";

	test = r.Encrypt(test);
	cout << test;
	
	test = r.Decrypt(test);
	cout << test;

	return 0;
}