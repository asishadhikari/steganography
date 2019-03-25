#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "helper.h"


int main(int argc, char** argv){
    int valid = 0;
    char *img;
    //command run in valid format
    if (argc != 3){
    	errno = EINVAL;
	error("Usage:\n\t./stegno [-e |-d ] image.jpg\n");
    }

    if( !strcmp(argv[1],"-e") ){
    	img = argv[2];
	encode(img);
    }else if( !(strcmp(argv[1], "-d")) ){
    	img = argv[2];
	decode(img);
    }else{
	errno = EINVAL;
	error("Usage:\n\t./stegno [-e |-d ] image.jpg\n");
    }
    
    return 0;
}
