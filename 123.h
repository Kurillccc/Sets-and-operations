#pragma once
#include "TBitField.h"
#include <string>
#include<iostream>
using namespace std;

class TSet
{
private:

	int univ;
	TBitField TB;

public:

	TSet(int u = 0)
	{
		univ = u;
		TB = TBitField(univ);
	}

	TSet(const TSet& tmp)
	{
		univ = tmp.univ;
		TB = tmp.TB;
	}

	~TSet() {}
	

	TSet& operator -(TSet tmp)
	{
		univ = tmp.univ;
		TB = tmp.TB;
		return *this;
	}

	void Add(int k)
	{
		if ((k > 0) && (k <= univ))
		{
			TB.Add(k, univ);
		}
	}

	string TSettostring()
	{
		return TB.Memtostring(univ);
	}

	TSet operator +(TSet tmp)
	{
		TSet res(univ);
		res.TB = TB + tmp.TB;
		return res;
	}

	TSet operator*(TSet tmp)
	{
		TSet res(univ);
		res.TB = TB - tmp.TB;
		return res;
	}

	TSet operator ~()
	{
		TSet res(univ);
		res.TB = ~TB;
		return res;
	}
};
