#include "stdafx.h"
#include "settings.h"
#include "dipole.h"

settings::settings(dipole new_spherical_position, dipole new_probe1, dipole new_probe2, dipole new_excitation, double new_dipole_angle, int new_number_particles, int new_number_steps, double new_scale)
{
	spherical_position = new_spherical_position;
	probe1 = new_probe1;
	probe2 = new_probe2;
	excitation = new_excitation;
	dipole_angle = new_dipole_angle;
	number_particles = new_number_particles;
	number_steps = new_number_steps;
	scale = new_scale;
}

settings::settings()
{
	spherical_position = dipole(1, 0, 90);
	probe1 = dipole(0, 0, 1);
	probe2 = dipole(1, 0, 0);
	excitation = dipole(0, 0, 1);
	dipole_angle = 45;
	number_particles = 100;
	number_steps = 15000;
	scale = 1;
}

void settings::view()
{
	using namespace std;
	cout << "\nCurrent settings:";
	cout << "\n1. Position: "; spherical_position.print();
	cout << "\n2. Probe 1: "; probe1.print();
	cout << "\n3. Probe 2: "; probe2.print();
	cout << "\n4. Excitation direction: "; excitation.print();
	cout << "\n5. Dipole angle: " << dipole_angle << " degrees";
	cout << "\n6. Number of particles: " << number_particles;
	cout << "\n7. Number of time steps: " << number_steps;
	cout << "\n8. Scale factor: " << scale << endl;
}

void settings::change()
{
	using namespace std;
	view();
	cout << "\nWhich setting would you like to change? (0 to restore defaults)\n";
	int command;
	cin >> command;
	if (!cin)
	{
		cin.clear();
		cin.ignore(255, '\n');
		command = -1;
		cout << "Invalid selection." << endl;
	}
	switch (command)
	{
	case 1:
		double r, theta, phi;
		cout << "New r? ";
		cin >> r;
		cout << "New theta? ";
		cin >> theta;
		cout << "New phi? ";
		cin >> phi;
		if (!cin)
		{
			cin.clear();
			cin.ignore(255, '\n');
			break;
		}
		set_position(dipole(r, theta, phi));
		break;
	case 2:
		double probe1_x, probe1_y, probe1_z;
		cout << "New x? ";
		cin >> probe1_x;
		cout << "New y? ";
		cin >> probe1_y;
		cout << "New z? ";
		cin >> probe1_z;
		if (!cin)
		{
			cin.clear();
			cin.ignore(255, '\n');
			break;
		}
		set_probe1(dipole(probe1_x, probe1_y, probe1_z));
		break;
	case 3:
		double probe2_x, probe2_y, probe2_z;
		cout << "New x? ";
		cin >> probe2_x;
		cout << "New y? ";
		cin >> probe2_y;
		cout << "New z? ";
		cin >> probe2_z;
		if (!cin)
		{
			cin.clear();
			cin.ignore(255, '\n');
			break;
		}
		set_probe2(dipole(probe2_x, probe2_y, probe2_z));
		break;
	case 4:
		double excite_x, excite_y, excite_z;
		cout << "New x? ";
		cin >> excite_x;
		cout << "New y? ";
		cin >> excite_y;
		cout << "New z? ";
		cin >> excite_z;
		if (!cin)
		{
			cin.clear();
			cin.ignore(255, '\n');
			break;
		}
		set_excitation(dipole(excite_x, excite_y, excite_z));
		break;
	case 5:
		double angle;
		cout << "New angle? ";
		cin >> angle;
		if (!cin)
		{
			cin.clear();
			cin.ignore(255, '\n');
			break;
		}
		set_dipole_angle(angle);
	case 6:
		int new_particles;
		cout << "Number of particles? ";
		cin >> new_particles;
		if (!cin)
		{
			cin.clear();
			cin.ignore(255, '\n');
			break;
		}
		set_number_particles(new_particles);
		break;
	case 7:
		int new_steps;
		cout << "Number of time steps? ";
		cin >> new_steps;
		if (!cin)
		{
			cin.clear();
			cin.ignore(255, '\n');
			break;
		}
		set_number_steps(new_steps);
		break;
	case 8:
		double new_scale;
		cout << "New scaling factor? ";
		cin >> new_scale;
		if (!cin)
		{
			cin.clear();
			cin.ignore(255, '\n');
			break;
		}
		set_scale(new_scale);
		break;
	case 0:
		spherical_position = dipole(1, 0, 90);
		probe1 = dipole(0, 0, 1);
		probe2 = dipole(1, 0, 0);
		excitation = dipole(0, 0, 1);
		dipole_angle = 45;
		number_particles = 100;
		number_steps = 15000;
		scale = 1;
		break;
	}
	view();
}