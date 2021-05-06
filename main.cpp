#include "Polynomials.h"
#include "DifferenceTable.h"
#include "Stirling.h"
#include "Newton.h"
#include "NewtonDiv.h"
#include "Lagrange.h"
#include <string>

int main()
{
	std::string input;
	bool inputErr = false;

	int count;
	std::cout << "Enter the number of sets of values.\n";
	do {
		if (inputErr) std::cout << "The entered number isn't valid. Please try again.\n";
		std::cin >> input;
		try {
			count = std::stoi(input);
			inputErr = false;
		}
		catch (...) { inputErr = true; }
	} while (inputErr);

	std::cout << "Enter the " << count << " x-values for the data set.\n";
	std::vector<double> x(count);
	for (int i = 0; i < count; i++) {
		do {
			if (inputErr) std::cout << "The entered number isn't valid. Please try again.\n";
			std::cin >> input;
			try {
				x[i] = std::stod(input);
				inputErr = false;
			}
			catch (...) { inputErr = true; }
		} while (inputErr);
	}

	std::cout << "Enter the " << count << " y-values for the data set.\n";
	std::vector<double> y(count);
	for (int i = 0; i < count; i++) {
		do {
			if (inputErr) std::cout << "The entered number isn't valid. Please try again.\n";
			std::cin >> input;
			try {
				y[i] = std::stod(input);
				inputErr = false;
			}
			catch (...) { inputErr = true; }
		} while (inputErr);
	}

	diff_tbl<double> differenceTbl (x, y);

	if (differenceTbl.equispaced) {
		std::cout << "The provided data points are equispaced.\n\n";
	}
	else {
		std::cout << "The provided data points are arbitrarily spaced.\n\n";
	}

    std::cout << "Numerical Methods Calculator.\nPlease input the number of the Interpolating formula to be used:\n\n";
	std::cout << "\t\tFor equispaced data points:\n";
	std::cout << "\t1. Newton's Forward Difference Interpolating Polynomial\n";
	std::cout << "\t2. Newton's Backward Difference Interpolating Polynomial\n";
	std::cout << "\t3. Stirling's Central Difference Interpolating Polynomial\n";
	std::cout << "\n\t\tFor arbitrarily spaced data points:\n";
	std::cout << "\t4. Lagrange Interpolating Polynomial\n";
	std::cout << "\t5. Newton's Divided Difference Interpolating Polynomial\n\n";

	polynomial<double> interpolatingPoly;

	inputErr = true;
	do {
		if (differenceTbl.equispaced) std::cout << "The data points are equispaced, so any formula can be used (1 - 5).\n";
		else std::cout << "The data points are arbitrarily spaced, so only valid formulas are 4 and 5.\n";

		std::cin >> input;
		if (differenceTbl.equispaced) {
			if (input == "1") {
				//NFDIP
				interpolatingPoly = getNewtonPolynomial(true, differenceTbl);
				inputErr = false;
			}
			else if (input == "2") {
				//NBDIP
				interpolatingPoly = getNewtonPolynomial(false, differenceTbl);
				inputErr = false;
			}
			else if (input == "3") {
				//SCDIP
				interpolatingPoly = getStirlingPolynomial(differenceTbl);
				inputErr = false;
			}
		}
		if (input == "4") {
			//LIP
			interpolatingPoly = getLagrangePolynomial(differenceTbl);
			inputErr = false;
		}
		else if (input == "5") {
			//NDDIP
			interpolatingPoly = getNewtonDivPolynomial(differenceTbl);
			inputErr = false;
		}
	} while (inputErr);

	double valueOfX;
	std::cout << "Enter the value of x for which y is to be calculated.\n";
	do {
		if (inputErr) std::cout << "The entered number isn't valid. Please try again.\n";
		std::cin >> input;
		try {
			valueOfX = std::stof(input);
			inputErr = false;
		}
		catch (...) { inputErr = true; }
	} while (inputErr);

	double valueOfY = interpolatingPoly.evaluate(valueOfX);
	std::cout << "The value of y at x = " << valueOfX << " is " << valueOfY << "\n";

	return 0;
}
