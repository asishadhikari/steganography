#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "helper.h"
void error(char *error){
        perror(error);
	exit(errno);
}
