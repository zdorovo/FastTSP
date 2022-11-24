PATH := /usr/um/gcc-4.7.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-4.7.0/lib64
LD_RUN_PATH := /usr/um/gcc-4.7.0/lib64

all: main.o fasttsp.o opttsp.o mst.o tspsolve.o
	g++ -O3 main.o fasttsp.o opttsp.o mst.o tspsolve.o -o cakequest

main.o: tspsolve.h main.cpp
	g++ -c main.cpp

fasttsp.o: tspsolve.h fasttsp.cpp
	g++ -c fasttsp.cpp

opttsp.o: tspsolve.h opttsp.cpp
	g++ -c opttsp.cpp
	
mst.o: tspsolve.h mst.cpp
	g++ -c mst.cpp

tspsolve.o: tspsolve.h tspsolve.cpp
	g++ -c tspsolve.cpp

clean:
	rm *.o cakequest
