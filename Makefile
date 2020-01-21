INCLUDES=-I../../irrlicht_engine/include
LIBS=-L../irrlicht_engine/lib/Linux
CFLAGS=-Wall
CXX=g++

ifeq ($(OS),Windows_NT)
	LIBS=-L../irrlicht_engine/lib/Win32-gcc
endif

LIBS+= -lIrrlicht

pmc: src/*.cpp
	cd src; \
	g++ $(CFLAGS) -o pmc $(INCLUDES) *.cpp $(LIBS);
	mv src/pmc .

clean:
	rm pmc
