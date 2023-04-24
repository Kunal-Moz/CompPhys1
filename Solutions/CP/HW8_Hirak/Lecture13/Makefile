# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
LIBS=-I$(CPT_PATH) -L$(CPT_PATH) -lcpt


all: scattering wheatstone prob1 prob3 prob3_2

scattering: scattering.cpp
	$(CC) $^  $(LIBS) -o scattering

wheatstone: wheatstone.cpp
	$(CC) $^  $(LIBS) -o wheatstone

prob1: prob1.cpp
	$(CC) $^  $(LIBS) -o prob1

prob3: prob3.cpp
	$(CC) $^  $(LIBS) -o prob3

prob3_2: prob3_2.cpp
	$(CC) $^  $(LIBS) -o prob3_2

clean:
	rm -rf *o scattering wheatstone prob1 prob3 prob3_2
