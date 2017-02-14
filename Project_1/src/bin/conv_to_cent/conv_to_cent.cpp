#include <iostream>
#include <iomanip>
#include "getarg.h"
#include "cent_convert.h"

using namespace std;

int main(int argc, char* argv[]) {

	int argSuccess = 0;
	double value = 0.0;

	argSuccess = get_argument(argc, argv, &value);

	if (argSuccess == 0)
		cout << setprecision(4) << value  << " degrees Fahrenheight is " << setprecision(4) << convert_to_cent(value) << " degree centigrade" << endl;

	return 0;

}

