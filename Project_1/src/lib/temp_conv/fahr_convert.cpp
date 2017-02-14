#include "fahr_convert.h"

const double factor = 9.0/5.0;

double convert_to_fahr (double cent) {
	return ((cent * factor) + 32.0);
}
