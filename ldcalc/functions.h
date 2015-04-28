#pragma once

#include "dipole.h"
#include "settings.h"
#include "results.h"
#include <vector>

double norm(dipole v);
double dot(dipole a, dipole b);
double randangle();
double check_theta(double oldtheta);
double check_phi(double oldphi);
dipole sphere_to_cart(dipole sphere_vector);
dipole rotate(dipole v, dipole axis, double degangle);
void run(results& new_result, settings options);
void save_results(results& new_result);