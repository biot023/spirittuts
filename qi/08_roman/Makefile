RM       := rm -f
CXXFLAGS := -std=c++11 -Wall -g
TARGET   := roman

all : $(TARGET)

.PHONY : all clean

$(TARGET) : $(TARGET).o
	$(CXX) -o $@ $+

clean :
	$(RM) $(TARGET).o $(TARGET)
