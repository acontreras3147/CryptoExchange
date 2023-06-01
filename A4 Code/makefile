# Anthony Norderhaug, Contreras
# CS 480 - Spring 2023
# RedID: 823899304, 824089247
#
# makefile for compiling all C and C++ source into 'cryptoexc' executable

PROGRAM = cryptoexc
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g3 -c

# Dependencies - C++ and C
DEPS_CPP = Brokerage.h Buffer.h Consumer.h Producer.h Request.h Service.h Synch.h
DEPS_C = cryptoexchange.h log.h

# Object files
OBJS = main.o Brokerage.o Buffer.o Consumer.o log.o Producer.o Request.o Service.o Synch.o

%.o: %.cpp $(DEPS_CPP)
	$(CXX) $(CXXFLAGS) -o $@ $<

%.o: %.c $(DEPS_C)
	gcc -c $<

$(PROGRAM) : $(OBJS)
	$(CXX) -pthread -o $(PROGRAM) $(OBJS)

clean :
	rm -f *.o $(PROGRAM)