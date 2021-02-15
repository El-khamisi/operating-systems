
CC = g++
flags = -pthread


all: app.out clean


app.out: main.o
	$(CC) -o app.out main.o $(flags)


main.o: main.cpp header.h
	$(CC) -c main.cpp

clean:
	-rm *.o