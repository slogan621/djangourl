# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=g++ 
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
CFLAGS=-c -Wall -g -std=c++0x -I ..

all: testdjangourls 

testdjangourls: testdjangourls.o djangourls.o
	$(CC) testdjangourls.o djangourls.o -o testdjangourls -lpthread -ldl -lboost_regex

djangourls.o: ../djangourls.cpp
	$(CC) $(CFLAGS) ../djangourls.cpp

testdjangourls.o: testdjangourls.cpp
	$(CC) $(CFLAGS) testdjangourls.cpp

clean:
	rm -rf *o testdjangourls
