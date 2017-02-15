#include <iostream>
#include <iomanip>
#include "fahr_convert.h"

using namespace std;

int main() {

	double centigrade = 0.0;
	double value = 0.0;

	cout << "Enter number of centigrade degrees: ";

	cin >> centigrade;
	
	value = convert_to_fahr(centigrade);

	cout << setprecision(4) << centigrade << " degree centigrade is " << setprecision(4) << value << " Fahrenheit." << endl; 

	return 0;

}

