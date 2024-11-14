# Trey Rubino

CXX = g++            # compiler
CXXFLAGS = -Wall -g  # debug flags
TARGET = client  	 # build name

all: $(TARGET)

$(TARGET): Parser.o Socket.o Utility.o Client.o main.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) Parser.o Socket.o Utility.o Client.o main.o

Parser.o: Parser.cpp
	$(CXX) $(CXXFLAGS) -c Parser.cpp

Socket.o: Socket.cpp
	$(CXX) $(CXXFLAGS) -c Socket.cpp

Utility.o: Utility.cpp
	$(CXX) $(CXXFLAGS) -c Utility.cpp

Client.o: Client.cpp
	$(CXX) $(CXXFLAGS) -c Client.cpp

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o $(TARGET)

submit:
	~schwesin/bin/submit cpsc328 project5

.PHONY: submit clean
