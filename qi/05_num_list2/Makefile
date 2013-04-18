RM       := rm -f
CXXFLAGS := -std=c++11 -Wall -g
TARGET   := num_list2

all : $(TARGET)

.PHONY : all clean

$(TARGET) : $(TARGET).o
	$(CXX) -o $@ $+

clean :
	$(RM) $(TARGET).o $(TARGET)
