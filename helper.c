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

void encode(char *img, char *secret, char *cipher){
	int fileSize;
	
	//open input image file
	if( (fin = fopen(img, "r"))==NULL ){
		errno = ENOENT;
		error("Make sure the usable image exists\n");
	}

	//read the image width and height (According to BMP file format byte 18 and 22)
	int height, width;
	fseek(fin,18,SEEK_SET);
	fread(&width,4,1,fin); 
	fread(&height,4,1,fin);
	printf("Given file %s's dimension is %d x %d \n",img, width,height);
	printf("Can store %d bytes\n",height*width*3/8);
	rewind(fin);

	//open file for writing user input
	fout = fopen(secret,"w+");
	char ch;
	printf("Please enter secret to hide, Press CTRL+D when when\n");
	//ctrl+D is not EOF but it causes an error for getchar() which is treated as EOF
	while ((ch = getchar())!=EOF)
		putc(ch,fout);
	rewind(fout);








}


void decode(char *img){


}
