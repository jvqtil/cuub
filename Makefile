ifeq ($(shell uname -s),Darwin)
	CFLAGS = -I/opt/homebrew/include -L/opt/homebrew/lib
else
	CFLAGS =
endif

build:
	gcc -o cuub main.c $(CFLAGS) -lraylib -Wall

install:
	mv cuub /usr/local/bin/
