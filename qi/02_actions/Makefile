RM       := rm -f
CXXFLAGS := -std=c++11 -Wall -g

all : actions

.PHONY : all clean

actions : actions.o
	$(CXX) -o $@ $+

clean :
	$(RM) actions.o actions
