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

void encode(char *img, char *secret){
	int fileSize;
	
	//open input image file
	if( (fin = fopen(img, "r"))==NULL ){
		errno = ENOENT;
		error("Make sure the usable image exists\n");
	}

	//read the image width and height (According to BMP file format byte 18 and 22)
	int height, width, capacity;
	fseek(fin,18L,SEEK_SET);
	fread(&width,4,1,fin); 
	fread(&height,4,1,fin);
	printf("Given file %s's dimension is %d x %d \n",img, width,height);
	printf("Can store %d bytes\n",(capacity=height*width*3/8));
	rewind(fin);

	//open file for writing user input
	fout = fopen(secret,"w+");
	char ch;
	printf("\n\t### Enter the secret messge to hide, Press CTRL+D when done.... ###\n>> ");
	//ctrl+D is not EOF but it causes an error for getchar() which is treated as EOF
	while ((ch = getchar())!=EOF)
		putc(ch,fout);
	rewind(fout);
	
	//obtain entered message size
	fseek(fout, 0L, SEEK_END);
	int msg_size = ftell(fout);
	rewind(fout);

	if(msg_size > capacity ){
		errno = EMSGSIZE;
		error("Choose a larger image file to hide the msg\n");
	}
	printf("\n%d bytes were entered as message\n",msg_size);

	//open the BMP file to write in
	char *prefix = "cipher-";
	char *fname = (char*) malloc(strlen(img)+strlen(prefix));
	strcpy(fname,prefix);
	strcpy(&fname[strlen(prefix)],img);
	printf("Cipher file will be named : %s\n",fname);

	if( (fout = fopen(fname,"w")) == NULL){
		errno = EPERM;
		error("Unable to open file to write\n");
	}	
	free(fname);

	//copy 54 byte header data 
	rewind(fin);
	rewind(fout);
	char c;
	for (int i = 0; i < 54; i++){
		c = fgetc(fin);
		fputc(c,fout);
	}


	






}


void decode(char *img){


}
