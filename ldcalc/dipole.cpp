#include "stdafx.h"
#include "dipole.h"
#include "functions.h"
#include <iostream>
#include <cassert>

dipole::dipole(double x, double y, double z)
{
	init(x, y, z);
}

dipole::dipole()
{
	init(0, 0, 0);
}

void dipole::init(double x, double y, double z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

void dipole::print()
{
	using namespace std;
	cout << "(" << m_x << "," << m_y << "," << m_z << ")";
}

dipole operator+(dipole a, dipole b)
{
	double x = a.m_x + b.m_x;
	double y = a.m_y + b.m_y;
	double z = a.m_z + b.m_z;
	return dipole(x, y, z);
}

dipole operator*(dipole a, double c)
{
	double x = a.m_x * c;
	double y = a.m_y * c;
	double z = a.m_z * c;
	return dipole(x, y, z);
}

dipole operator/(dipole a, double c)
{
	if (c == 0)
	{ 
		std::cerr << "Division by zero is not allowed." << std::endl;
		return a;
	}
	double x = a.m_x / c;
	double y = a.m_y / c;
	double z = a.m_z / c;
	return dipole(x, y, z);
}