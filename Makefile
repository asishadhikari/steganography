build:
	gcc stegano.c helper_decode.c helper_encode.c -o stegano

clean:
	rm stegano *.txt cipher*
