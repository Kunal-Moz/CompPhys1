# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
LIBS=-I$(CPT_PATH) -L$(CPT_PATH) -lcpt


all: triatomic matrixmult prob2

triatomic: triatomic.cpp
	$(CC) $^  $(LIBS) -o triatomic

matrixmult: matrixmult.cpp
	$(CC) $^  $(LIBS) -o matrixmult

prob2: prob2.cpp
	$(CC) $^  $(LIBS) -o prob2


clean:
	rm -rf *o triatomic matrixmult prob2
