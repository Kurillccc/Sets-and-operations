#pragma once
#include <string> 
#include <iostream>
using namespace std;

class TBitField
{
private:

	unsigned int* Mem;
	int size;

	int getnumberMem(int k)
	{
		return ((k - 1) / (sizeof(unsigned int) * 8));
	}

	int getnumberBit(int k)
	{
		return ((k - 1) % (sizeof(unsigned int) * 8));
	}

public:

	TBitField(int univ = 0)
	{
		size = univ / (sizeof(unsigned int) * 8) + 1;
		Mem = new unsigned int[size];

		for (int i = 0; i < size; i++)
		{
			Mem[i] = 0;
		}
	}

	TBitField(const TBitField& tmp)
	{
		size = tmp.size;
		Mem = new unsigned int[size];

		for (int i = 0; i < size; i++)
		{
			Mem[i] = tmp.Mem[i];
		}
	}

	~TBitField()
	{
		delete[]Mem;
	}


	TBitField& operator=(TBitField tmp)
	{
		if (size != tmp.size)
		{
			if (size != 0)
			{
				delete[] Mem;
			}
			size = tmp.size;
			Mem = new unsigned int[size];
		}
		for (int i = 0; i < size; i++)
		{
			Mem[i] = tmp.Mem[i];
		}

		return *this;
	}

	void Add(int k, int univ)
	{
		if ((k > 0) && (k <= univ))
		{
			Mem[getnumberMem(k)] = Mem[getnumberMem(k)] | (1 << getnumberBit(k));
		}
	}

	string Memtostring(int univ)
	{
		string res = "";

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < (sizeof(int) * 8); j++)
			{
				if (i * sizeof(int) * 8 + j + 1 <= univ)
				{
					if (Mem[i] & (1 << j))
					{
						res = res + " " + to_string(i * sizeof(int) * 8 + j + 1);
					}
				}
			}
		}

		return res;
	}

	TBitField operator+(TBitField tmp)
	{
		TBitField res(*this);

		if (size == tmp.size)
		{
			for (int i = 0; i < size; i++)
			{
				res.Mem[i] |= tmp.Mem[i];
			}
		}

		return res;
	}

	TBitField operator-(TBitField tmp)
	{
		TBitField res(*this);

		if (size == tmp.size)
		{
			for (int i = 0; i < size; i++)
			{
				res.Mem[i] &= tmp.Mem[i];
			}
		}

		return res;
	}

	TBitField operator~()
	{
		TBitField res(*this);

		for (int i = 0; i < size; i++)
		{
			res.Mem[i] = ~Mem[i];
		}

		return res;
	}
};