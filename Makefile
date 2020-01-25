INCLUDES=-I../../irrlicht_engine/include
LIBS=-L../irrlicht_engine/lib/Linux
CFLAGS=-Wall -g
CXX=g++
BIN_DIR=bin

ifeq ($(OS),Windows_NT)
	LIBS=-L../irrlicht_engine/lib/Win32-gcc
	BIN_FILE=$(BIN_DIR)/pmc.exe
else
	BIN_FILE=$(BIN_DIR)/pmc
endif

LIBS+= -lIrrlicht

game: src/*.cpp src/*/*.cpp src/*.h src/*/*.h
#Check if BIN_DIR exists. If not, create it
ifeq ("$(wildcard $(BIN_DIR))","")
	mkdir bin
endif

	cd src; \
	g++ $(CFLAGS) -o pmc $(INCLUDES) *.cpp */*.cpp $(LIBS);
	mv src/pmc $(BIN_DIR)

clean:
ifneq ("$(wildcard $(BIN_FILE))", "")
	rm $(BIN_FILE)
endif
