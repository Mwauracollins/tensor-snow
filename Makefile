CC = g++
CFLAGS = -Wall -fPIC -Iheaders
LDFLAGS = -shared
TARGET = build/libtensor.dll  # Generate .dll instead of .so

SRC = src/tensor.cpp
HEADERS = headers/tensor.h

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o
