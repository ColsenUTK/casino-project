CXX=		g++
CXXFLAGS=	-g -Wall -std=gnu++11
SHELL=		bash

all:		bin/main

bin/main:	dev/main.cpp dev/Casino_Colsen.cpp dev/Casino_Porter.cpp dev/CardDeck.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f bin/main

main:	bin/main
	@echo Running main...
	./bin/main
