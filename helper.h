#ifndef HELPER
#include <stdio.h>
#include <string.h>
#include <errno.h>
void error(char *msg);
void encode(char *img, char *secret);
void decode(char *img, char *secret);

//encrypt functions
int get_bit(char byte, int bit);
void size_encrypt(int num, FILE *fp1, FILE *fp3);
void steganograph(FILE *fp1, FILE *fp2, FILE *fp3);




//decrypt functions
#define HELPER
#endif
