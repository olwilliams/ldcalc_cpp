#include "stdafx.h"
#include "functions.h"
#include "dipole.h"
#include "results.h"
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>

double norm(dipole v)
{
	double x, y, z;
	x = v.get_x();
	y = v.get_y();
	z = v.get_z();
	return std::sqrt(x * x + y * y + z * z);
}

double dot(dipole a, dipole b)
{
	return a.get_x() * b.get_x() + a.get_y() * b.get_y() + a.get_z() * b.get_z();
}

dipole rotate(dipole v, dipole axis, double degangle)
{
	double x = v.get_x();
	double y = v.get_y();
	double z = v.get_z();

	const double pi = 3.14159265358979323846264338327950288;
	dipole norm_axis = axis / norm(axis);
	double ux = norm_axis.get_x();
	double uy = norm_axis.get_y();
	double uz = norm_axis.get_z();
	double radangle = degangle * pi / 180;

	//Rotation matrix elements
	double R11, R12, R13, R21, R22, R23, R31, R32, R33;
	R11 = cos(radangle) + ux * ux * (1 - cos(radangle));
	R12 = ux*uy*(1 - cos(radangle)) - uz*sin(radangle);
	R13 = ux*uz*(1 - cos(radangle)) + uy*sin(radangle);
	R21 = uy*ux*(1 - cos(radangle)) + uz*sin(radangle);
	R22 = cos(radangle) + uy * uy * (1 - cos(radangle));
	R23 = uy*uz*(1 - cos(radangle)) - ux*sin(radangle);
	R31 = uz*ux*(1 - cos(radangle)) - uy*sin(radangle);
	R32 = uz*uy*(1 - cos(radangle)) + ux*sin(radangle);
	R33 = cos(radangle) + uz * uz * (1 - cos(radangle));

	//Matrix multiplication
	double newx, newy, newz;
	newx = R11 * x + R12 * y + R13 * z;
	newy = R21 * x + R22 * y + R23 * z;
	newz = R31 * x + R32 * y + R33 * z;
	return dipole(newx, newy, newz);
}

double randangle()
{
	static std::default_random_engine generator;
	static std::normal_distribution<double> distribution(0, 1);
	double angle = distribution(generator);
	return angle;
}

double check_theta(double oldtheta)
{
	//Make sure that thetais in the interval [0, 360) degrees.
	double theta = oldtheta;
	while (theta >= 360)
	{
		theta -= 360;
	}
	while (theta < 0)
	{
		theta += 360;
	}
	return theta;
}

double check_phi(double oldphi)
{
	//Make sure that phi is in the interval [0, 180] degrees.
	double phi = oldphi;
	while (phi > 180)
	{
		phi -= 360;
	}
	while (phi < -180)
	{
		phi += 360;
	}
	if (phi < 0 && phi > -180)
	{
		phi = fabs(phi);
	}
	return phi;
}

dipole sphere_to_cart(dipole sphere_vector)
{
	const double pi = 3.14159265358979323846264338327950288;
	double r = sphere_vector.get_x();
	double theta = sphere_vector.get_y() * pi / 180;
	double phi = sphere_vector.get_z() * pi / 180;
	double x = r * cos(theta) * sin(phi);
	double y = r * sin(theta) * sin(phi);
	double z = r * cos(phi);
	return dipole(x, y, z);
}

void run(results& new_result, settings options)
{
	auto start = std::chrono::steady_clock::now(); //Start code timer

	//Retrieve simulation parameters
	int number_particles = options.get_number_particles();
	int number_steps = options.get_number_steps();
	dipole sphere_position = options.get_position();
	dipole plane_normal = sphere_to_cart(sphere_position);
	plane_normal = plane_normal / norm(plane_normal);
	dipole probe1 = options.get_probe1();
	probe1 = probe1 / norm(probe1);
	dipole probe2 = options.get_probe2();
	probe2 = probe2 / norm(probe2);
	dipole excitation = options.get_excitation();
	excitation = excitation / norm(excitation);
	double dipole_angle = options.get_dipole_angle();
	double scale = options.get_scale();
	new_result.change_size(number_steps);
	//Initialize the collection of dipoles

	/* Define dipole location: the dipole angle is added and subtracted from the membrane normal vector. 
	We choose te direction that has the most projection along the excitation direction. */
	dipole positive_dipole;
	positive_dipole.init(sphere_position.get_x(), check_theta(sphere_position.get_y()), check_phi(sphere_position.get_z() + dipole_angle));
	positive_dipole = sphere_to_cart(positive_dipole);
	dipole negative_dipole;
	negative_dipole.init(sphere_position.get_x(), check_theta(sphere_position.get_y()), check_phi(sphere_position.get_z() - dipole_angle));
	negative_dipole = sphere_to_cart(negative_dipole);
	double positive_overlap;
	positive_overlap = dot(positive_dipole, excitation);
	positive_overlap *= positive_overlap;
	double negative_overlap;
	negative_overlap = dot(negative_dipole, excitation);
	negative_overlap *= negative_overlap;
	dipole start_dipole;
	if (positive_overlap >= negative_overlap)
	{
		start_dipole = positive_dipole;
	}
	else
	{
		start_dipole = negative_dipole;
	}

	//A vector containing all of our dipoles
	std::vector<dipole> dipole_vector;
	dipole_vector.resize(number_particles);
	for (int n = 0; n < number_particles; n++)
	{
		dipole_vector[n] = start_dipole;
	}

	//At each time step, perturb each dipole and calculate absorbance with each probe
	for (int t = 0; t < number_steps; t++)
	{
		double abs1 = 0, abs2 = 0;
		for (int n = 0; n < number_particles; n++)
		{
			double randn = randangle() * scale;
			dipole_vector[n] = rotate(dipole_vector[n], plane_normal, randn);
			double abs1temp = dot(dipole_vector[n], probe1);
			abs1 += abs1temp * abs1temp;
			double abs2temp = dot(dipole_vector[n], probe2);
			abs2 += abs2temp * abs2temp;
		}
		new_result.add_point(t, abs1, abs2);
	}
	//new_result.print();
	auto end = std::chrono::steady_clock::now();
	auto diff = end - start;
	std::cout << "Time elapsed: " << std::chrono::duration<double>(diff).count() << " seconds" << std::endl;
}

void save_results(results& new_result)
{
	using namespace std;
	cout << "Filename to save as? ";
	string save_name;
	cin >> save_name;
	ofstream save_file(save_name);
	if (!save_file)
	{
		cout << "Error creating file." << endl;
		return;
	}
	for (int n = 0; n < new_result.get_size(); n++)
	{
		save_file << new_result.get_ld()[n] << "\n";
	}
	save_file.close();
}