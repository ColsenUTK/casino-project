CXX=		g++
CXXFLAGS=	-g -Wall -std=gnu++11
SHELL=		bash

all:		bin/test

bin/test:	dev/main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f bin/test

main:	bin/test
	@echo Running main...
	./bin/test
