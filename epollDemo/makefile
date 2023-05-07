CXX = g++

CFLAGS = -Wall -g

TARGET = main

$(TARGET): main.cpp mySocket.cpp mySocket.h
	$(CXX) $(CFLAGS) $^ -o $@
clean:
	rm -f $(TARGET)
