all: binary

clean:
	rm binary

binary: binary.c	
	gcc binary.c -o binary 

run:
	./binary Haiku.bin