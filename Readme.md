# Steganography 
 >Steganography is used to hide secret messages into media files that are indistinguishible to the normal observer
# To build
``` sh
  $ cd steganography
  $ make
```

# Embedding message
```
  $ ./stegano -E -i image.bmp -m message.txt 
```

# Decoding message
``` 
  $ ./stegno -D -i cipher.bmp -m secret.txt
```
*\*\*Please note that order of the flag does not matter*

# Flags
	-E = Encode message
	-D = Decode message
	-i = Original Image or Cipher Image
	-m = message saved as text file

# To remove generated binaries and media file
```
$ make clean
```