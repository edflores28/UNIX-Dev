#include "cent_convert.h"

const double factor = 5.0/9.0;

double convert_to_cent (double fahr) {
	return ((fahr - 32) * factor);
}
