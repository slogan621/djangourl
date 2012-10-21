CC=g++ 
CFLAGS=-c -Wall -g -I ..

all: testdjangourls 

testdjangourls: testdjangourls.o djangourls.o
	$(CC) testdjangourls.o djangourls.o -o testdjangourls -lpthread -ldl -lboost_regex

djangourls.o: ../djangourls.cpp
	$(CC) $(CFLAGS) ../djangourls.cpp

testdjangourls.o: testdjangourls.cpp
	$(CC) $(CFLAGS) testdjangourls.cpp

clean:
	rm -rf *o testdjangourls
