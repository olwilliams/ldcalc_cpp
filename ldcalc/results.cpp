#include "stdafx.h"
#include "results.h"

results::results(int new_size)
{
	size = new_size;
	absorbance1.resize(size);
	absorbance2.resize(size);
	ld.resize(size);
}

void results::add_point(int time_point, double abs1, double abs2)
{
	absorbance1[time_point] = abs1;
	absorbance2[time_point] = abs2;
	ld[time_point] = abs1 - abs2;
}

void results::print()
{
	using namespace std;
	cout << "\nLinear Dichroism: ";
	for (int n = 0; n < size; n++)
	{
		cout << ld[n] << " ";
	}
	cout << endl;
}

void results::change_size(int new_size)
{
	size = new_size;
	absorbance1.resize(size);
	absorbance2.resize(size);
	ld.resize(size);
}