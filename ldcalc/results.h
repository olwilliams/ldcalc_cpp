#pragma once

class results
{
private:
	std::vector<double> absorbance1;
	std::vector<double> absorbance2;
	std::vector<double> ld;
	int size;


public:
	results(int new_size);
	int get_size() { return size; }
	std::vector<double> get_ld() { return ld; }

	void add_point(int time_point, double abs1, double abs2);
	void print();
	void change_size(int new_size);
};