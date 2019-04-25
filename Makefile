objects = main.o TopUrl.o SDBMHash.o FastIO.o

main : $(objects)
	g++ -o main $(objects) -pthread

main.o : main.cpp TopUrl.o
	g++ -c main.cpp

TopUrl.o : TopUrl.cpp TopUrl.h SDBMHash.o FastIO.o
	g++ -c TopUrl.cpp -O2 -std=c++11

SDBMHash.o : SDBMHash.cpp SDBMHash.h
	g++ -c SDBMHash.cpp -O2

FastIO.o : FastIO.cpp FastIO.h
	g++ -c FastIO.cpp -O2

makedata : makedata.cpp
	g++ -o makedata makedata.cpp

clean    : 
	rm *.o