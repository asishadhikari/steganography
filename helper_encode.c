#include <stdlib.h>

#include "helper.h"

FILE *fin, *fsec, *fout;

void error(char *error){
        perror(error);
	exit(errno);
}


//return variable length bit shifts and corresponding lsf
int get_bit(char byte, int bit){
	return (byte >> (8 - bit) & 1);
}


void size_encrypt(int num,FILE *fp1, FILE *fp3){
	char file_buff;	
	int i, j = 0;
	int bit_msg;
	for(i = 1; i <= 8; i++){
		file_buff = fgetc(fp1);
		int file_byte_lsb = (file_buff & 1);
		bit_msg = get_bit(num, i);
		if(file_byte_lsb == bit_msg){
			fputc(file_buff, fp3);
		}
		else{
			if(file_byte_lsb == 0)
				file_buff = (file_buff | 1);
			else
				file_buff = (file_buff ^ 1);
			fputc(file_buff, fp3);
		}
	}

}


void steganograph(FILE *fp1, FILE *fp2, FILE *fp3)
{
	char file_buff = 0, msg_buff = 0, ch;	//temp var for one byte from file and msg
	int i;
	int bit_msg;
	while((msg_buff = fgetc(fp2)) != EOF)
	{
		for(i = 1; i <= 8; i++)
		{
			file_buff = fgetc(fp1);

			int file_byte_lsb = (file_buff & 1);

			bit_msg = get_bit(msg_buff, i);

			if(file_byte_lsb == bit_msg)
			{
				fputc(file_buff, fp3);
			}
			else
			{
				if(file_byte_lsb == 0)
					file_buff = (file_buff | 1);
				else
					file_buff = (file_buff ^ 1);

				fputc(file_buff, fp3);
			}
		}
	}

	/*copying rest of data */
	while(!feof(fp1))
	{
		char tmp_cpy = fgetc(fp1);
		fputc(tmp_cpy,fp3);

	}

	if(msg_buff == EOF)
		printf("\nMessage successfully embedded into cipher image\n");
	else
		error("Unable to embed the message");
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
	fsec = fopen(secret,"w+");
	char ch;
	printf("\n\t### Enter the secret messge to hide, Press CTRL+D when done.... ###\n>> ");
	//ctrl+D is not EOF but it causes an error for getchar() which is treated as EOF
	while ((ch = getchar())!=EOF)
		putc(ch,fsec);
	rewind(fsec);
	
	//obtain entered message size
	fseek(fsec, 0L, SEEK_END);
	int msg_size = ftell(fsec);
	rewind(fsec);

	if(msg_size > capacity ){
		errno = EMSGSIZE;
		error("Choose a larger image file to hide the msg\n");
	}


	printf("\n\n%d bytes were entered as message\n",msg_size);

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
	int i = 0;

	for (i = 0; i < 54; i++){
		c = fgetc(fin);
		fputc(c,fout);
	}
	size_encrypt(msg_size,fin,fout);
	steganograph(fin,fsec,fout);

	fclose(fin);	
	fclose(fsec);
	fclose(fout);

}