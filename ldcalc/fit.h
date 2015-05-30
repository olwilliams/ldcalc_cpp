#pragma once

#include <vector>

class fit
{
public:
	std::vector<double> parameters;

	fit()
	{
		parameters.resize(3);
		set_tau(0);
		set_amplitude(0);
		set_constant(0);
	}

	fit(double tau, double amplitude, double constant)
	{
		parameters.resize(3);
		set_tau(tau);
		set_amplitude(amplitude);
		set_constant(constant);
	}
	void set_tau(double tau) { parameters[0] = tau; }
	void set_amplitude(double amplitude) { parameters[1] = amplitude; }
	void set_constant(double constant) { parameters[2] = constant; }
	double get_tau() const { return parameters[0]; }
	double get_amplitude() const { return parameters[1]; }
	double get_constant() const { return parameters[2]; }
	int get_dimension() const { return 3; }

	friend fit operator+(const fit a, const fit b);
	friend fit operator-(const fit a, const fit b);
	friend fit operator*(const fit a, const double c);

	double& operator[](int index) { return parameters[index]; }
};

inline fit operator+(const fit a, const fit b)
{
	double tau = a.get_tau() + b.get_tau();
	double amplitude = a.get_amplitude() + b.get_amplitude();
	double constant = a.get_constant() + b.get_constant();
	return fit(tau, amplitude, constant);
}

inline fit operator-(const fit a, const fit b)
{
	double tau = a.get_tau() - b.get_tau();
	double amplitude = a.get_amplitude() - b.get_amplitude();
	double constant = a.get_constant() - b.get_constant();
	return fit(tau, amplitude, constant);
}

inline fit operator*(const fit a, const double c)
{
	double tau = c * a.get_tau();
	double amplitude = c * a.get_amplitude();
	double constant = c * a.get_constant();
	return fit(tau, amplitude, constant);
}

inline fit operator*(const double c, const fit a)
{
	return a * c;
}

inline fit& operator+=(fit &a, const fit &b)
{
	a = a + b;
	return a;
}