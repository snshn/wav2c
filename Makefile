# Makefile for wav2c

CFLAGS = -std=c99 -s -pedantic -Wall -Wextra -Wfatal-errors -pedantic-errors -O3 -D_XOPEN_SOURCE=500 -D_POSIX_C_SOURCE=200809L
CC     = gcc $(CFLAGS)

PROGNAME = wav2c
FILES = $(PROGNAME).c


all: $(PROGNAME)

$(PROGNAME): $(FILES)
	$(CC) $(FILES) -o $(PROGNAME) -O1 -Xlinker -s -lsndfile

clean:
	rm -rf $(PROGNAME)
