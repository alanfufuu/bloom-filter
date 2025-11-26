# Compiler
CXX = g++

CXXFLAGS = -std=c++17 -Wall -O2 -g

TARGET = test

SRCS = main.cpp hash.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp hash.h
	$(CXX) $(CXXFLAGS) -c main.cpp

hash.o: hash.cpp hash.h
	$(CXX) $(CXXFLAGS) -c hash.cpp

clean:
	rm -f $(TARGET) $(OBJS)


