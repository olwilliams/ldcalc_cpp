#pragma once

#include "results.h"
#include "fit.h"
#include "simplex.h"

std::vector<double> model(fit parameters, int time_points);

double objective(results &data, fit parameters);

bool terminate(const std::vector<double> &objective_values, double tolerance);

std::vector<int> index_order(const std::vector<double> &objective_values);

fit reflect(Simplex &simplex, fit centroid, int worst_index);

fit expand(fit reflect_point, fit centroid);

fit contract(fit point, fit centroid);

void shrink(Simplex &simplex, std::vector<double> &objective_points, int best_index, results data);

void transform(Simplex &simplex, std::vector<double> &objective_points, int best_index, int worst_index, int second_worst_index, fit centroid, results data);

fit nelder_mead(results &data, fit guess, double tolerance);