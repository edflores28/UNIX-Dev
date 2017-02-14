#include <stdlib.h>
#include "getarg.h"

int get_argument (int argc, char *argv[], double *return_value) {
	if (argc > 1){
		*return_value = atof(argv[1]);
		return 0;
	}
	else
		return -1;

}

