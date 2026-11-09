build:
	gcc -o cuub main.c -lraylib -Wall

install:
	mv cuub /usr/local/bin/
