#include "helper.h"
/* decryption of sizes */
void size_decryption(FILE *pf1, int *size_txt){
	int file_buff = 0, i;
	int ch, bit_msg;
	for (i = 0; i < 8; i++)
	{
		ch = fgetc(pf1);
		bit_msg = (ch & 1);
		if (bit_msg)
		{
			file_buff = (file_buff << 1) | 1;
		}
		else
		{
			file_buff = file_buff << 1;
		}
	}
	*size_txt = file_buff;
}

/* decryption of strings*/
void string_decryption(FILE *pf1,char *strng,int size)
{
	int file_buff=0, i, j=0, k=0;
	int ch, bit_msg;
	for (i = 0; i < (size * 8); i++)
	{
		j++;
		ch = fgetc(pf1);
		bit_msg = (ch & 1);
		if (bit_msg)
		{
			file_buff = (file_buff << 1) | 1;
		}
		else
		{
			file_buff = file_buff << 1;
		}

		if ( j == 8)
		{
			strng[k] =(char)file_buff; 
			j=0;
			k++;
			file_buff = 0;
		}
	}
	strng[k] = '\0';
}
/* decryption of secret message*/
void secret_decryption(int size_txt, FILE *pf1, FILE *pf2){
	int file_buff=0, i, j = 0, k = 0;
	int ch,bit_msg;
	char output[250] = {0};
	for (i = 0; i < (size_txt * 8); i++){
		j++;
		ch = fgetc(pf1);
		bit_msg = (ch & 1);
		if (bit_msg){
			file_buff = (file_buff << 1) | 1;
		}
		else{
			file_buff = file_buff << 1;
		}
		if ( j == 8){
			putc(file_buff, pf2);
			output[k++] = file_buff;
			j=0;
			file_buff = 0;
		}
	}
	printf("\n Found message: %s  \n\n", output);
}
void decode(char *argv_2, char *argv_4){
	FILE *pf1, *pf2;
	int size, size1, size_txt;
	//opening Image File
	if((pf1 = fopen(argv_2, "r")) == NULL) {
		errno = ENOENT;
		error("Make sure the cipher image exists\n");

	}

	fseek(pf1,54 ,SEEK_SET);
	
	if((pf2 = fopen(argv_4, "w+")) == NULL) {
		errno = ENOENT;
		error("Unable to open file to write secret into");
	}
	/*Decrypt the secret Text */
	size_decryption(pf1, &size_txt);
	secret_decryption(size_txt, pf1, pf2);

	printf("Secret message written to file : %s\n\n", argv_4);

	fclose(pf1);

}
