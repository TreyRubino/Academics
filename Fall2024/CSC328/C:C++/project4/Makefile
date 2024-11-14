# Trey Rubino

CXX = g++		# compiler
CXXFLAGS = -Wall -g	# debug flags
TARGET = webserver	# build name

all: $(TARGET)

$(TARGET): Parser.o Socket.o Session.o Utility.o main.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) Parser.o Socket.o Session.o Utility.o main.o

Parser.o: Parser.cpp
	$(CXX) $(CXXFLAGS) -c Parser.cpp

Socket.o: Socket.cpp
	$(CXX) $(CXXFLAGS) -c Socket.cpp

Session.o: Session.cpp
	$(CXX) $(CXXFLAGS) -c Session.cpp

Utility.o: Utility.cpp
	$(CXX) $(CXXFLAGS) -c Utility.cpp

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o $(TARGET)

submit:
	~schwesin/bin/submit cpsc328 project4

.PHONY: submit clean
