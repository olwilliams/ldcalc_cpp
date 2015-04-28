#include "stdafx.h"
#include "dipole.h"
#include "settings.h"
#include "functions.h"

void welcome()
{
	using namespace std;
	cout << "Welcome to ldcalc!" << endl;
}

void menu(settings& options, results& new_result)
{
	using namespace std;
	int command;
	cout << "\nWhat would you like to do?" << endl;
	cout << "1. Run simulation\n";
	cout << "2. View current settings\n";
	cout << "3. Change settings\n";
	cout << "4. Save last run\n";
	cout << "0. Exit\n";
	cin >> command;
	if (!cin)
	{
		cin.clear();
		cin.ignore(255, '\n');
		cout << "Invalid command." << endl;
	}

	switch (command)
	{
	case 1:
		run(new_result, options);
		break;
	case 2:
		options.view();
		break;
	case 3:
		options.change();
		break;
	case 4:
		save_results(new_result);
		break;
	case 0:
		cout << "Goodbye!" << endl;
		exit(0);
		break;
	default:
		cout << "Invalid command." << endl;
		break;
	}
}

int main()
{
	welcome();
	settings options = settings();
	results new_result = results(1);
	while (true)
	{
		menu(options, new_result);
	}
	return 0;
}