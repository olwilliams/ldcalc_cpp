#pragma once

class dipole
{
private:
	double m_x;
	double m_y;
	double m_z;

public:
	dipole();
	dipole(double x, double y, double z);
	double get_x() { return m_x; }
	double get_y() { return m_y; }
	double get_z() { return m_z; }
	void init(double x, double y, double z);
	void print();

	friend dipole operator+(dipole a, dipole b);
	friend dipole operator*(dipole a, double c);
	friend dipole operator/(dipole a, double c);
};