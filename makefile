all: binary


binary: binary.clean	
	gcc binary.c -o binary

run:
	./binary 