#pragma once

#include "dipole.h"
#include <iostream>

class settings
{
public:

	dipole spherical_position;
	dipole probe1;
	dipole probe2;
	dipole excitation;
	double dipole_angle;
	int number_particles;
	int number_steps;
	double scale;

	settings(dipole new_spherical_position, dipole new_probe1, dipole new_probe2, dipole new_excitation, double new_dipole_angle, int new_number_particles, int new_number_steps, double new_scale);
	settings();

	void set_position(dipole new_spherical_position) { spherical_position = new_spherical_position; }
	dipole get_position() { return spherical_position; }
	void set_probe1(dipole new_probe1) { probe1 = new_probe1; }
	dipole get_probe1() { return probe1; }
	void set_probe2(dipole new_probe2) { probe2 = new_probe2; }
	dipole get_probe2() { return probe2; }
	void set_excitation(dipole new_excitation) { excitation = new_excitation; }
	dipole get_excitation() { return excitation; }
	void set_dipole_angle(double new_dipole_angle) { dipole_angle = new_dipole_angle; }
	double get_dipole_angle() { return dipole_angle; }
	void set_number_particles(int new_number_particles) { number_particles = new_number_particles; }
	int get_number_particles() { return number_particles; }
	void set_number_steps(int new_number_steps) { number_steps = new_number_steps; }
	int get_number_steps() { return number_steps; }
	void set_scale(double new_scale) { scale = new_scale; }
	double get_scale() { return scale; }

	void view();
	void change();
};