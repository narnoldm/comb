CXX=g++
CXXFLAGS= -g


MAIN= main.exe
BDIR=./bin
SDIR=./src
DEP= readChem.o\


all: main

main: 
	$(CXX) $(CXXGLAGS) $(SDIR)/main.cpp -o $(BDIR)/main.exe




.PHONY: clean

clean:
	rm -f $(BDIR)/*.exe 
	rm -rf *.o
	rm -rf *.exe

