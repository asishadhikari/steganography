/*
    Ashish Adhikari
    MIT License.
    Howard University

Copyright 2019 Ashish Adhikari

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal 
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLI
ED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR 
A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYR
IGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN 
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WIT
H THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


*/
#include <stdio.h>
#include <errno.h>
#include <string.h>


#include "helper.h"

int main(int argc, char** argv){
    int valid = 0;
    char *img, *secret;
    img = secret = NULL;

    char *usage_error = "Usage:\n\t./stegno -E -i image.bmp -m message.txt\n\
    \t./stegno -D -i cipher.bmp -m secret.txt\n"; 
    //command run in valid format
    if (argc != 8 && argc != 6){
    	errno = EINVAL;
	error(usage_error);
    }

    if( !strcmp(argv[1],"-E") ){
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
       encode(img,secret);
    }else if( !(strcmp(argv[1], "-D")) ){
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
       decode(img,secret);
    }else{
	errno = EINVAL;
	error(usage_error);
    }
    
    return 0;
}
