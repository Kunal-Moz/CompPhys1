# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CXX=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
CXXFLAGS=-Wall -std=c++11


SRCS = $(wildcard Problem*.cpp)
OBJSRCS = $(wildcard StudentRecord*.cpp)

PROGS = $(patsubst %.cpp,%,$(SRCS)) 

LIBS = StudentRecord.o 

StudentRecord.o : StudentRecord.h $(OBJSRCS)
	$(CXX) $(CXXFLAGS) -c $(OBJSRCS)

all: $(LIBS) $(PROGS)

%: %.cpp $(wildcard *.h) 
	rm -f $@
	$(CXX) $(CXXFLAGS) $(LIBS)  $<  -o $@

clean:
	rm -f $(PROGS) $(LIBS)
