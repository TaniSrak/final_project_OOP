#include <iostream>
#include <vector>
#include <random>

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
		SieveOfEratoshenes eratosthenes = SieveOfEratoshenes(50);
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