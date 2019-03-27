build:
	gcc stegno.c helper_decode.c helper_encode.c -o stegno

clean:
	rm stegno *.txt cipher*
