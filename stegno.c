/*
    Ashish Adhikari
    MIT License.
    Howard University
*/
#include <stdio.h>
#include <errno.h>
#include <string.h>


#include "helper.h"

int main(int argc, char** argv){
    int valid = 0;
    char *img, *secret, *cipher;
    img = secret = cipher = NULL;

    char *usage_error = "Usage:\n\t./stegno -E -i image.bmp -m message.txt -c cipher.bmp\n\
    \t./stegno -D -i cipher.bmp -m secret.txt\n"; 
    //command run in valid format
    if (argc != 8 && argc != 6){
    	errno = EINVAL;
	error(usage_error);
    }

    if( !strcmp(argv[1],"-E") ){
	   if(argc!=8){
            errno = EINVAL;
            error(usage_error);
       }
       
       //Order of Argument does not matter
       for(int i = 2; i< argc; i++){
        if( !(strcmp(argv[i],"-i")) )
            img = argv[i+1];
     
        if( !(strcmp(argv[i],"-m")) )
            secret = argv[i+1];

        if( !(strcmp(argv[i],"-c")) )
            cipher = argv[i+1];
       }

       //make sure proper invocation by user
       if(!(img) || !(secret) || !(cipher)){
        errno = EINVAL;
        error(usage_error);
       }
       encode(img,secret,cipher);
    }else if( !(strcmp(argv[1], "-d")) ){
    	if(argc!=6){
            errno = EINVAL;
            error(usage_error);
        }
       //Order of Argument does not matter
       for(int i = 2; i< argc; i++){
        if( !(strcmp(argv[i],"-i")) )
            img = argv[i+1];
     
        if( !(strcmp(argv[i],"-m")) )
            secret = argv[i+1];
       }

       //make sure proper invocation by user
       if(!(img) || !(secret)){
        errno = EINVAL;
        error(usage_error);
       }
       decode(img);
    }else{
	errno = EINVAL;
	error(usage_error);
    }
    
    return 0;
}
