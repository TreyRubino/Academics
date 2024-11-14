# Trey Rubino

CXX = g++            # compiler
CXXFLAGS = -Wall -g  # debug flags
TARGET = server  	 # build name

all: $(TARGET)

$(TARGET): Parser.o Socket.o Utility.o Session.o Server.o main.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) Parser.o Socket.o Utility.o Session.o Server.o main.o

Parser.o: Parser.cpp
	$(CXX) $(CXXFLAGS) -c Parser.cpp

Socket.o: Socket.cpp
	$(CXX) $(CXXFLAGS) -c Socket.cpp

Utility.o: Utility.cpp
	$(CXX) $(CXXFLAGS) -c Utility.cpp

Session.o: Session.cpp
	$(CXX) $(CXXFLAGS) -c Session.cpp

Server.o: Server.cpp
	$(CXX) $(CXXFLAGS) -c Server.cpp

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o $(TARGET)

submit:
	~schwesin/bin/submit cpsc328 project6

.PHONY: submit clean
