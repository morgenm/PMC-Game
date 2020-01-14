INCLUDES=-I../../irrlicht_engine/include
LIBS=-L../irrlicht_engine/lib/Linux
CXX=g++

ifeq ($(OS),Windows_NT)
	LIBS=-L../irrlicht_engine/lib/Win32-gcc
endif

LIBS+= -lIrrlicht

pmc: src/main.cpp
	cd src; \
	g++ -o pmc $(INCLUDES) main.cpp $(LIBS);
	mv src/pmc .
