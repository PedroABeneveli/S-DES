CXX = g++
CXXFLAGS = -Iheaders -Wall

SRC_DIR = src
HEADER_DIR = headers

SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/bit_ops.cpp $(SRC_DIR)/modes.cpp $(SRC_DIR)/sdes.cpp $(SRC_DIR)/utils.cpp

OUTPUT = sdes

$(OUTPUT): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OUTPUT)