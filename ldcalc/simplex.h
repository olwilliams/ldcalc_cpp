#pragma once

#include <vector>
#include "fit.h"

class Simplex
{
private:
	int m_dimension;
	int m_size;
	void set_size(int size);
	void set_dimension(int dimension);

public:
	std::vector<fit> points;

	Simplex(int size);
	fit& operator[](int index)
	{
		return points[index];
	}
	int get_size() { return m_size; }
};