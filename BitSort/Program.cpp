#include<iostream>
#include<fstream>
using namespace std;

const int BUFFSIZE = 8152;

unsigned int getbits(unsigned int x, int p, int n) {
	return (x >> (p + 1 - n)) & ~(~0 << n);
}

unsigned int setbit(unsigned int x, int p)
{
	return x | (1 << p);
}

int main(int argc, char* argv[])
{
	unsigned int buff[BUFFSIZE];

	char* filename = nullptr;
	unsigned short num;

	if (argc > 1)
	{
		filename = argv[1];
	}
	else
	{
		cin >> filename;
	}

	ifstream ifs(filename, ios_base::binary);

	if (!ifs)
	{
		return 1;
	}

	while (ifs.read((char*)&num, sizeof(unsigned short)))
	{
		int number = (int)(num);
		int idx = number / 8;
		int pos = number % 8;

		if (getbits(buff[idx], pos, 1) > 0)
		{
			continue;
		}
		buff[idx] = setbit(buff[idx], pos);
	}

	for (int i = 0; i < BUFFSIZE; i++)
	{
		for (int j = 0; j < BUFFSIZE; j++)
		{
			int bit = getbits(buff[i], j, 1);

			if (bit == 0)
			{
				continue;
			}
			cout << (i * 8) + j << endl;
		}
	}

	ifs.close();
	return 0;
}