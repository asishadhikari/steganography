#include <stdio.h>

int main(int argc, char** argv){
	int valid = 0;
	char *arg1, *arg2, *arg3;	//to store the provided params
	if (argc!=5 && argc != 4)
		error("Usage:\n ./stegno -e original.img cipher.jpg secret.txt \n
				./stegno -d cipher.jpg secret.txt ");
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
