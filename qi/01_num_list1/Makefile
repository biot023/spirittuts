RM       := rm -f
CXXFLAGS := -std=c++11 -Wall -g

all : num_list1

.PHONY : all clean

num_list1 : num_list1.o
	$(CXX) -o $@ $+

clean :
	$(RM) num_list1.o num_list1
