#pragma once

#include <iostream>
#include <string> 
using namespace std;


class TBitField
{
private:

	unsigned int* mem;
	int size;

	int getnumbermem(int k)
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
		mem = new unsigned int[size];

		for (int i = 0; i < size; i++)
		{
			mem[i] = 0;
		}
	}

	TBitField(const TBitField& tmp)
	{
		size = tmp.size;
		mem = new unsigned int[size];

		for (int i = 0; i < size; i++)
		{
			mem[i] = tmp.mem[i];
		}
	}

	~TBitField()
	{
		delete[] mem;
	}


	TBitField& operator = (TBitField tmp)
	{
		if (size != tmp.size)
		{
			if (size != 0)
			{
				delete[] mem;
			}
			size = tmp.size;
			mem = new unsigned int[size];
		}
		for (int i = 0; i < size; i++)
		{
			mem[i] = tmp.mem[i];
		}

		return *this;
	}

	void Add(int k, int univ)
	{
		if ((k > 0) && (k <= univ))
		{
			mem[getnumbermem(k)] = mem[getnumbermem(k)] | (1 << getnumberBit(k));
		}
	}

	string memtostring(int univ)
	{
		string res = "";

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < (sizeof(int) * 8); j++)
			{
				if (i * sizeof(int) * 8 + j + 1 <= univ)
				{
					if (mem[i] & (1 << j))
					{
						res = res + " " + to_string(i * sizeof(int) * 8 + j + 1);
					}
				}
			}
		}

		return res;
	}

	TBitField operator + (TBitField tmp)
	{
		TBitField res(*this);

		if (size == tmp.size)
		{
			for (int i = 0; i < size; i++)
			{
				res.mem[i] |= tmp.mem[i];
			}
		}

		return res;
	}

	TBitField operator - (TBitField tmp)
	{
		TBitField res(*this);

		if (size == tmp.size)
		{
			for (int i = 0; i < size; i++)
			{
				res.mem[i] &= tmp.mem[i];
			}
		}

		return res;
	}

	TBitField operator ~ ()
	{
		TBitField res(*this);

		for (int i = 0; i < size; i++)
		{
			res.mem[i] = ~mem[i];
		}

		return res;
	}
};