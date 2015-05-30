#include "stdafx.h"
#include "simplex.h"

Simplex::Simplex(int size)
{
	set_dimension(size - 1);
	set_size(size);
}

void Simplex::set_dimension(int dimension)
{
	m_dimension = dimension;
}

void Simplex::set_size(int size)
{
	m_size = size;
	points.resize(size);
}