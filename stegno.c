#include <stdio.h>
#include <errno.h>
#include "helper.h"


int main(int argc, char** argv){
    int valid = 0;
    if (argc!=5 && argc != 4){
        error("Usage:\n ./stegno -e original.img cipher.jpg secret.txt \n\
 ./stegno -d cipher.jpg secret.txt ");
    	errno = EINVAL;
    }
    switch(argc){
        case 5:	
            break;
        case 4:
            break;
        default:
            break;		
    }	

    return 0;
}
