#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "helper.h"

FILE *fin, *fout;

void error(char *error){
        perror(error);
	exit(errno);
}

void encode(char *img){
	int fileSize;
	
	//open input image file
	if( (fin = fopen(img, "r"))==NULL )
		error("Make sure the usable image exists\n");
	
	
}

void decode(char *img){


}
