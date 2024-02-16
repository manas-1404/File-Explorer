CXX = g++
CXXFLAGS = -Wall -g

TARGET = stupidos

OBJS = FileSystem_srinivasgowda.o stupidOS_srinivasgowda.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

FileSystem_srinivasgowda.o: FileSystem_srinivasgowda.cpp FileSystem_srinivasgowda.h LinkedList_srinivasgowda.hpp Queue_srinivasgowda.hpp
	$(CXX) $(CXXFLAGS) -c FileSystem_srinivasgowda.cpp

stupidOS_srinivasgowda.o: stupidOS_srinivasgowda.cpp FileSystem_srinivasgowda.h
	$(CXX) $(CXXFLAGS) -c stupidOS_srinivasgowda.cpp

clean:
	rm -f $(TARGET) $(OBJS)
