objects = main.o TopUrl.o SDBMHash.o

main : $(objects)
	g++ -o main $(objects)

main.o : main.cpp
	g++ -c main.cpp

TopUrl.o : TopUrl.cpp TopUrl.h
	g++ -c TopUrl.cpp -O2

SDBMHash.o : SDBMHash.cpp SDBMHash.h
	g++ -c SDBMHash.cpp

makedata : makedata.cpp
	g++ -o makedata makedata.cpp